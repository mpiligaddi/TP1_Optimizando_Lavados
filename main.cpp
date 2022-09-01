#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include "laundry.h"
#include "garment.h"

#define PARAM_NUM 2
#define COMMENT 'c'
#define PROBLEM 'p'
#define INCOMPATIBLE 'e'
#define TIME 'n'

/*
Pre: Se debe tener un archivo a abrir
Pos: Se obtiene una linea de archivo si se pudo abrir bien y si la linea se leyó correctamente
*/

int get_line(std::ifstream& file, std::string& line) {
	if (!file.is_open()) {
		std::cout << "Error al abrir el archivo.\n";
		return 1;
	}

	std::getline(file,line);

	if (file.bad()) {
		std::cout << "Error al leer la linea del archivo.\n";
		return 1;
	}
	return 0;
}

int main(int argc, char const *argv[]) {
	if(argc != PARAM_NUM) {
		std::cout << "Se debe ingresar un archivo." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	std::string line;
	int reading_result = get_line(file,line);

	char operationKey;
	std::string comment;
	int numberOfGarments;
	int numberOfIncompatibleGarments;
	int firstIdGarment;
	int secondIdGarment;
	int washingTime;
	Laundry laundry;

	while (reading_result == 0) {
		if (file.eof()) break;
		std::istringstream stream(line);
		stream >> operationKey;
		
		if(operationKey == PROBLEM) {
			stream >> comment >> numberOfGarments >> numberOfIncompatibleGarments;
			laundry.setNumberOfGarments(numberOfGarments);
			laundry.setNumberOfIncompatibleGarments(numberOfIncompatibleGarments);
		}
		else if(operationKey == INCOMPATIBLE) {
			stream >> firstIdGarment >> secondIdGarment;
			laundry.setIncompatibleGarments(firstIdGarment, secondIdGarment);
		}
		else if(operationKey == TIME) {
			stream >> firstIdGarment >> washingTime;
			laundry.setWashingTime(firstIdGarment, washingTime);
		}

		reading_result = get_line(file,line);
	}

	laundry.makeGarmentGroups();
	laundry.showGarmentGroups();

	return 0;
}
