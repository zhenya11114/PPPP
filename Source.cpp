#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
#include <iostream>

constexpr auto SIZE = 16;

const std::string points[SIZE] = { "msk_AP","msk_TS","msk_WH","mzh_TS",
"mzh_WH","zvn_WH","NN_AP","NN_TS", "NN_WH","dzr_TS","dzr_WH",
"vlg_AP","vlg_TS","vlg_WH","kam_TS","kam_WH" };
const std::map<std::string, int> towns = {
	{"Moscow", 2},
	{"Mozhaisk", 4},
	{"Zvenigorod", 5},
	{"Nizhniy Novgorod", 8},
	{"Dzerzhinsk", 10},
	{"Volgograd", 13},
	{"Kamishin", 15} };
const std::map<std::string, int> table = {
	{"msk", 0},
	{"mzh", 1},
	{"zvn", 2},
	{"NN", 3},
	{"dzr", 4},
	{"vlg", 5},
	{"kam", 6} };
const std::tuple<int, int, double> tableCost[21] = {
	{500, 300, 100},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{0, 0, 0},
	{100, 60, 50},
	{500, 300, 100},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{200, 100, 500},
	{100, 60, 50},
	{500, 300, 100},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{200, 100, 500},
	{100, 60, 50} };
const int matrixDist[SIZE][SIZE] = {
{0, 20, 30, 108, 110, 65, 398, 0, 0, 0, 0, 926, 0, 0, 0, 0},
{20, 0, 10, 98, 100, 55, 0, 415, 0, 483, 0, 0, 937, 0, 1204, 0},
{30, 10, 0, 108, 110, 65, 0, 0, 430, 0, 390, 0, 0, 652, 0, 1234},
{108, 98, 108, 0, 5, 0, 0, 0, 0, 581, 0, 0, 1035, 0, 1302, 0},
{110, 100, 110, 5, 0, 78, 0, 0, 540, 0, 500, 0, 0 ,1062, 0, 1344},
{65, 55, 65, 0, 78, 0, 0, 0, 495, 0, 455, 0, 0, 1017, 0, 1299},
{398, 0, 0, 0, 0, 0, 0, 19, 23, 0, 26, 828, 0, 0, 0, 0},
{0, 415, 0, 0, 0, 0 ,19, 0, 4, 32, 0, 0, 840, 0, 919, 0},
{0, 0, 430, 0, 540, 495, 23, 4, 0, 0, 40, 0, 0, 849, 0, 1010},
{0, 483, 0, 581, 0, 0, 0, 32, 0, 0, 4, 0, 872, 0, 951, 0},
{0, 0, 390, 0, 500, 455, 26, 0, 40, 4, 0, 0, 0, 889, 0, 1050},
{926, 0, 0, 0, 0 ,0 ,828, 0, 0 ,0 ,0, 0, 15, 16, 0, 285},
{0, 937, 0, 1035, 0, 0, 0, 840, 0, 872, 0, 15, 0, 2, 257, 281},
{0, 0, 952, 0, 1062, 1017, 0, 0, 849, 0, 889, 16, 2, 0, 0 ,282},
{0, 1204, 0, 1302, 0, 0, 0, 919, 0, 951, 0, 0, 257, 0, 0, 2},
{0, 0, 1234, 0, 1344, 1299, 0, 0, 1010, 0, 1050, 285, 281, 282, 2, 0} };

enum Type { Turbo, Standart, Economy };

//Паттерн МОСТ - родительский класс
//реализуется посредством наследования в Train, Plane, Car
//затем используется в классе Track в конструкторе
class DistPriceable {
protected:
	int speed;
	int volume;
	double price;
	int distance;
public:
	virtual double sumCost(int, int);
	virtual double sumTime(int);
	virtual int getDistance();
};

double DistPriceable::sumCost(int mass, int dist)
{
	return (mass / volume) * sumTime(dist) * price;
}
double DistPriceable::sumTime(int dist)
{
	return dist / speed;
}
int DistPriceable::getDistance()
{
	return this->distance;
}

