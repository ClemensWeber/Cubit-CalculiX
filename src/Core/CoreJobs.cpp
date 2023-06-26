#include "CoreJobs.hpp"
#include "CalculiXCoreInterface.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"

#include "PyBroker.hpp"

#include "CubitProcess.hpp"
#include "CubitString.hpp"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fstream>
#include <iostream>
#include "loadUserOptions.hpp"

CoreJobs::CoreJobs()
{}

CoreJobs::~CoreJobs()
{}

bool CoreJobs::init()
{
  if (is_initialized)
  {
    return false; // already initialized
  }else{
    CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();
    is_initialized = true;  
    return true;
  }
}

bool CoreJobs::update()
{ 
  return true;
}

bool CoreJobs::reset()
{
  jobs_data.clear();
  CubitProcessHandler.clear();

  init();
  return true;
}

bool CoreJobs::check_initialized()
{
  return is_initialized;
}

bool CoreJobs::create_job(std::vector<std::string> options)
{
  int job_id;
  int job_last;
  
  if (jobs_data.size()==0)
  {
    job_id = 1;
  }
  else
  {
    job_last = jobs_data.size() - 1;
    job_id = std::stoi(jobs_data[job_last][0]) + 1;
  }

  this->add_job(job_id, options[0], options[1]);
  return true;
}

bool CoreJobs::modify_job(int job_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  int jobs_data_id = get_jobs_data_id_from_job_id(job_id);
  
  if (jobs_data_id == -1)
  {
    return false;
  } else {
    // name
    if (options_marker[0]==1)
    {
      jobs_data[jobs_data_id][1] = options[0];
    }
    // filepath
    if (options_marker[1]==1)
    {
      jobs_data[jobs_data_id][2] = options[1];
    }
    return true;
  }
}

bool CoreJobs::add_job(int job_id, std::string name, std::string filepath)
{
  std::vector<std::string> v = {std::to_string(job_id), name, filepath, "-1", "-1","","-1","",""};      
  jobs_data.push_back(v);
  return true;
}

bool CoreJobs::delete_job(int job_id)
{
  int jobs_data_id = get_jobs_data_id_from_job_id(job_id);
  if (jobs_data_id == -1)
  {
    return false;
  } else {
    jobs_data.erase(jobs_data.begin() + jobs_data_id);
    return true;
  }
}

