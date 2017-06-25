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

#define piValue 3.141592653589

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
#include <vtkOrientationMarkerWidget.h>
#include <vtkScalarBarWidget.h>
#include <vtkDataSetReader.h>
#include <vtkStructuredPointsReader.h>
#include <vtkStructuredPoints.h>
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
    bool scalar,vector,domain;
    int tempX=0,tempY=0,tempZ=0;
    int scalarColumn,vectorColumn;

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
    void on_vectorChoice_currentIndexChanged(int index);
    void on_axis_CB_stateChanged(int state);
    void on_outline_CB_stateChanged(int state);
    void on_scalar_CB_stateChanged(int state);
    void on_volume_CB_stateChanged(int state);
	void on_scalarLegendBar_CB_stateChanged(int state);
	void on_vectorLegendBar_CB_stateChanged(int state);
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
	void on_vo2Domain_LW_itemChanged(QListWidgetItem *item);
    void on_domain_CB_stateChanged(int state);
    void on_slice_CB_stateChanged(int state);
    void on_streamline_CB_stateChanged(int state);
    void on_vectorRange_CB_stateChanged(int state);
    void updateVTK(std::string fileNameScalar,std::string fileNameVector);
    
    
    void drawDomain(std::string domainName);
	void drawVO2Domain(std::string domainName);
    int loadData(QString filedir);
    int domainProcessing(QString filedir);
    int domainType(double px,double py, double pz);
	int vo2DomainType(double u1, double u2, double u3, double u4, double n1, double n2, double n3, double n4);
    double getMin(double *list,int length);
    double getMax(double *list,int length);
    double getAvg(double *list,int length);
    void outputScalar(QString path,int columnNumber,int x,int y, int z);
    void outputVector(QString path,int colX,int colY,int colZ,int x,int y,int z);
    
    void updateCamera(int choice);
    void updateExtraction(int x,int y, int z);
    void saveImage();
    void slotSwitch3D();
    void slotSwitch1D();
    void slotOutputStatus();
    QString slotLoadStatus();
    void slotBatch3D();
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
	void on_scalarLegend_LE_textChanged(const QString & text);
	void on_vectorLegend_LE_textChanged(const QString & text);
	void on_domainStdAngle_LE_editingFinished();
	void on_domainStdValue_LE_editingFinished();
	void on_domainRePlot_PB_released();
	void on_outlineWidth_LE_editingFinished();
	void on_domain_Combo_currentIndexChanged(int index);
	void on_domainColor_Combo_currentIndexChanged(int index);
	void on_opacityDomain_Combo_currentIndexChanged(int index);


	void on_vectorColorMode_Combo_currentIndexChanged(int index);
	double * getRGB(double px, double py, double pz, double magnitudeRange[2], double xyRange[2], double zRange[2]);
	double * convertHSLToRGB(double hue, double saturation, double lightness);
	double rescale(double value, double range[2]);
    void drawIsoSurface(vtkAlgorithmOutput * readerScalarPort);
    void on_isosurface_LW_itemChanged(QListWidgetItem *item);
    void on_vectorGlyph_CB_stateChanged(int state);
    void on_cameraSet_PB_released();
	void on_cameraGet_PB_released();
    void outputStatus(QFileInfo filedir);
    void loadStatus(QFileInfo filedir);
    void outputImage(QString load);
    void outputDomain(QString filedir,int x, int y, int z);
	void outputVO2Domain(QString filedir, int x, int y, int z);
    
protected:
    
    protected slots:
    
