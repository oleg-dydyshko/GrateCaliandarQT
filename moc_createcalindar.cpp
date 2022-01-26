/****************************************************************************
** Meta object code from reading C++ file 'createcalindar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../GrateCaliandarQT/createcalindar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createcalindar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateCalindar_t {
    QByteArrayData data[14];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateCalindar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateCalindar_t qt_meta_stringdata_CreateCalindar = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CreateCalindar"
QT_MOC_LITERAL(1, 15, 8), // "finished"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "update"
QT_MOC_LITERAL(4, 32, 4), // "int*"
QT_MOC_LITERAL(5, 37, 7), // "getSize"
QT_MOC_LITERAL(6, 45, 8), // "QString*"
QT_MOC_LITERAL(7, 54, 8), // "sviatyia"
QT_MOC_LITERAL(8, 63, 4), // "year"
QT_MOC_LITERAL(9, 68, 8), // "generate"
QT_MOC_LITERAL(10, 77, 8), // "onResult"
QT_MOC_LITERAL(11, 86, 14), // "QNetworkReply*"
QT_MOC_LITERAL(12, 101, 5), // "reply"
QT_MOC_LITERAL(13, 107, 10) // "onDownload"

    },
    "CreateCalindar\0finished\0\0update\0int*\0"
    "getSize\0QString*\0sviatyia\0year\0generate\0"
    "onResult\0QNetworkReply*\0reply\0onDownload"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateCalindar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    3,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   60,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,
      10,    1,   64,    2, 0x08 /* Private */,
      13,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6, 0x80000000 | 6,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void CreateCalindar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateCalindar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->update((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 2: _t->getSize((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3]))); break;
        case 3: _t->sviatyia((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->generate(); break;
        case 5: _t->onResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->onDownload((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CreateCalindar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateCalindar::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CreateCalindar::*)(int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateCalindar::update)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CreateCalindar::*)(int * , QString * , QString * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateCalindar::getSize)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CreateCalindar::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CreateCalindar.data,
    qt_meta_data_CreateCalindar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CreateCalindar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateCalindar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreateCalindar.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CreateCalindar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CreateCalindar::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CreateCalindar::update(int * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CreateCalindar::getSize(int * _t1, QString * _t2, QString * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
