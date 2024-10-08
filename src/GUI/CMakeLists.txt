project(Cubit-CalculiX_component_gui)

set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/ModelTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ModelTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BlocksTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BlocksTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NodesetTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NodesetTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SidesetTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SidesetTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsForcesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsForcesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsPressuresTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsPressuresTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsHeatfluxesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsHeatfluxesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsDisplacementsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsDisplacementsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsTemperaturesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsTemperaturesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsDisplacementsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsDisplacementsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsTemperaturesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsTemperaturesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsForcesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsForcesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsPressuresTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsPressuresTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsHeatfluxesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsHeatfluxesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsGravityTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsGravityTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsCentrifugalTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsLoadsCentrifugalTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsBCsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsBCsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsBCsDisplacementsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsBCsDisplacementsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsBCsTemperaturesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsBCsTemperaturesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsHistoryOutputsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsHistoryOutputsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsFieldOutputsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsFieldOutputsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsTree.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsTree.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PanelTable.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PanelTable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CCXBlocksElementTypePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CCXBlocksElementTypePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagement.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementItem.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementTable.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementTable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementElasticCard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementElasticCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementPlasticCard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementPlasticCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementDensityCard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementDensityCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementExpansionCard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementExpansionCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementSpecificHeatCard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementSpecificHeatCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementConductivityCard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MaterialManagementConductivityCard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateSolidPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateSolidPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateShellPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateShellPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateBeamPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateBeamPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateMembranePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsCreateMembranePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifySolidPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifySolidPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifyShellPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifyShellPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifyBeamPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifyBeamPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifyMembranePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsModifyMembranePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SectionsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsCreateRigidBodyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsCreateRigidBodyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsCreateTiePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsCreateTiePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsModifyRigidBodyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsModifyRigidBodyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsModifyTiePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsModifyTiePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ConstraintsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SurfaceInteractionsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ContactPairsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/AmplitudesDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/OrientationsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsForcesModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsForcesModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsPressuresModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsPressuresModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsHeatfluxesModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsHeatfluxesModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsGravityDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadsCentrifugalDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsDisplacementsModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsDisplacementsModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsTemperaturesModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/BCsTemperaturesModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsModifyNodePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsModifyNodePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsModifyElementPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsModifyElementPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsModifyContactPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsModifyContactPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HistoryOutputsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsModifyNodePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsModifyNodePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsModifyElementPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsModifyElementPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsModifyContactPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsModifyContactPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/FieldOutputsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InitialConditionsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsManagement.hpp
    ${CMAKE_CURRENT_LIST_DIR}/HBCsManagement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyParameterPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyParameterPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyStaticPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyStaticPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyFrequencyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyFrequencyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyBucklePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyBucklePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyHeatTransferPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyHeatTransferPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyCoupledTemperatureDisplacementPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyCoupledTemperatureDisplacementPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyUncoupledTemperatureDisplacementPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsModifyUncoupledTemperatureDisplacementPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsManagement.hpp
    ${CMAKE_CURRENT_LIST_DIR}/StepsManagement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/CustomLinesDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsCreatePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsCreatePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsModifyPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsModifyPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsDeletePanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsDeletePanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsActionsPanel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsActionsPanel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsMonitor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsMonitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsMonitorFRD.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsMonitorFRD.cpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsMonitorFRDPlot.hpp
    ${CMAKE_CURRENT_LIST_DIR}/JobsMonitorFRDPlot.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUITimer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GUITimer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Highlight.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Highlight.cpp
    )

# Add the parent scope so that our parent cmake list can use them
set(GUI_SRC ${SRC} PARENT_SCOPE)
set(GUI_MOC ${MOC} PARENT_SCOPE)
set(GUI_UI  ${UI}  PARENT_SCOPE)
