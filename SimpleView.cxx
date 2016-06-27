/*
 * Copyright 2007 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */


#include "ui_SimpleView.h"
#include "SimpleView.h"
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkDataObjectToTable.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkVectorText.h>
#include <vtkVolumeProperty.h>
#include <vtkAxesActor.h>
#include <vtkCubeAxesActor.h>
#include <vtkTransform.h>
#include <vtkCaptionActor2D.h>
#include <vtkProperty2D.h>
#include <vtkOutlineFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkDataArray.h>
#include <vtkProperty.h>
#include <vtkScalarBarActor.h>
#include <vtkTextProperty.h>
#include <vtkExtractVOI.h>
#include <vtkImageData.h>
#include <vtkArrowSource.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>
#include <vtkPointData.h>
#include <vtkDataSetAttributes.h>
#include <vtkRendererCollection.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkGeometryFilter.h>
#include <vtkExtractSelectedThresholds.h>
#include <vtkThresholdPoints.h>
#include <vtkImageMagnitude.h>
#include <vtkSelectionNode.h>
#include <vtkDoubleArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridVolumeRayCastMapper.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkUnstructuredGridVolumeZSweepMapper.h>
#include <vtkVolumeMapper.h>
#include <vtkExtractSelection.h>
#include <vtkSelection.h>
#include <vtkImageData.h>
#include <vtkImageCast.h>
#include <sstream>
#include <vtkSmartVolumeMapper.h>
#include <vtkThreshold.h>
#include <vtkDataSetTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkHedgeHog.h>
#include <vtkPointSource.h>
#include <vtkCompositeTransferFunctionItem.h>
#include <vtkStreamTracer.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkContourFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataNormals.h>
#include <vtkStreamLine.h>
#include <vtkHAVSVolumeMapper.h>
#include <vtkUnstructuredGridVolumeZSweepMapper.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "batch3D.h"




#define VTK_CREATE(type, name) \
vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

// Constructor
SimpleView::SimpleView()
{
//    QString styleSheet = QString("font: 15px Arial;").arg(QApplication::font().pointSize());
//    this->setStyleSheet(styleSheet);
    this->ui = new Ui_SimpleView;
    this->ui->setupUi(this);
    this->ui->vectorChoice->setView(new QListView());
    this->ui->RGB_Combo->setView(new QListView());
    this->ui->alpha_Combo->setView(new QListView());
    this->ui->scalarChoice->setView(new QListView());
//    this->ui->plot1DGeneral_LW->SetView
    
    for(int nr = 0; nr < 27; nr++){
        actorDomain.push_back(vtkActor::New());
        existDomain.push_back(false);
    }
    this->ui->qvtkWidget->setAutomaticImageCacheEnabled(1);
    VTK_CREATE(vtkTransform,transform);
    VTK_CREATE(vtkRenderer,renderer);
    transform->Translate(-5,-5.0,-5.0);
    axes->SetUserTransform(transform);
    axes->SetScale(10);
    axes->SetTotalLength(10,10,10);
    axes->GetXAxisCaptionActor2D()->GetProperty()->SetColor(0,0,0);
    axes->GetYAxisCaptionActor2D()->GetProperty()->SetColor(0,0,0);
    axes->GetZAxisCaptionActor2D()->GetProperty()->SetColor(0,0,0);
    
    // Set up action signals and slots
    connect(this->ui->actionOpenFile_scalar, SIGNAL(triggered()), this, SLOT(slotOpenFile_scalar()));
    connect(this->ui->actionOpenFile_vector, SIGNAL(triggered()), this, SLOT(slotOpenFile_vector()));
    connect(this->ui->actionOpenFile_domain, SIGNAL(triggered()), this, SLOT(slotOpenFile_domain()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    connect(this->ui->actionRefresh,SIGNAL(triggered()),this,SLOT(slotUpdate()));
    connect(this->ui->actionClear,SIGNAL(triggered()),this,SLOT(slotClear()));
    connect(this->ui->actionSave , SIGNAL(triggered()), this, SLOT(saveImage()));
    connect(this->ui->actionRotateToXP , SIGNAL(triggered()), this, SLOT(slotUpdateCamera1()));
    connect(this->ui->actionRotateToXN , SIGNAL(triggered()), this, SLOT(slotUpdateCamera2()));
    connect(this->ui->actionRotateToYP , SIGNAL(triggered()), this, SLOT(slotUpdateCamera3()));
    connect(this->ui->actionRotateToYN , SIGNAL(triggered()), this, SLOT(slotUpdateCamera4()));
    connect(this->ui->actionRotateToZP , SIGNAL(triggered()), this, SLOT(slotUpdateCamera5()));
    connect(this->ui->actionRotateToZN , SIGNAL(triggered()), this, SLOT(slotUpdateCamera6()));
    connect(this->ui->action1D,SIGNAL(triggered()), this, SLOT(slotSwitch1D()));
    connect(this->ui->action3D,SIGNAL(triggered()), this, SLOT(slotSwitch3D()));
    connect(this->ui->actionOutputStatus,SIGNAL(triggered()),this,SLOT(slotOutputStatus()));
    connect(this->ui->actionLoadStatus, SIGNAL(triggered()), this, SLOT(slotLoadStatus()));
    connect(this->ui->actionBatch3D,SIGNAL(triggered()),this,SLOT(slotBatch3D()));

    
    
    connect(this->ui->file1_Widget,SIGNAL(figureReplot()),this,SLOT(figurePlot()));
    connect(this->ui->file2_Widget,SIGNAL(figureReplot()),this,SLOT(figurePlot()));
    
//    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
//        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
//        qDebug()<<"creating new renderer";
//    }else{
//        renderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
//    }
    scatterStyle<<QCPScatterStyle::ssNone<<QCPScatterStyle::ssDot <<QCPScatterStyle::ssCross<<QCPScatterStyle::ssPlus<<QCPScatterStyle::ssCircle<<QCPScatterStyle::ssDisc<<QCPScatterStyle::ssSquare<<QCPScatterStyle::ssDiamond<<QCPScatterStyle::ssStar<<QCPScatterStyle::ssTriangle<<QCPScatterStyle::ssTriangleInverted<<QCPScatterStyle::ssCrossSquare<<QCPScatterStyle::ssPlusSquare<<QCPScatterStyle::ssCrossCircle<<QCPScatterStyle::ssPlusCircle;
    lineStyleList<<Qt::PenStyle::SolidLine<<Qt::PenStyle::DashLine<<Qt::PenStyle::DotLine<<Qt::PenStyle::DashDotLine<<Qt::PenStyle::DashDotDotLine;
    
    
    double** domainRGB;
    
    domainRGB=new double*[27];
    for (int i=0;i<27;++i){
        domainRGB[i] = new double[3];
    }
    domainRGB[0][0]=0.752912;domainRGB[0][1]=0.752912;domainRGB[0][2]=0.752912; //sub
    domainRGB[1][0]=0;domainRGB[1][1]=0;domainRGB[1][2]=1;  //R1+
    domainRGB[2][0]=0.46;domainRGB[2][1]=0.7175;domainRGB[2][2]=0.8135; //R1-
    domainRGB[3][0]=0;domainRGB[2][1]=0.1537870;domainRGB[3][2]=0.0; //R2+
    domainRGB[4][0]=0;domainRGB[4][1]=1;domainRGB[4][2]=0; //R2-
    domainRGB[5][0]=1;domainRGB[5][1]=0;domainRGB[5][2]=0; //R3+
    domainRGB[6][0]=1;domainRGB[6][1]=0.566921;domainRGB[6][2]=0.633741; //R3-
    domainRGB[7][0]=1;domainRGB[7][1]=0.418685;domainRGB[7][2]=0; //R4+
    domainRGB[8][0]=1;domainRGB[8][1]=1;domainRGB[8][2]=0; //R4-
    domainRGB[9][0]=1;domainRGB[9][1]=0;domainRGB[9][2]=1; //O1+
    domainRGB[10][0]=0.64629;domainRGB[10][1]=0.130165;domainRGB[10][2]=0.130165; //O1-
    domainRGB[11][0]=0.9;domainRGB[11][1]=0.566921;domainRGB[11][2]=0.633741; //O2+
    domainRGB[12][0]=0.751111;domainRGB[12][1]=0.393695;domainRGB[12][2]=0.751111; //O2-
    domainRGB[13][0]=0.418685;domainRGB[13][1]=0.027128;domainRGB[13][2]=0.027128; //O3+
    domainRGB[14][0]=0.678201;domainRGB[14][1]=0.498270;domainRGB[14][2]=0.301423; //O3-
    domainRGB[15][0]=0.476371;domainRGB[15][1]=0.035432;domainRGB[15][2]=0.14173; //O4+
    domainRGB[16][0]=0.961169;domainRGB[16][1]=0.251965;domainRGB[16][2]=0.199862; //O4-
    domainRGB[17][0]=0.355309;domainRGB[17][1]=0.968874;domainRGB[17][2]=0.355309; //O5+
    domainRGB[18][0]=0.038446;domainRGB[18][1]=0.646290;domainRGB[18][2]=0.038446; //O5-
    domainRGB[19][0]=0.766921;domainRGB[19][1]=0.766921;domainRGB[19][2]=0.766921; //O6+
    domainRGB[20][0]=0.169550;domainRGB[20][1]=0.169550;domainRGB[20][2]=0.169550; //O6-
    domainRGB[21][0]=0.566921;domainRGB[21][1]=0.566921;domainRGB[21][2]=0.566921; //a1+
    domainRGB[22][0]=0.393695;domainRGB[22][1]=0.015747;domainRGB[22][2]=0.885813; //a1-
    domainRGB[23][0]=0.0;domainRGB[23][1]=0.0;domainRGB[23][2]=0.0; //a2+
    domainRGB[24][0]=1.0;domainRGB[24][1]=0.710881;domainRGB[24][2]=0.0; //a2-
    domainRGB[25][0]=0.885813;domainRGB[25][1]=0.813533;domainRGB[25][2]=0.301423; //c+
    domainRGB[26][0]=0.8867188;domainRGB[26][1]=0.4335937;domainRGB[26][2]=0.0273438; //c-
    
    for (int i=0; i<27; i++) {
        this->ui->domain_LW->item(i)->setForeground(QColor(domainRGB[i][0]*255,255*domainRGB[i][1],domainRGB[i][2]*255));
    }
    
    
    

};

SimpleView::~SimpleView()
{
    // The smart pointers should clean up for up
    
}
void SimpleView::figurePlot(){
    this->ui->customPlot->replot();
}

void SimpleView::slotSwitch1D(){
    this->ui->stackedWidget->setCurrentIndex(1);
    xmin=0;
    xmax=0;
    ymin=0;
    ymax=0;
    zmax=0;
    zmin=0;
    this->ui->actionOpenFile_scalar->setEnabled(false);
    this->ui->actionOpenFile_vector->setEnabled(false);
    this->ui->actionOpenFile_domain->setEnabled(false);
//    this->ui->actionClear->setEnabled(false);
    this->ui->actionRotateToXN->setEnabled(false);
    this->ui->actionRotateToXP->setEnabled(false);
    this->ui->actionRotateToYN->setEnabled(false);
    this->ui->actionRotateToYP->setEnabled(false);
    this->ui->actionRotateToZN->setEnabled(false);
    this->ui->actionRotateToZP->setEnabled(false);
    this->ui->actionOutputStatus->setEnabled(false);
    this->ui->actionLoadStatus->setEnabled(false);
}

void SimpleView::slotSwitch3D(){
    this->ui->stackedWidget->setCurrentIndex(0);
    xmin=0;
    xmax=0;
    ymin=0;
    ymax=0;
    zmax=0;
    zmin=0;
    this->ui->actionOpenFile_scalar->setEnabled(true);
    this->ui->actionOpenFile_vector->setEnabled(true);
    this->ui->actionOpenFile_domain->setEnabled(true);
//    this->ui->actionClear->setEnabled(true);
    this->ui->actionRotateToXN->setEnabled(true);
    this->ui->actionRotateToXP->setEnabled(true);
    this->ui->actionRotateToYN->setEnabled(true);
    this->ui->actionRotateToYP->setEnabled(true);
    this->ui->actionRotateToZN->setEnabled(true);
    this->ui->actionRotateToZP->setEnabled(true);
    this->ui->actionOutputStatus->setEnabled(true);
    this->ui->actionLoadStatus->setEnabled(true);
}

void SimpleView::setup1DFigure(QCustomPlot *customPlot){
    // generate some data:
    int dataRows1=0;
    int dataRows2=0;
    this->ui->customPlot->clearGraphs();
    this->ui->customPlot->clearItems();
    this->ui->customPlot->clearPlottables();
    dataRows1=this->ui->file1_Widget->getFilteredCount();
    dataRows2=this->ui->file2_Widget->getFilteredCount();

    double xmin1D1=1;
    double xmax1D1=0;
    double ymin1D1=1;
    double ymax1D1=0;
    double xmin1D2=1;
    double xmax1D2=0;
    double ymin1D2=1;
    double ymax1D2=0;

    QVector<double> piTicks;
    QVector<QString> piLabels;
    if (this->ui->plot1DAutoTickX1_CB->isChecked()) {
        customPlot->xAxis->setAutoTicks(true);
        customPlot->xAxis->setAutoTickLabels(true);

    }else{
        customPlot->xAxis->setAutoTicks(false);
        customPlot->xAxis->setAutoTickLabels(false);
        std::istringstream iss1(this->ui->plot1DTickValueX1_LE->text().toStdString());
        std::string num;
        double number;
        std::istringstream convert;
        while(iss1){
            if(!std::getline(iss1, num, ',')) break;
            convert.str(num+" ");
            convert >> number;
            qDebug()<< QString::fromStdString(num) << number ;//<< convert;
            
            piTicks.push_back(number);
        }
        std::istringstream iss2(this->ui->plot1DTickLabelX1_LE->text().toStdString());
        while(iss2){
            if(!std::getline(iss2, num, ',')) break;
            piLabels.push_back(QString:: fromStdString(num));
        }
        customPlot->xAxis->setTickVector(piTicks);
        customPlot->xAxis->setTickVectorLabels(piLabels);
    }

    qDebug()<<piLabels<<piTicks;
    if(this->ui->plot1DTickLabelX1_CB->isChecked()){
        customPlot->xAxis->setTickLabels(true);
    }else{
        customPlot->xAxis->setTickLabels(false);
    }
    if(this->ui->plot1DTickLabelX2_CB->isChecked()){
        customPlot->xAxis2->setTickLabels(true);
    }else{
        customPlot->xAxis2->setTickLabels(false);
    }
    if(this->ui->plot1DTickLabelY1_CB->isChecked()){
        customPlot->yAxis->setTickLabels(true);
    }else{
        customPlot->yAxis->setTickLabels(false);
    }
    if(this->ui->plot1DTickLabelY2_CB->isChecked()){
        customPlot->yAxis2->setTickLabels(true);
    }else{
        customPlot->yAxis2->setTickLabels(false);
    }
    
    int graphNum=0;
    int columns1=this->ui->file1_Widget->getColumns();
    int columns2=this->ui->file2_Widget->getColumns();
    for(int colY=0;colY<columns1;colY++){
        QVector<double> x(dataRows1), y(dataRows1); // initialize with entries 0..100
        if (dataRows1>0) {
            if (this->ui->file1_Widget->findChild<QListWidget*>("plot1DFileY_LW")->item(colY)->checkState()!=0) {
                
                x=this->ui->file1_Widget->returnX();
                y=this->ui->file1_Widget->returnY(colY);
                if(xmin1D1>this->ui->file1_Widget->returnXMin())xmin1D1=this->ui->file1_Widget->returnXMin();
                if(xmax1D1<this->ui->file1_Widget->returnXMax())xmax1D1=this->ui->file1_Widget->returnXMax();
                if(ymin1D1>this->ui->file1_Widget->returnYMin())ymin1D1=this->ui->file1_Widget->returnYMin();
                if(ymax1D1<this->ui->file1_Widget->returnYMax())ymax1D1=this->ui->file1_Widget->returnYMax();
                // create graph and assign data to it:
                customPlot->addGraph();
                customPlot->graph(graphNum)->setData(x, y);
                customPlot->graph(graphNum)->setPen(this->ui->file1_Widget->getLineStyle(graphNum));
                customPlot->graph(graphNum)->setScatterStyle(this->ui->file1_Widget->getScatterStyle(graphNum));
                customPlot->graph(graphNum)->setName(this->ui->file1_Widget->getLineName(graphNum));
                graphNum++;
                
            }
        }
    }
    if (!this->ui->plot1DRangeMinX1_LE->text().isEmpty()) {
        qDebug()<<this->ui->plot1DRangeMinX1_LE->text();
        qDebug()<<isnan(this->ui->plot1DRangeMinX1_LE->text().toDouble());
        if (!isnan(this->ui->plot1DRangeMinX1_LE->text().toDouble())) {
            xmin1D1=this->ui->plot1DRangeMinX1_LE->text().toDouble();
        }
    }
    if (!this->ui->plot1DRangeMaxX1_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMaxX1_LE->text().toDouble())) {
            xmax1D1=this->ui->plot1DRangeMaxX1_LE->text().toDouble();
        }
    }
    if (!this->ui->plot1DRangeMinY1_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMinY1_LE->text().toDouble())) {
            ymin1D1=this->ui->plot1DRangeMinY1_LE->text().toDouble();
        }
    }
    if (!this->ui->plot1DRangeMaxY1_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMaxY1_LE->text().toDouble())) {
            ymax1D1=this->ui->plot1DRangeMaxY1_LE->text().toDouble();
        }
    }
    
    if(isnan(xmin1D1)){
        xmin1D1=0;
    }
    if(isnan(xmax1D1)){
        xmax1D1=1;
    }
    if(isnan(ymin1D1)){
        ymin1D1=0;
    }
    if(isnan(ymax1D1)){
        ymax1D1=1;
    }

    int graphNumLeft=graphNum;
    for(int colY=0;colY<columns2;colY++){
        QVector<double> x(dataRows2), y(dataRows2); // initialize with entries 0..100
        if (dataRows2 >0) {
            if (this->ui->file2_Widget->findChild<QListWidget*>("plot1DFileY_LW")->item(colY)->checkState()!=0) {
                
                x=this->ui->file2_Widget->returnX();
                y=this->ui->file2_Widget->returnY(colY);
                if(xmin1D2>this->ui->file2_Widget->returnXMin())xmin1D2=this->ui->file2_Widget->returnXMin();
                if(xmax1D2<this->ui->file2_Widget->returnXMax())xmax1D2=this->ui->file2_Widget->returnXMax();
                if(ymin1D2>this->ui->file2_Widget->returnYMin())ymin1D2=this->ui->file2_Widget->returnYMin();
                if(ymax1D2<this->ui->file2_Widget->returnYMax())ymax1D2=this->ui->file2_Widget->returnYMax();
                qDebug()<<"x,y:"<<x[0]<<colY<<y[0];
                qDebug()<<"x,y:"<<x[0]<<colY<<y[0]<<graphNum<<dataRows2;
                // create graph and assign data to it:
                customPlot->addGraph(customPlot->xAxis2,customPlot->yAxis2);
                customPlot->graph(graphNum)->setData(x, y);
                customPlot->graph(graphNum)->setPen(this->ui->file2_Widget->getLineStyle(graphNum-graphNumLeft));
                customPlot->graph(graphNum)->setScatterStyle(this->ui->file2_Widget->getScatterStyle(graphNum-graphNumLeft));
                customPlot->graph(graphNum)->setName(this->ui->file2_Widget->getLineName(graphNum-graphNumLeft));
                graphNum++;
                
            }
        }
    }
    
    if (!this->ui->plot1DRangeMinX2_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMinX2_LE->text().toDouble())) {
            xmin1D2=this->ui->plot1DRangeMinX2_LE->text().toDouble();
        }
    }
    if (!this->ui->plot1DRangeMaxX2_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMaxX2_LE->text().toDouble())) {
            xmax1D2=this->ui->plot1DRangeMaxX2_LE->text().toDouble();
        }
    }
    if (!this->ui->plot1DRangeMinY2_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMinY2_LE->text().toDouble())) {
            ymin1D2=this->ui->plot1DRangeMinY2_LE->text().toDouble();
        }
    }
    if (!this->ui->plot1DRangeMaxY2_LE->text().isEmpty()) {
        if (!isnan(this->ui->plot1DRangeMaxY2_LE->text().toDouble())) {
            ymax1D2=this->ui->plot1DRangeMaxY2_LE->text().toDouble();
        }
    }
    
    if(isnan(xmin1D2)){
        xmin1D2=0;
    }
    if(isnan(xmax1D2)){
        xmax1D2=1;
    }
    if(isnan(ymin1D2)){
        ymin1D2=0;
    }
    if(isnan(ymax1D2)){
        ymax1D2=1;
    }

    
    qDebug()<<"xyminmax:"<<xmin1D1<<xmax1D1<<ymin1D1<<ymax1D1;
    qDebug()<<"xyminmax:"<<xmin1D2<<xmax1D2<<ymin1D2<<ymax1D2;

    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    
