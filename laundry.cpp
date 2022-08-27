#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>

#include "laundry.h"

void Laundry::setNumberOfGarments(int numberOfGarments) {
	this->numberOfGarments = numberOfGarments;
}

void Laundry::setNumberOfIncompatibleGarments(int numberOfIncompatibleGarments) {
	this->numberOfIncompatibleGarments = numberOfIncompatibleGarments;
}

int Laundry::getNumberOfGarments() {
	return numberOfGarments;
}

int Laundry::getNumberOfIncompatibleGarments() {
	return numberOfIncompatibleGarments;
}

void Laundry::setIncompatiblePair(int firstId, int secondId) {
	auto firstGarment = garments.find(firstId);
    if (firstGarment == garments.end()) {
        Garment garment(firstId);
        garment.setIncompatibleGarment(secondId);
        garments.insert({firstId, garment});
        idGarments.push_back(firstId);
    }
    else {
    	firstGarment->second.setIncompatibleGarment(secondId);
    }
}

void Laundry::setIncompatibleGarments(int firstIdGarment, int secondIdGarment) {
	setIncompatiblePair(firstIdGarment, secondIdGarment);
	setIncompatiblePair(secondIdGarment, firstIdGarment);
}

void Laundry::setWashingTime(int firstIdGarment, int washingTime){
	auto firstGarment = garments.find(firstIdGarment);
    if (firstGarment == garments.end()) {
        Garment garment(firstIdGarment);
        garment.setWashingTime(washingTime);
        garments.insert({firstIdGarment, garment});
    }
    else {
    	firstGarment->second.setWashingTime(washingTime);
    }
}

//Despues, me fijo que prenda de cada grupo es la que tarda mas.

void Laundry::makeGarmentGroups() {
	int washingShift = 0;
	for(int i = 0; i < idGarments.size(); i++) {
		Garment garment = garments.at(idGarments.at(i));
		for(int j = i + 1; j < idGarments.size(); j++) {
			Garment garmentAux = garments.at(idGarments.at(j));
			for(int k = 0; k < garment.getIncompatibleGarments().size(); k++) {
				if(garment.getIncompatibleGarments().at(k) == garmentAux.getIdNumber()) {
					break;
				}
				else if((garment.getIncompatibleGarments().at(k) != garmentAux.getIdNumber()) 
					&& (k == garment.getIncompatibleGarments().size() - 1)) {
					garment.setWashingShift(washingShift);
					garmentAux.setWashingShift(washingShift);
					washingShift++;
				}
			}
		}
	}
}

//Cada renglón tiene dos valores separados por un espacio, el primero es el número de prenda,
//el según el número de lavado asignado. ej: "1 5" Esto sería lavar la prenda "1" en el lavado "5"

void Laundry::showGarmentGroups() {

}

Laundry::~Laundry() {
}