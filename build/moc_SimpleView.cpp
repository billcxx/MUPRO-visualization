/****************************************************************************
** Meta object code from reading C++ file 'SimpleView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SimpleView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpleView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SimpleView_t {
    QByteArrayData data[63];
    char stringdata0[1002];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimpleView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimpleView_t qt_meta_stringdata_SimpleView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SimpleView"
QT_MOC_LITERAL(1, 11, 19), // "slotOpenFile_scalar"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "slotOpenFile_vector"
QT_MOC_LITERAL(4, 52, 19), // "slotOpenFile_domain"
QT_MOC_LITERAL(5, 72, 8), // "slotExit"
QT_MOC_LITERAL(6, 81, 10), // "slotUpdate"
QT_MOC_LITERAL(7, 92, 25), // "on_scalarChoice_activated"
QT_MOC_LITERAL(8, 118, 5), // "index"
QT_MOC_LITERAL(9, 124, 25), // "on_vectorChoice_activated"
QT_MOC_LITERAL(10, 150, 23), // "on_axis_CB_stateChanged"
QT_MOC_LITERAL(11, 174, 5), // "state"
QT_MOC_LITERAL(12, 180, 26), // "on_outline_CB_stateChanged"
QT_MOC_LITERAL(13, 207, 25), // "on_scalar_CB_stateChanged"
QT_MOC_LITERAL(14, 233, 25), // "on_volume_CB_stateChanged"
QT_MOC_LITERAL(15, 259, 28), // "on_scalarBar_CB_stateChanged"
QT_MOC_LITERAL(16, 288, 25), // "on_vector_CB_stateChanged"
QT_MOC_LITERAL(17, 314, 26), // "on_extract_CB_stateChanged"
QT_MOC_LITERAL(18, 341, 26), // "on_xmin_LE_editingFinished"
QT_MOC_LITERAL(19, 368, 26), // "on_ymin_LE_editingFinished"
QT_MOC_LITERAL(20, 395, 26), // "on_zmin_LE_editingFinished"
QT_MOC_LITERAL(21, 422, 26), // "on_xmax_LE_editingFinished"
QT_MOC_LITERAL(22, 449, 26), // "on_ymax_LE_editingFinished"
QT_MOC_LITERAL(23, 476, 26), // "on_zmax_LE_editingFinished"
QT_MOC_LITERAL(24, 503, 30), // "on_scalarRange_CB_stateChanged"
QT_MOC_LITERAL(25, 534, 32), // "on_RGB_Combo_currentIndexChanged"
QT_MOC_LITERAL(26, 567, 34), // "on_alpha_Combo_currentIndexCh..."
QT_MOC_LITERAL(27, 602, 21), // "on_RGBAdd_PB_released"
QT_MOC_LITERAL(28, 624, 24), // "on_RGBDelete_PB_released"
QT_MOC_LITERAL(29, 649, 23), // "on_alphaAdd_PB_released"
QT_MOC_LITERAL(30, 673, 26), // "on_alphaDelete_PB_released"
QT_MOC_LITERAL(31, 700, 24), // "on_domain_LW_itemChanged"
QT_MOC_LITERAL(32, 725, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(33, 742, 4), // "item"
QT_MOC_LITERAL(34, 747, 25), // "on_domain_CB_stateChanged"
QT_MOC_LITERAL(35, 773, 9), // "updateVTK"
QT_MOC_LITERAL(36, 783, 11), // "std::string"
QT_MOC_LITERAL(37, 795, 14), // "fileNameScalar"
QT_MOC_LITERAL(38, 810, 14), // "fileNameVector"
QT_MOC_LITERAL(39, 825, 10), // "drawDomain"
QT_MOC_LITERAL(40, 836, 10), // "domainName"
QT_MOC_LITERAL(41, 847, 8), // "loadData"
QT_MOC_LITERAL(42, 856, 7), // "filedir"
QT_MOC_LITERAL(43, 864, 16), // "domainProcessing"
QT_MOC_LITERAL(44, 881, 10), // "domainType"
QT_MOC_LITERAL(45, 892, 2), // "px"
QT_MOC_LITERAL(46, 895, 2), // "py"
QT_MOC_LITERAL(47, 898, 2), // "pz"
QT_MOC_LITERAL(48, 901, 6), // "getMin"
QT_MOC_LITERAL(49, 908, 7), // "double*"
QT_MOC_LITERAL(50, 916, 4), // "list"
QT_MOC_LITERAL(51, 921, 6), // "length"
QT_MOC_LITERAL(52, 928, 6), // "getMax"
QT_MOC_LITERAL(53, 935, 6), // "getAvg"
QT_MOC_LITERAL(54, 942, 12), // "outputScalar"
QT_MOC_LITERAL(55, 955, 12), // "columnNumber"
QT_MOC_LITERAL(56, 968, 1), // "x"
QT_MOC_LITERAL(57, 970, 1), // "y"
QT_MOC_LITERAL(58, 972, 1), // "z"
QT_MOC_LITERAL(59, 974, 12), // "outputVector"
QT_MOC_LITERAL(60, 987, 4), // "colX"
QT_MOC_LITERAL(61, 992, 4), // "colY"
QT_MOC_LITERAL(62, 997, 4) // "colZ"

    },
    "SimpleView\0slotOpenFile_scalar\0\0"
    "slotOpenFile_vector\0slotOpenFile_domain\0"
    "slotExit\0slotUpdate\0on_scalarChoice_activated\0"
    "index\0on_vectorChoice_activated\0"
    "on_axis_CB_stateChanged\0state\0"
    "on_outline_CB_stateChanged\0"
    "on_scalar_CB_stateChanged\0"
    "on_volume_CB_stateChanged\0"
    "on_scalarBar_CB_stateChanged\0"
    "on_vector_CB_stateChanged\0"
    "on_extract_CB_stateChanged\0"
    "on_xmin_LE_editingFinished\0"
    "on_ymin_LE_editingFinished\0"
    "on_zmin_LE_editingFinished\0"
    "on_xmax_LE_editingFinished\0"
    "on_ymax_LE_editingFinished\0"
    "on_zmax_LE_editingFinished\0"
    "on_scalarRange_CB_stateChanged\0"
    "on_RGB_Combo_currentIndexChanged\0"
    "on_alpha_Combo_currentIndexChanged\0"
    "on_RGBAdd_PB_released\0on_RGBDelete_PB_released\0"
    "on_alphaAdd_PB_released\0"
    "on_alphaDelete_PB_released\0"
    "on_domain_LW_itemChanged\0QListWidgetItem*\0"
    "item\0on_domain_CB_stateChanged\0updateVTK\0"
    "std::string\0fileNameScalar\0fileNameVector\0"
    "drawDomain\0domainName\0loadData\0filedir\0"
    "domainProcessing\0domainType\0px\0py\0pz\0"
    "getMin\0double*\0list\0length\0getMax\0"
    "getAvg\0outputScalar\0columnNumber\0x\0y\0"
    "z\0outputVector\0colX\0colY\0colZ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimpleView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  209,    2, 0x0a /* Public */,
       3,    0,  210,    2, 0x0a /* Public */,
       4,    0,  211,    2, 0x0a /* Public */,
       5,    0,  212,    2, 0x0a /* Public */,
       6,    0,  213,    2, 0x0a /* Public */,
       7,    1,  214,    2, 0x0a /* Public */,
       9,    1,  217,    2, 0x0a /* Public */,
      10,    1,  220,    2, 0x0a /* Public */,
      12,    1,  223,    2, 0x0a /* Public */,
      13,    1,  226,    2, 0x0a /* Public */,
      14,    1,  229,    2, 0x0a /* Public */,
      15,    1,  232,    2, 0x0a /* Public */,
      16,    1,  235,    2, 0x0a /* Public */,
      17,    1,  238,    2, 0x0a /* Public */,
      18,    0,  241,    2, 0x0a /* Public */,
      19,    0,  242,    2, 0x0a /* Public */,
      20,    0,  243,    2, 0x0a /* Public */,
      21,    0,  244,    2, 0x0a /* Public */,
      22,    0,  245,    2, 0x0a /* Public */,
      23,    0,  246,    2, 0x0a /* Public */,
      24,    1,  247,    2, 0x0a /* Public */,
      25,    1,  250,    2, 0x0a /* Public */,
      26,    1,  253,    2, 0x0a /* Public */,
      27,    0,  256,    2, 0x0a /* Public */,
      28,    0,  257,    2, 0x0a /* Public */,
      29,    0,  258,    2, 0x0a /* Public */,
      30,    0,  259,    2, 0x0a /* Public */,
      31,    1,  260,    2, 0x0a /* Public */,
      34,    1,  263,    2, 0x0a /* Public */,
      35,    2,  266,    2, 0x0a /* Public */,
      39,    1,  271,    2, 0x0a /* Public */,
      41,    1,  274,    2, 0x0a /* Public */,
      43,    1,  277,    2, 0x0a /* Public */,
      44,    3,  280,    2, 0x0a /* Public */,
      48,    2,  287,    2, 0x0a /* Public */,
      52,    2,  292,    2, 0x0a /* Public */,
      53,    2,  297,    2, 0x0a /* Public */,
      54,    4,  302,    2, 0x0a /* Public */,
      59,    6,  311,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 36, 0x80000000 | 36,   37,   38,
    QMetaType::Void, 0x80000000 | 36,   40,
    QMetaType::Int, QMetaType::QString,   42,
    QMetaType::Int, QMetaType::QString,   42,
    QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,   45,   46,   47,
    QMetaType::Double, 0x80000000 | 49, QMetaType::Int,   50,   51,
    QMetaType::Double, 0x80000000 | 49, QMetaType::Int,   50,   51,
    QMetaType::Double, 0x80000000 | 49, QMetaType::Int,   50,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   55,   56,   57,   58,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   60,   61,   62,   56,   57,   58,

       0        // eod
};

