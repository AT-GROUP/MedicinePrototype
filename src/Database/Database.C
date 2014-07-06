#include "Database.H"
#include <QDebug>

Database::Database() {
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName(DB_NAME);
}

bool Database::createTables() {
  QSqlQuery query;
  
  QString nameTable = "CREATE TABLE MedicalInstitutions (id_institute INTEGER NOT NULL PRIMARY KEY, name TEXT);";
  bool state = query.exec(nameTable);
  
  QString locationTable = "CREATE TABLE Location (coordx DECIMAL, coordy DECIMAL, id_institute INTEGER NOT NULL, FOREIGN KEY(id_institute) REFERENCES MedicalInstitutions(id));";
  state |= query.exec(locationTable);
  
  QString departmentsTable = "CREATE TABLE Departments (reanimation BIT, surgery BIT, ambustial BIT, id_institute INTEGER NOT NULL, FOREIGN KEY(id_institute) REFERENCES MedicalInstitutions(id));";
  state |= query.exec(departmentsTable);
  
  QString infoTable = "CREATE TABLE InstituteInfo (capacity INTEGER, end_fund INTEGER, reanimobile INTEGER, ambulance INTEGER, id_institute INTEGER NOT NULL, FOREIGN KEY(id_institute) REFERENCES MedicalInstitutions(id));";
  state |= query.exec(infoTable);
  
  return state;
}

int Database::init() {
  if (!database.open())
    return -1;
  
  return !createTables();
}

bool Database::getMedicalInstituteByName(QString& instituteName, MedicalInstitute& MI) const {
  QSqlQuery query;
  
  int id = getId(instituteName);
  if (id == -1)
    return false;
  
  return getMedicalInstituteById(id, MI);
}

bool Database::getMedicalInstituteById(int id, MedicalInstitute& MI) const {
  QSqlQuery query;
  
  if (!query.prepare(selectName))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  QSqlRecord tableRec = query.record();
  if (!query.next()) {
    return false;
  } else {
    QString newName = query.value(tableRec.indexOf("name")).toString();
    MI.setName(newName);
    if (query.next())
      return false;
  }
  
  if (!query.prepare(selectLocation))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  tableRec = query.record();
  if (!query.next()) {
    return false;
  } else {
    MI.setCoords(query.value(tableRec.indexOf("coordx")).toDouble(), query.value(tableRec.indexOf("coordy")).toDouble());
    if (query.next())
      return false;
  }
  
  if (!query.prepare(selectDepartments))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  tableRec = query.record();
  if (!query.next()) {
    return false;
  } else {
    MI.setReanimation((bool)query.value(tableRec.indexOf("reanimation")).toInt());
    MI.setSurgery((bool)query.value(tableRec.indexOf("surgery")).toInt());
    MI.setAmbustial((bool)query.value(tableRec.indexOf("ambustial")).toInt());
    if (query.next())
      return false;
  }
  
  if (!query.prepare(selectInfo))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  tableRec = query.record();
  if (!query.next()) {
    return false;
  } else {
    MI.setCapacity(query.value(tableRec.indexOf("capacity")).toInt());
    MI.setEndFund(query.value(tableRec.indexOf("end_fund")).toInt());
    MI.setReanimobile(query.value(tableRec.indexOf("reanimobile")).toInt());
    MI.setAmbulance(query.value(tableRec.indexOf("ambulance")).toInt());
    if (query.next())
      return false;
  }
  
  return true;
}

int Database::getId(QString& name) const {
  QSqlQuery query;
  
  if (!query.prepare(idByName))
    return -1;
  query.bindValue(":name", name);
  if (!query.exec())
    return -1;
  int id;
  if (query.next())
    id = query.value(0).toInt();
  else
    return -1;
  if (query.next())
    return -1;
  return id;
}

