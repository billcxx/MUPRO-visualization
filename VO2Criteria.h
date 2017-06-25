#ifndef VO2Criteria_H
#define VO2Criteria_H

#include <QDialog>
#include <SimpleView.h>
#include <QMessageBox>
#include "ui_VO2Criteria.h"

//namespace Ui {
//	class DomainCriteria;
//}

class VO2Criteria : public QDialog
{
	Q_OBJECT

public:
	explicit VO2Criteria(SimpleView *simpleView, QDialog *parent = 0);
	~VO2Criteria();
	double getM1_mod();
	double getM1_ang();
	double getM2_mod();
	double getM2_ang();
	private slots:
	void on_vo2_M1_mod_LE_editingFinished();
	void on_vo2_M1_ang_LE_editingFinished();
	void on_vo2_M2_mod_LE_editingFinished();
	void on_vo2_M2_ang_LE_editingFinished();
private:
	Ui::VO2Criteria *domainui;
	SimpleView *main3D;
	double m1_mod = 0.1;
	double m1_ang = 10.0;
	double m2_mod = 0.1;
	double m2_ang = 10.0;


};

#endif /* VO2-criteria_H*/