/****************************************************************************
** Meta object code from reading C++ file 'enhancedstudent.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/models/enhancedstudent.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enhancedstudent.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_StudentProfileWidget_t {
    uint offsetsAndSizes[28];
    char stringdata0[21];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[8];
    char stringdata5[14];
    char stringdata6[16];
    char stringdata7[20];
    char stringdata8[24];
    char stringdata9[14];
    char stringdata10[16];
    char stringdata11[15];
    char stringdata12[16];
    char stringdata13[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_StudentProfileWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_StudentProfileWidget_t qt_meta_stringdata_StudentProfileWidget = {
    {
        QT_MOC_LITERAL(0, 20),  // "StudentProfileWidget"
        QT_MOC_LITERAL(21, 14),  // "studentUpdated"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 15),  // "EnhancedStudent"
        QT_MOC_LITERAL(53, 7),  // "student"
        QT_MOC_LITERAL(61, 13),  // "editRequested"
        QT_MOC_LITERAL(75, 15),  // "deleteRequested"
        QT_MOC_LITERAL(91, 19),  // "viewGradesRequested"
        QT_MOC_LITERAL(111, 23),  // "viewAttendanceRequested"
        QT_MOC_LITERAL(135, 13),  // "onEditClicked"
        QT_MOC_LITERAL(149, 15),  // "onDeleteClicked"
        QT_MOC_LITERAL(165, 14),  // "onPhotoClicked"
        QT_MOC_LITERAL(180, 15),  // "onGradesClicked"
        QT_MOC_LITERAL(196, 19)   // "onAttendanceClicked"
    },
    "StudentProfileWidget",
    "studentUpdated",
    "",
    "EnhancedStudent",
    "student",
    "editRequested",
    "deleteRequested",
    "viewGradesRequested",
    "viewAttendanceRequested",
    "onEditClicked",
    "onDeleteClicked",
    "onPhotoClicked",
    "onGradesClicked",
    "onAttendanceClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_StudentProfileWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       5,    0,   77,    2, 0x06,    3 /* Public */,
       6,    0,   78,    2, 0x06,    4 /* Public */,
       7,    0,   79,    2, 0x06,    5 /* Public */,
       8,    0,   80,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   81,    2, 0x08,    7 /* Private */,
      10,    0,   82,    2, 0x08,    8 /* Private */,
      11,    0,   83,    2, 0x08,    9 /* Private */,
      12,    0,   84,    2, 0x08,   10 /* Private */,
      13,    0,   85,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject StudentProfileWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_StudentProfileWidget.offsetsAndSizes,
    qt_meta_data_StudentProfileWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_StudentProfileWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<StudentProfileWidget, std::true_type>,
        // method 'studentUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const EnhancedStudent &, std::false_type>,
        // method 'editRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'viewGradesRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'viewAttendanceRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPhotoClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGradesClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAttendanceClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void StudentProfileWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StudentProfileWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->studentUpdated((*reinterpret_cast< std::add_pointer_t<EnhancedStudent>>(_a[1]))); break;
        case 1: _t->editRequested(); break;
        case 2: _t->deleteRequested(); break;
        case 3: _t->viewGradesRequested(); break;
        case 4: _t->viewAttendanceRequested(); break;
        case 5: _t->onEditClicked(); break;
        case 6: _t->onDeleteClicked(); break;
        case 7: _t->onPhotoClicked(); break;
        case 8: _t->onGradesClicked(); break;
        case 9: _t->onAttendanceClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StudentProfileWidget::*)(const EnhancedStudent & );
            if (_t _q_method = &StudentProfileWidget::studentUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StudentProfileWidget::*)();
            if (_t _q_method = &StudentProfileWidget::editRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StudentProfileWidget::*)();
            if (_t _q_method = &StudentProfileWidget::deleteRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StudentProfileWidget::*)();
            if (_t _q_method = &StudentProfileWidget::viewGradesRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StudentProfileWidget::*)();
            if (_t _q_method = &StudentProfileWidget::viewAttendanceRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *StudentProfileWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StudentProfileWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StudentProfileWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int StudentProfileWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void StudentProfileWidget::studentUpdated(const EnhancedStudent & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StudentProfileWidget::editRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StudentProfileWidget::deleteRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void StudentProfileWidget::viewGradesRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void StudentProfileWidget::viewAttendanceRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
