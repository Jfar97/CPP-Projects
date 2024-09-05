#include <iostream>
#include <string>
#include <vector>
#include "pet.hpp"
#include "dog.hpp"
#include "cat.hpp"

using namespace std;

int main()
{
	//Initializing two dog and one cat objects and creating pointers to them
	dog pet1 = dog("Bob", 65);
	dog pet2 = dog("Stan", 37);
	cat pet3 = cat("Tom", 12);

	dog* pPet1 = &pet1;
	dog* pPet2 = &pet2;
	cat* pPet3 = &pet3;

	//Initialzing a vector of pet pointers and adding the three pet pointer objects to it
	vector<pet*> pvec;
	pvec.push_back(pPet1);
	pvec.push_back(pPet2);
	pvec.push_back(pPet3);

	//Float variable for the fee of all the pets on the vector
	float totalFee = 0.0;

	//Loops through all the objects on the vector, prints their name and fee, and adds the fee to the total
	for (int i = 0; i < pvec.size(); i++)
	{
		cout << pvec[i]->getName() << " " << pvec[i]->getLicensingFee() << endl;
		totalFee += pvec[i]->getLicensingFee();
	}

	//Prints the total licensing fee
	cout << "total licensing fee = " << totalFee << endl;

	return 0;
}