#ifndef ATDYNAMICPROTOTYPE_H
#define ATDYNAMICPROTOTYPE_H

#include <QtWidgets/QMainWindow>
#include "ui_ATDynamicPrototype.h"

class ATDynamicPrototype : public QMainWindow
{
	Q_OBJECT

public:
	ATDynamicPrototype(QWidget *parent = 0);
	~ATDynamicPrototype();
	void displayScene(QGraphicsScene * scnene);

signals:
	void move_btn_clicked();

private slots:
	void on_btn_clicked();

private:
	Ui::ATDynamicPrototypeClass ui;
};

#endif // ATDYNAMICPROTOTYPE_H