//    QCPPlotTitle *plotTitle = new QCPPlotTitle(customPlot,this->ui->plot1DFigureTitle_LE->text());
    QCPPlotTitle* plotTitle = new QCPPlotTitle(customPlot,this->ui->plot1DFigureTitle_LE->text());
    qDebug()<<customPlot->plotLayout()->rowCount();
    if (customPlot->plotLayout()->rowCount()==1) {
        customPlot->plotLayout()->insertRow(0);
        customPlot->plotLayout()->addElement(0, 0,plotTitle);
    }else{
        customPlot->plotLayout()->removeAt(0);
        customPlot->plotLayout()->updateLayout();
        customPlot->plotLayout()->simplify();
        qDebug()<<customPlot->plotLayout()->rowCount();
        customPlot->plotLayout()->insertRow(0);
        qDebug()<<customPlot->plotLayout()->rowCount();
        customPlot->plotLayout()->addElement(0, 0,plotTitle);
    }
    // set labels:
    customPlot->xAxis->setLabel(this->ui->plot1DLabelX1_LE->text());
    customPlot->yAxis->setLabel(this->ui->plot1DLabelY1_LE->text());
    customPlot->xAxis2->setLabel(this->ui->plot1DLabelX2_LE->text());
    customPlot->yAxis2->setLabel(this->ui->plot1DLabelY2_LE->text());
    // make ticks on bottom axis go outward:
    customPlot->xAxis->setTickLength(0, 5);
    customPlot->xAxis->setSubTickLength(0, 3);
    // make ticks on right axis go inward and outward:
    customPlot->yAxis2->setTickLength(3, 3);
    customPlot->yAxis2->setSubTickLength(1, 1);

    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(xmin1D1, xmax1D1);
    customPlot->yAxis->setRange(ymin1D1, ymax1D1);
    customPlot->xAxis2->setRange(xmin1D2,xmax1D2);
    customPlot->yAxis2->setRange(ymin1D2,ymax1D2);
    
    if (this->ui->plot1DXGrid_CB->isChecked()) {
        customPlot->xAxis->grid()->setVisible(true);
    }else{
        customPlot->xAxis->grid()->setVisible(false);
    }
    if (this->ui->plot1DYGrid_CB->isChecked()) {
        customPlot->yAxis->grid()->setVisible(true);
    }else{
        customPlot->yAxis->grid()->setVisible(false);
    }
    
    if(this->ui->plot1DLegend_CB->isChecked()){
        this->ui->customPlot->legend->setVisible(true);
        double x=this->ui->plot1DLegendX_LE->text().toDouble();
        double y=this->ui->plot1DLegendY_LE->text().toDouble();
        double w=this->ui->plot1DLegendW_LE->text().toDouble();
        double h=this->ui->plot1DLegendH_LE->text().toDouble();
        qDebug()<<"xwyh:"<<x<<this->ui->customPlot->axisRect()->insetLayout()->elementCount();
        this->ui->customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::InsetPlacement::ipFree);
        this->ui->customPlot->axisRect()->insetLayout()->setInsetRect(0, QRectF(x,y,w,h));
    }
    
    if(!this->ui->plot1DFont_CB->isChecked()){
        QFont titleFont=this->ui->plot1DFont_fontComboBox->currentFont();
        if (this->ui->plot1DTitleFontSize_LE->text().isEmpty()) {
//            titleFont.setPointSize(10);
        }else{
            titleFont.setPointSize(this->ui->plot1DTitleFontSize_LE->text().toInt());
        }
        QFont axisFont=this->ui->plot1DFont_fontComboBox->currentFont();
        if (this->ui->plot1DAxisFontSize_LE->text().isEmpty()) {
            //            titleFont.setPointSize(10);
        }else{
            axisFont.setPointSize(this->ui->plot1DAxisFontSize_LE->text().toInt());
        }
        QFont tickFont=this->ui->plot1DFont_fontComboBox->currentFont();
        if (this->ui->plot1DTickFontSize_LE->text().isEmpty()) {
            //            titleFont.setPointSize(10);
        }else{
            tickFont.setPointSize(this->ui->plot1DTickFontSize_LE->text().toInt());
        }
        QFont legendFont=this->ui->plot1DFont_fontComboBox->currentFont();
        if (this->ui->plot1DLegendFontSize_LE->text().isEmpty()) {
            //            titleFont.setPointSize(10);
        }else{
            legendFont.setPointSize(this->ui->plot1DLegendFontSize_LE->text().toInt());
        }
//        qobject_cast<QCPPlotTitle*>(customPlot->plotLayout()->element(0, 0))->setTextColor(QColor(200,100,0));
        qobject_cast<QCPPlotTitle*>(customPlot->plotLayout()->element(0, 0))->setFont(titleFont);
        customPlot->legend->setFont(legendFont);
        customPlot->xAxis->setLabelFont(axisFont);
        customPlot->yAxis->setLabelFont(axisFont);
        customPlot->xAxis2->setLabelFont(axisFont);
        customPlot->yAxis2->setLabelFont(axisFont);
        customPlot->xAxis->setTickLabelFont(tickFont);
        customPlot->yAxis->setTickLabelFont(tickFont);
        customPlot->xAxis2->setTickLabelFont(tickFont);
        customPlot->yAxis2->setTickLabelFont(tickFont);
        
    }
    
    
    customPlot->replot();
}


void SimpleView::slotUpdate(){
    qDebug()<<"Slot update"<<scalarName.c_str()<<vectorName.c_str();
    if(this->ui->stackedWidget->currentIndex()==0){
        updateVTK(scalarName,vectorName);
    }else if(this->ui->stackedWidget->currentIndex()==1){
        setup1DFigure(this->ui->customPlot);
    }
}
void SimpleView::slotClear(){
//    this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->InitTraversal();
    if (this->ui->stackedWidget->currentIndex()==0) {
        if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
            
        }else{
            qDebug()<<"close";
            SimpleView *mySimpleView=new SimpleView();
            mySimpleView->show();
            this->ui->centralwidget->deleteLater();
//            this->ui->qvtkWidget->deleteLater();
            this->actorVector->Delete();
            this->actorScalar->Delete();
            for(int nr = 0; nr < 27; nr++){
                this->actorDomain[nr]->Delete();
            }
            for(int nr=0;nr<actorIso.count();nr++){
                actorIso[nr]->Delete();
            }
            this->close();
            qDebug()<<"nothing showing";
            
            
        }

    }else if (this->ui->stackedWidget->currentIndex()==1){
        this->ui->customPlot->clearGraphs();
    }
}

void SimpleView::updateVTK(std::string scalarName, std::string vectorName){
    // Qt Table View
    
    // Place the table view in the designer form
    // this->ui->container->layout()->addWidget(this->TableView->GetWidget());
    
    //Define the reader
    const char* fileNameScalar=scalarName.c_str();
    const char* fileNameVector=vectorName.c_str();
    //  int extent[6];
    double scalar_range[2];
    double vector_range[2];
    double valueRange[2];
    //  double sumValue;
    double vmin,vmax;
    std::ifstream scalarFile(scalarName);
    std::ifstream vectorFile(vectorName);
    
    
    VTK_CREATE(vtkRenderer,renderer);
    
    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
        qDebug()<<"creating new renderer";
    }else{
        renderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    }
//    renderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    VTK_CREATE(vtkDataSetReader, readerScalarOrigin);
    VTK_CREATE(vtkExtractVOI,readerScalar);
    VTK_CREATE(vtkVolumeProperty,volumePropertyScalar);
    VTK_CREATE(vtkThreshold,thresholdScalar);
    VTK_CREATE(vtkDataSetReader,readerVectorOrigin);
    VTK_CREATE(vtkExtractVOI,readerVector);
    VTK_CREATE(vtkArrowSource,arrowVector);
    VTK_CREATE(vtkMaskPoints,maskVector);
    VTK_CREATE(vtkGlyph3D,glyphVector);
    VTK_CREATE(vtkPolyDataMapper,mapperVector);
    VTK_CREATE(vtkHedgeHog,hedgehog);
    VTK_CREATE(vtkDataSetMapper,streamMapper);
    VTK_CREATE(vtkThresholdPoints,thresholdVector);
    VTK_CREATE(vtkPlane, plane);
    VTK_CREATE(vtkCutter, cutterScalar);
    VTK_CREATE(vtkCutter, cutterVector);
    VTK_CREATE(vtkPolyDataNormals, isoNormals);
    
    
    renderer->SetBackground(0.9,0.9,0.9);
    
    VTK_CREATE(vtkPiecewiseFunction,opacityScalar);
    VTK_CREATE(vtkPiecewiseFunction,opacityVector);
    VTK_CREATE(vtkPointSource,vectorSeed);
    VTK_CREATE(vtkLookupTable,tableScalar);
    VTK_CREATE(vtkColorTransferFunction,colorScalar);
    VTK_CREATE(vtkColorTransferFunction,colorVector);
    VTK_CREATE(vtkCompositeTransferFunctionItem,compositeColor);
    VTK_CREATE(vtkRenderer,rendererAxes);
    
    VTK_CREATE(vtkCubeAxesActor,cubeAxes);
    
    
    VTK_CREATE(vtkOutlineFilter,outlineScalar);
    VTK_CREATE(vtkDataSetMapper,outlineScalarMapper);
    
    VTK_CREATE(vtkOutlineFilter,outlineVector);
    VTK_CREATE(vtkDataSetMapper,outlineVectorMapper);
    VTK_CREATE(vtkContourFilter, isosurface);
    VTK_CREATE(vtkPolyDataMapper, isoMapper);
    
    VTK_CREATE(vtkStreamTracer,stream);
