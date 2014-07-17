#include <QApplication>
#include <QDebug>
//#include <QtWidgets>
//#include <QMainWindow>
#include "mainwindow.H"
#include "../Database/Database.H"
#include <vector>

int main(int argc, char *argv[])
{
  Database db = Database();
  db.init();

  MedicalInstitute MI = MedicalInstitute("some inst 1", 2310.2, 1345.35, true, false, true, 110, 0, 15, 57);
  db.insert(MI);
  MI = MedicalInstitute("some inst 2", 23, 15.46, true, true, false, 103, 10, 10, 50);
  db.insert(MI);
  MI = MedicalInstitute("some inst 3", 125.346, 976, false, true, false, 10, 5, 7, 5);
  db.insert(MI);

  std::vector <MedicalInstitute> institutions;
  db.getAllInstitutions(institutions);
  for (int i = 0; i < (int)institutions.size(); i++)
    institutions[i].print();

  MI = MedicalInstitute();
  QString oldName = "some inst 2";
  db.getMedicalInstituteByName(oldName, MI);
  QString newName = "new inst 2 name";
  MI.setName(newName);
  MI.setCapacity(777);
  db.update(oldName, MI);

  qDebug() << "\nafter update";
  institutions.clear();
  db.getAllInstitutions(institutions);
  for (int i = 0; i < (int)institutions.size(); i++)
    institutions[i].print();

  QString delName = "some inst 3";
  db.erase(delName);

  qDebug() << "\nafter erase";
  institutions.clear();
  db.getAllInstitutions(institutions);
  for (int i = 0; i < (int)institutions.size(); i++)
    institutions[i].print();

  QApplication a(argc, argv);

  MainWindow w;
  w.show();

  return a.exec();
}
