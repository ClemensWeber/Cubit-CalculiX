#include "ccxStepAddLoadCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxStepAddLoadCommand::ccxStepAddLoadCommand()
{}

ccxStepAddLoadCommand::~ccxStepAddLoadCommand()
{}

std::vector<std::string> ccxStepAddLoadCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("step <value:label='step id',help='<step id>'> ");
  syntax.append("add load ");
  syntax.append("[force <value:label='force id',help='<force id>'>...] " );
  syntax.append("[pressure <value:label='pressure id',help='<pressure id>'>...] " );
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxStepAddLoadCommand::get_syntax_help()
{
  std::vector<std::string> help(5);
  help[0] = "ccx step <step id> add load [force <force id>...] [pressure <pressure id>...]"; 

  return help;
}

std::vector<std::string> ccxStepAddLoadCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxStepAddLoadCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  
  int step_id;
  std::vector<int> force_ids;
  std::vector<int> pressure_ids;

  data.get_value("step id", step_id);

  data.get_values("force id", force_ids);
  data.get_values("pressure id", pressure_ids);
   
  if (!ccx_iface.step_add_loads(step_id, 1, force_ids))
  {
    output = "Failed adding Force!\n";
    PRINT_ERROR(output.c_str());
  }
  if (!ccx_iface.step_add_loads(step_id, 2, pressure_ids))
  {
    output = "Failed adding Pressure!\n";
    PRINT_ERROR(output.c_str());
  }
    
  return true;
}