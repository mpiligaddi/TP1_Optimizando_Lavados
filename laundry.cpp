#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>

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
    }
    else {
    	firstGarment->second.setIncompatibleGarment(secondId);
    }
}

/*
Pre: -
Pos: Devuelve true si se cumple la condicion de comparacion o false si no
*/

static bool cmp(std::pair<int, Garment>& a, std::pair<int, Garment>& b) {
    return a.second.getWashingTime() < b.second.getWashingTime();
}

/*
Pre: -
Pos: Se ordena un mapa segun sus valores agregandolo a un vector de pares. 
*/

std::vector<std::pair<int, Garment>> Laundry::sorting(std::map<int, Garment>& M) {
    std::vector<std::pair<int, Garment> > A;
    
    for (auto& it : M) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmp);

    return A;
}

/*
Pre: -
Pos: Se ordena el vector de id Garments para que se tengan los ids de las prendas con mayor tiempo de 
lavado primeras. 
*/

void Laundry::sortIdGarments() {
	std::vector<std::pair<int, Garment>> vector = sorting(garments);
    for(int i = vector.size() - 1; i >= 0; i--) {
    	idGarments.push_back(vector.at(i).first);
    }
}

/*
Pre: -
Pos: Se setea un par de prendas como incompatibles
*/

void Laundry::setIncompatibleGarments(int firstIdGarment, int secondIdGarment) {
	setIncompatiblePair(firstIdGarment, secondIdGarment);
	setIncompatiblePair(secondIdGarment, firstIdGarment);
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
	bool garmentAdded = false;
	for(int i = 0; i < idGarments.size(); i++) {
		Garment garment = garments.at(idGarments.at(i));
		if(groupOfGarments.empty()) {
			std::vector<Garment> garments;
			garments.push_back(garment);
			groupOfGarments.insert({washingShift,garments});
			washingShift++;
		}
		else {
			garmentAdded = iterateByGroups(garment);
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
Pos: Se recorren los grupos de prendas y en caso de que una prenda sea compatible con todas las prendas
de un grupo, se agrega a ese grupo y devuelve true en caso de ser agregada y false si no.
*/

int Laundry::iterateByGroups(Garment garment) {
	bool incompatible = false;
	bool garmentAdded = false;
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
	return garmentAdded;	
}
/*
Pre: -
Pos: Se muestra por un txt el id de la prenda junto con su grupo asignado.
*/

void Laundry::showGarmentGroups() {
	sort(idGarments.begin(), idGarments.end()); 
	std::ofstream outfile ("segunda_solucion.txt");
	int washingTotalTime = 0;
	int size = garments.size();
	for(int i = 0; i < size; i++) {
		int id = garments.at(idGarments.at(i)).getIdNumber();
		int washingShift = garments.at(idGarments.at(i)).getWashingShift();
		outfile << id << " " << washingShift << std::endl;
	}
	outfile.close();
}

Laundry::~Laundry() {
}
