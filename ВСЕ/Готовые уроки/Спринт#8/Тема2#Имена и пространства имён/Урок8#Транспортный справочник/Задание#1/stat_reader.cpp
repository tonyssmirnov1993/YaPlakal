#include "stat_reader.h"

void ParseAndPrintStat( TransportCatalogue& transport_catalogue, std::string_view request,
    std::ostream& output) {

    auto comm = request.substr(0, request.find(' '));
    auto numm_bus = request.substr(comm.size() + 1, request.find_last_not_of(' '));
    Bus* bus = transport_catalogue.GetBus(numm_bus);
    if (bus!=nullptr)
    {
        
        double dist = 0.0;
        int iter = 0;
        while (iter!=bus->bus_.size()-1)
        {
            dist+=ComputeDistance({ bus->bus_[iter]->latitude_, bus->bus_[iter]->longitude_ },
                { bus->bus_[iter + 1]->latitude_, bus->bus_[iter + 1]->longitude_ });
            ++iter;
        }
        //посчитать растояние по мануалу от А - В, В - С, С- Д и т.д
       auto size_uniq_stops = transport_catalogue.get_uniq_stops(bus).size();
        output << "Bus " << bus->name_ << ": "<<bus->bus_.size()<<" stops on route, "
           << size_uniq_stops<<" unique stops, "<< std::setprecision(6)<<dist<<" route length"<<std::endl;
        //ComputeDistance()
        
    }
    else {
       output << "Bus "<<numm_bus<<": "<<"not found"<<std::endl;
    }   
}