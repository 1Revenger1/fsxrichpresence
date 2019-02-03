#pragma once
#include "FSXRichPresence.h"
#include <map>
#include <string>
#include <string.h>

class FSXRICHPRESENCE_API AircraftParse {

	std::map<std::string, std::string> aircraftMap;
	std::map<std::string, std::string>::iterator it;

	public:
		std::string parsePlane(std::string);
		AircraftParse();
};