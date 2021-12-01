#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>


using namespace sf;

class Entity {
public:

	//---------- Graphic Components ------------//
	Sprite sprite;
	bool visible;


	//---------- Base Coordinates -------------------//
	float cx = 0.0f; //Numéro de la cellule en X
	float cy = 0.0f; //Numéro de la cellule en Y
	float xr = 0.0f; //Ratio de la cellule en X allant de 0.0f à 1.0f
	float yr = 0.0f; //Ratio de la cellule en Y allant de 0.0f à 1.0f


	//-------------- Resulting Coordinates -----------------//
	float xx = 0.0f;
	float yy = 0.0f;

	Entity() {

	}


};

