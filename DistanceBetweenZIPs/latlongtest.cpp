#define _USE_MATH_DEFINES
#include "GetFunctions.h"
#include "json.hpp"
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using json = nlohmann::json;

static const wstring firstHalf = L"https://nominatim.openstreetmap.org/search?q=";
static const wstring secondHalf = L"&format=jsonv2&countrycodes=us&addressdetails=1";

void distanceBetweenCoords(float lat1, float lon1, float lat2, float lon2)
{
	auto radlat1 = M_PI * lat1 / 180;
	auto radlat2 = M_PI * lat2 / 180;
	auto theta = lon1 - lon2;
	auto radtheta = M_PI * theta / 180;
	auto dist = sin(radlat1) * sin(radlat2) + cos(radlat1) * cos(radlat2) * cos(radtheta);
	if (dist > 1)
	{
		dist = 1;
	}
	dist = acos(dist);
	dist = dist * 180 / M_PI;
	dist = dist * 60 * 1.1515;
	dist = dist * 1.609344; // convert to KM explicitly, for some reason their conversion to "M" (assuming miles) is literally this times 1000, which is not right
	wcout << "The distance between those two points is: " << dist << " kilometers." << endl;
}

float avg(float one, float two) {
	return (one + two) / 2;
}

void getLatLongFromZIP(float& lat, float& lon, wstring ZIP) {
	wstring ret = AVW::GetToString(firstHalf + ZIP + secondHalf);
	json j = json::parse(ret);
	try {
		auto elements = j.front();
		for (auto& i : elements) {
			if (i.type_name() == "array") {
				vector<float> coords[4];
				for (auto& i2 : i) {
					string thing = to_string(i2);
					thing.erase(thing.begin(), thing.begin() + 1);
					thing.erase(thing.end() - 1, thing.end());
					coords->emplace_back(stof(thing));
				}
				lat = avg(coords->at(0), coords->at(1));
				lon = avg(coords->at(2), coords->at(3));
			}
		}
	}
	catch (json::exception& e) {
		wcout << e.what() << endl;
	}
}

int main()
{
	// get both zip codes
	// get json from OSM thing
	// process into floats
	// convert
	// profit
	wstring zip1, zip2;
	wcout << "Enter first ZIP code:" << endl;
	wcin >> zip1;
	wcout << "Enter second ZIP code:" << endl;
	wcin >> zip2;

	// "CURL" stuff
	float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;
	getLatLongFromZIP(x1, y1, zip1);
	this_thread::sleep_for(2s); //necessary to not get blocked
	getLatLongFromZIP(x2, y2, zip2);
	distanceBetweenCoords(x1, y1, x2, y2);
	return 0;
}