#ifndef RESPONSES_H_INCLUDED
#define RESPONSES_H_INCLUDED

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <iostream>

struct BusesForStopResponse {
	std::vector < std::string > buses;
};

std::ostream& operator << (std::ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse {
	std::string bus;

	std::vector < std::pair < std::string , std::vector < std::string > > > stops_for_buses;
};

std::ostream& operator << (std::ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse {
	std::map < std::string , std::vector < std::string > > buses_to_stops;
};

std::ostream& operator << (std::ostream &os, const AllBusesResponse &r);

#endif // RESPONSES_H_INCLUDED
