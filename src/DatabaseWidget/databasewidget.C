#include "databasewidget.H"
#include "ui_databasewidget.h"
#include <QTableWidgetItem>
#include "../../src/Database/Database.H"
#include <vector>

DatabaseWidget::DatabaseWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DatabaseWidget)
{
  ui->setupUi(this);
  QStringList columnLabels;
  columnLabels << "Название" << "Координата Х" << "Координата Y" << "Реанимация" << "Хирургия" << "Ожоговое отделение"
               << "Пропускная способность" << "Мощность конечного фонда" << "Количество машин скорой помощи" << "Количество реанимобилей";
  ui->mainTable->setColumnCount(10);
  ui->mainTable->setHorizontalHeaderLabels(columnLabels);

  std::vector <MedicalInstitute> MI = std::vector <MedicalInstitute>();
  db.init();

  db.getAllInstitutions(MI);
  update(MI);
}

DatabaseWidget::~DatabaseWidget()
{
  delete ui;
}

void DatabaseWidget::update(std::vector <MedicalInstitute>& MI) {
  ui->mainTable->setRowCount(MI.size());

  int nameColumn = 0;
  int xColumn = 1;
  int yColumn = 2;
  int reanimationColumn = 3;
  int surgeryColumn = 4;
  int ambustialColumn = 5;
  int capacityColumn = 6;
  int endFundColumn = 7;
  int ambulanceColumn = 8;
  int reanimobileColumn = 9;

  std::vector < std::vector <QTableWidgetItem*> > item = std::vector < std::vector <QTableWidgetItem*> >(MI.size(), std::vector <QTableWidgetItem*>(10));
  QString text;
  ui->mainTable->setSortingEnabled(false);

  for (int row = 0; row < MI.size(); ++row) {
    item[row][nameColumn] = new QTableWidgetItem;
    item[row][nameColumn]->setText(MI[row].getName());
    ui->mainTable->setItem(row, nameColumn, item[row][nameColumn]);

    item[row][xColumn] = new QTableWidgetItem;
    text = QString(std::to_string(MI[row].getX()).c_str());
    item[row][xColumn]->setText(text);
    ui->mainTable->setItem(row, xColumn, item[row][xColumn]);

    item[row][yColumn] = new QTableWidgetItem;
    text = QString(std::to_string(MI[row].getY()).c_str());
    item[row][yColumn]->setText(text);
    ui->mainTable->setItem(row, yColumn, item[row][yColumn]);

    item[row][reanimationColumn] = new QTableWidgetItem;
    if (MI[row].getReanimation())
      item[row][reanimationColumn]->setText("Да");
    else
      item[row][reanimationColumn]->setText("Нет");
    ui->mainTable->setItem(row, reanimationColumn, item[row][reanimationColumn]);

    item[row][surgeryColumn] = new QTableWidgetItem;
    if (MI[row].getSurgery())
      item[row][surgeryColumn]->setText("Да");
    else
      item[row][surgeryColumn]->setText("Нет");
    ui->mainTable->setItem(row, surgeryColumn, item[row][surgeryColumn]);

    item[row][ambustialColumn] = new QTableWidgetItem;
    if (MI[row].getAmbustial())
      item[row][ambustialColumn]->setText("Да");
    else
      item[row][ambustialColumn]->setText("Нет");
    ui->mainTable->setItem(row, ambustialColumn, item[row][ambustialColumn]);

    item[row][capacityColumn] = new QTableWidgetItem;
    text = QString(std::to_string(MI[row].getCapacity()).c_str());
    item[row][capacityColumn]->setText(text);
    ui->mainTable->setItem(row, capacityColumn, item[row][capacityColumn]);

    item[row][endFundColumn] = new QTableWidgetItem;
    text = QString(std::to_string(MI[row].getEndFund()).c_str());
    item[row][endFundColumn]->setText(text);
    ui->mainTable->setItem(row, endFundColumn, item[row][endFundColumn]);

    item[row][ambulanceColumn] = new QTableWidgetItem;
    text = QString(std::to_string(MI[row].getAmbulance()).c_str());
    item[row][ambulanceColumn]->setText(text);
    ui->mainTable->setItem(row, ambulanceColumn, item[row][ambulanceColumn]);

    item[row][reanimobileColumn] = new QTableWidgetItem;
    text = QString(std::to_string(MI[row].getReanimobile()).c_str());
    item[row][reanimobileColumn]->setText(text);
    ui->mainTable->setItem(row, reanimobileColumn, item[row][reanimobileColumn]);
  }

  ui->mainTable->setSortingEnabled(true);
}

double coordX, coordY;
bool reanimation, surgery, ambustial;
int capacity, endFund, ambulance, reanimobile;
