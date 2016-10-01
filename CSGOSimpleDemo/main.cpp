#include <iostream>
#include <chrono>

#include "CSGOSimpleDemo.h"

using namespace std;
using namespace std::chrono;

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();


	CSGOSimpleDemo demo("C:/Users/Pedro Henrique/Documents/Visual Studio 2015/Projects/CSGOSimpleDemo/Debug/2.dem");
	demo.setParsePacketEntities(true);
	// demo.setParseGameEvents(false);
	std::cout << demo.getHeader() << std::endl;
	demo.parseAll();

	auto p = demo.getParticipants();

	for (uint32 i = 0; i < p.size(); i++) {
		std::cout << p[i]._playerInfo << std::endl;
	}


	//for (uint32 i = 0; i < 10000; i++) {
	//	demo.parseNextTick();
	//}

	//demo.parseNextTick();
	
//	std::cout << "Parsed-> " << std::boolalpha << demo.isDemoParsed() << std::endl;


	//auto p = demo.getParticipants();

	//for (uint32 i = 0; i < p.size(); i++) {
	//	std::string name = p[i].name;
	//	std::cout << "P: " << name << " xuid:" << p[i].xuid << std::endl;
	//}


	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(t2 - t1).count();
	cout << "Total executation time: " << duration << " seconds" << endl;
	return 0;
}