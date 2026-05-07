//---------------------------------------------------------------------------

#pragma hdrstop

#include "Pathfiding.h"

Pathfiding::Pathfiding()
	: adjacency_list(DynamicAdjacencyList::getInstance()) {}

std::vector<int> Pathfiding::start_a_star(int start, int goal) {
	std::priority_queue<NodeState> openSet;
	std::map<int, NodeInfo> nodes;

	nodes[start].g = 0.0;
	double f_start = bfsHeuristic(start, goal);
	openSet.push(NodeState(start, 0.0, f_start));

    while (!openSet.empty()) {
		NodeState current = openSet.top();
		openSet.pop();
		int v = current.nodeId;

		if (nodes[v].visited) continue;
		nodes[v].visited = true;

		if (v == goal) {
			std::vector<int> path;
			while (v != -1) {
				path.push_back(v);
				v = nodes[v].came_from;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		const std::vector<std::pair<int, int> >& neighbors = adjacency_list.getNeighbors(v);
		for (int i = 0; i < neighbors.size(); i++) {
			int u = neighbors[i].first;
			double weight = neighbors[i].second;
			double tentative_g = nodes[v].g + weight;

			if (tentative_g < nodes[u].g) {
				nodes[u].g = tentative_g;
				nodes[u].came_from = v;
				double f = tentative_g + bfsHeuristic(u, goal);
				openSet.push(NodeState(u, tentative_g, f));
			}
		}
	}

	return std::vector<int>();
}

double Pathfiding::bfsHeuristic(int current, int goal){
	const int MIN_EDGE_WEIGHT = 1;
	if (!bfs_dist_from_goal.count(current)) return 0;
	return bfs_dist_from_goal[current] * MIN_EDGE_WEIGHT;
}

std::vector<int> Pathfiding::findPath(int start, int goal){
	precomputeBFS(goal);
	return start_a_star(start, goal);
}

std::vector<int> Pathfiding::findPath(int start, int goal, int banned) {
	std::priority_queue<NodeState> openSet;
	std::map<int, NodeInfo> nodes;

	nodes[start].g = 0.0;
	double f_start = bfsHeuristic(start, goal);
	openSet.push(NodeState(start, 0.0, f_start));

	while (!openSet.empty()) {
		NodeState current = openSet.top(); openSet.pop();
		int v = current.nodeId;

		if (nodes[v].visited) continue;
		nodes[v].visited = true;

		if (v == goal) {
			std::vector<int> path;
			while (v != -1) {
				path.push_back(v);
				v = nodes[v].came_from;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		const std::vector<std::pair<int, int> >& neighbors = adjacency_list.getNeighbors(v);
		for (int i = 0; i < neighbors.size(); ++i) {
			int u = neighbors[i].first;
			if (u == banned) continue;

			double weight = neighbors[i].second;
			double tentative_g = nodes[v].g + weight;

			if (tentative_g < nodes[u].g) {
				nodes[u].g = tentative_g;
				nodes[u].came_from = v;
				double f = tentative_g + bfsHeuristic(u, goal);
				openSet.push(NodeState(u, tentative_g, f));
			}
		}
	}
	return std::vector<int>();
}

void Pathfiding::precomputeBFS(int goal) {
    bfs_dist_from_goal.clear();

    std::queue<int> q;
    q.push(goal);
    bfs_dist_from_goal[goal] = 0;

    while (!q.empty()) {
        int v = q.front(); q.pop();

        const std::vector<std::pair<int, int> >& neighbors = adjacency_list.getNeighbors(v);
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int u = neighbors[i].first;
            if (!bfs_dist_from_goal.count(u)) {
                bfs_dist_from_goal[u] = bfs_dist_from_goal[v] + 1;
                q.push(u);
            }
        }
    }
}

int Pathfiding::getMaxArcIterations(int tagetLenth) {
	return 1000;
}

std::vector<int> Pathfiding::ArcIterationMethod(int start, int goal, int targetLength, const std::vector<int>& p0_path) {
	std::map<double, std::vector<int> > pathes;
	std::set<std::vector<int> > seen_paths;

	if (p0_path.size() < 2) return std::vector<int>();

	std::set<int> p0_nodes(p0_path.begin(), p0_path.end());

	std::queue<std::vector<int> > queue;
	queue.push(p0_path);
	seen_paths.insert(p0_path);

	int iterations = 0;
	int maxIterations = getMaxArcIterations(targetLength);

	while (!queue.empty() && iterations < maxIterations) {
		std::vector<int> current_path = queue.front();
		queue.pop();

		std::map<std::pair<int, int>, int> edge_map = buildEdgeMap(current_path);

		for (int i = 0; i + 1 < current_path.size(); ++i) {
			int from = current_path[i];
			int to = current_path[i + 1];

			std::vector<std::pair<int, int> > neighbors = adjacency_list.getNeighbors(from);
			int base_weight = edge_map[std::make_pair(from, to)];

			for (size_t j = 0; j < neighbors.size(); ++j) {
				int neighbor = neighbors[j].first;
				int weight = neighbors[j].second;

				if (neighbor == to) continue;
				if (weight < base_weight) continue;

				std::vector<int> new_path(current_path.begin(), current_path.begin() + i + 1);
				new_path.push_back(neighbor);

				std::vector<int> rest = findPath(neighbor, goal, from);
				if (rest.empty()) continue;

				new_path.insert(new_path.end(), rest.begin() + 1, rest.end());

				std::set<int> visited_nodes(new_path.begin(), new_path.end());
				if (visited_nodes.size() < new_path.size()) continue;

				if (seen_paths.count(new_path)) continue;

				double total_weight = 0;
				for (int k = 0; k + 1 < new_path.size(); ++k) {
					std::vector<std::pair<int, int> > nbs = adjacency_list.getNeighbors(new_path[k]);
					for (size_t t = 0; t < nbs.size(); ++t) {
						if (nbs[t].first == new_path[k + 1]) {
							total_weight += nbs[t].second;
							break;
						}
					}
				}

				if (new_path.back() == goal) {
					pathes[total_weight] = new_path;
					seen_paths.insert(new_path);
					queue.push(new_path);
				}
			}
		}

		++iterations;
	}

	if (!pathes.empty()) {
		return selectClosestToTargetLength(pathes, targetLength);
	}

	return std::vector<int>();
}


std::vector<int> Pathfiding::selectClosestToTargetLength(const std::map<double, std::vector<int> >& pathes, int targetLength) {
	if (pathes.empty()) return std::vector<int>();

	double epsilon_percent = 3.0;
	double epsilon_step = 1.0;
	double n = static_cast<double>(targetLength);

	while (true) {
		double eps = n * (epsilon_percent / 100.0);
		double lower = n - eps;
		double upper = n + eps;

		for (std::map<double, std::vector<int> >::const_iterator it = pathes.begin(); it != pathes.end(); ++it) {
			if (it->first >= lower && it->first <= upper) {
				return it->second;
			}
		}

		epsilon_percent += epsilon_step;

		if (epsilon_percent > 100.0) {
			break;
		}
	}

	double bestDiff = 1e9;
	std::map<double, std::vector<int> >::const_iterator bestIt = pathes.begin();

	for (std::map<double, std::vector<int> >::const_iterator it = pathes.begin(); it != pathes.end(); ++it) {
		double diff = std::abs(it->first - n);
		if (diff < bestDiff) {
			bestDiff = diff;
			bestIt = it;
		}
	}

	return bestIt->second;
}

std::map<std::pair<int, int>, int> Pathfiding::buildEdgeMap(const std::vector<int>& path) {
	std::map<std::pair<int, int>, int> edge_map;
	for (int i = 0; i + 1 < path.size(); ++i) {
		int from = path[i];
		int to = path[i + 1];
		std::vector<std::pair<int, int> > neighbors = adjacency_list.getNeighbors(from);
		for (int j = 0; j < neighbors.size(); ++j) {
			if (neighbors[j].first == to) {
				edge_map[std::make_pair(from, to)] = neighbors[j].second;
				break;
			}
		}
	}
	return edge_map;
}

std::vector<int> Pathfiding::findTargetPath(int start, int goal, int target){
	return ArcIterationMethod(start, goal, target, findPath(start, goal));
}

#pragma package(smart_init)
