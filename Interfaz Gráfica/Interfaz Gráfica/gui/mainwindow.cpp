#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agregar.h"
#include "dialog.h"

#include <QDateTime>
#include <QTimer>
#include "globales.h"
#include "libusb.h"
#include <iostream>

  static int N_OP=0;
  int rowCount, columnCount;
 QTimer *timer = new QTimer();
 QTableWidgetItem *item;
/*--------------------CONSTRUCTOR--------------------*/

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ui_agregar(nullptr)
{
    ui->setupUi(this);
    importCSVFileDB();
    importCSVFileH();
}



/*--------------------DESTRUCTOR--------------------*/

MainWindow::~MainWindow()
{
    delete ui;
}



/*-------------------------------------*/






/*--------------------METODOS--------------------*/

/*
Nombre: void MainWindow::importCSVFileDB()

Descripcion: Inicializa la tabla de la base de datos cargando la informacion del archivo.
*/
void MainWindow::importCSVFileDB()
{
    qDebug() << "App path : " << qApp->applicationDirPath();
    QFile importedCSV(QString(DBFILE_));
    QTableWidgetItem *item;
    QStringList rowOfData;
    QStringList rowData;
    QString data;
    int i,j;
    int rowCount, columnCount;

    if (importedCSV.open(QFile::ReadOnly))
    {
        qDebug()<<"tamanio:"<<importedCSV.size();
        if(importedCSV.size()==0){
            return ; // EL ARCHIVO ESTA VACIO NO HACE FALTA CARGAR NADA
        }
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    rowCount = rowOfData.size();
    qDebug()<<rowCount;
    columnCount = 5;

    ui->twBaseDeDatos->setRowCount(rowCount);
    ui->twBaseDeDatos->setColumnCount(columnCount);

    for(i = 0; i < rowCount; i++)
    {
        for(j = 0; j < columnCount; j++)
        {
            item = new QTableWidgetItem;

            rowData = rowOfData.at(i).split(",");
            //item->setData(Qt::EditRole,rowData[j]);
          item ->setText(rowData[j]);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable); //Hace que la tabla no sea editable
            ui->twBaseDeDatos->setItem(i,j,item);
        }
    }

   i=0;
   while(i!=rowCount){
       qDebug()<<ui->twBaseDeDatos->model()->index(i,4).data().toString();
       if(ui->twBaseDeDatos->model()->index(i,4).data().toString().at(0)=='A'){
           ui->twBaseDeDatos->model()->setData(ui->twBaseDeDatos->model()->index(i,4,QModelIndex()),QColor(Qt::red),Qt::BackgroundRole);
       }
       else{
           ui->twBaseDeDatos->model()->setData(ui->twBaseDeDatos->model()->index(i,4,QModelIndex()),QColor(Qt::green),Qt::BackgroundRole);
       }
       i++;
   }

ui->twBaseDeDatos->sortByColumn(1, Qt::AscendingOrder);

}

/*
Nombre: void MainWindow::importCSVFileH()

Descripcion: Inicializa la tabla del historial cargando la informacion del archivo.
*/
void MainWindow::importCSVFileH()
{
    QFile importedCSV(QString(HFILE_));
    QTableWidgetItem *item;
    QStringList rowOfData;
    QStringList rowData;
    QString data;
    int i,j;


    if (importedCSV.open(QFile::ReadOnly))
    {
        if(importedCSV.size()==0){
            return ; // EL ARCHIVO ESTA VACIO NO HACE FALTA CARGAR NADA
        }
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    rowCount = rowOfData.size();
    columnCount = 7;

    ui->twHistorial->setRowCount(rowCount);
    ui->twHistorial->setColumnCount(columnCount);

    for(i = 0; i < rowCount; i++)
    {
        for(j = 0; j < columnCount; j++)
        {
            item = new QTableWidgetItem;
            rowData = rowOfData.at(i).split(",");
            item ->setText(rowData[j]);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable); //Hace que la tabla no sea editable
            ui->twHistorial->setItem(i,j,item);
        }
    }

    ui->twHistorial->sortByColumn(0, Qt::DescendingOrder);
}

