
#include "ATWorld.h"
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QXmlStreamReader>
#include <fstream>
#include <iostream>
#include <exception>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlsave.h>
#include <exception>
//#include "MyGraphicsView.h"
#include <qfile.h>
//#include <osmreader.h>
//#include <osmium.hpp>

#define xml_for_each_child(root, iterator) for(xmlNode * iterator = root->children; iterator; iterator = iterator->next) if (iterator->type == XML_ELEMENT_NODE)

const char * xml_node_attr_data(xmlNode * node, const char * attr_name)
{
	for(xmlAttr * cur_attr = node->properties; cur_attr; cur_attr=cur_attr->next)
	{
		if(!strcmp((char*)cur_attr->name, attr_name))
			return (char*)(cur_attr->children->content);
	}
	return 0;
}


ATMap::ATMap(const std::string & file_name)
{
	xmlDoc * doc = xmlReadFile(file_name.c_str(), 0, 0);
	
	if(!doc)
		throw std::runtime_error("Unable to open map file");

	xmlNode * root_element = xmlDocGetRootElement(doc);
	
	//Parse nodes
	xml_for_each_child(root_element, xml_node)
	{
		if(!strcmp((char*)xml_node->name, "node"))
		{
			auto new_node = new MapNode(_atoi64(xml_node_attr_data(xml_node, "id")), atof(xml_node_attr_data(xml_node, "lat")), atof(xml_node_attr_data(xml_node, "lon")));
			m_nodes.insert(new_node);
		}
		else if(!strcmp((char*)xml_node->name, "way"))
		{
			auto new_road = new MapRoad();

			xml_for_each_child(xml_node, way_node)
			{
				if(!strcmp((char*)way_node->name, "nd"))
				{
					auto c_id = xml_node_attr_data(way_node, "ref");
					MapNode tmp_node(_atoi64(c_id));
					auto node_it = m_nodes.find(&tmp_node);
					if(node_it != m_nodes.end())
					{
						new_road->m_nodes.push_back(*node_it);
					}
					else
						throw std::runtime_error("Unable to find map node");
				}
			}

			m_roads.push_back(new_road);
		}
	}


	xmlFreeDoc(doc);
	xmlCleanupParser();

	//Zero point
	m_zeroPoint.latitude = 55.4770000;
	m_zeroPoint.longtitude = 37.0847000;
}

ATMap::~ATMap()
{
}

double ATMap::latitudeToCoord(double latitude, double longtitude) const
{	
	return 637800.137 * (latitude - m_zeroPoint.latitude)*sin(longtitude)*cos(latitude)*(150/(150+6378.137*sin(latitude)));
}

double ATMap::longtitudeToCoord(double longtitude, double latitude) const
{
	return -637800.137 * (longtitude - m_zeroPoint.longtitude)*cos(longtitude)*cos(latitude)*(150/(150+6378.137*sin(latitude)));

}

QPointF ATMap::toSceneCoords(const MapCoord & map_coords) const
{
	return QPointF(longtitudeToCoord(map_coords.longtitude, map_coords.latitude), latitudeToCoord(map_coords.latitude, map_coords.longtitude));

}



//=======================Map node visualization=========================
ATGraphicsMapNode::ATGraphicsMapNode(MapNode * p_node, const ATMap * p_map)
	:QGraphicsItemGroup()
{
	auto point = new QGraphicsEllipseItem(-1, -1, 2, 2, this);
	addToGroup(point);

	setPos(p_map->longtitudeToCoord(p_node->longtitude(), p_node->latitude()),p_map->latitudeToCoord(p_node->latitude(), p_node->longtitude()));
}

//======================Road visualization==============================
ATGraphicsMapRoad::ATGraphicsMapRoad(MapRoad * p_road, const ATMap * p_map)
{
	auto it = p_road->m_nodes.begin();

	QPointF zero_coord = p_map->toSceneCoords((*it)->m_coord);
	

	for(int i = 1; i < p_road->m_nodes.size(); ++i)
	{
		auto first_pt = p_road->m_nodes[i-1], last_pt = p_road->m_nodes[i];

		QPointF first_coord = p_map->toSceneCoords(first_pt->m_coord) - zero_coord, last_coord = p_map->toSceneCoords(last_pt->m_coord) - zero_coord;
		auto line = new QGraphicsLineItem(first_coord.x(), first_coord.y(), last_coord.x(), last_coord.y(), this);
		addToGroup(line);
	}

	setPos(zero_coord);
	//var
}

ATWorld::ATWorld(const std::string & map_file_name)
	:ATMap(map_file_name)
{
	loadMap();

	/*auto rect = new QGraphicsRectItem(0, 0, 300, 400);
	addItem(rect);

	m_pBall = new QGraphicsEllipseItem(-10, -10, 20, 20);
	m_pBall->setBrush(QBrush(QColor(0, 255, 0)));
	addItem(m_pBall);
	m_pBall->setPos(100, 60);*/

	//Place random ambulances
}

void ATWorld::loadMap()
{
	for(auto n : m_nodes)
	{
		auto new_gr_node = new ATGraphicsMapNode(n, this);

		addItem(new_gr_node);

	}

	for(auto r : m_roads)
	{
		auto new_gr_road = new ATGraphicsMapRoad(r, this);
		addItem(new_gr_road);
	}
}

void ATWorld::testUpdate()
{
	//auto old_pos = m_pBall->pos();
	//m_pBall->setPos(old_pos.x() + 0.3, old_pos.y() + 0.9);
}
