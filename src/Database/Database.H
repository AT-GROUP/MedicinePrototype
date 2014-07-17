#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <vector>

const QString DB_NAME = "MedicineDatabase.sqlite";

class MedicalInstitute {
  private:
    QString instituteName;
    double coordX, coordY;  
    bool reanimation, surgery, ambustial;
    int capacity, endFund, ambulance, reanimobile;
    int id;

  public:
    MedicalInstitute(QString name = "", double x = 0.0,
              double y = 0.0, bool reanDep = false, bool surgDep = false,
              bool ambusDep = false, int cap = 0, int fund = 0,
              int amb = 0, int reanimob = 0) 
              :instituteName(name),
              coordX(x),
              coordY(y),
              reanimation(reanDep),
              surgery(surgDep),
              ambustial(ambusDep),
              capacity(cap),
              endFund(fund),
              ambulance(amb),
              reanimobile(reanimob)
              {}
    ~MedicalInstitute() {}
    
    //TODO change print --> toString
    void print() const;
    
    void setName(QString&);
    void setCoords(double, double);
    void setReanimation(bool);
    void setSurgery(bool);
    void setAmbustial(bool);
    void setCapacity(int);
    void setEndFund(int);
    void setAmbulance(int);
    void setReanimobile(int);
    
    QString getName() const;
    double getX() const;
    double getY() const;
    bool getReanimation() const;
    bool getSurgery() const;
    bool getAmbustial() const;
    int getCapacity() const;
    int getEndFund() const;
    int getAmbulance() const;
    int getReanimobile() const;
};

class Database {
  private:
    QSqlDatabase database;
    
    const QString insertName = "INSERT INTO MedicalInstitutions (name) VALUES (:name)";
    const QString insertLocation = "INSERT INTO Location (coordx, coordy, id_institute) VALUES (:x, :y, :id)";
    const QString insertDepartments = "INSERT INTO Departments (reanimation, surgery, ambustial, id_institute) VALUES (:rean, :surg, :ambus, :id)";
    const QString insertInfo = "INSERT INTO InstituteInfo (capacity, end_fund, reanimobile, ambulance, id_institute) VALUES (:cap, :fund, :reanimobile, :ambulance, :id)";
    
    const QString eraseName = "DELETE FROM MedicalInstitutions WHERE (id_institute = :id);";
    const QString eraseLocation = "DELETE FROM Location WHERE (id_institute = :id);";
    const QString eraseDepartments = "DELETE FROM Departments WHERE (id_institute = :id);";
    const QString eraseInfo = "DELETE FROM InstituteInfo WHERE (id_institute = :id);";
    
    const QString selectAllId = "SELECT MedicalInstitutions.id_institute FROM MedicalInstitutions;";
    const QString idByName = "SELECT MedicalInstitutions.id_institute FROM MedicalInstitutions WHERE (MedicalInstitutions.name = :name);";
    const QString selectName = "SELECT * FROM MedicalInstitutions WHERE (MedicalInstitutions.id_institute = :id);";
    const QString selectLocation = "SELECT * FROM Location WHERE (Location.id_institute = :id);";
    const QString selectDepartments = "SELECT * FROM Departments WHERE (Departments.id_institute = :id);";
    const QString selectInfo = "SELECT * FROM InstituteInfo WHERE (InstituteInfo.id_institute = :id);";
    
    const QString updateName = "UPDATE MedicalInstitutions SET name = :name WHERE (id_institute = :id);";
    const QString updateLocation = "UPDATE Location SET coordx = :x, coordy = :y WHERE (id_institute = :id);";
    const QString updateDepartments = "UPDATE Departments SET reanimation = :rean, surgery = :surg, ambustial = :ambus WHERE (id_institute = :id);";
    const QString updateInfo = "UPDATE InstituteInfo SET capacity = :cap, end_fund = :fund, reanimobile = :reanimobile, ambulance = :ambulance WHERE (id_institute = :id);";
    
    int getId(QString&) const;
    bool createTables();
    bool getMedicalInstituteById(int, MedicalInstitute&) const;
  public:
    Database();
    ~Database() {}
    int init();
    bool insert(MedicalInstitute&);
    bool erase(QString&);
    bool getMedicalInstituteByName(QString&, MedicalInstitute&) const;
    bool update(QString&, MedicalInstitute&);
    bool getAllInstitutions(std::vector <MedicalInstitute>&) const;
};

#endif
