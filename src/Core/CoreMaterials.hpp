#ifndef COREMATERIALS_HPP
#define COREMATERIALS_HPP

class MaterialInterface;

class CoreMaterials
{

public:
  CoreMaterials();
  ~CoreMaterials();

  std::vector<std::vector<std::string>> material_cards; // used to store the material cards and its property prefix, maybe comes in handy later
  // materials_data[0][0] material_card
  // materials_data[0][1] material card property prefix

  bool is_initialized = false;

  bool init(); // initialize
  bool update(); // check for changes of the materials // just a placeholder right now
  bool reset(); // delete all data and initialize afterwards // just a placeholder right now
  bool check_initialized(); // check if object is initialized
  std::vector<std::string> get_group_list(); // get a list of CalculiX Material Groups
  std::string get_material_export(); // get CalculiX Material exports
  std::string get_material_cards_export(std::string material_name, std::string group_name); // get card exports for a material

  MaterialInterface *mat_iface;
};

#endif // COREMATERIALS_HPP