bool CoreJobs::run_job(int job_id)
{  
  std::string filepath;
  std::string log;
  std::string command;
  pid_t process_id;
  int int_wait;
  int CubitProcessHandler_data_id;
  CubitString programm;
  CubitString working_dir;
  CubitString temp;
  CubitString output;
  std::vector<CubitString> arguments(3);

  if (access(ccx_uo.mPathSolver.toStdString().c_str(), X_OK) == 0) 
  {
    setenv("OMP_NUM_THREADS",std::to_string(ccx_uo.mSolverThreads).c_str(),1);
  }else{
    log = "CCX Solver not found! checked path \"" + ccx_uo.mPathSolver.toStdString() + "\" \n";
    PRINT_INFO("%s", log.c_str());    
    return false;
  }

  int job_data_id;
  job_data_id = get_jobs_data_id_from_job_id(job_id);
  if (job_data_id != -1)
  {
    // create or get cubitprocess
    CubitProcessHandler_data_id = get_CubitProcessHandler_data_id_from_process_id(std::stoi(jobs_data[job_data_id][4]));
    if (CubitProcessHandler_data_id == -1)
    {
      CubitProcess newCubitProcess;
      CubitProcessHandler.push_back(newCubitProcess);
      CubitProcessHandler_data_id = CubitProcessHandler.size()-1;
    }else{
      log = "Kill Job " + jobs_data[job_data_id][1] + " with ID " + jobs_data[job_data_id][0] + " if already running \n";
      jobs_data[job_data_id][5] = "";
      PRINT_INFO("%s", log.c_str());
      CubitProcessHandler[CubitProcessHandler_data_id].kill();
      CubitProcessHandler[CubitProcessHandler_data_id].wait();
      //log = " Job killed with Exit Code " + std::to_string(CubitProcessHandler[CubitProcessHandler_data_id].exit_code()) + " \n";
      log = " Job killed!\n";
      PRINT_INFO("%s", log.c_str());
      jobs_data[job_data_id][3] = "3";
    }

    if (jobs_data[job_data_id][2]!="")
    {
      std::string shellstr;
      shellstr = "cp '" + jobs_data[job_data_id][2] + "' '" +jobs_data[job_data_id][1] + ".inp'";
      system(shellstr.c_str());
      filepath = jobs_data[job_data_id][1] + ".inp";
    } else {
      filepath = jobs_data[job_data_id][1] + ".inp";
      log = "Exporting Job " + jobs_data[job_data_id][1] + " with ID " + jobs_data[job_data_id][0] + " to \n";
      log.append(filepath +  " \n");
      PRINT_INFO("%s", log.c_str());
      command = "export ccx \"" + filepath + "\"";
      CubitInterface::cmd(command.c_str());
      if (CubitInterface::was_last_cmd_undoable())
      {
        return false;
      }
    }

    programm = ccx_uo.mPathSolver.toStdString().c_str();
    arguments[0] = "-i";
    arguments[1] = filepath.substr(0, filepath.size()-4);
    arguments[2] = NULL;
    
    
    CubitProcessHandler[CubitProcessHandler_data_id].set_program(programm);
    CubitProcessHandler[CubitProcessHandler_data_id].set_arguments(arguments);
    CubitProcessHandler[CubitProcessHandler_data_id].set_channel_mode(CubitProcess::ChannelMode::MergedChannels);
    temp = CubitProcessHandler[CubitProcessHandler_data_id].find_executable(programm);
    jobs_data[job_data_id][5] = "";
    jobs_data[job_data_id][7] = "";
    jobs_data[job_data_id][8] = "";
    CubitProcessHandler[CubitProcessHandler_data_id].start();
    process_id = CubitProcessHandler[CubitProcessHandler_data_id].pid();
    if (process_id!=0)
    { 
      jobs_data[job_data_id][4] = std::to_string(process_id);
      jobs_data[job_data_id][3] = "1";
      jobs_data[job_data_id][6] = "-1";
      /*
      log = " Path to executable ";
      log.append(working_dir.str() + temp.str() + "\n");
      log.append(temp.str() + "\n");
      log = " Output " + output.str() + " \n";
      PRINT_INFO("%s", log.c_str());
      */
    }
    return true;
  } else {
    return false;
  }
}

bool CoreJobs::wait_job(int job_id)
{  
  std::string log;
  CubitString output;
  int status=-1;
  
  int jobs_data_id=-1;
  int CubitProcessHandler_data_id;
  
  jobs_data_id = get_jobs_data_id_from_job_id(job_id);

  if (jobs_data_id != -1)
  {
    CubitProcessHandler_data_id = get_CubitProcessHandler_data_id_from_process_id(std::stoi(jobs_data[jobs_data_id][4]));
    if (CubitProcessHandler_data_id != -1)
    {
      
      
      log = " Waiting for Job " + jobs_data[jobs_data_id][2] + " to Exit \n";
      PRINT_INFO("%s", log.c_str());
          
      while (0 == kill(std::stoi(jobs_data[jobs_data_id][4]),0))
      {
        output = CubitProcessHandler[CubitProcessHandler_data_id].read_output_channel(-1);
        if (output != "")
        {
          log = " Output " + output.str() + " \n";
          //PRINT_INFO("%s", log.c_str());
          jobs_data[jobs_data_id][5] = jobs_data[jobs_data_id][5] + output.str();
          output = "";
          get_cvgsta(std::stoi(jobs_data[jobs_data_id][0]));
        }
        waitpid(std::stoi(jobs_data[jobs_data_id][4]), &status,WNOHANG);      
      }

      //errorcode = CubitProcessHandler[CubitProcessHandler_data_id].exit_code();
      if (status!=0)
      {
        log = "Job " + jobs_data[jobs_data_id][1] + " with ID " + jobs_data[jobs_data_id][0] + " exited with errors! \n";
        //log.append(" Exit Code " + std::to_string(errorcode) + " \n");
        PRINT_INFO("%s", log.c_str());
        jobs_data[jobs_data_id][3] = "4";
      }else{
        log = "Job " + jobs_data[jobs_data_id][1] + " with ID " + jobs_data[jobs_data_id][0] + " finished! \n";
        //log.append(" Exit Code " + std::to_string(errorcode) + " \n");
        PRINT_INFO("%s", log.c_str());
        jobs_data[jobs_data_id][3] = "2";
      }
      CubitProcessHandler.erase(CubitProcessHandler.begin() + CubitProcessHandler_data_id);
    }
  }

  return true;
}

