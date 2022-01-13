#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:
void notifyEliminarAccepted(int ID);

private slots:
    void on_buttonBox_2_accepted();


    void on_buttonBox_2_rejected();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