QString ENVIAR_DATOS(const QString& datos)
{
    QString Buff;
    QString Buff_RX;
    QString Buff_TX;
    unsigned int Datos;

    unsigned char  TxData [SIZE_TRAMA_USB];
     unsigned char RxData [SIZE_TRAMA_USB];
    unsigned char i;

    memcpy( TxData, datos.toStdString().c_str() ,datos.size());

    unsigned int Enviados;
    Buff=datos;
    int actual_length;

    qDebug() << datos;



    qDebug() << TxData[0];

    libusb_claim_interface(dev_handle, 0);
    i=0;
    Enviados = libusb_interrupt_transfer(dev_handle , 0x01 , TxData , sizeof (TxData) , &actual_length , 1000);
    libusb_interrupt_transfer(dev_handle , 0x81 , RxData , sizeof (RxData) , &actual_length , 1000);
    Buff_RX=QString::fromLatin1(reinterpret_cast<const  char *>(RxData));
    Buff_TX=QString::fromLatin1(reinterpret_cast<const  char *>(TxData));
    qDebug() << actual_length ;
    qDebug() << "data:" << Buff_TX << "Enviado";
    qDebug() << "data:" << Buff_RX << "RECIBIDA";
    return Buff_RX;

}

/*--------------------SLOTS--------------------*/

/*
Nombre: void MainWindow::appendTWBaseDeDatos(const QString& id, const QString& nombre, const QString& apellido, const QString& tarjeta)

Descripcion: Agrega la informacion del nuevo personal del dialogo 'Agregar' en la tabla.
*/
void MainWindow::appendTWBaseDeDatos(const QString& id, const QString& nombre, const QString& apellido, const QString& tarjeta)
{
    int rowCount;


    rowCount = ui->twBaseDeDatos->rowCount();

    ui->twBaseDeDatos->insertRow(rowCount);

    item = new QTableWidgetItem;
    item ->setText(id);
    ui->twBaseDeDatos->setItem(rowCount,0,item);

    item = new QTableWidgetItem;
    item ->setText(nombre);
    ui->twBaseDeDatos->setItem(rowCount,1,item);

    item = new QTableWidgetItem;
    item ->setText(apellido);
    ui->twBaseDeDatos->setItem(rowCount,2,item);

    item = new QTableWidgetItem;
    item ->setText(tarjeta);
    ui->twBaseDeDatos->setItem(rowCount,3,item);

    item = new QTableWidgetItem;
    item ->setText("Ausente");
    ui->twBaseDeDatos->setItem(rowCount,4,item);
    ui->twBaseDeDatos->model()->setData(ui->twBaseDeDatos->model()->index(rowCount,4,QModelIndex()),QColor(Qt::red),Qt::BackgroundRole);

}

/*
Nombre: void MainWindow::on_twBaseDeDatos_itemPressed(QTableWidgetItem *item)

Descripcion: Cuando se apreta la tabla, se habitita la opcion de editar y eliminar la fila.
*/
void MainWindow::on_twBaseDeDatos_itemPressed(QTableWidgetItem *item)
{

}

/*
Nombre: void MainWindow::on_pbEditar_clicked()

Descripcion: Cuando se apreta el boton 'Editar', hace que la tabla sea editable
*/
void MainWindow::on_pbEditar_clicked()
{
    int i,j;


    for(i = 0; i < ui->twBaseDeDatos->rowCount(); i++)
        for(j = 0; j < ui->twBaseDeDatos->columnCount(); j++)
            ui->twBaseDeDatos->item(i,j)->setFlags(ui->twBaseDeDatos->item(i,j)->flags() | Qt::ItemIsEditable); //Hace que la tabla sea editable
}

/*
Nombre: void MainWindow::on_pbAgregar_clicked()

Descripcion: Al presionar el boton 'Agregar' se abre un Dialog para ingresar datos del nuevo personal.
Si se apreta OK, se actualiza el archivo de base de datos de los personales, caso contrario, se descartan los datos ingresados.
*/
void MainWindow::on_pbAgregar_clicked()
{
  timer->stop();
   ENVIAR_DATOS("H");

    ui_agregar = new Agregar(this);
    qDebug() << QCoreApplication::applicationDirPath() ;
    connect(ui_agregar, &Agregar::notifyAgregarAccepted, this, &MainWindow::appendTWBaseDeDatos);

    ui_agregar->setModal(true);
    ui_agregar->exec();
    timer->start(1000);


}