bool CoreJobs::kill_job(int job_id)
{  
  std::string log;
  CubitString output;
  
  int jobs_data_id=-1;
  int CubitProcessHandler_data_id;
  
  jobs_data_id = get_jobs_data_id_from_job_id(job_id);

  if (jobs_data_id != -1)
  {
    CubitProcessHandler_data_id = get_CubitProcessHandler_data_id_from_process_id(std::stoi(jobs_data[jobs_data_id][4]));
    if (CubitProcessHandler_data_id != -1)
    {
      log = " Kill the Job " + jobs_data[jobs_data_id][2] + " \n";
      PRINT_INFO("%s", log.c_str());
      CubitProcessHandler[CubitProcessHandler_data_id].kill();
      CubitProcessHandler[CubitProcessHandler_data_id].wait();
      log = " Job killed with Exit Code " + std::to_string(CubitProcessHandler[CubitProcessHandler_data_id].exit_code()) + " \n";
      PRINT_INFO("%s", log.c_str());
      jobs_data[jobs_data_id][3] = "3";
      CubitProcessHandler.erase(CubitProcessHandler.begin() + CubitProcessHandler_data_id);
    }
  }

  return true;
}

bool CoreJobs::check_jobs()
{
  std::string log;
  CubitString output;
  
  int CubitProcessHandler_data_id;
  
  for (size_t i = 0; i < jobs_data.size(); i++)
  {
    // create or get cubitprocess
    CubitProcessHandler_data_id = get_CubitProcessHandler_data_id_from_process_id(std::stoi(jobs_data[i][4]));
        
    if (CubitProcessHandler_data_id != -1)
    {
      /*log = "Job ID " + jobs_data[i][0] + " \n";
      log.append("Job PID " + jobs_data[i][4] + " \n");
      log.append("PID " + std::to_string(CubitProcessHandler[CubitProcessHandler_data_id].pid()) + " \n");
      log.append("CubitProcessHandler_data_id " + std::to_string(CubitProcessHandler_data_id) + " \n");
      PRINT_INFO("%s", log.c_str());*/

      if (std::stoi(jobs_data[i][3])==1)
      {
        // check for output
        int ic=0;
        while (CubitProcessHandler[CubitProcessHandler_data_id].can_read_output())
        { 
          output = CubitProcessHandler[CubitProcessHandler_data_id].read_output_channel(1);
          if (output != "")
          {
            log = " Output " + output.str() + " \n";
            //PRINT_INFO("%s", log.c_str());
            jobs_data[i][5] = jobs_data[i][5] + output.str();
            output = "";
            get_cvgsta(std::stoi(jobs_data[i][0]));
          }else{
            ic+=1;
          }
          
          // break out of loop, so that output reading doesn't freeze gui
          if (ic==10)
          {
            break;
          }          
        }

        //solver processes still running?
        int status;
        waitpid(std::stoi(jobs_data[i][4]), &status,WNOHANG);
        //log = " wait Code " + std::to_string(status) + " \n";
        //PRINT_INFO("%s", log.c_str());
        
        if ((0 != kill(std::stoi(jobs_data[i][4]),0)) && (status!=0)) // if process doesn't exist and exited with error
        {
          CubitProcessHandler[CubitProcessHandler_data_id].wait();
          log = "Job " + jobs_data[i][1] + " with ID " + jobs_data[i][0] + " exited with errors! \n";
          //log.append(" Exit Code " + std::to_string(CubitProcessHandler[CubitProcessHandler_data_id].exit_code()) + " \n");
          PRINT_INFO("%s", log.c_str());
          jobs_data[i][3] = "4";
          CubitProcessHandler.erase(CubitProcessHandler.begin() + CubitProcessHandler_data_id);
        }else if ((0 != kill(std::stoi(jobs_data[i][4]),0)) && (status==0)) // if process doesn't exist and exited without error
        {
          CubitProcessHandler[CubitProcessHandler_data_id].wait();
          log = "Job " + jobs_data[i][1] + " with ID " + jobs_data[i][0] + " finished! \n";
          //log.append(" Exit Code " + std::to_string(CubitProcessHandler[CubitProcessHandler_data_id].exit_code()) + " \n");
          PRINT_INFO("%s", log.c_str());
          jobs_data[i][3] = "2";
          CubitProcessHandler.erase(CubitProcessHandler.begin() + CubitProcessHandler_data_id);
        }
      }
    }
  }

  return true;
}

