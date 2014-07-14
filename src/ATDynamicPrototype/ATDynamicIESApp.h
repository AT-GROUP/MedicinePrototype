
#ifndef ATDYNAMICPROTOTYPE_ATDynamicIESApp_H
#define ATDYNAMICPROTOTYPE_ATDynamicIESApp_H

#include <QtWidgets/QApplication>

class TempSolverWrapper;
class QTimer;
class ATWorld;

class ATDynamicIESApp: public QApplication
{
	Q_OBJECT
public:
	ATDynamicIESApp(int argc, char *argv[]);
	~ATDynamicIESApp();
	ATWorld * world();

private slots:
	void move_car();

private:
	QTimer * m_pTickTimer;
	TempSolverWrapper * m_pTemporalSolver;
	ATWorld * m_pWorld;
};

#endif