void MainWindow::on_Conectar_Bt_clicked()
{
    signed int r;
    unsigned int cnt;
    unsigned int i;
    signed int j, k, p;

    connected = 1;

    r = libusb_init(&ctx);

    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation

    cnt = libusb_get_device_list(ctx,&devs);

    qDebug() << "Hay" << cnt << "dispositivos conectados";

    for (i = 0; i < cnt; i++)
    {
        r = libusb_get_device_descriptor(devs[i],&desc);

        if(r < 0)
        {
            qDebug() << "Error con el device descriptor del dispositivo";
        }

        if(desc.idProduct == MY_PRODUCT && desc.idVendor == MY_VENDOR)
        {
           // ui->Enviar_Bt->setEnabled(true);
            ui->pbAgregar->setEnabled(true);
            //ui->pbEditar->setEnabled(true);
            Dispositivo = i;

            qDebug() << "Mi dispositivo es el" << i;
            qDebug() << "Tiene " << desc.bNumConfigurations << " cantidad de configuraciones";
            qDebug() << "Vendor ID: " << desc.idVendor;
            qDebug() << "Product ID: " << desc.idProduct;
            qDebug() << "Device Class: " << desc.bDeviceClass;
            qDebug() << "Serial Number: " << desc.iSerialNumber;


            libusb_get_config_descriptor(devs[Dispositivo], 0, &config);


             qDebug() <<"Interfaces: "<<(uint8_t)config->bNumInterfaces;

             for(j=0; j<(uint8_t )(config->bNumInterfaces); j++)
             {
                 inter = &config->interface[j];

                 qDebug()<<"Cantidad de conf. alternativas: "<<(uint8_t) (inter->num_altsetting);

                 for(k=0; k < (uint8_t) (inter->num_altsetting); k++)
                 {
                     interdesc = &inter->altsetting[k];

                     qDebug() << "Cant. de Interfaces: "<<(uint8_t )interdesc->bInterfaceNumber;

                     qDebug() << "Cant. de Endpoints: "<<(uint8_t )interdesc->bNumEndpoints;

                     for(p= 0 ; p<(uint8_t )interdesc->bNumEndpoints; p++)
                     {
                            epdesc = &interdesc->endpoint[p];

                            qDebug() << "Tipo de Descriptor: "<<(uint8_t )epdesc->bDescriptorType;

                            qDebug() << "Dirección de EP: "<<(uint8_t )epdesc->bEndpointAddress;

                     }

                 }
             }

            libusb_free_config_descriptor(config);


            r = libusb_open(devs[Dispositivo],&dev_handle);

            if(r<0)
            {
                qDebug() << "Error" << r << "abriendo dispositivo";
                return;
            }
            QDateTime date = QDateTime::currentDateTime();
            QDate date_day_of_week;
            QString formattedTime = date.toString("dd.MM.yyyy.hh:mm:ss");
            QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
            int anio=(formattedTimeMsg[9]-'0')+(formattedTimeMsg[8]-'0')*10+(formattedTimeMsg[7]-'0')*100+(formattedTimeMsg[6]-'0')*1000;
            int mes=(formattedTimeMsg[4]-'0')+(formattedTimeMsg[3]-'0')*10;
            int dia= (formattedTimeMsg[1]-'0')+(formattedTimeMsg[0]-'0')*10;

            date_day_of_week.setDate(anio,mes,dia);
            int dia_semana = date_day_of_week.dayOfWeek();

             QString FECHA_USB= 'T' + formattedTime + '.' + QString::number(dia_semana);
             qDebug() << FECHA_USB;
             ENVIAR_DATOS(FECHA_USB);



             connect(timer, SIGNAL(timeout()), this, SLOT(CHECK_USB()));
             timer->start(1000);
        }
    }
}

void MainWindow::on_Cancelar_lectura_clicked()
{
ENVIAR_DATOS("C");////CANCELAR OPERACION
}


