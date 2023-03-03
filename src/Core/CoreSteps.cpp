#include "CoreSteps.hpp"
#include "CubitInterface.hpp"
#include "CalculiXCoreInterface.hpp"

CoreSteps::CoreSteps()
{}

CoreSteps::~CoreSteps()
{}

bool CoreSteps::init()
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

bool CoreSteps::update()
{ 
  return true;
}

bool CoreSteps::reset()
{
  steps_data.clear();
  name_data.clear();
  parameter_data.clear();
  static_data.clear();
  frequency_data.clear();
  buckle_data.clear();
  heattransfer_data.clear();
  coupledtd_data.clear();
  uncoupledtd_data.clear();
  loads_data.clear();
  bcs_data.clear();
  
  init();
  return true;
}

bool CoreSteps::check_initialized()
{
  return is_initialized;
}

bool CoreSteps::create_step(std::vector<std::string> options)
{
  int step_id;
  int step_last;
  int sub_id;
  int sub_last;
  int name_id;
  int parameter_id;
  int step_type;
  int step_type_id;
  int loads_id;
  int bcs_id;
  
  if (steps_data.size()==0)
  {
    step_id = 1;
  }
  else
  {
    step_last = steps_data.size() - 1;
    step_id = steps_data[step_last][0] + 1;
  }

  // name
  if (name_data.size()==0)
  {
    sub_id = 1;
  }
  else
  {
    sub_last = name_data.size() - 1;
    sub_id = std::stoi(name_data[sub_last][0]) + 1;
  }
  name_id = sub_id;
  this->add_name(std::to_string(sub_id), options[0]);

  // parameter
  if (parameter_data.size()==0)
  {
    sub_id = 1;
  }
  else
  {
    sub_last = parameter_data.size() - 1;
    sub_id = std::stoi(parameter_data[sub_last][0]) + 1;
  }
  parameter_id = sub_id;
  this->add_parameter(std::to_string(sub_id));

  // step_type
  step_type = std::stoi(options[1]);
  
  if (step_type == 1)
  {  // noanalysis
    step_type_id = -1;
  }else if (step_type == 2)
  {  // static
    if (static_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = static_data.size() - 1;
      sub_id = std::stoi(static_data[sub_last][0]) + 1;
    }
    step_type_id = sub_id;
    this->add_static(std::to_string(sub_id));
  }else if (step_type == 3)
  {  // frequency
    if (frequency_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = frequency_data.size() - 1;
      sub_id = std::stoi(frequency_data[sub_last][0]) + 1;
    }
    step_type_id = sub_id;
    this->add_frequency(std::to_string(sub_id));
  }else if (step_type == 4)
  {  // buckle
    if (buckle_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = buckle_data.size() - 1;
      sub_id = std::stoi(buckle_data[sub_last][0]) + 1;
    }
    step_type_id = sub_id;
    this->add_buckle(std::to_string(sub_id));
  }else if (step_type == 5)
  {  // heattransfer
    if (heattransfer_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = heattransfer_data.size() - 1;
      sub_id = std::stoi(heattransfer_data[sub_last][0]) + 1;
    }
    step_type_id = sub_id;
    this->add_heattransfer(std::to_string(sub_id));
  }else if (step_type == 6)
  {  // coupledtd
    if (coupledtd_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = coupledtd_data.size() - 1;
      sub_id = std::stoi(coupledtd_data[sub_last][0]) + 1;
    }
    step_type_id = sub_id;
    this->add_coupledtd(std::to_string(sub_id));
  }else if (step_type == 7)
  {  // uncoupledtd
    if (uncoupledtd_data.size()==0)
    {
      sub_id = 1;
    }
    else
    {
      sub_last = uncoupledtd_data.size() - 1;
      sub_id = std::stoi(uncoupledtd_data[sub_last][0]) + 1;
    }
    step_type_id = sub_id;
    this->add_uncoupledtd(std::to_string(sub_id));
  }
  
  loads_id = step_id;

  bcs_id = step_id;

  this->add_step(step_id, name_id, parameter_id, step_type, step_type_id, loads_id, bcs_id);
  return true;
}

