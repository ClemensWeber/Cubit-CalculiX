#include "cmdPanelManager.hpp"
#include "Claro.hpp"
#include "NavigationModel.hpp"
#include "NavigationNode.hpp"
#include "MyCmdWidgetFactory.hpp"

#include <QAction>
#include <QIcon>
#include <QStringList>

cmdPanelManager::cmdPanelManager() :
  isInitialized(false),
  myFactory(NULL)
{}

cmdPanelManager::~cmdPanelManager()
{
  if(myFactory)
    delete myFactory;
}

void cmdPanelManager::initialize()
{
  if(isInitialized)
    return;

  // Set this variable to choose how to initialize your navigation nodes.
  bool use_xml = false;

  if(use_xml)
    initialize_from_xml();
  else
    initialize_from_code();

  // Once nodes are created and initialized, we want to associate them
  // with command panels.
  associate_panels_with_nodes();
  isInitialized = true;
}

void cmdPanelManager::clear()
{
  if(myFactory)
  {
    // Clean up my widgets
    myFactory->clear();

    // Remove the factory reference from my navigation nodes
    QStringList my_markers;
    my_markers.push_back("CCXBlocksElementType");
    my_markers.push_back("CCXSectionsCreateSolid");
    my_markers.push_back("CCXSectionsCreateShell");
    my_markers.push_back("CCXSectionsCreateBeam");
    my_markers.push_back("CCXSectionsCreateMembrane");
    my_markers.push_back("CCXSectionsModifySolid");
    my_markers.push_back("CCXSectionsModifyShell");
    my_markers.push_back("CCXSectionsModifyBeam");
    my_markers.push_back("CCXSectionsModifyMembrane");
    my_markers.push_back("CCXRigidBodyCreate");

    // For each marker, we want to get the navigation node and assign the node
    // to use this factory to get widgets as needed.
    NavigationModel* model = Claro::instance()->navigation_model();
    for(int i = 0; i < my_markers.size(); i++)
    {
      NavigationNode* node = model->getMarkedNode(my_markers[i]);
      if(node)
        node->setFactory(0);
    }
  }

  isInitialized = false;
}

void cmdPanelManager::initialize_from_xml()
{
  // If you are creating your command panel navigation buttons using xml files,
  // there is nothing you need to do to create navigation nodes (it is done
  // automatically). For an example, see MyNavigation.xml and copy it to the
  // Cubit/bin/xml folder.

  return;
}

