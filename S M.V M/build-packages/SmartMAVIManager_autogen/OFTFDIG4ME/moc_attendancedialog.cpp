/****************************************************************************
** Meta object code from reading C++ file 'attendancedialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/dialogs/attendancedialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attendancedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_AttendanceDialog_t {
    uint offsetsAndSizes[20];
    char stringdata0[17];
    char stringdata1[7];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[14];
    char stringdata5[13];
    char stringdata6[23];
    char stringdata7[4];
    char stringdata8[7];
    char stringdata9[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AttendanceDialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_AttendanceDialog_t qt_meta_stringdata_AttendanceDialog = {
    {
        QT_MOC_LITERAL(0, 16),  // "AttendanceDialog"
        QT_MOC_LITERAL(17, 6),  // "accept"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 14),  // "markAllPresent"
        QT_MOC_LITERAL(40, 13),  // "markAllAbsent"
        QT_MOC_LITERAL(54, 12),  // "markAllLeave"
        QT_MOC_LITERAL(67, 22),  // "onStudentStatusChanged"
        QT_MOC_LITERAL(90, 3),  // "row"
        QT_MOC_LITERAL(94, 6),  // "column"
        QT_MOC_LITERAL(101, 14)   // "saveAttendance"
    },
    "AttendanceDialog",
    "accept",
    "",
    "markAllPresent",
    "markAllAbsent",
    "markAllLeave",
    "onStudentStatusChanged",
    "row",
    "column",
    "saveAttendance"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_AttendanceDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    2,   54,    2, 0x08,    5 /* Private */,
       9,    0,   59,    2, 0x08,    8 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject AttendanceDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AttendanceDialog.offsetsAndSizes,
    qt_meta_data_AttendanceDialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_AttendanceDialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AttendanceDialog, std::true_type>,
        // method 'accept'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'markAllPresent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'markAllAbsent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'markAllLeave'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStudentStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'saveAttendance'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AttendanceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AttendanceDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->markAllPresent(); break;
        case 2: _t->markAllAbsent(); break;
        case 3: _t->markAllLeave(); break;
        case 4: _t->onStudentStatusChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->saveAttendance(); break;
        default: ;
        }
    }
}

const QMetaObject *AttendanceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AttendanceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AttendanceDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AttendanceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
