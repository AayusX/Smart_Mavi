/****************************************************************************
** Meta object code from reading C++ file 'communicationmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/communication/communicationmanager.h"
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'communicationmanager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CommunicationManager_t {
    uint offsetsAndSizes[52];
    char stringdata0[21];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[8];
    char stringdata5[8];
    char stringdata6[17];
    char stringdata7[20];
    char stringdata8[13];
    char stringdata9[21];
    char stringdata10[25];
    char stringdata11[26];
    char stringdata12[17];
    char stringdata13[18];
    char stringdata14[23];
    char stringdata15[10];
    char stringdata16[15];
    char stringdata17[15];
    char stringdata18[8];
    char stringdata19[6];
    char stringdata20[16];
    char stringdata21[8];
    char stringdata22[5];
    char stringdata23[15];
    char stringdata24[20];
    char stringdata25[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CommunicationManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CommunicationManager_t qt_meta_stringdata_CommunicationManager = {
    {
        QT_MOC_LITERAL(0, 20),  // "CommunicationManager"
        QT_MOC_LITERAL(21, 9),  // "emailSent"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 9),  // "messageId"
        QT_MOC_LITERAL(42, 7),  // "success"
        QT_MOC_LITERAL(50, 7),  // "smsSent"
        QT_MOC_LITERAL(58, 16),  // "notificationSent"
        QT_MOC_LITERAL(75, 19),  // "messageQueueUpdated"
        QT_MOC_LITERAL(95, 12),  // "pendingCount"
        QT_MOC_LITERAL(108, 20),  // "configurationChanged"
        QT_MOC_LITERAL(129, 24),  // "processScheduledMessages"
        QT_MOC_LITERAL(154, 25),  // "sendDailyAttendanceReport"
        QT_MOC_LITERAL(180, 16),  // "sendWeeklyReport"
        QT_MOC_LITERAL(197, 17),  // "sendMonthlyReport"
        QT_MOC_LITERAL(215, 22),  // "sendLowAttendanceAlert"
        QT_MOC_LITERAL(238, 9),  // "studentId"
        QT_MOC_LITERAL(248, 14),  // "attendanceRate"
        QT_MOC_LITERAL(263, 14),  // "sendGradeAlert"
        QT_MOC_LITERAL(278, 7),  // "subject"
        QT_MOC_LITERAL(286, 5),  // "grade"
        QT_MOC_LITERAL(292, 15),  // "sendParentAlert"
        QT_MOC_LITERAL(308, 7),  // "message"
        QT_MOC_LITERAL(316, 4),  // "type"
        QT_MOC_LITERAL(321, 14),  // "onNetworkReply"
        QT_MOC_LITERAL(336, 19),  // "processMessageQueue"
        QT_MOC_LITERAL(356, 23)   // "onScheduledMessageTimer"
    },
    "CommunicationManager",
    "emailSent",
    "",
    "messageId",
    "success",
    "smsSent",
    "notificationSent",
    "messageQueueUpdated",
    "pendingCount",
    "configurationChanged",
    "processScheduledMessages",
    "sendDailyAttendanceReport",
    "sendWeeklyReport",
    "sendMonthlyReport",
    "sendLowAttendanceAlert",
    "studentId",
    "attendanceRate",
    "sendGradeAlert",
    "subject",
    "grade",
    "sendParentAlert",
    "message",
    "type",
    "onNetworkReply",
    "processMessageQueue",
    "onScheduledMessageTimer"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CommunicationManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  110,    2, 0x06,    1 /* Public */,
       5,    2,  115,    2, 0x06,    4 /* Public */,
       6,    1,  120,    2, 0x06,    7 /* Public */,
       7,    1,  123,    2, 0x06,    9 /* Public */,
       9,    0,  126,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,  127,    2, 0x0a,   12 /* Public */,
      11,    0,  128,    2, 0x0a,   13 /* Public */,
      12,    0,  129,    2, 0x0a,   14 /* Public */,
      13,    0,  130,    2, 0x0a,   15 /* Public */,
      14,    2,  131,    2, 0x0a,   16 /* Public */,
      17,    3,  136,    2, 0x0a,   19 /* Public */,
      20,    3,  143,    2, 0x0a,   23 /* Public */,
      20,    2,  150,    2, 0x2a,   27 /* Public | MethodCloned */,
      23,    0,  155,    2, 0x08,   30 /* Private */,
      24,    0,  156,    2, 0x08,   31 /* Private */,
      25,    0,  157,    2, 0x08,   32 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Double,   15,   18,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   15,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   15,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CommunicationManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CommunicationManager.offsetsAndSizes,
    qt_meta_data_CommunicationManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CommunicationManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CommunicationManager, std::true_type>,
        // method 'emailSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'smsSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'notificationSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'messageQueueUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'configurationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processScheduledMessages'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendDailyAttendanceReport'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendWeeklyReport'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendMonthlyReport'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendLowAttendanceAlert'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'sendGradeAlert'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'sendParentAlert'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sendParentAlert'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onNetworkReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processMessageQueue'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onScheduledMessageTimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CommunicationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommunicationManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->emailSent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 1: _t->smsSent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 2: _t->notificationSent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->messageQueueUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->configurationChanged(); break;
        case 5: _t->processScheduledMessages(); break;
        case 6: _t->sendDailyAttendanceReport(); break;
        case 7: _t->sendWeeklyReport(); break;
        case 8: _t->sendMonthlyReport(); break;
        case 9: _t->sendLowAttendanceAlert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 10: _t->sendGradeAlert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 11: _t->sendParentAlert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 12: _t->sendParentAlert((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->onNetworkReply(); break;
        case 14: _t->processMessageQueue(); break;
        case 15: _t->onScheduledMessageTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CommunicationManager::*)(const QString & , bool );
            if (_t _q_method = &CommunicationManager::emailSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CommunicationManager::*)(const QString & , bool );
            if (_t _q_method = &CommunicationManager::smsSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CommunicationManager::*)(const QString & );
            if (_t _q_method = &CommunicationManager::notificationSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CommunicationManager::*)(int );
            if (_t _q_method = &CommunicationManager::messageQueueUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CommunicationManager::*)();
            if (_t _q_method = &CommunicationManager::configurationChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *CommunicationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommunicationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommunicationManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CommunicationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void CommunicationManager::emailSent(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CommunicationManager::smsSent(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CommunicationManager::notificationSent(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CommunicationManager::messageQueueUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CommunicationManager::configurationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
namespace {
struct qt_meta_stringdata_CommunicationSettingsDialog_t {
    uint offsetsAndSizes[18];
    char stringdata0[28];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[20];
    char stringdata5[18];
    char stringdata6[13];
    char stringdata7[13];
    char stringdata8[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CommunicationSettingsDialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CommunicationSettingsDialog_t qt_meta_stringdata_CommunicationSettingsDialog = {
    {
        QT_MOC_LITERAL(0, 27),  // "CommunicationSettingsDialog"
        QT_MOC_LITERAL(28, 17),  // "saveEmailSettings"
        QT_MOC_LITERAL(46, 0),  // ""
        QT_MOC_LITERAL(47, 15),  // "saveSMSSettings"
        QT_MOC_LITERAL(63, 19),  // "testEmailConnection"
        QT_MOC_LITERAL(83, 17),  // "testSMSConnection"
        QT_MOC_LITERAL(101, 12),  // "loadTemplate"
        QT_MOC_LITERAL(114, 12),  // "saveTemplate"
        QT_MOC_LITERAL(127, 14)   // "deleteTemplate"
    },
    "CommunicationSettingsDialog",
    "saveEmailSettings",
    "",
    "saveSMSSettings",
    "testEmailConnection",
    "testSMSConnection",
    "loadTemplate",
    "saveTemplate",
    "deleteTemplate"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CommunicationSettingsDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    0,   62,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject CommunicationSettingsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CommunicationSettingsDialog.offsetsAndSizes,
    qt_meta_data_CommunicationSettingsDialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CommunicationSettingsDialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CommunicationSettingsDialog, std::true_type>,
        // method 'saveEmailSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSMSSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'testEmailConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'testSMSConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadTemplate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveTemplate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteTemplate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CommunicationSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommunicationSettingsDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveEmailSettings(); break;
        case 1: _t->saveSMSSettings(); break;
        case 2: _t->testEmailConnection(); break;
        case 3: _t->testSMSConnection(); break;
        case 4: _t->loadTemplate(); break;
        case 5: _t->saveTemplate(); break;
        case 6: _t->deleteTemplate(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *CommunicationSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommunicationSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommunicationSettingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CommunicationSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_ParentPortal_t {
    uint offsetsAndSizes[32];
    char stringdata0[13];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[12];
    char stringdata5[16];
    char stringdata6[8];
    char stringdata7[12];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[13];
    char stringdata11[21];
    char stringdata12[15];
    char stringdata13[18];
    char stringdata14[22];
    char stringdata15[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ParentPortal_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ParentPortal_t qt_meta_stringdata_ParentPortal = {
    {
        QT_MOC_LITERAL(0, 12),  // "ParentPortal"
        QT_MOC_LITERAL(13, 15),  // "loginSuccessful"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 9),  // "studentId"
        QT_MOC_LITERAL(40, 11),  // "loginFailed"
        QT_MOC_LITERAL(52, 15),  // "messageReceived"
        QT_MOC_LITERAL(68, 7),  // "message"
        QT_MOC_LITERAL(76, 11),  // "loginParent"
        QT_MOC_LITERAL(88, 8),  // "username"
        QT_MOC_LITERAL(97, 8),  // "password"
        QT_MOC_LITERAL(106, 12),  // "logoutParent"
        QT_MOC_LITERAL(119, 20),  // "sendMessageToTeacher"
        QT_MOC_LITERAL(140, 14),  // "requestMeeting"
        QT_MOC_LITERAL(155, 17),  // "viewStudentGrades"
        QT_MOC_LITERAL(173, 21),  // "viewStudentAttendance"
        QT_MOC_LITERAL(195, 17)   // "updateContactInfo"
    },
    "ParentPortal",
    "loginSuccessful",
    "",
    "studentId",
    "loginFailed",
    "messageReceived",
    "message",
    "loginParent",
    "username",
    "password",
    "logoutParent",
    "sendMessageToTeacher",
    "requestMeeting",
    "viewStudentGrades",
    "viewStudentAttendance",
    "updateContactInfo"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ParentPortal[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    0,   77,    2, 0x06,    3 /* Public */,
       5,    1,   78,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    2,   81,    2, 0x0a,    6 /* Public */,
      10,    0,   86,    2, 0x0a,    9 /* Public */,
      11,    0,   87,    2, 0x08,   10 /* Private */,
      12,    0,   88,    2, 0x08,   11 /* Private */,
      13,    0,   89,    2, 0x08,   12 /* Private */,
      14,    0,   90,    2, 0x08,   13 /* Private */,
      15,    0,   91,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ParentPortal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ParentPortal.offsetsAndSizes,
    qt_meta_data_ParentPortal,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ParentPortal_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ParentPortal, std::true_type>,
        // method 'loginSuccessful'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'loginFailed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'messageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'loginParent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'logoutParent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendMessageToTeacher'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'requestMeeting'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'viewStudentGrades'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'viewStudentAttendance'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateContactInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ParentPortal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ParentPortal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loginSuccessful((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->loginFailed(); break;
        case 2: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->loginParent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->logoutParent(); break;
        case 5: _t->sendMessageToTeacher(); break;
        case 6: _t->requestMeeting(); break;
        case 7: _t->viewStudentGrades(); break;
        case 8: _t->viewStudentAttendance(); break;
        case 9: _t->updateContactInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ParentPortal::*)(int );
            if (_t _q_method = &ParentPortal::loginSuccessful; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ParentPortal::*)();
            if (_t _q_method = &ParentPortal::loginFailed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ParentPortal::*)(const QString & );
            if (_t _q_method = &ParentPortal::messageReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *ParentPortal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParentPortal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParentPortal.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ParentPortal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ParentPortal::loginSuccessful(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParentPortal::loginFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ParentPortal::messageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
