//
//  batch3D.hpp
//  SimpleView
//
//  Created by xx cheng on 6/24/16.
//
//

#ifndef BATCH3D_H
#define BATCH3D_H

#include <QDialog>
#include <SimpleView.h>
#include <QMessageBox>

namespace Ui{
    class Batch3D;
}

class batch3D : public QDialog
{
    Q_OBJECT
    
public:
    explicit batch3D(SimpleView *simpleView, QDialog *parent = 0);
    ~batch3D();
    private slots:
    void on_loadStatusFile_PB_released();
    void on_loadScalar_PB_released();
    void on_loadVector_PB_released();
    void on_loadDomain_PB_released();
    void on_exportDir_PB_released();
    bool loopThroughKt();
private:
    Ui::Batch3D *batchui;
    SimpleView *main3D;
    QString formName(QString fileName,int timeStep);
    QString formDataName(QString fileName,int timeStep);
    void accept();
    QString exportDir,scalarDir,vectorDir,domainDir;
    bool scalarFlag=false,vectorFlag=false,domainFlag=false,startFlag=false,intervalFlag=false,endFlag=false,outputFlag=false;
};



#endif /* BATCH3D_H */
