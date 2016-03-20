/********************************************************************************
** Form generated from reading UI file 'SimpleView.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEVIEW_H
#define UI_SIMPLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SimpleView
{
public:
    QAction *actionOpenFile_scalar;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionRefresh;
    QAction *actionSave;
    QAction *actionOpenFile_vector;
    QAction *actionOpenFile_domain;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *container;
    QVTKWidget *qvtkWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_9;
    QTabWidget *information_Tab;
    QWidget *tab_3;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_4;
    QLabel *rowcolScalar;
    QLabel *inputFileScalar;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *xMinMaxScalar;
    QLabel *label_24;
    QLabel *label_26;
    QLabel *yMinMaxScalar;
    QLabel *label_30;
    QLabel *zMinMaxScalar;
    QTableWidget *scalar_Table;
    QWidget *tab_4;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_5;
    QLabel *rowcolVector;
    QLabel *inputFileVector;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *xMinMaxVector;
    QLabel *label_25;
    QLabel *label_27;
    QLabel *yMinMaxVector;
    QLabel *label_33;
    QLabel *zMinMaxVector;
    QTableWidget *vector_Table;
    QWidget *tab_5;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout_8;
    QGridLayout *gridLayout_6;
    QLabel *rowcolDomain;
    QLabel *inputFileDomain;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *xMinMaxDomain;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *yMinMaxDomain;
    QLabel *label_42;
    QLabel *zMinMaxDomain;
    QTableWidget *domain_Table;
    QGroupBox *groupBox_2;
    QCheckBox *axis_CB;
    QCheckBox *scalarBar_CB;
    QCheckBox *extract_CB;
    QCheckBox *outline_CB;
    QTextBrowser *output;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QLabel *label_18;
    QLineEdit *xmin_LE;
    QLabel *label_19;
    QLineEdit *xmax_LE;
    QLabel *label_21;
    QLineEdit *ymin_LE;
    QLabel *label_20;
    QLineEdit *ymax_LE;
    QLabel *label_23;
    QLineEdit *zmin_LE;
    QLabel *label_22;
    QLineEdit *zmax_LE;
    QWidget *widget;
    QGroupBox *groupBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *RGB_Combo;
    QPushButton *RGBAdd_PB;
    QPushButton *RGBDelete_PB;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_12;
    QLineEdit *RGBValue_LE;
    QLabel *label_13;
    QLineEdit *RGBR_LE;
    QLineEdit *RGBG_LE;
    QLineEdit *RGBB_LE;
    QStackedWidget *RGB_Stack;
    QWidget *page;
    QTableWidget *RGBScalar_Table;
    QWidget *page_2;
    QTableWidget *RGBVector_Table;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *alpha_Combo;
    QPushButton *alphaAdd_PB;
    QPushButton *alphaDelete_PB;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_14;
    QLineEdit *alphaValue_LE;
    QLabel *label_15;
    QLineEdit *alpha_LE;
    QStackedWidget *alpha_Stack;
    QWidget *page_3;
    QTableWidget *alphaScalar_Table;
    QWidget *page_4;
    QTableWidget *alphaVector_Table;
    QGroupBox *groupBox_5;
    QCheckBox *vector_CB;
    QCheckBox *streamline_CB;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *vectorChoice;
    QLabel *label_4;
    QLineEdit *vectorScale_LE;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *vectorRange_CB;
    QLineEdit *vectorValueMin_LE;
    QLabel *label_7;
    QLineEdit *vectorValueMax_LE;
    QLabel *label_6;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_34;
    QLineEdit *seedNumber_LE;
    QLineEdit *seedRadius_LE;
    QLineEdit *seedCenterX_LE;
    QLineEdit *seedCenterY_LE;
    QLineEdit *seedCenterZ_LE;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLineEdit *streamStepLength_LE;
    QLineEdit *streamIntStepLength_LE;
    QGroupBox *groupBox_4;
    QCheckBox *domain_CB;
    QListWidget *domain_LW;
    QGroupBox *groupBox_3;
    QCheckBox *volume_CB;
    QCheckBox *scalar_CB;
    QComboBox *scalarChoice;
    QLabel *label;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *isosurface_CB;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_16;
    QLineEdit *lineEdit_19;
    QLabel *label_17;
    QLineEdit *lineEdit_20;
    QLineEdit *lineEdit_21;
    QLineEdit *lineEdit_22;
    QListWidget *listWidget_3;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_8;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_5;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *scalarRange_CB;
    QLineEdit *scalarValueMin_LE;
    QLabel *label_5;
    QLineEdit *scalarValueMax_LE;
    QWidget *tab_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SimpleView)
    {
        if (SimpleView->objectName().isEmpty())
            SimpleView->setObjectName(QStringLiteral("SimpleView"));
        SimpleView->resize(1222, 744);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        SimpleView->setWindowIcon(icon);
        SimpleView->setIconSize(QSize(22, 22));
        actionOpenFile_scalar = new QAction(SimpleView);
        actionOpenFile_scalar->setObjectName(QStringLiteral("actionOpenFile_scalar"));
        actionOpenFile_scalar->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile_scalar->setIcon(icon1);
        actionExit = new QAction(SimpleView);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionPrint = new QAction(SimpleView);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon2);
        actionRefresh = new QAction(SimpleView);
        actionRefresh->setObjectName(QStringLiteral("actionRefresh"));
        actionRefresh->setIcon(icon);
        actionSave = new QAction(SimpleView);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionOpenFile_vector = new QAction(SimpleView);
        actionOpenFile_vector->setObjectName(QStringLiteral("actionOpenFile_vector"));
        actionOpenFile_vector->setEnabled(true);
        actionOpenFile_vector->setIcon(icon1);
        actionOpenFile_domain = new QAction(SimpleView);
        actionOpenFile_domain->setObjectName(QStringLiteral("actionOpenFile_domain"));
        actionOpenFile_domain->setEnabled(true);
        actionOpenFile_domain->setIcon(icon1);
        centralwidget = new QWidget(SimpleView);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        container = new QWidget(tab);
        container->setObjectName(QStringLiteral("container"));
        container->setGeometry(QRect(0, 10, 591, 611));
        qvtkWidget = new QVTKWidget(container);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(1, 5, 589, 311));
        qvtkWidget->setMinimumSize(QSize(580, 300));
        layoutWidget = new QWidget(container);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 320, 581, 286));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        information_Tab = new QTabWidget(layoutWidget);
        information_Tab->setObjectName(QStringLiteral("information_Tab"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget_2 = new QWidget(tab_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 0, 321, 241));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        rowcolScalar = new QLabel(layoutWidget_2);
        rowcolScalar->setObjectName(QStringLiteral("rowcolScalar"));

        gridLayout_4->addWidget(rowcolScalar, 1, 1, 1, 1);

        inputFileScalar = new QLabel(layoutWidget_2);
        inputFileScalar->setObjectName(QStringLiteral("inputFileScalar"));

        gridLayout_4->addWidget(inputFileScalar, 0, 1, 1, 1);

        label_28 = new QLabel(layoutWidget_2);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_4->addWidget(label_28, 2, 0, 1, 1);

        label_29 = new QLabel(layoutWidget_2);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout_4->addWidget(label_29, 3, 0, 1, 1);

        xMinMaxScalar = new QLabel(layoutWidget_2);
        xMinMaxScalar->setObjectName(QStringLiteral("xMinMaxScalar"));

        gridLayout_4->addWidget(xMinMaxScalar, 2, 1, 1, 1);

        label_24 = new QLabel(layoutWidget_2);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_4->addWidget(label_24, 0, 0, 1, 1);

        label_26 = new QLabel(layoutWidget_2);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_4->addWidget(label_26, 1, 0, 1, 1);

        yMinMaxScalar = new QLabel(layoutWidget_2);
        yMinMaxScalar->setObjectName(QStringLiteral("yMinMaxScalar"));

        gridLayout_4->addWidget(yMinMaxScalar, 3, 1, 1, 1);

        label_30 = new QLabel(layoutWidget_2);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout_4->addWidget(label_30, 4, 0, 1, 1);

        zMinMaxScalar = new QLabel(layoutWidget_2);
        zMinMaxScalar->setObjectName(QStringLiteral("zMinMaxScalar"));

        gridLayout_4->addWidget(zMinMaxScalar, 4, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_4);

        scalar_Table = new QTableWidget(layoutWidget_2);
        if (scalar_Table->columnCount() < 3)
            scalar_Table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        scalar_Table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        scalar_Table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        scalar_Table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        scalar_Table->setObjectName(QStringLiteral("scalar_Table"));
        scalar_Table->setMinimumSize(QSize(0, 0));
        scalar_Table->setMaximumSize(QSize(100000, 16777215));
        scalar_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        scalar_Table->horizontalHeader()->setDefaultSectionSize(100);
        scalar_Table->horizontalHeader()->setMinimumSectionSize(40);
        scalar_Table->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_6->addWidget(scalar_Table);

        information_Tab->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        layoutWidget_3 = new QWidget(tab_4);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(0, 0, 321, 241));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        rowcolVector = new QLabel(layoutWidget_3);
        rowcolVector->setObjectName(QStringLiteral("rowcolVector"));

        gridLayout_5->addWidget(rowcolVector, 1, 1, 1, 1);

        inputFileVector = new QLabel(layoutWidget_3);
        inputFileVector->setObjectName(QStringLiteral("inputFileVector"));

        gridLayout_5->addWidget(inputFileVector, 0, 1, 1, 1);

        label_31 = new QLabel(layoutWidget_3);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_5->addWidget(label_31, 2, 0, 1, 1);

        label_32 = new QLabel(layoutWidget_3);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_5->addWidget(label_32, 3, 0, 1, 1);

        xMinMaxVector = new QLabel(layoutWidget_3);
        xMinMaxVector->setObjectName(QStringLiteral("xMinMaxVector"));

        gridLayout_5->addWidget(xMinMaxVector, 2, 1, 1, 1);

        label_25 = new QLabel(layoutWidget_3);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_5->addWidget(label_25, 0, 0, 1, 1);

        label_27 = new QLabel(layoutWidget_3);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_5->addWidget(label_27, 1, 0, 1, 1);

        yMinMaxVector = new QLabel(layoutWidget_3);
        yMinMaxVector->setObjectName(QStringLiteral("yMinMaxVector"));

        gridLayout_5->addWidget(yMinMaxVector, 3, 1, 1, 1);

        label_33 = new QLabel(layoutWidget_3);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_5->addWidget(label_33, 4, 0, 1, 1);

        zMinMaxVector = new QLabel(layoutWidget_3);
        zMinMaxVector->setObjectName(QStringLiteral("zMinMaxVector"));

        gridLayout_5->addWidget(zMinMaxVector, 4, 1, 1, 1);


        verticalLayout_7->addLayout(gridLayout_5);

        vector_Table = new QTableWidget(layoutWidget_3);
        if (vector_Table->columnCount() < 3)
            vector_Table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        vector_Table->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        vector_Table->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        vector_Table->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        vector_Table->setObjectName(QStringLiteral("vector_Table"));
        vector_Table->setMinimumSize(QSize(0, 0));
        vector_Table->setMaximumSize(QSize(100000, 16777215));
        vector_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        vector_Table->horizontalHeader()->setDefaultSectionSize(100);
        vector_Table->horizontalHeader()->setMinimumSectionSize(40);
        vector_Table->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_7->addWidget(vector_Table);

        information_Tab->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        layoutWidget_5 = new QWidget(tab_5);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(0, 0, 321, 241));
        verticalLayout_8 = new QVBoxLayout(layoutWidget_5);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        rowcolDomain = new QLabel(layoutWidget_5);
        rowcolDomain->setObjectName(QStringLiteral("rowcolDomain"));

        gridLayout_6->addWidget(rowcolDomain, 1, 1, 1, 1);

        inputFileDomain = new QLabel(layoutWidget_5);
        inputFileDomain->setObjectName(QStringLiteral("inputFileDomain"));

        gridLayout_6->addWidget(inputFileDomain, 0, 1, 1, 1);

        label_38 = new QLabel(layoutWidget_5);
        label_38->setObjectName(QStringLiteral("label_38"));

        gridLayout_6->addWidget(label_38, 2, 0, 1, 1);

        label_39 = new QLabel(layoutWidget_5);
        label_39->setObjectName(QStringLiteral("label_39"));

        gridLayout_6->addWidget(label_39, 3, 0, 1, 1);

        xMinMaxDomain = new QLabel(layoutWidget_5);
        xMinMaxDomain->setObjectName(QStringLiteral("xMinMaxDomain"));

        gridLayout_6->addWidget(xMinMaxDomain, 2, 1, 1, 1);

        label_40 = new QLabel(layoutWidget_5);
        label_40->setObjectName(QStringLiteral("label_40"));

        gridLayout_6->addWidget(label_40, 0, 0, 1, 1);

        label_41 = new QLabel(layoutWidget_5);
        label_41->setObjectName(QStringLiteral("label_41"));

        gridLayout_6->addWidget(label_41, 1, 0, 1, 1);

        yMinMaxDomain = new QLabel(layoutWidget_5);
        yMinMaxDomain->setObjectName(QStringLiteral("yMinMaxDomain"));

        gridLayout_6->addWidget(yMinMaxDomain, 3, 1, 1, 1);

        label_42 = new QLabel(layoutWidget_5);
        label_42->setObjectName(QStringLiteral("label_42"));

        gridLayout_6->addWidget(label_42, 4, 0, 1, 1);

        zMinMaxDomain = new QLabel(layoutWidget_5);
        zMinMaxDomain->setObjectName(QStringLiteral("zMinMaxDomain"));

        gridLayout_6->addWidget(zMinMaxDomain, 4, 1, 1, 1);


        verticalLayout_8->addLayout(gridLayout_6);

        domain_Table = new QTableWidget(layoutWidget_5);
        if (domain_Table->columnCount() < 3)
            domain_Table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        domain_Table->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        domain_Table->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        domain_Table->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        domain_Table->setObjectName(QStringLiteral("domain_Table"));
        domain_Table->setMinimumSize(QSize(0, 0));
        domain_Table->setMaximumSize(QSize(100000, 16777215));
        domain_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        domain_Table->horizontalHeader()->setDefaultSectionSize(100);
        domain_Table->horizontalHeader()->setMinimumSectionSize(40);
        domain_Table->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_8->addWidget(domain_Table);

        information_Tab->addTab(tab_5, QString());

        horizontalLayout_9->addWidget(information_Tab);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(230, 270));
        groupBox_2->setMaximumSize(QSize(230, 270));
        axis_CB = new QCheckBox(groupBox_2);
        axis_CB->setObjectName(QStringLiteral("axis_CB"));
        axis_CB->setGeometry(QRect(10, 30, 86, 20));
        scalarBar_CB = new QCheckBox(groupBox_2);
        scalarBar_CB->setObjectName(QStringLiteral("scalarBar_CB"));
        scalarBar_CB->setGeometry(QRect(70, 30, 86, 20));
        extract_CB = new QCheckBox(groupBox_2);
        extract_CB->setObjectName(QStringLiteral("extract_CB"));
        extract_CB->setGeometry(QRect(10, 60, 91, 20));
        outline_CB = new QCheckBox(groupBox_2);
        outline_CB->setObjectName(QStringLiteral("outline_CB"));
        outline_CB->setGeometry(QRect(100, 60, 86, 20));
        output = new QTextBrowser(groupBox_2);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(10, 180, 211, 81));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 92, 197, 85));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_18 = new QLabel(layoutWidget1);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_18, 0, 0, 1, 1);

        xmin_LE = new QLineEdit(layoutWidget1);
        xmin_LE->setObjectName(QStringLiteral("xmin_LE"));
        xmin_LE->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(xmin_LE, 0, 1, 1, 1);

        label_19 = new QLabel(layoutWidget1);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_19, 0, 2, 1, 1);

        xmax_LE = new QLineEdit(layoutWidget1);
        xmax_LE->setObjectName(QStringLiteral("xmax_LE"));
        xmax_LE->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(xmax_LE, 0, 3, 1, 1);

        label_21 = new QLabel(layoutWidget1);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_21, 1, 0, 1, 1);

        ymin_LE = new QLineEdit(layoutWidget1);
        ymin_LE->setObjectName(QStringLiteral("ymin_LE"));
        ymin_LE->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(ymin_LE, 1, 1, 1, 1);

        label_20 = new QLabel(layoutWidget1);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_20, 1, 2, 1, 1);

        ymax_LE = new QLineEdit(layoutWidget1);
        ymax_LE->setObjectName(QStringLiteral("ymax_LE"));
        ymax_LE->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(ymax_LE, 1, 3, 1, 1);

        label_23 = new QLabel(layoutWidget1);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_23, 2, 0, 1, 1);

        zmin_LE = new QLineEdit(layoutWidget1);
        zmin_LE->setObjectName(QStringLiteral("zmin_LE"));
        zmin_LE->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(zmin_LE, 2, 1, 1, 1);

        label_22 = new QLabel(layoutWidget1);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_22, 2, 2, 1, 1);

        zmax_LE = new QLineEdit(layoutWidget1);
        zmax_LE->setObjectName(QStringLiteral("zmax_LE"));
        zmax_LE->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(zmax_LE, 2, 3, 1, 1);


        horizontalLayout_9->addWidget(groupBox_2);

        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(589, 0, 581, 611));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(11, 404, 561, 211));
        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(4, 30, 281, 171));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
#ifndef Q_OS_MAC
        verticalLayout_3->setSpacing(-1);
#endif
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RGB_Combo = new QComboBox(layoutWidget2);
        RGB_Combo->setObjectName(QStringLiteral("RGB_Combo"));

        horizontalLayout_2->addWidget(RGB_Combo);

        RGBAdd_PB = new QPushButton(layoutWidget2);
        RGBAdd_PB->setObjectName(QStringLiteral("RGBAdd_PB"));
        RGBAdd_PB->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(RGBAdd_PB);

        RGBDelete_PB = new QPushButton(layoutWidget2);
        RGBDelete_PB->setObjectName(QStringLiteral("RGBDelete_PB"));
        RGBDelete_PB->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(RGBDelete_PB);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(label_12);

        RGBValue_LE = new QLineEdit(layoutWidget2);
        RGBValue_LE->setObjectName(QStringLiteral("RGBValue_LE"));
        RGBValue_LE->setEnabled(false);
        RGBValue_LE->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(RGBValue_LE);

        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(label_13);

        RGBR_LE = new QLineEdit(layoutWidget2);
        RGBR_LE->setObjectName(QStringLiteral("RGBR_LE"));
        RGBR_LE->setEnabled(false);
        RGBR_LE->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(RGBR_LE);

        RGBG_LE = new QLineEdit(layoutWidget2);
        RGBG_LE->setObjectName(QStringLiteral("RGBG_LE"));
        RGBG_LE->setEnabled(false);
        RGBG_LE->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(RGBG_LE);

        RGBB_LE = new QLineEdit(layoutWidget2);
        RGBB_LE->setObjectName(QStringLiteral("RGBB_LE"));
        RGBB_LE->setEnabled(false);
        RGBB_LE->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(RGBB_LE);


        verticalLayout_3->addLayout(horizontalLayout_4);

        RGB_Stack = new QStackedWidget(layoutWidget2);
        RGB_Stack->setObjectName(QStringLiteral("RGB_Stack"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        RGBScalar_Table = new QTableWidget(page);
        if (RGBScalar_Table->columnCount() < 4)
            RGBScalar_Table->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        RGBScalar_Table->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        RGBScalar_Table->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        RGBScalar_Table->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        RGBScalar_Table->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        RGBScalar_Table->setObjectName(QStringLiteral("RGBScalar_Table"));
        RGBScalar_Table->setEnabled(false);
        RGBScalar_Table->setGeometry(QRect(0, 0, 273, 81));
        RGBScalar_Table->setMaximumSize(QSize(300, 16777215));
        RGBScalar_Table->horizontalHeader()->setDefaultSectionSize(67);
        RGBScalar_Table->horizontalHeader()->setStretchLastSection(true);
        RGBScalar_Table->verticalHeader()->setDefaultSectionSize(25);
        RGB_Stack->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        RGBVector_Table = new QTableWidget(page_2);
        if (RGBVector_Table->columnCount() < 4)
            RGBVector_Table->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        RGBVector_Table->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        RGBVector_Table->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        RGBVector_Table->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        RGBVector_Table->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        RGBVector_Table->setObjectName(QStringLiteral("RGBVector_Table"));
        RGBVector_Table->setEnabled(false);
        RGBVector_Table->setGeometry(QRect(0, 0, 271, 91));
        RGBVector_Table->setMaximumSize(QSize(300, 16777215));
        RGBVector_Table->horizontalHeader()->setDefaultSectionSize(67);
        RGBVector_Table->horizontalHeader()->setStretchLastSection(true);
        RGBVector_Table->verticalHeader()->setDefaultSectionSize(25);
        RGB_Stack->addWidget(page_2);

        verticalLayout_3->addWidget(RGB_Stack);

        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(291, 31, 261, 171));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        alpha_Combo = new QComboBox(layoutWidget3);
        alpha_Combo->setObjectName(QStringLiteral("alpha_Combo"));

        horizontalLayout_3->addWidget(alpha_Combo);

        alphaAdd_PB = new QPushButton(layoutWidget3);
        alphaAdd_PB->setObjectName(QStringLiteral("alphaAdd_PB"));
        alphaAdd_PB->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(alphaAdd_PB);

        alphaDelete_PB = new QPushButton(layoutWidget3);
        alphaDelete_PB->setObjectName(QStringLiteral("alphaDelete_PB"));
        alphaDelete_PB->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(alphaDelete_PB);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_14 = new QLabel(layoutWidget3);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_8->addWidget(label_14);

        alphaValue_LE = new QLineEdit(layoutWidget3);
        alphaValue_LE->setObjectName(QStringLiteral("alphaValue_LE"));
        alphaValue_LE->setEnabled(false);
        alphaValue_LE->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_8->addWidget(alphaValue_LE);

        label_15 = new QLabel(layoutWidget3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_8->addWidget(label_15);

        alpha_LE = new QLineEdit(layoutWidget3);
        alpha_LE->setObjectName(QStringLiteral("alpha_LE"));
        alpha_LE->setEnabled(false);
        alpha_LE->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_8->addWidget(alpha_LE);


        verticalLayout->addLayout(horizontalLayout_8);

        alpha_Stack = new QStackedWidget(layoutWidget3);
        alpha_Stack->setObjectName(QStringLiteral("alpha_Stack"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        alphaScalar_Table = new QTableWidget(page_3);
        if (alphaScalar_Table->columnCount() < 2)
            alphaScalar_Table->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        alphaScalar_Table->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        alphaScalar_Table->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        alphaScalar_Table->setObjectName(QStringLiteral("alphaScalar_Table"));
        alphaScalar_Table->setEnabled(false);
        alphaScalar_Table->setGeometry(QRect(0, 0, 261, 91));
        alphaScalar_Table->setMaximumSize(QSize(300, 16777215));
        alphaScalar_Table->horizontalHeader()->setDefaultSectionSize(120);
        alphaScalar_Table->horizontalHeader()->setStretchLastSection(true);
        alphaScalar_Table->verticalHeader()->setDefaultSectionSize(25);
        alpha_Stack->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        alphaVector_Table = new QTableWidget(page_4);
        if (alphaVector_Table->columnCount() < 2)
            alphaVector_Table->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        alphaVector_Table->setHorizontalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        alphaVector_Table->setHorizontalHeaderItem(1, __qtablewidgetitem20);
        alphaVector_Table->setObjectName(QStringLiteral("alphaVector_Table"));
        alphaVector_Table->setEnabled(false);
        alphaVector_Table->setGeometry(QRect(0, 0, 261, 78));
        alphaVector_Table->setMaximumSize(QSize(300, 16777215));
        alphaVector_Table->horizontalHeader()->setDefaultSectionSize(120);
        alphaVector_Table->horizontalHeader()->setStretchLastSection(true);
        alphaVector_Table->verticalHeader()->setDefaultSectionSize(25);
        alpha_Stack->addWidget(page_4);

        verticalLayout->addWidget(alpha_Stack);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(290, 210, 281, 201));
        vector_CB = new QCheckBox(groupBox_5);
        vector_CB->setObjectName(QStringLiteral("vector_CB"));
        vector_CB->setGeometry(QRect(10, 20, 86, 20));
        streamline_CB = new QCheckBox(groupBox_5);
        streamline_CB->setObjectName(QStringLiteral("streamline_CB"));
        streamline_CB->setGeometry(QRect(300, 20, 86, 20));
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 151, 16));
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 60, 51, 16));
        vectorChoice = new QComboBox(groupBox_5);
        vectorChoice->setObjectName(QStringLiteral("vectorChoice"));
        vectorChoice->setGeometry(QRect(80, 60, 104, 26));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 150, 59, 16));
        vectorScale_LE = new QLineEdit(groupBox_5);
        vectorScale_LE->setObjectName(QStringLiteral("vectorScale_LE"));
        vectorScale_LE->setGeometry(QRect(80, 150, 113, 21));
        layoutWidget_4 = new QWidget(groupBox_5);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 90, 271, 40));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        vectorRange_CB = new QCheckBox(layoutWidget_4);
        vectorRange_CB->setObjectName(QStringLiteral("vectorRange_CB"));

        horizontalLayout_12->addWidget(vectorRange_CB);

        vectorValueMin_LE = new QLineEdit(layoutWidget_4);
        vectorValueMin_LE->setObjectName(QStringLiteral("vectorValueMin_LE"));

        horizontalLayout_12->addWidget(vectorValueMin_LE);

        label_7 = new QLabel(layoutWidget_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_12->addWidget(label_7);

        vectorValueMax_LE = new QLineEdit(layoutWidget_4);
        vectorValueMax_LE->setObjectName(QStringLiteral("vectorValueMax_LE"));

        horizontalLayout_12->addWidget(vectorValueMax_LE);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(320, 40, 121, 16));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(330, 60, 111, 16));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(330, 80, 59, 16));
        label_34 = new QLabel(groupBox_5);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(330, 100, 59, 16));
        seedNumber_LE = new QLineEdit(groupBox_5);
        seedNumber_LE->setObjectName(QStringLiteral("seedNumber_LE"));
        seedNumber_LE->setGeometry(QRect(440, 60, 113, 21));
        seedRadius_LE = new QLineEdit(groupBox_5);
        seedRadius_LE->setObjectName(QStringLiteral("seedRadius_LE"));
        seedRadius_LE->setGeometry(QRect(380, 80, 113, 21));
        seedCenterX_LE = new QLineEdit(groupBox_5);
        seedCenterX_LE->setObjectName(QStringLiteral("seedCenterX_LE"));
        seedCenterX_LE->setGeometry(QRect(380, 100, 51, 21));
        seedCenterY_LE = new QLineEdit(groupBox_5);
        seedCenterY_LE->setObjectName(QStringLiteral("seedCenterY_LE"));
        seedCenterY_LE->setGeometry(QRect(440, 110, 51, 21));
        seedCenterZ_LE = new QLineEdit(groupBox_5);
        seedCenterZ_LE->setObjectName(QStringLiteral("seedCenterZ_LE"));
        seedCenterZ_LE->setGeometry(QRect(500, 110, 51, 21));
        label_35 = new QLabel(groupBox_5);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(320, 120, 71, 16));
        label_36 = new QLabel(groupBox_5);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(320, 140, 81, 16));
        label_37 = new QLabel(groupBox_5);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(310, 160, 141, 16));
        streamStepLength_LE = new QLineEdit(groupBox_5);
        streamStepLength_LE->setObjectName(QStringLiteral("streamStepLength_LE"));
        streamStepLength_LE->setGeometry(QRect(410, 140, 113, 21));
        streamIntStepLength_LE = new QLineEdit(groupBox_5);
        streamIntStepLength_LE->setObjectName(QStringLiteral("streamIntStepLength_LE"));
        streamIntStepLength_LE->setGeometry(QRect(440, 160, 113, 21));
        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 210, 271, 201));
        domain_CB = new QCheckBox(groupBox_4);
        domain_CB->setObjectName(QStringLiteral("domain_CB"));
        domain_CB->setGeometry(QRect(10, 20, 86, 20));
        domain_LW = new QListWidget(groupBox_4);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(domain_LW);
        __qlistwidgetitem->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem1->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem2->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem3->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem4->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem5->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem6->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem7->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem8->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem9 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem9->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem10 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem10->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem11 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem11->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem12 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem12->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem13 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem13->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem14 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem14->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem15 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem15->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem16 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem16->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem17 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem17->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem18 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem18->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem19 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem19->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem20 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem20->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem21 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem21->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem22 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem22->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem23 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem23->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem24 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem24->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem25 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem25->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem26 = new QListWidgetItem(domain_LW);
        __qlistwidgetitem26->setCheckState(Qt::Checked);
        domain_LW->setObjectName(QStringLiteral("domain_LW"));
        domain_LW->setGeometry(QRect(10, 40, 256, 151));
        domain_LW->setSelectionMode(QAbstractItemView::SingleSelection);
        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(11, 0, 561, 211));
        volume_CB = new QCheckBox(groupBox_3);
        volume_CB->setObjectName(QStringLiteral("volume_CB"));
        volume_CB->setGeometry(QRect(20, 70, 131, 20));
        volume_CB->setChecked(true);
        scalar_CB = new QCheckBox(groupBox_3);
        scalar_CB->setObjectName(QStringLiteral("scalar_CB"));
        scalar_CB->setGeometry(QRect(20, 30, 86, 20));
        scalar_CB->setChecked(true);
        scalarChoice = new QComboBox(groupBox_3);
        scalarChoice->setObjectName(QStringLiteral("scalarChoice"));
        scalarChoice->setGeometry(QRect(160, 50, 104, 26));
        scalarChoice->setEditable(false);
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 50, 141, 16));
        layoutWidget4 = new QWidget(groupBox_3);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(280, 20, 275, 191));
        verticalLayout_5 = new QVBoxLayout(layoutWidget4);
#ifndef Q_OS_MAC
        verticalLayout_5->setSpacing(-1);
#endif
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        isosurface_CB = new QCheckBox(layoutWidget4);
        isosurface_CB->setObjectName(QStringLiteral("isosurface_CB"));
        isosurface_CB->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(isosurface_CB);

        pushButton_5 = new QPushButton(layoutWidget4);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget4);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(pushButton_6);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_16 = new QLabel(layoutWidget4);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(label_16);

        lineEdit_19 = new QLineEdit(layoutWidget4);
        lineEdit_19->setObjectName(QStringLiteral("lineEdit_19"));
        lineEdit_19->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(lineEdit_19);

        label_17 = new QLabel(layoutWidget4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(label_17);

        lineEdit_20 = new QLineEdit(layoutWidget4);
        lineEdit_20->setObjectName(QStringLiteral("lineEdit_20"));
        lineEdit_20->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(lineEdit_20);

        lineEdit_21 = new QLineEdit(layoutWidget4);
        lineEdit_21->setObjectName(QStringLiteral("lineEdit_21"));
        lineEdit_21->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(lineEdit_21);

        lineEdit_22 = new QLineEdit(layoutWidget4);
        lineEdit_22->setObjectName(QStringLiteral("lineEdit_22"));
        lineEdit_22->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(lineEdit_22);


        verticalLayout_5->addLayout(horizontalLayout_7);

        listWidget_3 = new QListWidget(layoutWidget4);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        listWidget_3->setMaximumSize(QSize(275, 16777215));

        verticalLayout_5->addWidget(listWidget_3);

        layoutWidget5 = new QWidget(groupBox_3);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(20, 120, 239, 91));
        verticalLayout_2 = new QVBoxLayout(layoutWidget5);
#ifndef Q_OS_MAC
        verticalLayout_2->setSpacing(-1);
#endif
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_8 = new QCheckBox(layoutWidget5);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        verticalLayout_2->addWidget(checkBox_8);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_8 = new QLabel(layoutWidget5);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        lineEdit = new QLineEdit(layoutWidget5);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(layoutWidget5);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(lineEdit_2, 0, 2, 1, 1);

        lineEdit_3 = new QLineEdit(layoutWidget5);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(lineEdit_3, 0, 3, 1, 1);

        label_9 = new QLabel(layoutWidget5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(layoutWidget5);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(lineEdit_4, 1, 1, 1, 1);

        lineEdit_6 = new QLineEdit(layoutWidget5);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(lineEdit_6, 1, 2, 1, 1);

        lineEdit_5 = new QLineEdit(layoutWidget5);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(lineEdit_5, 1, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        layoutWidget6 = new QWidget(groupBox_3);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 90, 251, 28));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        scalarRange_CB = new QCheckBox(layoutWidget6);
        scalarRange_CB->setObjectName(QStringLiteral("scalarRange_CB"));

        horizontalLayout_11->addWidget(scalarRange_CB);

        scalarValueMin_LE = new QLineEdit(layoutWidget6);
        scalarValueMin_LE->setObjectName(QStringLiteral("scalarValueMin_LE"));
        scalarValueMin_LE->setEnabled(false);

        horizontalLayout_11->addWidget(scalarValueMin_LE);

        label_5 = new QLabel(layoutWidget6);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_11->addWidget(label_5);

        scalarValueMax_LE = new QLineEdit(layoutWidget6);
        scalarValueMax_LE->setObjectName(QStringLiteral("scalarValueMax_LE"));
        scalarValueMax_LE->setEnabled(false);

        horizontalLayout_11->addWidget(scalarValueMax_LE);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        SimpleView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SimpleView);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1222, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        SimpleView->setMenuBar(menubar);
        statusbar = new QStatusBar(SimpleView);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SimpleView->setStatusBar(statusbar);
        toolBar = new QToolBar(SimpleView);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setOrientation(Qt::Horizontal);
        toolBar->setIconSize(QSize(22, 22));
        SimpleView->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenFile_scalar);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionRefresh);
        menuFile->addAction(actionExit);
        toolBar->addAction(actionOpenFile_scalar);
        toolBar->addAction(actionOpenFile_vector);
        toolBar->addAction(actionOpenFile_domain);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionRefresh);

        retranslateUi(SimpleView);

        tabWidget->setCurrentIndex(0);
        information_Tab->setCurrentIndex(2);
        RGB_Stack->setCurrentIndex(1);
        alpha_Stack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimpleView);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleView)
    {
        SimpleView->setWindowTitle(QApplication::translate("SimpleView", "SimpleView", 0));
        actionOpenFile_scalar->setText(QApplication::translate("SimpleView", "Open File...", 0));
#ifndef QT_NO_TOOLTIP
        actionOpenFile_scalar->setToolTip(QApplication::translate("SimpleView", "Open scalar file", 0));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("SimpleView", "Exit", 0));
        actionPrint->setText(QApplication::translate("SimpleView", "Print", 0));
        actionRefresh->setText(QApplication::translate("SimpleView", "Help", 0));
        actionSave->setText(QApplication::translate("SimpleView", "Save", 0));
        actionOpenFile_vector->setText(QApplication::translate("SimpleView", "Open File...", 0));
#ifndef QT_NO_TOOLTIP
        actionOpenFile_vector->setToolTip(QApplication::translate("SimpleView", "Open vector file", 0));
#endif // QT_NO_TOOLTIP
        actionOpenFile_domain->setText(QApplication::translate("SimpleView", "Open File...", 0));
#ifndef QT_NO_TOOLTIP
        actionOpenFile_domain->setToolTip(QApplication::translate("SimpleView", "Open vector file", 0));
#endif // QT_NO_TOOLTIP
        rowcolScalar->setText(QApplication::translate("SimpleView", "Colums number", 0));
        inputFileScalar->setText(QApplication::translate("SimpleView", "input file name", 0));
        label_28->setText(QApplication::translate("SimpleView", "x range:", 0));
        label_29->setText(QApplication::translate("SimpleView", "y range:", 0));
        xMinMaxScalar->setText(QApplication::translate("SimpleView", "xmin - xmax", 0));
        label_24->setText(QApplication::translate("SimpleView", "Input file:", 0));
        label_26->setText(QApplication::translate("SimpleView", "# of columns:", 0));
        yMinMaxScalar->setText(QApplication::translate("SimpleView", "ymin - ymax", 0));
        label_30->setText(QApplication::translate("SimpleView", "z range:", 0));
        zMinMaxScalar->setText(QApplication::translate("SimpleView", "zmin - zmax", 0));
        QTableWidgetItem *___qtablewidgetitem = scalar_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SimpleView", "Min", 0));
        QTableWidgetItem *___qtablewidgetitem1 = scalar_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SimpleView", "Max", 0));
        QTableWidgetItem *___qtablewidgetitem2 = scalar_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SimpleView", "Avg", 0));
        information_Tab->setTabText(information_Tab->indexOf(tab_3), QApplication::translate("SimpleView", "Scalar info", 0));
        rowcolVector->setText(QApplication::translate("SimpleView", "Colums number", 0));
        inputFileVector->setText(QApplication::translate("SimpleView", "input file name", 0));
        label_31->setText(QApplication::translate("SimpleView", "x range:", 0));
        label_32->setText(QApplication::translate("SimpleView", "y range:", 0));
        xMinMaxVector->setText(QApplication::translate("SimpleView", "xmin - xmax", 0));
        label_25->setText(QApplication::translate("SimpleView", "Input file:", 0));
        label_27->setText(QApplication::translate("SimpleView", "# of columns:", 0));
        yMinMaxVector->setText(QApplication::translate("SimpleView", "ymin - ymax", 0));
        label_33->setText(QApplication::translate("SimpleView", "z range:", 0));
        zMinMaxVector->setText(QApplication::translate("SimpleView", "zmin - zmax", 0));
        QTableWidgetItem *___qtablewidgetitem3 = vector_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("SimpleView", "Min", 0));
        QTableWidgetItem *___qtablewidgetitem4 = vector_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("SimpleView", "Max", 0));
        QTableWidgetItem *___qtablewidgetitem5 = vector_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("SimpleView", "Avg", 0));
        information_Tab->setTabText(information_Tab->indexOf(tab_4), QApplication::translate("SimpleView", "Vector info", 0));
        rowcolDomain->setText(QApplication::translate("SimpleView", "Colums number", 0));
        inputFileDomain->setText(QApplication::translate("SimpleView", "input file name", 0));
        label_38->setText(QApplication::translate("SimpleView", "x range:", 0));
        label_39->setText(QApplication::translate("SimpleView", "y range:", 0));
        xMinMaxDomain->setText(QApplication::translate("SimpleView", "xmin - xmax", 0));
        label_40->setText(QApplication::translate("SimpleView", "Input file:", 0));
        label_41->setText(QApplication::translate("SimpleView", "# of columns:", 0));
        yMinMaxDomain->setText(QApplication::translate("SimpleView", "ymin - ymax", 0));
        label_42->setText(QApplication::translate("SimpleView", "z range:", 0));
        zMinMaxDomain->setText(QApplication::translate("SimpleView", "zmin - zmax", 0));
        QTableWidgetItem *___qtablewidgetitem6 = domain_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("SimpleView", "Min", 0));
        QTableWidgetItem *___qtablewidgetitem7 = domain_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("SimpleView", "Max", 0));
        QTableWidgetItem *___qtablewidgetitem8 = domain_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("SimpleView", "Avg", 0));
        information_Tab->setTabText(information_Tab->indexOf(tab_5), QApplication::translate("SimpleView", "Domain info", 0));
        groupBox_2->setTitle(QApplication::translate("SimpleView", "General", 0));
        axis_CB->setText(QApplication::translate("SimpleView", "Axis", 0));
        scalarBar_CB->setText(QApplication::translate("SimpleView", "Scale bar", 0));
        extract_CB->setText(QApplication::translate("SimpleView", "Extraction", 0));
        outline_CB->setText(QApplication::translate("SimpleView", "Outline", 0));
        label_18->setText(QApplication::translate("SimpleView", "xmin:", 0));
        label_19->setText(QApplication::translate("SimpleView", "xmax:", 0));
        label_21->setText(QApplication::translate("SimpleView", "ymin:", 0));
        label_20->setText(QApplication::translate("SimpleView", "ymax:", 0));
        label_23->setText(QApplication::translate("SimpleView", "zmin:", 0));
        label_22->setText(QApplication::translate("SimpleView", "zmax:", 0));
        groupBox->setTitle(QApplication::translate("SimpleView", "Color", 0));
        RGB_Combo->clear();
        RGB_Combo->insertItems(0, QStringList()
         << QApplication::translate("SimpleView", "RGB default", 0)
         << QApplication::translate("SimpleView", "RGB scalar", 0)
         << QApplication::translate("SimpleView", "RGB vector", 0)
        );
        RGBAdd_PB->setText(QApplication::translate("SimpleView", "Add", 0));
        RGBDelete_PB->setText(QApplication::translate("SimpleView", "Delete", 0));
        label_12->setText(QApplication::translate("SimpleView", "Value:", 0));
        label_13->setText(QApplication::translate("SimpleView", "RGB:", 0));
        QTableWidgetItem *___qtablewidgetitem9 = RGBScalar_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("SimpleView", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem10 = RGBScalar_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("SimpleView", "R", 0));
        QTableWidgetItem *___qtablewidgetitem11 = RGBScalar_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("SimpleView", "G", 0));
        QTableWidgetItem *___qtablewidgetitem12 = RGBScalar_Table->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("SimpleView", "B", 0));
        QTableWidgetItem *___qtablewidgetitem13 = RGBVector_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("SimpleView", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem14 = RGBVector_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QApplication::translate("SimpleView", "R", 0));
        QTableWidgetItem *___qtablewidgetitem15 = RGBVector_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QApplication::translate("SimpleView", "G", 0));
        QTableWidgetItem *___qtablewidgetitem16 = RGBVector_Table->horizontalHeaderItem(3);
        ___qtablewidgetitem16->setText(QApplication::translate("SimpleView", "B", 0));
        alpha_Combo->clear();
        alpha_Combo->insertItems(0, QStringList()
         << QApplication::translate("SimpleView", "Alpha default", 0)
         << QApplication::translate("SimpleView", "Alpha scalar", 0)
         << QApplication::translate("SimpleView", "Alpha vector", 0)
        );
        alphaAdd_PB->setText(QApplication::translate("SimpleView", "Add", 0));
        alphaDelete_PB->setText(QApplication::translate("SimpleView", "Delete", 0));
        label_14->setText(QApplication::translate("SimpleView", "Value:", 0));
        label_15->setText(QApplication::translate("SimpleView", "Alpha:", 0));
        QTableWidgetItem *___qtablewidgetitem17 = alphaScalar_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("SimpleView", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem18 = alphaScalar_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QApplication::translate("SimpleView", "Alpha", 0));
        QTableWidgetItem *___qtablewidgetitem19 = alphaVector_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("SimpleView", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem20 = alphaVector_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem20->setText(QApplication::translate("SimpleView", "Alpha", 0));
        groupBox_5->setTitle(QApplication::translate("SimpleView", "Vector", 0));
        vector_CB->setText(QApplication::translate("SimpleView", "Vector", 0));
        streamline_CB->setText(QApplication::translate("SimpleView", "Streamline", 0));
        label_2->setText(QApplication::translate("SimpleView", "Columns to be plotted:", 0));
        label_3->setText(QApplication::translate("SimpleView", "x, y, z:", 0));
        label_4->setText(QApplication::translate("SimpleView", "Scale:", 0));
        vectorRange_CB->setText(QApplication::translate("SimpleView", "Magnitude range:", 0));
        label_7->setText(QApplication::translate("SimpleView", "to", 0));
        label_6->setText(QApplication::translate("SimpleView", "Point source seeds:", 0));
        label_10->setText(QApplication::translate("SimpleView", "Number of points:", 0));
        label_11->setText(QApplication::translate("SimpleView", "Radius:", 0));
        label_34->setText(QApplication::translate("SimpleView", "Center:", 0));
        label_35->setText(QApplication::translate("SimpleView", "Sreamline:", 0));
        label_36->setText(QApplication::translate("SimpleView", "Max steps :", 0));
        label_37->setText(QApplication::translate("SimpleView", "Integrate step length:", 0));
        groupBox_4->setTitle(QApplication::translate("SimpleView", "Domain plot", 0));
        domain_CB->setText(QApplication::translate("SimpleView", "Domain", 0));

        const bool __sortingEnabled = domain_LW->isSortingEnabled();
        domain_LW->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = domain_LW->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("SimpleView", "Substrate", 0));
        QListWidgetItem *___qlistwidgetitem1 = domain_LW->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("SimpleView", "R1+", 0));
        QListWidgetItem *___qlistwidgetitem2 = domain_LW->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("SimpleView", "R1-", 0));
        QListWidgetItem *___qlistwidgetitem3 = domain_LW->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("SimpleView", "R2+", 0));
        QListWidgetItem *___qlistwidgetitem4 = domain_LW->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("SimpleView", "R2-", 0));
        QListWidgetItem *___qlistwidgetitem5 = domain_LW->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("SimpleView", "R3+", 0));
        QListWidgetItem *___qlistwidgetitem6 = domain_LW->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("SimpleView", "R3-", 0));
        QListWidgetItem *___qlistwidgetitem7 = domain_LW->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("SimpleView", "R4+", 0));
        QListWidgetItem *___qlistwidgetitem8 = domain_LW->item(8);
        ___qlistwidgetitem8->setText(QApplication::translate("SimpleView", "R4-", 0));
        QListWidgetItem *___qlistwidgetitem9 = domain_LW->item(9);
        ___qlistwidgetitem9->setText(QApplication::translate("SimpleView", "O1+", 0));
        QListWidgetItem *___qlistwidgetitem10 = domain_LW->item(10);
        ___qlistwidgetitem10->setText(QApplication::translate("SimpleView", "O1-", 0));
        QListWidgetItem *___qlistwidgetitem11 = domain_LW->item(11);
        ___qlistwidgetitem11->setText(QApplication::translate("SimpleView", "O2+", 0));
        QListWidgetItem *___qlistwidgetitem12 = domain_LW->item(12);
        ___qlistwidgetitem12->setText(QApplication::translate("SimpleView", "O2-", 0));
        QListWidgetItem *___qlistwidgetitem13 = domain_LW->item(13);
        ___qlistwidgetitem13->setText(QApplication::translate("SimpleView", "O3+", 0));
        QListWidgetItem *___qlistwidgetitem14 = domain_LW->item(14);
        ___qlistwidgetitem14->setText(QApplication::translate("SimpleView", "O3-", 0));
        QListWidgetItem *___qlistwidgetitem15 = domain_LW->item(15);
        ___qlistwidgetitem15->setText(QApplication::translate("SimpleView", "O4+", 0));
        QListWidgetItem *___qlistwidgetitem16 = domain_LW->item(16);
        ___qlistwidgetitem16->setText(QApplication::translate("SimpleView", "O4-", 0));
        QListWidgetItem *___qlistwidgetitem17 = domain_LW->item(17);
        ___qlistwidgetitem17->setText(QApplication::translate("SimpleView", "O5+", 0));
        QListWidgetItem *___qlistwidgetitem18 = domain_LW->item(18);
        ___qlistwidgetitem18->setText(QApplication::translate("SimpleView", "O5-", 0));
        QListWidgetItem *___qlistwidgetitem19 = domain_LW->item(19);
        ___qlistwidgetitem19->setText(QApplication::translate("SimpleView", "O6+", 0));
        QListWidgetItem *___qlistwidgetitem20 = domain_LW->item(20);
        ___qlistwidgetitem20->setText(QApplication::translate("SimpleView", "O6-", 0));
        QListWidgetItem *___qlistwidgetitem21 = domain_LW->item(21);
        ___qlistwidgetitem21->setText(QApplication::translate("SimpleView", "T1+", 0));
        QListWidgetItem *___qlistwidgetitem22 = domain_LW->item(22);
        ___qlistwidgetitem22->setText(QApplication::translate("SimpleView", "T1-", 0));
        QListWidgetItem *___qlistwidgetitem23 = domain_LW->item(23);
        ___qlistwidgetitem23->setText(QApplication::translate("SimpleView", "T2+", 0));
        QListWidgetItem *___qlistwidgetitem24 = domain_LW->item(24);
        ___qlistwidgetitem24->setText(QApplication::translate("SimpleView", "T2-", 0));
        QListWidgetItem *___qlistwidgetitem25 = domain_LW->item(25);
        ___qlistwidgetitem25->setText(QApplication::translate("SimpleView", "T3+", 0));
        QListWidgetItem *___qlistwidgetitem26 = domain_LW->item(26);
        ___qlistwidgetitem26->setText(QApplication::translate("SimpleView", "T3-", 0));
        domain_LW->setSortingEnabled(__sortingEnabled);

        groupBox_3->setTitle(QApplication::translate("SimpleView", "Scalar", 0));
        volume_CB->setText(QApplication::translate("SimpleView", "Volume rendering", 0));
        scalar_CB->setText(QApplication::translate("SimpleView", "Scalar", 0));
        label->setText(QApplication::translate("SimpleView", "Column to be plotted:", 0));
        isosurface_CB->setText(QApplication::translate("SimpleView", "Isosurface", 0));
        pushButton_5->setText(QApplication::translate("SimpleView", "Add", 0));
        pushButton_6->setText(QApplication::translate("SimpleView", "Delete", 0));
        label_16->setText(QApplication::translate("SimpleView", "Value:", 0));
        label_17->setText(QApplication::translate("SimpleView", "RGB:", 0));
        checkBox_8->setText(QApplication::translate("SimpleView", "Slice 2D plane", 0));
        label_8->setText(QApplication::translate("SimpleView", "Point:", 0));
        label_9->setText(QApplication::translate("SimpleView", "Normal:", 0));
        scalarRange_CB->setText(QApplication::translate("SimpleView", "Value range:", 0));
        label_5->setText(QApplication::translate("SimpleView", "to", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SimpleView", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SimpleView", "Tab 2", 0));
        menuFile->setTitle(QApplication::translate("SimpleView", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class SimpleView: public Ui_SimpleView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEVIEW_H
