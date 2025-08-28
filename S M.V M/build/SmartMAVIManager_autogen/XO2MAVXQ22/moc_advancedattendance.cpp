/****************************************************************************
** Meta object code from reading C++ file 'advancedattendance.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/attendance/advancedattendance.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'advancedattendance.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_AdvancedAttendance_t {
    uint offsetsAndSizes[26];
    char stringdata0[19];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[14];
    char stringdata6[8];
    char stringdata7[16];
    char stringdata8[6];
    char stringdata9[8];
    char stringdata10[22];
    char stringdata11[21];
    char stringdata12[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AdvancedAttendance_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_AdvancedAttendance_t qt_meta_stringdata_AdvancedAttendance = {
    {
        QT_MOC_LITERAL(0, 18),  // "AdvancedAttendance"
        QT_MOC_LITERAL(19, 16),  // "attendanceMarked"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 11),  // "studentRoll"
        QT_MOC_LITERAL(49, 6),  // "status"
        QT_MOC_LITERAL(56, 13),  // "timeOutMarked"
        QT_MOC_LITERAL(70, 7),  // "timeOut"
        QT_MOC_LITERAL(78, 15),  // "reportGenerated"
        QT_MOC_LITERAL(94, 5),  // "grade"
        QT_MOC_LITERAL(100, 7),  // "section"
        QT_MOC_LITERAL(108, 21),  // "leaveRequestSubmitted"
        QT_MOC_LITERAL(130, 20),  // "leaveRequestApproved"
        QT_MOC_LITERAL(151, 9)   // "requestId"
    },
    "AdvancedAttendance",
    "attendanceMarked",
    "",
    "studentRoll",
    "status",
    "timeOutMarked",
    "timeOut",
    "reportGenerated",
    "grade",
    "section",
    "leaveRequestSubmitted",
    "leaveRequestApproved",
    "requestId"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_AdvancedAttendance[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   44,    2, 0x06,    1 /* Public */,
       5,    2,   49,    2, 0x06,    4 /* Public */,
       7,    2,   54,    2, 0x06,    7 /* Public */,
      10,    1,   59,    2, 0x06,   10 /* Public */,
      11,    1,   62,    2, 0x06,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QTime,    3,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject AdvancedAttendance::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AdvancedAttendance.offsetsAndSizes,
    qt_meta_data_AdvancedAttendance,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_AdvancedAttendance_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AdvancedAttendance, std::true_type>,
        // method 'attendanceMarked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'timeOutMarked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QTime &, std::false_type>,
        // method 'reportGenerated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'leaveRequestSubmitted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'leaveRequestApproved'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void AdvancedAttendance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AdvancedAttendance *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->attendanceMarked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->timeOutMarked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTime>>(_a[2]))); break;
        case 2: _t->reportGenerated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->leaveRequestSubmitted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->leaveRequestApproved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AdvancedAttendance::*)(const QString & , const QString & );
            if (_t _q_method = &AdvancedAttendance::attendanceMarked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AdvancedAttendance::*)(const QString & , const QTime & );
            if (_t _q_method = &AdvancedAttendance::timeOutMarked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AdvancedAttendance::*)(const QString & , const QString & );
            if (_t _q_method = &AdvancedAttendance::reportGenerated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AdvancedAttendance::*)(const QString & );
            if (_t _q_method = &AdvancedAttendance::leaveRequestSubmitted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AdvancedAttendance::*)(int );
            if (_t _q_method = &AdvancedAttendance::leaveRequestApproved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *AdvancedAttendance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AdvancedAttendance::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AdvancedAttendance.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AdvancedAttendance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AdvancedAttendance::attendanceMarked(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AdvancedAttendance::timeOutMarked(const QString & _t1, const QTime & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AdvancedAttendance::reportGenerated(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AdvancedAttendance::leaveRequestSubmitted(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AdvancedAttendance::leaveRequestApproved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
