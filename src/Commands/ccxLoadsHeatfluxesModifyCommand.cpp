#include "ccxLoadsHeatfluxesModifyCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxLoadsHeatfluxesModifyCommand::ccxLoadsHeatfluxesModifyCommand()
{}

ccxLoadsHeatfluxesModifyCommand::~ccxLoadsHeatfluxesModifyCommand()
{}

std::vector<std::string> ccxLoadsHeatfluxesModifyCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("modify heatflux <value:label='heatflux id',help='<heatlux id>'>");
  syntax.append("[op {mod | new}] " );
  syntax.append("[amplitude <value:label='amplitude id',help='<amplitude id>'>] ");
  syntax.append("[timedelay <value:label='timedelay',help='<timedelay>'>] ");
  
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxLoadsHeatfluxesModifyCommand::get_syntax_help()
{
  std::vector<std::string> help(5);
  help[0] = "ccx modify heatflux <heatflux id> [op {mod | new}] [amplitude <amplitude id>] [timedelay <value>]"; 

  return help;
}

std::vector<std::string> ccxLoadsHeatfluxesModifyCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxLoadsHeatfluxesModifyCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  std::vector<std::string> options;  
  std::vector<int> options_marker;
  int heatflux_id;
  std::string amplitude_id;
  int amplitude_value;
  std::string timedelay;
  double timedelay_value;

  data.get_value("heatflux id", heatflux_id);
  
  if (data.find_keyword("OP")){
    if (data.find_keyword("MOD")){
      options_marker.push_back(1);
      options.push_back("0");
    }else if (data.find_keyword("NEW"))
    {
      options_marker.push_back(1);
      options.push_back("1");
    }
  }else{
      options_marker.push_back(0);
      options.push_back("0");
  }

  if (!data.get_value("amplitude id", amplitude_value))
  {
    amplitude_id = "";
    options_marker.push_back(0);
  }
  else
  {
    amplitude_id = std::to_string(amplitude_value);
    options_marker.push_back(1);
  }
  options.push_back(amplitude_id);

  if (!data.get_value("timedelay", timedelay_value))
  {
    timedelay = "";
    options_marker.push_back(0);
  }
  else
  {
    timedelay = std::to_string(timedelay_value);
    options_marker.push_back(1);
  }
  options.push_back(timedelay);
  
  if (!ccx_iface.modify_loadsheatfluxes(heatflux_id, options, options_marker))
  {
    output = "Failed!\n";
    PRINT_ERROR(output.c_str());
  }
  options.clear();
    
  return true;
}