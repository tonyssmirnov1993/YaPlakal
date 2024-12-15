#pragma once
#include<string_view>
#include <deque>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "geo.h"

struct Stop {
	std::string name_;
	double latitude_=0.0;
	double longitude_=0.0;
};

struct Bus {
	
	std::string name_;
	std::vector<Stop*>bus_;
};


class TransportCatalogue {
public:
	 Stop* GetStop(std::string_view stop);
	 Bus* GetBus(std::string_view bus);
	
	void AddStop(std::string_view name, const Coordinates coordinate/*Stop& stop*/);
	void AddRoute(std::string_view bus_name, std::vector<std::string_view> stops);
	std::unordered_set<Stop*> get_uniq_stops(Bus* bus);
private:
	
	std::deque<Stop> stops_;
	std::deque<Bus> buses_;
	std::unordered_map<std::string_view, Stop*> stopname_to_stops_;
	std::unordered_map<std::string_view, Bus*> busname_to_bus_;

	// Реализуйте класс самостоятельно
};