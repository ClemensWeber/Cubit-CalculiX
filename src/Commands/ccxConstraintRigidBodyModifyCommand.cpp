#include "ccxConstraintRigidBodyModifyCommand.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "CalculiXCoreInterface.hpp"

ccxConstraintRigidBodyModifyCommand::ccxConstraintRigidBodyModifyCommand()
{}

ccxConstraintRigidBodyModifyCommand::~ccxConstraintRigidBodyModifyCommand()
{}

std::vector<std::string> ccxConstraintRigidBodyModifyCommand::get_syntax()
{
  std::vector<std::string> syntax_list;

  std::string syntax = "ccx ";
  syntax.append("modify constraint rigid body <value:label='constraint id',help='<constraint id>'>");
  syntax.append("[{nodeset|block} <value:label='entity id',help='<entity id>'>] ");
  syntax.append("[vertex <value:label='vertex',help='<vertex>'>]");

  syntax_list.push_back(syntax);

  return syntax_list;
}

std::vector<std::string> ccxConstraintRigidBodyModifyCommand::get_syntax_help()
{
  std::vector<std::string> help(1);
  help[0] = "ccx modify constraint rigid body <constraint id> [{nodeset|block} <entity id>] [vertex <vertex>]";

  return help;
}

std::vector<std::string> ccxConstraintRigidBodyModifyCommand::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool ccxConstraintRigidBodyModifyCommand::execute(CubitCommandData &data)
{
  
  CalculiXCoreInterface ccx_iface;

  std::string output;

  std::vector<std::string> options;
  std::vector<int> options_marker;
  int vertex_value;
  std::string vertex;
  int entity_id_value;
  std::string entity_id;
  int constraint_id;

  data.get_value("constraint id", constraint_id);
  
  // entity type
  if (data.find_keyword("NODESET"))
  {
    options.push_back("1");  
    options_marker.push_back(1);
  }else if (data.find_keyword("BLOCK"))
  {
    options.push_back("2");  
    options_marker.push_back(1);
  }else
  {
    options.push_back("");  
    options_marker.push_back(0);
  }
  
  if (!data.get_value("entity id", entity_id_value))
  {
    entity_id = "";
    options_marker.push_back(0);
  }
  else
  {
    entity_id = std::to_string(entity_id_value);
    options_marker.push_back(1);
  }
    
  if (!data.get_value("vertex", vertex_value))
  {
    vertex = "";
    options_marker.push_back(0);
  }
  else
  {
    vertex = std::to_string(vertex_value);
    options_marker.push_back(1);
  }
  
  options.push_back(entity_id);
  options.push_back(vertex);

  if (!ccx_iface.modify_constraint("RIGIDBODY",constraint_id,options,options_marker))
  {
    output = "Failed with ID " + std::to_string(constraint_id) + "!\n";
    PRINT_ERROR(output.c_str());
    return false;
  } 

  return true;
}