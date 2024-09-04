#ifndef CONTACTPAIRSCREATEPANEL_HPP
#define CONTACTPAIRSCREATEPANEL_HPP

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

class ContactPairsCreatePanel : public QWidget
{
  Q_OBJECT
  
public:
  explicit ContactPairsCreatePanel(QWidget *parent = 0);
  ~ContactPairsCreatePanel();

  bool isInitialized;
  CalculiXCoreInterface *ccx_iface;
  
private slots:
  void on_pushButton_apply_clicked(bool);
  void on_radioButton_5_toggled(bool toggled);
  void on_radioButton_6_toggled(bool toggled);

private:
  std::string log;

  QGridLayout* GridLayout;
  QVBoxLayout* VBoxLayout;
  QSpacerItem* vertical_spacer;
  QPushButton* pushButton_apply;
  QHBoxLayout* HBoxLayout_pushButton_apply;
  QSpacerItem* horizontal_spacer_pushButton_apply;
  QHBoxLayout* HBoxLayout_1;
  QHBoxLayout* HBoxLayout_2;
  QHBoxLayout* HBoxLayout_3;
  QHBoxLayout* HBoxLayout_4;
  QHBoxLayout* HBoxLayout_5;
  QHBoxLayout* HBoxLayout_6;
  QLabel* label_1;
  QLabel* label_2;
  QLabel* label_3;
  QLabel* label_4;
  QLabel* label_5;
  QLabel* label_6;
  QLineEdit* lineEdit_1;
  QComboBox* comboBox_2;
  QLineEdit* lineEdit_3;
  QLineEdit* lineEdit_4;
  QRadioButton* radioButton_5;
  QLineEdit* lineEdit_5;
  QRadioButton* radioButton_6;
  QLineEdit* lineEdit_6;
};

#endif // CONTACTPAIRSCREATEPANEL_HPP