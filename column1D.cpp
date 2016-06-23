#include "column1D.h"
#include "ui_column1D.h"
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <fstream>
#include <sstream>

column1D::column1D(QWidget *parent) :
QWidget(parent),
ui(new Ui::column1D)
{
    ui->setupUi(this);
//    connect(this->ui->load1DFile_PB, SIGNAL(clicked()), this, SLOT(on_load1DFile_PB_clicked()));
    scatterStyleList<<QCPScatterStyle::ssNone<<QCPScatterStyle::ssDot <<QCPScatterStyle::ssCross<<QCPScatterStyle::ssPlus<<QCPScatterStyle::ssCircle<<QCPScatterStyle::ssDisc<<QCPScatterStyle::ssSquare<<QCPScatterStyle::ssDiamond<<QCPScatterStyle::ssStar<<QCPScatterStyle::ssTriangle<<QCPScatterStyle::ssTriangleInverted<<QCPScatterStyle::ssCrossSquare<<QCPScatterStyle::ssPlusSquare<<QCPScatterStyle::ssCrossCircle<<QCPScatterStyle::ssPlusCircle;
    lineStyleList<<Qt::PenStyle::SolidLine<<Qt::PenStyle::DashLine<<Qt::PenStyle::DotLine<<Qt::PenStyle::DashDotLine<<Qt::PenStyle::DashDotDotLine;
    this->ui->plot1DFileX_Combo->setView(new QListView);

}

column1D::~column1D()
{
    delete ui;
}

int column1D::getColumns(){
    return columns;
}

QVector<double> column1D::returnX(){
    int dataRows=dataFiltered.count();
    int colX=this->ui->plot1DFileX_Combo->currentIndex();
    QVector<double> x(dataRows);
    qDebug()<<xmin1D<<xmax1D<<dataRows<<"xminmax"<<colX;

    if (dataRows>0) {
        xmin1D=dataFiltered[0][colX];
        xmax1D=dataFiltered[0][colX];
    }
    qDebug()<<xmin1D<<xmax1D<<dataRows<<"xminmax";

    for (int i=0; i<dataRows; i++) {
        x[i]=dataFiltered[i][colX];
        if(x[i]<=xmin1D) xmin1D=x[i];
        if(x[i]>=xmax1D) xmax1D=x[i];
    }
    qDebug()<<xmin1D<<xmax1D<<dataRows<<"xminmax";
    return x;
}

double column1D::returnXMin(){
    return xmin1D;
}

double column1D::returnXMax(){
    return xmax1D;
}

QVector<double> column1D::returnY(int colY){
    int dataRows=dataFiltered.count();
    QVector<double> y(dataRows);
    qDebug()<<ymin1D<<ymax1D<<dataRows<<"yminmax"<<colY;
    if (dataRows>0) {
        ymin1D=dataFiltered[0][colY];
        ymax1D=dataFiltered[0][colY];
    }
    qDebug()<<ymin1D<<ymax1D<<dataRows<<"yminmax";

    for (int i=0; i<dataRows; i++) {
        y[i]=dataFiltered[i][colY];
        if(y[i]<=ymin1D) ymin1D=y[i];
        if(y[i]>=ymax1D) {ymax1D=y[i];qDebug()<<y[i];}
    }

    qDebug()<<ymin1D<<ymax1D<<dataRows<<"yminmax";

//    qDebug()<<xmin1D<<xmax1D<<dataRows<<"yminmax";

    return y;
}

double column1D::returnYMin(){
    return ymin1D;
}

double column1D::returnYMax(){
    return ymax1D;
}


int column1D::filter(){
    if(dataFiltered.count()!=0){
        dataFiltered.clear();
    }
    std::ofstream output1;
    std::ofstream output2;

    std::ofstream output3;

    std::string str;
    
    str="filter_before.txt";
    const char *outdir1=str.c_str();
    
    output1.open(outdir1);
    output1 << "size" << "\n";
    output1 << sizeof(vtkData)<<"\n";
    for(int i=0;i<rows;i++){
        output1 << "i:" << i << ", vtkData:"<<vtkData[i][0] << "\n";
    }
    output1.close();
    
    str="filter.txt";
    const char *outdir=str.c_str();
    
    output2.open(outdir);
    for(int i=0;i<rows;i++){
        output2 << "i:" << i << ", vtkData:"<<vtkData[i][1] << "\n";
        if(filter1DData(vtkData[i])){
            dataFiltered.append(vtkData[i]);
        }
    }
    output2.close();
    qDebug()<<"rows:"<<rows;
    return dataFiltered.count();
}

int column1D::getFilteredCount(){
    if (loaded) {
        filter();
        return dataFiltered.count();
    }
    return 0;
}



