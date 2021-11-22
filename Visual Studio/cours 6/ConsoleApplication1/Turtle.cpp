#include "Turtle.hpp"

 Turtle::Turtle() {

	CircleShape* turtleHead = new CircleShape(20);
	turtleHead->setFillColor(sf::Color::Red);
	turtleHead->setOrigin(20, 20);
	head = turtleHead;

	CircleShape* turtleBody = new CircleShape(40);
	turtleBody->setFillColor(sf::Color::Green);
	turtleBody->setOrigin(40, 40);
	body = turtleBody;

	for (size_t i = 0; i < 4; i++)
	{
		CircleShape* paw = new CircleShape(12);
		paw->setFillColor(sf::Color::Yellow);
		paw->setOrigin(12, 12);
		paws.push_back(paw);
	}

	body->setOrigin(turtleBody->getRadius(), turtleBody->getRadius());
	radius = turtleBody->getRadius();
	head->setPosition(body->getPosition() + offset);
	head->setOrigin(body->getOrigin());
	Vector2f pawPosOffset = Vector2f(radius, -radius);
	for (auto p : paws) {
		p->setPosition(body->getPosition() + offset);
	}

}

 Turtle::~Turtle() {
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
	for (auto p : paws) {
		win.draw(*p, trs);
	}
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
