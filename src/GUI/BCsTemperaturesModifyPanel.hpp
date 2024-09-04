#ifndef BCSTEMPERATURESMODIFYPANEL_HPP
#define BCSTEMPERATURESMODIFYPANEL_HPP

#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>
#include <QTableWidget>
#include <QLineEdit>
#include <QRadioButton>

class CalculiXCoreInterface;

class BCsTemperaturesModifyPanel : public QWidget
{
  Q_OBJECT
  
public:
  explicit BCsTemperaturesModifyPanel(QWidget *parent = 0);
  ~BCsTemperaturesModifyPanel();

  bool isInitialized;
  CalculiXCoreInterface *ccx_iface;
  
private slots:
  void on_pushButton_apply_clicked(bool);

private:
  std::string log;

  QGridLayout* GridLayout;
  QVBoxLayout* VBoxLayout;
  QSpacerItem* vertical_spacer;
  QPushButton* pushButton_apply;
  QHBoxLayout* HBoxLayout_pushButton_apply;
  QSpacerItem* horizontal_spacer_pushButton_apply;
  QHBoxLayout* HBoxLayout_0;
  QHBoxLayout* HBoxLayout_1;
  QHBoxLayout* HBoxLayout_2;
  QHBoxLayout* HBoxLayout_3;
  QHBoxLayout* HBoxLayout_4;
  QLabel* label_0;
  QLabel* label_1;
  QLabel* label_2;
  QLabel* label_3;
  QLabel* label_4;
  QLineEdit* lineEdit_0;
  QComboBox* comboBox_1;
  QLineEdit* lineEdit_2;
  QLineEdit* lineEdit_3;
  QComboBox* comboBox_4;
};

#endif // BCSTEMPERATURESMODIFYPANEL_HPP