#ifndef CORESTEPS_HPP
#define CORESTEPS_HPP

class CalculiXCoreInterface;

class CoreSteps
{

public:
  CoreSteps();
  ~CoreSteps();

  // make 1 data storage for each step parameter
  // NAME
  // PARAMETER STEP
  // STATIC
  // FREQUENCY
  // BUCKLE
  // HEAT TRANSFER
  // COUPLED TEMPERATURE-DISPLACEMENT
  // UNCOUPLED TEMPERATURE-DISPLACEMENT
  // FORCES
  // BCS

  // STEP TYPES
  // 1: NO ANALYSIS
  // 2: STATIC
  // 3: FREQUENCY
  // 4: BUCKLE
  // 5: HEAT TRANSFER
  // 6: COUPLED TEMPERATURE-DISPLACEMENT
  // 7: UNCOUPLED TEMPERATURE-DISPLACEMENT

  std::vector<std::vector<int>> steps_data; // used to store the connection between a step id and step parameter id
  // steps_data[0][0] step_id
  // steps_data[0][1] name_id             option 0
  // steps_data[0][2] parameter_id        option 1
  // steps_data[0][3] step_type           option 2
  // steps_data[0][4] step_type_id        option 3
  // steps_data[0][5] loads_id            option 4
  // steps_data[0][6] bcs_id              option 5

  std::vector<std::vector<std::string>> name_data;
  // name_data[0][0] name_id
  // name_data[0][1] name

  std::vector<std::vector<std::string>> parameter_data;
  // parameter_data[0][0] parameter_id
  // parameter_data[0][1] PERTURBATION
  // parameter_data[0][2] NLGEOM {NLGEOM|NLGEOM=NO}
  // parameter_data[0][3] INC
  // parameter_data[0][4] INCF
  // parameter_data[0][5] THERMAL NETWORK
  // parameter_data[0][6] AMPLITUDE {AMPLITUDE=RAMP|AMPLITUDE=STEP}
  // parameter_data[0][7] SHOCK SMOOTHING

  std::vector<std::vector<std::string>> static_data;
  // static_data[0][0] static_id
  // static_data[0][1] solver
  // static_data[0][2] direct
  // static_data[0][3] explicit
  // static_data[0][4] time reset
  // static_data[0][5] total time at start

  std::vector<std::vector<int>> loads_data;
  // forces_data[0][0] loads_id
  // forces_data[0][1] load_type  // 1: force | 2: pressure
  // forces_data[0][2] load_id

  std::vector<std::vector<int>> bcs_data;
  // bcs_data[0][0] bcs_id
  // bcs_data[0][1] bc_type       // 1: displacement | 2: temperature
  // bcs_data[0][2] bc_id

  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the amplitude
  bool reset(); // delete all data and initialize afterwards
  bool check_initialized(); // check if object is initialized
  bool create_step(std::vector<std::string> options); // adds new step
  bool modify_step(int step_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker); // modify a step
  bool add_loads(int step_id, int load_type, std::vector<int> load_ids); // adds loads to loads_data
  bool add_bcs(int step_id, int bc_type, std::vector<int> bc_ids); // adds bcs to bcs_data
  bool remove_loads(int step_id, int load_type, std::vector<int> load_ids); // removes loads from loads_data
  bool remove_bcs(int step_id, int bc_type, std::vector<int> bc_ids); // removes bcs from bcs_data
  bool delete_step(int step_id); // deletes step from steps_data
  bool add_step(int step_id, int name_id, int parameter_id, int step_type, int step_type_id, int loads_id, int bcs_id); // adds new step to steps_data
  bool add_name(std::string name_id, std::string name); // adds new name to name_data
  bool add_parameter(std::string parameter_id); // adds new parameter to parameter_data
  bool add_static(std::string static_id); // adds new static to static_data
  bool add_load(int loads_id, int load_type, int load_id); // adds new load to loads_data
  bool add_bc(int bcs_id, int bc_type, int bc_id); // adds new bc to bcs_data
  int  get_steps_data_id_from_step_id(int step_id); // searches for the step_id in the steps_data and returns the indices or -1 if it fails
  int  get_name_data_id_from_name_id(int name_id); // searches for the name_id in the name_data and returns the indices or -1 if it fails
  int  get_parameter_data_id_from_parameter_id(int parameter_id); // searches for the parameter_id in the parameter_data and returns the indices or -1 if it fails
  int  get_static_data_id_from_static_id(int static_id); // searches for the static_id in the static_data and returns the indices or -1 if it fails
  int  get_load_data_id(int loads_id, int load_type,int load_id); // searches for the load_id in the load_data and returns the indices or -1 if it fails
  int  get_bc_data_id(int bcs_id, int bc_type, int bc_id); // searches for the bc_id in the bc_data and returns the indices or -1 if it fails
  std::vector<int> get_load_data_ids_from_loads_id(int loads_id); // searches for the loads_id in the loads_data and returns the indices or -1 if it fails
  std::vector<int> get_bc_data_ids_from_bcs_id(int bcs_id); // searches for the bcs_id in the bcs_data and returns the indices or -1 if it fails
  std::string get_step_export(); // get CalculiX step exports
  std::string print_data(); // prints out the data

  CalculiXCoreInterface *ccx_iface;
};

#endif // CORESTEPS_HPP