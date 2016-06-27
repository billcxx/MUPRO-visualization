//
//  batch3D.cpp
//  SimpleView
//
//  Created by xx cheng on 6/24/16.
//
//

#include "ui_batch3D.h"

#include "batch3D.h"


batch3D::batch3D(SimpleView *simpleView, QDialog *parent) :
QDialog(parent),
batchui(new Ui::Batch3D)
{
    batchui->setupUi(this);
    main3D=simpleView;
}

batch3D::~batch3D(){
    delete batchui;
}

void batch3D::on_loadStatusFile_PB_released(){
    this->main3D->slotLoadStatus();
    if (this->main3D->scalar) {
        this->batchui->loadScalar_PB->setEnabled(true);
    }else{
        this->batchui->loadScalar_PB->setEnabled(false);
    }
    if (this->main3D->vector) {
        this->batchui->loadVector_PB->setEnabled(true);
    }else{
        this->batchui->loadVector_PB->setEnabled(false);
    }
    if (this->main3D->domain) {
        this->batchui->loadDomain_PB->setEnabled(true);
    }else{
        this->batchui->loadDomain_PB->setEnabled(false);
    }
}

QString batch3D::formName(QString fileName,int timeStep){
    return fileName+"."+QString("%1").arg(timeStep,8,10,QChar('0'));
}

QString batch3D::formDataName(QString fileName,int timeStep){
    return fileName+"."+QString("%1").arg(timeStep,8,10,QChar('0'))+".dat";
}

void batch3D::on_loadScalar_PB_released(){
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Scalar data (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    this->batchui->scalarName_LB->setText(QFileInfo(load).baseName());
    if(!load.isEmpty()){
        scalarDir=QFileInfo(load).absolutePath();
        scalarFlag=true;
    }else{
        scalarFlag=false;
    }
}

void batch3D::on_loadVector_PB_released(){
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Vector data (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    this->batchui->vectorName_LB->setText(QFileInfo(load).baseName());
    if(!load.isEmpty()){
        vectorDir=QFileInfo(load).absolutePath();
        vectorFlag=true;
    }else{
        vectorFlag=false;
    }
}

void batch3D::on_loadDomain_PB_released(){
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Domain data (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    this->batchui->domainName_LB->setText(QFileInfo(load).baseName());
    if(!load.isEmpty()){
        domainDir=QFileInfo(load).absolutePath();
        domainFlag=true;
    }else{
        domainFlag=false;
    }
}

void batch3D::on_exportDir_PB_released(){
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::Directory);
    filedialog.setNameFilter(tr("Export directory (*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getExistingDirectory();
    //    this->batchui->exportDir_LB->setText(QFileInfo(load).baseName());
    if(!load.isEmpty()){
        exportDir=QFileInfo(load).absoluteFilePath();
        outputFlag=true;
    }else{
        outputFlag=false;
    }
    qDebug()<<"export"<<exportDir;
    //    this is for temperary hold
}

void batch3D::accept(){
    if (loopThroughKt()) {
        this->close();
    }else{
        QMessageBox::information(this, tr("Alert"), tr("All field must be filled before running batch processing."));
    }
}

bool batch3D::loopThroughKt(){
    int start=this->batchui->timeBegin_LE->text().toInt();
    int interval=this->batchui->timeInterval_LE->text().toInt();
    int end=this->batchui->timeEnd_LE->text().toInt();
    int hold;
    QString scalarName,vectorName,domainName,fileName;
    QString scalarData,vectorData,domainData;
    if (!this->batchui->timeBegin_LE->text().isEmpty()) {
        startFlag=true;
    }else{
        startFlag=false;
    }
    if (!this->batchui->timeInterval_LE->text().isEmpty()) {
        intervalFlag=true;
    }else{
        intervalFlag=false;
    }
    if (!this->batchui->timeBegin_LE->text().isEmpty()) {
        endFlag=true;
    }else{
        endFlag=false;
    }
    
    if ((scalarFlag||vectorFlag||domainFlag)&&startFlag&&intervalFlag&&endFlag&&outputFlag) {
        hold=(this->main3D->vectorColumn)*3;
        if(this->batchui->loadScalar_PB->isEnabled()){
            if(!QDir(exportDir+"/scalar/").exists()){
                QDir().mkdir(exportDir+"/scalar/");
                qDebug()<<"scalar created";
            }
        }
        if(this->batchui->loadVector_PB->isEnabled()){
            if(!QDir(exportDir+"/vector/").exists()){
                QDir().mkdir(exportDir+"/vector/");
                qDebug()<<"vector created";
            }
        }
        
        if(this->batchui->loadDomain_PB->isEnabled()){
            if(!QDir(exportDir+"/domain/").exists()){
                QDir().mkdir(exportDir+"/domain/");
                qDebug()<<"domain created";
            }
        }
        
        if(!QDir(exportDir+"/images/").exists()){
            QDir().mkdir(exportDir+"/images/");
            qDebug()<<"images created";
        }
        
        for(int i=start;i<=end;i=i+interval){
            if(this->batchui->loadScalar_PB->isEnabled()){
                fileName=scalarDir+"/"+this->batchui->scalarName_LB->text();
                scalarData=formDataName(fileName, i);
                qDebug()<<"scalarData:"<<scalarData<<" "<<fileName;
                this->main3D->loadData(scalarData);
                scalarName=exportDir+"/scalar/"+this->batchui->scalarName_LB->text();
                fileName=formName(scalarName,i);
                this->main3D->outputScalar(QFileInfo(fileName).absoluteFilePath(), this->main3D->scalarColumn, this->main3D->tempX-1, this->main3D->tempY-1, this->main3D->tempZ-1);
                qDebug()<<fileName;
                scalarName=fileName+"."+QString::number(this->main3D->scalarColumn+1)+".vtk";
                qDebug()<<scalarName;
            }
            if(this->batchui->loadVector_PB->isEnabled()){
                fileName=vectorDir+"/"+this->batchui->vectorName_LB->text();
                vectorData=formDataName(fileName, i);
                this->main3D->loadData(vectorData);
                vectorName=exportDir+"/vector/"+this->batchui->vectorName_LB->text();
                fileName=formName(vectorName,i);
                this->main3D->outputVector(fileName, hold, hold+1, hold+2, this->main3D->tempX-1, this->main3D->tempY-1, this->main3D->tempZ-1);
                qDebug()<<fileName;
                hold=hold+1;
                vectorName=fileName+"."+QString::number(hold)+QString::number(hold+1)+QString::number(hold+2)+".vtk";
                qDebug()<<vectorName;
            }
            this->main3D->updateVTK(scalarName.toStdString(), vectorName.toStdString());
            if(this->batchui->loadDomain_PB->isEnabled()){
                fileName=domainDir+"/"+this->batchui->domainName_LB->text();
                domainData=formDataName(fileName, i);
                this->main3D->loadData(domainData);
                domainName=exportDir+"/domain/"+this->batchui->domainName_LB->text();
                fileName=formName(domainName,i);
                this->main3D->outputDomain(fileName,this->main3D->tempX-1, this->main3D->tempY-1, this->main3D->tempZ-1);
                domainName=fileName+".domain.vtk";
                this->main3D->drawDomain(domainName.toStdString());
                qDebug()<<"filewtf:"<<fileName;
                qDebug()<<"domainwtf:"<<domainName;
            }
            fileName=formName(exportDir+"/images/"+this->batchui->outputName_LE->text(), i)+".png";
            this->main3D->outputImage(QFileInfo(fileName).absoluteFilePath());
        }
        return true;
    }else{
        return false;
    }
    
}