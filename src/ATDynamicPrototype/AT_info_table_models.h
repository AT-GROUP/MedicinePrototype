#ifndef ATINFOTABLEMODELS_H
#define ATINFOTABLEMODELS_H

#include <QAbstractTableModel>
#include <QMap>

class ATAccident_info_table_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit ATAccident_info_table_model():injured(1) {};

	void set_inj(int new_inj){injured = new_inj;};
private:
	int injured;

	int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

class ATAmbulance_info_table_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit ATAmbulance_info_table_model() : velocity(0),current_accident("none") {};

	void set_vel(int new_vel){velocity = new_vel;};
	void set_acc(QString new_acc){current_accident = new_acc;};
private:
	int velocity;
	QString current_accident;

	int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

class ATHospital_info_table_model : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit ATHospital_info_table_model() : wards(10) {};

	void set_wards(int new_wards){wards = new_wards;};
private:
	int wards;

	int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // ATINFOTABLEMODELS_H

