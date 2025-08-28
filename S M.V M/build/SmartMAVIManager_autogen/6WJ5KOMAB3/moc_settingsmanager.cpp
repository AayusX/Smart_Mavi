/****************************************************************************
** Meta object code from reading C++ file 'settingsmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/settings/settingsmanager.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsmanager.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_SettingsManager_t {
    uint offsetsAndSizes[24];
    char stringdata0[16];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[16];
    char stringdata5[9];
    char stringdata6[16];
    char stringdata7[16];
    char stringdata8[14];
    char stringdata9[13];
    char stringdata10[13];
    char stringdata11[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SettingsManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SettingsManager_t qt_meta_stringdata_SettingsManager = {
    {
        QT_MOC_LITERAL(0, 15),  // "SettingsManager"
        QT_MOC_LITERAL(16, 12),  // "themeChanged"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 5),  // "theme"
        QT_MOC_LITERAL(36, 15),  // "languageChanged"
        QT_MOC_LITERAL(52, 8),  // "language"
        QT_MOC_LITERAL(61, 15),  // "brandingChanged"
        QT_MOC_LITERAL(77, 15),  // "settingsChanged"
        QT_MOC_LITERAL(93, 13),  // "settingsReset"
        QT_MOC_LITERAL(107, 12),  // "saveSettings"
        QT_MOC_LITERAL(120, 12),  // "loadSettings"
        QT_MOC_LITERAL(133, 14)   // "reloadSettings"
    },
    "SettingsManager",
    "themeChanged",
    "",
    "theme",
    "languageChanged",
    "language",
    "brandingChanged",
    "settingsChanged",
    "settingsReset",
    "saveSettings",
    "loadSettings",
    "reloadSettings"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SettingsManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    1,   65,    2, 0x06,    3 /* Public */,
       6,    0,   68,    2, 0x06,    5 /* Public */,
       7,    0,   69,    2, 0x06,    6 /* Public */,
       8,    0,   70,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   71,    2, 0x0a,    8 /* Public */,
      10,    0,   72,    2, 0x0a,    9 /* Public */,
      11,    0,   73,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingsManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SettingsManager.offsetsAndSizes,
    qt_meta_data_SettingsManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SettingsManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsManager, std::true_type>,
        // method 'themeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'languageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'brandingChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'settingsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'settingsReset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reloadSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SettingsManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->themeChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->languageChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->brandingChanged(); break;
        case 3: _t->settingsChanged(); break;
        case 4: _t->settingsReset(); break;
        case 5: _t->saveSettings(); break;
        case 6: _t->loadSettings(); break;
        case 7: _t->reloadSettings(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsManager::*)(const QString & );
            if (_t _q_method = &SettingsManager::themeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsManager::*)(const QString & );
            if (_t _q_method = &SettingsManager::languageChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsManager::*)();
            if (_t _q_method = &SettingsManager::brandingChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingsManager::*)();
            if (_t _q_method = &SettingsManager::settingsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SettingsManager::*)();
            if (_t _q_method = &SettingsManager::settingsReset; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *SettingsManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SettingsManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SettingsManager::themeChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingsManager::languageChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingsManager::brandingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SettingsManager::settingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SettingsManager::settingsReset()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
namespace {
struct qt_meta_stringdata_SettingsDialog_t {
    uint offsetsAndSizes[46];
    char stringdata0[15];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[14];
    char stringdata5[15];
    char stringdata6[15];
    char stringdata7[15];
    char stringdata8[18];
    char stringdata9[16];
    char stringdata10[18];
    char stringdata11[13];
    char stringdata12[18];
    char stringdata13[21];
    char stringdata14[17];
    char stringdata15[19];
    char stringdata16[21];
    char stringdata17[14];
    char stringdata18[16];
    char stringdata19[16];
    char stringdata20[18];
    char stringdata21[23];
    char stringdata22[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SettingsDialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SettingsDialog_t qt_meta_stringdata_SettingsDialog = {
    {
        QT_MOC_LITERAL(0, 14),  // "SettingsDialog"
        QT_MOC_LITERAL(15, 15),  // "saveAllSettings"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 16),  // "resetAllSettings"
        QT_MOC_LITERAL(49, 13),  // "applySettings"
        QT_MOC_LITERAL(63, 14),  // "importSettings"
        QT_MOC_LITERAL(78, 14),  // "exportSettings"
        QT_MOC_LITERAL(93, 14),  // "onThemeChanged"
        QT_MOC_LITERAL(108, 17),  // "createCustomTheme"
        QT_MOC_LITERAL(126, 15),  // "editCustomTheme"
        QT_MOC_LITERAL(142, 17),  // "deleteCustomTheme"
        QT_MOC_LITERAL(160, 12),  // "previewTheme"
        QT_MOC_LITERAL(173, 17),  // "onLanguageChanged"
        QT_MOC_LITERAL(191, 20),  // "downloadLanguagePack"
        QT_MOC_LITERAL(212, 16),  // "selectSchoolLogo"
        QT_MOC_LITERAL(229, 18),  // "selectPrimaryColor"
        QT_MOC_LITERAL(248, 20),  // "selectSecondaryColor"
        QT_MOC_LITERAL(269, 13),  // "resetBranding"
        QT_MOC_LITERAL(283, 15),  // "previewBranding"
        QT_MOC_LITERAL(299, 15),  // "configureBackup"
        QT_MOC_LITERAL(315, 17),  // "configureSecurity"
        QT_MOC_LITERAL(333, 22),  // "configureNotifications"
        QT_MOC_LITERAL(356, 15)   // "configureSystem"
    },
    "SettingsDialog",
    "saveAllSettings",
    "",
    "resetAllSettings",
    "applySettings",
    "importSettings",
    "exportSettings",
    "onThemeChanged",
    "createCustomTheme",
    "editCustomTheme",
    "deleteCustomTheme",
    "previewTheme",
    "onLanguageChanged",
    "downloadLanguagePack",
    "selectSchoolLogo",
    "selectPrimaryColor",
    "selectSecondaryColor",
    "resetBranding",
    "previewBranding",
    "configureBackup",
    "configureSecurity",
    "configureNotifications",
    "configureSystem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SettingsDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  140,    2, 0x08,    1 /* Private */,
       3,    0,  141,    2, 0x08,    2 /* Private */,
       4,    0,  142,    2, 0x08,    3 /* Private */,
       5,    0,  143,    2, 0x08,    4 /* Private */,
       6,    0,  144,    2, 0x08,    5 /* Private */,
       7,    0,  145,    2, 0x08,    6 /* Private */,
       8,    0,  146,    2, 0x08,    7 /* Private */,
       9,    0,  147,    2, 0x08,    8 /* Private */,
      10,    0,  148,    2, 0x08,    9 /* Private */,
      11,    0,  149,    2, 0x08,   10 /* Private */,
      12,    0,  150,    2, 0x08,   11 /* Private */,
      13,    0,  151,    2, 0x08,   12 /* Private */,
      14,    0,  152,    2, 0x08,   13 /* Private */,
      15,    0,  153,    2, 0x08,   14 /* Private */,
      16,    0,  154,    2, 0x08,   15 /* Private */,
      17,    0,  155,    2, 0x08,   16 /* Private */,
      18,    0,  156,    2, 0x08,   17 /* Private */,
      19,    0,  157,    2, 0x08,   18 /* Private */,
      20,    0,  158,    2, 0x08,   19 /* Private */,
      21,    0,  159,    2, 0x08,   20 /* Private */,
      22,    0,  160,    2, 0x08,   21 /* Private */,

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

Q_CONSTINIT const QMetaObject SettingsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SettingsDialog.offsetsAndSizes,
    qt_meta_data_SettingsDialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SettingsDialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsDialog, std::true_type>,
        // method 'saveAllSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetAllSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applySettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'importSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onThemeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createCustomTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editCustomTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteCustomTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'previewTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onLanguageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'downloadLanguagePack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectSchoolLogo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectPrimaryColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectSecondaryColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetBranding'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'previewBranding'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'configureBackup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'configureSecurity'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'configureNotifications'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'configureSystem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveAllSettings(); break;
        case 1: _t->resetAllSettings(); break;
        case 2: _t->applySettings(); break;
        case 3: _t->importSettings(); break;
        case 4: _t->exportSettings(); break;
        case 5: _t->onThemeChanged(); break;
        case 6: _t->createCustomTheme(); break;
        case 7: _t->editCustomTheme(); break;
        case 8: _t->deleteCustomTheme(); break;
        case 9: _t->previewTheme(); break;
        case 10: _t->onLanguageChanged(); break;
        case 11: _t->downloadLanguagePack(); break;
        case 12: _t->selectSchoolLogo(); break;
        case 13: _t->selectPrimaryColor(); break;
        case 14: _t->selectSecondaryColor(); break;
        case 15: _t->resetBranding(); break;
        case 16: _t->previewBranding(); break;
        case 17: _t->configureBackup(); break;
        case 18: _t->configureSecurity(); break;
        case 19: _t->configureNotifications(); break;
        case 20: _t->configureSystem(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *SettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_ThemeEditor_t {
    uint offsetsAndSizes[24];
    char stringdata0[12];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[8];
    char stringdata5[13];
    char stringdata6[10];
    char stringdata7[13];
    char stringdata8[11];
    char stringdata9[12];
    char stringdata10[12];
    char stringdata11[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ThemeEditor_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ThemeEditor_t qt_meta_stringdata_ThemeEditor = {
    {
        QT_MOC_LITERAL(0, 11),  // "ThemeEditor"
        QT_MOC_LITERAL(12, 12),  // "themeCreated"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 4),  // "name"
        QT_MOC_LITERAL(31, 7),  // "content"
        QT_MOC_LITERAL(39, 12),  // "themeUpdated"
        QT_MOC_LITERAL(52, 9),  // "saveTheme"
        QT_MOC_LITERAL(62, 12),  // "previewTheme"
        QT_MOC_LITERAL(75, 10),  // "resetTheme"
        QT_MOC_LITERAL(86, 11),  // "importTheme"
        QT_MOC_LITERAL(98, 11),  // "exportTheme"
        QT_MOC_LITERAL(110, 10)   // "loadPreset"
    },
    "ThemeEditor",
    "themeCreated",
    "",
    "name",
    "content",
    "themeUpdated",
    "saveTheme",
    "previewTheme",
    "resetTheme",
    "importTheme",
    "exportTheme",
    "loadPreset"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ThemeEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   62,    2, 0x06,    1 /* Public */,
       5,    2,   67,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   72,    2, 0x08,    7 /* Private */,
       7,    0,   73,    2, 0x08,    8 /* Private */,
       8,    0,   74,    2, 0x08,    9 /* Private */,
       9,    0,   75,    2, 0x08,   10 /* Private */,
      10,    0,   76,    2, 0x08,   11 /* Private */,
      11,    0,   77,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ThemeEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ThemeEditor.offsetsAndSizes,
    qt_meta_data_ThemeEditor,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ThemeEditor_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ThemeEditor, std::true_type>,
        // method 'themeCreated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'themeUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'saveTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'previewTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'importTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportTheme'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadPreset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ThemeEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThemeEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->themeCreated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->themeUpdated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->saveTheme(); break;
        case 3: _t->previewTheme(); break;
        case 4: _t->resetTheme(); break;
        case 5: _t->importTheme(); break;
        case 6: _t->exportTheme(); break;
        case 7: _t->loadPreset(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThemeEditor::*)(const QString & , const QString & );
            if (_t _q_method = &ThemeEditor::themeCreated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThemeEditor::*)(const QString & , const QString & );
            if (_t _q_method = &ThemeEditor::themeUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *ThemeEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThemeEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThemeEditor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ThemeEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ThemeEditor::themeCreated(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThemeEditor::themeUpdated(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_stringdata_LanguageManager_t {
    uint offsetsAndSizes[10];
    char stringdata0[16];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_LanguageManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_LanguageManager_t qt_meta_stringdata_LanguageManager = {
    {
        QT_MOC_LITERAL(0, 15),  // "LanguageManager"
        QT_MOC_LITERAL(16, 15),  // "languageChanged"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 4),  // "code"
        QT_MOC_LITERAL(38, 17)   // "translationLoaded"
    },
    "LanguageManager",
    "languageChanged",
    "",
    "code",
    "translationLoaded"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_LanguageManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    1 /* Public */,
       4,    1,   29,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject LanguageManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LanguageManager.offsetsAndSizes,
    qt_meta_data_LanguageManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_LanguageManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LanguageManager, std::true_type>,
        // method 'languageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'translationLoaded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void LanguageManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LanguageManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->languageChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->translationLoaded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LanguageManager::*)(const QString & );
            if (_t _q_method = &LanguageManager::languageChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LanguageManager::*)(const QString & );
            if (_t _q_method = &LanguageManager::translationLoaded; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *LanguageManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LanguageManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LanguageManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LanguageManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    }
    return _id;
}

// SIGNAL 0
void LanguageManager::languageChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LanguageManager::translationLoaded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_stringdata_BackupManager_t {
    uint offsetsAndSizes[22];
    char stringdata0[14];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[8];
    char stringdata5[15];
    char stringdata6[20];
    char stringdata7[15];
    char stringdata8[11];
    char stringdata9[23];
    char stringdata10[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_BackupManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_BackupManager_t qt_meta_stringdata_BackupManager = {
    {
        QT_MOC_LITERAL(0, 13),  // "BackupManager"
        QT_MOC_LITERAL(14, 13),  // "backupCreated"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 8),  // "filename"
        QT_MOC_LITERAL(38, 7),  // "success"
        QT_MOC_LITERAL(46, 14),  // "backupRestored"
        QT_MOC_LITERAL(61, 19),  // "autoBackupCompleted"
        QT_MOC_LITERAL(81, 14),  // "backupProgress"
        QT_MOC_LITERAL(96, 10),  // "percentage"
        QT_MOC_LITERAL(107, 22),  // "performScheduledBackup"
        QT_MOC_LITERAL(130, 17)   // "cleanupOldBackups"
    },
    "BackupManager",
    "backupCreated",
    "",
    "filename",
    "success",
    "backupRestored",
    "autoBackupCompleted",
    "backupProgress",
    "percentage",
    "performScheduledBackup",
    "cleanupOldBackups"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_BackupManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   50,    2, 0x06,    1 /* Public */,
       5,    1,   55,    2, 0x06,    4 /* Public */,
       6,    1,   58,    2, 0x06,    6 /* Public */,
       7,    1,   61,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   64,    2, 0x08,   10 /* Private */,
      10,    0,   65,    2, 0x08,   11 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject BackupManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BackupManager.offsetsAndSizes,
    qt_meta_data_BackupManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_BackupManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BackupManager, std::true_type>,
        // method 'backupCreated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'backupRestored'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'autoBackupCompleted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'backupProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'performScheduledBackup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cleanupOldBackups'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void BackupManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackupManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backupCreated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 1: _t->backupRestored((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->autoBackupCompleted((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->backupProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->performScheduledBackup(); break;
        case 5: _t->cleanupOldBackups(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BackupManager::*)(const QString & , bool );
            if (_t _q_method = &BackupManager::backupCreated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BackupManager::*)(bool );
            if (_t _q_method = &BackupManager::backupRestored; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackupManager::*)(bool );
            if (_t _q_method = &BackupManager::autoBackupCompleted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BackupManager::*)(int );
            if (_t _q_method = &BackupManager::backupProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *BackupManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackupManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackupManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackupManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void BackupManager::backupCreated(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BackupManager::backupRestored(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BackupManager::autoBackupCompleted(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BackupManager::backupProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_stringdata_SystemMonitor_t {
    uint offsetsAndSizes[30];
    char stringdata0[14];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[7];
    char stringdata5[5];
    char stringdata6[13];
    char stringdata7[6];
    char stringdata8[16];
    char stringdata9[13];
    char stringdata10[10];
    char stringdata11[15];
    char stringdata12[7];
    char stringdata13[25];
    char stringdata14[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SystemMonitor_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SystemMonitor_t qt_meta_stringdata_SystemMonitor = {
    {
        QT_MOC_LITERAL(0, 13),  // "SystemMonitor"
        QT_MOC_LITERAL(14, 18),  // "performanceUpdated"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 3),  // "cpu"
        QT_MOC_LITERAL(38, 6),  // "memory"
        QT_MOC_LITERAL(45, 4),  // "disk"
        QT_MOC_LITERAL(50, 12),  // "highCPUUsage"
        QT_MOC_LITERAL(63, 5),  // "usage"
        QT_MOC_LITERAL(69, 15),  // "highMemoryUsage"
        QT_MOC_LITERAL(85, 12),  // "lowDiskSpace"
        QT_MOC_LITERAL(98, 9),  // "available"
        QT_MOC_LITERAL(108, 14),  // "databaseGrowth"
        QT_MOC_LITERAL(123, 6),  // "sizeMB"
        QT_MOC_LITERAL(130, 24),  // "updatePerformanceMetrics"
        QT_MOC_LITERAL(155, 17)   // "checkSystemHealth"
    },
    "SystemMonitor",
    "performanceUpdated",
    "",
    "cpu",
    "memory",
    "disk",
    "highCPUUsage",
    "usage",
    "highMemoryUsage",
    "lowDiskSpace",
    "available",
    "databaseGrowth",
    "sizeMB",
    "updatePerformanceMetrics",
    "checkSystemHealth"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SystemMonitor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   56,    2, 0x06,    1 /* Public */,
       6,    1,   63,    2, 0x06,    5 /* Public */,
       8,    1,   66,    2, 0x06,    7 /* Public */,
       9,    1,   69,    2, 0x06,    9 /* Public */,
      11,    1,   72,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,   75,    2, 0x08,   13 /* Private */,
      14,    0,   76,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Int,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SystemMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SystemMonitor.offsetsAndSizes,
    qt_meta_data_SystemMonitor,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SystemMonitor_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SystemMonitor, std::true_type>,
        // method 'performanceUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'highCPUUsage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'highMemoryUsage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'lowDiskSpace'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'databaseGrowth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updatePerformanceMetrics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkSystemHealth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SystemMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->performanceUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 1: _t->highCPUUsage((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->highMemoryUsage((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->lowDiskSpace((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->databaseGrowth((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->updatePerformanceMetrics(); break;
        case 6: _t->checkSystemHealth(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemMonitor::*)(double , double , double );
            if (_t _q_method = &SystemMonitor::performanceUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemMonitor::*)(double );
            if (_t _q_method = &SystemMonitor::highCPUUsage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemMonitor::*)(double );
            if (_t _q_method = &SystemMonitor::highMemoryUsage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemMonitor::*)(double );
            if (_t _q_method = &SystemMonitor::lowDiskSpace; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SystemMonitor::*)(int );
            if (_t _q_method = &SystemMonitor::databaseGrowth; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *SystemMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SystemMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SystemMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SystemMonitor::performanceUpdated(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SystemMonitor::highCPUUsage(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SystemMonitor::highMemoryUsage(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SystemMonitor::lowDiskSpace(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SystemMonitor::databaseGrowth(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
namespace {
struct qt_meta_stringdata_AboutDialog_t {
    uint offsetsAndSizes[14];
    char stringdata0[12];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[13];
    char stringdata5[12];
    char stringdata6[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AboutDialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_AboutDialog_t qt_meta_stringdata_AboutDialog = {
    {
        QT_MOC_LITERAL(0, 11),  // "AboutDialog"
        QT_MOC_LITERAL(12, 14),  // "showSystemInfo"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 11),  // "showLicense"
        QT_MOC_LITERAL(40, 12),  // "checkUpdates"
        QT_MOC_LITERAL(53, 11),  // "openWebsite"
        QT_MOC_LITERAL(65, 12)   // "sendFeedback"
    },
    "AboutDialog",
    "showSystemInfo",
    "",
    "showLicense",
    "checkUpdates",
    "openWebsite",
    "sendFeedback"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_AboutDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    0,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject AboutDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AboutDialog.offsetsAndSizes,
    qt_meta_data_AboutDialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_AboutDialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AboutDialog, std::true_type>,
        // method 'showSystemInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showLicense'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkUpdates'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openWebsite'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendFeedback'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AboutDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AboutDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showSystemInfo(); break;
        case 1: _t->showLicense(); break;
        case 2: _t->checkUpdates(); break;
        case 3: _t->openWebsite(); break;
        case 4: _t->sendFeedback(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *AboutDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AboutDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AboutDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AboutDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
