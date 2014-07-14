#include "ATDynamicPrototype.h"

using namespace std;

ATDynamicPrototype::ATDynamicPrototype(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

ATDynamicPrototype::~ATDynamicPrototype()
{

}

void ATDynamicPrototype::displayScene(QGraphicsScene * scnene)
{
	ui.gvMain->setScene(scnene);  
}

void ATDynamicPrototype::on_btn_clicked()
{
	emit move_btn_clicked();
}