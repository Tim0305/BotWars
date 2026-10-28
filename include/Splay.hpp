/**
 * @file Splay.hpp
 * @brief Header file defining the SplayTree class for network monitoring tracking
 * @author Team 1
 * @date 2026-10-31
 */

#pragma once

#include <vector>

#include "IP4.hpp"
#include "IPRecord.hpp"

/**
 * @class SplayTree
 * @brief Self-adjusting binary search tree that stores one IPRecord per IP address.
 *
 * @details Every insertion or search moves the visited IP to the root (splaying), so recently
 * used IPs are found faster. The amortized cost per operation is O(log n), although a single
 * operation can take O(n) (e.g. after inserting IPs in ascending order the tree is a chain).
 */
class SplayTree {
private:
    struct Node {
        IPRecord data;
        Node* left;
        Node* right;
        Node* parent;

        explicit Node(const IPRecord& val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;

    friend struct SplayTester;

    void replaceInParent(Node* a, Node* b);
    void rotateRight(Node* a);
    void rotateLeft(Node* a);
    void splay(Node* x);
    Node* lastOnPath(const IP4& ip) const;
    void destroy(Node* n);

    void collectRecords(Node* n, std::vector<IPRecord>& outVector) const;

public:
    SplayTree() = default;
    ~SplayTree() { destroy(root); }

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    /**
     * @brief Registers an access of an IP, creating its record if it does not exist yet.
     * @param ip The IP address that made the access.
     * @param success Whether the access was successful (Accepted).
     */
    void insertOrUpdate(const IP4& ip, bool success);

    /**
     * @brief Searches the record of an IP and moves it to the root of the tree.
     * @param ip The IP address to look for.
     * @return const IPRecord* The record, or nullptr if the IP is not in the tree.
     * @warning The pointer is only valid until the next insertOrUpdate or search call.
     */
    const IPRecord* search(const IP4& ip);

    /**
     * @brief Returns all the records sorted by IP address.
     */
    std::vector<IPRecord> getAllRecords() const;

    bool isEmpty() const { return root == nullptr; }
};