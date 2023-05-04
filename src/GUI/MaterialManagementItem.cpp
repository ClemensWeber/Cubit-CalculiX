#include "MaterialManagementItem.hpp"
#include "CalculiXCoreInterface.hpp"
#include "CubitInterface.hpp"
#include "CubitMessage.hpp"
#include "MaterialInterface.hpp"

MaterialManagementItem::MaterialManagementItem(QTreeWidget* parent):
  QTreeWidgetItem (parent),
  isInitialized(false)
{}

MaterialManagementItem::~MaterialManagementItem()
{
}

void MaterialManagementItem::initialize(QString material_id_qstring,QString material_name_qstring)
{
  if(isInitialized)
    return;
  CalculiXCoreInterface *ccx_iface = new CalculiXCoreInterface();

  mat_iface = dynamic_cast<MaterialInterface*>(CubitInterface::get_interface("Material"));

  QTreeWidgetItem::setText(0, material_name_qstring);
  QTreeWidgetItem::setText(1, material_id_qstring);

  MaterialInterface::Material material;
  MaterialInterface::Property prop;
  material_name = material_name_qstring.toStdString();
  material = mat_iface->get_material(material_name);
  double prop_scalar;
  MaterialVector prop_vector;
  MaterialMatrix prop_matrix;

  // we get the group properties for the Calculix-FEA Type
  group_properties = ccx_iface->get_material_group_properties();

  // we build our storages for the material data
  std::vector<int> property(3);
  for (size_t i = 0; i < group_properties.size(); i++)
  {
    property[0] = i;
    if (group_properties[i][1]=="1")
    {
      double tmp_scalar = 0;
      property[1] = 1;
      property[2] = property_scalar.size();
      prop = mat_iface->get_property(group_properties[i][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_scalar))
      {
        tmp_scalar = prop_scalar; 
      }
      property_scalar.push_back(tmp_scalar);
    }else if (group_properties[i][1]=="2")
    {
      std::vector<double> tmp_vector;
      property[1] = 2;
      property[2] = property_vector.size();
      prop = mat_iface->get_property(group_properties[i][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_vector))
      {
        tmp_vector = prop_vector; 
      }
      property_vector.push_back(tmp_vector);
    }
    /*else if (group_properties[i][1]=="3")
    {
      std::vector<std::vector<double>> tmp_tabular;
      property[1] = 3;
      property[2] = property_tabular.size();
      prop = mat_iface->get_property(group_properties[i][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_tabular))
      {
        tmp_tabular = prop_tabular; 
      }
      property_tabular.push_back(tmp_tabular);
    }*/
    else if (group_properties[i][1]=="4")
    {
      std::vector<std::vector<double>> tmp_matrix;
      property[1] = 4;
      property[2] = property_matrix.size();
      prop = mat_iface->get_property(group_properties[i][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_matrix))
      {
        tmp_matrix = prop_matrix; 
      }
      property_matrix.push_back(tmp_matrix);
    }
    properties.push_back(property);

  }
  
  isInitialized = true;
}

void MaterialManagementItem::update()
{
  MaterialInterface::Material material;
  MaterialInterface::Property prop;
  material = mat_iface->get_material(material_name);
  double prop_scalar;
  MaterialVector prop_vector;
  MaterialMatrix prop_matrix;

  for (size_t i = 0; i < properties.size(); i++)
  {
    if (properties[i][1]==1)
    {
      double tmp_scalar=0;
      prop = mat_iface->get_property(group_properties[properties[i][0]][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_scalar))
      {
        tmp_scalar = prop_scalar; 
      }
      property_scalar[properties[i][2]] = tmp_scalar;
    }else if (properties[i][1]==2)
    {
      std::vector<double> tmp_vector;
      prop = mat_iface->get_property(group_properties[properties[i][0]][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_vector))
      {
        tmp_vector = prop_vector; 
      }
      property_vector[properties[i][2]] = tmp_vector;
    }
    else if (properties[i][1]==4)
    {
      std::vector<std::vector<double>> tmp_matrix;
      prop = mat_iface->get_property(group_properties[properties[i][0]][0]);
      if (mat_iface->get_material_property_value(material, prop, prop_matrix))
      {
        tmp_matrix = prop_matrix; 
      }
      property_matrix[properties[i][2]] = tmp_matrix;
    }
  }

  property_scalar_gui = property_scalar;
  //property_vector_gui = property_vector;
  //property_tabular_gui = property_tabular;
  property_matrix_gui = property_matrix;
}