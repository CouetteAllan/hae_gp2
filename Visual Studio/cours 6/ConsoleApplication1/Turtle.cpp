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
	if(automatik)
		cmds = applyCmdInter(cmds, dt);

	else {
		while (cmds) {
			applyCmd(cmds);
			cmds = cmds->popFirst();
		}
	}
}

void Turtle::createTextureInWindow(float width, float height)
{
	drawTexture.create(width, height);
}

void Turtle::turtleDrawing()
{
	if (isDrawing) {
		CircleShape brush(penRadius);
		brush.setFillColor(color);
		brush.setOrigin(penRadius,penRadius);

		drawTexture.draw(brush,trs);

	}
}

void Turtle::translate(float value)
{
	Command* move = new Command (Advance, value);
	appendCmd(move);
	if(!automatik)
		commandsSaved.push_back(move);
}

void Turtle::rotate(float value)
{
	Command* rot = new Command(Turn, value);
	appendCmd(rot);
	if(!automatik)
		commandsSaved.push_back(rot);

}

void Turtle::draw(bool value)
{
	if (value) {
		Command* draw = new Command(PenDown,0.0f);
		appendCmd(draw);
		if(!automatik)
			commandsSaved.push_back(draw);

	}
	else {
		Command* noDraw = new Command(PenUp);
		appendCmd(noDraw);
		if(!automatik)
			commandsSaved.push_back(noDraw);

	}
}

void Turtle::clear()
{
	isDrawing = false;
	trs = Transform::Identity;
	trs.translate(startPosition);
	drawTexture.clear(Color::Color(0,0,0,0));
	while (cmds) {
		cmds = cmds->popFirst();
	}
}

void Turtle::writeCommands(const char* fileName)
{
	FILE* f = nullptr;
	fopen_s(&f, fileName, "wb");
	if (f) {
		write(f, cmds);
		fflush(f);
		fclose(f);
	}

}

void Turtle::write(FILE* f, Command* cmd)
{
	switch (cmd->type) {
	case Clear:
		fprintf(f, "PenDown");
		break;
	case Advance:
		fprintf(f, "Advance %0.0f\n", cmd->originalValue);
		break;
	case Turn: 
		fprintf(f, "Turn %0.0f\n", cmd->originalValue);
		break;
	case PenDown:
		fprintf(f, "PenDown\n");

		break;
	case PenUp:
		fprintf(f, "PenUp\n");
		break;
	}
	if (cmd->next)
		write(f, cmd->next);
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
	dt = 1.0f / 60.0f;
	if (cmd == nullptr)                   
		return nullptr;
	float time = 2.0f;

	if (cmd->originalValue > 0)      
	{
		cmd->currentValue -= dt * cmd->originalValue;
		if (cmd->currentValue <= 0)
			return cmd->popFirst();
	}
	else if (cmd->originalValue < 0)
	{
		cmd->currentValue += dt * -cmd->originalValue;
		if (cmd->currentValue >= 0)
			return cmd->popFirst();

	}
	switch (cmd->type) {
	case Advance:
		trs.translate(0, -(cmd->originalValue * dt)* 2 );
		break;
	case Turn:
		trs.rotate((cmd->originalValue * dt) );
		break;

	case PenDown:
		isDrawing = true;
		return cmd->popFirst();
		break;
	case PenUp:
		isDrawing = false;
		return cmd->popFirst();
		break;
	case Clear:
		clear();
		return cmd->next;
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
