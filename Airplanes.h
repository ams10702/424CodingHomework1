#ifndef AIRPLANES_H
#define AIRPLANES_H

/*
Andrew Simon
2/20/2024
AERSP 424 Homework 1
*/


#include <string>
#include <array>
#include <memory>


//Problems 3 and 4
class Plane {
	private:
		double pos, vel, distance;
		bool at_SCE;
		std::string origin, destination;
		//Problem 2 container
		std::string planeRoutes[9] = { std::to_string(160), "SCE", "PHL", std::to_string(640), "SCE", "PHL", std::to_string(220), "SCE", "PHL" };
	public:
		Plane(std::string from, std::string to) { //Plane constructor
			origin = from;
			destination = to;
			//Pulls out the distance from the origin and destination given: using container from Q2.
			if (((origin == "SCE") && (destination == "PHL")) || ((origin == "PHL") && (destination == "SCE"))) { 
				distance = std::stoi(planeRoutes[0]); //this distance applies to both directions from each location
			}
			if (((origin == "SCE") && (destination == "ORD")) || ((origin == "ORD") && (destination == "SCE"))) {
				distance = std::stoi(planeRoutes[3]);
			}
			if (((origin == "SCE") && (destination == "EWR")) || ((origin == "PHL") && (destination == "EWR"))) {
				distance = std::stoi(planeRoutes[6]);
			}
			pos = vel = at_SCE = 0;
			std::cout << "Plane created at " << this << std::endl;
		}
		~Plane() {
			std::cout << "Plane destroyed" << std::endl; //deconstructor
		}
		void operate(double dt) {
			std::string swap;
			if (pos < distance) {
				pos = pos + (vel * dt); //dt in seconds, vel in mi/sec
				at_SCE = 0; //makes sure that at_SCE remains at zero while not at SCE
			}
			else {
				if (destination == "SCE") {
					at_SCE = 1;
				}
				swap = origin;
				origin = destination;
				destination = swap; //temp string to make swap work
				pos = 0.0;
			}
			if (pos < 0) {
				pos = 0.0; //makes sure there is no pos overflow
			}
		}
		// Get/Set functions
		double getPos() { 
			return pos;
		}
		std::string getOrigin() {
			return origin;
		}
		std::string getDestination() {
			return destination;
		}
		bool getat_SCE() {
			return at_SCE;
		}
		double getVel() {
			return vel;
		}
		void setVel(double newVel) {
			vel = newVel;
		}
};

//Problem 6

class Pilot {
private:
	std::string name;
public:
	Plane *myPlane; //Old style pointer
	Pilot(std::string pilotName, Plane* planePTR){
		name = pilotName; 
		myPlane = planePTR;
		std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane" << std::endl; //names the pilot when they are constructed
	}
	~Pilot() {
		std::cout << "Pilot " << name << " has exited the plane" << std::endl;
	}
	std::string getName() {
		return name;
	}
};

//Problem 8

class modernPilot { //Pilot using modern pointer
private:
	std::string name;
public:
	std::shared_ptr<Plane> myPlane; //modern shared pointer to avoid ownership fights
	modernPilot(std::string pilotName, std::shared_ptr<Plane> planePTR) { //constructor now wants modern pointer
		name = pilotName;
		myPlane = planePTR;
		std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane" << std::endl;
	}
	~modernPilot() {
		std::cout << "Pilot " << name << " has exited the plane" << std::endl; //non pointer related stuff identical
	}
	std::string getName() {
		return name;
	}
};

#endif

