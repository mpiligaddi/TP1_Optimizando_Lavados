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
//NO ME AGARRA TODOS LOS ID. POR EJEMPLO EL 378 FALTA. PORQUE? porque son parte del segundo elemento solo *(second id)
//tenfo que poner la condicion para el segundo id tambien, ahora no es como el primer problema que se repiten si o si
//los incompatibles en ambos elementos, solo en 1 
void Laundry::setIncompatiblePair(int firstId, int secondId) {
	auto firstGarment = garments.find(firstId);
    if (firstGarment == garments.end()) {
    	printf("Estoy con el id %i\n",firstId );
        Garment garment(firstId);
        garment.setIncompatibleGarment(secondId);
        garments.insert({firstId, garment});
        idGarments.push_back(firstId); // en la entrega 2 se repite el id garment 
    }
    else {
    	firstGarment->second.setIncompatibleGarment(secondId);
    }
    /*auto secondGarment = garments.find(secondId);
    if (secondGarment == garments.end()) {
    	printf("Estoy con el id %i\n",secondId );
        Garment garment(secondId);
        garment.setIncompatibleGarment(firstId);
        garments.insert({secondId, garment});
        idGarments.push_back(firstId); // en la entrega 2 se repite el id garment 
    }
    else {
    	secondGarment->second.setIncompatibleGarment(firstId);
    }*/
}

/*
Pre: -
Pos: Se setea un par de prendas como incompatibles
*/

void Laundry::setIncompatibleGarments(int firstIdGarment, int secondIdGarment) {
	setIncompatiblePair(firstIdGarment, secondIdGarment);
	setIncompatiblePair(secondIdGarment, firstIdGarment); //por este tipo de solucion creo que no se imprimen en orden en el txt
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
	sort(idGarments.begin(), idGarments.end());
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
	std::ofstream outfile ("segunda_solucion.txt");
	int washingTotalTime = 0;
	//sort(idGarments.begin(), idGarments.end());
	int size = garments.size();
	//printf("el size de garments es %i\n", );
	//printf("el size de id garments es %i\n",size );
	for(int i = 0; i < size; i++) {
		//int id = 0;
		//int washingShift = 5;
		//NO ME AGARRA TODOS LOS ID. POR EJEMPLO EL 378 FALTA. PORQUE?
		//printf("numero i es %i\n",i );
		//printf("numero idGarments.at(i) es %i\n", idGarments.at(i) );
		int id = garments.at(idGarments.at(i)).getIdNumber(); // donde se cargan los id garments ? creo que eso falla 
		//no se cargan todos los id garments. 
		int washingShift = garments.at(idGarments.at(i)).getWashingShift();
		//printf("el id es %i\n",id );
		outfile << id << " " << washingShift << std::endl;
	}
	outfile.close();
}

void Laundry::getWashingTotalTime() {
	int washingTotalTime = 0;
	Garment garmentDefinitory;
	for(int i = 0; i < groupOfGarments.size(); i++) {
		auto group = groupOfGarments.find(i);
		for(int j = 0; j < group->second.size() - 1; j++) {
			Garment garment = group->second.at(j);
			Garment garmentAux = group->second.at(j + 1);
			if(garment.getWashingTime() >= garmentAux.getWashingTime()) {
				garmentDefinitory = garment;
			}
			else {
				garmentDefinitory = garmentAux;
			}
		}
		printf("Washing time del grupo %i es %i\n",i,garmentDefinitory.getWashingTime() );
		washingTotalTime = washingTotalTime + garmentDefinitory.getWashingTime();
	}
	printf("El tiempo total de lavado es de %i\n",washingTotalTime);
}

Laundry::~Laundry() {
}
