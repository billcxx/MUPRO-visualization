//
//  simulationDataFilter.hpp
//  SimpleView
//
//  Created by xx cheng on 5/27/16.
//
//

#ifndef simulationDataFilter_hpp
#define simulationDataFilter_hpp

#include <stdio.h>
#include <QString>
#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QListWidget>
#include <QListView>
#include <iostream>
#include <fstream>

class simulationDataFilter {
    double **vtkData;
    int columns;
    
    
public:
    int xmax,ymax,zmax;
    int xmin,ymin,zmin;
    simulationDataFilter();
    ~simulationDataFilter();
    int loadData(QString filedir);
    std::string outputScalar(int columnNumber,int x,int y, int z);
    std::string outputVector(int colX,int colY,int colZ,int x,int y,int z);
    int domainProcessing(QString filedir);
    int domainType(double px,double py, double pz);
    
};

#endif /* simulationDataFilter_hpp */


