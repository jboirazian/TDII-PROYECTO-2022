#ifndef PERSONAL_H
#define PERSONAL_H

#include "main.h"

class personal
{
public:
    personal();

    void setPersonal(int id, QString nombre, QString apellido, QString tarjetaID, char estado);

    int getId();
    QString getNombre();
    QString getApellido();
    QString getTarjetaID();
    char getEstado();


private:
    int id;
    QString nombre;
    QString apellido;
    QString tarjetaID;
    char estado;
};

#endif // PERSONAL_H
