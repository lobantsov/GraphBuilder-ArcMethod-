//---------------------------------------------------------------------------

#pragma hdrstop
#include "DynamicAdjacencyList.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

DynamicAdjacencyList& DynamicAdjacencyList::getInstance() {
    static DynamicAdjacencyList instance;
    return instance;
}

bool DynamicAdjacencyList::match_pair_first(const std::pair<int, int>& p, int value) {
    return p.first == value;
}

void DynamicAdjacencyList::addEdge(int u, int v, int weight) {
    adj[u].push_back(std::make_pair(v, weight));
    adj[v].push_back(std::make_pair(u, weight));
}

void DynamicAdjacencyList::removeEdge(int u, int v) {
    std::vector<std::pair<int, int> >& neighbors_u = adj[u];
    for (std::vector<std::pair<int, int> >::iterator it = neighbors_u.begin(); it != neighbors_u.end(); ) {
        if (match_pair_first(*it, v))
            it = neighbors_u.erase(it);
        else
            ++it;
    }

    std::vector<std::pair<int, int> >& neighbors_v = adj[v];
    for (std::vector<std::pair<int, int> >::iterator it = neighbors_v.begin(); it != neighbors_v.end(); ) {
        if (match_pair_first(*it, u))
            it = neighbors_v.erase(it);
        else
            ++it;
    }
}

const std::vector<std::pair<int, int> >& DynamicAdjacencyList::getNeighbors(int u) const {
    static const std::vector<std::pair<int, int> > empty;
    std::map<int, std::vector<std::pair<int, int> > >::const_iterator it = adj.find(u);
    return (it != adj.end()) ? it->second : empty;
}

bool DynamicAdjacencyList::hasEdge(int u, int v) const {
    std::map<int, std::vector<std::pair<int, int> > >::const_iterator it = adj.find(u);
    if (it == adj.end()) return false;

    const std::vector<std::pair<int, int> >& neighbors = it->second;
    for (size_t i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i].first == v) return true;
    }
    return false;
}

void DynamicAdjacencyList::printNeighbors(int u) const {
    std::map<int, std::vector<std::pair<int, int> > >::const_iterator it = adj.find(u);
    if (it == adj.end()) {
        std::cout << "No neighbors for node " << u << std::endl;
        return;
    }

    std::cout << "Neighbors of node " << u << ": ";
    const std::vector<std::pair<int, int> >& neighbors = it->second;
    for (size_t i = 0; i < neighbors.size(); ++i) {
        std::cout << "(" << neighbors[i].first << ", w=" << neighbors[i].second << ") ";
    }
    std::cout << std::endl;
}

void DynamicAdjacencyList::saveToFile(const std::string& filename) const {
    std::ofstream out(filename.c_str());
    if (!out.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    for (std::map<int, std::vector<std::pair<int, int> > >::const_iterator it = adj.begin(); it != adj.end(); ++it) {
        out << it->first << ":";
        const std::vector<std::pair<int, int> >& neighbors = it->second;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            out << " (" << neighbors[i].first << ", " << neighbors[i].second << ")";
        }
        out << std::endl;
    }

    out.close();
}

void DynamicAdjacencyList::clear(){
    adj.clear();
}
