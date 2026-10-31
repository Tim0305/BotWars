/**
 * @file Splay.hpp
 * @brief Header file defining the SplayTree (bottom-up) class with parent links. Values do not
 * repeat.
 * @author Team 1
 * @date 2026-10-31
 */

#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class SplayTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
    };

public:
    SplayTree() = default;
    ~SplayTree() { destroy(root); }

    // Copying is disabled so that two trees never own the same nodes.
    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    // Searches for x and splays the node where the search ends: x if it is in the tree, otherwise
    // the last node of its search path (lastOnPath gives it). Returns whether x is in the tree. An
    // empty tree returns false. Complexity: amortized O(log n)
    bool contains(T x) {
        if (root == nullptr)
            return false;

        Node* n = lastOnPath(x);
        splay(n);
        return n->data == x;
    }

    // Inserts x as in a BST, as a new leaf, and splays the new node. Returns true.
    // lastOnPath(x) gives the node that holds x, or the node where x must hang. A repeated value
    // adds no node: it splays the node that already holds x and returns false. Set the parent of
    // the new node. Complexity: amortized O(log n)
    bool insert(T x) {
        if (root == nullptr) {
            root = new Node{x, nullptr, nullptr, nullptr};
            return true;
        }

        Node* n = lastOnPath(x);
        if (n->data == x) {
            splay(n);
            return false;
        }

        Node* newNode = new Node{x, nullptr, nullptr, n};
        if (x > n->data)
            n->right = newNode;
        else
            n->left = newNode;
        splay(newNode);
        return true;
    }

    // Removes x. First contains(x): if x is not there, returns false (the tree was still splayed).
    // Otherwise x is the root: delete it, and TL and TR, its two subtrees, become separate trees.
    // With no TL, TR is the whole tree. Otherwise make TL the tree, splay its maximum
    // (lastOnPath(x) finds it, because x is greater than every key of TL), and hang TR as the right
    // child of the new root. Keep every parent link correct. Returns true. Complexity: amortized
    // O(log n)
    bool remove(T x) {
        if (!contains(x))
            return false;

        Node* TL = root->left;
        Node* TR = root->right;
        delete root;

        if (TL == nullptr) {
            root = TR;
            if (TR != nullptr)
                TR->parent = nullptr;
        } else {
            TL->parent = nullptr;
            Node* max = TL;
            while (max->right != nullptr) max = max->right;
            splay(max);  // Moves max to the root
            root = max;
            max->right = TR;
            if (TR != nullptr)
                TR->parent = max;
        }

        return true;
    }

    T& getRootValue() {
        if (root == nullptr)
            throw runtime_error("Splay Tree is empty");
        return root->data;
    }

    // The public methods that print also end the line.
    vector<T> preorder() const {
        vector<T> dataList;
        preorder(root, dataList);
        return dataList;
    }

    vector<T> inorder() const {
        vector<T> dataList;
        inorder(root, dataList);
        return dataList;
    }

private:
    Node* root = nullptr;

    // b takes the place of a: under the parent of a, or as the root.
    void replaceInParent(Node* a, Node* b) {
        b->parent = a->parent;
        if (a->parent == nullptr)
            root = b;
        else if (a == a->parent->left)
            a->parent->left = b;
        else
            a->parent->right = b;
    }

    // Rotates right at a: b, the left child of a, rises and a goes down to its right. The right
    // subtree of b becomes the left subtree of a. Keep every parent link correct; replaceInParent
    // puts b where a was (it also updates root when a was the root). Complexity: O(1)
    void rotateRight(Node* a) {
        if (a == nullptr || a->left == nullptr)
            return;

        Node* b = a->left;
        a->left = b->right;
        if (b->right != nullptr)
            b->right->parent = a;
        b->right = a;
        replaceInParent(a, b);
        a->parent = b;
    }

    // The mirror image: the right child of a rises and a goes down to its left.
    // Complexity: O(1)
    void rotateLeft(Node* a) {
        if (a == nullptr || a->right == nullptr)
            return;

        Node* b = a->right;
        a->right = b->left;
        if (b->left != nullptr)
            b->left->parent = a;
        b->left = a;
        replaceInParent(a, b);
        a->parent = b;
    }

    // Moves x to the root. While x has a parent P, look at its grandparent G and apply the case:
    //   no G:                          zig (rotate right at P) or zag (rotate left at P)
    //   P is the left child of G:      zig-zig (right at G, then right at P) or zig-zag (left at P,
    //   then right at G) P is the right child of G:     zag-zag (left at G, then left at P) or
    //   zag-zig (right at P, then left at G)
    // Complexity: amortized O(log n)
    void splay(Node* x) {
        if (x == nullptr)
            return;
        while (x->parent != nullptr) {
            Node* P = x->parent;
            Node* G = P->parent;
            if (G != nullptr) {
                if (G->left == P) {
                    if (P->left == x) {
                        // zig-zig
                        rotateRight(G);
                        rotateRight(P);
                    } else {
                        // zig-zag
                        rotateLeft(P);
                        rotateRight(G);
                    }
                } else {
                    if (P->left == x) {
                        // zag-zig
                        rotateRight(P);
                        rotateLeft(G);
                    } else {
                        // zag-zag
                        rotateLeft(G);
                        rotateLeft(P);
                    }
                }

            } else if (P->left == x)
                // zig
                rotateRight(P);
            else
                // zag
                rotateLeft(P);
        }
    }

    // Returns the node with x, or the last node of the search path of x. root is not null.
    Node* lastOnPath(T x) const {
        Node* n = root;
        while (x != n->data) {
            Node* next = (x < n->data) ? n->left : n->right;
            if (next == nullptr)
                break;
            n = next;
        }
        return n;
    }

    void preorder(Node* n, vector<T>& dataList) const {
        if (n == nullptr)
            return;
        dataList.push_back(n->data);
        preorder(n->left, dataList);
        preorder(n->right, dataList);
    }

    void inorder(Node* n, vector<T>& dataList) const {
        if (n == nullptr)
            return;
        inorder(n->left, dataList);
        dataList.push_back(n->data);
        inorder(n->right, dataList);
    }

    void destroy(Node* n) {
        if (n == nullptr)
            return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
};

#endif
