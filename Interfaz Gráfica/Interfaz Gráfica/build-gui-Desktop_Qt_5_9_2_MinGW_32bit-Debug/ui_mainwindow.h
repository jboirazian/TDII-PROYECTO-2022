/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionInformaci_n;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tHistorial;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *twHistorial;
    QWidget *tBaseDeDatos;
    QHBoxLayout *horizontalLayout;
    QTableWidget *twBaseDeDatos;
    QGroupBox *gbPushBottons;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pbAgregar;
    QPushButton *pbEliminar;
    QPushButton *Conectar_Bt;
    QMenuBar *menubar;
    QMenu *menuAccess_Control;
    QMenu *menuAyuda;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(745, 457);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMouseTracking(false);
        actionInformaci_n = new QAction(MainWindow);
        actionInformaci_n->setObjectName(QStringLiteral("actionInformaci_n"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(false);
        tHistorial = new QWidget();
        tHistorial->setObjectName(QStringLiteral("tHistorial"));
        horizontalLayout_2 = new QHBoxLayout(tHistorial);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        twHistorial = new QTableWidget(tHistorial);
        if (twHistorial->columnCount() < 7)
            twHistorial->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twHistorial->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        twHistorial->setObjectName(QStringLiteral("twHistorial"));

        horizontalLayout_2->addWidget(twHistorial);

        tabWidget->addTab(tHistorial, QString());
        tBaseDeDatos = new QWidget();
        tBaseDeDatos->setObjectName(QStringLiteral("tBaseDeDatos"));
        horizontalLayout = new QHBoxLayout(tBaseDeDatos);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        twBaseDeDatos = new QTableWidget(tBaseDeDatos);
        if (twBaseDeDatos->columnCount() < 5)
            twBaseDeDatos->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        twBaseDeDatos->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        twBaseDeDatos->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        twBaseDeDatos->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        twBaseDeDatos->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        twBaseDeDatos->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        twBaseDeDatos->setObjectName(QStringLiteral("twBaseDeDatos"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twBaseDeDatos->sizePolicy().hasHeightForWidth());
        twBaseDeDatos->setSizePolicy(sizePolicy1);
        twBaseDeDatos->setAutoFillBackground(false);
        twBaseDeDatos->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout->addWidget(twBaseDeDatos);

        gbPushBottons = new QGroupBox(tBaseDeDatos);
        gbPushBottons->setObjectName(QStringLiteral("gbPushBottons"));
        gbPushBottons->setMaximumSize(QSize(496, 16777215));
        gridLayout_2 = new QGridLayout(gbPushBottons);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        pbAgregar = new QPushButton(gbPushBottons);
        pbAgregar->setObjectName(QStringLiteral("pbAgregar"));
        pbAgregar->setEnabled(false);

        gridLayout_2->addWidget(pbAgregar, 1, 0, 1, 1);

        pbEliminar = new QPushButton(gbPushBottons);
        pbEliminar->setObjectName(QStringLiteral("pbEliminar"));
        pbEliminar->setEnabled(false);

        gridLayout_2->addWidget(pbEliminar, 2, 0, 1, 1);

        Conectar_Bt = new QPushButton(gbPushBottons);
        Conectar_Bt->setObjectName(QStringLiteral("Conectar_Bt"));

        gridLayout_2->addWidget(Conectar_Bt, 4, 0, 1, 1);


        horizontalLayout->addWidget(gbPushBottons);

        tabWidget->addTab(tBaseDeDatos, QString());

        horizontalLayout_3->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 745, 21));
        menuAccess_Control = new QMenu(menubar);
        menuAccess_Control->setObjectName(QStringLiteral("menuAccess_Control"));
        menuAyuda = new QMenu(menubar);
        menuAyuda->setObjectName(QStringLiteral("menuAyuda"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuAccess_Control->menuAction());
        menubar->addAction(menuAyuda->menuAction());
        menuAyuda->addAction(actionInformaci_n);

        retranslateUi(MainWindow);
        QObject::connect(Conectar_Bt, SIGNAL(clicked(bool)), pbEliminar, SLOT(setDisabled(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionInformaci_n->setText(QApplication::translate("MainWindow", "Informaci\303\263n", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = twHistorial->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "#Op", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = twHistorial->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Fecha", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = twHistorial->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Hora", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = twHistorial->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Estado", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = twHistorial->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Num Tarjeta", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = twHistorial->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Nombre", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = twHistorial->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Apellido", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tHistorial), QApplication::translate("MainWindow", "Historial", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = twBaseDeDatos->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = twBaseDeDatos->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Nombre", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = twBaseDeDatos->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Apellido", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = twBaseDeDatos->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Num Tarjeta", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = twBaseDeDatos->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "Estado", Q_NULLPTR));
        gbPushBottons->setTitle(QString());
        pbAgregar->setText(QApplication::translate("MainWindow", "Agregar", Q_NULLPTR));
        pbEliminar->setText(QApplication::translate("MainWindow", "Eliminar", Q_NULLPTR));
        Conectar_Bt->setText(QApplication::translate("MainWindow", "Conectar", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tBaseDeDatos), QApplication::translate("MainWindow", "Base de Datos", Q_NULLPTR));
        menuAccess_Control->setTitle(QApplication::translate("MainWindow", "Archivo", Q_NULLPTR));
        menuAyuda->setTitle(QApplication::translate("MainWindow", "Ayuda", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
