#ifndef ARCH_HPP
#define ARCH_HPP

#include <stdexcept>
#include <vector>

#include "ArcVertex.hpp"
#include "SearchAlgorithms.hpp"

using namespace std;

template <typename T>
class ArcListGraph {
private:
    struct Arc {
        int from;
        int to;
        int weight;
        Arc* nextOut;
        Arc* nextIn;
    };
    vector<T> ids;
    vector<ArcVertex<Arc>> g;
    vector<Arc*> arcs;

    int getId(const T& value) const {
        int index = sequentialSearch(ids, value);
        return index == NOT_FOUND ? NOT_FOUND : index + 1;
    }

public:
    ArcListGraph(const ArcListGraph&) = delete;
    ArcListGraph& operator=(const ArcListGraph&) = delete;
    ArcListGraph() { g.resize(1); }

    ~ArcListGraph() {
        for (Arc* arc : arcs) delete arc;
    }

    void addEdge(const T& u, const T& v, int weight = 1) {
        int from = getId(u);

        // Create vertices if they don't exist
        if (from == NOT_FOUND) {
            ids.push_back(u);
            from = ids.size();
            g.resize(ids.size() + 1);
        }

        int to = getId(v);
        if (to == NOT_FOUND) {
            ids.push_back(v);
            to = ids.size();
            g.resize(ids.size() + 1);
        }

        // Check if the edge already exists
        for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
            if (arc->to == to) {
                arc->weight++;
                return;
            }

        // Create new Edge
        Arc* arc = new Arc{from, to, weight, g[from].getOut(), g[to].getIn()};
        g[from].setOut(arc);
        g[to].setIn(arc);

        // Update the in-deg and out-deg
        g[from].incrementOutDeg();
        g[to].incrementInDeg();

        arcs.push_back(arc);
    }

    bool hasEdge(const T& u, const T& v) const {
        int from = getId(u);
        int to = getId(v);

        if (from == NOT_FOUND || to == NOT_FOUND)
            return false;

        for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
            if (arc->to == to)
                return true;
        return false;
    }

    vector<T> outNeighbors(const T& u) const {
        int from = getId(u);
        vector<T> result;

        if (from != NOT_FOUND)
            for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
                result.push_back(ids[arc->to - 1]);
        return result;
    }

    vector<T> inNeighbors(const T& v) const {
        int to = getId(v);
        vector<T> result;
        if (to != NOT_FOUND)
            for (Arc* arc = g[to].getIn(); arc != nullptr; arc = arc->nextIn)
                result.push_back(ids[arc->from - 1]);
        return result;
    }

    int getOutDegree(const T& u) const {
        int from = getId(u);
        if (from == NOT_FOUND)
            throw invalid_argument("Value not found");
        return g[from].getOutDeg();
    }

    int getInDegree(const T& v) const {
        int to = getId(v);
        if (to == NOT_FOUND)
            throw invalid_argument("Value not found");
        return g[to].getInDeg();
    }
};

#endif