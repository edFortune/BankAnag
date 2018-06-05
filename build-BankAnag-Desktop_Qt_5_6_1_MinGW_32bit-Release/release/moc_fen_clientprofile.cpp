/****************************************************************************
** Meta object code from reading C++ file 'fen_clientprofile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_client/fen_clientProfile/fen_clientprofile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fen_clientprofile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Fen_ClientProfile_t {
    QByteArrayData data[16];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fen_ClientProfile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fen_ClientProfile_t qt_meta_stringdata_Fen_ClientProfile = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Fen_ClientProfile"
QT_MOC_LITERAL(1, 18, 15), // "onTabBarClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 21), // "showDialogFormInscrip"
QT_MOC_LITERAL(4, 57, 15), // "addPicdialogBox"
QT_MOC_LITERAL(5, 73, 19), // "addPicRef_dialogBox"
QT_MOC_LITERAL(6, 93, 20), // "addPicForm_dialogBox"
QT_MOC_LITERAL(7, 114, 8), // "imprimer"
QT_MOC_LITERAL(8, 123, 5), // "print"
QT_MOC_LITERAL(9, 129, 9), // "QPrinter*"
QT_MOC_LITERAL(10, 139, 8), // "chercher"
QT_MOC_LITERAL(11, 148, 7), // "refresh"
QT_MOC_LITERAL(12, 156, 18), // "changePageDocument"
QT_MOC_LITERAL(13, 175, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 192, 23), // "onClicked_addMemoButton"
QT_MOC_LITERAL(15, 216, 23) // "onClicked_effMemoButton"

    },
    "Fen_ClientProfile\0onTabBarClicked\0\0"
    "showDialogFormInscrip\0addPicdialogBox\0"
    "addPicRef_dialogBox\0addPicForm_dialogBox\0"
    "imprimer\0print\0QPrinter*\0chercher\0"
    "refresh\0changePageDocument\0QListWidgetItem*\0"
    "onClicked_addMemoButton\0onClicked_effMemoButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fen_ClientProfile[] = {

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
       1,    1,   74,    2, 0x0a /* Public */,
       3,    0,   77,    2, 0x0a /* Public */,
       4,    0,   78,    2, 0x0a /* Public */,
       5,    0,   79,    2, 0x0a /* Public */,
       6,    0,   80,    2, 0x0a /* Public */,
       7,    0,   81,    2, 0x0a /* Public */,
       8,    1,   82,    2, 0x0a /* Public */,
      10,    0,   85,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x0a /* Public */,
      12,    2,   87,    2, 0x0a /* Public */,
      14,    0,   92,    2, 0x0a /* Public */,
      15,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Fen_ClientProfile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fen_ClientProfile *_t = static_cast<Fen_ClientProfile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTabBarClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->showDialogFormInscrip(); break;
        case 2: _t->addPicdialogBox(); break;
        case 3: _t->addPicRef_dialogBox(); break;
        case 4: _t->addPicForm_dialogBox(); break;
        case 5: _t->imprimer(); break;
        case 6: _t->print((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 7: _t->chercher(); break;
        case 8: _t->refresh(); break;
        case 9: _t->changePageDocument((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 10: _t->onClicked_addMemoButton(); break;
        case 11: _t->onClicked_effMemoButton(); break;
        default: ;
        }
    }
}

const QMetaObject Fen_ClientProfile::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Fen_ClientProfile.data,
      qt_meta_data_Fen_ClientProfile,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Fen_ClientProfile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fen_ClientProfile::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Fen_ClientProfile.stringdata0))
        return static_cast<void*>(const_cast< Fen_ClientProfile*>(this));
    return QWidget::qt_metacast(_clname);
}

int Fen_ClientProfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
