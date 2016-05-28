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
#include <string>

#define VTK_CREATE(type, name) \
vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

// Constructor
SimpleView::SimpleView()
{
    QString styleSheet = QString("font: 15px Arial;").arg(QApplication::font().pointSize());
    this->setStyleSheet(styleSheet);
    this->ui = new Ui_SimpleView;
    this->ui->setupUi(this);
    this->TableView = vtkSmartPointer<vtkQtTableView>::New();
    this->ui->RGB_Combo->setView(new QListView());
    this->ui->alpha_Combo->setView(new QListView());
    this->ui->scalarChoice->setView(new QListView());
    for(int nr = 0; nr < 27; nr++){
        actorDomain.push_back(vtkActor::New());
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

    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
        qDebug()<<"creating new renderer";
    }else{
        renderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    }
    
};

SimpleView::~SimpleView()
{
    // The smart pointers should clean up for up
    
}


void SimpleView::slotSwitch1D(){
    this->ui->stackedWidget->setCurrentIndex(1);
}

void SimpleView::slotSwitch3D(){
    this->ui->stackedWidget->setCurrentIndex(0);
}

void SimpleView::setup1DFigure(QCustomPlot *customPlot){
    
}

void SimpleView::slotUpdate(){
    qDebug()<<"Slot update"<<scalarName.c_str()<<vectorName.c_str();
    updateVTK(scalarName,vectorName);
}
void SimpleView::slotClear(){
    this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->InitTraversal();
    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){

    }else{
//        qDebug()<<"renderers"<<this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems();
//        for(int i=0;i<this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetNumberOfPropsRendered();i++){
//        this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->GetNextActor());
////        this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetVolumes()->GetLastProp());
//
//            qDebug()<<"clean new renderer"<<0<<" "<<this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetNumberOfPropsRendered();
//        }
//        VTK_CREATE(vtkRenderer, renderer);
//        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
//        this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveAllViewProps();
//        actorScalar=NULL;
//        vtkSmartPointer<vtkVolume> actorScalar = vtkSmartPointer<vtkVolume>::New();
//        this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->GetNextActor());
//        this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorScalar);
//        updateCamera(0);
        
//        this->ui->qvtkWidget->deleteLater();
//        actorScalar->Delete();
//        actorVector->Delete();
        
        
        
        qDebug()<<"close";
        SimpleView *mySimpleView=new SimpleView();
        mySimpleView->show();
        
//        this->ui = new Ui_SimpleView;
//        this->ui->setupUi(this);
//        this->ui->qvtkWidget->setAutomaticImageCacheEnabled(1);
//
//        VTK_CREATE(vtkRenderer,renderer);
//
//        
//        // Set up action signals and slots
//        
//        if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
//            this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
//            qDebug()<<"creating new renderer";
//        }else{
//            renderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
//        }
        this->ui->centralwidget->deleteLater();
        this->ui->qvtkWidget->deleteLater();
        this->actorVector->Delete();
        this->actorScalar->Delete();
        for(int nr = 0; nr < 27; nr++){
            this->actorDomain[nr]->Delete();
        }
        this->close();
        qDebug()<<"nothing showing";


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
    renderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
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
    VTK_CREATE(vtkActor,streamActor);
    VTK_CREATE(vtkThresholdPoints,thresholdVector);
    VTK_CREATE(vtkPlane, plane);
    VTK_CREATE(vtkCutter, cutter);
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
    renderer->AddActor(actorScalar);
    renderer->AddActor(actorVector);
    VTK_CREATE(vtkDoubleArray,range);
    
    
    double planeOX=0,planeOY=0,planeOZ=0;
    double planeNX=0,planeNY=0,planeNZ=0;
    planeOX=this->ui->sliceOriginX->text().toDouble();
    planeOY=this->ui->sliceOriginY->text().toDouble();
    planeOZ=this->ui->sliceOriginZ->text().toDouble();
    planeNX=this->ui->sliceNormalX->text().toDouble();
    planeNY=this->ui->sliceNormalY->text().toDouble();
    plane->SetOrigin(planeOX, planeOY, planeOZ);
    plane->SetNormal(planeNX, planeNY, planeNZ);
    cutter->SetCutFunction(plane);
    
    if (scalarFile){
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
        isosurface->SetInputConnection(readerScalar->GetOutputPort());
        isosurface->ComputeScalarsOn();
        isosurface->ComputeNormalsOn();
        isosurface->GenerateTrianglesOn();
        int contoursNumber=0;
        qDebug()<<"Fine up till here"<<this->ui->RGBIso_Table->rowCount();
        contoursNumber=this->ui->RGBIso_Table->rowCount();
        qDebug()<<"Fine after"<<contoursNumber;
        isosurface->SetNumberOfContours(contoursNumber);
        qDebug()<<"fine after iso";
        for (int i=0; i<contoursNumber; i++) {
            isosurface->SetValue(i, this->ui->RGBIso_Table->item(i,0)->text().toDouble());
            qDebug()<<"Number of isosurface"<<i<<" "<<this->ui->RGBIso_Table->item(i,0)->text().toDouble();
        }
        //        if(contoursNumber!=0){
        isoNormals->SetInputConnection(0, isosurface->GetOutputPort());
        isoMapper->SetInputConnection(isoNormals->GetOutputPort());
        isoMapper->ScalarVisibilityOff();
        actorIsosurface->SetMapper(isoMapper);
        actorIsosurface->GetProperty()->SetColor(0, 0, 0);
        renderer->AddActor(actorIsosurface);
        if (this->ui->isosurface_CB->checkState()) {
            actorIsosurface->SetVisibility(true);
            qDebug()<<"showing isosurface";
        }else{
            actorIsosurface->SetVisibility(false);
            qDebug()<<"not showing isosurface";
        }
        //        }
        
        VTK_CREATE(vtkSmartVolumeMapper,mapperScalar);
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
            mapperScalar1->SetInputConnection(0,tetra->GetOutputPort(0));
            mapperScalar1->Update();
            actorScalar->SetMapper(mapperScalar1);
            qDebug()<<actorScalar;
        }else{
            range->InsertNextValue(scalar_range[0]);
            range->InsertNextValue(scalar_range[1]);
            vmin=scalar_range[0];
            vmax=scalar_range[1];
            mapperScalar->SetInputConnection(0,readerScalar->GetOutputPort(0));
            // mapperScalar->SetLookupTable(tableScalar);
            actorScalar->SetMapper(mapperScalar);
        }
        
        if(this->ui->scalar_CB->checkState()==0 || this->ui->volume_CB->checkState()==0){
            actorScalar->SetVisibility(false);
        }else{
            actorScalar->SetVisibility(true);
        }
        
        
        VTK_CREATE(vtkPolyDataMapper, cutterMapper);
        cutter->SetInputConnection(0, readerScalar->GetOutputPort(0));
        cutterMapper->SetInputConnection(0, cutter->GetOutputPort(0));
        actorCutter->SetMapper(cutterMapper);
        renderer->AddActor(actorCutter);
        if (this->ui->slice_CB->checkState()) {
            actorCutter->SetVisibility(true);
        }else{
            actorCutter->SetVisibility(false);
        }
        
        valueRange[0]=scalar_range[0];
        valueRange[1]=scalar_range[1];
        outlineScalar->SetInputConnection(readerScalar->GetOutputPort());
    }else{
        outlineScalarActor->SetVisibility(false);
    }
    
    if (vectorFile){
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
        
        if(this->ui->vector_CB->checkState()!=0){
            actorVector->SetVisibility(true);
        }else{
            actorVector->SetVisibility(false);
        }
        valueRange[0]=vector_range[0];
        valueRange[1]=vector_range[1];
        outlineVector->SetInputConnection(readerVector->GetOutputPort());
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
                R=this->ui->RGBScalar_Table->item(i,1)->text().toDouble();
                G=this->ui->RGBScalar_Table->item(i,2)->text().toDouble();
                B=this->ui->RGBScalar_Table->item(i,3)->text().toDouble();
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
                R=this->ui->RGBVector_Table->item(i,1)->text().toDouble();
                G=this->ui->RGBVector_Table->item(i,2)->text().toDouble();
                B=this->ui->RGBVector_Table->item(i,3)->text().toDouble();
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
    outlineScalarMapper->SetInputConnection(outlineScalar->GetOutputPort());
    outlineScalarActor->SetMapper(outlineScalarMapper);
    outlineScalarActor->GetProperty()->SetColor(0,0,0);
    renderer->AddActor(outlineScalarActor);
    
    outlineVectorMapper->SetInputConnection(outlineVector->GetOutputPort());
    outlineVectorActor->SetMapper(outlineVectorMapper);
    outlineVectorActor->GetProperty()->SetColor(0,0,0);
    renderer->AddActor(outlineVectorActor);
    
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
        outlineVectorActor->SetVisibility(true);
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

void SimpleView::on_scalarBar_CB_stateChanged(int state){
    if(state!=0){
        scalarScaleBarActor->SetVisibility(true);
    }else{
        scalarScaleBarActor->SetVisibility(false);
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
                this->ui->scalarChoice->removeItem(i);
            }
        }else{
            
        }
        for (int i = 0; i < columns; ++i)
        {
            outputScalar(i,xmax,ymax,zmax);
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
        
        this->ui->scalar_Table->clearContents();
        for (int i=0; i<this->ui->scalar_Table->rowCount(); i++) {
            this->ui->scalar_Table->removeRow(i);
        }
        for(int i=0;i<columns;++i){
            for (int j=0;j<rows;++j){
                dataHold[j]=vtkData[j][i];
            }
            this->ui->scalar_Table->insertRow(this->ui->scalar_Table->rowCount());
            printstatus = QString::fromStdString(std::to_string(getMin(dataHold,rows)));
            this->ui->scalar_Table->setItem(this->ui->scalar_Table->rowCount()-1,0,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getMax(dataHold,rows)));
            this->ui->scalar_Table->setItem(this->ui->scalar_Table->rowCount()-1,1,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getAvg(dataHold,rows)));
            this->ui->scalar_Table->setItem(this->ui->scalar_Table->rowCount()-1,2,new QTableWidgetItem(printstatus));
        }
        
        this->ui->information_Tab->setCurrentIndex(0);
        scalarName=(std::to_string(this->ui->scalarChoice->currentIndex()+1)+".vtk").c_str();
        updateVTK(scalarName,vectorName);
        delete this->vtkData;
    }
}

