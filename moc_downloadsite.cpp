/****************************************************************************
** Meta object code from reading C++ file 'downloadsite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../GrateCaliandarQT/downloadsite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadsite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_downloadSite_t {
    QByteArrayData data[12];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_downloadSite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_downloadSite_t qt_meta_stringdata_downloadSite = {
    {
QT_MOC_LITERAL(0, 0, 12), // "downloadSite"
QT_MOC_LITERAL(1, 13, 17), // "downloadSiteStart"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 4), // "int*"
QT_MOC_LITERAL(4, 37, 8), // "QString*"
QT_MOC_LITERAL(5, 46, 18), // "downloadSiteUpdate"
QT_MOC_LITERAL(6, 65, 18), // "downloadSiteFinish"
QT_MOC_LITERAL(7, 84, 16), // "dowloadSiteArray"
QT_MOC_LITERAL(8, 101, 14), // "QNetworkReply*"
QT_MOC_LITERAL(9, 116, 5), // "reply"
QT_MOC_LITERAL(10, 122, 15), // "dowloadSiteFile"
QT_MOC_LITERAL(11, 138, 8) // "download"

    },
    "downloadSite\0downloadSiteStart\0\0int*\0"
    "QString*\0downloadSiteUpdate\0"
    "downloadSiteFinish\0dowloadSiteArray\0"
    "QNetworkReply*\0reply\0dowloadSiteFile\0"
    "download"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_downloadSite[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    1,   49,    2, 0x06 /* Public */,
       6,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   53,    2, 0x08 /* Private */,
      10,    1,   56,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void downloadSite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<downloadSite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadSiteStart((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2]))); break;
        case 1: _t->downloadSiteUpdate((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 2: _t->downloadSiteFinish(); break;
        case 3: _t->dowloadSiteArray((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->dowloadSiteFile((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->download(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (downloadSite::*)(int * , QString * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&downloadSite::downloadSiteStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (downloadSite::*)(int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&downloadSite::downloadSiteUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (downloadSite::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&downloadSite::downloadSiteFinish)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject downloadSite::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_downloadSite.data,
    qt_meta_data_downloadSite,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *downloadSite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *downloadSite::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_downloadSite.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int downloadSite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void downloadSite::downloadSiteStart(int * _t1, QString * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void downloadSite::downloadSiteUpdate(int * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void downloadSite::downloadSiteFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
