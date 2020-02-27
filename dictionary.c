#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"


//Each node in the tree will be one of these
typedef struct Node Node;

struct Node {
	int key;
	int val;
	Node* left;
	Node* right;
};


//Dictionary will be used as a "manager"
struct Dictionary {
	Node* root;
	int size;
};


/***********
*Function Name: initNode
*Input: void
*Output: Node*
*Function Operation:
	The function allocates memory for a new node and initializes all of its values at null.
*************/
Node* initNode() {
	Node* node = (Node*)malloc(sizeof(Node));
	
	//If malloc fails
	if (node == NULL) {
		return node;
	}

	node->key = 0;
	node->val = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/***********
*Function Name: initDictionary
*Input: void
*Output: Dictionary*
*Function Operation:
	Initializes a "manager" for the dictionary. It contains a pointer to the root node
	in the tree and the size of the dictionary.
*************/
Dictionary* initDictionary() {
	Dictionary* dcty = (Dictionary*)malloc(sizeof(Dictionary));
	//Possibility of failed allocation is handled in later functions.
	dcty->root = NULL;
	dcty->size = 0;
	return dcty;
}


/***********
*Function Name: destroyNodes
*Input: Node*
*Output: void
*Function Operation:
	This function traverses the entire tree using recursion.
	and frees the memory that was allocated for each node.
*************/
void destroyNodes(Node* node) {
	if (node->left == NULL && node->right == NULL) {
		free(node);
		return;
	}

	if (node->left != NULL && node->right != NULL) {
		destroyNodes(node->left);
		node->left = NULL;
		destroyNodes(node->right);
		node->right = NULL;
		free(node);
		return;
	}

	if (node->left != NULL && node->right == NULL) {
		destroyNodes(node->left);
		node->left = NULL;
		free(node);
		return;
	}

	if (node->left == NULL && node->right != NULL) {
		destroyNodes(node->right);
		node->right = NULL;
		free(node);
		return;
	}

}


/***********
*Function Name: destroyDictionary
*Input: Dictoinary*
*Output: void
*Function Operation:
	This function uses destroyNodes to free allocated memory for the tree
	and then destroys the "manager" by freeing it.
*************/
void destroyDictionary(Dictionary* d) {
	//If allocation for the dictionary had failed to begin with
	if (d == NULL) {
		return;
	}

	//If the dictionary is empty or if allocation for the root failed
	else if (d->root == NULL) {
		free(d);
		return;
	}

	else {
		destroyNodes(d->root);
		d->root = NULL;
		d->size = 0;
		free(d);
		return;
	}

}

/***********
*Function Name: sizeOfDictionary
*Input: Dictionary*
*Output: int
*Function Operation:
	Returns size of dictionary.
*************/
int sizeOfDictionary(Dictionary* d) {
	return d->size;
}


/***********
*Function Name: insertNode
*Input: Dictionary*, Node*, int key, int value
*Output: Result
*Function Operation:
	Initializes and inserts a new node to the tree where it belongs.
	Uses recursion to find the correct location.
*************/
Result insertNode(Dictionary* d, Node* node, int key, int value) {
	assert(d != NULL);

	//If the key is an existing key, its value is overwritten
	if (key == node->key) {
	node->val = value;
	return SUCCESS;
	}

	//Initializes a new node to the "left" of the existing node.
	else if (key < node->key && node->left == NULL) {
	node->left = initNode();
	//If malloc from initNode fails
	if (node->left == NULL) {
		return MEM_ERROR;
	}
	node->left->key = key;
	node->left->val = value;
	d->size++;
	return SUCCESS;
	}

	//Initializes a new node to the "right" of the existing node.
	else if (key > node->key&& node->right == NULL) {
	node->right = initNode();
	//If allocation failed
	if (node->right == NULL) {
		return MEM_ERROR;
	}
	node->right->key = key;
	node->right->val = value;
	d->size++;

	return SUCCESS;
	}


	//If the key is smaller than key in current node, it is "sent" left
	else if (key < node->key) {
	Node* follower = node->left;
	return insertNode(d, follower, key, value);
	}

	//If the key is smaller than key in current node, it is "sent" right
	else if (key > node->key) {
	Node* follower = node->right;
	return insertNode(d, follower, key, value);
	}

	return SUCCESS;
}


/***********
*Function Name: putInDictionary
*Input: Dictionary*, int key, int value
*Output: Result
*Function Operation:
	Uses insertNode to add values to the dictionary.
*************/

Result putInDictionary(Dictionary* d, int key, int value) {
	//If allocation of dictionary failed.
	if (d == NULL) {
		return MEM_ERROR;
	}

	//If the dictionary tree is currently empty
	else if (d->root == NULL) {
		d->root = initNode();
		if (d->root == NULL) {
			return MEM_ERROR;
		}
		d->root->key = key;
		d->root->val = value;
		d->size++;
		return SUCCESS;
	}

	else return insertNode(d, d->root, key, value);
}


/***********
*Function Name: findNode
*Input: Node*, int key
*Output: int
*Function Operation:
	Uses recursion to find the value assigned to a given key.
*************/
int findNode(Node* node, int key) {
	assert(node != NULL);


	if (key == node->key) {
		return node->val;
	}


	//Traverses the tree to the "left"
	else if (key < node->key) {
		Node* follower = node->left;
		//If there is no "left", then the requested value does not exist in the tree
		if (follower == NULL) {
			return 0;
		}
		else return findNode(follower, key);
	}

	//Same thing for the "right"
	else if (key > node->key) {
		Node* follower = node->right;
		if (follower == NULL) {
			return 0;
		}
		else return findNode(follower, key);
	}
}


/***********
*Function Name: getFromDictionary
*Input: Dictionary*, int key
*Output: int
*Function Operation:
	Uses findNode to retrieve a value from the dictionary.

	If the tree does not contain the requested key,
	or if there was a memory error at any point,
	then 0 is returned.

	NOTE: This means that 0 CANNOT be a value in the tree, it can only
	be a key. I'm only following instructions, if this turns out to be buggy
	when an inputted value is 0, then that's not my fault! This is how you
	wanted us to write the program...
*************/

int getFromDictionary(Dictionary* d, int key) {
	assert(d != NULL);
	
	//If initialization of dictionary failed
	if (d == NULL) {
		return 0;
	}

	//If tree is empty or initialization of root failed
	else if (d->root == NULL) {
		return 0;
	}
	
	//Otherwise
	else return findNode(d->root, key);
}


/***********
*Function Name: findParentOfMin
*Input: Node*
*Output: Node*
*Function Operation:
	Finds the parent node of the minimum value in the tree.
*************/
Node* findParentOfMin(Node* node) {
	Node* child = node->left;
	Node* childLeft = node->left->left;

	if (childLeft != NULL) {
		return findParentOfMin(child);
	}

	else return node;
}

/***********
*Function Name: removeNonRootNode
*Input: Dictoinary*, Node*, int key
*Output: Result
*Function Operation:
	Removes nodes from the tree.
*************/
Result removeNonRootNode(Dictionary* d, Node* node, int key) {
	assert(d != NULL);
	
	Node* child = NULL;
	int direction = 0;

	//Flag for if target node is to the left of current node
	if (node->left != NULL && node->left->key == key) {
		child = node->left;
		direction = 1;
	}
	//Flag for if target node is to the right of current node
	else if (node->right != NULL && node->right->key == key) {
		child = node->right;
		direction = 2;
	}

	//If the target node has no children
	if (child->left == NULL && child->right == NULL) {
		free(child);
		child = NULL;
		if (direction == 1) {
			node->left = NULL;
		}
		else if (direction == 2) {
			node->right = NULL;
		}
		d->size--;
		return SUCCESS;
	}

	//If the target node has only left child
	else if (child->left != NULL && child->right == NULL) {
		Node* temp = child->left;
		temp->right = child->left->right;
		temp->left = child->left->left;
		free(child);
		child = NULL;
		//If target is to the left of its parent
		if (direction == 1) {
			node->left->right = temp->right;
			node->left->left = temp->left;
			node->left->key = temp->key;
			node->left->val = temp->val;
			node->left = temp;
		}

		//If target is to the right of its parent
		else if (direction == 2) {
			node->right->right = temp->right;
			node->right->left = temp->left;
			node->right->key = temp->key;
			node->right->val = temp->val;
			node->right = temp;
		}

		d->size--;
		return SUCCESS;
	}

	//Same thing for when target node has only right child
	else if (child->left == NULL && child->right != NULL) {
		Node* temp = child->right;
		temp->right = child->right->right;
		temp->left = child->right->left;
		free(child);
		child = NULL;
		if (direction == 1) {
			node->left->right = temp->right;
			node->left->left = temp->left;
			node->left->key = temp->key;
			node->left->val = temp->val;
			node->left = temp;
		}

		else if (direction == 2) {
			node->right->right = temp->right;
			node->right->left = temp->left;
			node->right->key = temp->key;
			node->right->val = temp->val;
			node->right = temp;
		}

		d->size--;
		return SUCCESS;
	}


	/*
	When the target node has two children, it is overwritten by the next smallest node
	in the tree, which is found using this algorithm. The next smallest node of any given node
	in the binary tree will always be the leftmost node branching from the first node to the right.
	*/
	else if (child->left != NULL && child->right != NULL) {
		Node* parentOfMin = NULL;
		Node* minNode = NULL;

		/*
		If the next node to the right does not branch to the left,
		then it is the next smallest node.
		*/
		if (child->right->left == NULL) {
			parentOfMin = child;
			minNode = child->right;
		}

		/*
		If the next node to the right does branch to the left,
		then findParentOfMin traverses the branch as far left
		as possible to find the parent of the minimum node.
		*/
		else {
			parentOfMin = findParentOfMin(child->right);
			//The minimum node itself is to the left of its parent.
			minNode = parentOfMin->left;
		}

		//The target node is overwritten.
		child->key = minNode->key;
		child->val = minNode->val;
		/*
		Since the minimum node will never have a node smaller than it (to its left),
		then it either has one child (to its right) or no children at all.
		removeNonrootNode is used to remove the minimum node.
		*/
		return removeNonRootNode(d, parentOfMin, minNode->key);
	}
}

/***********
*Function Name: removeRoot
*Input: Dictoinary*, Node*, int key
*Output: Result
*Function Operation:
	Removes root from the tree. Since the root has no parent node,
	we use a separate function.

	If the root is the only node in the tree, this is handled earlier on
	in removeFromDictionary
*************/
Result removeRoot(Dictionary* d, Node* node, int key) {
	assert(d != NULL);
	
	//If root has only a right child
	if (node->left != NULL && node->right == NULL) {
		Node* temp = node->left;
		free(node);
		node->left = temp->left;
		node->right = temp->right;
		node->key = temp->key;
		node->val = temp->val;
		node = temp;
		d->size--;
		return SUCCESS;
	}
	
	//If root has only a left child
	else if (node->right != NULL && node->left == NULL) {
		Node* temp = node->right;
		free(node);
		node->left = temp->left;
		node->right = temp->right;
		node->key = temp->key;
		node->val = temp->val;
		node = temp;
		d->size--;
		return SUCCESS;
	}

	//If root has two children, we use the same algorithm for two-child node removal
	else if (node->right != NULL && node->left != NULL) {
		Node* temp = NULL;
		//If the node to the right of the root does not branch left
		if (node->right->left == NULL) {
			temp = node->right;
			temp->left = node->left;
			free(node);
			node->left = temp->left;
			node->right = temp->right;
			node->key = temp->key;
			node->val = temp->val;
			node = temp;
			d->size--;
			return SUCCESS;
		}
		//If the node to the right of the root does branch left, the minimum is found.
		else {
			Node* parentOfMin = findParentOfMin(node->right);
			Node* minNode = parentOfMin->left;
			node->key = minNode->key;
			node->val = minNode->val;
			return removeNonRootNode(d, parentOfMin, minNode->key);
		}
	
	}


}

/***********
*Function Name: performRemoval
*Input: Dictionary*, Node*, int key
*Output: Result
*Function Operation:
	Determines whether node to be removed is a root or non-root node,
	and then calls the relevant function.
*************/
Result performRemoval(Dictionary* d, Node* node, int key) {
	if (key == node->key) {
		return removeRoot(d, node, key);
	}

	else return removeNonRootNode(d, node, key);
}

/***********
*Function Name: isKeyInChild
*Input: Node*, int key
*Output: int
*Function Operation:
	Identifies if the current node is the parent of the node we want to remove.
*************/

int isKeyInChild(Node* node, int key) {
	if (node->key == key) {
		return 1;
	}
	else return 0;
}

/***********
*Function Name: removeNode
*Input: Dictionary*, Node*, int key
*Output: Result
*Function Operation:
	Traverses the tree until it arrives at the parent node of the node to be removed,
	and then it calls performRemoval.
*************/

Result removeNode(Dictionary* d, Node* node, int key) {
	assert(node != NULL);

	//The requested node does not exist in the tree. No change is made
	if (getFromDictionary(d, key) == 0) {
		return FAILURE;
	}

	//If the node to be removed is the root.
	else if (key == node->key) {
		return performRemoval(d, node, key);
	}

	//Traversing the tree to the left to find the parent
	else if (key < node->key) {
		//If the target node is to the right of the current node
		if (node->right != NULL && isKeyInChild(node->right, key)) {
			return performRemoval(d, node, key);
		}
		//If target node is to the left of the current node
		else if (node->left != NULL && isKeyInChild(node->left, key)) {
			return performRemoval(d, node, key);
		}
		//Recurisve call to continue traversing
		else return removeNode(d, node->left, key);
	}

	//Traversing the tree to the right
	else if (key > node->key) {
		//If target node is to the right of the current node
		if (node->right != NULL && isKeyInChild(node->right, key)) {
			return performRemoval(d, node, key);
		}
		//If target node is to the left of the current node
		else if (node->left != NULL && isKeyInChild(node->left, key)) {
			return performRemoval(d, node, key);
		}
		//Recursive call to continue traversing
		else return removeNode(d, node->right, key);
	}

}

/***********
*Function Name: removeFromDictionary
*Input: Dictoinary*, int key
*Output: Result
*Function Operation:
	Begins the process of removing a node from the tree.
*************/

Result removeFromDictionary(Dictionary* d, int key) {
	//If allocation of the dictionary failed.
	if (d == NULL) {
		return MEM_ERROR;
	}

	//If the tree is empty or if allocation of the root failed
	else if (d->root == NULL) {
		return FAILURE;
	}

	//If the root is the only node in the tree
	else if (d->root->key == key && d->root->left == NULL && d->root->right == NULL) {
		free(d->root);
		d->root = NULL;
		d->size = 0;
		return SUCCESS;
	}
	
	//Otherwise, calls removeNode, which will find the target node and ultimately remove.
	else return removeNode(d, d->root, key);
}

/***********
*Function Name: printNodes
*Input: Node*
*Output: void
*Function Operation:
	Uses recursion to traverse the tree and print its nodes.
	Uses the in-order algorithm to print everything in ascending order.
*************/

void printNodes(Node* node) {
	
	//When arrived at a leaf node.
	if (node->left == NULL && node->right == NULL) {
		printf("[%d:%d]", node->key, node->val);
		return;
	}

	/*
	When a node has two children, then a recursive call is used to print
	all the nodes to its left (which are all smaller than it is),
	then the node itself is printed, and then all the nodes to its right
	(which are all larger than it is) are printed.
	*/
	else if (node->left != NULL && node->right != NULL) {
		printNodes(node->left);
		printf("[%d:%d]", node->key, node->val);
		printNodes(node->right);
		return;
	}

	/*
	When the node has only a left child, then all the nodes to its left,
	which are smaller than it is, are printed, and then it is printed.
	*/
	else if (node->left != NULL && node->right == NULL) {
		printNodes(node->left);
		printf("[%d:%d]", node->key, node->val);
		return;
	}

	/*
	When the node has only a right child, it is printed first,
	because it is smaller than all the nodes to its right,
	and then the nodes to its right are printed.
	*/
	else if (node->left == NULL && node->right != NULL) {
		printf("[%d:%d]", node->key, node->val);
		printNodes(node->right);
		return;
	}
}

/***********
*Function Name: printDictionary
*Input: Dictoinary*
*Output: void
*Function Operation:
	Manages the printing of the nodes in the tree
*************/

void printDictionary(Dictionary* d) {
	//If allocation of the tree failed.
	if (d == NULL) {
		printf("{}");
		return;
	}

	//If the tree is empty or if allocation of the root failed.
	if (d->root == NULL) {
		printf("{}");
		return;
	}
	
	//Otherwise, printNodes is called.
	else {
		printf("{");
		printNodes(d->root);
		printf("}");
		return;
	}
}

/***********
*Function Name: createDictionaryFromArrays
*Input: int keys[], int values[], int size
*Output: Dictionary*
*Function Operation:
	Initializes a dictionary and uses a "for" loop to push arrays of keys
	and corresponding values into the tree.
*************/

Dictionary* createDictionaryFromArrays(int keys[], int values[], int size) {
	Dictionary* d = initDictionary();
	//If initializtion of dictionary failed.
	if (d == NULL) {
		return d;
	}

	int i = 0;
	for (i = 0; i < size; i++) {
		Result result = putInDictionary(d, keys[i], values[i]);
		/*
		If at any point the push failed (for example, initialization of a node
		failed), then the operation is aborted and the existing dictionary
		is destroyed and a NULL uninitialized dictionary is returned.
		*/
		if (result != SUCCESS) {
			destroyDictionary(d);
			d = NULL;
			return d;
		}
	}
	
	return d;
}
