/**
 * @file Splay.cpp
 * @author Team 1
 * @brief Implementation of Splay class and its utility functions
 * @date 2026-31-10
 */

 #include "Splay.hpp"

 void SplayTree::replaceInParent(Node *a, Node *b){
    b->parent = a->parent;
		if (a->parent == nullptr) root = b;
		else if (a == a->parent->left) a->parent->left = b;
		else a->parent->right = b;
 }

 void SplayTree::rotateRight(Node *a){
    Node *b = a->left;
		a->left = b->right;
		if (b->right != nullptr){
			b->right->parent = a;
		}
		replaceInParent(a, b);
		b->right = a;
		a->parent = b;
 }

 void SplayTree::rotateLeft(Node *a){
    Node *b = a->right;
		a->right = b->left;
		if (b->left != nullptr){
			b->left->parent = a;
		}
		replaceInParent(a, b);
		b->left = a;
		a->parent = b;
 }

 void SplayTree::splay(Node *x){
    if (x == nullptr) return;
		while (x->parent != nullptr){
			Node *p = x->parent;
			Node *g = p->parent;
			if (g == nullptr){
				if (x == p->left){
					// Zig
					rotateRight(p);
				} else {
					// Zag
					rotateLeft(p);
				}
			} else if (p == g->left){
				if (x == p->left){
					// Zig-zig
					rotateRight(g);
					rotateRight(p);
				} else {
					// Zig-zag
					rotateLeft(p);
					rotateRight(g);
				}	
			} else {
				if (x == p->right){
					// Zag-zag
					rotateLeft(g);
					rotateLeft(p);
				} else {
					// Zag-zig
					rotateRight(p);
					rotateLeft(g);
				}
			}
		}
 }

 Node* SplayTree::lastOnPath(int x) const{
    Node *n = root;
		while (x != n->info) {
			Node *next = (x < n->info) ? n->left : n->right;
			if (next == nullptr) break;
			n = next;
		}
		return n;
 }

 void SplayTree::preorder(Node *n) const{
    if (n == nullptr) return;
		cout << n->info << " ";
		preorder(n->left);
		preorder(n->right);
 }

 void SplayTree::inorder(Node *n) const{
    if (n == nullptr) return;
		inorder(n->left);
		cout << n->info << " ";
		inorder(n->right);
 }

 void SplayTree::destroy(Node *n){
    if (n == nullptr) return;
		destroy(n->left);
		destroy(n->right);
		delete n;
 }

 bool SplayTree::contains(int x){
    if (root == nullptr) return false;
		Node *n = lastOnPath(x);
		splay(n);
		return (n->info == x);
 }

 bool SplayTree::insert(int x){
    if (root == nullptr){
			root = new Node{x, nullptr, nullptr, nullptr};
			return true;
		}
		Node *n = lastOnPath(x);
		if (n->info == x){
			splay(n);
			return false;
		}
		Node *newNode = new Node {x, nullptr, nullptr, n};
		if (x < n->info){
			n->left = newNode;
		} else {
			n->right = newNode;
		}
		splay(newNode);
		return true;
 }

 bool SplayTree::remove(int x){
    if (!contains(x)) return false;

		Node *leftSubtree = root->left;
		Node *rightSubtree = root->right;

		if (leftSubtree != nullptr) leftSubtree->parent = nullptr;
		if (rightSubtree != nullptr) rightSubtree->parent = nullptr;

		Node *toDelete = root;

		if (leftSubtree == nullptr){
			root = rightSubtree;
		} else {
			root = leftSubtree;

			Node *maxNode = lastOnPath(x);
			splay(maxNode);

			root->right = rightSubtree;
			if (rightSubtree != nullptr){
				rightSubtree->parent = root;
			}
		}
		delete toDelete;
		return true;
 }

 void SplayTree::preorder() const {
    preorder(root);
	cout << "\n";
 }

 void SplayTree::inorder() const {
    inorder(root);
	cout << "\n";
 }