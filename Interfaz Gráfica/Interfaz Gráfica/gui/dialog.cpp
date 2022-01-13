#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
QString ENVIAR_DATOS(const QString& datos);
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_2_accepted()
{
   QString TRAMA;
QString TRAMA_ELIMINAR_4CERO= "E0000";
QString TRAMA_ELIMINAR_3CERO= "E000";
QString TRAMA_ELIMINAR_2CERO= "E00";
QString TRAMA_ELIMINAR_1CERO= "E0";
QString TRAMA_ELIMINAR_0CERO= "E";
if(0<ui->lineEdit->text().toInt()){
    TRAMA=TRAMA_ELIMINAR_4CERO+ui->lineEdit->text();
}
if(9<ui->lineEdit->text().toInt())
{
       TRAMA=TRAMA_ELIMINAR_3CERO+ui->lineEdit->text();

}
if(99<ui->lineEdit->text().toInt())
{
       TRAMA=TRAMA_ELIMINAR_2CERO+ui->lineEdit->text();

}
if(999<ui->lineEdit->text().toInt())
{
       TRAMA=TRAMA_ELIMINAR_1CERO+ui->lineEdit->text();

}
if(9999<(ui->lineEdit->text().toInt()))
{
       TRAMA=TRAMA_ELIMINAR_0CERO+ui->lineEdit->text();

}

ENVIAR_DATOS(TRAMA);

emit notifyEliminarAccepted(ui->lineEdit->text().toInt());

}

void Dialog::on_buttonBox_2_rejected()
{
    ENVIAR_DATOS("C");

    emit notifyEliminarAccepted(ui->lineEdit->text().toInt());
}
