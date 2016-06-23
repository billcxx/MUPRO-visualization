#ifndef COLUMN1D_H
#define COLUMN1D_H

#include <QWidget>
#include <QListWidgetItem>
#include "qcustomplot.h"

namespace Ui{
    class column1D;
}

class column1D : public QWidget
{
    Q_OBJECT
    
public:
    explicit column1D(QWidget *parent = 0);
    int getFilteredCount();
    ~column1D();
    QVector<double> returnX();
    double returnXMin();
    double returnXMax();
    QVector<double> returnY(int colY);
    double returnYMin();
    double returnYMax();
    int getColumns();
    QPen getLineStyle(int rowNumber);
    QCPScatterStyle getScatterStyle(int rowNumber);
    QString getLineName(int rowNumber);
    
signals:
    void figureReplot();
    
private slots:
    void on_load1DFile_PB_clicked();
    int loadData1D(QString filedir);
    void on_plot1DAddRelationFile_PB_released();
    bool filter1DData(double *data);
    void on_plot1DFileY_LW_itemClicked(QListWidgetItem* item);
    
    void on_plot1DSetLine_PB_released();
    void on_plot1DLines_LW_currentRowChanged(int rowNum);
    void on_plot1DRemoveRelationFile_PB_released();
    
protected:
    void paintEvent(QPaintEvent *);
    
    
private:
    double getMin(double *list,int length);
    double getMax(double *list,int length);
    double getAvg(double *list,int length);
    int filter();
    bool loaded=false;
    double **vtkData;
    QVector<double*> dataFiltered;
    QString printstatus;
//    double xmin=0,xmax=0,ymin=0,ymax=0,zmin=0,zmax=0;
    double xmin1D=1,xmax1D=0,ymin1D=1,ymax1D=0;
    int columns,rows;
    
    QVector<Qt::PenStyle> lineStyleList;
    QVector<int> scatterStyle;
    QVector<QPen> lineStyle;
    QVector<QString> lineName;
    QVector< QVector<double> > rgbWidth;
    QVector<QCPScatterStyle::ScatterShape> scatterStyleList;
    
    Ui::column1D *ui;

    
};

#endif // COLUMN1D_H
