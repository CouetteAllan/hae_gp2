#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <math.h>
#include "World.hpp"
#include <map>
#include <optional>
#include "Tool.hpp"

using namespace sf;

enum EType {
	Player,
	Wall,
	Enemy,
};

class Entity;

class State {
public:
	Entity*		e = nullptr;

	virtual void onEnter() = 0;
	virtual void onUpdate(double dt) = 0;

};


class IdleState : public State {
public:
	float timer = 1.0f;
	float timerReset = timer;

	IdleState(Entity* _e) {
		e = _e;
	}

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

class WalkState : public State {
public:
	WalkState(Entity* _e) {
		e = _e;
	}

	virtual void onEnter();
	virtual void onUpdate(double dt);

};

class RunState : public State {
public:
	RunState(Entity* _e) {
		e = _e;
	}

	virtual void onEnter();
	virtual void onUpdate(double dt);

};

class CoverState : public State {
public:
	CoverState(Entity* _e) {
		e = _e;
	}

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

class Entity {
public:


	//---------- Graphic Components ------------//
	Shape* sprite = nullptr;
	bool visible = true;
	EType type;

	//---------- Base Coordinates -------------------//
	int cx = 0; //Numéro de la cellule en X
	int cy = 0; //Numéro de la cellule en Y
	float rx = 0.0f; //Ratio de la cellule en X allant de 0.0f à 1.0f
	float ry = 0.0f; //Ratio de la cellule en Y allant de 0.0f à 1.0f

	//-------------- Movement -------------------------//
	float dx = 0.0f;
	float dy = 0.0f;
	inline static float friction = 0.827f;
	bool isGrounded = false;
	bool gravity = true;


	//-------------- Resulting Coordinates -----------------//
	double xx = 0.0f;
	double yy = 0.0f;

	const inline static int stride = 32;

	std::vector<sf::Vector2i>	curPath;
	std::optional<sf::Vector2i> target;


	int click = 0;

	State* currentState = nullptr;

	Entity( Shape* shape, float _cx, float _cy, EType _type = Player) {
		type = _type;
		cx = _cx;
		cy = _cy;
		sprite = shape;
		syncSprite();
		if (type == Player) {
			currentState = new IdleState(this);
			currentState->onEnter();
		}
	}


	void setPosition(float x, float y);

	void setState(State* state);
	void syncSprite();
	void update(double dt);
	void updatePath(double dt);
	void draw(RenderWindow &win);

	bool isColliding(int _cx, int _cy);
};

