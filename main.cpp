/*
Andrew Simon
2/20/2024
AERSP 424 Homework 1
*/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Airplanes.h"




std::vector<double>weightmaker(int passengers) { //Creates a vector since we don't know how many front/back passengers exist
	std::vector<double> weightVec; //optimization maybe? works in MATLAB
	weightVec.resize(passengers);
	for (int i = 0; i < passengers; i++) { //iterates through the vector to its length
		std::cout << "Weight of passenger " + std::to_string(i + 1) + ": (lb) ";
		std::cin >> weightVec.at(i);
	}
	return weightVec;
}


double isSafe(double planeWeight, double planeMoment, double CG, float fuelDensity, double fuelMoment) {
	double newFuel = 0;
	double newCG;
	double newWeight;
	std::cout << CG << std::endl;
	std::cout << planeWeight << std::endl;
	std::cout << planeMoment << std::endl;
	/*
	if (planeWeight > 2950.0) { //simple check to see if the plane is above max weight
		newFuel = (2950.0 - planeWeight) / fuelDensity;
		newWeight = 2950.0;
	}
	*/
	if (CG < 82.1) {
		newFuel = (planeMoment - (82.1 * planeWeight)) / (fuelDensity * (82.1 - fuelMoment));
		newWeight = planeWeight + (newFuel * fuelDensity);
		std::cout << "The new weight is " + std::to_string(newWeight) + " lbs." << std::endl;
		if (newWeight > 2950) {
			std::cout << "There is no value of fuel for which the plane's center of gravity is within tolerances." << std::endl;
			newFuel = 0;
		}
	}
	else if (CG > 84.7) {
		newFuel = (planeMoment - (84.7 * planeWeight)) / (fuelDensity * (84.7 - fuelMoment)); //solves for the new amount of fuel to move the CG back to tolerances
		newWeight = planeWeight + (newFuel * fuelDensity);
		std::cout << "The new weight is " + std::to_string(newWeight) + " lbs." << std::endl;
		if (newWeight > 2950) {
			std::cout << "There is no value of fuel for which the plane's center of gravity is within tolerances." << std::endl; 
			//Handles edge cases where the amount of fuel needed exceeds max allowed weight
			newFuel = 0; //gives up and assumes this is not solvable
		}
	}
	std::cout << std::fixed << std::setprecision(1) << std::to_string(newFuel) + " gallons of fuel were added.";
	return newFuel;
}



