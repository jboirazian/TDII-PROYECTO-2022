/********************************************************************************
** Form generated from reading UI file 'agregar.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGREGAR_H
#define UI_AGREGAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Agregar
{
public:
    QFormLayout *formLayout;
    QLabel *lbID;
    QLineEdit *leID;
    QLabel *lbNombre;
    QLineEdit *leNombre;
    QLabel *lbApellido;
    QLineEdit *leApellido;
    QLabel *lbTarjetaID;
    QLineEdit *leTarjetaID;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton;

    void setupUi(QDialog *Agregar)
    {
        if (Agregar->objectName().isEmpty())
            Agregar->setObjectName(QStringLiteral("Agregar"));
        Agregar->setEnabled(true);
        Agregar->resize(362, 184);
        formLayout = new QFormLayout(Agregar);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        lbID = new QLabel(Agregar);
        lbID->setObjectName(QStringLiteral("lbID"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lbID);

        leID = new QLineEdit(Agregar);
        leID->setObjectName(QStringLiteral("leID"));
        leID->setEnabled(true);
        leID->setReadOnly(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, leID);

        lbNombre = new QLabel(Agregar);
        lbNombre->setObjectName(QStringLiteral("lbNombre"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lbNombre);

        leNombre = new QLineEdit(Agregar);
        leNombre->setObjectName(QStringLiteral("leNombre"));

        formLayout->setWidget(1, QFormLayout::FieldRole, leNombre);

        lbApellido = new QLabel(Agregar);
        lbApellido->setObjectName(QStringLiteral("lbApellido"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lbApellido);

        leApellido = new QLineEdit(Agregar);
        leApellido->setObjectName(QStringLiteral("leApellido"));

        formLayout->setWidget(2, QFormLayout::FieldRole, leApellido);

        lbTarjetaID = new QLabel(Agregar);
        lbTarjetaID->setObjectName(QStringLiteral("lbTarjetaID"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lbTarjetaID);

        leTarjetaID = new QLineEdit(Agregar);
        leTarjetaID->setObjectName(QStringLiteral("leTarjetaID"));
        leTarjetaID->setEnabled(false);
        leTarjetaID->setReadOnly(false);

        formLayout->setWidget(3, QFormLayout::FieldRole, leTarjetaID);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::FieldRole, verticalSpacer);

        buttonBox = new QDialogButtonBox(Agregar);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(false);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(5, QFormLayout::FieldRole, buttonBox);

        pushButton = new QPushButton(Agregar);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(4, QFormLayout::LabelRole, pushButton);


        retranslateUi(Agregar);
        QObject::connect(buttonBox, SIGNAL(accepted()), Agregar, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Agregar, SLOT(reject()));
        QObject::connect(pushButton, SIGNAL(clicked(bool)), buttonBox, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(Agregar);
    } // setupUi

    void retranslateUi(QDialog *Agregar)
    {
        Agregar->setWindowTitle(QApplication::translate("Agregar", "Dialog", Q_NULLPTR));
        lbID->setText(QApplication::translate("Agregar", "ID", Q_NULLPTR));
        lbNombre->setText(QApplication::translate("Agregar", "Nombre", Q_NULLPTR));
        lbApellido->setText(QApplication::translate("Agregar", "Apellido", Q_NULLPTR));
        lbTarjetaID->setText(QApplication::translate("Agregar", "Tarjeta ID", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Agregar", "GET TARJETA ID", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Agregar: public Ui_Agregar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGREGAR_H
