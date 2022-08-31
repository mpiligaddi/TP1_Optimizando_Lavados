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

void Laundry::verIncompatibleDeXPrenda(int id) {
	prueba++;
	auto firstGarment = garments.find(id);
    if (firstGarment == garments.end()) {
        printf("no encontro la prenda\n");
        return;
    }
    else {
    	firstGarment->second.showIncompatibleGarment();
    }
}

void Laundry::setIncompatibleGarments(int firstIdGarment, int secondIdGarment) {
	setIncompatiblePair(firstIdGarment, secondIdGarment);
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

/*
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
					garments.at(idGarments.at(i)).setWashingShift(washingShift);
					garments.at(idGarments.at(j)).setWashingShift(washingShift);
					washingShift++;
				}
			}
		}
	}
}*/
/*
void Laundry::makeGarmentGroups() {
	int washingShift = 0;
	bool incompatible = false;
	for(int i = 0; i < idGarments.size(); i++) {
		Garment garment = garments.at(idGarments.at(i));
		printf("Incompatibles de %i:\n", garment.getIdNumber());
		for(int j = 0; j < idGarments.size(); j++) {
			if(j == i) continue;
			incompatible = false;
			Garment garmentAux = garments.at(idGarments.at(j));
			//printf("garmet aux %i\n", garmentAux.getIdNumber());
			printf("Numero a analizar que este en la lista de incompatibles de %i es el %i: \n", garment.getIdNumber(), garmentAux.getIdNumber());
			for(int k = 0; k < garment.getIncompatibleGarments().size(); k++) {

				printf("%i\n", garment.getIncompatibleGarments().at(k));
				//printf("numero de k %i\n", k);
				//printf("numero  %li\n", garment.getIncompatibleGarments().size() - 1);
				//ese primer if analizarlo para todo el grupo 
				if(garment.getIncompatibleGarments().at(k) == garmentAux.getIdNumber()) {
					printf("cai aca\n"); //todos caen aca
					incompatible = true;
				}
				if((incompatible == false) && (k == garment.getIncompatibleGarments().size() - 1)) {
					//printf("HOLAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
					printf("son compatibles ;)\n");
					garments.at(idGarments.at(i)).setWashingShift(washingShift);
					garments.at(idGarments.at(j)).setWashingShift(washingShift);
				}
			}
		}
		washingShift++;
	}
}*/

/*

void Laundry::makeGarmentGroups() {
	for(int i = 0; i < idGarments.size(); i++) {
		Garment garment = garments.at(idGarments.at(i));
		groupOfGarments.find(i);
		if(groupOfGarments.end()) {
			//se crea un nuevo grupo y se inserta en el map
		}
		else {
			for(int j = 0; j < groupOfGarments.second.size(); j++) {
				for(int k = 0; k < garment.getIncompatibleGarments().size(); k++) {
					for(int p = 0; p < groupOfGarments.second.at().size(); p++) {
						if(garment.getIncompatibleGarments().at(k) == groupOfGarments.second.at(i).at(p).getIdNumber()) {
							printf("cai aca\n"); //todos caen aca
							incompatible = true;
						}
						if((incompatible == false) && (k == garment.getIncompatibleGarments().size() - 1)) {
							//printf("HOLAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
							printf("son compatibles ;)\n");
							garments.at(idGarments.at(i)).setWashingShift(washingShift);
							garments.at(idGarments.at(j)).setWashingShift(washingShift);
							washingShift++;
						}
					}
				}
			}
		}
	}
}*/


void Laundry::makeGarmentGroups() {
	int washingShift = 0;
	bool incompatible = false;
	bool garmentAdded = false;
	for(int i = 0; i < idGarments.size(); i++) {
		garmentAdded = false;
		Garment garment = garments.at(idGarments.at(i)); //Garment en cuestion. Se debe agregar a algun grupo.
		//printf("El garment actual es %i\n", garment.getIdNumber());
		if(groupOfGarments.empty()) {
			// se crea un grupo directamente y se lo agrega ahi.
			//printf("Como el mapa de grupos de prendas esta vacio, creo un grupo y agrego la prenda ahi.\n");
			std::vector<Garment> garments;
			garment.setWashingTime(washingShift);
			garments.push_back(garment);
			groupOfGarments.insert({washingShift,garments});
			/*for(int l = 0 ; l < groupOfGarments.size(); l++) {
				for(int u = 0 ; u < groupOfGarments.at(l).size(); u++) {
					printf("Elementos que hay en el grupo %i: %i\n", l,groupOfGarments.at(l).at(u).getIdNumber());
				}
			}*/
			washingShift++;
		}
		else {
			for(int j = 0; j < groupOfGarments.size(); j++) {
				if(garmentAdded == true) continue;
				auto vectorOfGarments = groupOfGarments.find(j); //Se recorre grupo por grupo.
				//printf("recorro el grupo numero %i\n", vectorOfGarments->first);
				incompatible = false;
				int size = vectorOfGarments->second.size(); //recorro el vector de garments de cada grupo
				//printf("EL SIZE ES %i\n", size );
				for(int p = 0; p < size; p++) {
					if(incompatible == true) {
						continue;
					}
					Garment garmentAux = vectorOfGarments->second.at(p); //Se recorre cada garment del vector del grupo en cuestion.
					//porque solo se recorre 1?

					//printf("Numero a analizar que este en la lista de incompatibles de %i es el %i: \n", garment.getIdNumber(), garmentAux.getIdNumber());

					for(int k = 0; k < garment.getIncompatibleGarments().size(); k++) {
						if(garment.getIncompatibleGarments().at(k) == garmentAux.getIdNumber()) {
							incompatible = true;
						}
						/*if((incompatible == false) && (k == garment.getIncompatibleGarments().size() - 1)) {
							//printf("AGREGUE!\n");
							garments.at(garment.getIdNumber()).setWashingShift(j);
							//garments.at(garmentAux.getIdNumber()).setWashingShift(j); //RARO
							vectorOfGarments->second.push_back(garment);
							groupOfGarments.at(j) = vectorOfGarments->second;
							//groupOfGarments.insert({j, })
							garmentAdded = true;
						}*/
					}
					/*if(incompatible == true) {
						printf("chau!\n");
						return;
					}*/
					if((incompatible == false) && (p == size - 1)) {
						garments.at(garment.getIdNumber()).setWashingShift(j);
						//garments.at(garmentAux.getIdNumber()).setWashingShift(j); //RARO
						vectorOfGarments->second.push_back(garment);
						groupOfGarments.at(j) = vectorOfGarments->second;
						//groupOfGarments.insert({j, })
						garmentAdded = true;
					}
				}
			}
			if(garmentAdded == false) {
				//printf("creo un nuevo grupo\n");
				std::vector<Garment> vectorOfGarments;
				//garment.setWashingShift(washingShift); //esto_
				garments.at(garment.getIdNumber()).setWashingShift(washingShift);
				vectorOfGarments.push_back(garments.at(garment.getIdNumber()));
				//garments.at(0).setWashingShift(washingShift); //RARO
				groupOfGarments.insert({washingShift,vectorOfGarments});
				washingShift++;
			}			
		}
	}
	/*for(int l = 0 ; l < groupOfGarments.size(); l++) {
		for(int u = 0 ; u < groupOfGarments.at(l).size(); u++) {
			printf("Elementos que hay en el grupo %i: %i\n", l,groupOfGarments.at(l).at(u).getIdNumber());
		}
	}*/
}

//A PARTIR DEL 10 CUADNO SE EMPIEZAN A COPIAR ESTA MAL!


/*
*Se crea nuevo grupo (siempre es incompatible con alguien, no queda otra)
*Se une a un grupo existente 

Tengo un map en laundy con clave numero de grupo y valor una lista de garments (que estarian en ese grupo)
Si hay algun id de la lista de garments que no es compatible con mi garment en cuestion, paso al grupo siguiente y asi 
hasta terminar de recorrer el map. 
Si termino de recorrer el map y no me uni a ningun grupo, creo un grupo y lo agrego al map. 


Una vez que los ordeno por grupos, me fijo, si cada elemento de cada grupo tiene que:

*su tiempo de lavado es menor que el mayor elemento de otro grupo (teniendo en cuenta que debe ser "el menor de los mayores" que
cumple con las condiciones)
*es compatible con todos los elementos de ese grupo

Se va a cambiar de grupo. 


Se va a hacer hasta que no se realizen mas cambios...

------


Para cuando tenga que optimizar por tiempo de lavado teniendo en cuenta la separacion de las prendas del principio:
*Que va a ser mas optimo, tener mas grupos de lavado pero con menos tiempo c.u o menos grupos de lavado y con mas tiempo c.u?

*/

//Cada renglón tiene dos valores separados por un espacio, el primero es el número de prenda,
//el según el número de lavado asignado. ej: "1 5" Esto sería lavar la prenda "1" en el lavado "5"

void Laundry::showGarmentGroups() {
	for(int i = 0; i < garments.size(); i++) {
		int id = garments.at(idGarments.at(i)).getIdNumber();
		int washingShift = garments.at(idGarments.at(i)).getWashingShift();
		std::cout << id << " " << washingShift << std::endl;
	}
}

Laundry::~Laundry() {
}