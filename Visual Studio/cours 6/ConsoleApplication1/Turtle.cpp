#include "Turtle.hpp"

 Turtle::Turtle() {

	CircleShape* turtleHead = new CircleShape(20);
	turtleHead->setFillColor(sf::Color::Red);
	turtleHead->setOrigin(20, 20);
	head = turtleHead;

	CircleShape* turtleBody = new CircleShape(40);
	turtleBody->setOrigin(40, 40);
	turtleBody->setTexture(&textureTurtle);
	turtleBody->setFillColor(Color::Green);
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
	Vector2f pawPosOffset = Vector2f(radius - 10, -radius + 10);
	Vector2f pawPosOffset2 = Vector2f((radius - 10), radius - 10);
	for (size_t i = 0; i < 2; i++) {
		pawPosOffset = -pawPosOffset;
		paws[i]->setPosition(pawPosOffset);
	}

	for (size_t i = 2; i < 4; i++) {
		pawPosOffset2 = -pawPosOffset2;
		paws[i]->setPosition(pawPosOffset2);
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
	turtleDrawing();
	drawTexture.display();
	cmds = applyCmdInter(cmds, dt);
}

void Turtle::createTextureInWindow(float width, float height)
{
	drawTexture.create(width, height);
}

void Turtle::turtleDrawing()
{
	if (isDrawing) {
		CircleShape brush(15);
		brush.setFillColor(color);
		brush.setOrigin(15,15);

		brush.setPosition(Vector2f(0, radius));
		drawTexture.draw(brush,trs);

	}
}

void Turtle::translate(float value)
{
	Command* move = new Command (Advance, value);
	appendCmd(move);
}

void Turtle::rotate(float value)
{
	Command* rot = new Command(Turn, value);
	appendCmd(rot);
}



Color Turtle::changeColor()
{
	if (color == Color::Black)
		return Color::Magenta;
	if (color == Color::Magenta)
		return Color::Green;
	if (color == Color::Green)
		return Color::White;
	if (color == Color::White)
		return Color::Yellow;
	if (color == Color::Yellow)
		return Color::Black;
}

Command * Turtle::applyCmdInter(Command * cmd, double dt)
{

	if (cmd == nullptr)                   
		return nullptr;
	dt = 1.0f / 60.0f;
	float time = 2.0f;
	float ratio = cmd->currentValue / cmd->originalValue;

	if (cmd->originalValue > 0)      
	{
		cmd->currentValue -= dt * cmd->originalValue;
		if (cmd->currentValue <= 0)
			return cmd->popFirst();
	}
	else                                  
	{
		cmd->currentValue += dt * -cmd->originalValue;
		if (cmd->currentValue >= 0)
			return cmd->popFirst();

	}
	switch (cmd->type) {
	case Advance:
		trs.translate(0, (cmd->originalValue * dt));

		break;
	case Turn:
		trs.rotate((cmd->originalValue * dt));


		break;

	default:
		break;
	}
	return cmds;



}

void Turtle::appendCmd(Command* cmd)
{
	if (cmds)
		cmds->append(cmd);
	else
		cmds = cmd;


}

Command* Turtle::applyCmd(Command* cmd)
{
	switch (cmd->type) {
	case Advance:
		trs.translate(0,cmd->originalValue);

		break;
	case Turn:
		trs.rotate(cmd->originalValue);

		break;

	default:
		break;
	}
	return nullptr;
}

/*Command* Command::clone()
{
	return nullptr;
}*/
