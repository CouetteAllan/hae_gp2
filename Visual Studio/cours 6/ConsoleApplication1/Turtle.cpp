#include "Turtle.hpp"

inline Turtle::Turtle(CircleShape* _body, CircleShape* _head) {
	head = _head;
	body = _body;
	body->setOrigin(_body->getRadius(), _body->getRadius());
	radius = _body->getRadius();
	head->setPosition(body->getPosition() + offset);
	head->setOrigin(body->getOrigin());


}

inline Turtle::~Turtle() {
	if (head) {
		delete head;
		head = nullptr;
	}
	if (body) {
		delete body;
		body = nullptr;
	}
}

void Turtle::draw(RenderWindow& win)
{
	win.draw(*body,trs);
	win.draw(*head,trs);
}

void Turtle::update(double dt)
{
	auto pos = getPosition();
	pos.x = dx * dt;
	setPosition(pos);

}

void Turtle::changeColor()
{

}

void Turtle::appendCmd(Command* cmd)
{
	if(!cmds)
		cmds = cmd;



	appendCmd(cmds->next);
}

Command* Turtle::applyCmd(Command* cmd)
{
	if (cmd->type == Advance) {
		cmd->originalValue;
	}

	return nullptr;
}

/*Command* Command::clone()
{
	return nullptr;
}*/