void SimpleView::on_scalarChoice_currentIndexChanged(int index){
//    if (index!=this->ui->scalarChoice->currentIndex()){
        scalarName=(std::to_string(index+1)+".vtk").c_str();
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
        this->ui->domain_CB->setCheckState(Qt::Unchecked);
        QFileInfo filehold(load);
        qDebug()<<columns<<columns/3;
        qDebug()<<xmax<<ymax<<zmax;
        int current=this->ui->vectorChoice->count();
        if(current!=0){
            for(i=0;i<current+1;++i){
                this->ui->vectorChoice->removeItem(i);
            }
        }else{
            
        }
        for (i = 0; i < columns/3; ++i)
        {
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<QString::fromStdString(std::to_string(3*i+1)+std::to_string(3*i+2)+std::to_string(3*i+3));
            outputVector(3*i,3*i+1,3*i+2,xmax,ymax,zmax);
            this->ui->vectorChoice->addItem(QString::fromStdString(std::to_string(3*i+1)+std::to_string(3*i+2)+std::to_string(3*i+3)));
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<xmax<<ymax<<zmax;
            qDebug()<<"not sure why nothing shows up";
            qDebug()<<"not sure why nothing shows up";
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
            this->ui->vector_Table->removeRow(i);
        }
        for(i=0;i<columns;++i){
            for (int j=0;j<rows;++j){
                dataHold[j]=vtkData[j][i];
            }
            this->ui->vector_Table->insertRow(this->ui->vector_Table->rowCount());
            printstatus = QString::fromStdString(std::to_string(getMin(dataHold,rows)));
            this->ui->vector_Table->setItem(this->ui->vector_Table->rowCount()-1,0,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getMax(dataHold,rows)));
            this->ui->vector_Table->setItem(this->ui->vector_Table->rowCount()-1,1,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getAvg(dataHold,rows)));
            this->ui->vector_Table->setItem(this->ui->vector_Table->rowCount()-1,2,new QTableWidgetItem(printstatus));
        }
        this->ui->vectorValueMin_LE->setText("0");
        this->ui->vectorValueMax_LE->setText("10000");
        this->ui->information_Tab->setCurrentIndex(1);
        int index=this->ui->vectorChoice->currentIndex();
        vectorName=(std::to_string(3*index+1)+std::to_string(3*index+2)+std::to_string(3*index+3)+".vtk").c_str();
        
        updateVTK(scalarName,vectorName);
        delete this->vtkData;
        
    }
}

