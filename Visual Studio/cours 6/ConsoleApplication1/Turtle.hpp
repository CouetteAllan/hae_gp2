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

	Command(CmdType t, float value = 0.0) {
		type = t;
		originalValue = value;
		currentValue = value;
	}

	Command* append(Command* cmd) {
		if (!next) {
			 next = cmd;
			 return this;
		}
		else
			 next->append(cmd);

	}

	Command* popFirst() {
		Command* ru = next;
		delete this;
		return ru;
	}
};

class Turtle : public Transformable{
public:
	Transform trs;

	CircleShape* head = nullptr;
	CircleShape* body = nullptr;
	CircleShape* paw = nullptr;

	Texture textureTurtle;
	std::vector<CircleShape*> paws;
	float radius = 20.0f;
	Vector2f offset = Vector2f(radius, -radius);
	float dx = 0.0f;
	float rot = 0.0f;
	 
	bool isDrawing = false;
	RenderTexture drawTexture;

	Color color = Color::Black;



	Turtle();

	~Turtle();

	virtual void draw(RenderWindow& win);
	virtual void update(double dt);

	void createTextureInWindow(float width, float height);
	void turtleDrawing();

	void translate(float value);
	void rotate(float value);

	Color changeColor();
	Command* applyCmdInter(Command* cmd, double dt);
	void appendCmd(Command* cmd);

protected:
	Command* applyCmd(Command* cmd);
	Command* cmds = nullptr;
	bool calledOnce = false;
};