class Train : public DistPriceable
{
public:
	Train();
	Train(std::tuple<int, int, double>, int);
	~Train();
};
class Plane : public DistPriceable
{
public:
	Plane();
	Plane(std::tuple<int, int, double>, int);
	~Plane();
};
class Car : public DistPriceable
{
public:
	Car();
	Car(std::tuple<int, int, double>, int);
	~Car();
};

class Track
{
	double cost;
	double time;
	int volume;
public:
	Track();
	//Паттерн МОСТ - встраивание в объект
	Track(std::vector<DistPriceable>&, int);
	Track(DistPriceable&, int);
	double getCost();
	~Track();
};

//Паттерн СТРАТЕГИЯ - объявление классов
//реализация без шаблонов
//используется в классе Order
class Strategy
{
public:
	virtual ~Strategy() {}
	virtual Track use(int* path, int volume) = 0;
};
class Context
{
protected:
	Strategy* operation;

public:
	virtual ~Context() {}
	virtual Track useStrategy(int* path, int volume) = 0;
	virtual void setStrategy(Strategy* v) = 0;
};
class OrderContext : public Context{
public:
	Track useStrategy(int* path, int volume)
	{
		return operation->use(path, volume);
	}

	void setStrategy(Strategy* o)
	{
		operation = o;
	}
};

class BestGenStrategy_1 : public Strategy
{
public:
	Track use(int* path, int volume) {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[0]]))
			{
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Track track = Track(car1, volume);
		return track;
	}
};
class BestGenStrategy_2 : public Strategy
{
public:
	Track use(int* path, int volume) {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[0]]))
			{
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Car car2 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[2]]))
			{
				car2 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
			}
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		Track track = Track();

		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[1]]) && points[path[1]].find("TS"))
			{
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);

				std::vector<DistPriceable> v;
				v.push_back(car1);
				v.push_back(car2);
				v.push_back(train1);
				track = Track(v, volume);
			}

			if ((*it).first.find(points[path[1]]) && points[path[1]].find("AP"))
			{
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[1]][path[2]]);

				std::vector<DistPriceable> v;
				v.push_back(car1);
				v.push_back(car2);
				v.push_back(plane1);
				track = Track(v, volume);
			}
		}

		return track;
	}
};
class BestGenStrategy_3 : public Strategy
{
public:
	Track use(int* path, int volume) {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[0]]))
			{
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[1]]) && points[path[1]].find("TS"))
			{
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
			}
			if ((*it).first.find(points[path[1]]) && points[path[1]].find("AP"))
			{
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[1]][path[2]]);
			}
		}

		Car car2 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[2]]))
			{
				car2 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
			}
		}

		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[3]]) && points[path[3]].find("AP"))
			{
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[3]][path[4]]);
			}
			if ((*it).first.find(points[path[3]]) && points[path[3]].find("TS"))
			{
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[3]][path[4]]);
			}
		}

		Car car3 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[4]]))
			{
				car3 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[4]][path[5]]);
			}
		}

		std::vector<DistPriceable> v;
		v.push_back(car1);
		v.push_back(car2);
		v.push_back(car3);
		v.push_back(train1);
		v.push_back(plane1);
		Track track = Track(v, volume);
		return track;
	}
};
class BestGenStrategy_4 : public Strategy
{
public:
	Track use(int* path, int volume) {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[0]]))
			{
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Train train1 = Train();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[1]]))
			{
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
			}
		}

		Car car2 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[2]]))
			{
				car2 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
			}
		}

		Plane plane1 = Plane();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[3]]))
			{
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[3]][path[4]]);
			}
		}

		Car car3 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[4]]))
			{
				car3 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[4]][path[5]]);
			}
		}

		Train train2 = Train();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[5]]))
			{
				train2 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[5]][path[6]]);
			}
		}

		Car car4 = Car();
		for (auto it = table.begin(); it != table.end(); it++)
		{
			if ((*it).first.find(points[path[6]]))
			{
				car4 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[6]][path[7]]);
			}
		}

		std::vector<DistPriceable> v;
		v.push_back(car1);
		v.push_back(car2);
		v.push_back(car3);
		v.push_back(car4);
		v.push_back(train1);
		v.push_back(train2);
		v.push_back(plane1);
		Track track = Track(v, volume);

		return track;
	}
};

