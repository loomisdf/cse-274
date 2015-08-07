#include "BST.h"

#include <sstream>

BSTNode::BSTNode() {
	k = -1;
	v = "";
	left = NULL;
	right = NULL;
}

BSTNode::BSTNode(int myK, string myV) {
	k = myK;
	v = myV;
	left = NULL;
	right = NULL;
}

BST::BST() {
	root = NULL;
}

BST::~BST() {
	while (root != NULL){
		remove(root->k);
	}
}

unsigned long BST::size() {
	return sizeHelper(root);
}

void BST::insert(int k, string v) {
	root = insertHelper(root, k, v);
}

void BST::remove(int k) {
	root = removeHelper(root, k);
}

string BST::find(int k) {
	BSTNode* n = findHelper(root, k);
	if (n == NULL){
		return "";
	}
	else {
		return n->v;
	}
}

bool BST::intExists(int k) {
	if (find(k) != "") {
		return true;
	}
	else {
		return false;
	}
}

int BST::next(int k) {
	BSTNode* n = nextHelper(root, k);
	if (n == NULL) {
		return k;
	} 
	return n->k;
}

int BST::prev(int k) {
	BSTNode* n = prevHelper(root, k);
	if (n == NULL) {
		return k;
	}
	return n->k;
}

void BST::printPreOrder() {
	printPreOrderHelper(root);
}

void BST::printInOrder() {
	printInOrderHelper(root);
}

void BST::printPostOrder() {
	printPostOrderHelper(root);
}

unsigned long BST::sizeHelper(BSTNode* r) {
	if (r == NULL) {
		return 0;
	}
	else {
		return 1 + sizeHelper(r->left) + sizeHelper(r->right);
	}
}

BSTNode* BST::insertHelper(BSTNode* r, int k, string v) {
	if (r == NULL) {
		r = new BSTNode(k, v);
	}
	else if (k < r->k) {
		r->left = insertHelper(r->left, k, v);
	}
	else if (k > r->k) {
		r->right = insertHelper(r->right, k, v);
	}
	return r;
}

BSTNode* BST::removeHelper(BSTNode* r, int k) {
	if (r == NULL) {
		return NULL;
	}
	if (k == r->k) {
		// r is the node to remove

		// r has no children
		if (r->left == NULL && r->right == NULL) {
			return NULL;
		}
		// if r has one child, just replace it
		if (r->left == NULL) {
			return r->right;
		}
		if (r->right == NULL) {
			return r->left;
		}

		// If r has two children
		BSTNode* temp = max(r->left);
		r->k = temp->k;
		r->v = temp->v;
		r->left = removeHelper(temp, temp->k);
		return r;
	}
	else if (k < r->k) {
		r->left = removeHelper(r->left, k);
		return r;
	}
	else if (k > r->k) {
		r->right = removeHelper(r->right, k);
		return r;
	}

}

BSTNode* BST::findHelper(BSTNode* r, int k) {
	stringstream exception;
	exception << "A node matching " << k << " was not found";

	try {
		if (r == NULL) {
			throw exception.str();
		}
		else if (r->k == k) {
			return r;
		}		
		else if (k < r->k) {
			return findHelper(r->left, k);
		}
		else if (k > r->k) {
			return findHelper(r->right, k);
		}
	}
	catch (string exception) {
		cout << exception << endl;
	}
}

BSTNode* BST::nextHelper(BSTNode* r, int k) {
	if (r == NULL) {
		return NULL;
	}
	else if (r->k == k) {
		if (r->right == NULL) {
			return r;
		}
		else {
			return min(r->right);
		}
	}
	else if (r->k > k) {
		if (k == max(r->left)->k) {
			return r;
		}
		else {
			return nextHelper(r->left, k);
		}
	}
	else if (r->k < k) {
		return nextHelper(r->right, k);
	}
}

BSTNode* BST::prevHelper(BSTNode* r, int k) {
	if (r == NULL) {
		return NULL;
	}
	else if (r->k == k) {
		if (r->left == NULL) {
			return r;
		}
		else {
			return max(r->left);
		}
	}
	else if (r->k > k) {
		return prevHelper(r->left, k);
	}
	else if (r->k < k) {
		
		if (k == min(r->right)->k) {
			return r;
		}
		else {
			return prevHelper(r->right, k);
		}
	}
}

void BST::printPreOrderHelper(BSTNode* r) {
	//cout << "(" << r->k << "," << r->v << ") ";
	if (r != NULL) {
		cout << "(" << r->k << "," << r->v << ")";
		printPreOrderHelper(r->left);
		printPreOrderHelper(r->right);
	}
}

void BST::printInOrderHelper(BSTNode* r) {
	if (r != NULL){
		printInOrderHelper(r->left);
		cout << "(" << r->k << ", " << r->v << ") ";
		printInOrderHelper(r->right);
	}
}

void BST::printPostOrderHelper(BSTNode* r) {
	if (r != NULL){
		printPostOrderHelper(r->left);
		printPostOrderHelper(r->right);
		cout << "(" << r->k << ", " << r->v << ") ";
	}
}

BSTNode* BST::min(BSTNode* r) {
	if (r->left == NULL) {
		return r;
	}
	else {
		r = min(r->left);
	}
}

BSTNode* BST::max(BSTNode* r) {
	if (r->right == NULL) {
		return r;
	}
	else {
		r = max(r->right);
	}
}
