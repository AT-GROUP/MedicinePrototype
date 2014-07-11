
#include "ATWorld.h"
#include "AT_info_table_models.h"
#include <QtWidgets/QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QHeaderView>
#include <fstream>
#include <iostream>
#include <exception>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlsave.h>
#include <exception>

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

//===================== ATSceneItem ==============================
void ATSceneItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
   prx_item = this->scene()->addWidget(this_info);
   prx_item->setPos(event->scenePos());
   this_info->show();
   event->accept();
}

void ATSceneItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{    
    this_info->hide();
    event->accept();
}

void ATSceneItem::do_the_stuff(QTableView * this_info)
{
	this_info->setAutoScroll (false);
    this_info->horizontalHeader()->hide();
    this_info->verticalHeader()->hide();
	this_info->resizeColumnsToContents();
	this_info->setFixedSize(this_info->horizontalHeader()->length(), this_info->verticalHeader()->length());
	this_info->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this_info->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//====================== Accidents ==============================
ATAccident::ATAccident(MapNode * pos, int inj)
	:injured(inj), amb_on_scene(0)
{
	set_pos(pos);

	setPixmap(QPixmap("./Resources/dtp.png"));

	this_info = new QTableView();
    this_info->setModel(new ATAccident_info_table_model());
	do_the_stuff(this_info);
}

bool ATAccident::set_inj()
{
	if (amb_on_scene == 0)
	{
		injured = std::rand() % 9 + 1;
		return false;
	}
	else
	{
		int inj_old;
		if (amb_on_scene == 1)
		{
			inj_old = injured;
			injured += std::rand() % 5;
			if (inj_old == injured)
				return false;
			else
				return true;
		}
		else
		{
			inj_old = injured;
			injured += std::rand() % 1;
			if (inj_old == injured)
				return false;
			else
				return true;
		}
	}
}

//====================== Ambulances ==============================
ATAmbulance::ATAmbulance(MapNode * pos)
	:cur_velocity(0), cur_acc(NULL)
{
	set_pos(pos);

	setPixmap(QPixmap("./Resources/amb_car.png"));

	this_info = new QTableView();
    this_info->setModel(new ATAmbulance_info_table_model());
    do_the_stuff(this_info);
}

bool ATAmbulance::move(MapRoad *path, MapCoord zeroPoint)
{
	int length = 0;
	int start_x = path->m_nodes.at(0)->latitude();
	int start_y = path->m_nodes.at(0)->longtitude();
	int cur_x, cur_y, prev_x, prev_y;
	prev_x = start_x;
	prev_y = start_y;

	for (auto node : path->m_nodes)
	{
		if (length < cur_velocity)
		{
			if (length == 0)
				length = sqrt((node->latitude() - prev_x)*(node->latitude() - prev_x) + (node->longtitude() - prev_y)*(node->longtitude() - prev_y));   //рассчет расстояния между предъидущей и текущей точками
			else
				length += sqrt((node->latitude() - prev_x)*(node->latitude() - prev_x) + (node->longtitude() - prev_y)*(node->longtitude() - prev_y));  //рассчет расстояния между предъидущей и текущей точками

			prev_x = node->latitude();
			prev_y = node->longtitude();
			this->set_pos(node);
			setPos(637800.137 * (node->latitude() - zeroPoint.latitude)*sin(node->longtitude())*cos(node->latitude())*(150/(150+6378.137*sin(node->latitude()))), -637800.137 * (node->longtitude() - zeroPoint.longtitude)*cos(node->longtitude())*cos(node->latitude())*(150/(150+6378.137*sin(node->latitude()))));
		}
		else
		{
			MapNode *new_pos = new MapNode(NULL , (node->latitude() - prev_x)/length, (node->longtitude() - prev_y)/length);
			this->set_pos(new_pos);
			setPos(637800.137 * (new_pos->latitude() - zeroPoint.latitude)*sin(new_pos->longtitude())*cos(new_pos->latitude())*(150/(150+6378.137*sin(new_pos->latitude()))), -637800.137 * (new_pos->longtitude() - zeroPoint.longtitude)*cos(new_pos->longtitude())*cos(new_pos->latitude())*(150/(150+6378.137*sin(new_pos->latitude()))));
			length = 0;
		}
	}
	return true;
}

//====================== Hospitals ===============================
ATHospital::ATHospital(MapNode * pos, int new_wards)
	:wards(new_wards), all_amb(NULL), car_slots(9)
{
	set_pos(pos);

	setPixmap(QPixmap("./Resources/Hosp.png"));

	for (int i=0; i < car_slots; ++i)
	{
		free_cars += std::to_string(i);
	}

	this_info = new QTableView();
    this_info->setModel(new ATHospital_info_table_model());
    do_the_stuff(this_info);
}

ATAmbulance * ATHospital::get_car()
{
	std::string str; int i;
	if (car_slots < 10 && car_slots >= 0)
	{
		str = free_cars[car_slots];
		free_cars.erase(car_slots-1,1);
		car_slots -= 1;
	}
	i = atoi(str.c_str());
	return all_amb.at(i);
}

//======================== World =================================
ATWorld::ATWorld(const std::string & map_file_name)
	:ATMap(map_file_name), hospitals(NULL), active_accidents(NULL)
{
	loadMap();
	
	ATAmbulance *amb1 = new ATAmbulance(m_roads.at(10)->m_nodes.at(0));
	//amb1->setPos(637800.137 * (m_roads.at(10)->m_nodes.at(0)->latitude() - m_zeroPoint.latitude)*sin(m_roads.at(10)->m_nodes.at(0)->longtitude())*cos(m_roads.at(10)->m_nodes.at(0)->latitude())*(150/(150+6378.137*sin(m_roads.at(10)->m_nodes.at(0)->latitude()))), -637800.137 * (m_roads.at(10)->m_nodes.at(0)->longtitude() - m_zeroPoint.longtitude)*cos(m_roads.at(10)->m_nodes.at(0)->longtitude())*cos(m_roads.at(10)->m_nodes.at(0)->latitude())*(150/(150+6378.137*sin(m_roads.at(10)->m_nodes.at(0)->latitude()))));
	amb1->setPos(-5000, 10000);
	addItem(amb1);
	//amb1->move(m_roads.at(2), m_zeroPoint);
	
	/*
	QPoint *pnt1 = new QPoint(100,60);
	auto acc = new ATAccident(pnt1, 1);
	addItem(acc);

	QPoint *pnt2 = new QPoint(60,10);
	auto amb = new ATAmbulance(pnt2);
	addItem(amb);

	QPoint *pnt3 = new QPoint(210,100);
	auto hsp = new ATHospital(pnt3, 100);
	addItem(hsp);*/
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
