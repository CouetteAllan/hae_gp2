#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

enum CmdType {
	Advance,
	Turn
};

struct Command {
	CmdType type = Advance;
	float originalValue = 0.0f;
	float currentValue = 0.0f;
	Command* next = nullptr;

	//Command* clone();
};

class Turtle : public Transformable{
public:
	Transform trs;

	CircleShape* head = nullptr;
	CircleShape* body = nullptr;
	float radius = 20.0f;
	Vector2f offset = Vector2f(radius, -radius);
	float dx = 0.0f;
	float rot = 0.0f;

	bool isDrawing = false;

	Color color;



	Turtle(CircleShape* _body, CircleShape* _head);

	~Turtle();

	virtual void draw(RenderWindow& win);
	virtual void update(double dt);
	void changeColor();

	void appendCmd(Command* cmd);

protected:
	Command* applyCmd(Command* cmd);
	Command* cmds = nullptr;

};