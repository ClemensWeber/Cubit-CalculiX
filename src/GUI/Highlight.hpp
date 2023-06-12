
#ifndef HIGHLIGHT_HPP
#define HIGHLIGHT_HPP

#include <QWidget>
#include <QList>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class ModelTree;
class BlocksTree;
class NodesetTree;
class SidesetTree;
class MaterialTree;
class MaterialManagement;
class SectionsTree;
class ConstraintsTree;
class SurfaceInteractionsTree;
class ContactPairsTree;
class AmplitudesTree;
class LoadsTree;
class LoadsForcesTree;
class LoadsPressuresTree;
class BCsTree;
class BCsDisplacementsTree;
class BCsTemperaturesTree;
class HistoryOutputsTree;
class FieldOutputsTree;
class InitialConditionsTree;
class StepsTree;
class StepsLoadsTree;
class StepsLoadsForcesTree;
class StepsLoadsPressuresTree;
class StepsBCsTree;
class StepsBCsDisplacementsTree;
class StepsBCsTemperaturesTree;
class StepsHistoryOutputsTree;
class StepsFieldOutputsTree;
class StepsManagement;
class JobsTree;
class JobsMonitor;
class QTreeWidgetItem;

class CalculiXCoreInterface;

class Highlight : public QWidget
{
  Q_OBJECT

public:
  Highlight(ModelTree *parent);
  ~Highlight();

  CalculiXCoreInterface* ccx_iface;
  QList<QTreeWidgetItem*> selected;

public slots:
  void ModelTreeItemClicked(QTreeWidgetItem* item, int column);
  void ModelTreeItemSelectionChanged();
};

#endif // HIGHLIGHT_HPP