//    vtkStreamLine* stream =vtkStreamLine::New();
    renderer->AddActor(actorScalar);
    renderer->AddActor(actorVector);
    VTK_CREATE(vtkDoubleArray,range);
    
    
    double planeOX=0,planeOY=0,planeOZ=0;
    double planeNX=0,planeNY=0,planeNZ=0;
    
    

    

    
    if (scalarFile && this->ui->scalar_CB->isChecked()){
        readerScalarOrigin->SetFileName(fileNameScalar);
        qDebug() << readerScalarOrigin;
        readerScalarOrigin->Update();
        readerScalarOrigin->GetOutput()->GetPointData()->GetScalars()->GetRange(scalar_range);
        readerScalar->SetInputConnection(readerScalarOrigin->GetOutputPort());
        if (this->ui->extract_CB->checkState()!=0){
            xminAll=this->ui->xmin_LE->text().toInt();
            yminAll=this->ui->ymin_LE->text().toInt();
            zminAll=this->ui->zmin_LE->text().toInt();
            xmaxAll=this->ui->xmax_LE->text().toInt();
            ymaxAll=this->ui->ymax_LE->text().toInt();
            zmaxAll=this->ui->zmax_LE->text().toInt();
            readerScalar->SetVOI(xminAll,xmaxAll,yminAll,ymaxAll,zminAll,zmaxAll);
            readerScalar->Update();
        }else{
            readerScalar->Update();
        }
//        isosurface->SetInputConnection(readerScalar->GetOutputPort());
//        isosurface->ComputeScalarsOn();
//        isosurface->ComputeNormalsOn();
//        isosurface->GenerateTrianglesOn();
//        int contoursNumber=0;
//        qDebug()<<"Fine up till here"<<this->ui->RGBIso_Table->rowCount();
//        contoursNumber=this->ui->RGBIso_Table->rowCount();
//        qDebug()<<"Fine after"<<contoursNumber;
//        isosurface->SetNumberOfContours(contoursNumber);
//        qDebug()<<"fine after iso";
//        for (int i=0; i<contoursNumber; i++) {
//            isosurface->SetValue(i, this->ui->RGBIso_Table->item(i,0)->text().toDouble());
//            qDebug()<<"Number of isosurface"<<i<<" "<<this->ui->RGBIso_Table->item(i,0)->text().toDouble();
//        }
//        //        if(contoursNumber!=0){
//        isoNormals->SetInputConnection(0, isosurface->GetOutputPort());
//        isoMapper->SetInputConnection(isoNormals->GetOutputPort());
//        isoMapper->ScalarVisibilityOff();
//        actorIsosurface->SetMapper(isoMapper);
//        actorIsosurface->GetProperty()->SetColor(0, 0, 0);
//        renderer->AddActor(actorIsosurface);
//        if (this->ui->isosurface_CB->checkState()) {
//            actorIsosurface->SetVisibility(true);
//            qDebug()<<"showing isosurface";
//        }else{
//            actorIsosurface->SetVisibility(false);
//            qDebug()<<"not showing isosurface";
//        }
        //        }
        
        if (this->ui->scalarRange_CB->checkState()){
            vmin=this->ui->scalarValueMin_LE->text().toDouble();
            vmax=this->ui->scalarValueMax_LE->text().toDouble();
            range->InsertNextValue(vmin);
            range->InsertNextValue(vmax);
            thresholdScalar->SetInputConnection(readerScalar->GetOutputPort());
            thresholdScalar->ThresholdBetween(vmin,vmax);
            
            VTK_CREATE(vtkDataSetTriangleFilter,tetra);
            tetra->SetInputConnection(0,thresholdScalar->GetOutputPort(0));
            VTK_CREATE(vtkUnstructuredGridVolumeRayCastMapper,mapperScalar1);
//            VTK_CREATE(vtkUnstructuredGridVolumeZSweepMapper,mapperScalar1);
            mapperScalar1->SetInputConnection(0,tetra->GetOutputPort(0));
            mapperScalar1->Update();
            actorScalar->SetMapper(mapperScalar1);
            qDebug()<<actorScalar;
        }else{
            range->InsertNextValue(scalar_range[0]);
            range->InsertNextValue(scalar_range[1]);
            vmin=scalar_range[0];
            vmax=scalar_range[1];
            VTK_CREATE(vtkSmartVolumeMapper,mapperScalar);
//            VTK_CREATE(vtkVolumeMapper,mapperScalar);
            mapperScalar->SetInputConnection(0,readerScalar->GetOutputPort(0));
            // mapperScalar->SetLookupTable(tableScalar);
            actorScalar->SetMapper(mapperScalar);
        }
        if(this->ui->isosurface_CB->isChecked()){
            drawIsoSurface(readerScalar->GetOutputPort());
        }
        
        if(this->ui->scalar_CB->checkState()==0 || this->ui->volume_CB->checkState()==0){
            actorScalar->SetVisibility(false);
        }else{
            actorScalar->SetVisibility(true);
        }
        
        
        VTK_CREATE(vtkPolyDataMapper, cutterMapper);
        cutterScalar->SetInputConnection(0, readerScalar->GetOutputPort(0));
        cutterMapper->SetInputConnection(0, cutterScalar->GetOutputPort(0));
        actorCutter->SetMapper(cutterMapper);
        renderer->AddActor(actorCutter);
        
        if (data2Dx||data2Dy||data2Dz) {
            plane->SetOrigin(0, 0, 0);
            if (data2Dx) {
                plane->SetNormal(1, 0, 0);
            }else if(data2Dy){
                plane->SetNormal(0, 1, 0);
            }else if(data2Dz){
                plane->SetNormal(0, 0, 1);
            }
            cutterScalar->SetCutFunction(plane);
            actorCutter->SetVisibility(true);

        }else{
            planeOX=this->ui->sliceOriginX->text().toDouble();
            planeOY=this->ui->sliceOriginY->text().toDouble();
            planeOZ=this->ui->sliceOriginZ->text().toDouble();
            planeNX=this->ui->sliceNormalX->text().toDouble();
            planeNY=this->ui->sliceNormalY->text().toDouble();
            plane->SetOrigin(planeOX, planeOY, planeOZ);
            plane->SetNormal(planeNX, planeNY, planeNZ);
            cutterScalar->SetCutFunction(plane);

            if (this->ui->slice_CB->checkState()) {
                actorCutter->SetVisibility(true);
            }else{
                actorCutter->SetVisibility(false);
            }
        }
        
        valueRange[0]=scalar_range[0];
        valueRange[1]=scalar_range[1];
        outlineScalar->SetInputConnection(readerScalar->GetOutputPort());
        outlineScalarMapper->SetInputConnection(outlineScalar->GetOutputPort());
        outlineScalarActor->SetMapper(outlineScalarMapper);
        outlineScalarActor->GetProperty()->SetColor(0,0,0);
        renderer->AddActor(outlineScalarActor);
    }else{
        outlineScalarActor->SetVisibility(false);
    }
    
    if (vectorFile && this->ui->vector_CB->isChecked()){
        //Then is the vector part
        readerVectorOrigin->SetFileName(fileNameVector);
        readerVectorOrigin->Update();
        
        readerVectorOrigin->GetOutput()->GetPointData()->GetVectors()->GetRange(vector_range,-1);
        
        
        readerVectorOrigin->GetOutput()->GetPointData()->SetActiveScalars("Magnitude");
        readerVectorOrigin->GetOutput()->GetPointData()->SetActiveVectors("vector");
        
        
        readerVector->SetInputConnection(0,readerVectorOrigin->GetOutputPort(0));
        if (this->ui->extract_CB->checkState()!=0){
            xminAll=this->ui->xmin_LE->text().toInt();
            yminAll=this->ui->ymin_LE->text().toInt();
            zminAll=this->ui->zmin_LE->text().toInt();
            xmaxAll=this->ui->xmax_LE->text().toInt();
            ymaxAll=this->ui->ymax_LE->text().toInt();
            zmaxAll=this->ui->zmax_LE->text().toInt();
            readerVector->SetVOI(xminAll,xmaxAll,yminAll,ymaxAll,zminAll,zmaxAll);
            readerVector->Update();
        }else{
            qDebug()<<xmin<<xmax;
            // readerVector->GetVOI(extent);
            // readerVector->SetVOI(extent);
            readerVector->Update();
        }
        
        arrowVector->Update();
        
        vector_range[0]=this->ui->vectorValueMin_LE->text().toDouble();
        vector_range[1]=this->ui->vectorValueMax_LE->text().toDouble();
        

        thresholdVector->SetInputData(readerVector->GetOutput());

        
        thresholdVector->ThresholdBetween(vector_range[0],vector_range[1]);
        thresholdVector->Update();
        glyphVector->SetSourceConnection(0,arrowVector->GetOutputPort(0));
        glyphVector->SetInputConnection(thresholdVector->GetOutputPort());
        glyphVector->SetVectorModeToUseVector();
        glyphVector->SetColorModeToColorByVector();
        glyphVector->SetScaleModeToScaleByVector();
        glyphVector->SetScaleFactor(this->ui->vectorScale_LE->text().toDouble());
        glyphVector->Update();
        
        mapperVector->SetInputConnection(glyphVector->GetOutputPort());
        mapperVector->SetScalarRange(vector_range);
        mapperVector->SetLookupTable(colorVector);
        
        actorVector->SetMapper(mapperVector);
        
        if(this->ui->vectorGlyph_CB->checkState()!=0){
            actorVector->SetVisibility(true);
        }else{
            actorVector->SetVisibility(false);
        }
        valueRange[0]=vector_range[0];
        valueRange[1]=vector_range[1];
        outlineVector->SetInputConnection(readerVector->GetOutputPort());
        outlineVectorMapper->SetInputConnection(outlineVector->GetOutputPort());
        outlineVectorActor->SetMapper(outlineVectorMapper);
        outlineVectorActor->GetProperty()->SetColor(0,0,0);
        renderer->AddActor(outlineVectorActor);
        
        
        
        if(this->ui->streamline_CB->isChecked()){
            vectorSeed->SetCenter(this->ui->seedCenterX_LE->text().toDouble(), this->ui->seedCenterY_LE->text().toDouble(), this->ui->seedCenterZ_LE->text().toDouble());
            vectorSeed->SetNumberOfPoints(this->ui->seedNumber_LE->text().toInt());
            vectorSeed->SetRadius(this->ui->seedRadius_LE->text().toDouble());
            stream->SetSourceConnection(vectorSeed->GetOutputPort());
            stream->SetInputConnection(readerVector->GetOutputPort());
            stream->SetMaximumPropagation(this->ui->streamStepLength_LE->text().toDouble());
//            stream->SetIntegrationStepLength(this->ui->streamIntStepLength_LE->text().toDouble());
//            stream->SetStepLength(this->ui->streamStepLength_LE->text().toDouble());
            stream->SetIntegrationDirectionToForward();
            streamMapper->SetInputConnection(stream->GetOutputPort());
            actorStream->SetMapper(streamMapper);
            renderer->AddActor(actorStream);
        }
        
    }else{
        outlineVectorActor->SetVisibility(false);
    }
    
    //Define the color map
    // opacityScalar=volumePropertyScalar->GetScalarOpacity();
    // opacityVector=volumePropertyScalar->GetScalarOpacity();
    if (this->ui->alpha_Combo->currentIndex()==0){
        opacityScalar->AddPoint(scalar_range[0],1.0);
        opacityScalar->AddPoint((scalar_range[0]+scalar_range[1])/2,0);
        opacityScalar->AddPoint(scalar_range[1],1.0);
        opacityVector->AddPoint(vector_range[0],1.0);
        opacityVector->AddPoint((vector_range[0]+vector_range[1])/2,0);
        opacityVector->AddPoint(vector_range[1],1.0);
    }else{
        double alphaValue,alpha;
        if (this->ui->alphaScalar_Table->rowCount()!=0){
            for (int i=0;i<this->ui->alphaScalar_Table->rowCount();i++){
                alphaValue=this->ui->alphaScalar_Table->item(i,0)->text().toDouble();
                alpha=this->ui->alphaScalar_Table->item(i,1)->text().toDouble();
                opacityScalar->AddPoint(alphaValue,alpha);
            }
        }else{
            opacityScalar->AddPoint(scalar_range[0],1.0);
            opacityScalar->AddPoint((scalar_range[0]+scalar_range[1])/2,1.0);
            opacityScalar->AddPoint(scalar_range[1],1.0);
        }
        
        if (this->ui->alphaVector_Table->rowCount()!=0){
            for (int i=0;i<this->ui->alphaVector_Table->rowCount();i++){
                alphaValue=this->ui->alphaVector_Table->item(i,0)->text().toDouble();
                alpha=this->ui->alphaVector_Table->item(i,1)->text().toDouble();
                opacityVector->AddPoint(alphaValue,alpha);
            }
        }else{
            opacityVector->AddPoint(vector_range[0],1.0);
            opacityVector->AddPoint((vector_range[0]+vector_range[1])/2,1.0);
            opacityVector->AddPoint(vector_range[1],1.0);
        }
    }
    
    
    colorScalar->SetColorSpaceToLab();
    colorVector->SetColorSpaceToLab();
    if (this->ui->RGB_Combo->currentIndex()==0){
        colorScalar->AddRGBPoint(scalar_range[0],0.0,0.0,1.0);
        colorScalar->AddRGBPoint((scalar_range[0]+scalar_range[1])/2,0,1,0);
        colorScalar->AddRGBPoint(scalar_range[1],1.0,0.0,0.0);
        colorVector->AddRGBPoint(vector_range[0],0.0,0.0,1.0);
        colorVector->AddRGBPoint((vector_range[0]+vector_range[1])/2,0,1,0);
        colorVector->AddRGBPoint(vector_range[1],1.0,0.0,0.0);
    }else{
        double RGBValue,R,G,B;
        if (this->ui->RGBScalar_Table->rowCount()!=0){
            tableScalar->SetNumberOfColors(this->ui->RGBScalar_Table->rowCount());
            for (int i=0;i<this->ui->RGBScalar_Table->rowCount();i++){
                RGBValue=this->ui->RGBScalar_Table->item(i,0)->text().toDouble();
                R=this->ui->RGBScalar_Table->item(i,1)->text().toDouble()/255;
                G=this->ui->RGBScalar_Table->item(i,2)->text().toDouble()/255;
                B=this->ui->RGBScalar_Table->item(i,3)->text().toDouble()/255;
                // A=this->ui->RGBScalar_Table->item(i,4)->text().toDouble();
                colorScalar->AddRGBPoint(RGBValue,R,G,B);
            }
        }else{
            colorScalar->AddRGBPoint(scalar_range[0],0.0,0.0,1.0);
            colorScalar->AddRGBPoint((scalar_range[0]+scalar_range[1])/2,0,1,0);
            colorScalar->AddRGBPoint(scalar_range[1],1.0,0.0,0.0);
        }
        
        if (this->ui->RGBVector_Table->rowCount()!=0){
            for (int i=0;i<this->ui->RGBVector_Table->rowCount();i++){
                RGBValue=this->ui->RGBVector_Table->item(i,0)->text().toDouble();
                R=this->ui->RGBVector_Table->item(i,1)->text().toDouble()/255;
                G=this->ui->RGBVector_Table->item(i,2)->text().toDouble()/255;
                B=this->ui->RGBVector_Table->item(i,3)->text().toDouble()/255;
                colorVector->AddRGBPoint(RGBValue,R,G,B);
            }
        }else{
            colorVector->AddRGBPoint(vector_range[0],0.0,0.0,1.0);
            colorVector->AddRGBPoint((vector_range[0]+vector_range[1])/2,0,1,0);
            colorVector->AddRGBPoint(vector_range[1],1.0,0.0,0.0);
        }
    }
    
    compositeColor->SetOpacityFunction(opacityScalar);
    compositeColor->SetColorTransferFunction(colorScalar);
    
    if (this->ui->volume_CB->checkState()!=0){
        volumePropertyScalar->SetScalarOpacity(opacityScalar);
        volumePropertyScalar->SetColor(colorScalar);
        volumePropertyScalar->SetInterpolationTypeToNearest();
        actorScalar->SetProperty(volumePropertyScalar);
        actorScalar->Update();
    }
    
    
    renderer->AddActor(axes);

    

    
    RGBPoint=3;
    scalarScaleBarActor->SetLookupTable(colorScalar);
    scalarScaleBarActor->SetTitle("Scalar");
    scalarScaleBarActor->SetNumberOfLabels(RGBPoint);
    scalarScaleBarActor->GetTitleTextProperty()->SetColor(0,0,0);
    scalarScaleBarActor->GetLabelTextProperty()->SetColor(0,0,0);
    scalarScaleBarActor->SetPosition(0.1,0.05);
    scalarScaleBarActor->UseOpacityOn();
    renderer->AddActor2D(scalarScaleBarActor);
    
    vectorScaleBarActor->SetLookupTable(colorVector);
    vectorScaleBarActor->SetTitle("Vector");
    vectorScaleBarActor->SetNumberOfLabels(RGBPoint);
    vectorScaleBarActor->GetTitleTextProperty()->SetColor(0,0,0);
    vectorScaleBarActor->GetLabelTextProperty()->SetColor(0,0,0);
    vectorScaleBarActor->SetPosition(0.8,0.05);
    vectorScaleBarActor->UseOpacityOn();
    renderer->AddActor2D(vectorScaleBarActor);
    
    if(this->ui->outline_CB->checkState()!=0){
        if (this->ui->scalar_CB->checkState()!=0){
            outlineScalarActor->SetVisibility(true);
        }
        if (this->ui->vector_CB->checkState()!=0){
            outlineVectorActor->SetVisibility(true);
        }
    }else{
        outlineScalarActor->SetVisibility(false);
        outlineVectorActor->SetVisibility(false);
    }
    
    if(this->ui->axis_CB->checkState()!=0){
        axes->SetVisibility(true);
    }else{
        axes->SetVisibility(false);
    }
    
    if(this->ui->scalarBar_CB->checkState()!=0){
        if(this->ui->scalar_CB->checkState()!=0){
            scalarScaleBarActor->SetVisibility(true);
        }else{
            scalarScaleBarActor->SetVisibility(false);
        }
        
        if(this->ui->vector_CB->checkState()!=0){
            vectorScaleBarActor->SetVisibility(true);
        }else{
            vectorScaleBarActor->SetVisibility(false);
        }
    }else{
        scalarScaleBarActor->SetVisibility(false);
        vectorScaleBarActor->SetVisibility(false);
    }
    
    
    // VTK/Qt wedded
    // this->ui->qvtkWidget->GetRenderWindow()->RemoveRenderer(renderer);
    
    
    if(reset){
        updateCamera(-1);
    }else{
        updateCamera(0);
    }
    
}

