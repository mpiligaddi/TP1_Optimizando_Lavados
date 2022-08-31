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

int Garment::getWashingShift() {
	return washingShift;
}

void Garment::setWashingTime(int washingTime) {
	this->washingTime = washingTime;
}

void Garment::setWashingShift(int washingShift) {
	//printf("washing shift %i\n", washingShift );
	this->washingShift = washingShift;
}

void Garment::setIncompatibleGarment(int idGarment) {
	for(int i = 0; i < incompatibleGarments.size(); i++) {
		if(incompatibleGarments.at(i) == idGarment) return;
	}
	incompatibleGarments.push_back(idGarment);
}

void Garment::showIncompatibleGarment() {
	printf("incompatibles de %i:\n", id);
	for(int i = 0; i < incompatibleGarments.size(); i++) {
		printf("%i\n", incompatibleGarments.at(i));
	}
	printf("numero de incompatibles: %li\n",incompatibleGarments.size() );
	printf("--------------------------------------\n");
}

std::vector<int> Garment::getIncompatibleGarments() {
	return incompatibleGarments;
}

Garment::~Garment() {
}