//AircraftParse.cpp : Defines the exported functions for the DLL application.
//

#pragma once

#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include "FSXRichPresence.h"
#include "AircraftParse.h"

using namespace std;

AircraftParse::AircraftParse() {
	aircraftMap.insert(make_pair(string("b739"), string("b737")));
	aircraftMap.insert(make_pair(string("b738"), string("b737")));
	aircraftMap.insert(make_pair(string("b736"), string("b737")));
	aircraftMap.insert(make_pair(string("a321"), string("a320")));
	aircraftMap.insert(make_pair(string("a319"), string("a320")));
	aircraftMap.insert(make_pair(string("a318"), string("a320")));
	aircraftMap.insert(make_pair(string("a318cfm"), string("a320")));
	aircraftMap.insert(make_pair(string("a319cfm"), string("a320")));
	aircraftMap.insert(make_pair(string("a318iae"), string("a320")));
	aircraftMap.insert(make_pair(string("a319iae"), string("a320")));
	aircraftMap.insert(make_pair(string("a320cfm"), string("a320")));
	aircraftMap.insert(make_pair(string("a321cfm"), string("a320")));
	aircraftMap.insert(make_pair(string("a320iae"), string("a320")));
	aircraftMap.insert(make_pair(string("a321iae"), string("a320")));
	aircraftMap.insert(make_pair(string("b77w"), string("b777")));
	aircraftMap.insert(make_pair(string("b77l"), string("b777")));
};

string AircraftParse::parsePlane(string buffer) {
	string temp = buffer;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

	it = aircraftMap.find(temp);
	
	if(it != aircraftMap.end()) {
		return aircraftMap.find(temp)->second;
	}
	else {
		return temp;
	}
};
