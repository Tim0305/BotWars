/**
 * @file Splay.cpp
 * @author Team 1
 * @brief Implementation of SplayTree class and its utility functions
 * @date 2026-31-10
 */

 #include "Splay.hpp"


 /**
 * @brief Replaces node a with node b in relation to its parent.
 */
 void SplayTree::replaceInParent(Node *a, Node *b){
   if (!a->parent) {
        root = b;
    } else if (a == a->parent->left) {
        a->parent->left = b;
    } else {
        a->parent->right = b;
    }
    if (b) {
        b->parent = a->parent;
    }
 }

 /**
 * @brief Performs a right rotation around node a.
 */
 void SplayTree::rotateRight(Node *a){
    Node *b = a->left;
	a->left = b->right;
	if (b->right != nullptr){
		b->right->parent = a;
	}
	b->parent = a->parent;
	replaceInParent(a, b);
	b->right = a;
	a->parent = b;
 }

 /**
 * @brief Performs a left rotation around node a.
 */
 void SplayTree::rotateLeft(Node *a){
    Node *b = a->right;
	a->right = b->left;
	if (b->left != nullptr){
		b->left->parent = a;
	}
	b->parent = a->parent;
	replaceInParent(a, b);
	b->left = a;
	a->parent = b;
 }

 /**
 * @brief Brings node x to the root using splay operations (Zig, Zig-Zig, Zig-Zag).
 */
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

 /**
 * @brief Finds the node matching the IP or returns the last node on the path (for insertion).
 */
 Node* SplayTree::lastOnPath(const IP4& ip) const{
    if (!root) return nullptr;

    Node *curr = root;
    Node *prev = nullptr;

    while (curr) {
        prev = curr;
        if (ip == curr->data.ip) {
            return curr;
        } else if (ip < curr->data.ip) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return prev;
 }

/**
 * @brief Searches for an IP, brings it to the root via splay, and returns its node pointer.
 */
Node* SplayTree::search(const IP4& ip) {
    Node *node = lastOnPath(ip);
    if (node) {
        splay(node);
    }
    return (node && node->data.ip == ip) ? root : nullptr;
}

/**
 * @brief Inserts a new IP or updates its counters if it already exists, splaying it to the root.
 */
void SplayTree::insertOrUpdate(const IP4& ip, bool success){
	if (!root) {
        root = new Node(IPRecord(ip, success));
        return;
    }

    Node *node = lastOnPath(ip);
    splay(node); // Splay the last node visited on the path to root

    if (node->data.ip == ip) {
        // IP exists, counters are updated
        node->data.totalAccesses++;
        if (success) {
            node->data.successfulAccesses++;
        }
    } else {
        // IP doesn't exist, we create new node and insert it as  a child
        Node *newNode = new Node(IPRecord(ip, success));
        if (ip < node->data.ip) {
            newNode->left = node->left;
            newNode->right = node;
            if (node->left) {
                node->left->parent = newNode;
            }
            node->left = nullptr;
        } else {
            newNode->right = node->right;
            newNode->left = node;
            if (node->right) {
                node->right->parent = newNode;
            }
            node->right = nullptr;
        }
        node->parent = newNode;
        root = newNode; // New node goes up to the root
    }
}

/**
 * @brief Recursively collects all records in-order.
 */
void SplayTree::collectRecords(Node *n, vector<IPRecord>& outVector) const {
    if (!n) return;
    collectRecords(n->left, outVector);
    outVector.push_back(n->data);
    collectRecords(n->right, outVector);
}

/**
 * @brief Returns all IP records stored in the tree.
 */
vector<IPRecord> SplayTree::getAllRecords() const {
    vector<IPRecord> records;
    collectRecords(root, records);
    return records;
}

/**
 * @brief Recursively destroys the tree to free memory.
 */
 void SplayTree::destroy(Node *n){
    if (n == nullptr) return;
		destroy(n->left);
		destroy(n->right);
		delete n;
 }

 