void column1D::on_load1DFile_PB_clicked(){
    QFileDialog filedialog;
    
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.*)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    if (!load.isEmpty()) {
        columns=loadData1D(load);
        loaded = true;
        double *dataHold= new double[rows];
        QFileInfo filehold(load);
        // outputScalar(0,xmax,ymax,zmax);
        for (int i=0; i<columns; i++) {
            this->ui->plot1DFileX_Combo->addItem(QString::fromStdString(std::to_string(i+1)));
        }
        int current=this->ui->plot1DFileY_LW->count();
        if(current!=0){
            for(int i=0;i<current+1;++i){
                this->ui->plot1DFileY_LW->takeItem(i);
            }
        }else{
            
        }
        for (int i = 0; i < columns; ++i)
        {
            this->ui->plot1DFileY_LW->addItem(QString::fromStdString(std::to_string(i+1)));
            this->ui->plot1DFileY_LW->item(i)->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable );
            this->ui->plot1DFileY_LW->item(i)->setCheckState(Qt::Unchecked);
        }
        
        this->ui->plot1DFileY_LW->sortItems();
        
        
        current=this->ui->plot1DColFile_Combo->count();
        this->ui->plot1DRelationFile_Combo->setEnabled(true);
        this->ui->plot1DRelationValueFile_LE->setEnabled(true);
        if(current!=0){
            for(int i=0;i<current+1;++i){
                this->ui->plot1DColFile_Combo->removeItem(i);
            }
        }else{
        }
        for (int i = 0; i < columns; ++i)
        {
            this->ui->plot1DColFile_Combo->addItem(QString::fromStdString(std::to_string(i+1)));
        }
        
        
        this->ui->plot1DFileName_LE->setText(filehold.fileName());
        
        printstatus = QString::fromStdString(std::to_string(columns));
        this->ui->plot1DFileColNum_LE->setText(printstatus);
        
//        printstatus = QString::fromStdString("0 - "+std::to_string(xmax));
//        this->ui->plot1Dxminxmax_LE->setText(printstatus);
//        
//        printstatus = QString::fromStdString("0 - "+std::to_string(ymax));
//        this->ui->plot1Dyminymax_LE->setText(printstatus);
//        
//        printstatus = QString::fromStdString("0 - "+std::to_string(zmax));
//        this->ui->plot1Dzminzmax_LE->setText(printstatus);
//        
        this->ui->plot1DFile_Table->clearContents();
        for (int i=0; i<this->ui->plot1DFile_Table->rowCount(); i++) {
            this->ui->plot1DFile_Table->removeRow(i);
        }
        for(int i=0;i<columns;++i){
            for (int j=0;j<rows;++j){
                dataHold[j]=vtkData[j][i];
            }
            this->ui->plot1DFile_Table->insertRow(this->ui->plot1DFile_Table->rowCount());
            printstatus = QString::fromStdString(std::to_string(getMin(dataHold,rows)));
            qDebug()<<"column:"<<i<<rows<<this->ui->plot1DFile_Table->rowCount();
            qDebug()<<"min:"<<printstatus;
            this->ui->plot1DFile_Table->setItem(this->ui->plot1DFile_Table->rowCount()-1,0,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getMax(dataHold,rows)));
            qDebug()<<"max:"<<printstatus;
            this->ui->plot1DFile_Table->setItem(this->ui->plot1DFile_Table->rowCount()-1,1,new QTableWidgetItem(printstatus));
            printstatus = QString::fromStdString(std::to_string(getAvg(dataHold,rows)));
            qDebug()<<"avg:"<<printstatus;
            this->ui->plot1DFile_Table->setItem(this->ui->plot1DFile_Table->rowCount()-1,2,new QTableWidgetItem(printstatus));
        }
//        this->ui->plot1DFile_Table->sortItems(0);
        
    }
    
}



