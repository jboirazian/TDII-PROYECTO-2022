#include "personal.h"

/*--------------------CONSTRUCTOR--------------------*/

personal::personal()
{
    id = 0;
    nombre = nullptr;
    apellido = nullptr;
    tarjetaID = nullptr;
    estado = 0;
}


/*--------------------METODOS--------------------*/

void personal::setPersonal(int id, QString nombre, QString apellido, QString tarjetaID, char estado)
{
    this->id = id;
    this->nombre = nombre;
    this->apellido = apellido;
    this->tarjetaID = tarjetaID;
    this->estado = estado;
}

int personal::getId()
{
    return id;
}

QString personal::getNombre()
{
    return nombre;
}

QString personal::getApellido()
{
    return apellido;
}

QString personal::getTarjetaID()
{
    return tarjetaID;
}

char personal::getEstado()
{
    return estado;
}
