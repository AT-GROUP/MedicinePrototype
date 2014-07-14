#include "ATDynamicIESApp.h"
#include "forms/ATDynamicPrototype.h"
#include "ATWorld.h"

using namespace std;

int main(int argc, char *argv[])
{
	ATDynamicIESApp a(argc, argv);

	ATDynamicPrototype w;

	w.show();

	w.displayScene(a.world());

	return a.exec();
}
