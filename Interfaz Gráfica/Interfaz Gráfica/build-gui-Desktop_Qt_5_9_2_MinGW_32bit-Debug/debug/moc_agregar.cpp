/****************************************************************************
** Meta object code from reading C++ file 'agregar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/agregar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agregar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Agregar_t {
    QByteArrayData data[13];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Agregar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Agregar_t qt_meta_stringdata_Agregar = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Agregar"
QT_MOC_LITERAL(1, 8, 21), // "notifyAgregarAccepted"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 2), // "id"
QT_MOC_LITERAL(4, 34, 6), // "nombre"
QT_MOC_LITERAL(5, 41, 8), // "apellido"
QT_MOC_LITERAL(6, 50, 7), // "tarjeta"
QT_MOC_LITERAL(7, 58, 15), // "Tarjeta_a_texto"
QT_MOC_LITERAL(8, 74, 13), // "ENVIAR_DATOS_"
QT_MOC_LITERAL(9, 88, 5), // "datos"
QT_MOC_LITERAL(10, 94, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(11, 116, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(12, 138, 21) // "on_pushButton_clicked"

    },
    "Agregar\0notifyAgregarAccepted\0\0id\0"
    "nombre\0apellido\0tarjeta\0Tarjeta_a_texto\0"
    "ENVIAR_DATOS_\0datos\0on_buttonBox_accepted\0"
    "on_buttonBox_rejected\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Agregar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   44,    2, 0x06 /* Public */,
       7,    1,   53,    2, 0x06 /* Public */,
       8,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   59,    2, 0x08 /* Private */,
      11,    0,   60,    2, 0x08 /* Private */,
      12,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::QString, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Agregar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Agregar *_t = static_cast<Agregar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notifyAgregarAccepted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 1: _t->Tarjeta_a_texto((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { QString _r = _t->ENVIAR_DATOS_((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->on_buttonBox_accepted(); break;
        case 4: _t->on_buttonBox_rejected(); break;
        case 5: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Agregar::*_t)(const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Agregar::notifyAgregarAccepted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Agregar::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Agregar::Tarjeta_a_texto)) {
                *result = 1;
                return;
            }
        }
        {
            typedef QString (Agregar::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Agregar::ENVIAR_DATOS_)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Agregar::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Agregar.data,
      qt_meta_data_Agregar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Agregar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Agregar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Agregar.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Agregar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Agregar::notifyAgregarAccepted(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Agregar::Tarjeta_a_texto(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
QString Agregar::ENVIAR_DATOS_(const QString & _t1)
{
    QString _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