bool CoreSteps::modify_step(int step_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker)
{
  int sub_data_id;
  int steps_data_id = get_steps_data_id_from_step_id(step_id);
  //modify_type = 0 for changing name

  if (steps_data_id == -1)
  {
    return false;
  } else {
    // name
    if (modify_type==0)
    {
      if (options_marker[0]==1)
      {
        sub_data_id = get_name_data_id_from_name_id(steps_data[steps_data_id][1]);
        name_data[sub_data_id][1] = options[0];
      }
    }
    // parameter
    if (modify_type==1)
    {
      sub_data_id = get_parameter_data_id_from_parameter_id(steps_data[steps_data_id][2]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          parameter_data[sub_data_id][i+1] = options[i];
        }
      }
    }

    if ((steps_data[steps_data_id][3]==2) && (steps_data[steps_data_id][3]==modify_type))
    { // static
      sub_data_id = get_static_data_id_from_static_id(steps_data[steps_data_id][4]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          static_data[sub_data_id][i+1] = options[i];
        }
      }
    }else if ((steps_data[steps_data_id][3]==3) && (steps_data[steps_data_id][3]==modify_type))
    { // frequency
      sub_data_id = get_frequency_data_id_from_frequency_id(steps_data[steps_data_id][4]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          frequency_data[sub_data_id][i+1] = options[i];
        }
      }
    }else if ((steps_data[steps_data_id][3]==4) && (steps_data[steps_data_id][3]==modify_type))
    { // buckle
      sub_data_id = get_buckle_data_id_from_buckle_id(steps_data[steps_data_id][4]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          buckle_data[sub_data_id][i+1] = options[i];
        }
      }
    }else if ((steps_data[steps_data_id][3]==5) && (steps_data[steps_data_id][3]==modify_type))
    { // heattransfer
      sub_data_id = get_heattransfer_data_id_from_heattransfer_id(steps_data[steps_data_id][4]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          heattransfer_data[sub_data_id][i+1] = options[i];
        }
      }
    }else if ((steps_data[steps_data_id][3]==6) && (steps_data[steps_data_id][3]==modify_type))
    { // coupledtd
      sub_data_id = get_coupledtd_data_id_from_coupledtd_id(steps_data[steps_data_id][4]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          coupledtd_data[sub_data_id][i+1] = options[i];
        }
      }
    }else if ((steps_data[steps_data_id][3]==7) && (steps_data[steps_data_id][3]==modify_type))
    { // uncoupledtd
      sub_data_id = get_uncoupledtd_data_id_from_uncoupledtd_id(steps_data[steps_data_id][4]);
      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          uncoupledtd_data[sub_data_id][i+1] = options[i];
        }
      }
    }

    return true;
  }
}

bool CoreSteps::add_loads(int step_id, int load_type, std::vector<int> load_ids)
{
  int loads_id;
  int steps_data_id = get_steps_data_id_from_step_id(step_id);
  if (steps_data_id == -1)
  {
    return false;
  } else {
    loads_id = steps_data[steps_data_id][5];
    
    for (size_t i = 0; i < load_ids.size(); i++)
    {
      if (get_load_data_id(loads_id, load_type, load_ids[i])==-1)
      {
        add_load(loads_id, load_type, load_ids[i]);
      }
    }
    return true;
  }
}

bool CoreSteps::add_bcs(int step_id, int bc_type, std::vector<int> bc_ids)
{
  int bcs_id;
  int steps_data_id = get_steps_data_id_from_step_id(step_id);
  if (steps_data_id == -1)
  {
    return false;
  } else {
    bcs_id = steps_data[steps_data_id][6];
    
    for (size_t i = 0; i < bc_ids.size(); i++)
    {
      if (get_bc_data_id(bcs_id, bc_type, bc_ids[i])==-1)
      {
        add_bc(bcs_id, bc_type, bc_ids[i]);
      }
    }
    return true;
  }
}

bool CoreSteps::remove_loads(int step_id, int load_type, std::vector<int> load_ids)
{
  int loads_id;
  int loads_data_id;
  int steps_data_id = get_steps_data_id_from_step_id(step_id);
  if (steps_data_id == -1)
  {
    return false;
  } else {
    loads_id = steps_data[steps_data_id][5];
    
    for (size_t i = load_ids.size(); i > 0; i--)
    {
      loads_data_id = get_load_data_id(loads_id, load_type, load_ids[i-1]);
      if (loads_data_id!=-1)
      {
        loads_data.erase(loads_data.begin() + loads_data_id);
      }
    }
    return true;
  }
}

