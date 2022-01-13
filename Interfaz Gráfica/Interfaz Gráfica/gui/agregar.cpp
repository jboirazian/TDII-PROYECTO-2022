#include "agregar.h"
#include "ui_agregar.h"
#include "mainwindow.h"
#include "main.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

QString ENVIAR_DATOS(const QString& datos);

/*--------------------CONSTRUCTOR--------------------*/

Agregar::Agregar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Agregar)
{
    ui->setupUi(this);

    QFile importedCSV(QString(DBFILE_));
    QStringList rowOfData;
    QString data;



    importedCSV.close();
}



/*--------------------DESTRUCTOR--------------------*/

Agregar::~Agregar()
{
    delete ui;
}



/*--------------------SLOTS--------------------*/

/*
Nombre: void Agregar::on_buttonBox_accepted()

Descripcion: Escribe los datos ingresados en el dialogo en el archivo y emite una señal para que la ventana principal
pueda actualizar la tabla de la base de datos con la nueva informacion del personal.
*/
void Agregar::on_buttonBox_accepted()
{  
    QString TRAMA;
    QString TRAMA_ELIMINAR_4CERO= ",0000";
    QString TRAMA_ELIMINAR_3CERO= ",000";
    QString TRAMA_ELIMINAR_2CERO= ",00";
    QString TRAMA_ELIMINAR_1CERO= ",0";
    QString TRAMA_ELIMINAR_0CERO= ",";

    if(0<ui->leID->text().toInt()){
        TRAMA=TRAMA_ELIMINAR_4CERO+ui->leID->text();
    }
    if(9<ui->leID->text().toInt())
    {
           TRAMA=TRAMA_ELIMINAR_3CERO+ui->leID->text();

    }
    if(99<ui->leID->text().toInt())
    {
           TRAMA=TRAMA_ELIMINAR_2CERO+ui->leID->text();

    }
    if(999<ui->leID->text().toInt())
    {
           TRAMA=TRAMA_ELIMINAR_1CERO+ui->leID->text();

    }
    if(9999<(ui->leID->text().toInt()))
    {
           TRAMA=TRAMA_ELIMINAR_0CERO+ui->leID->text();

    }


    QString PERSONA= 'A' + ui->leTarjetaID->text() + TRAMA  +','+ ui->leNombre->text() +','+ ui->leApellido->text() +'\n'+'\0'  ;

    ENVIAR_DATOS(PERSONA);

    QFile importedCSV(QString(DBFILE));
        qDebug() << "App path agregar.cpp : " << qApp->applicationDirPath();

        if (!importedCSV.open(QFile::WriteOnly | QIODevice::Append |QIODevice::Text))
        {
            qDebug() << "No se pudo abrir el archivo 'dataBase.csv'.-----";
        }

        //Escribo en el archivo 'importedCSV' los datos ingresados en los LabelEdits del dialog 'Agregar'
        QTextStream stream(&importedCSV);
        stream << '\n';
        stream << ui->leID->text() + ",";
        stream << ui->leNombre->text() + ",";
        stream << ui->leApellido->text() + ",";
        stream << ui->leTarjetaID->text() + ",";
        stream << "Ausente";

        importedCSV.close();

        //Emito una señal para que MainWindow actualice su TableWidget con los datos del nuevo personal
        emit notifyAgregarAccepted(ui->leID->text(), ui->leNombre->text(), ui->leApellido->text(), ui->leTarjetaID->text());
}

void Agregar::on_buttonBox_rejected()
{
    ENVIAR_DATOS("C");
}

void Agregar::on_pushButton_clicked()
{
    QString subString = ENVIAR_DATOS("").mid(0,10);
        ui->leTarjetaID->insert(subString);
}
