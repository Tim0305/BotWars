#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ArcListGraph {
    // Define Vertex/Arc and store them.
    int n;
    struct Arc {
        int from, to;
        Arc* nextOut;
        Arc* nextIn;
    };

    struct Vertex {
        Arc* out = nullptr;
        Arc* in = nullptr;
    };
    vector<Vertex> vertices;
public:
    explicit ArcListGraph(int n) {
        // your code here
        this->n = n;
        this->vertices.resize(n + 1);
    }

    void addEdge(int u, int v) {
        // your code here
        Arc* arc = new Arc{u, v, vertices[u].out, vertices[v].in};
        vertices[u].out = arc;
        vertices[v].in = arc;
    }

    bool hasEdge(int u, int v) const {
        // your code here
        for (Arc* arc = vertices[u].out; arc != nullptr; arc = arc->nextOut){
            if (arc->to == v) return true;
        }
        return false;
    }

    vector<int> outNeighbors(int u) const {
        // your code here
        vector<int> result;
        for (Arc* arc = vertices[u].out; arc != nullptr; arc = arc->nextOut){
            result.push_back(arc->to);
        }
        return result;
    }

    vector<int> inNeighbors(int v) const {
        // your code here
         vector<int> result;
        for (Arc* arc = vertices[v].in; arc != nullptr; arc = arc->nextIn){
            result.push_back(arc->from);
        }
        return result;
    }
};