bool CoreSteps::remove_bcs(int step_id, int bc_type, std::vector<int> bc_ids)
{
  int bcs_id;
  int bcs_data_id;
  int steps_data_id = get_steps_data_id_from_step_id(step_id);
  if (steps_data_id == -1)
  {
    return false;
  } else {
    bcs_id = steps_data[steps_data_id][6];
    
    for (size_t i = bc_ids.size(); i > 0; i--)
    {
      bcs_data_id = get_bc_data_id(bcs_id, bc_type, bc_ids[i-1]);
      if (bcs_data_id!=-1)
      {
        bcs_data.erase(bcs_data.begin() + bcs_data_id);
      }
    }
    return true;
  }
}

bool CoreSteps::delete_step(int step_id)
{
  int sub_data_id;
  std::vector<int> sub_data_ids;
  int steps_data_id = get_steps_data_id_from_step_id(step_id);
  if (steps_data_id == -1)
  {
    return false;
  } else {
    sub_data_id = get_name_data_id_from_name_id(steps_data[steps_data_id][1]);
    if (sub_data_id != -1){
      name_data.erase(name_data.begin() + sub_data_id);  
    }
    sub_data_id = get_parameter_data_id_from_parameter_id(steps_data[steps_data_id][2]);
    if (sub_data_id != -1){
      parameter_data.erase(parameter_data.begin() + sub_data_id);  
    }
    if (steps_data[steps_data_id][3]==2)
    {
      sub_data_id = get_static_data_id_from_static_id(steps_data[steps_data_id][4]);
      if (sub_data_id != -1){
        static_data.erase(static_data.begin() + sub_data_id);  
      }
    }
    if (steps_data[steps_data_id][3]==3)
    {
      sub_data_id = get_frequency_data_id_from_frequency_id(steps_data[steps_data_id][4]);
      if (sub_data_id != -1){
        frequency_data.erase(frequency_data.begin() + sub_data_id);  
      }
    }
    if (steps_data[steps_data_id][3]==4)
    {
      sub_data_id = get_buckle_data_id_from_buckle_id(steps_data[steps_data_id][4]);
      if (sub_data_id != -1){
        buckle_data.erase(buckle_data.begin() + sub_data_id);  
      }
    }
    if (steps_data[steps_data_id][3]==5)
    {
      sub_data_id = get_heattransfer_data_id_from_heattransfer_id(steps_data[steps_data_id][4]);
      if (sub_data_id != -1){
        heattransfer_data.erase(heattransfer_data.begin() + sub_data_id);  
      }
    }
    if (steps_data[steps_data_id][3]==6)
    {
      sub_data_id = get_coupledtd_data_id_from_coupledtd_id(steps_data[steps_data_id][4]);
      if (sub_data_id != -1){
        coupledtd_data.erase(coupledtd_data.begin() + sub_data_id);  
      }
    }
    if (steps_data[steps_data_id][3]==7)
    {
      sub_data_id = get_uncoupledtd_data_id_from_uncoupledtd_id(steps_data[steps_data_id][4]);
      if (sub_data_id != -1){
        uncoupledtd_data.erase(uncoupledtd_data.begin() + sub_data_id);  
      }
    }
    sub_data_ids = get_load_data_ids_from_loads_id(steps_data[steps_data_id][5]);
    for (size_t i = sub_data_ids.size(); i > 0; i--)
    {
      loads_data.erase(loads_data.begin() + sub_data_ids[i-1]);
    }
    sub_data_ids = get_bc_data_ids_from_bcs_id(steps_data[steps_data_id][6]);
    for (size_t i = sub_data_ids.size(); i > 0; i--)
    {
      bcs_data.erase(bcs_data.begin() + sub_data_ids[i-1]);
    }
    steps_data.erase(steps_data.begin() + steps_data_id);
    return true;
  }
}

bool CoreSteps::add_step(int step_id, int name_id, int parameter_id, int step_type, int step_type_id, int loads_id, int bcs_id)
{
  std::vector<int> v = {step_id,name_id,parameter_id,step_type,step_type_id,loads_id,bcs_id};
 
  steps_data.push_back(v);

  return true;
}

