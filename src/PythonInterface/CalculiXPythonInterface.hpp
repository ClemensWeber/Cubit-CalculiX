#ifndef CALCULIXPYTHONINTERFACE_HPP
#define CALCULIXPYTHONINTERFACE_HPP

#include <vector>
#include <string>

/* don't forget to wrap with 'swig -python -py3 -c++ CalculiXPythonInterface.i'  

and if compiling fails because of qt replace Python.h with 

#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

*/

class CalculiXCoreInterface;

class CalculiXPythonInterface
{

public:
  CalculiXPythonInterface();
  ~CalculiXPythonInterface();
	
  void help(); // prints out python interface help
    
  //QUERY results
  //FRD results
  std::vector<std::string> frd_get_result_block_types(int job_id); // returns a list of all result block types
  std::vector<std::string> frd_get_result_block_components(int job_id, std::string result_block_type); // returns a list of all result block components for a block type
  std::vector<int> frd_get_total_increments(int job_id); // returns a list of the total increments
  double frd_get_time_from_total_increment(int job_id, int total_increment); // returns a the time for a total increment
  std::vector<int> frd_get_node_ids_between_values(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double lower_value,double upper_value); // returns the global node ids within the values
  std::vector<int> frd_get_node_ids_smaller_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value); // returns the global node ids smaller than the value
  std::vector<int> frd_get_node_ids_greater_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value); // returns the global node ids greater than the value
  std::vector<int> frd_get_element_ids_between_values(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double lower_value,double upper_value); // returns the global element ids within the values
  std::vector<int> frd_get_element_ids_smaller_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value); // returns the global element ids smaller than the values
  std::vector<int> frd_get_element_ids_greater_value(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double value); // returns the global element ids greater than the values
  std::vector<int> frd_get_element_ids_over_limit(int job_id,int total_increment,std::string result_block_type,std::string result_block_component,double limit); // returns the global element ids where the largest difference between nodal values exceeds the limit
  double frd_get_node_value(int job_id,int node_id, int total_increment,std::string result_block_type,std::string result_block_component); // returns the queried node_id value
  std::vector<double> frd_get_node_values(int job_id,int node_id, int total_increment,std::string result_block_type); // returns the queried node_id values
  //DAT results

  CalculiXCoreInterface *ccx_iface;
};

#endif // CALCULIXPYTHONINTERFACE_HPP
