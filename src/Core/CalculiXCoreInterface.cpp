#include "CalculiXCoreInterface.hpp"
#include "loadCalculiXCore.hpp"

CalculiXCoreInterface::CalculiXCoreInterface()
{}

CalculiXCoreInterface::~CalculiXCoreInterface()
{}

std::string CalculiXCoreInterface::print_data()
{
  return ccx_core.print_data();
}

bool CalculiXCoreInterface::log_str(std::string str_log)
{
  ccx_core.print_to_log(str_log);
  return true;
}

std::vector<std::string> CalculiXCoreInterface::get_ccx_element_types()
{ 
  return ccx_core.get_ccx_element_types();
}

bool CalculiXCoreInterface::set_ccx_element_type(int block_id, std::string ccx_element_type)
{
  if (ccx_core.set_ccx_element_type(block_id, ccx_element_type))
  {
    return true;
  }else{
    return false;
  }
}

bool CalculiXCoreInterface::core_update()
{
  if (ccx_core.update())
  {
    return true;
  }else{
    return false;
  }
}

bool CalculiXCoreInterface::core_reset()
{
  if (ccx_core.reset())
  {
    return true;
  }else{
    return false;
  }
}

std::vector<std::vector<std::string>> CalculiXCoreInterface::get_blocks_tree_data()
{ 
  return ccx_core.get_blocks_tree_data();
}