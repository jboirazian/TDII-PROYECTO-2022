#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
#include "agregar.h"
#include "dialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pbAgregar_clicked();

    void appendTWBaseDeDatos(const QString& id, const QString& nombre, const QString& apellido, const QString& tarjeta);

    void on_twBaseDeDatos_itemPressed(QTableWidgetItem *item);

    void on_pbEditar_clicked();

    void on_pbGuardar_clicked();

    void on_Conectar_Bt_clicked();

     QString CHECK_USB();
    void on_activar_rfid_clicked();

    void on_Cancelar_lectura_clicked();

    void on_pushButton_clicked();

    void on_pbEliminar_clicked();

    void Borrar_DB(int ID);

public slots:

private:
    Ui::MainWindow *ui;

    Agregar *ui_agregar;

    Dialog *ui_dialog;

    void importCSVFileDB();
     void PERSONA_STATUS(int row);
    void importCSVFileH();
    void exportCSVFileH();
};
#endif // MAINWINDOW_H
