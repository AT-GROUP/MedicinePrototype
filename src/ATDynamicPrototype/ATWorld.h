
#ifndef ATDYNAMICPROTOTYPE_ATWorld_H
#define ATDYNAMICPROTOTYPE_ATWorld_H

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItemGroup>
#include <unordered_set>
#include <functional>
#include <vector>
#include <QListWidget>
#include <QXmlStreamReader>
struct MapCoord
{
	MapCoord(double latitude_ = 0.0, double longtitude_ = 0.0)
		:latitude(latitude_), longtitude(longtitude_)
	{
	}

	MapCoord operator-(const MapCoord & other)
	{
		MapCoord result(latitude - other.latitude, longtitude - other.longtitude);
		return result;
	}

	double	latitude,//x
			longtitude;	//y
};

struct MapNode
{
	MapNode(size_t name_, double latitude_ = 0.0, double longtitude_ = 0.0)
		:m_name(name_), m_coord(latitude_, longtitude_)
	{

	}

	double latitude() const
	{
		return m_coord.latitude;
	}

	double longtitude() const
	{
		return m_coord.longtitude;
	}
	
	size_t m_name;

	MapCoord m_coord;
};

struct NodeHasher
{
	size_t operator()(const MapNode * el) const
	{
		std::hash<size_t> hasher;
		return hasher(el->m_name);
	}
};

struct NodeEqualer
{
	bool operator()(const MapNode * el1, const MapNode * el2) const
	{
		return el1->m_name == el2->m_name;
	}
};

struct MapRoad
{
	std::vector<MapNode*> m_nodes;
};

class ATMap
{
public:
	ATMap(const std::string & file_name);
	~ATMap();
	double latitudeToCoord(double latitude, double longtitude) const;
	double longtitudeToCoord(double longtitude, double latitude ) const;
	QPointF toSceneCoords(const MapCoord & map_coords) const;
	
protected:
	  
	std::unordered_set<MapNode*, NodeHasher, NodeEqualer> m_nodes;
	std::vector<MapRoad*> m_roads;
	MapCoord m_zeroPoint;
};

class ATGraphicsMapNode : public QGraphicsItemGroup
{
public:
	ATGraphicsMapNode(MapNode * p_node, const ATMap * p_map);
private:
	MapNode * m_pNode;
};

class ATGraphicsMapRoad : public QGraphicsItemGroup
{
public:
	ATGraphicsMapRoad(MapRoad * p_road, const ATMap * p_map);
private:
	MapRoad * m_pRoad;
};

class ATWorld : public QGraphicsScene, public ATMap
{
	Q_OBJECT

public:
	ATWorld(const std::string & map_file_name);
	void loadMap();
	
public slots:
	void testUpdate();
		
private:
	QGraphicsEllipseItem * m_pBall;
	
};

#endif