bool CoreJobs::get_cvgsta(int job_id)
{
  int jobs_data_id=-1;
  
  jobs_data_id = get_jobs_data_id_from_job_id(job_id);

  if (jobs_data_id != -1)
  {
    std::string cvg = "";
    std::string sta = "";
    std::string cvgline = "";
    std::string staline = "";
    std::ifstream cvgfile;
    std::ifstream stafile;
    cvgfile.open(jobs_data[jobs_data_id][1] + ".cvg");
    stafile.open(jobs_data[jobs_data_id][1] + ".sta");
    if (cvgfile.is_open())
    {
      while (cvgfile)
      {
        std::getline(cvgfile,cvgline);
        cvg.append(cvgline + "\n");
      }

      jobs_data[jobs_data_id][7] = cvg;
    }
    if (stafile.is_open())
    {
      while (stafile)
      {
        std::getline(stafile,staline);
        sta.append(staline + "\n");
      }
      jobs_data[jobs_data_id][8] = sta;
    }
    cvgfile.close();
    stafile.close();
  }
  return true;
}

bool CoreJobs::check_zombie()
{
  std::string log;
  CubitString output;
  
  int CubitProcessHandler_data_id;
  
  for (size_t ci = 0; ci < CubitProcessHandler.size(); ci++)
  {
    for (size_t i = 0; i < jobs_data.size(); i++)
    {
      // create or get cubitprocess
      CubitProcessHandler_data_id = get_CubitProcessHandler_data_id_from_process_id(std::stoi(jobs_data[i][4]));
          
      if (CubitProcessHandler_data_id == -1)
      {
        //result processes still running?
        int status;
        waitpid(CubitProcessHandler[ci].pid(), &status,WNOHANG);
        //log = "Result wait Code " + std::to_string(status) + " \n";
        //PRINT_INFO("%s", log.c_str());
          
        if ((0 != kill(CubitProcessHandler[ci].pid(),0)) && (status!=0)) // if process doesn't exist and exited with error
        {
          CubitProcessHandler[ci].wait();
          //log = "Result Exit Code " + std::to_string(CubitProcessHandler[ci].exit_code()) + " \n";
          //PRINT_INFO("%s", log.c_str());
          CubitProcessHandler.erase(CubitProcessHandler.begin() + ci);
        }else if ((0 != kill(CubitProcessHandler[ci].pid(),0)) && (status==0)) // if process doesn't exist and exited without error
        {
          CubitProcessHandler[ci].wait();
          //log = "Result Exit Code " + std::to_string(CubitProcessHandler[ci].exit_code()) + " \n";
          //PRINT_INFO("%s", log.c_str());
          CubitProcessHandler.erase(CubitProcessHandler.begin() + ci);
        }
      }
    }
  }
  return true;
}

bool CoreJobs::result_ccx2paraview_job(int job_id)
{
  std::string log;
  std::string filepath;
  std::vector<std::string> cmd;

  if (access(ccx_uo.mPathccx2paraview.toStdString().c_str(), F_OK) == 0) 
  {
  }else{
    log = "ccx2paraview not found! checked path \"" + ccx_uo.mPathccx2paraview.toStdString() + "\" \n";
    PRINT_INFO("%s", log.c_str());    
    return false;
  }

  int job_data_id;
  job_data_id = get_jobs_data_id_from_job_id(job_id);
  if (job_data_id != -1)
  {
    if (std::stoi(jobs_data[job_data_id][3])>1)
    {
      std::string shellstr;
      shellstr = "rm " + jobs_data[job_data_id][1] + "*vtk";
      system(shellstr.c_str());

      filepath = jobs_data[job_data_id][1] + ".frd";
      cmd.push_back("import subprocess");
      cmd.push_back("print('Converting Results... GUI may freeze. This can take some time.')");
      cmd.push_back("returned_value = subprocess.call(\"python3 " + ccx_uo.mPathccx2paraview.toStdString() + " " +  filepath + " vtk\",shell=True)");
      cmd.push_back("if returned_value==0: print('Finished')\nelse:print('Error occurred!')");
      PyBroker::run_script(cmd);
      jobs_data[job_data_id][6] = "1";
    }  
  }

  return true;
}

