/****************************************************************************
** Meta object code from reading C++ file 'all_transactions_view.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Point-Of-Service/all_transactions_view.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'all_transactions_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
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
struct qt_meta_stringdata_All_transactions_view_t {
    uint offsetsAndSizes[10];
    char stringdata0[22];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_All_transactions_view_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_All_transactions_view_t qt_meta_stringdata_All_transactions_view = {
    {
        QT_MOC_LITERAL(0, 21),  // "All_transactions_view"
        QT_MOC_LITERAL(22, 10),  // "objectSent"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 11),  // "Transaction"
        QT_MOC_LITERAL(46, 8)   // "selected"
    },
    "All_transactions_view",
    "objectSent",
    "",
    "Transaction",
    "selected"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_All_transactions_view[] = {

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
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject All_transactions_view::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_All_transactions_view.offsetsAndSizes,
    qt_meta_data_All_transactions_view,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_All_transactions_view_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<All_transactions_view, std::true_type>,
        // method 'objectSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Transaction, std::false_type>
    >,
    nullptr
} };

void All_transactions_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<All_transactions_view *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->objectSent((*reinterpret_cast< std::add_pointer_t<Transaction>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (All_transactions_view::*)(Transaction );
            if (_t _q_method = &All_transactions_view::objectSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *All_transactions_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *All_transactions_view::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_All_transactions_view.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int All_transactions_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void All_transactions_view::objectSent(Transaction _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
