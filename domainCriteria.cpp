#include "domainCriteria.h"
//#include "ui_domainCriteria.h"


domainCriteria::domainCriteria(SimpleView *simpleView, QDialog *parent) :
QDialog(parent),
domainui(new Ui::DomainCriteria)
{
	domainStdAngle = 180.0 ;
	domainStdValue = 0.5;
	qDebug() << "domain :::" << domainStdAngle << domainStdValue;
	domainui->setupUi(this);
	main3D = simpleView;
}

domainCriteria::~domainCriteria()
{
	delete domainui;
}

double domainCriteria::getDomainStdAngle()
{
	qDebug() << "return angle:" << domainStdAngle;
	return domainStdAngle;
}

double domainCriteria::getDomainStdValue()
{
	qDebug() << "return value:" << domainStdValue;
	return domainStdValue;
}
void domainCriteria::on_domainStdValue_LE_editingFinished()
{
	domainStdValue = this->domainui->domainStdValue_LE->text().toDouble();
}
void domainCriteria::on_domainStdAngle_LE_editingFinished() {
	domainStdAngle = this->domainui->domainStdAngle_LE->text().toDouble();
	qDebug() << "domain angle:" << domainStdAngle;
}
