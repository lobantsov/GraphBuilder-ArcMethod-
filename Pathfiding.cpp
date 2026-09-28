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
		for (int i = 0; i < (int)neighbors.size(); i++) {
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

// NOTE: this overload no longer calls precomputeBFS() internally.
// It relies on bfs_dist_from_goal already being populated for `goal` by
// the caller (ArcIterationMethod precomputes it once up front, instead of
// every nested call re-running a full BFS over the whole graph — with
// thousands of nodes that repeated BFS was the dominant cost by far).
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
		for (int i = 0; i < (int)neighbors.size(); ++i) {
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

int Pathfiding::getMaxArcIterations(int targetLength) {
	// Adaptive cap instead of a hardcoded 1000: scales with target length,
	// bounded on both sides. At thousands of nodes the branching factor per
	// iteration is much larger, so this cap is what keeps worst-case time
	// bounded — tune divisor/bounds against your graph's typical edge
	// weight and average node degree.
	int iterations = targetLength / 10;
	if (iterations < 200) iterations = 200;
	if (iterations > 2000) iterations = 2000;
	return iterations;
}

// ---- helpers (free functions, not class members, to avoid touching the
// class interface declared in the header beyond what's already there) ----

// FNV-1a hash over a path's node sequence. Used as a std::set<size_t> key
// instead of storing/comparing full std::vector<int> paths in seen_paths:
// at graph sizes in the thousands, paths can be long, and comparing full
// vectors on every set lookup/insert (O(path length) per comparison) adds
// up. Hashing to a single size_t means each comparison inside the set is
// O(1) instead of O(path length) — we still pay O(log n) for the set
// itself (unordered_set isn't available on this compiler), but the
// per-comparison cost drops sharply. Collisions are astronomically
// unlikely for this use case (would only cause a legitimate new path to
// be skipped as a false "already seen").
static size_t hashPath(const std::vector<int>& path) {
	size_t h = 2166136261u; // FNV offset basis (32-bit, portable across int sizes)
	for (size_t i = 0; i < path.size(); ++i) {
		h ^= static_cast<size_t>(path[i]);
		h *= 16777619u; // FNV prime (32-bit)
	}
	return h;
}

// Total weight of a path, by summing edge weights via adjacency lookups.
static double sumPathWeight(DynamicAdjacencyList& adjacency_list, const std::vector<int>& path) {
	double total = 0.0;
	for (int k = 0; k + 1 < (int)path.size(); ++k) {
		const std::vector<std::pair<int, int> >& nbs = adjacency_list.getNeighbors(path[k]);
		for (size_t t = 0; t < nbs.size(); ++t) {
			if (nbs[t].first == path[k + 1]) {
				total += nbs[t].second;
				break;
			}
		}
	}
	return total;
}

// Prefix weight sums for a path: prefix[i] = weight of path[0..i-1..i], so
// the weight of path[0..i] is available in O(1) instead of re-summing from
// scratch for every candidate arc explored off this path.
static std::vector<double> buildPrefixWeights(DynamicAdjacencyList& adjacency_list, const std::vector<int>& path) {
	std::vector<double> prefix(path.size(), 0.0);
	for (int k = 0; k + 1 < (int)path.size(); ++k) {
		const std::vector<std::pair<int, int> >& nbs = adjacency_list.getNeighbors(path[k]);
		double w = 0.0;
		for (size_t t = 0; t < nbs.size(); ++t) {
			if (nbs[t].first == path[k + 1]) {
				w = nbs[t].second;
				break;
			}
		}
		prefix[k + 1] = prefix[k] + w;
	}
	return prefix;
}

std::vector<int> Pathfiding::ArcIterationMethod(int start, int goal, int targetLength, const std::vector<int>& p0_path) {
	std::map<double, std::vector<int> > pathes;
	// Hash-based seen-path tracking (see hashPath comment above) instead of
	// std::set<std::vector<int>>, which does an O(path length) vector
	// comparison per set operation.
	std::set<size_t> seen_paths;

	if (p0_path.size() < 2) return std::vector<int>();

	std::queue<std::vector<int> > queue;
	queue.push(p0_path);
	seen_paths.insert(hashPath(p0_path));

	int iterations = 0;
	int maxIterations = getMaxArcIterations(targetLength);

	// bfs_dist_from_goal only depends on `goal`, so compute it once here
	// rather than inside every internal findPath(...) call below.
	precomputeBFS(goal);

	double n = static_cast<double>(targetLength);
	double earlyExitEpsilonPercent = 3.0; // matches selectClosestToTargetLength's initial tolerance

	while (!queue.empty() && iterations < maxIterations) {
		std::vector<int> current_path = queue.front();
		queue.pop();

		std::map<std::pair<int, int>, int> edge_map = buildEdgeMap(current_path);
		std::vector<double> prefix = buildPrefixWeights(adjacency_list, current_path);

		for (int i = 0; i + 1 < (int)current_path.size(); ++i) {
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

				size_t pathHash = hashPath(new_path);
				if (seen_paths.count(pathHash)) continue;

				if (new_path.back() != goal) continue;

				// Incremental weight: prefix up to `from` + edge(from,neighbor)
				// + weight of `rest`, instead of re-summing the whole new_path
				// from scratch on every candidate.
				double rest_weight = sumPathWeight(adjacency_list, rest);
				double total_weight = prefix[i + 1] + weight + rest_weight;

				pathes[total_weight] = new_path;
				seen_paths.insert(pathHash);
				queue.push(new_path);

				double diff = std::abs(total_weight - n);
				double diffPercent = (n > 0.0) ? (diff / n * 100.0) : 0.0;

				// Early exit: stop as soon as a candidate is within
				// tolerance, instead of exhausting maxIterations.
				if (diffPercent <= earlyExitEpsilonPercent) {
					return new_path;
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
	for (int i = 0; i + 1 < (int)path.size(); ++i) {
		int from = path[i];
		int to = path[i + 1];
		std::vector<std::pair<int, int> > neighbors = adjacency_list.getNeighbors(from);
		for (int j = 0; j < (int)neighbors.size(); ++j) {
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