int main() {
	//Question 1:
	
	float emptyPlaneWeight; //floats are used since decimal weight is useful but we don't need 15 digits of precision for any of these
	float emptyPlaneMoment;
	int frontSeaters; //cant have fractions of people
	float frontSeatMoment;
	std::vector<double> frontSeatWeight;
	int rearSeaters;  //cant have fractions of people
	float rearSeatMoment;
	std::vector<double> rearSeatWeight;
	float fuel;
	float fuelGallonMass;
	float fuelMoment;
	float baggageWeight;
	float baggageMoment;
	double aircraftWeight; //doubles for extra precision
	double aircraftMoment;
	double CGLocation;
	std::cout << "What is the weight of the empty plane? (lb) "; //All of these just output a question and then store the response inside their respective variable
	std::cin >> emptyPlaneWeight;
	std::cout << "What is the moment of the empty plane? (lb*in) ";
	std::cin >> emptyPlaneMoment;
	std::cout << "How many front seat occupants? ";
	std::cin >> frontSeaters;
	frontSeatWeight = weightmaker(frontSeaters); //calls function that returns a vector
	std::cout << "What is the front seat moment arm? (lb*in) ";
	std::cin >> frontSeatMoment;
	std::cout << "How many rear seat occupants? ";
	std::cin >> rearSeaters;
	rearSeatWeight = weightmaker(rearSeaters);
	std::cout << "What is the rear seat moment arm? ";
	std::cin >> rearSeatMoment;
	std::cout << "How many gallons of fuel? ";
	std::cin >> fuel;
	std::cout << "How much does each gallon of fuel weight? ";
	std::cin >> fuelGallonMass;
	std::cout << "What is the fuel tank moment arm? ";
	std::cin >> fuelMoment;
	std::cout << "What is the weight of the baggage? (lb) ";
	std::cin >> baggageWeight;
	std::cout << "What is the baggage moment arm? (lb*in) ";
	std::cin >> baggageMoment;
	aircraftWeight = emptyPlaneWeight + (fuel * fuelGallonMass) + baggageWeight; //Sums everything not passenger dependent
	aircraftMoment = emptyPlaneMoment + fuelMoment * fuel * fuelGallonMass + baggageMoment * baggageWeight; //Finds the moment of everything not passenger dependent
	for (int i = 0; i < frontSeatWeight.size(); i++) { // extracts each value from the vector and multiplies it to obtain the weight and moment it provides
		aircraftWeight = aircraftWeight + frontSeatWeight.at(i);
		aircraftMoment = aircraftMoment + (frontSeatWeight.at(i)*frontSeatMoment);
	}
	for (int i = 0; i < rearSeatWeight.size(); i++) {
		aircraftMoment = aircraftMoment + (rearSeatWeight.at(i) * rearSeatMoment);
		aircraftWeight = aircraftWeight + rearSeatWeight.at(i);
	}
	CGLocation = aircraftMoment / aircraftWeight; //Finds the current CG Location
	fuel = fuel + isSafe(aircraftWeight, aircraftMoment, CGLocation, fuelGallonMass, fuelMoment); //Finds the new fuel value by calling a function to calculate.
	

	//Question 5:
	std::cout << std::endl << "Question 5 starts here:" << std::endl << std::endl;
	Plane Plane1("SCE", "PHL");
	Plane1.setVel(0.125); //450 MPH in mi/sec
	for (int i = 0; i < 1000; i++) { //iterates for 1000 iterations
		Plane1.operate(50); //dt = 50
		std::cout << "Time: " + std::to_string(i * 50) + ", Position: " + std::to_string(Plane1.getPos()) << std::endl;
	}
	Plane1.~Plane(); //gets rid of the plane

	//Question 7:
	std::cout << std::endl << "Question 7 starts here:" << std::endl << std::endl;

	Plane Plane2("SCE", "PHL"); //Creates plane object
	Pilot Pilot1("A", &Plane2); //Creates pilot 1, in control of plane2
	Pilot Pilot2("B", 0); //creates pilot 2, not in control so ptr is given to 0
	Plane2.setVel(0.125); //450 MPH in mi/sec
	bool pilot1command = true; //keeps track of which pilot is in charge
	std::cout << "Pilot " + Pilot1.getName() << " is in command of plane " << Pilot1.myPlane << std::endl;
	std::cout << "Pilot " + Pilot2.getName() << " is in command of plane " << Pilot2.myPlane << std::endl;
	for (int i = 0; i < 1000; i++) {
		Plane2.operate(50); 
		if (Plane2.getat_SCE() == true) {
			std::cout << "The plane " << &Plane2 << " is at SCE." << std::endl;
			if (pilot1command == true) { //uses boolean to correctly swap the pointer with plane2's memory address in it.
				Pilot2.myPlane = Pilot1.myPlane;
				Pilot1.myPlane = 0;
				pilot1command = false;
			}
			else {
				Pilot1.myPlane = Pilot2.myPlane;
				Pilot2.myPlane = 0;
				pilot1command = true;
			}
			std::cout << "Pilot " + Pilot1.getName() << " is in command of plane " << Pilot1.myPlane << std::endl; //outputs the changed command status
			std::cout << "Pilot " + Pilot2.getName() << " is in command of plane " << Pilot2.myPlane << std::endl;

		}
	}
	Pilot1.~Pilot(); //gets rid of the pilots and plane once the algorithm is complete
	Pilot2.~Pilot();
	Plane2.~Plane();


	//Question 8:
	//The algorithm is identical to before, except that it uses a different class which wants a modern pointer
	std::cout << std::endl << "Question 8 starts here:" << std::endl << std::endl;


	std::shared_ptr<Plane> Plane3 = std::make_shared<Plane>("SCE", "PHL");
	std::shared_ptr<Plane> Temp(nullptr); //Temporary pointer now required for the swap to work.
	modernPilot modernPilot1("C", Plane3);
	modernPilot modernPilot2("D", 0); 
	(*Plane3).setVel(0.125); //450 MPH in mi/sec
	bool modernPilot1command = true;
	std::cout << "Pilot " + modernPilot1.getName() << " is in command of plane " << modernPilot1.myPlane << std::endl;
	std::cout << "Pilot " + modernPilot2.getName() << " is in command of plane " << modernPilot2.myPlane << std::endl;
	for (int i = 0; i < 1000; i++) {
		(*Plane3).operate(50);
		if ((*Plane3).getat_SCE() == true) { //I know we aren't supposed to use * but i NEED it to be able to even use the object I just made
			std::cout << "The plane " << Plane3 << " is at SCE." << std::endl;
			if (pilot1command == true) {
				Temp = modernPilot2.myPlane;
				modernPilot2.myPlane = modernPilot1.myPlane;
				modernPilot1.myPlane = Temp;
				modernPilot1command = false;
			}
			else {
				Temp = modernPilot1.myPlane;
				modernPilot1.myPlane = modernPilot2.myPlane;
				modernPilot2.myPlane = Temp;
				modernPilot1command = true; 
			}
			std::cout << "Pilot " + modernPilot1.getName() << " is in command of plane " << modernPilot1.myPlane << std::endl;
			std::cout << "Pilot " + modernPilot2.getName() << " is in command of plane " << modernPilot2.myPlane << std::endl;

		}
	}
	modernPilot1.~modernPilot();
	modernPilot2.~modernPilot();
	(*Plane3).~Plane();



	return 0;
}



