#include "World.hpp"
#include "Entity.hpp"

std::vector<Entity*> World::objects;	
std::vector<RectangleShape*> World::grid;
std::vector<sf::Vector2i> World::currentPath;
Dijkstra World::dij;
Entity * World::player = nullptr;
std::vector<sf::Vector2i> World::walls;

void World::draw(RenderWindow& win)
{
	for (auto o : objects) {
		o->draw(win);	
	}
	/*for (auto r : grid) {
		win.draw(*r);
	}*/

	sf::RectangleShape rs(sf::Vector2f(Entity::stride, Entity::stride));
	rs.setOutlineThickness(1);
	rs.setOutlineColor(sf::Color::Red);
	for (auto& v : walls) {
		rs.setPosition(v.x * Entity::stride, v.y * Entity::stride);
		win.draw(rs);
	}

	sf::RectangleShape rrs(sf::Vector2f(4, 4));
	rrs.setFillColor(sf::Color::Red);
	auto& g = dij.g;
	for (auto & v : g) {
		rrs.setPosition(v.first.x * Entity::stride + 0.5 * Entity::stride, v.first.y * Entity::stride + 0.5 * Entity::stride);
		win.draw(rrs);
	}
	


	sf::VertexArray arr;
	arr.setPrimitiveType(sf::Lines);
	for (auto & p : dij.pred) {
		sf::Vertex start;
		sf::Vertex end;
		start.color = sf::Color::Green;
		start.color.a = 127;
		end.color = start.color;

		start.position.x = (p.first.x + 0.5) * Entity::stride;
		start.position.y = (p.first.y + 0.5) * Entity::stride;

		end.position.x = (p.second.x + 0.5) * Entity::stride;
		end.position.y = (p.second.y + 0.5) * Entity::stride;

		arr.append(start);
		arr.append(end);
	}
	win.draw(arr);

	sf::VertexArray arrPath;
	arrPath.setPrimitiveType(sf::LinesStrip);
	for (auto& p : currentPath) {
		sf::Vertex start;
		start.color = sf::Color::Magenta;

		start.position.x = (p.x + 0.5) * Entity::stride;
		start.position.y = (p.y + 0.5) * Entity::stride;

		arrPath.append(start);
	}
	win.draw(arrPath);
}

static bool isColliding(int ccx, int ccy) {
	if (ccx < 0)
		return true;
	if (ccy < 0)
		return true;

	if (ccx >= 1280 / Entity::stride)
		return true;

	if (ccy >= 720 / Entity::stride)
		return true;

	for (auto& vi : World::walls)
		if ((vi.x == ccx) && (vi.y == ccy))
			return true;

	return false;
}

void World::init() {
	dij.dist[sf::Vector2i(0, 0)] = 1.0f;
}

void World::update(double dt)
{
	Entity* p = nullptr;
	for (auto o : objects) {
		o->update(dt);

	}
}

std::optional<sf::Vector2i> Dijkstra::findMin(std::vector<Vector2i>& q ) {
	std::optional<sf::Vector2i>  res = std::nullopt;
	float distMin = 1024 * 1024;
	for (auto& s : q) {
		if (dist[s] < distMin) {
			distMin = dist[s];
			res = s;
		}
	}
	return res;
}

float len(const sf::Vector2i & s) {
	return sqrt(s.y * s.y + s.x * s.x);
}

void Dijkstra::updateDist(sf::Vector2i & s1, sf::Vector2i & s2)
{
	float d_s1s2 = len(s2 - s1);
	if (dist[s2] > (dist[s1] + d_s1s2)) {
		dist[s2] = dist[s1] + d_s1s2;
		pred[s2] = s1;
	}

}


void Dijkstra::compute(const sf::Vector2i& start)
{
	using namespace sf;
	g.clear();
	int maxCellW = World::W / Entity::stride + 1;
	int maxCellH = World::H / Entity::stride + 1;
	for (int y = 0; y < maxCellH; ++y)
		for (int x = 0; x < maxCellW; ++x) {
			if (!isColliding(x, y))
				g[sf::Vector2i(x, y)] = true;
		}
	queue.clear();
	dist.clear();
	pred.clear();
	init(start);
	while (!queue.empty()) {
		std::optional<sf::Vector2i> s1 = findMin(queue);
		if (s1 == std::nullopt)
			break;

		auto pos = std::find(queue.begin(), queue.end(), *s1);
		if (pos != queue.end())
			queue.erase(pos);
		sf::Vector2i dirs[] = {
			sf::Vector2i(0,1),
			sf::Vector2i(0,-1),
			sf::Vector2i(-1,0),
			sf::Vector2i(1,0),
		};
		for (int i = 0; i < 4; ++i) {
			sf::Vector2i neighbor = *s1 + dirs[i];
			if (g.find(neighbor) != g.end())
				updateDist(*s1, neighbor);
		}
	}
	int here = 0;
}

void Dijkstra::init(const sf::Vector2i & start)
{
	for (auto& s : g) {
		dist[s.first] = 1024 * 1024;
		queue.push_back(s.first);
	}
	dist[start] = 0;
}
