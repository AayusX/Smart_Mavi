/****************************************************************************
** Meta object code from reading C++ file 'surveydialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "include/surveydialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'surveydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SurveyDialog_t {
    QByteArrayData data[14];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SurveyDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SurveyDialog_t qt_meta_stringdata_SurveyDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SurveyDialog"
QT_MOC_LITERAL(1, 13, 8), // "nextPage"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "previousPage"
QT_MOC_LITERAL(4, 36, 10), // "addTeacher"
QT_MOC_LITERAL(5, 47, 10), // "addSubject"
QT_MOC_LITERAL(6, 58, 8), // "addClass"
QT_MOC_LITERAL(7, 67, 21), // "removeSelectedTeacher"
QT_MOC_LITERAL(8, 89, 21), // "removeSelectedSubject"
QT_MOC_LITERAL(9, 111, 19), // "removeSelectedClass"
QT_MOC_LITERAL(10, 131, 25), // "onTeacherSelectionChanged"
QT_MOC_LITERAL(11, 157, 19), // "addSubjectToTeacher"
QT_MOC_LITERAL(12, 177, 24), // "removeSubjectFromTeacher"
QT_MOC_LITERAL(13, 202, 12) // "finishSurvey"

    },
    "SurveyDialog\0nextPage\0\0previousPage\0"
    "addTeacher\0addSubject\0addClass\0"
    "removeSelectedTeacher\0removeSelectedSubject\0"
    "removeSelectedClass\0onTeacherSelectionChanged\0"
    "addSubjectToTeacher\0removeSubjectFromTeacher\0"
    "finishSurvey"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SurveyDialog[] = {

 // content:
       8,       // revision
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
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SurveyDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SurveyDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->nextPage(); break;
        case 1: _t->previousPage(); break;
        case 2: _t->addTeacher(); break;
        case 3: _t->addSubject(); break;
        case 4: _t->addClass(); break;
        case 5: _t->removeSelectedTeacher(); break;
        case 6: _t->removeSelectedSubject(); break;
        case 7: _t->removeSelectedClass(); break;
        case 8: _t->onTeacherSelectionChanged(); break;
        case 9: _t->addSubjectToTeacher(); break;
        case 10: _t->removeSubjectFromTeacher(); break;
        case 11: _t->finishSurvey(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SurveyDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_SurveyDialog.data,
    qt_meta_data_SurveyDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SurveyDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SurveyDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SurveyDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SurveyDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
