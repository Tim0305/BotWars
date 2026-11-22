#ifndef ARCH_HPP
#define ARCH_HPP

#include <vector>

#include "ArcVertex.hpp"
#include "SearchAlgorithms.hpp"

using namespace std;

template <typename T, typename U>
class ArcListGraph {
private:
    struct Arc {
        T from;
        U to;
        int weight;
        Arc* nextOut;
        Arc* nextIn;
    };
    int n;
    vector<T> srcIds;
    vector<U> dstIds;
    vector<ArcVertex<Arc>> g;
    vector<Arc*> arcs;

    int getSrcIndex(const T& value) { return sequentialSearch(srcIds, value); }

    int getDstIndex(const U& value) { return sequentialSearch(srcIds, value); }

public:
    ArcListGraph() {
        n = 0;
        srcIds.resize(n + 1);
        dstIds.resize(n + 1);
        g.resize(n + 1);
    }

    ~ArcListGraph() {
        for (Arc* arc : arcs) delete arc;
    }

    void addEdge(const T& u, const U& v, int weight = 1) {
        int from = getSrcIndex(u);
        int to = getDstIndex(v);

        Arc* arc = new Arc{from, to, weight, g[from].getOut(), g[to].getIn()};
        g[from].setOut(arc);
        g[to].setIn(arc);

        // Update the in-deg and out-deg
        g[from].incrementOutDeg();
        g[to].incrementInDeg();

        arcs.push_back(arc);
    }

    bool hasEdge(const T& u, const U& v) const {
        int from = getSrcIndex(u);
        int to = getDstIndex(v);
        for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
            if (arc->to == to)
                return true;
        return false;
    }

    vector<U> outNeighbors(const T& u) const {
        int from = getSrcIndex(u);
        vector<U> result;
        for (Arc* arc = g[from].getOut(); arc != nullptr; arc = arc->nextOut)
            result.push_back(arc->to);
        return result;
    }

    vector<T> inNeighbors(const U& v) const {
        int to = getDstIndex(v);
        vector<T> result;
        for (Arc* arc = g[to].getIn(); arc != nullptr; arc = arc->nextIn)
            result.push_back(arc->from);
        return result;
    }

    int getOutDegree(const T& u) const {
        int from = getSrcIndex(u);
        return g[from].getOutDeg();
    }

    int getInDegree(const U& v) const {
        int to = getDstIndex(v);
        return g[to].getInDeg();
    }
};

#endif