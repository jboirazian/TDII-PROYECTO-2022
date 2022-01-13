/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "on_pbAgregar_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "appendTWBaseDeDatos"
QT_MOC_LITERAL(4, 53, 2), // "id"
QT_MOC_LITERAL(5, 56, 6), // "nombre"
QT_MOC_LITERAL(6, 63, 8), // "apellido"
QT_MOC_LITERAL(7, 72, 7), // "tarjeta"
QT_MOC_LITERAL(8, 80, 28), // "on_twBaseDeDatos_itemPressed"
QT_MOC_LITERAL(9, 109, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(10, 127, 4), // "item"
QT_MOC_LITERAL(11, 132, 19), // "on_pbEditar_clicked"
QT_MOC_LITERAL(12, 152, 20), // "on_pbGuardar_clicked"
QT_MOC_LITERAL(13, 173, 22), // "on_Conectar_Bt_clicked"
QT_MOC_LITERAL(14, 196, 9), // "CHECK_USB"
QT_MOC_LITERAL(15, 206, 23), // "on_activar_rfid_clicked"
QT_MOC_LITERAL(16, 230, 27), // "on_Cancelar_lectura_clicked"
QT_MOC_LITERAL(17, 258, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(18, 280, 21), // "on_pbEliminar_clicked"
QT_MOC_LITERAL(19, 302, 9), // "Borrar_DB"
QT_MOC_LITERAL(20, 312, 2) // "ID"

    },
    "MainWindow\0on_pbAgregar_clicked\0\0"
    "appendTWBaseDeDatos\0id\0nombre\0apellido\0"
    "tarjeta\0on_twBaseDeDatos_itemPressed\0"
    "QTableWidgetItem*\0item\0on_pbEditar_clicked\0"
    "on_pbGuardar_clicked\0on_Conectar_Bt_clicked\0"
    "CHECK_USB\0on_activar_rfid_clicked\0"
    "on_Cancelar_lectura_clicked\0"
    "on_pushButton_clicked\0on_pbEliminar_clicked\0"
    "Borrar_DB\0ID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    4,   75,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
      11,    0,   87,    2, 0x08 /* Private */,
      12,    0,   88,    2, 0x08 /* Private */,
      13,    0,   89,    2, 0x08 /* Private */,
      14,    0,   90,    2, 0x08 /* Private */,
      15,    0,   91,    2, 0x08 /* Private */,
      16,    0,   92,    2, 0x08 /* Private */,
      17,    0,   93,    2, 0x08 /* Private */,
      18,    0,   94,    2, 0x08 /* Private */,
      19,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pbAgregar_clicked(); break;
        case 1: _t->appendTWBaseDeDatos((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 2: _t->on_twBaseDeDatos_itemPressed((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->on_pbEditar_clicked(); break;
        case 5: _t->on_Conectar_Bt_clicked(); break;
        case 6: { QString _r = _t->CHECK_USB();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->on_Cancelar_lectura_clicked(); break;
        case 9: _t->on_pushButton_clicked(); break;
        case 10: _t->on_pbEliminar_clicked(); break;
        case 11: _t->Borrar_DB((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