class Order
{
	double cost;
	int volume;
	std::string startPoint;
	std::string finishPoint;
	enum::Type type;
	Track track;

	//Паттерн СТРАТЕГИЯ - встраивание
	OrderContext context;
	BestGenStrategy_1 bgs1;
	BestGenStrategy_2 bgs2;
	BestGenStrategy_3 bgs3;
	BestGenStrategy_4 bgs4;
public:
	Order();
	Order(Type, std::string, std::string, int);
	~Order();
	int decr(std::string);
	int** matrixUpd(Type);
	int* optim(int**, int, int);
	Track best(std::string, std::string, Type, int);
};

Train::Train()
{
	this->price = 200;
	this->speed = 100;
	this->volume = 500;
	this->distance = 0;
}
Train::Train(std::tuple<int, int, double> tuple, int dist)
{
	this->price = std::get<0>(tuple);
	this->speed = std::get<1>(tuple);
	this->volume = std::get<2>(tuple);
	this->distance = dist;
}
Train::~Train()
{

}

Car::Car()
{
	this->price = 100;
	this->speed = 60;
	this->volume = 50;
	this->distance = 0;
}
Car::Car(std::tuple<int, int, double> tuple, int dist)
{
	this->price = std::get<0>(tuple);
	this->speed = std::get<1>(tuple);
	this->volume = std::get<2>(tuple);
	this->distance = dist;
}
Car::~Car()
{

}

Plane::Plane()
{
	this->price = 500;
	this->speed = 300;
	this->volume = 100;
	this->distance = 0;
}
Plane::Plane(std::tuple<int, int, double> tuple, int dist)
{
	this->price = std::get<0>(tuple);
	this->speed = std::get<1>(tuple);
	this->volume = std::get<2>(tuple);
	this->distance = dist;
}
Plane::~Plane()
{

}

Track::Track()
{
	this->cost = 0;
	this->time = 0;
	this->volume = 0;
}
Track::~Track()
{

}
Track::Track(DistPriceable& objects, int volume) {
	cost += objects.sumCost(volume, objects.getDistance());
	time += objects.sumTime(objects.getDistance());
}
Track::Track(std::vector<DistPriceable>& objects, int volume) {
	for (DistPriceable& o : objects) {
		cost += o.sumCost(volume, o.getDistance());
		time += o.sumTime(o.getDistance());
	}
}

double Track::getCost()
{
	return this->cost;
}

Order::Order()
{
	this->cost = 0;
	this->volume = 0;
	this->startPoint = "";
	this->finishPoint = "";
	this->track = Track();
	this->type = Type::Economy;
}
Order::Order(Type deliv, std::string startP, std::string finishP, int volume)
{
	this->startPoint = startP;
	this->finishPoint = finishP;
	type = deliv;
	this->track = best(startP, finishP, deliv, volume);
	this->cost = track.getCost();
	this->volume = volume;
}
Order::~Order()
{

}

