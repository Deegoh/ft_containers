#include <iostream>

enum Color {RED, BLACK};

struct Node {
	int value;
	Color color;
	Node *left;
	Node *right;
	Node *parent;
	Node(int v) : value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
	Node *root;
	Node *nil;

	void leftRotate(Node *&, Node *&);
	void rightRotate(Node *&, Node *&);
	void insertFixup(Node *&, Node *&);
	void transplant(Node *&, Node *&, Node *&);
	void deleteFixup(Node *&, Node *&);
	Node* minimum(Node *&);
	Node* maximum(Node *&);
	Node* successor(Node *&);
	Node* predecessor(Node *&);
	void inorder(Node *&);

public:
	RedBlackTree();
	void insert(int);
	void remove(int);
	Node* search(int);
	Node* getRoot();
	void inorder();
};git pu