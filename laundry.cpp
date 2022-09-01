#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "laundry.h"

/*
Pre: -
Pos: Se setea el numero de prendas totales de la lavandería
*/

void Laundry::setNumberOfGarments(int numberOfGarments) {
	this->numberOfGarments = numberOfGarments;
}

/*
Pre: -
Pos: Se setea el numero de incompatibilidades totales de la lavandería
*/

void Laundry::setNumberOfIncompatibleGarments(int numberOfIncompatibleGarments) {
	this->numberOfIncompatibleGarments = numberOfIncompatibleGarments;
}

/*
Pre: -
Pos: Se setea un par de prendas como incompatibles
*/

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

/*
Pre: -
Pos: Se setea un par de prendas como incompatibles
*/

void Laundry::setIncompatibleGarments(int firstIdGarment, int secondIdGarment) {
	setIncompatiblePair(firstIdGarment, secondIdGarment);
}

/*
Pre: -
Pos: Se setea el tiempo de lavado de cada prenda
*/

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

/*
Pre: -
Pos: Se generan grupos de lavado para cada prenda, separando las incompatibles.
*/

void Laundry::makeGarmentGroups() {
	int washingShift = 0;
	bool incompatible = false;
	bool garmentAdded = false;
	for(int i = 0; i < idGarments.size(); i++) {
		garmentAdded = false;
		Garment garment = garments.at(idGarments.at(i));
		if(groupOfGarments.empty()) {
			std::vector<Garment> garments;
			garments.push_back(garment);
			groupOfGarments.insert({washingShift,garments});
			washingShift++;
		}
		else {
			for(int j = 0; j < groupOfGarments.size(); j++) {
				if(garmentAdded == true) continue;
				auto vectorOfGarments = groupOfGarments.find(j);
				incompatible = false;
				int size = vectorOfGarments->second.size();
				for(int p = 0; p < size; p++) {
					if(incompatible == true) continue;
					Garment garmentAux = vectorOfGarments->second.at(p);
					for(int k = 0; k < garment.getIncompatibleGarments().size(); k++) {
						if(garment.getIncompatibleGarments().at(k) == garmentAux.getIdNumber()) incompatible = true;
					}
					if((incompatible == false) && (p == size - 1)) {
						garments.at(garment.getIdNumber()).setWashingShift(j);
						vectorOfGarments->second.push_back(garment);
						groupOfGarments.at(j) = vectorOfGarments->second;
						garmentAdded = true;
					}
				}
			}
			if(garmentAdded == false) {
				std::vector<Garment> vectorOfGarments;
				garments.at(garment.getIdNumber()).setWashingShift(washingShift);
				vectorOfGarments.push_back(garments.at(garment.getIdNumber()));
				groupOfGarments.insert({washingShift,vectorOfGarments});
				washingShift++;
			}			
		}
	}
}

/*
Pre: -
Pos: Se muestra por pantalla el id de la prenda junto con su grupo asignado.
*/

void Laundry::showGarmentGroups() {
	std::ofstream outfile ("primer_solucion.txt");
	int washingTotalTime = 0;
	for(int i = 0; i < garments.size(); i++) {
		int id = garments.at(idGarments.at(i)).getIdNumber();
		int washingShift = garments.at(idGarments.at(i)).getWashingShift();
		outfile << id << " " << washingShift << std::endl;
	}
	outfile.close();
}

Laundry::~Laundry() {
}
