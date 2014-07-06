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