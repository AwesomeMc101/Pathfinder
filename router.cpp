struct Connection;
#define min(a,b) a < b ? a : b
struct Location {
	char name;
	std::vector<Connection> connections;
};
struct Connection {
	int distance;
	Location* loc;
};

struct Final_Data {
	int dist;
	std::vector<char> route;
};

Final_Data route(Location* l, Location* f, int dist, std::vector<char> names, int found_min) {
	names.emplace_back(l->name);
	if (found_min < dist) {
		printf("EARLY! %d > %d\n", dist, found_min);
		return { dist, names };
	}
	if (l == f) {
		return { dist, names };
	}
	Final_Data m = { INT_MAX, {} };
	for (Connection& c : l->connections) {
		auto l = route(c.loc, f, dist + c.distance, names, found_min);
		if (l.dist < m.dist) {
			m = l;
		}
	}
	return m;
}
std::vector<int> find(std::vector<Location*> nodes) {
	Location* start = nodes[0];
	Location* end = nodes.back();
	std::vector<char> names;
	Final_Data m = { INT_MAX, {} };
	for (Connection& c : start->connections) {
		auto shortest = route(c.loc, end, c.distance, names, m.dist);
		if (shortest.dist < m.dist) {
			m = shortest;
		}
	}
	printf("\n");
	for (auto& c : m.route) {
		std::cout << c << " -> ";
	}

	return { m.dist };
}

int main()
{
	std::vector<Location*> nodes{};

	Location a = { 'a' };
	Location b = { 'b' };
	Location c = { 'c' };
	Location d = { 'd' };
	Location e = { 'e' };
	Location f = { 'f' };
	Location g = { 'g' };

	Connection ab = { 4, &b };
	Connection ac = { 7, &c };
	Connection ae = { 3, &e };
	
	Connection bf = { 7, &f };
	Connection ef = { 11, &f };
	Connection de = { 2, &e };
	Connection cd = { 1, &d };
	Connection dg = { 13, &g };

	a.connections = { ab, ac, ae };
	b.connections = { bf };
	c.connections = { cd };
	d.connections = { de, dg };
	e.connections = { ef };

	nodes = { &a,&b,&c,&d,&e,&f, &g };
	std::cout << find(nodes)[0];
}
