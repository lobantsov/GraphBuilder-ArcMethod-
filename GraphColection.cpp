//---------------------------------------------------------------------------

#pragma hdrstop

#include "GraphColection.h"
//---------------------------------------------------------------------------
GraphCollection::GraphCollection()
    : adjacency_list(DynamicAdjacencyList::getInstance()) {
    adjective_matrix = NULL;
    adjective_matrix_size = 0;
}

void GraphCollection::addBranch(int id1, int id2, int branch_weight){
		Node* n1 = findNodeById(id1);
		Node* n2 = findNodeById(id2);

		if (n1 && n2) {
		   branches.push_back(new Branch(n1,n2));
		   adjacency_list.addEdge(n1->id, n2->id, branch_weight);
		   this->mediator_->Notify_branch(n1->x, n1->y, n2->x, n2->y, branch_weight);
		} else {
			std::cerr << "Error: One or both nodes not found.\n";
		}
}

void GraphCollection::addBranch(Node* node1, Node* node2, int branch_weight){
	branches.push_back(new Branch(node1, node2, branch_weight));
	adjacency_list.addEdge(node1->id, node2->id, branch_weight);
	this->mediator_->Notify_branch(node1->x, node1->y, node2->x, node2->y, branch_weight);
}

void GraphCollection::addNode(Node* node){
	nodes.push_back(node);
}

Node* GraphCollection::findNodeById(int id) {
		for (int i=0; i<nodes.size(); i++) {
			if (nodes[i]->id == id) {
				return nodes[i];
			}
		}
	return NULL;
}

Node* GraphCollection::findNodeByPoint(int x, int y) {
		for (int i=0; i<nodes.size(); i++) {
			if (mod(x,y, nodes[i]->x, nodes[i]->y) <= nodes[i]->radius) {
				return nodes[i];
			}
		}
	return NULL;
}

float GraphCollection::mod(int c1_x, int c1_y, int c2_x, int c2_y) {
	float a = (float)sqrt((double)((c2_x - c1_x) * (c2_x - c1_x) + (c2_y - c1_y) * (c2_y - c1_y)));
	return  a;
}

void GraphCollection::deleteNode(Node* node){
	std::vector<Branch*> branches_ = findBranchesByNode(node);
	nodes.erase(std::find(nodes.begin(), nodes.end(), node));
	if(branches_.size() > 0){
		for (int i = 0; i < branches_.size(); i++) {
//			branches.erase(std::find(branches.begin(), branches.end(), branches_[i]));
//			this->mediator_->Notify_delete_branch(branches_[i]);
//		  delete(branches_[i]);
			deleteBranch(branches_[i]);
		}
		branches_.clear();
	}
	this->mediator_->Notify_delete_node(node);
    delete(node);
}

void GraphCollection::deleteBranch(Branch* branch){
	branches.erase(std::find(branches.begin(), branches.end(), branch));
	adjacency_list.removeEdge(branch->node1->id, branch->node2->id);
	this->mediator_->Notify_delete_branch(branch);
	delete(branch);
}

std::vector<Branch*> GraphCollection::findBranchesByNode(Node* node){
	std::vector<Branch*> branches_;
	for (int i = 0; i < branches.size(); i++) {
		if(branches[i]->node1 == node || branches[i]->node2 == node)
			branches_.push_back(branches[i]);
	}
	return branches_;
}

Branch* GraphCollection::findBranchByPoint(int x, int y){
	for (int i = 0; i < branches.size(); i++) {
		float A = branches[i]->node2->y - branches[i]->node1->y;
		float B = branches[i]->node1->x - branches[i]->node2->x;
		float C = branches[i]->node2->x * branches[i]->node1->y - branches[i]->node1->x * branches[i]->node2->y;
		float d = std::abs(A * x + B * y + C)/(std::sqrt(A * A + B * B));
		if(d < 10) return branches[i];
	}
	return NULL;
}

void GraphCollection::buildPath(std::vector<int> Nodes, bool visibility){
	for (int i = 0; i < Nodes.size(); i++) {
        Node* n = findNodeById(Nodes[i]);
		if (n) {
			this->mediator_->Notify_draw_selected_node(n, visibility);
        }

        if (i + 1 < Nodes.size()) {
            Node* n1 = findNodeById(Nodes[i]);
            Node* n2 = findNodeById(Nodes[i + 1]);

            if (n1 && n2) {
                for (int j = 0; j < branches.size(); ++j) {
                    Branch* b = branches[j];
					if ((b->node1 == n1 && b->node2 == n2) || (b->node1 == n2 && b->node2 == n1)) {
                        this->mediator_->Notify_draw_selected_branch(b,visibility);
                        break;
                    }
                }
            }
        }
	}
}

void GraphCollection::saveBinary(std::string filename){
		std::ofstream outFile(filename.c_str(), std::ios::binary);
	if (!outFile) {
		std::cerr << "log::error - wrong path" << std::endl;
        return;
	}

    size_t nodeCount = nodes.size();
    outFile.write(reinterpret_cast<const char*>(&nodeCount), sizeof(nodeCount));

    for (size_t i = 0; i < nodeCount; ++i) {
        outFile.write(reinterpret_cast<const char*>(&nodes[i]->id), sizeof(nodes[i]->id));
        outFile.write(reinterpret_cast<const char*>(&nodes[i]->x), sizeof(nodes[i]->x));
        outFile.write(reinterpret_cast<const char*>(&nodes[i]->y), sizeof(nodes[i]->y));
        outFile.write(reinterpret_cast<const char*>(&nodes[i]->radius), sizeof(nodes[i]->radius));
    }

    size_t branchCount = branches.size();
    outFile.write(reinterpret_cast<const char*>(&branchCount), sizeof(branchCount));

    for (size_t i = 0; i < branchCount; ++i) {
        int node1_id = branches[i]->node1->id;
        int node2_id = branches[i]->node2->id;
        outFile.write(reinterpret_cast<const char*>(&node1_id), sizeof(node1_id));
        outFile.write(reinterpret_cast<const char*>(&node2_id), sizeof(node2_id));
        outFile.write(reinterpret_cast<const char*>(&branches[i]->weigth), sizeof(branches[i]->weigth));
    }

	outFile.close();
}

