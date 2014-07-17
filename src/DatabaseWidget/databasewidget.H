#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include "../../src/Database/Database.H"

namespace Ui {
  class DatabaseWidget;
}

class DatabaseWidget : public QWidget
{
  Q_OBJECT
  
public:
  explicit DatabaseWidget(QWidget *parent = 0);
  ~DatabaseWidget();
  
private:
  Database db;
  void update(std::vector <MedicalInstitute>&);
  Ui::DatabaseWidget *ui;
};

#endif // DATABASEWIDGET_H
