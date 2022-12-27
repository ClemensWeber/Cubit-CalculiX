/*!
 *  \file MyComp.cpp
 *  \brief
 *    Provides an example of creating a custom component.
 *  \author Michael Plooster
 *  \date 11 Feb 2014
 */

#include "CalculiXComp.hpp"

#include "Broker.hpp"
#include "ComponentInfo.hpp"
#include "ExportManager.hpp"
#include "MenuManager.hpp"
#include "Observer.hpp"
#include "cmdPanelManager.hpp"
#include "CCXDockWindowTree.hpp"
#include "ToolbarManager.hpp"

// Default constructor. Remember to include the component name (should match
// the module name in mycomp.i).
CalculiXComp::CalculiXComp() :
  Component("CalculiXComp"),
  myMenus(NULL),
  myToolbars(NULL),
  mycmdPanels(NULL),
  myCCXDockWindowTree(NULL),
  myExportManager(NULL),
  mListener(NULL)
{}

CalculiXComp::~CalculiXComp()
{
  if(myMenus)
    delete myMenus;

  if(myToolbars)
    delete myToolbars;

  if(mycmdPanels)
    delete mycmdPanels;

  if(myCCXDockWindowTree)
    delete myCCXDockWindowTree;

  if(myExportManager)
    delete myExportManager;

  if(mListener)
    delete mListener;
}

void CalculiXComp::start_up(int withGUI)
{
  if(withGUI)
  {
    setup_menus();
    setup_toolbars();
    setup_command_panels();
    setup_CCXDockWindowTree(); // command panels has to be setup before dockwindow
    add_exports();
    boolwithGUI = true;
  }

  setup_observers(withGUI);
}

void CalculiXComp::clean_up()
{
  cleanup_menus();
  cleanup_toolbars();
  cleanup_command_panels();
  cleanup_CCXDockWindowTree();
  cleanup_exports();
  cleanup_observers();

  // Let the framework know you are done.
  clean_up_complete();
}

void CalculiXComp::update()
{
  if(boolwithGUI)
  {
    if(myCCXDockWindowTree)
    myCCXDockWindowTree->update();
  }
}

void CalculiXComp::reset()
{
  if(boolwithGUI)
  {
    if(myCCXDockWindowTree)
    myCCXDockWindowTree->reset();
  }
}

void CalculiXComp::setup_menus()
{
  if(!myMenus)
    myMenus = new MenuManager;

  myMenus->add_to_existing_menu();
  myMenus->setup_custom_menu();
}

void CalculiXComp::cleanup_menus()
{
  if(myMenus)
    myMenus->remove_menu_items();
}

void CalculiXComp::setup_toolbars()
{
  if(!myToolbars)
    myToolbars = new ToolbarManager;

  myToolbars->add_to_existing_toolbar();
  myToolbars->setup_custom_toolbar();
}

void CalculiXComp::cleanup_toolbars()
{
  if(myToolbars)
    myToolbars->remove_toolbar_items();
}

void CalculiXComp::setup_command_panels()
{
  if(!mycmdPanels)
    mycmdPanels = new cmdPanelManager;

  mycmdPanels->initialize();
}

void CalculiXComp::cleanup_command_panels()
{
  if(mycmdPanels)
    mycmdPanels->clear();
}

void CalculiXComp::setup_CCXDockWindowTree()
{
  if(!myCCXDockWindowTree)
    myCCXDockWindowTree = new CCXDockWindowTree;

  myCCXDockWindowTree->initialize();
}

void CalculiXComp::cleanup_CCXDockWindowTree()
{
  if(myCCXDockWindowTree)
    myCCXDockWindowTree->clear();
}


void CalculiXComp::add_exports()
{
  if(!myExportManager)
  {
    myExportManager = new ExportManager();
    myExportManager->add_export_types();
  }
}

void CalculiXComp::cleanup_exports()
{
  if(myExportManager)
    myExportManager->remove_export_types();
}

void CalculiXComp::setup_observers(int withGUI)
{
  if(!mListener)
  {
    mListener = new Observer();

    // Let Cubit know that this class will be observing events
    mListener->register_observer();

    // get a connection down to the observer
    mListener->fetch_comp(this);
  }
}

void CalculiXComp::cleanup_observers()
{
  if(mListener)
  {
    // If cubitcomp is still loaded, we need to unregister the observer.
    ComponentInfo cubitcomp_info;
    Broker::instance()->get_component_info("cubitcomp", cubitcomp_info);
    if(cubitcomp_info.get_state() == "Loaded")
      mListener->unregister_observer();

    delete mListener;
    mListener = NULL;
  }
}