QString MainWindow::CHECK_USB(){

 QString TRAMA_DATOS_TOTAL = ENVIAR_DATOS("Z").mid(0,11);
 QString ENCABEZADO =  TRAMA_DATOS_TOTAL.at(0);


 if(ENCABEZADO!="N")////// HAY UNA TARJETA DISPONIBLE
 {

     QDateTime date = QDateTime::currentDateTime();
     QString formattedTime = date.toString("hh:mm:ss");
     QString formattedDAY = date.toString("dd/MM/yy");
    QString E_I;

     if(TRAMA_DATOS_TOTAL.at(10)=="1"){
         E_I="INGRESO";
     }
     else{

           E_I="EGRESO";
     }
     int i=1;
     int N__OP=0;
     ////ENCONTRAR EL VALOR DE OPERACION ACTUAL
     N__OP= ui->twHistorial->model()->rowCount()-1;

     //// ENCONTRAR EL NOMBRE Y APELLIDO
     QString NOMBRE;
     QString APELLIDO;
    i=0;
    while( ui->twBaseDeDatos->model()->index(i,3).data().toString() !=TRAMA_DATOS_TOTAL.mid(0,10) && i<=100){
        qDebug()<<ui->twBaseDeDatos->model()->index(i,3).data().toString();
        i++;
     }

     NOMBRE=ui->twBaseDeDatos->model()->index(i,1).data().toString() ;
     APELLIDO=ui->twBaseDeDatos->model()->index(i,2).data().toString() ;
     qDebug()<<NOMBRE;
     qDebug()<<APELLIDO;

     QFile importedCSV(QString(HFILE_));


         if (!importedCSV.open(QFile::WriteOnly | QIODevice::Append |QIODevice::Text))
         {
             qDebug() << "No se pudo abrir el archivo 'historial.log'.";
             return "ERROR";
         }




         //Escribo en el archivo ''historial.log'
         QTextStream stream(&importedCSV);
         stream << '\n';
         stream <<   QString::number(N__OP) + ",";
         stream << formattedDAY + ",";
         stream << formattedTime + ",";
         stream << E_I+ ",";
         stream << TRAMA_DATOS_TOTAL.mid(0,10) + ",";
         stream << NOMBRE + ",";
         stream << APELLIDO ;

         importedCSV.close();
         N_OP++;




     //// AGREGO LOS DATOS A LA WIDGET DEL HISTORIAL
    ui->twHistorial->insertRow(0);
    ui->twHistorial->setItem(0, 4, new QTableWidgetItem(TRAMA_DATOS_TOTAL.mid(0,10)));
    ui->twHistorial->setItem(0, 2, new QTableWidgetItem(formattedTime));
    ui->twHistorial->setItem(0, 1, new QTableWidgetItem(formattedDAY));
    ui->twHistorial->setItem(0, 3, new QTableWidgetItem(E_I));
    ui->twHistorial->setItem(0, 5, new QTableWidgetItem(NOMBRE));
    ui->twHistorial->setItem(0, 6, new QTableWidgetItem(APELLIDO));
    ui->twHistorial->setItem(0, 0, new QTableWidgetItem(QString::number(N__OP)));

    /// PONGO PRESENTE/AUSENTE/RETIRADO EN EL CASILLERO
    PERSONA_STATUS(i);
    ///ACTUALIZO EL CSV
    exportCSVFileH();
    return TRAMA_DATOS_TOTAL;
 }


return ENCABEZADO;

}

void MainWindow::PERSONA_STATUS(int row){

    if(ui->twBaseDeDatos->model()->index(row,4).data().toString()=="Ausente"){
        ui->twBaseDeDatos->setItem(row, 4, new QTableWidgetItem("Presente"));
        ui->twBaseDeDatos->model()->setData(ui->twBaseDeDatos->model()->index(row,4,QModelIndex()),QColor(Qt::green),Qt::BackgroundRole);
    }
    else{
        ui->twBaseDeDatos->setItem(row, 4, new QTableWidgetItem("Ausente"));
        ui->twBaseDeDatos->model()->setData(ui->twBaseDeDatos->model()->index(row,4,QModelIndex()),QColor(Qt::red),Qt::BackgroundRole);
    }



}



void MainWindow::on_pushButton_clicked()
{
    qDebug()<< CHECK_USB();
}

void MainWindow::Borrar_DB(int ID){


int i =0;
while( ui->twBaseDeDatos->model()->index(i,0).data().toInt()!= ID && i<=100){
            qDebug()<< ui->twBaseDeDatos->model()->index(i,0).data().toInt();
            i++;
}

ui->twBaseDeDatos->removeRow(i);//BORRO ESA FILA.

/// ACTUALIZO EL CSV
exportCSVFileH();
}


void MainWindow::exportCSVFileH(){

    int i=0;
    int N_ROWS = ui->twBaseDeDatos->model()->rowCount();
    qDebug()<<N_ROWS;
    QFile f(QString(DBFILE_));
    if (f.open(QIODevice::WriteOnly)) {
        QTextStream stream(&f);
        while(i<N_ROWS){

            stream << ui->twBaseDeDatos->model()->index(i,0).data().toString() + ",";///ID
            stream << ui->twBaseDeDatos->model()->index(i,1).data().toString()+ ",";/// NOMBRE
            stream << ui->twBaseDeDatos->model()->index(i,2).data().toString() + ",";/// APELLIDO
            stream << ui->twBaseDeDatos->model()->index(i,3).data().toString() + ",";/// NUMERO TARJETA
            stream << ui->twBaseDeDatos->model()->index(i,4).data().toString();/// AUSENTE/PRESENTE
            if(i!=N_ROWS-1){
                stream << '\n';
            }
            i++;
        }

    }





}

void MainWindow::on_pbEliminar_clicked()
{
    timer->stop();
    ENVIAR_DATOS("H");/// PANTALLA DE CONFIGURACION
    ui_dialog = new Dialog(this);
    connect(ui_dialog, &Dialog::notifyEliminarAccepted, this, &MainWindow::Borrar_DB);

    ui_dialog->setModal(true);
    ui_dialog->exec();
    timer->start(1000);
}