void SimpleView::on_axis_CB_stateChanged(int state){
    if(state!=0){
        axes->SetVisibility(true);
        reset=false;
    }else{
        axes->SetVisibility(false);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->update();
}

void SimpleView::on_outline_CB_stateChanged(int state){
    if(this->ui->scalar_CB->checkState()){
        if(state!=0){
            outlineScalarActor->SetVisibility(true);
        }else{
            outlineScalarActor->SetVisibility(false);
        }
    }else{
        outlineScalarActor->SetVisibility(false);
    }
    
    if(this->ui->vector_CB->checkState()){
        if(state!=0){
            outlineVectorActor->SetVisibility(true);
        }else{
            outlineVectorActor->SetVisibility(false);
        }
    }else{
        outlineVectorActor->SetVisibility(false);
    }
    
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}

void SimpleView::on_scalar_CB_stateChanged(int state){
    if(state==0){
        this->ui->scalarChoice->setEnabled(false);
        this->ui->volume_CB->setEnabled(false);
    }else{
        this->ui->scalarChoice->setEnabled(true);
        this->ui->volume_CB->setEnabled(true);
    }
    
    if(state==0 || this->ui->volume_CB->checkState()==0){
        actorScalar->SetVisibility(false);
    }else{
        actorScalar->SetVisibility(true);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}

void SimpleView::on_volume_CB_stateChanged(int state){
    if(state==0 || this->ui->scalar_CB->checkState()==0){
        actorScalar->SetVisibility(false);
    }else{
        actorScalar->SetVisibility(true);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}


void SimpleView::on_vectorGlyph_CB_stateChanged(int state){
    if(state==0 || this->ui->vector_CB->checkState()==0){
        actorVector->SetVisibility(false);
    }else{
        actorVector->SetVisibility(true);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}

void SimpleView::on_scalarBar_CB_stateChanged(int state){
    if(state!=0 && this->ui->scalar_CB->isChecked()){
        scalarScaleBarActor->SetVisibility(true);
    }else{
        scalarScaleBarActor->SetVisibility(false);
    }
    if(state!=0 && this->ui->vector_CB->isChecked()){
        vectorScaleBarActor->SetVisibility(true);
    }else{
        vectorScaleBarActor->SetVisibility(false);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}

void SimpleView::on_vector_CB_stateChanged(int state){
    if(state!=0){
        actorVector->SetVisibility(true);
    }else{
        actorVector->SetVisibility(false);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}


void SimpleView::on_extract_CB_stateChanged(int state){
    if (state==0){
        this->ui->xmin_LE->setEnabled(false);
        this->ui->xmax_LE->setEnabled(false);
        this->ui->ymin_LE->setEnabled(false);
        this->ui->ymax_LE->setEnabled(false);
        this->ui->zmin_LE->setEnabled(false);
        this->ui->zmax_LE->setEnabled(false);
    }else{
        this->ui->xmin_LE->setEnabled(true);
        this->ui->xmax_LE->setEnabled(true);
        this->ui->ymin_LE->setEnabled(true);
        this->ui->ymax_LE->setEnabled(true);
        this->ui->zmin_LE->setEnabled(true);
        this->ui->zmax_LE->setEnabled(true);
        this->ui->xmin_LE->setText(QString::fromStdString(std::to_string(xminAll)));
        this->ui->ymin_LE->setText(QString::fromStdString(std::to_string(yminAll)));
        this->ui->zmin_LE->setText(QString::fromStdString(std::to_string(zminAll)));
        this->ui->xmax_LE->setText(QString::fromStdString(std::to_string(xmaxAll)));
        this->ui->ymax_LE->setText(QString::fromStdString(std::to_string(ymaxAll)));
        this->ui->zmax_LE->setText(QString::fromStdString(std::to_string(zmaxAll)));
    }
}

void SimpleView::on_xmin_LE_editingFinished(){
    // updateVTK(scalarName,vectorName);
}

void SimpleView::on_xmax_LE_editingFinished(){
    // updateVTK(scalarName,vectorName);
}

void SimpleView::on_ymin_LE_editingFinished(){
    // updateVTK(scalarName,vectorName);
}

void SimpleView::on_ymax_LE_editingFinished(){
    // updateVTK(scalarName,vectorName);
}

void SimpleView::on_zmin_LE_editingFinished(){
    // updateVTK(scalarName,vectorName);
}

void SimpleView::on_zmax_LE_editingFinished(){
    // updateVTK(scalarName,vectorName);
}




// Action to be taken upon file open
void SimpleView::slotOpenFile_scalar()
{
    QFileDialog filedialog;
    
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    if (!load.isEmpty()) {
        columns=loadData(load);
        
        if(tempX==1){
            data2Dx=true;
        }else{
            data2Dx=false;
        }
        if(tempY==1){
            data2Dy=true;
        }else{
            data2Dy=false;
        }
        if(tempZ==1){
            data2Dz=true;
        }else{
            data2Dz=false;
        }
        
        
        this->ui->scalar_CB->setCheckState(Qt::Checked);
        this->ui->volume_CB->setCheckState(Qt::Checked);
        this->ui->vector_CB->setCheckState(Qt::Unchecked);
        this->ui->domain_CB->setCheckState(Qt::Unchecked);
        int rows=(xmax+1)*(ymax+1)*(zmax+1);
        double *dataHold= new double[rows];
        QFileInfo filehold(load);
        // outputScalar(0,xmax,ymax,zmax);
        int current=this->ui->scalarChoice->count();
        if(current!=0){
            for(int i=0;i<current+1;++i){
                this->ui->scalarChoice->removeItem(0);
            }
        }else{
            
        }
        qDebug()<<"output scalar:"<<filehold.absolutePath()+"/"+filehold.baseName();
        scalarDir=QFileInfo(filehold.absolutePath()+"/"+filehold.baseName());
        for (int i = 0; i < columns; ++i)
        {
            outputScalar(scalarDir.absoluteFilePath(),i,xmax,ymax,zmax);
            this->ui->scalarChoice->addItem(QString::fromStdString(std::to_string(i+1)));
        }
        
        this->ui->inputFileScalar->setText(filehold.fileName());
        
        printstatus = QString::fromStdString(std::to_string(columns));
        this->ui->rowcolScalar->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(xmax));
        this->ui->xMinMaxScalar->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(ymax));
        this->ui->yMinMaxScalar->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(zmax));
        this->ui->zMinMaxScalar->setText(printstatus);
        
//        this->ui->scalar_Table->clearContents();
        for (int i=0; i<this->ui->scalar_Table->rowCount(); i++) {
            this->ui->scalar_Table->removeRow(0);
        }
        for(int i=0;i<columns;++i){
            for (int j=0;j<rows;++j){
                dataHold[j]=vtkData[j][i];
            }
            if(this->ui->scalar_Table->rowCount()<columns){
                this->ui->scalar_Table->insertRow(this->ui->scalar_Table->rowCount());
            }
            printstatus = QString::fromStdString(std::to_string(getMin(dataHold,rows)));
            this->ui->scalar_Table->setItem(i,0,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getMax(dataHold,rows)));
            this->ui->scalar_Table->setItem(i,1,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getAvg(dataHold,rows)));
            this->ui->scalar_Table->setItem(i,2,new QTableWidgetItem(printstatus));
        }
        
//        this->ui->information_Tab->setCurrentIndex(0);
        scalarName=(scalarDir.absoluteFilePath().toStdString()+"."+std::to_string(this->ui->scalarChoice->currentIndex()+1)+".vtk").c_str();
        updateVTK(scalarName,vectorName);
        delete this->vtkData;
    }
}

void SimpleView::on_scalarChoice_currentIndexChanged(int index){
//    if (index!=this->ui->scalarChoice->currentIndex()){
        scalarName=(scalarDir.absolutePath().toStdString()+std::to_string(index+1)+".vtk").c_str();
        qDebug()<<"scalar"<<scalarName.c_str();
        updateVTK(scalarName,vectorName);
//    }
}
void SimpleView::slotOpenFile_vector()
{
    QFileDialog filedialog;
    int i;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    if (!load.isEmpty()) {
        columns=loadData(load);
        int rows=(xmax+1)*(ymax+1)*(zmax+1);
        double *dataHold= new double[rows];
        this->ui->scalar_CB->setCheckState(Qt::Unchecked);
        this->ui->volume_CB->setCheckState(Qt::Unchecked);
        this->ui->vector_CB->setCheckState(Qt::Checked);
        this->ui->vectorGlyph_CB->setCheckState(Qt::Checked);
        this->ui->domain_CB->setCheckState(Qt::Unchecked);
        QFileInfo filehold(load);
        qDebug()<<columns<<columns/3;
        qDebug()<<xmax<<ymax<<zmax;
        int current=this->ui->vectorChoice->count();
        if(current!=0){
            for(i=0;i<current+1;++i){
                this->ui->vectorChoice->removeItem(0);
            }
        }else{
            
        }
        vectorDir=QFileInfo(filehold.absolutePath()+"/"+filehold.baseName());
        for (i = 0; i < columns/3; ++i)
        {
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<QString::fromStdString(std::to_string(3*i+1)+std::to_string(3*i+2)+std::to_string(3*i+3));
            outputVector(vectorDir.absoluteFilePath(),3*i,3*i+1,3*i+2,xmax,ymax,zmax);
            this->ui->vectorChoice->addItem(QString::fromStdString(std::to_string(3*i+1)+std::to_string(3*i+2)+std::to_string(3*i+3)));
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<xmax<<ymax<<zmax;
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<filehold.absolutePath().append(filehold.baseName());
        }
        this->ui->inputFileVector->setText(filehold.fileName());
        
        printstatus = QString::fromStdString(std::to_string(columns));
        this->ui->rowcolVector->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(xmax));
        this->ui->xMinMaxVector->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(ymax));
        this->ui->yMinMaxVector->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(zmax));
        this->ui->zMinMaxVector->setText(printstatus);
        
        this->ui->vector_Table->clearContents();
        for (int i=0; i<this->ui->vector_Table->rowCount(); i++) {
            this->ui->vector_Table->removeRow(0);
        }
        for(i=0;i<columns;++i){
            for (int j=0;j<rows;++j){
                dataHold[j]=vtkData[j][i];
            }
            if(this->ui->vector_Table->rowCount()<columns){
                this->ui->vector_Table->insertRow(this->ui->vector_Table->rowCount());
            }
            printstatus = QString::fromStdString(std::to_string(getMin(dataHold,rows)));
            this->ui->vector_Table->setItem(i,0,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getMax(dataHold,rows)));
            this->ui->vector_Table->setItem(i,1,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getAvg(dataHold,rows)));
            this->ui->vector_Table->setItem(i,2,new QTableWidgetItem(printstatus));
        }
        for (int j=0;j<rows;++j){
            dataHold[j]=sqrt(pow(vtkData[j][0],2.0)+pow(vtkData[j][1],2.0)+pow(vtkData[j][2],2.0));
        }
        this->ui->vectorValueMin_LE->setText(QString::fromStdString(std::to_string(getMin(dataHold,rows))));
        this->ui->vectorValueMax_LE->setText(QString::fromStdString(std::to_string(getMax(dataHold,rows))));
        this->ui->vectorScale_LE->setText(QString::fromStdString(std::to_string(2/getMax(dataHold, rows))));
//        this->ui->information_Tab->setCurrentIndex(1);
        int index=this->ui->vectorChoice->currentIndex();
        vectorName=(vectorDir.absoluteFilePath().toStdString()+"."+std::to_string(3*index+1)+std::to_string(3*index+2)+std::to_string(3*index+3)+".vtk").c_str();
        
        updateVTK(scalarName,vectorName);
        delete this->vtkData;
        
    }
}

void SimpleView::on_vectorChoice_activated(int index){
    if(index!=this->ui->vectorChoice->currentIndex()){
        vectorName=(vectorDir.absolutePath().toStdString()+std::to_string(3*index+1)+std::to_string(3*index+2)+std::to_string(3*index+3)+".vtk").c_str();
        updateVTK(scalarName,vectorName);
    }
}

void SimpleView::outputScalar(QString path,int columnNumber,int x, int y, int z){
    long rowNumber;

    if (data2Dx) {
        x=x+2;
    }else{
        x=x+1;
    }
    if (data2Dy) {
        y=y+2;
    }else{
        y=y+1;
    }
    if (data2Dz) {
        z=z+2;
    }else{
        z=z+1;
    }
    rowNumber=x*y*z;
    std::ofstream output;
    std::string str;
    str=path.toStdString()+"."+std::to_string(columnNumber+1)+".vtk";
    const char *outdir=str.c_str();
    output.open(outdir);
    output << "# vtk DataFile Version 3.0\n";
    output << "Structured Points\n";
    output << "ASCII\n";
    output << "\n";
    output << "DATASET STRUCTURED_POINTS\n";
    output << "DIMENSIONS " << std::to_string(x) << " " << std::to_string(y) <<" "<< std::to_string(z) << "\n";
    output << "ORIGIN 0 0 0\n";
    output << "SPACING 1 1 1\n";
    output << "\n";
    output << "POINT_DATA " << std::to_string(rowNumber)+"\n";
    output << "SCALARS scalar float\n";
    output << "LOOKUP_TABLE default\n";
    output << std::scientific;
    
    for (int m=0;m<z;++m){
        for (int n=0;n<y;++n){
            for (int w=0;w<x;++w){
                if (data2Dx||data2Dy||data2Dz) {
                    if (data2Dx) {
                        output << setw(14) << vtkData[0*y*z+n*z+m][columnNumber] << "\n";
                    }else if(data2Dy){
                        output << setw(14) << vtkData[w*(y-1)*z+0*z+m][columnNumber] << "\n";
                    }else if(data2Dz){
                        output << setw(14) << vtkData[w*y*(z-1)+n*(z-1)+0][columnNumber] << "\n";
                    }
                }else{
                    output << setw(14) << vtkData[w*y*z+n*z+m][columnNumber] << "\n";
                }
            }
        }
    }
    output.close();
    scalarName=str;
}

void SimpleView::outputVector(QString path,int colX,int colY,int colZ, int x, int y, int z){
    long rowNumber;
    x=x+1;
    y=y+1;
    z=z+1;
    rowNumber=x*y*z;
    std::ofstream output;
    std::string str;
    str=path.toStdString()+"."+std::to_string(colX+1)+std::to_string(colY+1)+std::to_string(colZ+1)+".vtk";
    const char *outdir=str.c_str();
    output.open(outdir);
    output << "# vtk DataFile Version 3.0\n";
    output << "Structured Points\n";
    output << "ASCII\n";
    output << "\n";
    output << "DATASET STRUCTURED_POINTS\n";
    output << "DIMENSIONS " << std::to_string(x) << " " << std::to_string(y) <<" "<< std::to_string(z) << "\n";
    output << "ORIGIN 0 0 0\n";
    output << "SPACING 1 1 1\n";
    output << "\n";
    output << "POINT_DATA " << std::to_string(rowNumber)+"\n";
    output << "SCALARS Magnitude float \n";
    output << "LOOKUP_TABLE default \n";
    output << std::scientific;
    for (int m=0;m<z;++m){
        for (int n=0;n<y;++n){
            for (int w=0;w<x;++w){
                output << setw(14) << sqrt(pow(vtkData[w*y*z+n*z+m][colX],2)+pow(vtkData[w*y*z+n*z+m][colY],2)+pow(vtkData[w*y*z+n*z+m][colZ],2)) << "\n";
            }
        }
    }
    
    output << "\n";
    output << "VECTORS vector float\n";
    output << std::scientific;
    for (int m=0;m<z;++m){
        for (int n=0;n<y;++n){
            for (int w=0;w<x;++w){
                output << setw(14) << vtkData[w*y*z+n*z+m][colX] << " " << setw(14) << vtkData[w*y*z+n*z+m][colY] << " " << setw(14) << vtkData[w*y*z+n*z+m][colZ] << "\n";
            }
        }
    }
    output.close();
    vectorName=str;
}

void SimpleView::slotExit() {
    qApp->exit();
}

int SimpleView::loadData(QString filedir){
    //First we need to decide whether the first line of the file needs to be kept
    std::ifstream input;
    std::ofstream output;
    float a;
    int i=0,x=0,y=0,z=0,hold=0,columnNumber=0;
    long rowNumber=0;
    int count1=0;
    int count2=0;
    
    QFileInfo filehold(filedir);
    QByteArray dir1=filedir.toLatin1();
    const char *dir=dir1.data();
    qDebug()<<dir;
    input.open(dir);
    std::string str,line,line1,line2;
    std::getline(input,line1);
    std::getline(input,line2);
    std::istringstream iss1(line1);
    std::istringstream iss2(line2);
    input.close();
    
    
    
    while(iss1 >> a){
        count1++;
    }
    while(iss2 >> a){
        count2++;
    }
//    input.open(dir);
//    for (rowNumber=0; std::getline(input, line); rowNumber++) {
//    }
//    input.close();
    
    if (count1!=count2){
        input.open(dir);
        std::getline(input,line1);
        std::istringstream iss1(line1);
        iss1 >> x >> y >> z;
        
        input.close();
    }else{
        std::ifstream read(dir, std::ios_base::ate );//open file
        int length = 0;
        
        char c = '\0';
        
        if( read )
        {
            length = read.tellg();//Get file size
            
            // loop backward over the file
            
            for(int i = length-2; i > 0; i-- )
            {
                read.seekg(i);
                c = read.get();
                if( c == '\r' || c == '\n' )//new line?
                    break;
            }
            std::getline(read, line1);//read last line
            std::istringstream iss1(line1);
            iss1 >> x >> y >> z;
            read.close();
            
        }
        
    }

    
    columnNumber=count2-3;
    rowNumber=(x)*(y)*(z);
    
    vtkData= new double*[rowNumber];
    for (i=0;i<rowNumber;++i){
        vtkData[i] = new double[columnNumber];
    }
    input.open(dir);
    if (count1!=count2){
        
        std::getline(input,line1);
        std::istringstream iss1(line1);
        
    }else{
        
    }
    for (int j=0;j<rowNumber;++j){
        std::getline(input,line);
        std::istringstream iss(line);
        iss >> hold>>hold>>hold;
        for (int k=0;k<columnNumber;++k){
            iss >> std::scientific;
            iss >>  vtkData[j][k];
        }
    }
    input.close();

    updateExtraction(x,y,z);
    tempX=x;
    tempY=y;
    tempZ=z;
    

    return columnNumber;
}



