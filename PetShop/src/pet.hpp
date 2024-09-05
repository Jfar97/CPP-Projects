//.hpp file definition for the pet class
#ifndef pet_hpp
#define pet_hpp

#include <string>
#include <iostream>

using namespace std;

//pet super class definition
class pet
{
public:
	pet(string name, int weight);
	virtual float getLicensingFee() = 0;
	string getName();
	int getWeight();
protected:
	//String member that represents the name of the pet
	string name;
	//Integer member that represents the weight of the pet
	int weight;
};


//pet constructor definition
pet::pet(string name, int weight)
{
	this->name = name;
	this->weight = weight;
}


//Function definition of getter for a pet object's name
string pet::getName()
{
	return this->name;
}


//Function definition of setter for a pet object's weight
int pet::getWeight()
{
	return this->weight;
}

#endif