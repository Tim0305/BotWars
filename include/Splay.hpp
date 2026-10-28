/**
 * @file Splay.hpp
 * @brief Header file defining the Splay class
 * @author Team 1
 * @date 2026-31-10
 */

#pragma once

#include <iostream>
using namespace std;

struct Node {
	int info;
	Node *left;
	Node *right;
	Node *parent;
};

class SplayTree{
private:
    Node *root = nullptr;

    friend struct SplayTester;

    void replaceInParent(Node *a, Node *b);
    void rotateRight(Node *a);
    void rotateLeft(Node *a);
    void splay(Node *x);
    Node *lastOnPath(int x) const;
    void preorder(Node *n) const;
    void inorder(Node *n) const;
    void destroy(Node *n);

public:
    SplayTree() = default;
	~SplayTree() { destroy(root); }
        
    SplayTree(const SplayTree &) = delete;
	SplayTree &operator=(const SplayTree &) = delete;

    bool contains(int x);
    bool insert(int x);
    bool remove(int x);
    void preorder() const;
    void inorder() const;

};