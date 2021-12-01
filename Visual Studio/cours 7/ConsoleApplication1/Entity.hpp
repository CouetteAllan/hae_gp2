#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <math.h>


using namespace sf;

enum EType {
	Player,
	Wall,
	Enemy,
};

class Entity {
public:

	//---------- Graphic Components ------------//
	Sprite sprite;
	bool visible;
	EType type;

	//---------- Base Coordinates -------------------//
	int cx = 0; //Numéro de la cellule en X
	int cy = 0; //Numéro de la cellule en Y
	float xr = 0.0f; //Ratio de la cellule en X allant de 0.0f à 1.0f
	float yr = 0.0f; //Ratio de la cellule en Y allant de 0.0f à 1.0f


	//-------------- Resulting Coordinates -----------------//
	float xx = 0.0f;
	float yy = 0.0f;

	Entity(EType _type = Player, float x = 640.0f, float y = 360.0f) {
		type = _type;
		xx = x;
		yy = y;
		cx = floor(xx / 16);
		cy = floor(yy / 16);
		xr = (xx - cx * 16) / 16;
		yr = (yy - cy * 16) / 16;
	}


	void setPosition(float x, float y);

	void update(double dt);


};

