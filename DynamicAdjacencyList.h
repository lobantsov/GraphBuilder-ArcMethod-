#ifndef DYNAMIC_ADJACENCY_LIST_H
#define DYNAMIC_ADJACENCY_LIST_H

#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

class DynamicAdjacencyList {
private:
    std::map<int, std::vector<std::pair<int, int> > > adj;

	bool match_pair_first(const std::pair<int, int>& p, int value);

	DynamicAdjacencyList(){}

public:

	static DynamicAdjacencyList& getInstance();

	void clear();

	void addEdge(int u, int v, int weight);

	void removeEdge(int u, int v);

	const std::vector<std::pair<int, int> >& getNeighbors(int u) const;

	bool hasEdge(int u, int v) const;

	void saveToFile(const std::string& filename) const;

	void printNeighbors(int u) const;
};

#endif