void cmdPanelManager::initialize_from_code()
{
  QIcon *NodeIconPointer;
  // This example shows how to create the command panel navigation buttons (nodes)
  // using the NavigationModel directly.
  NavigationModel* model = Claro::instance()->navigation_model();
  if(!model)
    return;
  
  NavigationNode* root_node;
  NavigationNode* node;
  //##############################
  // add BlocksTree Nodes
  // add new Node between Exodus/Block and ExodusElementTypeBlock
  root_node = model->getNode("Exodus/Block");
  node = model->addNode("Element Types", root_node);
  model->setNodeMarker(node, "ElementTypeBlockNavigation");
  // set new Parent to ExodusElementTypeBlock and remove from old
  node = model->getMarkedNode("ExodusElementTypeBlock");
  root_node->removeChild(root_node->getChildIndex(node));
  root_node = model->getMarkedNode("ElementTypeBlockNavigation");
  node->setParent(root_node);
  root_node->insertChild(root_node->childCount()+1,node);
  NodeIconPointer = node->getIcon();
  root_node->setIcon(NodeIconPointer);
  // add Element Type Node
  root_node = model->getMarkedNode("ElementTypeBlockNavigation");
  node = model->addNode("CCX Element Types", root_node);
  model->setNodeMarker(node, "CCXBlocksElementType");

  //##############################
  // add Materials and Section Nodes
  root_node = model->getNode("Exodus");
  node = model->addNode("CCX Sections", root_node);
  model->setNodeMarker(node, "CCXSections");
  root_node = model->getMarkedNode("CCXSections");
  node = model->addNode("Create", root_node);
  model->setNodeMarker(node, "CCXSectionsCreate");
  node = model->addNode("Modify", root_node);
  model->setNodeMarker(node, "CCXSectionsModify");
  node = model->addNode("Delete", root_node);
  model->setNodeMarker(node, "CCXSectionsDelete");
  //##
  root_node = model->getMarkedNode("CCXSectionsCreate");
  node = model->addNode("Create Solid Section", root_node);
  model->setNodeMarker(node, "CCXSectionsCreateSolid");
  node = model->addNode("Create Shell Section", root_node);
  model->setNodeMarker(node, "CCXSectionsCreateShell");
  node = model->addNode("Create Beam Section", root_node);
  model->setNodeMarker(node, "CCXSectionsCreateBeam");
  node = model->addNode("Create Membrane Section", root_node);
  model->setNodeMarker(node, "CCXSectionsCreateMembrane");
  //##
  root_node = model->getMarkedNode("CCXSectionsModify");
  node = model->addNode("Modify Solid Section", root_node);
  model->setNodeMarker(node, "CCXSectionsModifySolid");
  node = model->addNode("Modify Shell Section", root_node);
  model->setNodeMarker(node, "CCXSectionsModifyShell");
  node = model->addNode("Modify Beam Section", root_node);
  model->setNodeMarker(node, "CCXSectionsModifyBeam");
  node = model->addNode("Modify Membrane Section", root_node);
  model->setNodeMarker(node, "CCXSectionsModifyMembrane");

  //##############################
  // add Constraint Nodes
  // add new Node between FEA/Create and FEAConstraintCreate
  root_node = model->getNode("FEA/Create");
  node = model->addNode("Constraints", root_node);
  model->setNodeMarker(node, "FEAConstraintCreateNavigation");
  //node->setUseComboForChildren(true);
  // set new Parent to FEAConstraintCreate and remove from old
  node = model->getMarkedNode("FEAConstraintCreate");
  root_node->removeChild(root_node->getChildIndex(node));
  root_node = model->getMarkedNode("FEAConstraintCreateNavigation");
  node->setParent(root_node);
  root_node->insertChild(root_node->childCount()+1,node);
  NodeIconPointer = node->getIcon();
  root_node->setIcon(NodeIconPointer);
  // add Constraint Node
  root_node = model->getMarkedNode("FEAConstraintCreateNavigation");
  node = model->addNode("CCX Rigid Body", root_node);
  model->setNodeMarker(node, "CCXRigidBodyCreate");
}

void cmdPanelManager::associate_panels_with_nodes()
{
  // The widget factory is in charge of giving out our panels when the framework
  // needs them.
  if(!myFactory)
    myFactory = new MyCmdWidgetFactory();

  // Setup a list of the markers that identify my navigation nodes. Note that
  // we did not include our root marker because we do not need to create a
  // command panel for it.
  QStringList my_markers;
  my_markers.push_back("CCXBlocksElementType");
  my_markers.push_back("CCXSectionsCreateSolid");
  my_markers.push_back("CCXSectionsCreateShell");
  my_markers.push_back("CCXSectionsCreateBeam");
  my_markers.push_back("CCXSectionsCreateMembrane");
  my_markers.push_back("CCXSectionsModifySolid");
  my_markers.push_back("CCXSectionsModifyShell");
  my_markers.push_back("CCXSectionsModifyBeam");
  my_markers.push_back("CCXSectionsModifyMembrane");
  my_markers.push_back("CCXRigidBodyCreate");

  // For each marker, we want to get the navigation node and assign the node
  // to use this factory to get widgets as needed.
  NavigationModel* model = Claro::instance()->navigation_model();
  for(int i = 0; i < my_markers.size(); i++)
  {
    NavigationNode* node = model->getMarkedNode(my_markers[i]);
    if(node)
      node->setFactory(myFactory);
  }
}
