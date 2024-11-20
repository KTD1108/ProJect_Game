#pragma once
#include "../include/Entity.h"

class Enemy :public Entity {
private:
	int reload, fire;
	int RGBTimer;
public:
	Enemy();
	int getReload();
	void setReload(int);
	int enemyFire();
	void setFire(int);
	int getType();
	void setType(int);
	int getRGBTimer();
	void setRGBTimer(int);

};