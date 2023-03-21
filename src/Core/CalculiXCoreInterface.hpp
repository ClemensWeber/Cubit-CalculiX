#ifndef CALCULIXCOREINTERFACE_HPP
#define CALCULIXCOREINTERFACE_HPP

class MeshExportInterface;

class CalculiXCoreInterface
{

public:
  CalculiXCoreInterface();
  ~CalculiXCoreInterface();
	
  bool set_use_ccx_autocleanup(bool bool_use);
  bool set_use_ccx_logfile(bool bool_use);
  std::string print_data();
  bool log_str(std::string str_log);
  std::vector<int> parser(std::string parse_type, std::string parse_string);
  std::vector<std::string> get_ccx_element_types(); // returns all supported ccx element types
  bool set_ccx_element_type(int block_id, std::string ccx_element_type); // sets the ccx element type for a block
  std::string get_ccx_element_type(int block_id); // gets the ccx element type for a block
  std::string get_block_name(int block_id); // gets the block name
  std::string get_nodeset_name(int nodeset_id); // gets the nodeset name
  std::string get_sideset_name(int sideset_id); // gets the sideset name
  std::string get_surfaceinteraction_name(int surfaceinteraction_id); // gets the surfaceinteraction name
  std::string get_amplitude_name(int amplitude_id); // gets the surfaceinteraction name
  bool core_update(); // lets the core check for updates aka changes from the entities
  bool core_reset(); // reset the whole core to the init level
  std::vector<int> get_blocks(); // gets the block ids from core blocks
  std::string get_material_export_data(); // gets the export data from materials core
  std::string get_section_export_data(); // gets the export data from sections core
  std::string get_constraint_export_data(); // gets the export data from constraints core
  std::string get_surfaceinteraction_export_data(); // gets the export data from surfaceinteractions core
  std::string get_contactpair_export_data(); // gets the export data from contactpairs core
  std::string get_amplitude_export_data(); // gets the export data from amplitudes core
  std::string get_initialcondition_export_data(); // gets the export data from core
  std::string get_step_export_data(); // gets the export data from core
  bool create_section(std::string section_type,int block_id, int material_id, std::vector<std::string> options); // adds a new section
  bool modify_section(std::string section_type,int section_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a section  
  bool delete_section(int section_id); // delete section
  bool create_constraint(std::string constraint_type, std::vector<std::string> options); // adds a new constraint
  bool modify_constraint(std::string constraint_type,int constraint_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a constraint  
  bool delete_constraint(int constraint_id); // delete constraint
  bool create_constraint_tie_from_cubitcontactpair(std::string name, std::string position_tolerance); // create constraint tie from cubit contact pairs
  std::vector<int> get_rigidbody_vertex_list(); // get list of rigid body vertices
  bool referencepoints_update_on_export(int max_node_id); // update reference points
  bool referencepoints_reset_on_export(); // reset reference points
  std::string get_referencepoints_export(); // export reference points
  std::string get_referencepoints_export_nodesets(); // export reference points
  int  referencepoints_get_ref_from_vertex_id(int vertex_id); // get ref_node for the vertex_id  and returns -1 if it fails
  int  referencepoints_get_rot_from_vertex_id(int vertex_id); // get ref_node for the vertex_id  and returns -1 if it fails
  bool add_sideset_face(std::string sideset_id, std::string sideset_name, std::string face); // gets the sideset/elset name and face
  std::vector<std::vector<std::string>> get_sideset_face(int sideset_id); // gets the sideset/elset name and face
  bool create_surfaceinteraction(std::string surfacebehavior_type, std::vector<std::string> options, std::vector<std::vector<std::string>> options2); // adds a new surfaceinteraction
  bool modify_surfaceinteraction(std::string modify_type, int surfaceinteraction_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2); // modifies a surfaceinteraction
  bool delete_surfaceinteraction(int surfaceinteraction_id); // delete surface interaction
  bool create_contactpair(std::vector<std::string> options); // adds a new contactpair
  bool modify_contactpair(int contactpair_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a contactpair  
  bool delete_contactpair(int contactpair_id); // delete contact pair
  bool create_contactpair_from_cubitcontactpair(int surfaceinteraction_id, std::string contactpairtype, std::string adjust, std::string adjust_nodeset); // create contact pairs from cubit contact pairs with given surface interaction
  bool create_amplitude(std::vector<std::string> options, std::vector<std::vector<std::string>> options2); // adds a new amplitude
  bool modify_amplitude(int amplitude_id, std::vector<std::string> options, std::vector<int> options_marker, std::vector<std::vector<std::string>> options2); // modify a amplitude
  bool delete_amplitude(int amplitude_id); // delete amplitude
  bool modify_loadsforces(int force_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a force
  bool modify_loadspressures(int pressure_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a pressure
  bool modify_bcsdisplacements(int displacement_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a displacement
  bool modify_bcstemperatures(int displacement_id, std::vector<std::string> options, std::vector<int> options_marker); // modify a temperature
  bool create_historyoutput(std::vector<std::string> options); // adds a new output
  bool modify_historyoutput(int output_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker); // modify a output
  bool delete_historyoutput(int output_id); // delete output
  std::vector<std::string> get_historyoutput_node_keys();
  std::vector<std::string> get_historyoutput_element_keys();
  std::vector<std::string> get_historyoutput_contact_keys();
  bool create_fieldoutput(std::vector<std::string> options); // adds a new output
  bool modify_fieldoutput(int output_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker); // modify a output
  bool delete_fieldoutput(int output_id); // delete output
  std::vector<std::string> get_fieldoutput_node_keys();
  std::vector<std::string> get_fieldoutput_element_keys();
  std::vector<std::string> get_fieldoutput_contact_keys();
  bool create_initialcondition(std::vector<std::string> options); // adds a new initialcondition
  bool modify_initialcondition(int initialcondition_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker); // modify a initialcondition
  bool delete_initialcondition(int initialcondition_id); // delete initialcondition
  bool create_step(std::vector<std::string> options); // adds a new step
  bool modify_step(int step_id, int modify_type, std::vector<std::string> options, std::vector<int> options_marker); // modify a step
  bool delete_step(int step_id); // delete step
  bool step_add_loads(int step_id, int load_type, std::vector<int> load_ids); // adds loads to loads_data
  bool step_add_bcs(int step_id, int bc_type, std::vector<int> bc_ids); // adds bcs to bcs_data
  bool step_add_historyoutputs(int step_id, std::vector<int> historyoutput_ids); // adds historyoutputs to historyoutputs_data
  bool step_add_fieldoutputs(int step_id, std::vector<int> fieldoutput_ids); // adds fieldoutputs to fieldoutputs_data
  bool step_remove_loads(int step_id, int load_type, std::vector<int> load_ids); // removes loads from loads_data
  bool step_remove_bcs(int step_id, int bc_type, std::vector<int> bc_ids); // removes bcs from bcs_data
  bool step_remove_historyoutputs(int step_id, std::vector<int> historyoutput_ids); // removes historyoutputs to historyoutputs_data
  bool step_remove_fieldoutputs(int step_id, std::vector<int> fieldoutput_ids); // removes fieldoutputs to fieldoutputs_data
  std::vector<std::vector<std::string>> get_blocks_tree_data(); // gets the data from core blocks to build the tree
  std::vector<std::vector<std::string>> get_nodeset_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_sideset_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_material_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_sections_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_constraints_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_surfaceinteractions_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_contactpairs_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_amplitudes_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_loadsforces_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_loadspressures_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_bcsdisplacements_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_bcstemperatures_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_historyoutputs_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_fieldoutputs_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_initialconditions_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_tree_data(); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_loadsforces_tree_data(int step_id); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_loadspressures_tree_data(int step_id); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_bcsdisplacements_tree_data(int step_id); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_bcstemperatures_tree_data(int step_id); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_historyoutputs_tree_data(int step_id); // gets the data from core to build the tree
  std::vector<std::vector<std::string>> get_steps_fieldoutputs_tree_data(int step_id); // gets the data from core to build the tree

  MeshExportInterface *me_iface;
};

#endif // CALCULIXCOREINTERFACE_HPP