int column1D::loadData1D(QString filedir){
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

    
    columnNumber=count2;
    input.open(dir);
    for (rowNumber=0; std::getline(input, line); rowNumber++) {
    }
    input.close();
    qDebug()<<"Rownumber"<<rowNumber<<count1<<count2;
    
    if (count1!=count2){
//        input.open(dir);
//        std::getline(input,line1);
//        std::istringstream iss1(line1);
//        iss1 >> x >> y >> z;
//        
//        input.close();
        rowNumber--;
    }else{
        iss1 >> x;
        qDebug()<<"x:"<<x;
        if(isnan(x)){
            rowNumber--;
        }
//        std::ifstream read(dir, std::ios_base::ate );//open file
//        int length = 0;
//        
//        char c = '\0';
//        
//        if( read )
//        {
//            length = read.tellg();//Get file size
//            
//            // loop backward over the file
//            
//            for(int i = length-2; i > 0; i-- )
//            {
//                read.seekg(i);
//                c = read.get();
//                if( c == '\r' || c == '\n' )//new line?
//                    break;
//            }
//            std::getline(read, line1);//read last line
//            std::istringstream iss1(line1);
//            iss1 >> x >> y >> z;
//            read.close();
//            
//        }
        
    }

    
    vtkData= new double*[rowNumber];
    for (i=0;i<rowNumber;++i){
        vtkData[i] = new double[columnNumber];
    }
    input.open(dir);
    if (count1!=count2){
        
        std::getline(input,line1);
        std::istringstream iss1(line1);
        
    }else{
        iss1 >> x;
        qDebug()<<"x:"<<x;
        if(isnan(x)){
            std::getline(input,line1);
            std::istringstream iss1(line1);
        }
        
    }
    for (int j=0;j<rowNumber;++j){
        std::getline(input,line);
        std::istringstream iss(line);
        for (int k=0;k<columnNumber;++k){
            iss >> std::scientific;
            iss >>  vtkData[j][k];
        }
    }
    input.close();
    
    str="load.txt";
    const char *outdir=str.c_str();
    
    output.open(outdir);
    for(int i=0;i<rowNumber;i++){
        output << "i:" << i << ", vtkData:"<<vtkData[i][0] << "\n";
    }
    output.close();
    
    
//    xmax=x;
//    ymax=y;
//    zmax=z;
    rows = rowNumber;
    return columnNumber;
}


bool column1D::filter1DData(double *data){
    bool flagHolder=true;
        qDebug()<<"data:"<<*data<<data[0]<<data[1]<<data[2];
    for(int i=0;i<this->ui->plot1DRelationFile_Table->rowCount();i++){
        int relationCol=this->ui->plot1DRelationFile_Table->item(i, 0)->text().toInt()-1;
        double value=this->ui->plot1DRelationFile_Table->item(i, 2)->text().toDouble();
        std::string relation=this->ui->plot1DRelationFile_Table->item(i,1)->text().toStdString();
        //        qDebug()<<"relation:"<<relationCol<<relation.c_str()<<value;
        if(relation=="="){
            if (data[relationCol]==value) {
//                flagHolder*=true;
            }else{
                flagHolder=false;
            }
        }else if(relation==">"){
            if (data[relationCol]>value) {
//                flagHolder*=true;
            }else{
                flagHolder=false;
            }
        }else if(relation==">="){
            if (data[relationCol]>=value) {
//                flagHolder*=true;
            }else{
                flagHolder=false;
            }
        }else if(relation=="<"){
            if (data[relationCol]<value) {
//                flagHolder*=true;
            }else{
                flagHolder=false;
            }
        }else if(relation=="<="){
            if (data[relationCol]<=value) {
//                flagHolder*=true;
            }else{
                flagHolder=false;
            }
        }
    }
    return flagHolder;
}

void column1D::on_plot1DAddRelationFile_PB_released(){
    QString item;
    int row;
    qDebug()<<"Add button pushed";
    if ((this->ui->plot1DColFile_Combo->count()==0) |
        this->ui->plot1DRelationValueFile_LE->text().isEmpty()){
    }else{
        this->ui->plot1DRelationFile_Table->setEnabled(true);
        row=this->ui->plot1DRelationFile_Table->rowCount();
        qDebug()<<row;
        this->ui->plot1DRelationFile_Table->insertRow(row);
        //      row=row;
        item=this->ui->plot1DColFile_Combo->currentText();
        this->ui->plot1DRelationFile_Table->setItem(row,0,new QTableWidgetItem(item));
        item=this->ui->plot1DRelationFile_Combo->currentText();
        this->ui->plot1DRelationFile_Table->setItem(row,1,new QTableWidgetItem(item));
        item=this->ui->plot1DRelationValueFile_LE->text();
        this->ui->plot1DRelationFile_Table->setItem(row,2,new QTableWidgetItem(item));
        // item=this->ui->RGBA_LE->text();
        // this->ui->RGBScalar_Table->setItem(row,4,new QTableWidgetItem(item));
        this->ui->plot1DRelationFile_Table->sortItems(0,Qt::AscendingOrder);
        
    }
    
}

