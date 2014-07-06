
#include "ATDynamicIESApp.h"
#include <QtCore/QTimer>
#include <TempSolverWrapper/TempSolverWrapper.h>
#include "ATWorld.h"

ATDynamicIESApp::ATDynamicIESApp(int argc, char *argv[])
	:QApplication(argc, argv), m_pWorld(new ATWorld("map.osm"))
{
		
	m_pTemporalSolver = new TempSolverWrapper();
	//string res = wr->processMessage("aaaa123");

	m_pTickTimer = new QTimer(this);
	connect(m_pTickTimer, &QTimer::timeout, m_pWorld, &ATWorld::testUpdate);
	m_pTickTimer->start(50);



}

ATDynamicIESApp::~ATDynamicIESApp()
{
	m_pTickTimer->stop();
	delete m_pTickTimer;
	delete m_pTemporalSolver;
}

ATWorld * ATDynamicIESApp::world()
{
	return m_pWorld;
}