void SimpleView::on_scalarRange_CB_stateChanged(int state){
    if(state==0){
        this->ui->scalarValueMin_LE->setEnabled(false);
        this->ui->scalarValueMax_LE->setEnabled(false);
    }else{
        this->ui->scalarValueMin_LE->setEnabled(true);
        this->ui->scalarValueMax_LE->setEnabled(true);
    }
}
void SimpleView::on_RGBAdd_PB_released(){
    QString item;
    int row;
    if (this->ui->RGB_Combo->currentIndex()!=3) {
        if (this->ui->RGBValue_LE->text().isEmpty() |
            this->ui->RGBR_LE->text().isEmpty() |
            this->ui->RGBG_LE->text().isEmpty() |
            this->ui->RGBB_LE->text().isEmpty()){
        }else{
            switch (this->ui->RGB_Stack->currentIndex()) {
                case 0:
                    row=this->ui->RGBScalar_Table->rowCount();
                    qDebug()<<row;
                    this->ui->RGBScalar_Table->insertRow(row);
                    //      row=row;
                    item=this->ui->RGBValue_LE->text();
                    this->ui->RGBScalar_Table->setItem(row,0,new QTableWidgetItem(item));
                    item=this->ui->RGBR_LE->text();
                    this->ui->RGBScalar_Table->setItem(row,1,new QTableWidgetItem(item));
                    item=this->ui->RGBG_LE->text();
                    this->ui->RGBScalar_Table->setItem(row,2,new QTableWidgetItem(item));
                    item=this->ui->RGBB_LE->text();
                    this->ui->RGBScalar_Table->setItem(row,3,new QTableWidgetItem(item));
                    // item=this->ui->RGBA_LE->text();
                    // this->ui->RGBScalar_Table->setItem(row,4,new QTableWidgetItem(item));
                    this->ui->RGBScalar_Table->sortItems(0,Qt::AscendingOrder);
                    break;
                    
                case 1:
                    row=this->ui->RGBVector_Table->rowCount();
                    qDebug()<<row;
                    this->ui->RGBVector_Table->insertRow(row);
                    //      row=row;
                    item=this->ui->RGBValue_LE->text();
                    this->ui->RGBVector_Table->setItem(row,0,new QTableWidgetItem(item));
                    item=this->ui->RGBR_LE->text();
                    this->ui->RGBVector_Table->setItem(row,1,new QTableWidgetItem(item));
                    item=this->ui->RGBG_LE->text();
                    this->ui->RGBVector_Table->setItem(row,2,new QTableWidgetItem(item));
                    item=this->ui->RGBB_LE->text();
                    this->ui->RGBVector_Table->setItem(row,3,new QTableWidgetItem(item));
                    // item=this->ui->RGBA_LE->text();
                    // this->ui->RGBVector_Table->setItem(row,4,new QTableWidgetItem(item));
                    this->ui->RGBVector_Table->sortItems(0,Qt::AscendingOrder);
                    break;
                    
                default:
                    break;
            }
            
        }
    }else{
        if ((this->ui->isoValue_Combo->count()<=0) |
            this->ui->RGBR_LE->text().isEmpty() |
            this->ui->RGBG_LE->text().isEmpty() |
            this->ui->RGBB_LE->text().isEmpty()){
        }else{
            row=this->ui->RGBIso_Table->rowCount();
            qDebug()<<row;
            item=this->ui->isoValue_Combo->currentText();
            bool notExist=true;
            for (int i=0; i<this->ui->RGBIso_Table->rowCount(); i++) {
                if(this->ui->RGBIso_Table->item(i, 0)->text()==item){
                    notExist=false;
                }
            }
            if (notExist) {
                this->ui->RGBIso_Table->insertRow(row);
                //      row=row;
                
                this->ui->RGBIso_Table->setItem(row,0,new QTableWidgetItem(item));
                item=this->ui->RGBR_LE->text();
                this->ui->RGBIso_Table->setItem(row,1,new QTableWidgetItem(item));
                item=this->ui->RGBG_LE->text();
                this->ui->RGBIso_Table->setItem(row,2,new QTableWidgetItem(item));
                item=this->ui->RGBB_LE->text();
                this->ui->RGBIso_Table->setItem(row,3,new QTableWidgetItem(item));
                // item=this->ui->RGBA_LE->text();
                // this->ui->RGBScalar_Table->setItem(row,4,new QTableWidgetItem(item));
                this->ui->RGBIso_Table->sortItems(0,Qt::AscendingOrder);
            }
            
        }
        
    }
}

void SimpleView::on_RGBDelete_PB_released(){
    switch (this->ui->RGB_Stack->currentIndex()) {
        case 0:
            this->ui->RGBScalar_Table->removeRow(this->ui->RGBScalar_Table->currentRow());
            break;
        case 1:
            this->ui->RGBVector_Table->removeRow(this->ui->RGBVector_Table->currentRow());
            break;
        case 2:{
            int row=this->ui->RGBIso_Table->currentRow();
            this->ui->RGBIso_Table->removeRow(row);
            break;
        }
        default:
            break;
    }
}

void SimpleView::on_RGB_Combo_currentIndexChanged(int index){
    if (index==0){
        this->ui->RGBIso_SW->setCurrentIndex(0);
        this->ui->RGBIso_SW->setEnabled(false);
        this->ui->RGBValue_LE->setEnabled(false);
        this->ui->RGBR_LE->setEnabled(false);
        this->ui->RGBG_LE->setEnabled(false);
        this->ui->RGBB_LE->setEnabled(false);
        // this->ui->RGBA_LE->setEnabled(false);
        this->ui->RGBScalar_Table->setEnabled(false);
        this->ui->RGBVector_Table->setEnabled(false);
        this->ui->RGBIso_Table->setEnabled(false);
        this->ui->RGB_Stack->setEnabled(false);
        this->ui->isoValue_Combo->setEnabled(false);
    }else{
        if (index!=3) {
            this->ui->RGBIso_SW->setEnabled(true);
            this->ui->RGBIso_SW->setCurrentIndex(0);
            this->ui->RGBValue_LE->setEnabled(true);
            this->ui->RGBR_LE->setEnabled(true);
            this->ui->RGBG_LE->setEnabled(true);
            this->ui->RGBB_LE->setEnabled(true);
            // this->ui->RGBA_LE->setEnabled(true);
            this->ui->RGBScalar_Table->setEnabled(true);
            this->ui->RGBVector_Table->setEnabled(true);
            
            this->ui->RGB_Stack->setEnabled(true);
            if(index==1){
                this->ui->RGB_Stack->setCurrentIndex(0);
            }else if(index==2){
                this->ui->RGB_Stack->setCurrentIndex(1);
            }
        }else{
            this->ui->RGBIso_SW->setEnabled(true);
            this->ui->RGB_Stack->setCurrentIndex(2);
            this->ui->RGBIso_SW->setCurrentIndex(1);
            if (this->ui->isosurface_CB->isChecked()) {
                this->ui->isoValue_Combo->setEnabled(true);
                this->ui->RGBR_LE->setEnabled(true);
                this->ui->RGBG_LE->setEnabled(true);
                this->ui->RGBB_LE->setEnabled(true);
                this->ui->RGBIso_Table->setEnabled(true);
                this->ui->RGB_Stack->setEnabled(true);
            }else{
                this->ui->isoValue_Combo->setEnabled(false);
                this->ui->RGBR_LE->setEnabled(false);
                this->ui->RGBG_LE->setEnabled(false);
                this->ui->RGBB_LE->setEnabled(false);
                this->ui->RGBIso_Table->setEnabled(false);
                this->ui->RGB_Stack->setEnabled(false);
            }
        }
        

    }
    
}

void SimpleView::on_alpha_Combo_currentIndexChanged(int index){
    if (index==0){
        this->ui->alphaValue_LE->setEnabled(false);
        this->ui->alpha_LE->setEnabled(false);
        this->ui->alphaScalar_Table->setEnabled(false);
        this->ui->alphaVector_Table->setEnabled(false);
        this->ui->alpha_Stack->setEnabled(false);
    }else{
        this->ui->alphaValue_LE->setEnabled(true);
        this->ui->alpha_LE->setEnabled(true);
        this->ui->alphaScalar_Table->setEnabled(true);
        this->ui->alphaVector_Table->setEnabled(true);
        this->ui->alpha_Stack->setEnabled(true);
        if(index==1){
            this->ui->alpha_Stack->setCurrentIndex(0);
        }else if(index==2){
            this->ui->alpha_Stack->setCurrentIndex(1);
        }
    }
}

void SimpleView::on_alphaAdd_PB_released(){
    QString item;
    int row;
    if (this->ui->alphaValue_LE->text().isEmpty() |
        this->ui->alpha_LE->text().isEmpty()){
    }else{
        if (this->ui->alpha_Stack->currentIndex()==0){
            row=this->ui->alphaScalar_Table->rowCount();
            qDebug()<<row;
            this->ui->alphaScalar_Table->insertRow(row);
            //      row=row;
            item=this->ui->alphaValue_LE->text();
            this->ui->alphaScalar_Table->setItem(row,0,new QTableWidgetItem(item));
            item=this->ui->alpha_LE->text();
            this->ui->alphaScalar_Table->setItem(row,1,new QTableWidgetItem(item));
            this->ui->alphaScalar_Table->sortItems(0,Qt::AscendingOrder);
        }else if (this->ui->alpha_Stack->currentIndex()==1){
            row=this->ui->alphaVector_Table->rowCount();
            qDebug()<<row;
            this->ui->alphaVector_Table->insertRow(row);
            //      row=row;
            item=this->ui->alphaValue_LE->text();
            this->ui->alphaVector_Table->setItem(row,0,new QTableWidgetItem(item));
            item=this->ui->alpha_LE->text();
            this->ui->alphaVector_Table->setItem(row,1,new QTableWidgetItem(item));
            this->ui->RGBVector_Table->sortItems(0,Qt::AscendingOrder);
        }
        
    }
    
}

void SimpleView::on_alphaDelete_PB_released(){
    if (this->ui->alpha_Stack->currentIndex()==0){
        this->ui->alphaScalar_Table->removeRow(this->ui->alphaScalar_Table->currentRow());
    }else if (this->ui->alpha_Stack->currentIndex()==1){
        this->ui->alphaVector_Table->removeRow(this->ui->alphaVector_Table->currentRow());
    }
}

double SimpleView::getMin(double *list,int length){
    double minValue;
    minValue=list[0];
    for(int i=0;i<length;++i){
        if(list[i]<minValue){
            minValue=list[i];
        }
    }
    return minValue;
}

double SimpleView::getMax(double *list,int length){
    double maxValue;
    maxValue=list[0];
    for(int i=0;i<length;++i){
        if(list[i]>maxValue){
            maxValue=list[i];
        }
    }
    return maxValue;
}

double SimpleView::getAvg(double *list,int length){
    double avgValue;
    avgValue=0;
    for(int i=0;i<length;++i){
        avgValue=avgValue+list[i];
    }
    avgValue=avgValue/length;
    return avgValue;
}

int SimpleView::domainProcessing(QString filedir){
    //  double nR1p=0,nR1m=0;
    //  double nR2p=0,nR2m=0;
    //  double nR3p=0,nR3m=0;
    //  double nR4p=0,nR4m=0;
    //  double nO1p=0,nO1m=0;
    //  double nO2p=0,nO2m=0;
    //  double nO3p=0,nO3m=0;
    //  double nO4p=0,nO4m=0;
    //  double nO5p=0,nO5m=0;
    //  double nO6p=0,nO6m=0;
    //  double nT1p=0,nT1m=0;
    //  double nT2p=0,nT2m=0;
    //  double nT3p=0,nT3m=0;

    
    int columnNumber=loadData(filedir);
    qDebug()<<filedir;


    outputDomain(filedir,xmax,ymax,zmax);


    
    for (int i=0;i<27;i++){
        qDebug()<<i<<existDomain[i];
        if(existDomain[i]){
            this->ui->domain_LW->item(i)->setCheckState(Qt::Checked);
        }else{
            this->ui->domain_LW->item(i)->setCheckState(Qt::Unchecked);
        }
    }
    return columnNumber;
}

void SimpleView::outputDomain(QString filedir,int x, int y, int z){
    int rowNumber=(x+3)*(y+3)*(z+3);
    int mR=0,mO=0,mT=0,mN=0,mfilm=0; //mN is for null, mfilm is for total film
    double fR,fT,fO,fN;
    int i=0,j=0,k=0;
    int nfs=0,nsub=0;
    long hold;
    double px,py,pz;
    int* outputData= new int[rowNumber];
    std::fill_n(outputData,rowNumber,-1);
    qDebug()<<xmax<<" "<<ymax<<" "<<zmax<<" "<<rowNumber;
    
    for (i=0;i<zmax+1;i++){
        rowNumber=1*(zmax+1)*(ymax+1)+0*(zmax+1)+i;
        px=vtkData[rowNumber][0];
        py=vtkData[rowNumber][1];
        pz=vtkData[rowNumber][2];
        // qDebug()<<i << " "<<rowNumber<<std::abs(px)+std::abs(py)+std::abs(pz) ;
        if(std::abs(px)+std::abs(py)+std::abs(pz)>0.000001){
            nfs=i;
        }
    }
    for (i=zmax;i>0;i--){
        rowNumber=1*(zmax+1)*(ymax+1)+0*(zmax+1)+i;
        px=vtkData[rowNumber][0];
        py=vtkData[rowNumber][1];
        pz=vtkData[rowNumber][2];
        // qDebug()<<i << " "<<rowNumber<<std::abs(px)+std::abs(py)+std::abs(pz) ;
        if(std::abs(px)+std::abs(py)+std::abs(pz)>0.000001){
            nsub=i-1;
        }
    }
    qDebug()<<nfs<<" "<<nsub;
    for (i=1;i<xmax+2;i++){
        for (j=1;j<ymax+2;j++){
            for (k=1;k<nsub+2;k++){
                hold=k*(xmax+3)*(ymax+3)+j*(xmax+3)+i; //+3
                outputData[hold]=0;
            }
        }
    }
    for (i=1;i<xmax+2;i++){
        for (j=1;j<ymax+2;j++){
            for (k=nsub+2;k<nfs+2;k++){
                rowNumber=(i-1)*(zmax+1)*(ymax+1)+(j-1)*(zmax+1)+(k-1); //+3
                // qDebug()<<"vtkdata:"<<rowNumber;
                px=vtkData[rowNumber][0];
                py=vtkData[rowNumber][1];
                pz=vtkData[rowNumber][2];
                hold=k*(xmax+3)*(ymax+3)+j*(xmax+3)+i; //+3
                // qDebug()<<"outputdata"<<rowNumber;
                outputData[hold]=domainType(px,py,pz);
                if(outputData[hold]>=1 && outputData[hold]<9) mR++;
                if(outputData[hold]>=9 && outputData[hold]<21) mO++;
                if(outputData[hold]>=21 && outputData[hold]<27) mT++;
                if(outputData[hold]==-1) mN++;
                // if (outputData[hold]==0)qDebug()<<i<<" "<<j<<" "<<k<<" "<<px<<" "<<py<<" "<<pz<<" "<<outputData[hold] << " "<<domainType(px,py,pz) << " "<<hold;
                // outputData[rowNumber]=-1;
            }
        }
    }
    if(ymax==0){
        for (i=1;i<xmax+2;i++){
            for (k=1;k<nfs+2;k++){
                hold=k*(xmax+3)*(ymax+3)+(1)*(xmax+3)+i; //+3
                outputData[hold-xmax-3]=outputData[hold];
                outputData[hold+xmax+3]=outputData[hold];
            }
        }
    }
    mfilm=mR+mO+mT+mN;
    fR=mR/mfilm;
    fT=mT/mfilm;
    fO=mO/mfilm;
    fN=mN/mfilm;
    qDebug()<<mR<<" "<<mT<<" "<<mO<<" "<<mN;

    
    rowNumber=(x+3)*(y+3)*(z+3);

    std::ofstream output;
    std::string str;
//    QFileInfo filehold(filedir);
//    domainDir= QFileInfo(filehold.absolutePath()+"/"+filehold.baseName());
    str=filedir.toStdString()+".domain.vtk";
    const char *outdir=str.c_str();
    output.open(outdir);
    output << "# vtk DataFile Version 3.0\n";
    output << "Structured Points\n";
    output << "ASCII\n";
    output << "\n";
    output << "DATASET STRUCTURED_POINTS\n";
    output << "DIMENSIONS " << std::to_string(xmax+3) << " " << std::to_string(ymax+3) <<" "<< std::to_string(zmax+3) << "\n"; //+3
    output << "ORIGIN -1 -1 -1\n";
    output << "SPACING 1 1 1\n";
    output << "\n";
    output << "POINT_DATA " << std::to_string(rowNumber)+"\n";
    output << "SCALARS domain int\n";
    output << "LOOKUP_TABLE default\n";
    for (i=0;i<rowNumber;++i){
        output << outputData[i] << "\n";
    }
    output.close();
    for (int i=0;i<rowNumber;++i){
        //        qDebug()<<outputData[i];
        if (outputData[i]!=-1) {
            existDomain[outputData[i]]=true;
        }
    }
}

