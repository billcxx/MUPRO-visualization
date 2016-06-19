/*=========================================================================
 
 Program:   Visualization Toolkit
 Module:    SimpleView.h
 Language:  C++
 
 Copyright 2009 Sandia Corporation.
 Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 license for use of this work by or on behalf of the
 U.S. Government. Redistribution and use in source and binary forms, with
 or without modification, are permitted provided that this Notice and any
 statement of authorship are reproduced on all copies.
 
 =========================================================================*/
#ifndef SimpleView_H
#define SimpleView_H

#include "vtkSmartPointer.h"    // Required for smart pointer internal ivars.
#include <vtkQtTableView.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QListWidget>
#include <QListView>
#include <iostream>
#include <fstream>
#include <vtkCamera.h>
#include <vtkAxesActor.h>
#include <vtkSmartPointer.h>
#include <vtkScalarBarActor.h>
#include <vtkActor.h>
#include <vtkVolume.h>
#include <vtkExtractVOI.h>
#include <vtkStreamLine.h>
#include "qcustomplot.h"

#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QtMath>

// Forward Qt class declarations
class Ui_SimpleView;

// Forward VTK class declarations
class vtkQtTableView;


class SimpleView : public QMainWindow
{
    Q_OBJECT
    
public:
    
    // Constructor/Destructor
    SimpleView();
    ~SimpleView();
    
    public slots:
    
    virtual void slotOpenFile_scalar();
    virtual void slotOpenFile_vector();
    virtual void slotOpenFile_domain();
    virtual void slotExit();
    virtual void slotUpdate();
    virtual void slotClear();
    virtual void slotUpdateCamera1();
    virtual void slotUpdateCamera2();
    virtual void slotUpdateCamera3();
    virtual void slotUpdateCamera4();
    virtual void slotUpdateCamera5();
    virtual void slotUpdateCamera6();
    
    void figurePlot();
    
    void on_scalarChoice_currentIndexChanged(int index);
    void on_vectorChoice_activated(int index);
    void on_axis_CB_stateChanged(int state);
    void on_outline_CB_stateChanged(int state);
    void on_scalar_CB_stateChanged(int state);
    void on_volume_CB_stateChanged(int state);
    void on_scalarBar_CB_stateChanged(int state);
    void on_vector_CB_stateChanged(int state);
    void on_extract_CB_stateChanged(int state);
    void on_xmin_LE_editingFinished();
    void on_ymin_LE_editingFinished();
    void on_zmin_LE_editingFinished();
    void on_xmax_LE_editingFinished();
    void on_ymax_LE_editingFinished();
    void on_zmax_LE_editingFinished();
    void on_scalarRange_CB_stateChanged(int state);
    void on_RGB_Combo_currentIndexChanged(int index);
    void on_alpha_Combo_currentIndexChanged(int index);
    void on_RGBAdd_PB_released();
    void on_RGBDelete_PB_released();
    void on_alphaAdd_PB_released();
    void on_alphaDelete_PB_released();
    void on_domain_LW_itemChanged(QListWidgetItem *item);
    void on_domain_CB_stateChanged(int state);
    void updateVTK(std::string fileNameScalar,std::string fileNameVector);
    
    
    void drawDomain(std::string domainName);
    int loadData(QString filedir);
    int domainProcessing(QString filedir);
    int domainType(double px,double py, double pz);
    double getMin(double *list,int length);
    double getMax(double *list,int length);
    double getAvg(double *list,int length);
    void outputScalar(int columnNumber,int x,int y, int z);
    void outputVector(int colX,int colY,int colZ,int x,int y,int z);
    
    void updateCamera(int choice);
    void updateExtraction(int x,int y, int z);
    void saveImage();
    void slotSwitch3D();
    void slotSwitch1D();
    void setup1DFigure(QCustomPlot *customPlot);
    


    void on_plot1DGeneral_LW_currentRowChanged(int index);
    void on_plot1DXGrid_CB_stateChanged(int state);
    void on_plot1DYGrid_CB_stateChanged(int state);
    void on_plot1DAutoTickX1_CB_stateChanged(int state);
    void on_plot1DAutoTickX2_CB_stateChanged(int state);
    void on_plot1DAutoTickY1_CB_stateChanged(int state);
    void on_plot1DAutoTickY2_CB_stateChanged(int state);
    void on_plot1DAxisX1_CB_stateChanged(int state);
    void on_plot1DAxisX2_CB_stateChanged(int state);
    void on_plot1DAxisY1_CB_stateChanged(int state);
    void on_plot1DAxisY2_CB_stateChanged(int state);
    void on_plot1DTickLabelX1_CB_stateChanged(int state);
    void on_plot1DTickLabelY1_CB_stateChanged(int state);
    void on_plot1DTickLabelX2_CB_stateChanged(int state);
    void on_plot1DTickLabelY2_CB_stateChanged(int state);
    void on_plot1DLegend_CB_stateChanged(int state);
    void on_plot1DFont_CB_stateChanged(int state);
    void on_isosurface_CB_stateChanged(int state);
    void on_isoAdd_PB_released();
    void on_isoDelete_PB_released();
    void drawIsoSurface(vtkAlgorithmOutput * readerScalarPort);
    void on_isosurface_LW_itemChanged(QListWidgetItem *item);
protected:
    
    protected slots:
    
private:
    
    vtkSmartPointer<vtkQtTableView> TableView= vtkSmartPointer<vtkQtTableView>::New();
    int columns;
    std::string scalarName,vectorName;
    // Designer form
    Ui_SimpleView *ui;
    QString printstatus;
    double cameraPosition[3],cameraFocal[3];
    int xmin=0,xmax=0,ymin=0,ymax=0,zmin=0,zmax=0;
    int xminAll=0,xmaxAll=0,yminAll=0,ymaxAll=0,zminAll=0,zmaxAll=0;
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    double **vtkData;
    double RGBPoint;
    bool reset=true;
    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkActor> outlineScalarActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> outlineVectorActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> outlineDomainActor = vtkSmartPointer<vtkActor>::New();
//    vtkSmartPointer<vtkActor> actorVector = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actorIsosurface = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkScalarBarActor> scalarScaleBarActor = vtkSmartPointer<vtkScalarBarActor>::New();
    vtkSmartPointer<vtkScalarBarActor> vectorScaleBarActor = vtkSmartPointer<vtkScalarBarActor>::New();
//    vtkSmartPointer<vtkVolume> actorScalar = vtkSmartPointer<vtkVolume>::New();
//    vtkSmartPointer<vtkActor> actorCutter = vtkSmartPointer<vtkActor>::New();
    vtkActor *actorCutter = vtkActor::New();
    vtkActor *actorVector = vtkActor::New();
    vtkActor *actorStream = vtkActor::New();
    vtkVolume *actorScalar = vtkVolume::New();
    std::vector<vtkActor *> actorDomain;
    QVector<vtkActor*> actorIso;
    QVector<Qt::PenStyle> lineStyleList;
    QVector<QCPScatterStyle> scatterStyle;
    QVector<QPen> lineStyle;
    QVector< QVector<double> > rgbWidth;
    QVector<QCPScatterStyle::ScatterShape> scatterStyleList;
    

};

#endif // SimpleView_H
