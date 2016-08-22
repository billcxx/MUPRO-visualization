#ifndef DomainCriteria_H
#define DomainCriteria_H

#include <QDialog>
#include <SimpleView.h>
#include <QMessageBox>
#include "ui_domainCriteria.h"

//namespace Ui {
//	class DomainCriteria;
//}

class domainCriteria : public QDialog
{
	Q_OBJECT

public:
	explicit domainCriteria(SimpleView *simpleView, QDialog *parent = 0);
	~domainCriteria();
	double getDomainStdAngle();
	double getDomainStdValue();
	private slots:
	void on_domainStdAngle_LE_editingFinished();
	void on_domainStdValue_LE_editingFinished();
private:
	Ui::DomainCriteria *domainui;
	SimpleView *main3D;
	double domainStdAngle = 4.0;
	double domainStdValue = 0.5;

};

#endif /* DomainCriteria_H*/