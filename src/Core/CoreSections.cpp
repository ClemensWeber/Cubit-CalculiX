#include "CoreSections.hpp"
#include "CubitInterface.hpp"

CoreSections::CoreSections()
{}

CoreSections::~CoreSections()
{}

bool CoreSections::init()
{
  if (is_initialized)
  {
    return false; // already initialized
  }else{
    is_initialized = true;  
    return true;
  }
}

bool CoreSections::update()
{ 
  return true;
}

bool CoreSections::reset()
{
  sections_data.clear();
  solid_section_data.clear();
  shell_section_data.clear();
  beam_section_data.clear();
  membrane_section_data.clear();
  init();
  return true;
}

bool CoreSections::check_initialized()
{
  return is_initialized;
}

bool CoreSections::create_section(std::string section_type,int block_id, std::string material_name, std::vector<std::string> options)
{
  int section_id;
  int section_last;
  int sub_section_id;
  int sub_section_last;

  if (section_type=="SOLID")
  {
    if (solid_section_data.size()==0)
    {
      sub_section_id = 1;
    }
    else
    {
      sub_section_last = solid_section_data.size() - 1;
      sub_section_id = std::stoi(solid_section_data[sub_section_last][0]) + 1;
    }
    this->add_solid_section(std::to_string(sub_section_id), std::to_string(block_id), material_name, options[0], options[1]);
  }
  
  if (sections_data.size()==0)
  {
    section_id = 1;
  }
  else
  {
    section_last = sections_data.size() - 1;
    section_id = sections_data[section_last][0] + 1;
  }

  this->add_section(section_id,1,sub_section_id);
  return true;
}

bool CoreSections::modify_section(std::string section_type,int section_id, std::vector<std::string> options, std::vector<int> options_marker)
{
  int section_type_value;
  if (section_type=="SOLID")
  {
    section_type_value = 1;
  }else if (section_type=="SHELL")
  {
    section_type_value = 2;
  }else if (section_type=="BEAM")
  {
    section_type_value = 3;
  }else if (section_type=="MEMBRANE")
  {
    section_type_value = 4;
  }

  int sub_section_data_id;
  int sections_data_id = get_sections_data_id_from_section_id(section_id);
  
  if (sections_data_id == -1)
  {
    return false;
  } else {
    if ((sections_data[sections_data_id][1]==1) && (sections_data[sections_data_id][1]==section_type_value))
    {
      sub_section_data_id = get_solid_section_data_id_from_solid_section_id(sections_data[sections_data_id][2]);

      for (size_t i = 0; i < options.size(); i++)
      {
        if (options_marker[i]==1)
        {
          solid_section_data[sub_section_data_id][i+1] = options[i];
        }
      }
    }
    return true;
  }
}

bool CoreSections::add_section(int section_id, int section_type, int section_type_id)
{
  std::vector<int> v = {section_id, section_type, section_type_id};
      
  sections_data.push_back(v);

  return true;
}

bool CoreSections::add_solid_section(std::string solid_section_id, std::string block_id, std::string material_name,std::string orientation,std::string thickness)
{
  std::vector<std::string> v = {solid_section_id, block_id, material_name, orientation, thickness};
      
  solid_section_data.push_back(v);

  return true;
}

bool CoreSections::delete_section(int section_id)
{
  int sub_section_data_id;
  int sections_data_id = get_sections_data_id_from_section_id(section_id);
  if (sections_data_id == -1)
  {
    return false;
  } else {
    if (sections_data[sections_data_id][1]==1)
    {
      sub_section_data_id = get_solid_section_data_id_from_solid_section_id(sections_data[sections_data_id][2]);
      solid_section_data.erase(solid_section_data.begin() + sub_section_data_id);  
    }
    sections_data.erase(sections_data.begin() + sections_data_id);
    return true;
  }
}
bool CoreSections::modify_section_id(int section_id, int new_section_id)
{
  int sections_data_id = get_sections_data_id_from_section_id(section_id);
  if (sections_data_id == -1)
  {
    return false;
  } else {
    sections_data[sections_data_id][0]=new_section_id;
    return true;
  }
}

int CoreSections::get_sections_data_id_from_section_id(int section_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < sections_data.size(); i++)
  {
    if (sections_data[i][0]==section_id)
    {
        return_int = i;
    }  
  }
  return return_int;
}

int CoreSections::get_solid_section_data_id_from_solid_section_id(int solid_section_id)
{ 
  int return_int = -1;
  for (size_t i = 0; i < solid_section_data.size(); i++)
  {
    if (solid_section_data[i][0]==std::to_string(solid_section_id))
    {
        return_int = i;
    }  
  }
  return return_int;
}

std::string CoreSections::get_section_export() // get a list of the CalculiX section exports
{
  std::vector<std::string> sections_export_list;
  sections_export_list.push_back("********************************** S E C T I O N S ****************************");
  std::string str_temp;
  int sub_section_data_id;

  //loop over all sections
  for (size_t i = 0; i < sections_data.size(); i++)
  { 

    // SOLID
    if (sections_data[i][1] == 1)
    {
      sub_section_data_id = get_solid_section_data_id_from_solid_section_id(sections_data[i][2]);

      str_temp = "*SOLID SECTION, MATERIAL=";
      str_temp.append(solid_section_data[sub_section_data_id][2]);
      str_temp.append(", ELSET=");
      str_temp.append(solid_section_data[sub_section_data_id][1]);
      
      if (solid_section_data[sub_section_data_id][3]!="")
      {
        str_temp.append(", ORIENTATION=");
        str_temp.append(solid_section_data[sub_section_data_id][3]);
      }

      sections_export_list.push_back(str_temp);

      if (solid_section_data[sub_section_data_id][4]!="")
      { 
        sections_export_list.push_back(solid_section_data[sub_section_data_id][4]);
      }    
    }
    // SHELL
    // BEAM
    // MEMBRANE
  }

  std::string section_export;

  for (size_t i = 0; i < sections_export_list.size(); i++)
  {
    section_export.append(sections_export_list[i] + "\n");
  }
  
  return section_export;
}

std::string CoreSections::print_data()
{
  std::string str_return;
  str_return = "\n CoreSections sections_data: \n";
  str_return.append("section_id, section_type, section_type_id \n");

  for (size_t i = 0; i < sections_data.size(); i++)
  {
    str_return.append(std::to_string(sections_data[i][0]) + " " + std::to_string(sections_data[i][1]) + " " + std::to_string(sections_data[i][2]) + " \n");
  }

  str_return.append("\n CoreSections solid_section_data: \n");
  str_return.append("solid_section_id,block_id,material,orientation,thickness \n");

  for (size_t i = 0; i < solid_section_data.size(); i++)
  {
    str_return.append(solid_section_data[i][0] + " " + solid_section_data[i][1] + " " + solid_section_data[i][2] + " " + solid_section_data[i][3] + " " + solid_section_data[i][4] + " \n");
  }
  
  return str_return;
}