//
//  simulationDataFilter.cpp
//  SimpleView
//
//  Created by xx cheng on 5/27/16.
//
//

#include "simulationDataFilter.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>



int simulationDataFilter::loadData(QString filedir){
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
    
    
    return columnNumber;
}


std::string simulationDataFilter::outputScalar(int columnNumber,int x, int y, int z){
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
                output << std::setw(14) << vtkData[w*y*z+n*z+m][columnNumber] << "\n";
            }
        }
    }
    output.close();
    return str;
}

std::string simulationDataFilter::outputVector(int colX,int colY,int colZ, int x, int y, int z){
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
                output << std::setw(14) << sqrt(pow(vtkData[w*y*z+n*z+m][colX],2)+pow(vtkData[w*y*z+n*z+m][colY],2)+pow(vtkData[w*y*z+n*z+m][colZ],2)) << "\n";
            }
        }
    }
    
    output << "\n";
    output << "VECTORS vector float\n";
    output << std::scientific;
    for (int m=0;m<z;++m){
        for (int n=0;n<y;++n){
            for (int w=0;w<x;++w){
                output << std::setw(14) << vtkData[w*y*z+n*z+m][colX] << " " << std::setw(14) << vtkData[w*y*z+n*z+m][colY] << " " << std::setw(14) << vtkData[w*y*z+n*z+m][colZ] << "\n";
            }
        }
    }
    output.close();
    return str;
}


int simulationDataFilter::domainProcessing(QString filedir){
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

int simulationDataFilter::domainType(double px,double py, double pz){
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

