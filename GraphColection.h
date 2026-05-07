#ifndef GraphColectionH
#define GraphColectionH
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include "Node.h"
#include "Branch.h"
#include "BaseComponent.h"
#include "DynamicAdjacencyList.h"
#include "Pathfiding.h"

class GraphCollection : public BaseComponent {
private:
	std::vector<Node*> nodes;
	std::vector<Branch*> branches;
	std::vector<int> n_path;
	int** adjective_matrix;
	int adjective_matrix_size;

	float mod(int c1_x, int c1_y, int c2_x, int c2_y);
	int get_node_index(Node* node);
	int** getAdjectiveMatrixCopy();
	std::vector<int> getNodesId();

	DynamicAdjacencyList& adjacency_list;
	Pathfiding pathfiding;
public:

	GraphCollection();

	~GraphCollection() {
		for (int i = 0; i < nodes.size(); i++) {
			delete nodes[i];
		}
		for (int i = 0; i < branches.size(); i++) {
			delete branches[i];
		}
	}

	void addNode(Node* node);
	void addBranch(int id1, int id2, int branch_weight);
	void deleteNode(Node* node);
	void addBranch(Node* node1, Node* node2, int branch_weight);
	void deleteBranch(Branch* branch);

	void buildPath(std::vector<int> Nodes, bool visibility);

	Node* findNodeById(int id);
	Node* findNodeByPoint(int x, int y);
	Branch* findBranchByPoint(int x, int y);
	std::vector<Branch*> findBranchesByNode(Node* node);

	void saveBinary(std::string filename);
	std::pair<int,int> loadBinary(std::string filename);
	void saveAdjectiveMatrix(std::string filename);
	void saveAdjectiveList(std::string filename);

	std::vector<int> find_shorted_path(int start, int goal);
    std::vector<int> find_target_path(int start, int goal, int targetLenth);

	size_t getNodeCount() const { return nodes.size(); }
	size_t getBranchCount() const { return branches.size(); }

	__property int** AdjectiveMatrix = { read = getAdjectiveMatrixCopy };
	__property std::vector<int> NodesId = { read = getNodesId };
};

#endif