void SimpleView::on_vectorChoice_activated(int index){
    if(index!=this->ui->vectorChoice->currentIndex()){
        vectorName=(std::to_string(3*index+1)+std::to_string(3*index+2)+std::to_string(3*index+3)+".vtk").c_str();
        updateVTK(scalarName,vectorName);
    }
}

void SimpleView::outputScalar(int columnNumber,int x, int y, int z){
    long rowNumber;
    x=x+1;
    y=y+1;
    z=z+1;
    rowNumber=x*y*z;
    std::ofstream output;
    std::string str;
    str=std::to_string(columnNumber+1)+".vtk";
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
                output << setw(14) << vtkData[w*y*z+n*z+m][columnNumber] << "\n";
            }
        }
    }
    output.close();
    scalarName=str;
}

void SimpleView::outputVector(int colX,int colY,int colZ, int x, int y, int z){
    long rowNumber;
    x=x+1;
    y=y+1;
    z=z+1;
    rowNumber=x*y*z;
    std::ofstream output;
    std::string str;
    str=std::to_string(colX+1)+std::to_string(colY+1)+std::to_string(colZ+1)+".vtk";
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
    int i=0,x=0,y=0,z=0,columnNumber=0;
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
    input.close();
    
    
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
    rowNumber=x*y*z;
    
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
        iss >> x>>y>>z;
        for (int k=0;k<columnNumber;++k){
            iss >> std::scientific;
            iss >>  vtkData[j][k];
        }
    }
    input.close();

    updateExtraction(x,y , z);


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
    if (this->ui->RGBValue_LE->text().isEmpty() |
        this->ui->RGBR_LE->text().isEmpty() |
        this->ui->RGBG_LE->text().isEmpty() |
        this->ui->RGBB_LE->text().isEmpty()){
    }else{
        if (this->ui->RGB_Stack->currentIndex()==0){
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
        }else if (this->ui->RGB_Stack->currentIndex()==1){
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
        }else if (this->ui->RGB_Stack->currentIndex()==2){
            row=this->ui->RGBIso_Table->rowCount();
            qDebug()<<row;
            this->ui->RGBIso_Table->insertRow(row);
            //      row=row;
            item=this->ui->RGBValue_LE->text();
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

void SimpleView::on_RGBDelete_PB_released(){
    if (this->ui->RGB_Stack->currentIndex()==0){
        this->ui->RGBScalar_Table->removeRow(this->ui->RGBScalar_Table->currentRow());
    }else if (this->ui->RGB_Stack->currentIndex()==1){
        this->ui->RGBVector_Table->removeRow(this->ui->RGBVector_Table->currentRow());
    }
}

void SimpleView::on_RGB_Combo_currentIndexChanged(int index){
    if (index==0){
        this->ui->RGBValue_LE->setEnabled(false);
        this->ui->RGBR_LE->setEnabled(false);
        this->ui->RGBG_LE->setEnabled(false);
        this->ui->RGBB_LE->setEnabled(false);
        // this->ui->RGBA_LE->setEnabled(false);
        this->ui->RGBScalar_Table->setEnabled(false);
        this->ui->RGBVector_Table->setEnabled(false);
        this->ui->RGBIso_Table->setEnabled(false);
        this->ui->RGB_Stack->setEnabled(false);
    }else{
        this->ui->RGBValue_LE->setEnabled(true);
        this->ui->RGBR_LE->setEnabled(true);
        this->ui->RGBG_LE->setEnabled(true);
        this->ui->RGBB_LE->setEnabled(true);
        // this->ui->RGBA_LE->setEnabled(true);
        this->ui->RGBScalar_Table->setEnabled(true);
        this->ui->RGBVector_Table->setEnabled(true);
        this->ui->RGBIso_Table->setEnabled(true);
        this->ui->RGB_Stack->setEnabled(true);
        if(index==1){
            this->ui->RGB_Stack->setCurrentIndex(0);
        }else if(index==2){
            this->ui->RGB_Stack->setCurrentIndex(1);
        }else if (index==3){
            this->ui->RGB_Stack->setCurrentIndex(2);
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
    int mR=0,mO=0,mT=0,mN=0,mfilm=0; //mN is for null, mfilm is for total film
    double fR,fT,fO,fN;
    int i=0,j=0,k=0;
    int nfs=0,nsub=0;
    long hold;
    double px,py,pz;
    
    int columnNumber=loadData(filedir);
    qDebug()<<filedir;
    long rowNumber=(xmax+3)*(ymax+3)*(zmax+3); //+3
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
    
    rowNumber=(xmax+3)*(ymax+3)*(zmax+3); //+3
    std::ofstream output;
    std::string str;
    str="domain.vtk";
    const char *outdir=str.c_str();
    output.open(outdir);
    output << "# vtk DataFile Version 3.0\n";
    output << "Structured Points\n";
    output << "ASCII\n";
    output << "\n";
    output << "DATASET STRUCTURED_POINTS\n";
    output << "DIMENSIONS " << std::to_string(xmax+3) << " " << std::to_string(ymax+3) <<" "<< std::to_string(zmax+3) << "\n"; //+3
    output << "ORIGIN 0 0 0\n";
    output << "SPACING 1 1 1\n";
    output << "\n";
    output << "POINT_DATA " << std::to_string(rowNumber)+"\n";
    output << "SCALARS domain int\n";
    output << "LOOKUP_TABLE default\n";
    for (i=0;i<rowNumber;++i){
        output << outputData[i] << "\n";
    }
    output.close();
    
    return columnNumber;
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
        columns=domainProcessing(load);
        qDebug()<<"after domain processing";
        int rows=(xmax+1)*(ymax+1)*(zmax+1);
        double *dataHold= new double[rows];
        QFileInfo filehold(load);
        this->ui->scalar_CB->setCheckState(Qt::Unchecked);
        this->ui->volume_CB->setCheckState(Qt::Unchecked);
        this->ui->vector_CB->setCheckState(Qt::Unchecked);
        this->ui->domain_CB->setCheckState(Qt::Checked);
        
        
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
        this->ui->information_Tab->setCurrentIndex(2);
        qDebug()<<"before vtk part";
        drawDomain("domain.vtk");
        delete this->vtkData;
    }
}


void SimpleView::drawDomain(std::string domainName){
    const char* fileNameDomain=domainName.c_str();
    //  int extent[6];
    double domain_range[2];
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
    readerDomainOrigin->GetOutput()->GetPointData()->GetScalars()->GetRange(domain_range);
    qDebug()<<domain_range;
    readerDomain->SetInputConnection(readerDomainOrigin->GetOutputPort());
    readerDomain->SetVOI(0,xmax+2,0,ymax+2,0,zmax+2);
    readerDomain->Update();
    
    double R[3];
    
    if (this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetNumberOfItems()==0){
        this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(domainRenderer);
    }else{
        domainRenderer=this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    }
    
    for(int i=0;i<27;i++){
        VTK_CREATE(vtkThreshold,domainThreshold);
        VTK_CREATE(vtkDataSetSurfaceFilter,domainSurface);
        VTK_CREATE(vtkSmoothPolyDataFilter,domainSmooth);
        VTK_CREATE(vtkPolyDataNormals,normalGenerator);
        VTK_CREATE(vtkDataSetMapper,domainMapper);
        qDebug()<<"create the domain"<<i;
        readerDomain->Update();
        domainThreshold->SetInputConnection(readerDomain->GetOutputPort());
        domainThreshold->AllScalarsOff();
        domainThreshold->ThresholdBetween(i-0.5,i+0.5);
        domainThreshold->Update();
        qDebug()<<"before surface"<<i;
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
        qDebug()<<domainRGB[i][0]<<" "<<domainRGB[i][1]<<" "<<domainRGB[i][2];
        actorDomain[i]->GetProperty()->SetColor(domainRGB[i][0],domainRGB[i][1],domainRGB[i][2]);
        actorDomain[i]->GetProperty()->GetColor(R);
        qDebug()<<"out "<<R[0]<<" "<<R[1]<<" "<<R[2];
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
}


void SimpleView::saveImage(){
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptSave);
    filedialog.setDefaultSuffix("png");
    QString load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Images (*.png)"));
    
    
    
    VTK_CREATE(vtkWindowToImageFilter, windowToImage);
    windowToImage->SetInput(this->ui->qvtkWidget->GetRenderWindow());
    windowToImage->SetMagnification(3);
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
    this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->ResetCamera();
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
        case 0:
            break;
        case 1:
            camera->SetPosition(-3*xmax-ymax/2-zmax/2, ymax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 2:
            camera->SetPosition(3*xmax+ymax/2+zmax/2, ymax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 3:
            camera->SetPosition(xmax/2, -3*ymax-xmax/2-zmax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 4:
            camera->SetPosition(xmax/2, 3*ymax+xmax/2+zmax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
        case 5:
            camera->SetPosition(xmax/2, ymax/2, -3*zmax-ymax/2-xmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 1, 0);
            break;
        case 6:
            camera->SetPosition(xmax/2, ymax/2, 3*zmax+ymax/2+xmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 1, 0);
            break;
        default:
            camera->SetPosition(xmax/2, 3*ymax+xmax/2+zmax/2, zmax/2);
            camera->SetFocalPoint(xmax/2, ymax/2, zmax/2);
            camera->SetViewUp(0, 0, 1);
            break;
    }
    qDebug()<<"updateCamera"<<choice;
    this->ui->qvtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->SetActiveCamera(camera);
    this->ui->qvtkWidget->GetRenderWindow()->Render();
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