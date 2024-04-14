#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
int node_size = 0;
int node_distances = 0;

struct Node {
	int data;
	Node* left;
	Node* right;
};
void addDistances(Node* root, int distances, int check);
Node* createNode(int data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = newNode->right = nullptr;

	return newNode;
}

void createTree(Node ** root, int start, int end, vector<int>myVector) {
	if (start > end) {
		return;
	}
	int middle = (start + end) / 2;
	*root = createNode(myVector[middle]);
	createTree(& (*root)->left, start, middle - 1, myVector);
	createTree(&(*root)->right, middle + 1, end, myVector);
}	


void add_parent(Node * root, unordered_map<Node*, Node*>&q, int distances, int check, int target, int parent) {
	node_distances += root->data, check= check+1;
	if (check == distances) {
		return;
	}

	if (root->left && root->left->data != target) {
		add_parent(root->left, q, distances, check , target, parent);
	}
	if (root->right && root->right->data != target) {
		add_parent(root->right, q, distances, check, target, parent);
	}
	if (q.find(root) != q.end() && root->data == parent) {
		add_parent(q[root], q, distances, check, target = root->data, parent = (q[root])->data);
	}
	
	}
	
int finTarget(Node * root, int target, int distance) {
	unordered_map<Node*, Node*>p;
	queue<Node*>q; 
	Node* target_node = nullptr;
	q.push(root);
	while (!q.empty()) {

		if (q.front()->data == target) {
			cout << "target node: " << q.front()->data << endl;
			 target_node = q.front();
		}

		if (q.front()->left) {
			p[q.front()->left] = q.front();
			q.push(q.front()->left);
		}
	
		if (q.front()->right) {
			p[q.front()->right] = q.front();
			q.push(q.front()->right);
		}
		q.pop();
	}
	cout  << "parent: " << (p[root->right])->data << endl;
	if (target_node != nullptr) {
		addDistances(target_node, distance, 0);
		for (auto pair : p) {
			if (pair.first == target_node) {
				if (p.find(pair.second) != p.end()) {
					add_parent(pair.second, p, distance, 0, target, pair.second->data);
					break;
				}

			}
		}
	}
	
	return node_distances;
}

void addDistances(Node* root, int distances, int check) {
	node_distances += root->data;
	if (distances == check) {
		return;
	}
	if (root->left) {
		addDistances(root->left, distances, check + 1);
	}
	if (root->right) {
		addDistances(root->right, distances, check +1);
	}



}







int main() {
	vector<int>myVector = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Node* root = nullptr;
	createTree(&root, 0, myVector.size() - 1, myVector);
	int target = 4;
	int distance = 6;
	root->right->right->right->right = createNode(12);
	root->right->right->right->right->right = createNode(20);
	
	cout << finTarget(root, target, distance);
	

	

}