bool Database::update(QString& oldName, MedicalInstitute& MI) {
  MedicalInstitute oldMI = MedicalInstitute();
  getMedicalInstituteByName(oldName, oldMI);
  int id = getId(oldName);
  
  QString temp = MI.getName();
  if (getId(temp) != -1)
    return false;
  
  QSqlQuery query;
  
  if (oldMI.getName() != MI.getName()) {
    if (!query.prepare(updateName))
      return false;
    query.bindValue(":name", MI.getName());
    query.bindValue(":id", id);
    if (!query.exec())
      return false;
  }
  
  if (oldMI.getX() != MI.getX() || oldMI.getY() != MI.getY()) {
    if (!query.prepare(updateLocation))
      return false;
    query.bindValue(":x", MI.getX());
    query.bindValue(":y", MI.getY());
    query.bindValue(":id", id);
    if (!query.exec())
      return false;
  }
  
  if (oldMI.getReanimation() != MI.getReanimation() || oldMI.getSurgery() != MI.getSurgery() || oldMI.getAmbustial() != MI.getAmbustial()) {
    if (!query.prepare(updateDepartments))
      return false;
    query.bindValue(":rean", MI.getReanimation());
    query.bindValue(":surg", MI.getSurgery());
    query.bindValue(":ambus", MI.getAmbustial());
    query.bindValue(":id", id);
    if (!query.exec())
      return false;
  }
  
  if (oldMI.getCapacity() != MI.getCapacity() || oldMI.getEndFund() != MI.getEndFund() || oldMI.getAmbulance() != MI.getAmbulance() || oldMI.getReanimobile() != MI.getReanimobile()) {
    if (!query.prepare(updateInfo))
      return false;
    query.bindValue(":cap", MI.getCapacity());
    query.bindValue(":fund", MI.getEndFund());
    query.bindValue(":ambulance", MI.getAmbulance());
    query.bindValue(":reanimobile", MI.getReanimobile());
    query.bindValue(":id", id);
    if (!query.exec())
      return false;
  }
  
  return true;
}

bool Database::erase(QString& instituteName) {
  QSqlQuery query;
  
  int id = getId(instituteName);
  if (id == -1)
    return false;
  
  if (!query.prepare(eraseName))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  
  if (!query.prepare(eraseLocation))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
    
  if (!query.prepare(eraseDepartments))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
    
  if (!query.prepare(eraseInfo))
    return false;
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  
  return true;
}

bool Database::insert(MedicalInstitute& MI) {
  QSqlQuery query;
  
  QString temp = MI.getName();
  int id = getId(temp);
  if (id != -1)
    return false;
  
  if (!query.prepare(insertName))
    return false;
  query.bindValue(":name", MI.getName());
  if (!query.exec())
    return false;
  
  id = getId(temp);
  if (id == -1)
    return false;
  
  if (!query.prepare(insertLocation))
    return false;
  query.bindValue(":x", MI.getX());
  query.bindValue(":y", MI.getY());
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  
  if (!query.prepare(insertDepartments))
    return false;
  query.bindValue(":rean", (int)MI.getReanimation());
  query.bindValue(":ambus", (int)MI.getAmbustial());
  query.bindValue(":surg", (int)MI.getSurgery());
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  
  if (!query.prepare(insertInfo))
    return false;
  query.bindValue(":cap", MI.getCapacity());
  query.bindValue(":fund", MI.getEndFund());
  query.bindValue(":reanimobile", MI.getReanimobile());
  query.bindValue(":ambulance", MI.getAmbulance());
  query.bindValue(":id", id);
  if (!query.exec())
    return false;
  
  return true;
}

void Database::getAllInstitutions(std::vector <MedicalInstitute>& institutions) const {
  QSqlQuery query;
  MedicalInstitute MI = MedicalInstitute();
  
  query.exec(selectAllId);
  while (query.next()) {
    if (getMedicalInstituteById(query.value(0).toInt(), MI))
      institutions.push_back(MI);
  }
}

void MedicalInstitute::setName(QString& name) {
  instituteName = name;
}

void MedicalInstitute::setCoords(double x, double y) {
  coordX = x;
  coordY = y;
}

void MedicalInstitute::setReanimation(bool state) {
  reanimation = state;
}

void MedicalInstitute::setSurgery(bool state) {
  surgery = state;
}

void MedicalInstitute::setAmbustial(bool state) {
  ambustial = state;
}

void MedicalInstitute::setCapacity(int newCapacity) {
  capacity = newCapacity;
}

void MedicalInstitute::setEndFund(int newFund) {
  endFund = newFund;
}

void MedicalInstitute::setAmbulance(int newAmbulance) {
  ambulance = newAmbulance;
}

void MedicalInstitute::setReanimobile(int newReanimobile) {
  reanimobile = newReanimobile;
}

QString MedicalInstitute::getName() const {
  return instituteName;
}

double MedicalInstitute::getX() const {
  return coordX;
}

double MedicalInstitute::getY() const {
  return coordY;
}

bool MedicalInstitute::getReanimation() const {
  return reanimation;
}

bool MedicalInstitute::getSurgery() const {
  return surgery;
}

bool MedicalInstitute::getAmbustial() const {
  return ambustial;
}

int MedicalInstitute::getCapacity() const {
  return capacity;
}

int MedicalInstitute::getEndFund() const {
  return endFund;
}

int MedicalInstitute::getAmbulance() const {
  return ambulance;
}

int MedicalInstitute::getReanimobile() const {
  return reanimobile;
}

void MedicalInstitute::print() const {
  qDebug() << instituteName << " " << coordX << " " << coordY <<
            " " << reanimation << " " << surgery <<
            " " << ambustial << " " << capacity <<
            " " << endFund << " " << ambulance <<
            " " << reanimobile;
}