int SimpleView::domainType(double px,double py, double pz){
    double plot1=0,plot2=0,plot3=0;
    bool alongX=false,alongY=false,alongZ=false;
    int returnValue;
    int isROT;
    plot1=0.3;
    plot2=0.3;
    plot3=0.3;
    if(std::abs(px)>plot1) alongX=true;
    if(std::abs(py)>plot2) alongY=true;
    if(std::abs(pz)>plot3) alongZ=true;
    
    isROT=alongZ+alongY+alongX;
    returnValue=-1;
    // qDebug()<<px<<" "<<py<<" "<<pz<<" "<<alongX<<" "<<alongY<<" "<<alongZ<<" "<<isROT;
    if(isROT==3){ // Is a R phase
        if( px > plot1 &&  py > plot2 &&  pz > plot3) returnValue = 1; //R1+
        if(-px > plot1 && -py > plot2 && -pz > plot3) returnValue = 2; //R1-
        if(-px > plot1 &&  py > plot2 &&  pz > plot3) returnValue = 3; //R2+
        if( px > plot1 && -py > plot2 && -pz > plot3) returnValue = 4; //R2-
        if(-px > plot1 && -py > plot2 &&  pz > plot3) returnValue = 5; //R3+
        if( px > plot1 &&  py > plot2 && -pz > plot3) returnValue = 6; //R3-
        if( px > plot1 && -py > plot2 &&  pz > plot3) returnValue = 7; //R4+
        if(-px > plot1 &&  py > plot2 && -pz > plot3) returnValue = 8; //R4-
    }else if(isROT==2){ // Is a O phase
        if( px > plot1 &&  py > plot2 &&  std::abs(pz) < plot3) returnValue = 9;  //O1+
        if(-px > plot1 && -py > plot2 &&  std::abs(pz) < plot3) returnValue = 10; //O1-
        if( px > plot1 && -py > plot2 &&  std::abs(pz) < plot3) returnValue = 11; //O2+
        if(-px > plot1 &&  py > plot2 &&  std::abs(pz) < plot3) returnValue = 12; //O2-
        if( px > plot1 &&  std::abs(py) < plot2 &&  pz > plot3) returnValue = 13; //O3+
        if(-px > plot1 &&  std::abs(py) < plot2 && -pz > plot3) returnValue = 14; //O3-
        if( px > plot1 &&  std::abs(py) < plot2 && -pz > plot3) returnValue = 15; //O4+
        if(-px > plot1 &&  std::abs(py) < plot2 &&  pz > plot3) returnValue = 16; //O4-
        if( std::abs(px) < plot1 &&  py > plot2 &&  pz > plot3) returnValue = 17; //O5+
        if( std::abs(px) < plot1 && -py > plot2 && -pz > plot3) returnValue = 18; //O5-
        if( std::abs(px) < plot1 &&  py > plot2 && -pz > plot3) returnValue = 19; //O6+
        if( std::abs(px) < plot1 && -py > plot2 &&  pz > plot3) returnValue = 20; //O6-
    }else if(isROT==1){ // Is a T phase
        if( px > plot1 &&  std::abs(py) < plot2 &&  std::abs(pz) < plot3) returnValue = 21; //T1+
        if(-px > plot1 &&  std::abs(py) < plot2 &&  std::abs(pz) < plot3) returnValue = 22; //T1-
        if( std::abs(px) < plot1 &&  py > plot2 &&  std::abs(pz) < plot3) returnValue = 23; //T2+
        if( std::abs(px) < plot1 && -py > plot2 &&  std::abs(pz) < plot3) returnValue = 24; //T2-
        if( std::abs(px) < plot1 &&  std::abs(py) < plot2 &&  pz > plot3) returnValue = 25; //T3+
        if( std::abs(px) < plot1 &&  std::abs(py) < plot2 && -pz > plot3) returnValue = 26; //T3-
    }else if(isROT==0){
        if( (std::abs(px)+std::abs(py)+std::abs(pz)) <= 0.0001){
            returnValue = -1;
            // qDebug()<<(std::abs(px)+std::abs(py)+std::abs(pz))<<" "<<returnValue;
        }else{
            returnValue = -1;
            // qDebug()<<(std::abs(px)+std::abs(py)+std::abs(pz))<<" "<<returnValue;
        }
    }
    return returnValue;
}

void SimpleView::slotOpenFile_domain(){
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    if (!load.isEmpty()) {
        columns=loadData(load);
        qDebug()<<"after domain processing";
        int rows=(xmax+1)*(ymax+1)*(zmax+1);
        double *dataHold= new double[rows];
        existDomain.fill(false);
        QFileInfo filehold(load);
        this->ui->scalar_CB->setCheckState(Qt::Unchecked);
        this->ui->volume_CB->setCheckState(Qt::Unchecked);
        this->ui->vector_CB->setCheckState(Qt::Unchecked);
        this->ui->domain_CB->setCheckState(Qt::Checked);
        
        outputDomain(load,xmax,ymax,zmax);
        
        for (int i=0;i<27;i++){
            qDebug()<<i<<existDomain[i];
            if(existDomain[i]){
                this->ui->domain_LW->item(i)->setCheckState(Qt::Checked);
            }else{
                this->ui->domain_LW->item(i)->setCheckState(Qt::Unchecked);
            }
        }

        
        this->ui->inputFileDomain->setText(filehold.fileName());
        
        printstatus = QString::fromStdString(std::to_string(columns));
        this->ui->rowcolDomain->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(xmax));
        this->ui->xMinMaxDomain->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(ymax));
        this->ui->yMinMaxDomain->setText(printstatus);
        
        printstatus = QString::fromStdString("0 - "+std::to_string(zmax));
        this->ui->zMinMaxDomain->setText(printstatus);
        
        this->ui->domain_Table->clearContents();
        for (int i=0; i<this->ui->domain_Table->rowCount(); i++) {
            this->ui->domain_Table->removeRow(i);
        }
        for(int i=0;i<columns;++i){
            for (int j=0;j<rows;++j){
                dataHold[j]=vtkData[j][i];
            }
            // qDebug()<<i<<" "<<dataHold[i];
            this->ui->domain_Table->insertRow(this->ui->domain_Table->rowCount());
            printstatus = QString::fromStdString(std::to_string(getMin(dataHold,rows)));
            this->ui->domain_Table->setItem(this->ui->domain_Table->rowCount()-1,0,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getMax(dataHold,rows)));
            this->ui->domain_Table->setItem(this->ui->domain_Table->rowCount()-1,1,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getAvg(dataHold,rows)));
            this->ui->domain_Table->setItem(this->ui->domain_Table->rowCount()-1,2,new QTableWidgetItem(printstatus));
        }
//        this->ui->information_Tab->setCurrentIndex(2);
        qDebug()<<"before vtk part"<<domainDir.absoluteFilePath()+".domain.vtk";
        drawDomain(domainDir.absoluteFilePath().toStdString()+".domain.vtk");
        delete this->vtkData;
    }
}


void SimpleView::drawDomain(std::string domainName){
    const char* fileNameDomain=domainName.c_str();
    //  int extent[6];
//    double domain_range[2];
    //  double sumValue;
    //  double vmin,vmax;
    double** domainRGB;
    std::ifstream domainFile(domainName);
    
    domainRGB=new double*[27];
    for (int i=0;i<27;++i){
        domainRGB[i] = new double[3];
    }
    qDebug()<<"before color";
    
    VTK_CREATE(vtkRenderer,domainRenderer);
    VTK_CREATE(vtkDataSetReader, readerDomainOrigin);
    domainRGB[0][0]=0.752912;domainRGB[0][1]=0.752912;domainRGB[0][2]=0.752912; //sub
    domainRGB[1][0]=0;domainRGB[1][1]=0;domainRGB[1][2]=1;  //R1+
    domainRGB[2][0]=0.46;domainRGB[2][1]=0.7175;domainRGB[2][2]=0.8135; //R1-
    domainRGB[3][0]=0;domainRGB[2][1]=0.1537870;domainRGB[3][2]=0.0; //R2+
    domainRGB[4][0]=0;domainRGB[4][1]=1;domainRGB[4][2]=0; //R2-
    domainRGB[5][0]=1;domainRGB[5][1]=0;domainRGB[5][2]=0; //R3+
    domainRGB[6][0]=1;domainRGB[6][1]=0.566921;domainRGB[6][2]=0.633741; //R3-
    domainRGB[7][0]=1;domainRGB[7][1]=0.418685;domainRGB[7][2]=0; //R4+
    domainRGB[8][0]=1;domainRGB[8][1]=1;domainRGB[8][2]=0; //R4-
    domainRGB[9][0]=1;domainRGB[9][1]=0;domainRGB[9][2]=1; //O1+
    domainRGB[10][0]=0.64629;domainRGB[10][1]=0.130165;domainRGB[10][2]=0.130165; //O1-
    domainRGB[11][0]=0.9;domainRGB[11][1]=0.566921;domainRGB[11][2]=0.633741; //O2+
    domainRGB[12][0]=0.751111;domainRGB[12][1]=0.393695;domainRGB[12][2]=0.751111; //O2-
    domainRGB[13][0]=0.418685;domainRGB[13][1]=0.027128;domainRGB[13][2]=0.027128; //O3+
    domainRGB[14][0]=0.678201;domainRGB[14][1]=0.498270;domainRGB[14][2]=0.301423; //O3-
    domainRGB[15][0]=0.476371;domainRGB[15][1]=0.035432;domainRGB[15][2]=0.14173; //O4+
    domainRGB[16][0]=0.961169;domainRGB[16][1]=0.251965;domainRGB[16][2]=0.199862; //O4-
    domainRGB[17][0]=0.355309;domainRGB[17][1]=0.968874;domainRGB[17][2]=0.355309; //O5+
    domainRGB[18][0]=0.038446;domainRGB[18][1]=0.646290;domainRGB[18][2]=0.038446; //O5-
    domainRGB[19][0]=0.766921;domainRGB[19][1]=0.766921;domainRGB[19][2]=0.766921; //O6+
    domainRGB[20][0]=0.169550;domainRGB[20][1]=0.169550;domainRGB[20][2]=0.169550; //O6-
    domainRGB[21][0]=0.566921;domainRGB[21][1]=0.566921;domainRGB[21][2]=0.566921; //a1+
    domainRGB[22][0]=0.393695;domainRGB[22][1]=0.015747;domainRGB[22][2]=0.885813; //a1-
    domainRGB[23][0]=0.0;domainRGB[23][1]=0.0;domainRGB[23][2]=0.0; //a2+
    domainRGB[24][0]=1.0;domainRGB[24][1]=0.710881;domainRGB[24][2]=0.0; //a2-
    domainRGB[25][0]=0.885813;domainRGB[25][1]=0.813533;domainRGB[25][2]=0.301423; //c+
    domainRGB[26][0]=0.8867188;domainRGB[26][1]=0.4335937;domainRGB[26][2]=0.0273438; //c-
    qDebug()<<"after color"<<domainRGB[0][2];
    
    VTK_CREATE(vtkExtractVOI,readerDomain);
    // renWinInteractor->SetRenderWindow(this->ui->qvtkWidget->GetRenderWindow());
    
    readerDomainOrigin->SetFileName(fileNameDomain);
    qDebug() << readerDomainOrigin << fileNameDomain;
    readerDomainOrigin->Update();
//    readerDomainOrigin->GetOutput()->GetPointData()->GetScalars()->GetRange(domain_range);
//    qDebug()<<domain_range;
    readerDomain->SetInputConnection(readerDomainOrigin->GetOutputPort());
    readerDomain->SetVOI(0,xmax+2,0,ymax+2,0,zmax+2);
    readerDomain->Update();
    
    double R[3];
    
    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(domainRenderer);
        qDebug()<<"domain renderer";
    }else{
        qDebug()<<"false domain renderer";
        domainRenderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    }
    
    for(int i=0;i<27;i++){
        VTK_CREATE(vtkThreshold,domainThreshold);
        VTK_CREATE(vtkDataSetSurfaceFilter,domainSurface);
        VTK_CREATE(vtkSmoothPolyDataFilter,domainSmooth);
        VTK_CREATE(vtkPolyDataNormals,normalGenerator);
        VTK_CREATE(vtkDataSetMapper,domainMapper);
//        qDebug()<<"create the domain"<<i;
        readerDomain->Update();
        domainThreshold->SetInputConnection(readerDomain->GetOutputPort());
        domainThreshold->AllScalarsOff();
        domainThreshold->ThresholdBetween(i-0.5,i+0.5);
        domainThreshold->Update();
//        qDebug()<<"before surface"<<i;
        domainSurface->SetInputData(domainThreshold->GetOutput());
        domainSurface->Update();
        domainSmooth->SetInputConnection(domainSurface->GetOutputPort());
        domainSmooth->SetNumberOfIterations(30);
        domainSmooth->SetRelaxationFactor(0.1);
        domainSmooth->FeatureEdgeSmoothingOff();
        domainSmooth->BoundarySmoothingOn();
        domainSmooth->Update();
        normalGenerator->SetInputData(domainSmooth->GetOutput());
        normalGenerator->ComputePointNormalsOn();
        normalGenerator->ComputeCellNormalsOn();
        normalGenerator->Update();
        domainMapper->SetInputConnection(normalGenerator->GetOutputPort());
        domainMapper->ScalarVisibilityOff();
        domainMapper->Update();
        actorDomain[i]->SetMapper(domainMapper);
//        qDebug()<<domainRGB[i][0]<<" "<<domainRGB[i][1]<<" "<<domainRGB[i][2];
        actorDomain[i]->GetProperty()->SetColor(domainRGB[i][0],domainRGB[i][1],domainRGB[i][2]);
        actorDomain[i]->GetProperty()->GetColor(R);
//        qDebug()<<"out "<<R[0]<<" "<<R[1]<<" "<<R[2];
        // actorDomain[i]->GetProperty()->SetDiffuseColor(domainRGB[i][0],domainRGB[i][1],domainRGB[i][2]);
        // actorDomain[i]->GetProperty()->SetRepresentationToSurface();
        actorDomain[i]->Modified();
        actorDomain[i]->SetVisibility(true);
        domainRenderer->AddActor(actorDomain[i]);
    }
    // actorDomain[0]->SetVisibility(false);
    // actorDomain[25]->GetProperty()->SetColor(1,0,0);
    // actorDomain[25]->GetBackfaceProperty()->SetColor(1,0,0);
    
    
    // if(this->ui->domain_CB->checkState()==0){
    //   actorDomain[0]->SetVisibility(false);
    // }else{
    //   actorDomain[0]->SetVisibility(true);
    // }
    
    VTK_CREATE(vtkOutlineFilter,outlineDomain);
    VTK_CREATE(vtkDataSetMapper,outlineDomainMapper);
    outlineDomain->SetInputConnection(readerDomainOrigin->GetOutputPort());
    outlineDomainMapper->SetInputConnection(outlineDomain->GetOutputPort());
    outlineDomainActor->SetMapper(outlineDomainMapper);
    outlineDomainActor->GetProperty()->SetColor(0,1,0);

    domainRenderer->SetBackground(0.9,0.9,0.9);
    domainRenderer->AddActor(outlineDomainActor);
    
    if(!reset){domainRenderer->SetActiveCamera(camera);}
    
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->update();
    
    camera=domainRenderer->GetActiveCamera();
    reset=false;
    
}

