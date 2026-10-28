/**
 * @file Splay.hpp
 * @brief Header file defining the SplayTree class for network monitoring tracking
 * @author Team 1
 * @date 2026-10-31
 */

#pragma once

#include <iostream>
#include <vector>
#include "IP4.hpp"
#include "IPRecord.hpp"

using namespace std;

struct Node {
	IPRecord data;
	Node *left;
	Node *right;
	Node *parent;

    Node(IPRecord val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree{
private:
    Node *root = nullptr;

    friend struct SplayTester;

    void replaceInParent(Node *a, Node *b);
    void rotateRight(Node *a);
    void rotateLeft(Node *a);
    void splay(Node *x);
    Node *lastOnPath(const IP4& ip) const;
    void destroy(Node *n);

    void collectRecords(Node *n, vector<IPRecord>& outVector) const;

public:
    SplayTree() = default;
	~SplayTree() { destroy(root); }
        
    SplayTree(const SplayTree &) = delete;
	SplayTree &operator=(const SplayTree &) = delete;

    void insertOrUpdate(const IP4& ip, bool success);
    Node* search(const IP4& ip);
    vector<IPRecord> getAllRecords() const;
    bool isEmpty() const { return root == nullptr; }
};