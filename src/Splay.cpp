/**
 * @file Splay.cpp
 * @author Team 1
 * @brief Implementation of SplayTree class and its utility functions
 * @date 2026-10-31
 */

#include "Splay.hpp"

using std::vector;

/**
 * @brief Replaces node a with node b in relation to its parent.
 */
void SplayTree::replaceInParent(Node* a, Node* b) {
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
void SplayTree::rotateRight(Node* a) {
    Node* b = a->left;
    a->left = b->right;
    if (b->right != nullptr) {
        b->right->parent = a;
    }
    replaceInParent(a, b);
    b->right = a;
    a->parent = b;
}

/**
 * @brief Performs a left rotation around node a.
 */
void SplayTree::rotateLeft(Node* a) {
    Node* b = a->right;
    a->right = b->left;
    if (b->left != nullptr) {
        b->left->parent = a;
    }
    replaceInParent(a, b);
    b->left = a;
    a->parent = b;
}

/**
 * @brief Brings node x to the root using splay operations (Zig, Zig-Zig, Zig-Zag).
 */
void SplayTree::splay(Node* x) {
    if (x == nullptr) return;
    while (x->parent != nullptr) {
        Node* p = x->parent;
        Node* g = p->parent;
        if (g == nullptr) {
            if (x == p->left) {
                // Zig
                rotateRight(p);
            } else {
                // Zag
                rotateLeft(p);
            }
        } else if (p == g->left) {
            if (x == p->left) {
                // Zig-zig
                rotateRight(g);
                rotateRight(p);
            } else {
                // Zig-zag
                rotateLeft(p);
                rotateRight(g);
            }
        } else {
            if (x == p->right) {
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
SplayTree::Node* SplayTree::lastOnPath(const IP4& ip) const {
    if (!root) return nullptr;

    Node* curr = root;
    Node* prev = nullptr;

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
 * @brief Searches for an IP, brings it to the root via splay, and returns its record.
 */
const IPRecord* SplayTree::search(const IP4& ip) {
    Node* node = lastOnPath(ip);
    if (node) {
        splay(node);
    }
    return (node && node->data.ip == ip) ? &node->data : nullptr;
}

/**
 * @brief Inserts a new IP or updates its counters if it already exists, splaying it to the root.
 */
void SplayTree::insertOrUpdate(const IP4& ip, bool success) {
    if (!root) {
        root = new Node(IPRecord(ip, success));
        return;
    }

    Node* node = lastOnPath(ip);
    splay(node);  // Splay the last node visited on the path to root

    if (node->data.ip == ip) {
        // IP exists, counters are updated
        node->data.registerAccess(success);
    } else {
        // IP doesn't exist, we create new node and insert it as the new root
        Node* newNode = new Node(IPRecord(ip, success));
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
        root = newNode;  // New node goes up to the root
    }
}

/**
 * @brief Collects all records in-order (iteratively, so a very deep tree cannot overflow the stack).
 */
void SplayTree::collectRecords(Node* n, vector<IPRecord>& outVector) const {
    vector<Node*> pending;
    Node* curr = n;

    while (curr || !pending.empty()) {
        while (curr) {
            pending.push_back(curr);
            curr = curr->left;
        }
        curr = pending.back();
        pending.pop_back();
        outVector.push_back(curr->data);
        curr = curr->right;
    }
}

/**
 * @brief Returns all IP records stored in the tree, sorted by IP address.
 */
vector<IPRecord> SplayTree::getAllRecords() const {
    vector<IPRecord> records;
    collectRecords(root, records);
    return records;
}

/**
 * @brief Destroys the tree to free memory (iteratively, so a very deep tree cannot overflow the stack).
 */
void SplayTree::destroy(Node* n) {
    vector<Node*> pending;
    if (n) pending.push_back(n);

    while (!pending.empty()) {
        Node* curr = pending.back();
        pending.pop_back();
        if (curr->left) pending.push_back(curr->left);
        if (curr->right) pending.push_back(curr->right);
        delete curr;
    }
}