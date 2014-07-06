#ifndef AMAPVIEW_H
#define AMAPVIEW_H

#include <QGraphicsView>

class AMapView : public QGraphicsView
{
	Q_OBJECT

public:
	AMapView(QWidget *parent = 0);
	~AMapView();

protected:
	virtual void wheelEvent(QWheelEvent* event);
};

#endif // AMAPVIEW_H
