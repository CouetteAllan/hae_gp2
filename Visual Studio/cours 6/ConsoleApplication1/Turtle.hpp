#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>

using namespace sf;

enum CmdType {
	Advance,
	Turn,
	PenDown,
	PenUp,
	Clear,
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
		else {
			 next = next->append(cmd);
			 return this;
		}

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
	float penRadius = 15.0f;
	Vector2f offset = Vector2f(radius, -radius);
	Vector2f startPosition = Vector2f(640, 360);
	float dx = 0.0f;
	float rot = 0.0f;
	 
	std::list<Command*> commandsSaved;

	bool isDrawing = false;
	bool automatik = false;
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
	void draw(bool value);
	void clear();
	
	void writeCommands(const char* fileName);
	void write(FILE* f, Command* cmd);

	Color changeColor();
	Command* applyCmdInter(Command* cmd, double dt);
	void appendCmd(Command* cmd);

	Command* cmds = nullptr;
protected:
	Command* applyCmd(Command* cmd);
	bool calledOnce = false;
};