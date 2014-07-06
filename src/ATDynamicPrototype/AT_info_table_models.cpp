#include "AT_info_table_models.h"

//====================== Accidents ==============================
int ATAccident_info_table_model::rowCount(const QModelIndex &parent) const
{
    return 1;
}
int ATAccident_info_table_model::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ATAccident_info_table_model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
        {
            if (index.row() == 0)
                return ("Casualties");
        }
        if (index.column() == 1)
        {
            if (index.row() == 0)
                return injured;
        }
    }
    return QVariant();
}

//====================== Ambulances ==============================
int ATAmbulance_info_table_model::rowCount(const QModelIndex &parent) const
{
    return 2;
}
int ATAmbulance_info_table_model::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ATAmbulance_info_table_model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
        {
            if (index.row() == 0)
                return ("Velocity");
            if (index.row() == 1)
                return ("Current Accident");
        }
        if (index.column() == 1)
        {
            if (index.row() == 0)
                return velocity;
            if (index.row() == 1)
                return current_accident;
        }
    }
    return QVariant();
}

//====================== Hospitals ===============================
int ATHospital_info_table_model::rowCount(const QModelIndex &parent) const
{
    return 1;
}
int ATHospital_info_table_model::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ATHospital_info_table_model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
        {
            if (index.row() == 0)
                return ("Hospital wards");
        }
        if (index.column() == 1)
        {
            if (index.row() == 0)
                return wards;
        }
    }
    return QVariant();
}