void SimpleView::on_domain_LW_itemChanged(QListWidgetItem *item){
    int i=0;
    i=this->ui->domain_LW->row(item);
    if(item->checkState()){
        actorDomain[i]->SetVisibility(true);
    }else{
        actorDomain[i]->SetVisibility(false);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->update();

}

void SimpleView::on_domain_CB_stateChanged(int state){
    if(state==0){
        this->ui->domain_LW->setEnabled(false);
        outlineDomainActor->SetVisibility(false);
        for(int i=0;i<27;i++){
            actorDomain[i]->SetVisibility(false);
        }
    }else{
        outlineDomainActor->SetVisibility(true);
        this->ui->domain_LW->setEnabled(true);
        for(int i=0;i<27;i++){
            actorDomain[i]->SetVisibility(true);
        }
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->update();

}


void SimpleView::saveImage(){
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptSave);
    filedialog.setDefaultSuffix("png");
    QString load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Images (*.png)"));
    qDebug()<<load;
    if(this->ui->stackedWidget->currentIndex()==0){
        outputImage(load);
    }else{
        this->ui->customPlot->savePng(load);
    }
    this->ui->qvtkWidget->update();
}

void SimpleView::outputImage(QString load){
    VTK_CREATE(vtkWindowToImageFilter, windowToImage);
    windowToImage->SetInput(this->ui->qvtkWidget->GetRenderWindow());
    windowToImage->SetMagnification(5);
    windowToImage->SetInputBufferTypeToRGBA();
    windowToImage->FixBoundaryOff();
    windowToImage->ReadFrontBufferOn();
    windowToImage->Update();
    VTK_CREATE(vtkPNGWriter, writer);
    writer->SetFileName(load.toStdString().c_str());
    writer->SetInputConnection(windowToImage->GetOutputPort());
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    windowToImage->Modified();
    writer->Write();
//    this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();
    this->ui->qvtkWidget->GetRenderWindow()->Render();

}

void SimpleView::slotUpdateCamera1(){
    updateCamera(1);
}

void SimpleView::slotUpdateCamera2(){
    updateCamera(2);
}

void SimpleView::slotUpdateCamera3(){
    updateCamera(3);
}

void SimpleView::slotUpdateCamera4(){
    updateCamera(4);
}

void SimpleView::slotUpdateCamera5(){
    updateCamera(5);
}

void SimpleView::slotUpdateCamera6(){
    updateCamera(6);
}


void SimpleView::updateCamera(int choice){
    switch (choice) {
        case -1:
            camera->SetPosition(3*ymax+ymax+zmax, 3*xmax+ymax+zmax, zmax+xmax+ymax);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 0:
            break;
        case 1:
            camera->SetPosition(-3*xmax-ymax*2-zmax*2, ymax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 2:
            camera->SetPosition(3*xmax+ymax*2+zmax*2, ymax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 3:
            camera->SetPosition(xmax/2, -3*ymax-xmax*2-zmax*2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 4:
            camera->SetPosition(xmax/2, 3*ymax+xmax*2+zmax*2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 5:
            camera->SetPosition(xmax/2, ymax/2, -3*zmax-ymax*2-xmax*2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 1, 0);
            break;
        case 6:
            camera->SetPosition(xmax/2, ymax/2, 3*zmax+ymax*2+xmax*2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 1, 0);
            break;
        default:
            camera->SetPosition(xmax/2, 3*ymax+xmax*2+zmax*2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
    }
    qDebug()<<"updateCamera"<<choice;
    this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->SetActiveCamera(camera);
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->GetRenderWindow()->GetInteractor()->Render();
    this->ui->qvtkWidget->update();
    this->update();
    camera=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
    reset=false;
}

void SimpleView::updateExtraction(int x,int y, int z){
    if (xmaxAll<x-1) {
        xmaxAll=x-1;
    }
    if (ymaxAll<y-1) {
        ymaxAll=y-1;
    }
    if (zmaxAll<z-1) {
        zmaxAll=z-1;
    }
    xminAll=0;
    yminAll=0;
    zminAll=0;
    xmax=x-1;
    ymax=y-1;
    zmax=z-1;
    xmin=0;
    ymin=0;
    zmin=0;
    this->ui->xmin_LE->setText(QString::fromStdString(std::to_string(xminAll)));
    this->ui->ymin_LE->setText(QString::fromStdString(std::to_string(yminAll)));
    this->ui->zmin_LE->setText(QString::fromStdString(std::to_string(zminAll)));
    this->ui->xmax_LE->setText(QString::fromStdString(std::to_string(xmaxAll)));
    this->ui->ymax_LE->setText(QString::fromStdString(std::to_string(ymaxAll)));
    this->ui->zmax_LE->setText(QString::fromStdString(std::to_string(zmaxAll)));
}






void SimpleView::on_plot1DGeneral_LW_currentRowChanged(int index){
    this->ui->plot1DGeneral_SW->setCurrentIndex(index);
}

void SimpleView::on_plot1DXGrid_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->customPlot->xAxis->grid()->setVisible(true);
    }else{
        this->ui->customPlot->xAxis->grid()->setVisible(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DYGrid_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->customPlot->yAxis->grid()->setVisible(true);
    }else{
        this->ui->customPlot->yAxis->grid()->setVisible(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DAutoTickX1_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->plot1DTickValueX1_LE->setEnabled(false);
        this->ui->plot1DTickLabelX1_LE->setEnabled(false);
    }else{
        this->ui->plot1DTickValueX1_LE->setEnabled(true);
        this->ui->plot1DTickLabelX1_LE->setEnabled(true);
    }
}

void SimpleView::on_plot1DAutoTickX2_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->plot1DTickValueX2_LE->setEnabled(false);
        this->ui->plot1DTickLabelX2_LE->setEnabled(false);
    }else{
        this->ui->plot1DTickValueX2_LE->setEnabled(true);
        this->ui->plot1DTickLabelX2_LE->setEnabled(true);
    }
}

void SimpleView::on_plot1DAutoTickY1_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->plot1DTickValueY1_LE->setEnabled(false);
        this->ui->plot1DTickLabelY1_LE->setEnabled(false);
    }else{
        this->ui->plot1DTickValueY1_LE->setEnabled(true);
        this->ui->plot1DTickLabelY1_LE->setEnabled(true);
    }
}

void SimpleView::on_plot1DAutoTickY2_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->plot1DTickValueY2_LE->setEnabled(false);
        this->ui->plot1DTickLabelY2_LE->setEnabled(false);
    }else{
        this->ui->plot1DTickValueY2_LE->setEnabled(true);
        this->ui->plot1DTickLabelY2_LE->setEnabled(true);
    }
}

void SimpleView::on_plot1DAxisX1_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->customPlot->xAxis->setVisible(true);
        this->ui->plot1DAutoTickX1_CB->setEnabled(true);
        this->ui->plot1DRangeMaxX1_LE->setEnabled(true);
        this->ui->plot1DRangeMinX1_LE->setEnabled(true);
        this->ui->plot1DLabelX1_LE->setEnabled(true);
        this->ui->plot1DTickLabelX1_CB->setEnabled(true);
    }else{
        this->ui->customPlot->xAxis->setVisible(false);
        this->ui->plot1DAutoTickX1_CB->setEnabled(false);
        this->ui->plot1DRangeMaxX1_LE->setEnabled(false);
        this->ui->plot1DRangeMinX1_LE->setEnabled(false);
        this->ui->plot1DLabelX1_LE->setEnabled(false);
        this->ui->plot1DTickLabelX1_CB->setEnabled(false);

    }
    this->ui->customPlot->replot();
}