std::pair<int,int> GraphCollection::loadBinary(std::string filename){
    int totalWeight = 0;
	int index = 0;
	std::ifstream inFile(filename.c_str(), std::ios::binary);
    if (!inFile) {
		std::cerr << "log::error - wrong path" << std::endl;
		return std::make_pair(-1,-1);
	}

	for (int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
	nodes.clear();

	for (int i; i < branches.size(); i++) {
		delete branches[i];
	}
	branches.clear();

	this->mediator_->Notify_clear_canvas();

    adjacency_list.clear();

    size_t nodeCount;
    inFile.read(reinterpret_cast<char*>(&nodeCount), sizeof(nodeCount));

    for (size_t i = 0; i < nodeCount; ++i) {
        int id, x, y, radius;
        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&radius), sizeof(radius));

        Node* node = new Node(id, x, y);
		node->radius = radius;
		nodes.push_back(node);
		this->mediator_->Notify_load_node(node);
		index++;
	}

    size_t branchCount;
    inFile.read(reinterpret_cast<char*>(&branchCount), sizeof(branchCount));

	for (size_t i = 0; i < branchCount; ++i) {
		int node1_id, node2_id, weight;
        inFile.read(reinterpret_cast<char*>(&node1_id), sizeof(node1_id));
        inFile.read(reinterpret_cast<char*>(&node2_id), sizeof(node2_id));
        inFile.read(reinterpret_cast<char*>(&weight), sizeof(weight));

		Node* node1 = NULL;
		Node* node2 = NULL;
		for (int i = 0; i < nodes.size(); i++) {
			if (nodes[i]->id == node1_id) node1 = nodes[i];
			if (nodes[i]->id == node2_id) node2 = nodes[i];
		}

		if (node1 && node2) {
			Branch* branch = new Branch(node1, node2, weight);
			totalWeight += weight;
			branches.push_back(branch);
			adjacency_list.addEdge(node1->id, node2->id, branch->weigth);
			this->mediator_->Notify_load_branch(branch);
		}
	}

	inFile.close();
	return std::make_pair(index, totalWeight);
}

void GraphCollection::saveAdjectiveMatrix(std::string filename){
	if (nodes.empty()) {
		std::cerr << "No nodes to save in matrix.\n";
		return;
	}

	if(adjective_matrix != NULL){
		for (int i = 0; i < adjective_matrix_size; i++) {
			delete[] adjective_matrix[i];
		}
		delete[] adjective_matrix;
	}

	adjective_matrix_size = nodes.size();
	adjective_matrix = new int*[adjective_matrix_size];
	for (int i = 0; i < adjective_matrix_size; i++) {
		adjective_matrix[i] = new int [adjective_matrix_size];
	}

    for (int i = 0; i < adjective_matrix_size; i++) {
        for (int j = 0; j < adjective_matrix_size; j++) {
			if (i == j) {
                adjective_matrix[i][j] = 0;
            } else {
				adjective_matrix[i][j] = -1;
            }
        }
	}

	for (int i = 0; i < adjective_matrix_size; i++) {
		for (int j = 0; j < branches.size(); j++) {
			if (branches[j]->node1 == nodes[i]) {
				adjective_matrix[i][get_node_index(branches[j]->node2)] = branches[j]->weigth;
			} else if (branches[j]->node2 == nodes[i]) {
				adjective_matrix[i][get_node_index(branches[j]->node1)] = branches[j]->weigth;
			}
		}
	}

	std::ofstream file(filename.c_str());

	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
			file << adjective_matrix[i][j] << "\t";
		}
		file << std::endl;
	}

	file.close();
}

void GraphCollection::saveAdjectiveList(std::string filename){
    adjacency_list.saveToFile(filename);
}

int GraphCollection::get_node_index(Node* node){
	for (int i = 0; i < nodes.size(); i++) {
		if(nodes[i] == node) return i;
	}
	return -1;
}

int** GraphCollection::getAdjectiveMatrixCopy() {
    if (adjective_matrix == NULL) {
		return NULL;
	}

	int** copy = new int*[adjective_matrix_size];
    for (int i = 0; i < adjective_matrix_size; i++) {
        copy[i] = new int[adjective_matrix_size];
        for (int j = 0; j < adjective_matrix_size; j++) {
			copy[i][j] = adjective_matrix[i][j];
        }
    }

	return copy;
}

std::vector<int> GraphCollection::getNodesId() {
	std::vector<int> copy;
    for (size_t i = 0; i < nodes.size(); i++) {
		copy.push_back(nodes[i]->id);
    }
    return copy;
}

std::vector<int> GraphCollection::find_shorted_path(int start, int goal){
	return pathfiding.findPath(start, goal);
}

std::vector<int> GraphCollection::find_target_path(int start, int goal, int targetLenth){
	return pathfiding.findTargetPath(start, goal, targetLenth);
}

#pragma package(smart_init)
