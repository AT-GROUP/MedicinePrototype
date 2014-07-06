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

private:
	Ui::ATDynamicPrototypeClass ui;
};

#endif // ATDYNAMICPROTOTYPE_H
