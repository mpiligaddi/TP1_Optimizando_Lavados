#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>

#include "garment.h"

Garment::Garment(int numberId): id(numberId), washingTime(0), washingShift(0) {
}

Garment::Garment() {
}

/*
Pre: -
Pos: Se devuelve el id de la prenda correspondiente
*/

int Garment::getIdNumber() {
	return id;
}

/*
Pre: -
Pos: Se devuelve el grupo de lavado de la prenda correspondiente
*/

int Garment::getWashingShift() {
	return washingShift;
}

/*
Pre: -
Pos: Se devuelve el tiempo de lavado de la prenda correspondiente
*/

int Garment::getWashingTime() {
	return washingTime;
}

/*
Pre: -
Pos: Se setea el tiempo de lavado de la prenda correspondiente
*/

void Garment::setWashingTime(int washingTime) {
	this->washingTime = washingTime;
}

/*
Pre: -
Pos: Se setea el grupo de lavado de la prenda correspondiente
*/

void Garment::setWashingShift(int washingShift) {
	this->washingShift = washingShift;
}

/*
Pre: -
Pos: Se setea una prenda incompatible a la prenda correspondiente
*/

void Garment::setIncompatibleGarment(int idGarment) {
	for(int i = 0; i < incompatibleGarments.size(); i++) {
		if(incompatibleGarments.at(i) == idGarment) return;
	}
	incompatibleGarments.push_back(idGarment);
}

/*
Pre: -
Pos: Se devuelve las prendas incompatibles de la prenda correspondiente
*/

std::vector<int> Garment::getIncompatibleGarments() {
	return incompatibleGarments;
}

Garment::~Garment() {
}