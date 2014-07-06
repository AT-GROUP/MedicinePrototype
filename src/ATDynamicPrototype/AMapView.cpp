#include "AMapView.h"
#include <QtGui/QWheelEvent>

AMapView::AMapView(QWidget *parent) : QGraphicsView(parent)
{
	setDragMode(ScrollHandDrag);
}

AMapView::~AMapView()
{

}

void AMapView::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers().testFlag(Qt::ControlModifier))
	{
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		double scaleFactor = 1.15;
		if(event->delta() > 0)
		{
			scale(scaleFactor, scaleFactor);
		} 
		else 
		{
			scale(1.0 / scaleFactor, 1.0 / scaleFactor);
		}
	}
}