private:
    
    vtkSmartPointer<vtkQtTableView> TableView= vtkSmartPointer<vtkQtTableView>::New();
    int columns;
    std::string scalarName,vectorName,domainName;
    QFileInfo scalarDir,vectorDir,domainDir;
	double** domainRGB, **domainRGBHold,** vo2DomainRGB, **vo2DomainRGBHold;
    // Designer form
    Ui_SimpleView *ui;
    QString printstatus;
	bool updateFlag = false;
	double cameraPosition[3], cameraFocal[3], pointFraction[27] = { 0.0 };
    QVector<QString> domainList ,vo2DomainList;
    int xmin=0,xmax=0,ymin=0,ymax=0,zmin=0,zmax=0;
	int outlineWidth = 1;
    int xminAll=0,xmaxAll=0,yminAll=0,ymaxAll=0,zminAll=0,zmaxAll=0;
	double domainStandardValue = 0.3, domainStandardAngle = 180.0, domainStandardAngleRad=180.0*3.141592653589/180;
	double M1mod = 0.1, M2mod = 0.1, M1ang = 10.0*3.141592653589 / 180, M2ang = 10.0*3.141592653589 / 180;
	double domainOrth[27][3] = {
		{0,0,0},
		{1/std::sqrt(3),1/std::sqrt(3),1/std::sqrt(3) },
		{-1/std::sqrt(3),-1 / std::sqrt(3),-1 / std::sqrt(3) },
		{ -1 / std::sqrt(3),1/std::sqrt(3),1/std::sqrt(3) },
		{ 1/std::sqrt(3),-1 / std::sqrt(3),-1 / std::sqrt(3) },
		{ -1 / std::sqrt(3),-1 / std::sqrt(3),1/std::sqrt(3) },
		{ 1/std::sqrt(3),1/std::sqrt(3),-1 / std::sqrt(3) },
		{ 1/std::sqrt(3),-1 / std::sqrt(3),1/std::sqrt(3) },
		{ -1 / std::sqrt(3),1/std::sqrt(3),-1 / std::sqrt(3) },
		{ 1/std::sqrt(2),1/std::sqrt(2),0},
		{-1 / std::sqrt(2),-1 / std::sqrt(2),0},
		{ 1/std::sqrt(2),-1 / std::sqrt(2),0},
		{ -1 / std::sqrt(2),1/std::sqrt(2),0},
		{ 1/std::sqrt(2),0,1/std::sqrt(2) },
		{ -1 / std::sqrt(2),0,-1 / std::sqrt(2) },
		{ 1/std::sqrt(2),0,-1 / std::sqrt(2) },
		{ -1 / std::sqrt(2),0,1/std::sqrt(2) },
		{0,1/std::sqrt(2),1/std::sqrt(2) },
		{0,-1 / std::sqrt(2),-1 / std::sqrt(2) },
		{0,1/std::sqrt(2),-1 / std::sqrt(2) },
		{0,-1 / std::sqrt(2),1/std::sqrt(2) },
		{1,0,0},
		{-1,0,0},
		{0,1,0},
		{0,-1,0},
		{0,0,1},
		{0,0,-1}
	};
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    double **vtkData;
    double RGBPoint;
    bool reset=true;
    bool data2Dx=false,data2Dy=false,data2Dz=false;
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
    vtkSmartPointer<vtkActor> actorCutter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actorVector = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actorStream = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkActor> vectorRTActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkVolume> actorScalar = vtkSmartPointer<vtkVolume>::New();
	vtkSmartPointer<vtkStructuredPointsReader> readerVectorOrigin = vtkSmartPointer<vtkStructuredPointsReader>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> widget =vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	vtkSmartPointer<vtkOrientationMarkerWidget> vectorOrientationLegend = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	vtkSmartPointer<vtkScalarBarWidget> scalarLegendWidget = vtkSmartPointer<vtkScalarBarWidget>::New();
	vtkSmartPointer<vtkScalarBarWidget> vectorLegendWidget = vtkSmartPointer<vtkScalarBarWidget>::New();
    std::vector<vtkActor *> actorDomain;
    QVector<bool> existDomain;
    QVector<vtkActor*> actorIso;
    QVector<Qt::PenStyle> lineStyleList;
    QVector<QCPScatterStyle> scatterStyle;
    QVector<QPen> lineStyle;
    QVector< QVector<double> > rgbWidth;
    QVector<QCPScatterStyle::ScatterShape> scatterStyleList;

    

};

#endif // SimpleView_H