bool CoreJobs::result_cgx_job(int job_id)
{
  std::string filepath;
  std::string log;
  std::string command;

  if (access(ccx_uo.mPathCGX.toStdString().c_str(), X_OK) == 0) 
  {
  }else{
    log = "CGX not found! checked path \"" + ccx_uo.mPathCGX.toStdString() + "\" \n";
    PRINT_INFO("%s", log.c_str());    
    return false;
  }

  int job_data_id;
  job_data_id = get_jobs_data_id_from_job_id(job_id);
  if (job_data_id != -1)
  {    
    if (std::stoi(jobs_data[job_data_id][3])>1)
    {
      filepath = jobs_data[job_data_id][1] + ".frd";

      std::string shellstr;
      shellstr = "nohup " + ccx_uo.mPathCGX.toStdString() + " " + filepath + " &";
      system(shellstr.c_str());

      log = "Opening Results with CGX for Job " + jobs_data[job_data_id][1] + " with ID " + jobs_data[job_data_id][0] + "\n";
      //log.append(filepath +  " \n");
      PRINT_INFO("%s", log.c_str());
    }
  } else {
    return false;
  }
  return true;
}

bool CoreJobs::result_paraview_job(int job_id)
{  
  std::string filepath;
  std::string log;
  std::string command;

  if (access(ccx_uo.mPathParaView.toStdString().c_str(), X_OK) == 0) 
  {
  }else{
    log = "ParaView not found! checked path \"" + ccx_uo.mPathParaView.toStdString() + "\" \n";
    PRINT_INFO("%s", log.c_str());    
    return false;
  }

  int job_data_id;
  job_data_id = get_jobs_data_id_from_job_id(job_id);
  if (job_data_id != -1)
  {    
    if ((std::stoi(jobs_data[job_data_id][3])>1) && (jobs_data[job_data_id][6] == "1"))
    {      
      filepath = jobs_data[job_data_id][1] + ".vtk";
      if (access(filepath.c_str(), W_OK) != 0) 
      {
        filepath = jobs_data[job_data_id][1] + "...vtk";
      }

      std::string shellstr;
      shellstr = "nohup " + ccx_uo.mPathParaView.toStdString() + " --data=" + filepath + " &";
      system(shellstr.c_str());

      log = "Opening Results with Paraview for Job " + jobs_data[job_data_id][1] + " with ID " + jobs_data[job_data_id][0] + "\n";
      //log.append(filepath +  " \n");
      //log.append(arg +  " \n");
      PRINT_INFO("%s", log.c_str());
    }
  } else {
    return false;
  }
  return true;  
}

int CoreJobs::get_jobs_data_id_from_job_id(int job_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < jobs_data.size(); i++)
  {
    if (jobs_data[i][0]==std::to_string(job_id))
    {
      return_int = i;
    }  
  }
  return return_int;
}

int CoreJobs::get_CubitProcessHandler_data_id_from_process_id(int process_id)
{ 
  int return_int = -1;
  
  for (size_t i = 0; i < CubitProcessHandler.size(); i++)
  {
    if (process_id == CubitProcessHandler[i].pid())
    {
      return_int = i;
    }  
  }
  
  return return_int;
}

std::vector<std::string> CoreJobs::get_job_data(int job_id)
{
  int job_data_id;
  job_data_id = get_jobs_data_id_from_job_id(job_id);
  if (job_data_id != -1)
  {
    return jobs_data[job_data_id];
  }else{
    std::vector<std::string> tmp;
    return tmp;
  }
}

std::string CoreJobs::print_data()
{
  std::string str_return;
  str_return = "\n CoreJobs jobs_data: \n";
  str_return.append("job_id, name, filepath, status, process id, output \n");

  for (size_t i = 0; i < jobs_data.size(); i++)
  {
    str_return.append(jobs_data[i][0] + " " + jobs_data[i][1] + " " + jobs_data[i][2] + " " + jobs_data[i][3] + " " + jobs_data[i][4] + " \n");
    str_return.append(jobs_data[i][5] + " \n");
    str_return.append(jobs_data[i][6] + " \n");
    str_return.append(jobs_data[i][7] + " \n");
    str_return.append(jobs_data[i][8] + " \n");
  }

  return str_return;
}