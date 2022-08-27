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
#define TIME 'd'

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
		//definición del problema formato: p c n m "c" es un comentario, "n" es la cantidad de prendas y "m" la cantidad de incompatibilidades ej: "p edges 10 30"
		if(operationKey == PROBLEM) {
			stream >> comment >> numberOfGarments >> numberOfIncompatibleGarments;
			laundry.setNumberOfGarments(numberOfGarments);
			laundry.setNumberOfIncompatibleGarments(numberOfIncompatibleGarments);
		}
		//"e": incompatibilidad formato: e n1 n2 "n1" y "n2" son los números de prenda incompatibles entre ellas ej: "e 1 2"
		else if(operationKey == INCOMPATIBLE) {
			stream >> firstIdGarment >> secondIdGarment;
			laundry.setIncompatibleGarments(firstIdGarment, secondIdGarment);
		}
		//"n": tiempo de lavado formato: n n1 c1 "n1" es el número de prenda y "c1" el tiempo de lavado ej: "n 5 3"
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