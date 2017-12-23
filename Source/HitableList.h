#ifndef HITABLELISTH
#define HITABLELISTH

#include "Hitable.h"

class HitableList : public Hitable {
public:
	HitableList() {}
	HitableList(Hitable **l, int n) { list = l; listSize = n; }

	virtual bool Hit(const Ray& _r, float _tMin, float _tMax, HitRecord& _record) const;

	Hitable **list;
	int listSize;
};

bool HitableList::Hit(const Ray& _r, float _tMin, float _tMax, HitRecord& _record) const {
	HitRecord tempRecord;
	bool hitAnything = false;

	double closestSoFar = _tMax;
	for (int i = 0; i < listSize; i++) {
		if (list[i]->Hit(_r, _tMin, closestSoFar, tempRecord)) {
			hitAnything = true;
			closestSoFar = tempRecord.t;
			_record = tempRecord;
		}
	}

	return hitAnything;
}

#endif