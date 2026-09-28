#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include "DynamicAdjacencyList.h"

class Pathfiding {
private:
    struct NodeState {
        int nodeId;
        double g;
        double f;

        NodeState(int n, double g_, double f_) : nodeId(n), g(g_), f(f_) {}

        bool operator<(const NodeState& other) const {
            return f > other.f;
        }
    };

    struct NodeInfo {
        double g;
        int came_from;
        bool visited;

        NodeInfo() : g(1e9), came_from(-1), visited(false) {}
    };

	DynamicAdjacencyList& adjacency_list;

	std::map<int, int> bfs_dist_from_goal;

	double bfsHeuristic(int current, int goal);

	void precomputeBFS(int goal);

	std::vector<int> start_a_star(int start, int goal);

	int getMaxArcIterations(int targetLength);

	std::vector<int> ArcIterationMethod(int start, int goal, int targetLength, const std::vector<int>& p0_path);

    std::vector<int> selectClosestToTargetLength(const std::map<double, std::vector<int> >& pathes, int targetLength);

	std::vector<int> findPath(int start, int goal, int banned);

    std::map<std::pair<int, int>, int> buildEdgeMap(const std::vector<int>& path);

public:
	std::vector<int> findPath(int start, int goal);

	std::vector<int> findTargetPath(int start, int goal, int target);

	Pathfiding();
};

#endif