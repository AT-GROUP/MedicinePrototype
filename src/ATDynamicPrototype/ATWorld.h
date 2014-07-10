
#ifndef ATDYNAMICPROTOTYPE_ATWorld_H
#define ATDYNAMICPROTOTYPE_ATWorld_H

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItemGroup>
#include <QTableWidget>
#include <unordered_set>
#include <functional>
#include <vector>

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
	double latitudeToCoord(double latitude) const;
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
class ATSceneItem : public QGraphicsPixmapItem
{
public:
	ATSceneItem() :cur_pos(NULL) {setAcceptHoverEvents(true);};

	MapNode get_pos() 
		{ return *cur_pos;};
	void set_pos(MapNode * pos) 
		{cur_pos = pos;};

	QGraphicsProxyWidget * prx_item;
	QTableView * this_info;

	void do_the_stuff(QTableView * this_info);

private:
	MapNode * cur_pos;

protected:
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event);
};

class ATAccident : public ATSceneItem			 //дтп TBD * отображение кол-ва скорых при наведении
{
public:
	ATAccident(MapNode * pos, int inj);

	int get_inj()
		{ return injured; };            //вернуть кол-во жертв
	bool set_inj();                              //рандом на кол-во пострадавших, если изменилось кол-во пострадавших (при создании события или по приезду бригады на место), то - true

private:
	int injured;                                 //кол-во пострадавших
	int amb_on_scene;
};


class ATAmbulance : public ATSceneItem			 //скорая TBD * отображение текущего направления движения (на дтп/в больницу)
{
public:
	ATAmbulance(MapNode * pos);

	bool on_acc() 
		{ if (cur_acc != NULL) return true; };   //если бригада на задании (cur_acc != NULL), то true
	ATAccident * get_acc() 
		{ return cur_acc; };            //вернуть текущее задание
	void set_acc(ATAccident * acc) 
		{ cur_acc = acc; };     //задать активное задание
	int get_vel() 
		{ return cur_velocity; };                //вернуть скорость
	void set_vel(int vel) 
		{ cur_velocity = vel; };         //задать скорость

	void process_acc()
		{};                        //обработка дтп

	bool update()
		{};                             //обновление положения бригады на карте

private:
	ATAccident * cur_acc;                        //текущее задание для бригады
	int cur_velocity;                            //скорость машины
};

class ATHospital : public ATSceneItem			 //больница TBD * отображение кол-ва свободных мест для пострадавших, кол-ва скорых (иконки(зеленые палки/уменьшенные иконки скорой) цветные(в гараже(свободны))/серые(на задании))
{
public:
	ATHospital(MapNode * pos, int new_wards);   

	ATAmbulance * get_car();                     //вернуть машину (первую свободную)
	void add_car (ATAmbulance * car)
		{ all_amb.push_back(car); };          //добавить машину

private:
	std::vector <ATAmbulance *> all_amb;         //список бригад в данном лечебном учреждении
	MapNode * pos;                                //расположение больницы
	int wards;                                   //кол-во палат
	int car_slots;
	std::string free_cars;
};

class ATWorld : public QGraphicsScene, public ATMap
{
	Q_OBJECT

public:
	ATWorld(const std::string & map_file_name);
	
	void loadMap();
	void generate_acc()
		{};

	void generate_accident()
		{};                  //сгенерировать дтп
	void resolve_accident()
		{};                   //устранить последствия дтп

public slots:
	void testUpdate();
private:
	QGraphicsEllipseItem * m_pBall;
	std::vector <ATAccident *> active_accidents; //список активных дтп
 	std::vector <ATHospital *> hospitals;        //список больниц
};


#endif
