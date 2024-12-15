#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    int stop_count;
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string input_operation;
    is >> input_operation;
    if(input_operation == "NEW_BUS"s){
        q.stops.clear();
        q.type = QueryType::NewBus;
        is >> q.bus;
        is >> q.stop_count;
        for (int i=0; i<q.stop_count; ++i){
            string bus_stop;
            is >> bus_stop;
            q.stops.push_back(bus_stop);
        }
    }
    else if (input_operation == "BUSES_FOR_STOP"s){
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (input_operation == "STOPS_FOR_BUS"s){
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (input_operation == "ALL_BUSES"s){
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string > Buses_For_Stop_Response;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    for (const auto& bus : r.Buses_For_Stop_Response) {
		os << bus << " ";
	}
	return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector <string> Stops_Response;
	vector< vector <string>> Bus_Response;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.Stops_Response.empty()) {
		os << "No bus";
	}
	else {
		int count = 0;
		for (const auto& i : r.Stops_Response) {
			os << "Stop " << i << ": ";
			for (const auto& j : r.Bus_Response[count]) {
				os << j << " ";
			}
			if ( count + 1 != r.Stops_Response.size())
				os << endl;
			++count;
		}
	}
	return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> All_Buses_Response;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.All_Buses_Response.empty()) {
		os << "No buses";
	}
	else {
		int count = 0;
		for (const auto& bus_item : r.All_Buses_Response) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}

			if (count + 1 != r.All_Buses_Response.size())
			os << endl;
			++count;
		}
	}
	return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        buses_to_stops[bus] = stops;
		for (const auto& stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse list;
		if (stops_to_buses.count(stop) == 0) {
			list.Buses_For_Stop_Response.push_back("No stop");
		}
		else {
			 list.Buses_For_Stop_Response = stops_to_buses.at(stop);
		}
		return list;
	}

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse list;
		if (buses_to_stops.count(bus) != 0){
			for (const string& stop : buses_to_stops.at(bus)) {
				list.Stops_Response.push_back(stop);
				if (stops_to_buses.at(stop).size() == 1) {
					list.Bus_Response.push_back({ "no interchange" });
				}
				else {
					vector <string> list2;
					for (const string& other_bus : stops_to_buses.at(stop)) {
						if (bus != other_bus) {
							list2.push_back(other_bus);
						}
					}
					list.Bus_Response.push_back(list2);
				}
			}
		}
		return list;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse list;
		if (!buses_to_stops.empty()) {
			for (const auto& bus_item : buses_to_stops) {
				for (const string& stop : bus_item.second) {
					list.All_Buses_Response[bus_item.first].push_back(stop);
				}
			}
		}
		return list;
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}