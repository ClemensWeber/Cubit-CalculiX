#include "ccxStepCreateCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxStepCreateCommand::ccxStepCreateCommand()
{}

ccxStepCreateCommand::~ccxStepCreateCommand()
{}

std::vector<std::string> ccxStepCreateCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("create step ");
  syntax.append("name <string:type='unquoted', number='1', label='name', help='<name>'> " );
  syntax.append("{static|frequency|buckle|heattransfer|coupledtemperaturedisplacement|uncoupledtemperaturedisplacement|noanalysis}" );
  syntax_list.push_back(syntax);
  
  return syntax_list;
}

std::vector<std::string> ccxStepCreateCommand::get_syntax_help()
{
  std::vector<std::string> help(5);
  help[0] = "ccx create step name <name> {static|frequency|buckle|heattransfer|coupledtemperaturedisplacement|uncoupledtemperaturedisplacement|noanalysis}"; 

  return help;
}

std::vector<std::string> ccxStepCreateCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxStepCreateCommand::execute(CubitCommandData &data)
{
  CalculiXCoreInterface ccx_iface;

  std::string output;
  std::vector<std::string> options;  
  std::string name;

  data.get_string("name", name);
  options.push_back(name);

  if (data.find_keyword("NOANALYSIS"))
  {
    options.push_back("1");
  } else if (data.find_keyword("STATIC"))
  {
    options.push_back("2");
  } else if (data.find_keyword("FREQUENCY"))
  {
    options.push_back("3");
  } else if (data.find_keyword("BUCKLE"))
  {
    options.push_back("4");
  } else if (data.find_keyword("HEATTRANSFER"))
  {
    options.push_back("5");
  } else if (data.find_keyword("COUPLEDTEMPERATUREDISPLACEMENT"))
  {
    options.push_back("6");
  } else if (data.find_keyword("UNCOUPLEDTEMPERATUREDISPLACEMENT"))
  {
    options.push_back("7");
  }
  
  if (!ccx_iface.create_step(options))
  {
    output = "Failed!\n";
    PRINT_ERROR(output.c_str());
  }
  options.clear();
    
  return true;
}