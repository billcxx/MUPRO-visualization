#include "VO2Criteria.h"
//#include "ui_domainCriteria.h"


VO2Criteria::VO2Criteria(SimpleView *simpleView, QDialog *parent) :
QDialog(parent),
domainui(new Ui::VO2Criteria)
{
	m1_mod = 0.1 ;
	m1_ang = 10.0;
	m2_mod = 0.1 ;
	m2_ang = 10.0;
	qDebug() << "domain :::" << m1_mod << m1_ang;
	domainui->setupUi(this);
	main3D = simpleView;
}

VO2Criteria::~VO2Criteria()
{
	delete domainui;
}

double VO2Criteria::getM1_mod()
{
	qDebug() << "return angle:" << m1_mod;
	return m1_mod;
}

double VO2Criteria::getM1_ang()
{
	qDebug() << "return value:" << m1_ang;
	return m1_ang;
}
double VO2Criteria::getM2_mod()
{
	qDebug() << "return angle:" << m2_mod;
	return m2_mod;
}

double VO2Criteria::getM2_ang()
{
	qDebug() << "return value:" << m2_ang;
	return m2_ang;
}

void VO2Criteria::on_vo2_M1_mod_LE_editingFinished()
{
	m1_mod = this->domainui->vo2_M1_mod_LE->text().toDouble();
}
void VO2Criteria::on_vo2_M1_ang_LE_editingFinished()
{
	m1_ang = this->domainui->vo2_M1_ang_LE->text().toDouble();
}
void VO2Criteria::on_vo2_M2_mod_LE_editingFinished()
{
	m2_mod = this->domainui->vo2_M2_mod_LE->text().toDouble();
}
void VO2Criteria::on_vo2_M2_ang_LE_editingFinished()
{
	m2_ang = this->domainui->vo2_M2_ang_LE->text().toDouble();
}
