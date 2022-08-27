#ifndef __GARMENT_H__
#define __GARMENT_H__

#include <vector>

class Garment {
	int id; //Cada prenda tiene un identificador 
	int washingTime; //Tiempo de lavado de cada prenda
	std::vector<int> incompatibleGarments; //Vector para saber cuales son las prendas incompatibles de cada lavado, las mismas se identifican con el numero de id.
	int washingShift; //Turno de lavado de cada prenda
	public:
	~Garment();
};

#endif /*__GARMENT_H__*/

