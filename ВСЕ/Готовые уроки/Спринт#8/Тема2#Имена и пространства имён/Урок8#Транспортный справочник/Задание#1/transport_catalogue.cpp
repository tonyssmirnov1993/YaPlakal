#include "transport_catalogue.h"

 Stop* TransportCatalogue::GetStop(std::string_view stop)
{
	if (stopname_to_stops_.empty()) {
		return nullptr;
	}

	if (stopname_to_stops_.find(stop) != stopname_to_stops_.end()) {
		return stopname_to_stops_.at(stop);
	}
	return nullptr;
}

  Bus* TransportCatalogue::GetBus(std::string_view bus)
{
	 if (busname_to_bus_.empty()) { return nullptr; }

	 if (busname_to_bus_.find(bus)!=busname_to_bus_.end())
	 {
		 return busname_to_bus_.at(bus);
	 }
	return nullptr;
}

void TransportCatalogue::AddStop(std::string_view name, const Coordinates coordinate/*Stop& stop*/)
{
	
	stops_.push_back({ std::string(name), coordinate.lat, coordinate.lng });
	stopname_to_stops_[stops_.back().name_] = &stops_.back();
	
	//stops_to_buses_.insert(std::move(stop));
}

void TransportCatalogue::AddRoute(std::string_view bus_name, std::vector<std::string_view>stops)
{
	
	Bus bus_buf;
	bus_buf.name_ = bus_name;

	for (auto& stop : stops) {
		if (stopname_to_stops_.find(stop) != stopname_to_stops_.end()) {
			
			
			bus_buf.bus_.push_back( stopname_to_stops_.at(stop) );			
			//buses_.push_back(bus_buf);
			//busname_to_bus_[bus_buf.name_] = &bus_buf;
			//stopname_to_stops_.at(stop);
			//buses_.push_back({bus_name, })
		}
		else {
			//Bus bus_buf;
			stops_.push_back({ std::string(stop), 0.0, 0.0 });
			stopname_to_stops_[stops_.back().name_] = &stops_.back();
			//bus_buf.name_ = bus_name;
			bus_buf.bus_.push_back(stopname_to_stops_.at(stop));
			//buses_.push_back(bus_buf);
			
		}		
	}
			
	buses_.push_back(bus_buf);
	busname_to_bus_[buses_.back().name_] = &buses_.back();
	
}

std::unordered_set<Stop*> TransportCatalogue::get_uniq_stops(Bus* bus)
{
	std::unordered_set<Stop*> uniq_stops;
	uniq_stops.insert(bus->bus_.begin(), bus->bus_.end());
	return uniq_stops;
}