void column1D::on_plot1DFileY_LW_itemClicked(QListWidgetItem* item){
    if(item->checkState()){
        this->ui->plot1DLines_LW->addItem(item->text());
//        this->ui->plot1DLines_LW->sortItems();
        
        lineStyle.push_back(QPen());
        scatterStyle.push_back(int());
        lineName.push_back(QString());
        
        this->ui->plot1DLines_LW->setCurrentItem(this->ui->plot1DLines_LW->findItems(item->text(), Qt::MatchExactly).first());
        this->ui->plot1DLineRGBR_LE->setText("0");
        this->ui->plot1DLineRGBG_LE->setText("0");
        this->ui->plot1DLineRGBB_LE->setText("0");
        this->ui->plot1DLineWeight_LE->setText("2");
        this->ui->plot1DScatterStyle_Combo->setCurrentIndex(0);
        this->ui->plot1DLineStyle_Combo->setCurrentIndex(0);
        this->ui->plot1DLineName_LE->setText(QString::fromStdString("line"+std::to_string(lineStyle.count())));
        on_plot1DSetLine_PB_released();
    }else{
        if(!(this->ui->plot1DLines_LW->findItems(item->text(), Qt::MatchExactly).isEmpty())){
            int rownum=this->ui->plot1DLines_LW->row(this->ui->plot1DLines_LW->findItems(item->text(), Qt::MatchExactly).first());
            this->ui->plot1DLines_LW->takeItem(rownum);
            lineName.remove(rownum);
            lineStyle.remove(rownum);
            scatterStyle.remove(rownum);
            qDebug()<<"rownum" << rownum;
        }
    }
    if (this->ui->plot1DLines_LW->count()==0) {
        this->ui->plot1DSetLine_PB->setEnabled(false);
    }else{
        this->ui->plot1DSetLine_PB->setEnabled(true);
    }
    qDebug()<<"check:"<<item->checkState();
//    emit figureReplot();
}


void column1D::on_plot1DSetLine_PB_released(){
    int R=this->ui->plot1DLineRGBR_LE->text().toDouble();
    int G=this->ui->plot1DLineRGBG_LE->text().toDouble();
    int B=this->ui->plot1DLineRGBB_LE->text().toDouble();
    int weight=this->ui->plot1DLineWeight_LE->text().toDouble();
    int index=this->ui->plot1DLines_LW->currentRow();
    int psIndex=this->ui->plot1DLineStyle_Combo->currentIndex();
    int sIndex=this->ui->plot1DScatterStyle_Combo->currentIndex();
    QString name=this->ui->plot1DLineName_LE->text();
    
    lineStyle[index].setBrush(QColor(R,G,B));
    lineStyle[index].setWidth(weight);
    lineStyle[index].setStyle(lineStyleList[psIndex]);
    scatterStyle[index]=sIndex;
    lineName[index]=name;
    qDebug()<< "index:" << index << weight << R << G << B << name;
}

void column1D::on_plot1DLines_LW_currentRowChanged(int rowNum){
    if(rowNum!=-1){
        this->ui->plot1DLineRGBR_LE->setText(QString::fromStdString(std::to_string(lineStyle[rowNum].color().red())));
        this->ui->plot1DLineRGBG_LE->setText(QString::fromStdString(std::to_string(lineStyle[rowNum].color().green())));
        this->ui->plot1DLineRGBB_LE->setText(QString::fromStdString(std::to_string(lineStyle[rowNum].color().blue())));
        this->ui->plot1DLineWeight_LE->setText(QString::fromStdString(std::to_string(lineStyle[rowNum].width())));
        this->ui->plot1DScatterStyle_Combo->setCurrentIndex(scatterStyle[rowNum]);
        this->ui->plot1DLineStyle_Combo->setCurrentIndex(lineStyleList.indexOf(lineStyle[rowNum].style()));
        this->ui->plot1DLineName_LE->setText(lineName[rowNum]);
    }
    
}

void column1D::on_plot1DRemoveRelationFile_PB_released(){
    if(this->ui->plot1DRelationFile_Table->rowCount()>0){
        this->ui->plot1DRelationFile_Table->removeRow(this->ui->plot1DRelationFile_Table->currentRow());
    }
}

QPen column1D::getLineStyle(int rowNumber){
    return lineStyle[rowNumber];
}

QCPScatterStyle column1D::getScatterStyle(int rowNumber){
    return scatterStyleList[scatterStyle[rowNumber]];
}

QString column1D::getLineName(int rowNumber){
    return lineName[rowNumber];
}


double column1D::getMin(double *list,int length){
    double minValue;
    minValue=list[0];
    for(int i=0;i<length;++i){
        if(list[i]<minValue){
            minValue=list[i];
        }
    }
    return minValue;
}

double column1D::getMax(double *list,int length){
    double maxValue;
    maxValue=list[0];
    for(int i=0;i<length;++i){
        if(list[i]>maxValue){
            maxValue=list[i];
        }
    }
    return maxValue;
}

double column1D::getAvg(double *list,int length){
    double avgValue;
    avgValue=0;
    for(int i=0;i<length;++i){
        avgValue=avgValue+list[i];
    }
    avgValue=avgValue/length;
    return avgValue;
}

void column1D::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//    qDebug()<<"painting border";
}

