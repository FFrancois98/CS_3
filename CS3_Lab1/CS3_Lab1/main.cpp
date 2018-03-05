#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct node {
	int key;
	node* left;
	node* right;
};
class TreeType {
public:
	TreeType();
	void insert(node*, int);
	void inorder(node*);
	node* root;

};
int main() {
	TreeType BinarySearch;

	BinarySearch.insert(BinarySearch.root, 12);
	BinarySearch.insert(BinarySearch.root, 10);
	BinarySearch.insert(BinarySearch.root, 20);

	BinarySearch.inorder(BinarySearch.root);

	return 0;
}
TreeType::TreeType() {
	root = NULL;
}
void TreeType::insert(node* trunk, int branch) {
	node* interim_branch = new node;
	interim_branch->key = branch;
	interim_branch->left = NULL;
	interim_branch->right = NULL;

	if (root == NULL) {
		root = interim_branch;
		return;
	}
	else {
		if (trunk->key > branch) {
			if (trunk->left != NULL) {
				insert(trunk->left, branch);
			}
			else {
				trunk->left = interim_branch;
				return;
			}
		}
		else {
			if (trunk->right != NULL) {
				insert(trunk->right, branch);
			}
			else {
				trunk->right = interim_branch;
				return;
			}
		}
	}
}

void TreeType::inorder(node* trunk) {
	if (root == NULL) {
		cout << "This BST is empty. There is nothing to inorder traverse. " << endl;
		return;
	}
	else {
		if (trunk != NULL) {
			inorder(trunk->left);
			cout << trunk->key << " " << endl;
			inorder(trunk->right);
		}
	}
}
