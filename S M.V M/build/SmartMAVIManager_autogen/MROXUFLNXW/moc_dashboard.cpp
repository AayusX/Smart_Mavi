/****************************************************************************
** Meta object code from reading C++ file 'dashboard.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/widgets/dashboard.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dashboard.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_StatCard_t {
    uint offsetsAndSizes[10];
    char stringdata0[9];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_StatCard_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_StatCard_t qt_meta_stringdata_StatCard = {
    {
        QT_MOC_LITERAL(0, 8),  // "StatCard"
        QT_MOC_LITERAL(9, 12),  // "valueChanged"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 5),  // "value"
        QT_MOC_LITERAL(29, 7)   // "clicked"
    },
    "StatCard",
    "valueChanged",
    "",
    "value",
    "clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_StatCard[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    2 /* Public */,
       4,    0,   29,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::Int, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject StatCard::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_StatCard.offsetsAndSizes,
    qt_meta_data_StatCard,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_StatCard_t,
        // property 'value'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<StatCard, std::true_type>,
        // method 'valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void StatCard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StatCard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StatCard::*)(int );
            if (_t _q_method = &StatCard::valueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StatCard::*)();
            if (_t _q_method = &StatCard::clicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<StatCard *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->value(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<StatCard *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setValue(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *StatCard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatCard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StatCard.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int StatCard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void StatCard::valueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StatCard::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
namespace {
struct qt_meta_stringdata_QuickActionCard_t {
    uint offsetsAndSizes[6];
    char stringdata0[16];
    char stringdata1[16];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QuickActionCard_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QuickActionCard_t qt_meta_stringdata_QuickActionCard = {
    {
        QT_MOC_LITERAL(0, 15),  // "QuickActionCard"
        QT_MOC_LITERAL(16, 15),  // "actionTriggered"
        QT_MOC_LITERAL(32, 0)   // ""
    },
    "QuickActionCard",
    "actionTriggered",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QuickActionCard[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QuickActionCard::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_QuickActionCard.offsetsAndSizes,
    qt_meta_data_QuickActionCard,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QuickActionCard_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QuickActionCard, std::true_type>,
        // method 'actionTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QuickActionCard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QuickActionCard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->actionTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QuickActionCard::*)();
            if (_t _q_method = &QuickActionCard::actionTriggered; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *QuickActionCard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuickActionCard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuickActionCard.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int QuickActionCard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QuickActionCard::actionTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_stringdata_NotificationWidget_t {
    uint offsetsAndSizes[6];
    char stringdata0[19];
    char stringdata1[9];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NotificationWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NotificationWidget_t qt_meta_stringdata_NotificationWidget = {
    {
        QT_MOC_LITERAL(0, 18),  // "NotificationWidget"
        QT_MOC_LITERAL(19, 8),  // "autoHide"
        QT_MOC_LITERAL(28, 0)   // ""
    },
    "NotificationWidget",
    "autoHide",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NotificationWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject NotificationWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_NotificationWidget.offsetsAndSizes,
    qt_meta_data_NotificationWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NotificationWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NotificationWidget, std::true_type>,
        // method 'autoHide'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void NotificationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NotificationWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->autoHide(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *NotificationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotificationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NotificationWidget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int NotificationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_Dashboard_t {
    uint offsetsAndSizes[34];
    char stringdata0[10];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[18];
    char stringdata5[24];
    char stringdata6[21];
    char stringdata7[22];
    char stringdata8[15];
    char stringdata9[6];
    char stringdata10[16];
    char stringdata11[5];
    char stringdata12[18];
    char stringdata13[23];
    char stringdata14[20];
    char stringdata15[21];
    char stringdata16[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Dashboard_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Dashboard_t qt_meta_stringdata_Dashboard = {
    {
        QT_MOC_LITERAL(0, 9),  // "Dashboard"
        QT_MOC_LITERAL(10, 19),  // "addTeacherRequested"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 19),  // "addStudentRequested"
        QT_MOC_LITERAL(51, 17),  // "addClassRequested"
        QT_MOC_LITERAL(69, 23),  // "markAttendanceRequested"
        QT_MOC_LITERAL(93, 20),  // "viewReportsRequested"
        QT_MOC_LITERAL(114, 21),  // "openSettingsRequested"
        QT_MOC_LITERAL(136, 14),  // "onThemeChanged"
        QT_MOC_LITERAL(151, 5),  // "theme"
        QT_MOC_LITERAL(157, 15),  // "onWindowResized"
        QT_MOC_LITERAL(173, 4),  // "size"
        QT_MOC_LITERAL(178, 17),  // "refreshStatistics"
        QT_MOC_LITERAL(196, 22),  // "onQuickActionTriggered"
        QT_MOC_LITERAL(219, 19),  // "showAttendanceChart"
        QT_MOC_LITERAL(239, 20),  // "showPerformanceChart"
        QT_MOC_LITERAL(260, 14)   // "showTrendChart"
    },
    "Dashboard",
    "addTeacherRequested",
    "",
    "addStudentRequested",
    "addClassRequested",
    "markAttendanceRequested",
    "viewReportsRequested",
    "openSettingsRequested",
    "onThemeChanged",
    "theme",
    "onWindowResized",
    "size",
    "refreshStatistics",
    "onQuickActionTriggered",
    "showAttendanceChart",
    "showPerformanceChart",
    "showTrendChart"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Dashboard[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,
       3,    0,   93,    2, 0x06,    2 /* Public */,
       4,    0,   94,    2, 0x06,    3 /* Public */,
       5,    0,   95,    2, 0x06,    4 /* Public */,
       6,    0,   96,    2, 0x06,    5 /* Public */,
       7,    0,   97,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   98,    2, 0x0a,    7 /* Public */,
      10,    1,  101,    2, 0x0a,    9 /* Public */,
      12,    0,  104,    2, 0x08,   11 /* Private */,
      13,    0,  105,    2, 0x08,   12 /* Private */,
      14,    0,  106,    2, 0x08,   13 /* Private */,
      15,    0,  107,    2, 0x08,   14 /* Private */,
      16,    0,  108,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QSize,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Dashboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Dashboard.offsetsAndSizes,
    qt_meta_data_Dashboard,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Dashboard_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Dashboard, std::true_type>,
        // method 'addTeacherRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addStudentRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addClassRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'markAttendanceRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'viewReportsRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openSettingsRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onThemeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onWindowResized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSize &, std::false_type>,
        // method 'refreshStatistics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onQuickActionTriggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showAttendanceChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showPerformanceChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showTrendChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Dashboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dashboard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addTeacherRequested(); break;
        case 1: _t->addStudentRequested(); break;
        case 2: _t->addClassRequested(); break;
        case 3: _t->markAttendanceRequested(); break;
        case 4: _t->viewReportsRequested(); break;
        case 5: _t->openSettingsRequested(); break;
        case 6: _t->onThemeChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onWindowResized((*reinterpret_cast< std::add_pointer_t<QSize>>(_a[1]))); break;
        case 8: _t->refreshStatistics(); break;
        case 9: _t->onQuickActionTriggered(); break;
        case 10: _t->showAttendanceChart(); break;
        case 11: _t->showPerformanceChart(); break;
        case 12: _t->showTrendChart(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dashboard::*)();
            if (_t _q_method = &Dashboard::addTeacherRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dashboard::*)();
            if (_t _q_method = &Dashboard::addStudentRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Dashboard::*)();
            if (_t _q_method = &Dashboard::addClassRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Dashboard::*)();
            if (_t _q_method = &Dashboard::markAttendanceRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Dashboard::*)();
            if (_t _q_method = &Dashboard::viewReportsRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Dashboard::*)();
            if (_t _q_method = &Dashboard::openSettingsRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *Dashboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dashboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dashboard.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Dashboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Dashboard::addTeacherRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Dashboard::addStudentRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Dashboard::addClassRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Dashboard::markAttendanceRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Dashboard::viewReportsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Dashboard::openSettingsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
namespace {
struct qt_meta_stringdata_DashboardAnimator_t {
    uint offsetsAndSizes[6];
    char stringdata0[18];
    char stringdata1[20];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_DashboardAnimator_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_DashboardAnimator_t qt_meta_stringdata_DashboardAnimator = {
    {
        QT_MOC_LITERAL(0, 17),  // "DashboardAnimator"
        QT_MOC_LITERAL(18, 19),  // "onAnimationFinished"
        QT_MOC_LITERAL(38, 0)   // ""
    },
    "DashboardAnimator",
    "onAnimationFinished",
    ""
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_DashboardAnimator[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject DashboardAnimator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DashboardAnimator.offsetsAndSizes,
    qt_meta_data_DashboardAnimator,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_DashboardAnimator_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DashboardAnimator, std::true_type>,
        // method 'onAnimationFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void DashboardAnimator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DashboardAnimator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onAnimationFinished(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *DashboardAnimator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardAnimator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DashboardAnimator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DashboardAnimator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
