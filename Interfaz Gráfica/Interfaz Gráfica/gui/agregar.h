#ifndef AGREGAR_H
#define AGREGAR_H

#include "main.h"


namespace Ui {
class Agregar;
}

class Agregar : public QDialog
{
    Q_OBJECT

public:
    explicit Agregar(QWidget *parent = nullptr);

    ~Agregar();

signals:
    void notifyAgregarAccepted(const QString& id, const QString& nombre, const QString& apellido, const QString& tarjeta);
    void Tarjeta_a_texto(const QString& tarjeta);
    QString ENVIAR_DATOS_(const QString& datos);
private:
    Ui::Agregar *ui;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pushButton_clicked();
};

#endif // AGREGAR_H
