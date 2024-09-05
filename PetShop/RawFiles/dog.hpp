//.hpp file definition for dog subclass
#ifndef dog_hpp
#define dog_hpp

#include <string>
#include <iostream>
//Includes pet.hpp file to inherit superclass
#include "pet.hpp"

using namespace std;

//dog subclass definition
class dog : public pet
{
public:
	dog(string name, int weight);
	virtual float getLicensingFee();
private:
	//Static float member that represents the monthly fee rate for all dog objects
	static float monthlyRate;
};


//Static member definition for the dog class
float dog::monthlyRate = 2.0;

//dog constructor definition
dog::dog(string name, int weight) :pet(name, weight)
{
}

//Function definition for calculating the monthly fee of a dog object
float dog::getLicensingFee()
{
	return weight * dog::monthlyRate;
}

#endif