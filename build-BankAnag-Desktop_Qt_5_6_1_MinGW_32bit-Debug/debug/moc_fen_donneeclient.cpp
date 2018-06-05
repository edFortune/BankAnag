/****************************************************************************
** Meta object code from reading C++ file 'fen_donneeclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_client/fen_donneeclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fen_donneeclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Fen_DonneeClient_t {
    QByteArrayData data[7];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fen_DonneeClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fen_DonneeClient_t qt_meta_stringdata_Fen_DonneeClient = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Fen_DonneeClient"
QT_MOC_LITERAL(1, 17, 7), // "getData"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "modifierData"
QT_MOC_LITERAL(4, 39, 15), // "addPicdialogBox"
QT_MOC_LITERAL(5, 55, 19), // "addPicRef_dialogBox"
QT_MOC_LITERAL(6, 75, 27) // "addPicFormInscrip_dialogBox"

    },
    "Fen_DonneeClient\0getData\0\0modifierData\0"
    "addPicdialogBox\0addPicRef_dialogBox\0"
    "addPicFormInscrip_dialogBox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fen_DonneeClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Fen_DonneeClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fen_DonneeClient *_t = static_cast<Fen_DonneeClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getData(); break;
        case 1: _t->modifierData(); break;
        case 2: _t->addPicdialogBox(); break;
        case 3: _t->addPicRef_dialogBox(); break;
        case 4: _t->addPicFormInscrip_dialogBox(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Fen_DonneeClient::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Fen_DonneeClient.data,
      qt_meta_data_Fen_DonneeClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Fen_DonneeClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fen_DonneeClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Fen_DonneeClient.stringdata0))
        return static_cast<void*>(const_cast< Fen_DonneeClient*>(this));
    return QWidget::qt_metacast(_clname);
}

int Fen_DonneeClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
