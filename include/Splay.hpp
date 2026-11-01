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

/**
 * @class SplayTree
 * @brief Tree that moves inserted or searched values to the root.
 * @tparam T Any comparable data type.
 * @details Repeated values are not added. The tree cannot be copied.
 * For complexity, n is the number of nodes in the tree.
 */
template <typename T>
class SplayTree {
private:
    /**
     * @brief Stores a value and links to its children and parent.
     */
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
    };

public:
    /**
     * @brief Creates an empty tree.
     * Complexity: O(1).
     */
    SplayTree() = default;

    /**
     * @brief Deletes all nodes in the tree.
     * Complexity: O(n).
     */
    ~SplayTree() { destroy(root); }

    /**
     * @brief Prevents copying the tree.
     */
    SplayTree(const SplayTree&) = delete;

    /**
     * @brief Prevents replacing the tree with a copy of another tree.
     */
    SplayTree& operator=(const SplayTree&) = delete;

    /**
     * @brief Searches for a value and moves the found node to the root.
     * Complexity: amortized O(log n), O(n) in the worst case.
     * @param x Value to search for.
     * @return true If the value is found.
     * @return false Otherwise.
     * @post If the value is not found, the last node visited is moved to the root.
     */
    bool contains(T x) {
        if (root == nullptr)
            return false;

        Node* n = lastOnPath(x);
        splay(n);
        return n->data == x;
    }

    /**
     * @brief Adds a value and moves it to the root.
     * Complexity: amortized O(log n), O(n) in the worst case.
     * @param x Value to insert.
     * @return true If a new value is added.
     * @return false If the value is already in the tree.
     * @post An existing value is moved to the root without being added again.
     */
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

    /**
     * @brief Removes a value from the tree.
     * Complexity: amortized O(log n), O(n) in the worst case.
     * @param x Value to remove.
     * @return true If the value is removed.
     * @return false If the value is not found.
     */
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

    /**
     * @brief Gets the value stored at the root.
     * Complexity: O(1).
     * @return T& The root value, which can be updated.
     * @pre Updates must not change the order of the tree. IPRecord counters may be changed.
     * @throws std::runtime_error If the tree is empty.
     */
    T& getRootValue() {
        if (root == nullptr)
            throw runtime_error("Splay Tree is empty");
        return root->data;
    }

    /**
     * @brief Gets the values by visiting the root, left side and right side.
     * Complexity: O(n).
     * @return vector<T> Values in preorder, or an empty vector if the tree is empty.
     */
    vector<T> preorder() const {
        vector<T> dataList;
        preorder(root, dataList);
        return dataList;
    }

    /**
     * @brief Gets all values in ascending order.
     * Complexity: O(n).
     * @return vector<T> Sorted values, or an empty vector if the tree is empty.
     */
    vector<T> inorder() const {
        vector<T> dataList;
        inorder(root, dataList);
        return dataList;
    }

    /**
     * @brief Gets values between start and end, including both limits.
     * Complexity: O(n).
     * @param start First value in the range.
     * @param end Last value in the range.
     * @return vector<T> Matching values in ascending order, or an empty vector if none match.
     */
    vector<T> inorderRange(T start, T end) const {
        vector<T> dataList;
        inorderRange(root, start, end, dataList);
        return dataList;
    }

    /**
     * @brief Gets the height of the tree.
     * Complexity: O(n).
     * @return int Number of edges on the longest path from the root to a leaf.
     * An empty tree has height -1 and a tree with one node has height 0.
     */
    int height() const { return getHeight(root); }

private:
    Node* root = nullptr;

    /**
     * @brief Replaces a with b under its parent, or at the root.
     * Complexity: O(1).
     * @param a Node to replace.
     * @param b Node that takes its place.
     * @pre Both nodes must exist.
     */
    void replaceInParent(Node* a, Node* b) {
        b->parent = a->parent;
        if (a->parent == nullptr)
            root = b;
        else if (a == a->parent->left)
            a->parent->left = b;
        else
            a->parent->right = b;
    }

    /**
     * @brief Moves the left child above its parent.
     * Complexity: O(1).
     * @param a Parent node to rotate.
     * @post Does nothing if a or its left child does not exist.
     */
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

    /**
     * @brief Moves the right child above its parent.
     * Complexity: O(1).
     * @param a Parent node to rotate.
     * @post Does nothing if a or its right child does not exist.
     */
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

    /**
     * @brief Moves a node to the root using rotations.
     * Complexity: amortized O(log n), O(n) in the worst case.
     * @param x Node to move; does nothing if it does not exist.
     */
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

    /**
     * @brief Finds a value or the last node visited while looking for it.
     * Complexity: O(log n) if the tree is balanced, O(n) in the worst case.
     * @param x Value to search for.
     * @pre The tree must not be empty.
     * @return Node* The matching node, or the last node visited.
     */
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

    /**
     * @brief Adds values by visiting the node, left side and right side.
     * Complexity: O(n).
     * @param n First node to visit.
     * @param dataList Vector where the values are added.
     */
    void preorder(Node* n, vector<T>& dataList) const {
        if (n == nullptr)
            return;
        dataList.push_back(n->data);
        preorder(n->left, dataList);
        preorder(n->right, dataList);
    }

    /**
     * @brief Adds the values below a node in ascending order.
     * Complexity: O(n).
     * @param n First node to visit.
     * @param dataList Vector where the values are added.
     */
    void inorder(Node* n, vector<T>& dataList) const {
        if (n == nullptr)
            return;
        inorder(n->left, dataList);
        dataList.push_back(n->data);
        inorder(n->right, dataList);
    }

    /**
     * @brief Adds values between start and end, including both limits.
     * Complexity: O(n).
     * @param n First node to visit.
     * @param start First value in the range.
     * @param end Last value in the range.
     * @param dataList Vector where matching values are added.
     */
    void inorderRange(Node* n, T start, T end, vector<T>& dataList) const {
        if (n == nullptr)
            return;
        if (n->data >= start) {
            inorderRange(n->left, start, end, dataList);
        }
        if (n->data >= start && n->data <= end) {
            dataList.push_back(n->data);
        }
        if (n->data <= end) {
            inorderRange(n->right, start, end, dataList);
        }
    }

    /**
     * @brief Deletes a node and all nodes below it.
     * Complexity: O(n).
     * @param n First node to delete; does nothing if it does not exist.
     */
    void destroy(Node* n) {
        if (n == nullptr)
            return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    /**
     * @brief Gets the height starting from a node.
     * Complexity: O(n).
     * @param n First node of the part of the tree to measure.
     * @return int Height in edges, or -1 if n does not exist.
     */
    int getHeight(Node* n) const {
        if (n == nullptr)
            return -1;
        return 1 + std::max(getHeight(n->left), getHeight(n->right));
    }
};

#endif