Track Order::best(std::string startP, std::string finishP, Type deliv, int volume)
{
	int start = decr(startP);
	int finish = decr(finishP);
	int** mat = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
		mat[i] = new int[SIZE];
	mat = matrixUpd(deliv);
	int* path = new int[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		path[i] = -1;
	}
	path = optim(mat, start, finish);
	int count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (path[i] != -1)
		{
			count++;
		}
		else
		{
			break;
		}
	}

	//Паттерн СТРАТЕГИЯ - встраивание
	switch (count)
	{
	case 1:
	{
		context.setStrategy(&bgs1);
		return context.useStrategy(path, volume);
	}
	case 3:
	{
		context.setStrategy(&bgs2);
		return context.useStrategy(path, volume);
	}
	case 5:
	{
		context.setStrategy(&bgs3);
		return context.useStrategy(path, volume);
	}
	case 7:
	{
		context.setStrategy(&bgs4);
		return context.useStrategy(path, volume);
	}
	}
}
int** Order::matrixUpd(Type type)
{
	int** matrix = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		matrix[i] = new int[SIZE];
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = matrixDist[i][j];
		}
	}
	switch (type)
	{
	case Economy:
		for (int i = 0; i < SIZE; i++)
		{
			if (points[i].find("TS"))
				for (int j = 0; j < SIZE; j++)
					matrix[i][j] = 99999;
		}
	case Standart:
		for (int i = 0; i < SIZE; i++)
		{
			if (points[i].find("AP"))
				for (int j = 0; j < SIZE; j++)
					matrix[i][j] = 99999;
		}
	case Turbo:
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
				if (matrix[i][j] == 0)
					matrix[i][j] = 99999;
		}
	}
	return matrix;
}
int* Order::optim(int** arr, int beginPoint, int endPoint)
{
	int* d = new int[SIZE];
	int* v = new int[SIZE];
	int temp, minindex, min;
	int begin_index = beginPoint;

	for (int i = 0; i < SIZE; i++)
	{
		d[i] = 99999;
		v[i] = 1;
	}
	d[begin_index] = 0;

	do {
		minindex = 99999;
		min = 99999;
		for (int i = 0; i < SIZE; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != 99999)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (arr[minindex][i] > 0)
				{
					temp = min + arr[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 99999);

	int* ver = new int[SIZE];
	int end = endPoint;
	ver[0] = end;
	int k = 1;
	int weight = d[end];

	while (end != begin_index)
	{
		for (int i = 0; i < SIZE; i++)
			if (arr[end][i] != 0)
			{
				int temp = weight - arr[end][i];
				if (temp == d[i])
				{
					weight = temp;
					end = i;
					ver[k] = i + 1;
					k++;
				}
			}
	}
	for (int i = 0; i < k / 2; i++)
		std::swap(ver[i], ver[k - 1 - i]);
	delete[] d, v;
	return ver;
}
int Order::decr(std::string str)
{
	for (auto it = towns.begin(); it != towns.end(); it++)
	{
		if (str._Equal((*it).first))
			return (*it).second;
	}
	return -1;
}

//Паттерн ЗАМЕСТИТЕЛЬ - реализация
class OrderProxy {
private:
	Order* order = nullptr;
public:
	bool createOrder();
	bool createOrder(Type, std::string, std::string, int);
	int decr(std::string);
	int** matrixUpd(Type);
	int* optim(int**, int, int);
	Track best(std::string, std::string, Type, int);
};

bool OrderProxy::createOrder() {
	if (order != nullptr) {
		order = new Order();
		return true;
	}
	return false;
}
bool OrderProxy::createOrder(Type deliv, std::string startP, std::string finishP, int volume) {
	if (order != nullptr) {
		order = new Order(deliv, startP, finishP, volume);
		return true;
	}
	return false;
}
int OrderProxy::decr(std::string str) {
	if (order != nullptr) {
		return order->decr(str);
	}
	return NULL;
}
int** OrderProxy::matrixUpd(Type type) {
	if (order != nullptr) {
		return order->matrixUpd(type);
	}
	return nullptr;
}
int* OrderProxy::optim(int** arr, int beginPoint, int endPoint) {
	if (order != nullptr) {
		return order->optim(arr, beginPoint, endPoint);
	}
	return nullptr;
}
Track OrderProxy::best(std::string startP, std::string finishP, Type deliv, int volume) {
	if (order != nullptr) {
		return order->best(startP, finishP, deliv, volume);
	}
	return Track();
}