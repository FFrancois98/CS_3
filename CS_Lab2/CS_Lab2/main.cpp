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
	void deleteNode(node*, int);
	void inorder(node*);
	void preorder(node*);
	void postorder(node*);
	node* root;

};
int main() {
	TreeType BinarySearch;

	BinarySearch.insert(BinarySearch.root, 12);
	BinarySearch.insert(BinarySearch.root, 10);
	BinarySearch.insert(BinarySearch.root, 20);

	BinarySearch.insert(BinarySearch.root, 30);
	BinarySearch.insert(BinarySearch.root, 45);
	BinarySearch.insert(BinarySearch.root, 22);

	BinarySearch.insert(BinarySearch.root, 11);
	BinarySearch.insert(BinarySearch.root, 6);
	BinarySearch.insert(BinarySearch.root, 8);

	cout << "Inorder Traversal: ";
	BinarySearch.inorder(BinarySearch.root);
	cout << endl;

	BinarySearch.deleteNode(BinarySearch.root, 10);

	cout << "Inorder Traversal: ";
	BinarySearch.inorder(BinarySearch.root);
	cout << endl;

	cout << "Preorder Traversal: ";
	BinarySearch.preorder(BinarySearch.root);
	cout << endl;

	cout << "Postorder Traversal: ";
	BinarySearch.postorder(BinarySearch.root);
	cout << endl;
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
		cout << "This BST is empty. There is nothing to inorderly traverse. " << endl;
		return;
	}
	else {
		if (trunk != NULL) {
			inorder(trunk->left);
			cout << trunk->key << " ";
			inorder(trunk->right);
		}
	}
}

void TreeType::preorder(node* trunk) {
	if (root == NULL) {
		cout << "This BST is empty. There is nothing to preorderly traverse. " << endl;
		return;
	}
	else {
		if (trunk != NULL) {
			cout << trunk->key << " ";
			preorder(trunk->left);
			preorder(trunk->right);
		}
	}
}
void TreeType::postorder(node* trunk) {
	if (root == NULL) {
		cout << "This BST is empty. There is nothing to postorderly traverse. " << endl;
		return;
	}
	else {
		if (trunk != NULL) {
			postorder(trunk->left);
			postorder(trunk->right);
			cout << trunk->key << " ";
		}
	}
}

void TreeType::deleteNode(node* trunk, int branch) {
	bool search = false;
	node* prev = NULL;				// keeps track of the parent node of the current node
	node* curr = trunk;				// keeps track of the current node

	if (curr == NULL) {
		cout << "There are no nodes to delete because the tree is empty!! :)" << endl;
		return;
	}
	while (curr != NULL) {			// searching for the node to be deleted.
		if (curr->key == branch) {	// the node has been found
			search = true;
			break;
		}
		else {						// the node hasn't found been found yet.
			prev = curr;
			if (curr->key < branch) {
				curr = curr->right;
			}
			else {
				curr = curr->left;
			}
		}
	}
	if (!search) {					// the node doesn't exist in the tree
		cout << "This node does not exist in the tree. :(" << endl;
		return;
	}
	// CASE 1: Removing a Leaf Node
	if (curr->left == NULL && curr->right == NULL)
	{
		if (prev->left == curr) {
			prev->left = NULL;
		}
		else {
			prev->right = NULL;
		}
		delete curr;
		cout << branch << " has been removed from the Tree." << endl;
		return;
	}

	// CASE 2: Removing a Node with One Child
	if (curr->left == NULL && curr->right != NULL) {		// the right child is present
		if (prev->left == curr) {						// determining whether the current node is in the left or right subtree of the parent
			prev->left = curr->right;					// connects the parent node to the child of the current node
			delete curr;
			curr = NULL;
			cout << branch << " has been deleted from the tree. :)" << endl;
			return;
		}
		else {
			prev->right = curr->right;
			delete curr;
			curr = NULL;
			cout << branch << " has been deleted from the tree. :)" << endl;
			return;
		}

	}
	else if (curr->left != NULL && curr->right == NULL) {		// the left child is present
		if (prev->left == curr) {
			prev->left = curr->left;
			delete curr;
			curr = NULL;
			cout << branch << " has been deleted from the tree. :)" << endl;
			return;
		}
		else {
			prev->right = curr->left;
			delete curr;
			curr = NULL;
			cout << branch << " has been deleted from the tree. :)" << endl;
			return;
		}
	}

	// CASE 3: Removing a node with Two Child
	if (curr->left != NULL && curr->right != NULL)						// determines if the curr node has 2 children
	{
		node* check = curr->right;										// the right subtree of the curr node
		if ((curr->left == NULL) && (curr->right == NULL))				// the right subtree doesn't have children
		{
			curr = check;												
			delete check;
			curr->right = NULL;
			cout << branch << " has been deleted from the tree. :)" << endl;
		}
		else {															// Right child has children
			// If the node's right child has a left child, finds the smallest left node of the right subtree
			if ((curr->right)->left != NULL) {
				node* leftCurr;						
				node* leftCurrPrev;
				leftCurrPrev = curr->right;
				leftCurr = (curr->right)->left;
				while (leftCurr->left != NULL)			// searching for the left most node of right subtree
				{
					leftCurrPrev = leftCurr;
					leftCurr = leftCurr->left;
				}
				curr->key = leftCurr->key;
				delete leftCurr;
				leftCurrPrev->left = NULL;
				cout << branch << " has been deleted from the tree. :)" << endl;
			}
			else {
				// the node has right children
				node* temp = curr->right;				
				curr->key = temp->key;
				curr->right = temp->right;
				delete temp;
				cout << branch << " has been deleted from the tree. :)" << endl;
			}
		}
		return;
	}
}
/*

Inorder Traversal: 6 8 10 11 12 20 22 30 45
10 has been deleted from the tree. :)
Inorder Traversal: 6 8 11 12 20 22 30 45
Preorder Traversal: 12 11 6 8 20 30 22 45
Postorder Traversal: 8 6 11 22 45 30 20 12
Press any key to continue . . .

*/