bool CoreSteps::add_name(std::string name_id, std::string name)
{
  std::vector<std::string> v = {name_id, name};
  
  name_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_parameter(std::string parameter_id)
{
  std::vector<std::string> v = {parameter_id,"","","","","","",""};
  
  parameter_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_static(std::string static_id)
{
  std::vector<std::string> v = {static_id,"","","","","","","","","",""};
  
  static_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_frequency(std::string frequency_id)
{
  std::vector<std::string> v = {frequency_id,"","","","","","",""};
  
  frequency_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_buckle(std::string buckle_id)
{
  std::vector<std::string> v = {buckle_id,"","","","",""};
  
  buckle_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_heattransfer(std::string heattransfer_id)
{
  std::vector<std::string> v = {heattransfer_id,"","","","","","","","","","","","",""};
  
  heattransfer_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_coupledtd(std::string coupledtd_id)
{
  std::vector<std::string> v = {coupledtd_id,"","","","","","","","","","","","",""};
  
  coupledtd_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_uncoupledtd(std::string uncoupledtd_id)
{
  std::vector<std::string> v = {uncoupledtd_id,"","","","","","","","","","","",""};
  
  uncoupledtd_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_load(int loads_id, int load_type, int load_id)
{
  std::vector<int> v = {loads_id, load_type, load_id};
  
  loads_data.push_back(v);
  
  return true;
}

bool CoreSteps::add_bc(int bcs_id, int load_type, int load_id)
{
  std::vector<int> v = {bcs_id, load_type, load_id};
  
  bcs_data.push_back(v);
  
  return true;
}

int CoreSteps::get_steps_data_id_from_step_id(int step_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < steps_data.size(); i++)
  {
    if (steps_data[i][0]==step_id)
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_name_data_id_from_name_id(int name_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < name_data.size(); i++)
  {
    if (name_data[i][0]==std::to_string(name_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_parameter_data_id_from_parameter_id(int parameter_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < parameter_data.size(); i++)
  {
    if (parameter_data[i][0]==std::to_string(parameter_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_static_data_id_from_static_id(int static_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < static_data.size(); i++)
  {
    if (static_data[i][0]==std::to_string(static_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_frequency_data_id_from_frequency_id(int frequency_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < frequency_data.size(); i++)
  {
    if (frequency_data[i][0]==std::to_string(frequency_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_buckle_data_id_from_buckle_id(int buckle_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < buckle_data.size(); i++)
  {
    if (buckle_data[i][0]==std::to_string(buckle_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_heattransfer_data_id_from_heattransfer_id(int heattransfer_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < heattransfer_data.size(); i++)
  {
    if (heattransfer_data[i][0]==std::to_string(heattransfer_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_coupledtd_data_id_from_coupledtd_id(int coupledtd_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < coupledtd_data.size(); i++)
  {
    if (coupledtd_data[i][0]==std::to_string(coupledtd_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_uncoupledtd_data_id_from_uncoupledtd_id(int uncoupledtd_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < uncoupledtd_data.size(); i++)
  {
    if (uncoupledtd_data[i][0]==std::to_string(uncoupledtd_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_load_data_id(int loads_id, int load_type,int load_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < loads_data.size(); i++)
  {
    if ((loads_data[i][0]==loads_id) && (loads_data[i][1]==load_type) && (loads_data[i][2]==load_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSteps::get_bc_data_id(int bcs_id, int bc_type,int bc_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < bcs_data.size(); i++)
  {
    if ((bcs_data[i][0]==bcs_id) && (bcs_data[i][1]==bc_type) && (bcs_data[i][2]==bc_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

std::vector<int> CoreSteps::get_load_data_ids_from_loads_id(int loads_id)
{ 
  std::vector<int> return_int;
  for (size_t i = 0; i < loads_data.size(); i++)
  {
    if (loads_data[i][0]==loads_id)
    {
        return_int.push_back(i);
    }  
  }
  return return_int;
}

std::vector<int> CoreSteps::get_bc_data_ids_from_bcs_id(int bcs_id)
{ 
  std::vector<int> return_int;
  for (size_t i = 0; i < bcs_data.size(); i++)
  {
    if (bcs_data[i][0]==bcs_id)
    {
        return_int.push_back(i);
    }  
  }
  return return_int;
}

std::string CoreSteps::get_step_export() // get a list of the CalculiX step exports
{
  std::vector<std::string> steps_export_list;
  steps_export_list.push_back("********************************** S T E P S ****************************");
  std::string str_temp;
  int sub_data_id;
  std::vector<int> sub_data_ids;
  /*
  //loop over all amplitudes
  for (size_t i = 0; i < amplitudes_data.size(); i++)
  { 
    str_temp = "*AMPLITUDE, NAME=";
    sub_data_id = get_name_amplitude_data_id_from_name_amplitude_id(amplitudes_data[i][1]);
    str_temp.append(name_amplitude_data[sub_data_id][1]);
    //shiftx
    sub_data_id = get_shiftx_amplitude_data_id_from_shiftx_amplitude_id(amplitudes_data[i][2]);
    if(shiftx_amplitude_data[sub_data_id][1]!="")
    {
      str_temp.append(", SHIFTX=");
      str_temp.append(shiftx_amplitude_data[sub_data_id][1]);
    }
    //shifty
    sub_data_id = get_shifty_amplitude_data_id_from_shifty_amplitude_id(amplitudes_data[i][3]);
    if(shifty_amplitude_data[sub_data_id][1]!="")
    {
      str_temp.append(", SHIFTY=");
      str_temp.append(shifty_amplitude_data[sub_data_id][1]);
    }
    // time_type
    if (amplitudes_data[i][4]==1)
    {
      str_temp.append(", TIME=TOTAL TIME"); 
    }
    
    amplitudes_export_list.push_back(str_temp);

    // second line
    // time_amplitude

    sub_data_ids = get_amplitudevalues_amplitude_data_ids_from_amplitudevalues_amplitude_id(amplitudes_data[i][5]);
    // second lines
    str_temp = "";
    int ii = 0;
    for (size_t i = 0; i < sub_data_ids.size(); i++)
    {
      if ((i != 0) && (ii!=0))
      {
        str_temp.append(",");
      }
      ii = ii + 1;
      
      str_temp.append(amplitudevalues_amplitude_data[sub_data_ids[i]][1]);
      str_temp.append(",");
      str_temp.append(amplitudevalues_amplitude_data[sub_data_ids[i]][2]);
      if (ii == 4)
      {
        ii = 0;
        str_temp.append(",");
        amplitudes_export_list.push_back(str_temp);
        str_temp = "";
      }
    }
    amplitudes_export_list.push_back(str_temp);
  }
  */
  std::string step_export;

  for (size_t i = 0; i < steps_export_list.size(); i++)
  {
    step_export.append(steps_export_list[i] + "\n");
  }

  return step_export;
}

std::string CoreSteps::print_data()
{
  std::string str_return;
  str_return = "\n CoreSteps steps_data: \n";
  str_return.append("step_id, name_id, parameter_id, step_type, step_type_id, loads_id, bcs_id \n");

  for (size_t i = 0; i < steps_data.size(); i++)
  {
    str_return.append(std::to_string(steps_data[i][0]) + " " + std::to_string(steps_data[i][1]) + " " + std::to_string(steps_data[i][2]) + " " + std::to_string(steps_data[i][3]) + " " + std::to_string(steps_data[i][4]) + " " + std::to_string(steps_data[i][5]) + " " + std::to_string(steps_data[i][6]) + " \n");
  }

  str_return.append("\n CoreSteps name_data: \n");
  str_return.append("name_id, name \n");

  for (size_t i = 0; i < name_data.size(); i++)
  {
    str_return.append(name_data[i][0] + " " + name_data[i][1] + " \n");
  }

  str_return.append("\n CoreSteps parameter_data: \n");
  str_return.append("parameter_id, PERTURBATION, NLGEOM, INC, INCF, THERMAL NETWORK, AMPLITUDE, SHOCK SMOOTHING \n");

  for (size_t i = 0; i < parameter_data.size(); i++)
  {
    str_return.append(parameter_data[i][0] + " " + parameter_data[i][1] + " " + parameter_data[i][2] + " " + parameter_data[i][3] + " " + parameter_data[i][4] + " " + parameter_data[i][5] + " " + parameter_data[i][6] + " " + parameter_data[i][7] + " \n");
  }

  str_return.append("\n CoreSteps static_data: \n");
  str_return.append("static_id, solver, direct, explicit, time reset, time at start, initial time increment, time period of the step, minimum time increment allowed, maximum time increment allowed, initial time increment CFD \n");

  for (size_t i = 0; i < static_data.size(); i++)
  {
    str_return.append(static_data[i][0] + " " + static_data[i][1] + " " + static_data[i][2] + " " + static_data[i][3] + " " + static_data[i][4] + " " + static_data[i][5] + " " + static_data[i][6] + " " + static_data[i][7] + " " + static_data[i][8] + " " + static_data[i][9] + " " + static_data[i][10] + " \n");
  }

  str_return.append("\n CoreSteps frequency_data: \n");
  str_return.append("frequency_id, solver, storage, global, cycmpc, number of eigenfrequencies desired, lower value, upper value \n");

  for (size_t i = 0; i < frequency_data.size(); i++)
  {
    str_return.append(frequency_data[i][0] + " " + frequency_data[i][1] + " " + frequency_data[i][2] + " " + frequency_data[i][3] + " " + frequency_data[i][4] + " " + frequency_data[i][5] + " " + frequency_data[i][6] + " " + frequency_data[i][7] + " \n");
  }

  str_return.append("\n CoreSteps buckle_data: \n");
  str_return.append("buckle_id, solver, number of buckling factors, accuracy, lanczos vectors, maximum iterations \n");

  for (size_t i = 0; i < buckle_data.size(); i++)
  {
    str_return.append(buckle_data[i][0] + " " + buckle_data[i][1] + " " + buckle_data[i][2] + " " + buckle_data[i][3] + " " + buckle_data[i][4] + " " + buckle_data[i][5] + " \n");
  }

  str_return.append("\n CoreSteps heattransfer_data: \n");
  str_return.append("heattransfer_id, solver, direct, steady state, frequency, modal dynamic, storage, deltmx, time reset, total time at start, initial time increment, time period of the step, minimum time increment allowed, maximum time increment allowed \n");

  for (size_t i = 0; i < heattransfer_data.size(); i++)
  {
    str_return.append(heattransfer_data[i][0] + " " + heattransfer_data[i][1] + " " + heattransfer_data[i][2] + " " + heattransfer_data[i][3] + " " + heattransfer_data[i][4] + " " + heattransfer_data[i][5] + " " + heattransfer_data[i][6] + " " + heattransfer_data[i][7] + " " + heattransfer_data[i][8] + " " + heattransfer_data[i][9] + " " + heattransfer_data[i][10] + " " + heattransfer_data[i][11] + " " + heattransfer_data[i][12] + " " + heattransfer_data[i][13] + " \n");
  }

  str_return.append("\n CoreSteps coupledtd_data: \n");
  str_return.append("coupledtd_id, solver, direct, alpha, steady state, deltmx, time reset, total time at start, compressible, initial time increment, time period of the step, minimum time increment allowed, maximum time increment allowed, initial time increment CFD \n");

  for (size_t i = 0; i < coupledtd_data.size(); i++)
  {
    str_return.append(coupledtd_data[i][0] + " " + coupledtd_data[i][1] + " " + coupledtd_data[i][2] + " " + coupledtd_data[i][3] + " " + coupledtd_data[i][4] + " " + coupledtd_data[i][5] + " " + coupledtd_data[i][6] + " " + coupledtd_data[i][7] + " " + coupledtd_data[i][8] + " " + coupledtd_data[i][9] + " " + coupledtd_data[i][10] + " " + coupledtd_data[i][11] + " " + coupledtd_data[i][12] + " " + coupledtd_data[i][13] + " \n");
  }
  
  str_return.append("\n CoreSteps uncoupledtd_data: \n");
  str_return.append("uncoupledtd_id, solver, direct, alpha, steady state, deltmx, explicit, time reset, total time at start, initial time increment, time period of the step, minimum time increment allowed, maximum time increment allowed \n");

  for (size_t i = 0; i < uncoupledtd_data.size(); i++)
  {
    str_return.append(uncoupledtd_data[i][0] + " " + uncoupledtd_data[i][1] + " " + uncoupledtd_data[i][2] + " " + uncoupledtd_data[i][3] + " " + uncoupledtd_data[i][4] + " " + uncoupledtd_data[i][5] + " " + uncoupledtd_data[i][6] + " " + uncoupledtd_data[i][7] + " " + uncoupledtd_data[i][8] + " " + uncoupledtd_data[i][9] + " " + uncoupledtd_data[i][10] + " " + uncoupledtd_data[i][11] + " " + uncoupledtd_data[i][12] + " \n");
  }

  str_return.append("\n CoreSteps loads_data: \n");
  str_return.append("loads_id, load_type, load_id \n");

  for (size_t i = 0; i < loads_data.size(); i++)
  {
    str_return.append(std::to_string(loads_data[i][0]) + " " + std::to_string(loads_data[i][1]) + " " + std::to_string(loads_data[i][2]) + " \n");
  } 

  str_return.append("\n CoreSteps bcs_data: \n");
  str_return.append("bcs_id, bc_type, bc_id \n");

  for (size_t i = 0; i < bcs_data.size(); i++)
  {
    str_return.append(std::to_string(bcs_data[i][0]) + " " + std::to_string(bcs_data[i][1]) + " " + std::to_string(bcs_data[i][2]) + " \n");
  } 

  return str_return;
}