void SimpleView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SimpleView *_t = static_cast<SimpleView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotOpenFile_scalar(); break;
        case 1: _t->slotOpenFile_vector(); break;
        case 2: _t->slotOpenFile_domain(); break;
        case 3: _t->slotExit(); break;
        case 4: _t->slotUpdate(); break;
        case 5: _t->on_scalarChoice_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_vectorChoice_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_axis_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_outline_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_scalar_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_volume_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_scalarBar_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_vector_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_extract_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_xmin_LE_editingFinished(); break;
        case 15: _t->on_ymin_LE_editingFinished(); break;
        case 16: _t->on_zmin_LE_editingFinished(); break;
        case 17: _t->on_xmax_LE_editingFinished(); break;
        case 18: _t->on_ymax_LE_editingFinished(); break;
        case 19: _t->on_zmax_LE_editingFinished(); break;
        case 20: _t->on_scalarRange_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_RGB_Combo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_alpha_Combo_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_RGBAdd_PB_released(); break;
        case 24: _t->on_RGBDelete_PB_released(); break;
        case 25: _t->on_alphaAdd_PB_released(); break;
        case 26: _t->on_alphaDelete_PB_released(); break;
        case 27: _t->on_domain_LW_itemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 28: _t->on_domain_CB_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->updateVTK((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 30: _t->drawDomain((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 31: { int _r = _t->loadData((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 32: { int _r = _t->domainProcessing((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 33: { int _r = _t->domainType((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 34: { double _r = _t->getMin((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 35: { double _r = _t->getMax((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 36: { double _r = _t->getAvg((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 37: _t->outputScalar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 38: _t->outputVector((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        default: ;
        }
    }
}

const QMetaObject SimpleView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimpleView.data,
      qt_meta_data_SimpleView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SimpleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleView.stringdata0))
        return static_cast<void*>(const_cast< SimpleView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimpleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 39;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
