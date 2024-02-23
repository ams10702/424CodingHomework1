#ifndef AIRPLANES_H
#define AIRPLANES_H


#include <string>
#include <array>


//Problems 3 and 4
class Plane {
	private:
		double pos, vel, distance;
		bool at_SCE;
		std::string origin, destination;
		//Problem 2 container
		std::string planeRoutes[9] = { std::to_string(160), "SCE", "PHL", std::to_string(640), "SCE", "PHL", std::to_string(220), "SCE", "PHL" };
	public:
		Plane(std::string from, std::string to) {
			origin = from;
			destination = to;
			if (((origin == "SCE") && (destination == "PHL")) || ((origin == "PHL") && (destination == "SCE"))) {
				distance = std::stoi(planeRoutes[0]);
			}
			if (((origin == "SCE") && (destination == "ORD")) || ((origin == "ORD") && (destination == "SCE"))) {
				distance = std::stoi(planeRoutes[3]);
			}
			if (((origin == "SCE") && (destination == "EWR")) || ((origin == "PHL") && (destination == "EWR"))) {
				distance = std::stoi(planeRoutes[6]);
			}
			pos = vel = at_SCE = 0;
			std::cout << "Plane created at" << this;
		}
		~Plane() {
			std::cout << "Plane destroyed";
		}
		void operate(double dt) {
			std::string swap;
			if (pos < distance) {
				pos = pos + (vel * dt);
				at_SCE = 0;
			}
			else {
				if (destination == "SCE") {
					at_SCE = 1;
				}
				swap = origin;
				origin = destination;
				destination = swap;
				pos = 0.0;
			}
			if (pos < 0) {
				pos = 0.0;
			}
		}
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
		double setVel(double newVel) {
			vel = newVel;
		}
};

//Problem 6

class Pilot {
private:
	std::string name;
public:
	Plane *myPlane;
	Pilot(std::string pilotName, Plane* planePTR){
		name = pilotName;
		myPlane = planePTR;
		std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane";
	}
	~Pilot() {
		std::cout << "Pilot " << name << " has exited the plane";
	}
	std::string getName() {
		return name;
	}
};

#endif

