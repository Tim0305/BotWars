#ifndef ARCH_HPP
#define ARCH_HPP

#include <vector>
#include "ArcVertex.hpp"

using namespace std;

template<typename T, typename U>
class ArcListGraph {
private:
    int n;

    struct Arc {
        T from;          // Se corrigió el punto y coma faltante
        U to;
        int weight;
        Arc* nextOut;
        Arc* nextIn;
    };

    vector<ArcVertex<Arc>> vertices;

public:
    explicit ArcListGraph(int n) {
        this->n = n;
        this->vertices.resize(n + 1);
    }

    // Se agregó un valor por defecto para weight (1) y se usan los tipos T y U
    void addEdge(T u, U v, int weight = 1) {
        Arc* arc = new Arc{u, v, weight, vertices[u].getOut(), vertices[v].getIn()};
        vertices[u].setOut(arc);
        vertices[v].setIn(arc);
        
        // Actualizamos los grados de entrada y salida
        vertices[u].incrementOutDeg();
        vertices[v].incrementInDeg();
    }

    bool hasEdge(T u, U v) const {
        for (Arc* arc = vertices[u].getOut(); arc != nullptr; arc = arc->nextOut) {
            if (arc->to == v) return true;
        }
        return false;
    }

    vector<U> outNeighbors(T u) const {
        vector<U> result;
        for (Arc* arc = vertices[u].getOut(); arc != nullptr; arc = arc->nextOut) {
            result.push_back(arc->to);
        }
        return result;
    }

    vector<T> inNeighbors(U v) const {
        vector<T> result;
        for (Arc* arc = vertices[v].getIn(); arc != nullptr; arc = arc->nextIn) {
            result.push_back(arc->from);
        }
        return result;
    }

    // Métodos opcionales para consultar los grados aprovechando los atributos de ArcVertex
    int getOutDegree(T u) const {
        return vertices[u].getOutDeg();
    }

    int getInDegree(U v) const {
        return vertices[v].getInDeg();
    }
};

#endif