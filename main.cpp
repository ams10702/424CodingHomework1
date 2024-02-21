/*
Andrew Simon
2/20/2024
AERSP 424 Homework 1
Question 1
*/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>



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
	if (planeWeight > 2950.0) { //simple check to see if the plane is above max weight
		newFuel = (2950.0 - planeWeight) / fuelDensity;
		newWeight = 2950.0;
	}
	if (CG > 82.1) {
		newFuel = (planeMoment - (82.1 * planeWeight)) / (fuelDensity * (82.1 - fuelMoment));
		newWeight = planeWeight + (newFuel * fuelDensity);
		std::cout << "The new weight is " + std::to_string(newWeight) + " lbs." << std::endl;
		if (newWeight > 2950) {
			std::cout << "There is no value of fuel for which the plane's center of gravity is within tolerances." << std::endl;
			newFuel = 0;
		}
	}
	else if (CG < -84.7) {
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
	std::cout << "What is the weight of the empty plane? (lb) ";
	std::cin >> emptyPlaneWeight;
	std::cout << "What is the moment of the empty plane? (lb*in) ";
	std::cin >> emptyPlaneMoment;
	std::cout << "How many front seat occupants? ";
	std::cin >> frontSeaters;
	frontSeatWeight = weightmaker(frontSeaters); //calls function that returns a vector
	std::cout << "What is the rear seat moment arm? (lb*in) ";
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
	aircraftWeight = emptyPlaneWeight + (fuel * fuelGallonMass) + baggageWeight;
	aircraftMoment = emptyPlaneMoment * emptyPlaneWeight + fuelMoment * fuel * fuelGallonMass + baggageMoment * baggageWeight;
	for (int i = 0; i < frontSeatWeight.size(); i++) { // extracts each value from the vector and multiplies it to obtain the weight and moment
		aircraftWeight = aircraftWeight + frontSeatWeight.at(i);
		aircraftMoment = aircraftMoment + (frontSeatWeight.at(i)*frontSeatMoment);
	}
	for (int i = 0; i < rearSeatWeight.size(); i++) {
		aircraftMoment = aircraftMoment + (rearSeatWeight.at(i) * rearSeatMoment);
		aircraftWeight = aircraftWeight + rearSeatWeight.at(i);
	}
	CGLocation = aircraftMoment / aircraftWeight;
	fuel = fuel + isSafe(aircraftWeight, aircraftMoment, CGLocation, fuelGallonMass, fuelMoment); //saves new fuel value
	return 0;
}



