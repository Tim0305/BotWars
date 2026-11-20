#ifndef ARCVERTEX_HPP
#define ARCVERTEX_HPP

template<typename ArcType>
class ArcVertex {
private:
    ArcType* out = nullptr;
    ArcType* in = nullptr;
    int outDeg = 0;
    int inDeg = 0;

public:
    ArcVertex() = default;

    // Getters
    ArcType* getOut() const { return out; }
    ArcType* getIn() const { return in; }
    int getOutDeg() const { return outDeg; }
    int getInDeg() const { return inDeg; }

    // Setters y modificadores
    void setOut(ArcType* newOut) { out = newOut; }
    void setIn(ArcType* newIn) { in = newIn; }
    void incrementOutDeg() { outDeg++; }
    void incrementInDeg() { inDeg++; }
};

#endif