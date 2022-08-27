#ifndef __LAUNDRY_H__
#define __LAUNDRY_H__

#include <map>
#include "garment.h"

class Laundry {
	int numberOfGarments; //La lavanderia tiene un total de prendas
	int numberOfIncompatibleGarments; //La lavanderia tiene un total de prendas incompatibles
	std::map<int, Garment> garments;
	std::vector<int> idGarments;
	void setIncompatiblePair(int firstId, int secondId);
	public:
	void setNumberOfGarments(int numberOfGarments);
	void setNumberOfIncompatibleGarments(int numberOfIncompatibleGarments);
	int getNumberOfGarments();
	int getNumberOfIncompatibleGarments();
	void setIncompatibleGarments(int firstIdGarment, int secondIdGarment);
	void setWashingTime(int firstIdGarment, int washingTime);
	void makeGarmentGroups();
	void showGarmentGroups();
	~Laundry();
};

#endif /*__LAUNDRY_H__*/

