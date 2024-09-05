//.hpp file definition for cat subclass
#ifndef cat_hpp
#define cat_hpp

#include <string>
#include <iostream>
//Includes pet.hpp file to inherit superclass
#include "pet.hpp"

using namespace std;

//cat subclass definition
class cat : public pet
{
public:
	cat(string name, int weight);
	virtual float getLicensingFee();
private:
	//Static float member that represents the monthly fee rate for all cat objects
	static float monthlyRate;
};

//Static member definition for the cat class
float cat::monthlyRate = 1.5;

//cat constructor definition
cat::cat(string name, int weight) :pet(name, weight)
{
}


//Function definition for calculating the monthly fee of a cat object
float cat::getLicensingFee()
{
	return weight * cat::monthlyRate;
}

#endif