void SimpleView::on_plot1DAxisX2_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->customPlot->xAxis2->setVisible(true);
        this->ui->plot1DAutoTickX2_CB->setEnabled(true);
        this->ui->plot1DRangeMaxX2_LE->setEnabled(true);
        this->ui->plot1DRangeMinX2_LE->setEnabled(true);
        this->ui->plot1DLabelX2_LE->setEnabled(true);
        this->ui->plot1DTickLabelX2_CB->setEnabled(true);

    }else{
        this->ui->customPlot->xAxis2->setVisible(false);
        this->ui->plot1DAutoTickX2_CB->setEnabled(false);
        this->ui->plot1DRangeMaxX2_LE->setEnabled(false);
        this->ui->plot1DRangeMinX2_LE->setEnabled(false);
        this->ui->plot1DLabelX2_LE->setEnabled(false);
        this->ui->plot1DTickLabelX2_CB->setEnabled(false);

    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DAxisY1_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->customPlot->yAxis->setVisible(true);
        this->ui->plot1DAutoTickY1_CB->setEnabled(true);
        this->ui->plot1DRangeMaxY1_LE->setEnabled(true);
        this->ui->plot1DRangeMinY1_LE->setEnabled(true);
        this->ui->plot1DLabelY1_LE->setEnabled(true);
        this->ui->plot1DTickLabelY1_CB->setEnabled(true);

    }else{
        this->ui->customPlot->yAxis->setVisible(false);
        this->ui->plot1DAutoTickY1_CB->setEnabled(false);
        this->ui->plot1DRangeMaxY1_LE->setEnabled(false);
        this->ui->plot1DRangeMinY1_LE->setEnabled(false);
        this->ui->plot1DLabelY1_LE->setEnabled(false);
        this->ui->plot1DTickLabelY1_CB->setEnabled(false);

    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DAxisY2_CB_stateChanged(int state){
    qDebug()<<state;
    if (state) {
        this->ui->customPlot->yAxis2->setVisible(true);
        this->ui->plot1DAutoTickY2_CB->setEnabled(true);
        this->ui->plot1DRangeMaxY2_LE->setEnabled(true);
        this->ui->plot1DRangeMinY2_LE->setEnabled(true);
        this->ui->plot1DLabelY2_LE->setEnabled(true);
        this->ui->plot1DTickLabelY2_CB->setEnabled(true);

    }else{
        this->ui->customPlot->yAxis2->setVisible(false);
        this->ui->plot1DAutoTickY2_CB->setEnabled(false);
        this->ui->plot1DRangeMaxY2_LE->setEnabled(false);
        this->ui->plot1DRangeMinY2_LE->setEnabled(false);
        this->ui->plot1DLabelY2_LE->setEnabled(false);
        this->ui->plot1DTickLabelY2_CB->setEnabled(false);

    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DTickLabelX1_CB_stateChanged(int state){
    if(state){
        this->ui->customPlot->xAxis->setTickLabels(true);
    }else{
        this->ui->customPlot->xAxis->setTickLabels(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DTickLabelY1_CB_stateChanged(int state){
    if(state){
        this->ui->customPlot->yAxis->setTickLabels(true);
    }else{
        this->ui->customPlot->yAxis->setTickLabels(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DTickLabelX2_CB_stateChanged(int state){
    if(state){
        this->ui->customPlot->xAxis2->setTickLabels(true);
    }else{
        this->ui->customPlot->xAxis2->setTickLabels(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DTickLabelY2_CB_stateChanged(int state){
    if(state){
        this->ui->customPlot->yAxis2->setTickLabels(true);
    }else{
        this->ui->customPlot->yAxis2->setTickLabels(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DLegend_CB_stateChanged(int state){
    if(state){
        this->ui->customPlot->legend->setVisible(true);
        this->ui->plot1DLegendX_LE->setEnabled(true);
        this->ui->plot1DLegendY_LE->setEnabled(true);
        this->ui->plot1DLegendW_LE->setEnabled(true);
        this->ui->plot1DLegendH_LE->setEnabled(true);
        this->ui->plot1DLegendX_LB->setEnabled(true);
        this->ui->plot1DLegendY_LB->setEnabled(true);
        this->ui->plot1DLegendW_LB->setEnabled(true);
        this->ui->plot1DLegendH_LB->setEnabled(true);
        int x=this->ui->plot1DLegendX_LE->text().toDouble();
        int y=this->ui->plot1DLegendY_LE->text().toDouble();
        int w=this->ui->plot1DLegendW_LE->text().toDouble();
        int h=this->ui->plot1DLegendH_LE->text().toDouble();
        this->ui->customPlot->legend->setOuterRect(QRect(x, y, w, h));
    }else{
        this->ui->customPlot->legend->setVisible(false);
        this->ui->plot1DLegendX_LE->setEnabled(false);
        this->ui->plot1DLegendY_LE->setEnabled(false);
        this->ui->plot1DLegendW_LE->setEnabled(false);
        this->ui->plot1DLegendH_LE->setEnabled(false);
        this->ui->plot1DLegendX_LB->setEnabled(false);
        this->ui->plot1DLegendY_LB->setEnabled(false);
        this->ui->plot1DLegendW_LB->setEnabled(false);
        this->ui->plot1DLegendH_LB->setEnabled(false);
    }
    this->ui->customPlot->replot();
}

void SimpleView::on_plot1DFont_CB_stateChanged(int state){
    qDebug()<<"font CB"<<state;
    if(!state){
        this->ui->plot1DFont_fontComboBox->setEnabled(true);
        this->ui->plot1DTitleFontSize_LE->setEnabled(true);
        this->ui->plot1DAxisFontSize_LE->setEnabled(true);
        this->ui->plot1DTickFontSize_LE->setEnabled(true);
        this->ui->plot1DLegendFontSize_LE->setEnabled(true);
        this->ui->plot1DTitleFontSize_LB->setEnabled(true);
        this->ui->plot1DAxisFontSize_LB->setEnabled(true);
        this->ui->plot1DTickFontSize_LB->setEnabled(true);
        this->ui->plot1DLegendFontSize_LB->setEnabled(true);
    }else{
        this->ui->plot1DFont_fontComboBox->setEnabled(false);
        this->ui->plot1DTitleFontSize_LE->setEnabled(false);
        this->ui->plot1DAxisFontSize_LE->setEnabled(false);
        this->ui->plot1DTickFontSize_LE->setEnabled(false);
        this->ui->plot1DLegendFontSize_LE->setEnabled(false);
        this->ui->plot1DTitleFontSize_LB->setEnabled(false);
        this->ui->plot1DAxisFontSize_LB->setEnabled(false);
        this->ui->plot1DTickFontSize_LB->setEnabled(false);
        this->ui->plot1DLegendFontSize_LB->setEnabled(false);
    }
}

void SimpleView::on_isosurface_CB_stateChanged(int state){
    if(state){
        this->ui->isoValue_LE->setEnabled(true);
        this->ui->isoValue_LB->setEnabled(true);
        this->ui->isoAdd_PB->setEnabled(true);
        this->ui->isoDelete_PB->setEnabled(true);
        this->ui->isosurface_LW->setEnabled(true);
        
    }else{
        this->ui->isoValue_LE->setEnabled(false);
        this->ui->isoValue_LB->setEnabled(false);
        this->ui->isoAdd_PB->setEnabled(false);
        this->ui->isoDelete_PB->setEnabled(false);
        this->ui->isosurface_LW->setEnabled(false);
    }
    int index=this->ui->RGB_Combo->currentIndex();
    
    if (index==3){
        this->ui->RGBIso_SW->setEnabled(true);
        if (this->ui->isosurface_CB->isChecked()) {
            this->ui->isoValue_Combo->setEnabled(true);
            this->ui->RGBValue_LE->setEnabled(true);
            this->ui->RGBR_LE->setEnabled(true);
            this->ui->RGBG_LE->setEnabled(true);
            this->ui->RGBB_LE->setEnabled(true);
            this->ui->RGBIso_Table->setEnabled(true);
            this->ui->RGB_Stack->setEnabled(true);
        }else{
            this->ui->isoValue_Combo->setEnabled(false);
            this->ui->RGBValue_LE->setEnabled(false);
            this->ui->RGBR_LE->setEnabled(false);
            this->ui->RGBG_LE->setEnabled(false);
            this->ui->RGBB_LE->setEnabled(false);
            this->ui->RGBIso_Table->setEnabled(false);
            this->ui->RGB_Stack->setEnabled(false);
        }
    }

}

void SimpleView::on_isoAdd_PB_released(){
    if (!this->ui->isoValue_LE->text().isEmpty()) {
        QList<QListWidgetItem *> item=this->ui->isosurface_LW->findItems(this->ui->isoValue_LE->text(), Qt::MatchExactly);
        if (item.size()==0) {
            actorIso.push_back(vtkActor::New());
            int row=this->ui->isosurface_LW->count();
            QString text=this->ui->isoValue_LE->text();
            this->ui->isosurface_LW->insertItem(row, text);
            this->ui->isosurface_LW->item(row)->setFlags(this->ui->isosurface_LW->item(row)->flags() | Qt::ItemIsUserCheckable);
            this->ui->isosurface_LW->item(row)->setCheckState(Qt::Checked);
            this->ui->isoValue_Combo->addItem(text);
        }
    }
}

void SimpleView::on_isosurface_LW_itemChanged(QListWidgetItem *item){
    int i=0;
    i=this->ui->isosurface_LW->row(item);
    if(item->checkState()){
        actorIso[i]->SetVisibility(true);
    }else{
        actorIso[i]->SetVisibility(false);
    }
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->update();

}


void SimpleView::on_isoDelete_PB_released(){
    if (this->ui->isosurface_LW->selectedItems().count()>0) {
        this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(actorIso[this->ui->isosurface_LW->currentRow()]);
        actorIso.removeAt(this->ui->isosurface_LW->currentRow());
        QString text=this->ui->isosurface_LW->currentItem()->text();
        int comboRow=this->ui->isoValue_Combo->findText(text);
        this->ui->isosurface_LW->takeItem(this->ui->isosurface_LW->currentRow());
        this->ui->isoValue_Combo->removeItem(comboRow);
        QList<QTableWidgetItem*> item=this->ui->RGBIso_Table->findItems(text, Qt::MatchExactly);
        for (int i=0; i<item.size(); i++) {
            if(this->ui->RGBIso_Table->column(item[i])==0){
                this->ui->RGBIso_Table->removeRow(this->ui->RGBIso_Table->row(item[i]));
                break;
            }else{
                continue;
            }
        }
    }
    qDebug()<<"check iso"<<actorIso.count()<<this->ui->isosurface_LW->count();
    this->ui->qvtkWidget->GetRenderWindow()->Render();
    this->ui->qvtkWidget->update();


}

void SimpleView::drawIsoSurface(vtkAlgorithmOutput * readerScalarPort){
    VTK_CREATE(vtkRenderer, isoRenderer);
//    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
//        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(isoRenderer);
//    }else{
        isoRenderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
//    }
    int contourNum=0;
    contourNum=this->ui->isosurface_LW->count();
    
    for (int i=0; i<contourNum; i++) {
        VTK_CREATE(vtkMarchingCubes, contour);
        VTK_CREATE(vtkDataSetMapper, contourMapper);
        contour->SetInputConnection(readerScalarPort);
        contour->SetValue(0,this->ui->isosurface_LW->item(i)->text().toDouble());
        contour->ComputeNormalsOn();
        contourMapper->SetInputConnection(contour->GetOutputPort());
        actorIso[i]->SetMapper(contourMapper);
        qDebug()<<"actorISo:"<<i;
        isoRenderer->RemoveActor(actorIso[i]);
        isoRenderer->AddActor(actorIso[i]);
        qDebug()<<"isorenderer:"<<isoRenderer->GetNumberOfPropsRendered();
    }
    
    for (int i=0; i<this->ui->RGBIso_Table->rowCount(); i++) {
        int isoNum=this->ui->isosurface_LW->row(this->ui->isosurface_LW->findItems(this->ui->RGBIso_Table->item(i, 0)->text(), Qt::MatchExactly).first());
        double r=this->ui->RGBIso_Table->item(i, 1)->text().toDouble()/255;
        double g=this->ui->RGBIso_Table->item(i, 2)->text().toDouble()/255;
        double b=this->ui->RGBIso_Table->item(i, 3)->text().toDouble()/255;
        qDebug()<<"rgbisonum:"<<isoNum<<r<<g<<b<<actorIso.size();
        actorIso[isoNum]->GetMapper()->ScalarVisibilityOff();
        actorIso[isoNum]->GetProperty()->SetColor(r, g, b);
        //        actorIso[isoNum]->GetProperty()->SetRepresentationToSurface();
    }

    

    if(!reset){isoRenderer->SetActiveCamera(camera);}
    
//    this->ui->qvtkWidget->GetRenderWindow()->Render();
//    this->ui->qvtkWidget->update();

    camera=isoRenderer->GetActiveCamera();
    reset=false;

}

void SimpleView::on_cameraSet_PB_released(){
    double positionX,positionY,positionZ;
    double focalX,focalY,focalZ;
    double viewX,viewY,viewZ;
    positionX=this->ui->cameraPositionX_LE->text().toDouble();
    positionY=this->ui->cameraPositionY_LE->text().toDouble();
    positionZ=this->ui->cameraPositionZ_LE->text().toDouble();
    focalX=this->ui->cameraFocalX_LE->text().toDouble();
    focalY=this->ui->cameraFocalY_LE->text().toDouble();
    focalZ=this->ui->cameraFocalZ_LE->text().toDouble();
    viewX=this->ui->cameraViewUpX_LE->text().toDouble();
    viewY=this->ui->cameraViewUpY_LE->text().toDouble();
    viewZ=this->ui->cameraViewUpZ_LE->text().toDouble();
    camera->SetPosition(positionX, positionY, positionZ);
    camera->SetFocalPoint(focalX, focalY, focalZ);
    camera->SetViewUp(viewX, viewY, viewZ);
    updateCamera(0);
}

void SimpleView::outputStatus(QFileInfo filedir){
    std::ofstream output;
    output.open(filedir.absoluteFilePath().toStdString().c_str());
    output << this->ui->outline_CB->checkState() << endl;
    output << this->ui->scalarBar_CB->checkState() << endl;
    output << this->ui->axis_CB->checkState() << endl;
    output << this->ui->extract_CB->checkState() << endl;
    output << this->ui->xmin_LE->text().toDouble() << " " << this->ui->xmax_LE->text().toDouble() << endl;
    output << this->ui->ymin_LE->text().toDouble() << " " << this->ui->ymax_LE->text().toDouble() << endl;
    output << this->ui->zmin_LE->text().toDouble() << " " << this->ui->zmax_LE->text().toDouble() << endl;
    output << this->ui->cameraPositionX_LE->text().toDouble() << " " << this->ui->cameraPositionY_LE->text().toDouble() << " " << this->ui->cameraPositionZ_LE->text().toDouble() << endl;
    output << this->ui->cameraFocalX_LE->text().toDouble() << " " << this->ui->cameraFocalY_LE->text().toDouble() << " " << this->ui->cameraFocalZ_LE->text().toDouble() << endl;
    output << this->ui->cameraViewUpX_LE->text().toDouble()<< " " << this->ui->cameraViewUpY_LE->text().toDouble()<< " " << this->ui->cameraViewUpZ_LE->text().toDouble()<< endl;
    output << this->ui->RGBScalar_Table->rowCount() <<endl;
    //output for the scalar RGB table
    for (int i=0; i<this->ui->RGBScalar_Table->rowCount(); i++) {
        output << this->ui->RGBScalar_Table->item(i, 0)->text().toDouble()<< " " << this->ui->RGBScalar_Table->item(i, 1)->text().toInt()<< " " << this->ui->RGBScalar_Table->item(i, 2)->text().toInt()<< " " << this->ui->RGBScalar_Table->item(i, 3)->text().toInt()<< endl;
    }
    output <<this->ui->RGBVector_Table->rowCount()<<endl;
    //output for the vector RGb table
    for (int i=0; i<this->ui->RGBVector_Table->rowCount(); i++) {
        output << this->ui->RGBVector_Table->item(i, 0)->text().toDouble()<< " " << this->ui->RGBVector_Table->item(i, 1)->text().toInt()<< " " << this->ui->RGBVector_Table->item(i, 2)->text().toInt()<< " " << this->ui->RGBVector_Table->item(i, 3)->text().toInt()<< endl;
    }
    //output for the iso RGB table
    output <<this->ui->RGBIso_Table->rowCount()<<endl;
    for (int i=0; i<this->ui->RGBIso_Table->rowCount(); i++) {
        output << this->ui->RGBIso_Table->item(i, 0)->text().toDouble()<< " " << this->ui->RGBIso_Table->item(i, 1)->text().toInt()<< " " << this->ui->RGBIso_Table->item(i, 2)->text().toInt()<< " " << this->ui->RGBIso_Table->item(i, 3)->text().toInt()<< endl;
    }
    //output for the scalar alpha table
    output << this->ui->alphaScalar_Table->rowCount()<<endl;
    for (int i=0; i<this->ui->alphaScalar_Table->rowCount(); i++) {
        output << this->ui->alphaScalar_Table->item(i, 0)->text().toDouble()<< " " << this->ui->alphaScalar_Table->item(i, 1)->text().toDouble()<< endl;
    }
    
    //output for the scalar tab
    output << this->ui->scalar_CB->checkState() << endl;
    output << this->ui->scalarChoice->count() << endl;
    output << this->ui->scalarChoice->currentIndex() << endl;
    output << this->ui->volume_CB->checkState() << endl;
    output << this->ui->scalarRange_CB->checkState() << endl;
    output << this->ui->scalarValueMin_LE->text().toDouble() << " " << this->ui->scalarValueMax_LE->text().toDouble()<< endl;
    output << this->ui->slice_CB->checkState() << endl;
    output << this->ui->sliceOriginX->text().toDouble() << " " << this->ui->sliceOriginY->text().toDouble() << " " << this->ui->sliceOriginZ->text().toDouble() << endl;
    output << this->ui->sliceNormalX->text().toDouble() << " " << this->ui->sliceNormalY->text().toDouble() << " " << this->ui->sliceNormalZ->text().toDouble() << endl;
    // output for the isosurface list widget
    output << this->ui->isosurface_CB->checkState() <<endl;
    output << this->ui->isosurface_LW->count() << endl;
    for (int i=0; i<this->ui->isosurface_LW->count(); i++) {
        output << this->ui->isosurface_LW->item(i)->text().toDouble() << " " << this->ui->isosurface_LW->item(i)->checkState() <<endl;
    }
    
    //output for the vector tab
    output << this->ui->vector_CB->checkState()<<endl;
    output << this->ui->vectorChoice->count()<<endl;
    output << this->ui->vectorChoice->currentIndex()<<endl;
    output << this->ui->vectorGlyph_CB->checkState()<<endl;
    output << this->ui->vectorScale_LE->text().toDouble()<<endl;
    output << this->ui->vectorRange_CB->checkState()<<endl;
    output << this->ui->vectorValueMin_LE->text().toDouble()<< " " << this->ui->vectorValueMax_LE->text().toDouble()<<endl;
    output << this->ui->streamline_CB->checkState()<<endl;
    output << this->ui->seedNumber_LE->text().toInt()<<endl;
    output << this->ui->seedRadius_LE->text().toDouble()<<endl;
    output << this->ui->seedCenterX_LE->text().toDouble()<< " " << this->ui->seedCenterY_LE->text().toDouble()<< " " << this->ui->seedCenterZ_LE->text().toDouble()<<endl;
    output << this->ui->streamStepLength_LE->text().toDouble()<<endl;
//    output << this->ui->streamIntStepLength_LE->text().toDouble()<<endl;
    
    // output for the domain tab
    output << this->ui->domain_CB->checkState()<<endl;
    for (int i=0; i<this->ui->domain_LW->count(); i++) {
        output << this->ui->domain_LW->item(i)->checkState()<<endl;
    }

    output.close();
}

void SimpleView::slotOutputStatus(){
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptSave);
    filedialog.setDefaultSuffix("txt");
    QString load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Status (*.txt)"));
    qDebug()<<load;
    qDebug()<<QFileInfo(load).absoluteFilePath().toStdString().c_str();
    if (!load.isEmpty()) {
        outputStatus(QFileInfo(load));
    }
}

void SimpleView::loadStatus(QFileInfo filedir){
    std::string line;
    std::ifstream input;
    
    qDebug()<<filedir.absoluteFilePath().toStdString().c_str();
    
    int checkstate;
    int index;
    std::string min,max;
    std::string x,y,z;
    std::string value,r,g,b,a;
    int count;
    
    input.open(filedir.absoluteFilePath().toStdString().c_str());
    input >> checkstate ;
    this->ui->outline_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> checkstate ;
    this->ui->scalarBar_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> checkstate;
    this->ui->axis_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> checkstate;
    this->ui->extract_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> min >> max;
    this->ui->xmin_LE->setText(QString::fromStdString(min));
    this->ui->xmax_LE->setText(QString::fromStdString(max));
    input >> min >> max;
    this->ui->ymin_LE->setText(QString::fromStdString(min));
    this->ui->ymax_LE->setText(QString::fromStdString(max));
    input >> min >> max;
    this->ui->zmin_LE->setText(QString::fromStdString(min));
    this->ui->zmax_LE->setText(QString::fromStdString(max));
    input >> x >> y >> z;
    this->ui->cameraPositionX_LE->setText(QString::fromStdString(x));
    this->ui->cameraPositionY_LE->setText(QString::fromStdString(y));
    this->ui->cameraPositionZ_LE->setText(QString::fromStdString(z));
    input >> x >> y >> z;
    this->ui->cameraFocalX_LE->setText(QString::fromStdString(x));
    this->ui->cameraFocalY_LE->setText(QString::fromStdString(y));
    this->ui->cameraFocalZ_LE->setText(QString::fromStdString(z));
    input >> x >> y >> z;
    this->ui->cameraViewUpX_LE->setText(QString::fromStdString(x));
    this->ui->cameraViewUpY_LE->setText(QString::fromStdString(y));
    this->ui->cameraViewUpZ_LE->setText(QString::fromStdString(z));
    input >> count;
    while (this->ui->RGBScalar_Table->rowCount()>count) {
        this->ui->RGBScalar_Table->removeRow(0);
    }
    while (this->ui->RGBScalar_Table->rowCount()<count) {
        this->ui->RGBScalar_Table->insertRow(0);
    }
    for (int i=0; i<count; i++) {
        input >> value >> r >> g >> b;
        this->ui->RGBScalar_Table->item(i, 0)->setText(QString::fromStdString(value));
        this->ui->RGBScalar_Table->item(i, 1)->setText(QString::fromStdString(r));
        this->ui->RGBScalar_Table->item(i, 2)->setText(QString::fromStdString(g));
        this->ui->RGBScalar_Table->item(i, 3)->setText(QString::fromStdString(b));
        
    }
    
    
    input >> count;
    while (this->ui->RGBVector_Table->rowCount()>count) {
        this->ui->RGBVector_Table->removeRow(0);
    }
    while (this->ui->RGBVector_Table->rowCount()<count) {
        this->ui->RGBVector_Table->insertRow(0);
    }
    for (int i=0; i<count; i++) {
        input >> value >> r >> g >> b;
        this->ui->RGBVector_Table->item(i, 0)->setText(QString::fromStdString(value));
        this->ui->RGBVector_Table->item(i, 1)->setText(QString::fromStdString(r));
        this->ui->RGBVector_Table->item(i, 2)->setText(QString::fromStdString(g));
        this->ui->RGBVector_Table->item(i, 3)->setText(QString::fromStdString(b));
        
    }
    
    
    input >> count;
    while (this->ui->RGBIso_Table->rowCount()>count) {
        this->ui->RGBIso_Table->removeRow(0);
    }
    while (this->ui->RGBIso_Table->rowCount()<count) {
        this->ui->RGBIso_Table->insertRow(0);
    }
    for (int i=0; i<count; i++) {
        input >> value >> r >> g >> b;
        this->ui->RGBIso_Table->item(i, 0)->setText(QString::fromStdString(value));
        this->ui->RGBIso_Table->item(i, 1)->setText(QString::fromStdString(r));
        this->ui->RGBIso_Table->item(i, 2)->setText(QString::fromStdString(g));
        this->ui->RGBIso_Table->item(i, 3)->setText(QString::fromStdString(b));
        
    }
    
    input >> count;
    while (this->ui->alphaScalar_Table->rowCount()>count) {
        this->ui->alphaScalar_Table->removeRow(0);
    }
    while (this->ui->alphaScalar_Table->rowCount()<count) {
        this->ui->alphaScalar_Table->insertRow(0);
    }
    for (int i=0; i<count; i++) {
        input >> value >> a;
        this->ui->alphaScalar_Table->item(i, 0)->setText(QString::fromStdString(value));
        this->ui->alphaScalar_Table->item(i, 1)->setText(QString::fromStdString(a));
    }
    
    input >> checkstate;
    this->ui->scalar_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    scalar=checkstate;
    input >> count;
    //    while (this->ui->scalarChoice->count()>0) {
    //        this->ui->scalarChoice->removeItem(0);
    //    }
    //    for (int i=0; i<count; i++) {
    //        this->ui->scalarChoice->insertItem(i, QString::number(i+1));
    //    }
    input >> index;
    this->ui->scalarChoice->setCurrentIndex(index);
    scalarColumn=index;
    input >> checkstate;
    this->ui->volume_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> checkstate;
    this->ui->scalarRange_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> min >> max;
    this->ui->scalarValueMin_LE->setText(QString::fromStdString(min));
    this->ui->scalarValueMax_LE->setText(QString::fromStdString(max));
    input >> checkstate;
    this->ui->slice_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> x >> y >> z;
    this->ui->sliceOriginX->setText(QString::fromStdString(x));
    this->ui->sliceOriginY->setText(QString::fromStdString(y));
    this->ui->sliceOriginZ->setText(QString::fromStdString(z));
    input >> x >> y >> z;
    this->ui->sliceNormalX->setText(QString::fromStdString(x));
    this->ui->sliceNormalY->setText(QString::fromStdString(y));
    this->ui->sliceNormalZ->setText(QString::fromStdString(z));
    
    input >> checkstate;
    this->ui->isosurface_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> count;
    while (this->ui->isosurface_LW->count()>0) {
        this->ui->isosurface_LW->takeItem(0);
    }
    for (int i=0; i<count; i++) {
        input >> value >> checkstate;
        this->ui->isoValue_LE->setText(QString::fromStdString(value));
        this->on_isoAdd_PB_released();
//        this->ui->isosurface_LW->insertItem(i, QString::fromStdString(value));
        this->ui->isosurface_LW->item(i)->setFlags(this->ui->isosurface_LW->item(i)->flags() | Qt::ItemIsUserCheckable);
        this->ui->isosurface_LW->item(i)->setCheckState(static_cast<Qt::CheckState>(checkstate));
    }
    
    
    input >> checkstate;
    this->ui->vector_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    vector=checkstate;
    input >> count;
    input >> index;
    this->ui->vectorChoice->setCurrentIndex(index);
    vectorColumn=index;
    input >> checkstate;
    this->ui->vectorGlyph_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> value;
    this->ui->vectorScale_LE->setText(QString::fromStdString(value));
    input >> checkstate;
    this->ui->vectorRange_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> min >> max;
    this->ui->vectorValueMin_LE->setText(QString::fromStdString(min));
    this->ui->vectorValueMax_LE->setText(QString::fromStdString(max));
    input >> checkstate;
    this->ui->streamline_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    input >> value;
    this->ui->seedNumber_LE->setText(QString::fromStdString(value));
    input >> value;
    this->ui->seedRadius_LE->setText(QString::fromStdString(value));
    input >> x >> y >> z;
    this->ui->seedCenterX_LE->setText(QString::fromStdString(x));
    this->ui->seedCenterY_LE->setText(QString::fromStdString(y));
    this->ui->seedCenterZ_LE->setText(QString::fromStdString(z));
    input >> value;
    this->ui->streamStepLength_LE->setText(QString::fromStdString(value));
//    input >> value;
//    this->ui->streamIntStepLength_LE->setText(QString::fromStdString(value));
    
    input >> checkstate;
    this->ui->domain_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
    domain=checkstate;
    for (int i=0; i<27; i++) {
        input >> checkstate;
        this->ui->domain_LW->item(i)->setCheckState(static_cast<Qt::CheckState>(checkstate));
    }
    
    input.close();

}

void SimpleView::slotLoadStatus(){
    QFileDialog filedialog;
    
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Status input (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    if (!load.isEmpty()) {
        loadStatus(QFileInfo(load));
    }
}

void SimpleView::slotBatch3D(){
    qDebug()<<"Batch producing 3D plot";
    batch3D *dialog=new batch3D(this);
    dialog->show();
}