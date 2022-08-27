#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>

#include "garment.h"

Garment::Garment(int numberId): id(numberId), washingTime(0), washingShift(0) {

}

int Garment::getIdNumber() {
	return id;
}

void Garment::setWashingTime(int washingTime) {
	this->washingTime = washingTime;
}

void Garment::setWashingShift(int washingShift) {
	this->washingShift = washingShift;
}


void Garment::setIncompatibleGarment(int idGarment) {
	for(int i = 0; i < incompatibleGarments.size(); i++) {
		if(incompatibleGarments.at(i) == idGarment) return;
	}
	incompatibleGarments.push_back(idGarment);
}

std::vector<int> Garment::getIncompatibleGarments() {
	return incompatibleGarments;
}

Garment::~Garment() {
}