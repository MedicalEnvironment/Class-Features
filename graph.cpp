#include <iostream>
#include <vector>
#include <unordered_set>

class IGraph {
public:
    virtual ~IGraph() {}
    IGraph() {}
    IGraph(IGraph* _oth) {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int numVertices) : adjacencyLists(numVertices) {}

    void AddEdge(int from, int to) override {
        adjacencyLists[from].insert(to);
    }

    int VerticesCount() const override {
        return adjacencyLists.size();
    }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override {
        vertices.clear();
        for (const auto& adjacentVertex : adjacencyLists[vertex]) {
            vertices.push_back(adjacentVertex);
        }
    }

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override {
        vertices.clear();
        for (int i = 0; i < adjacencyLists.size(); ++i) {
            for (const auto& adjacentVertex : adjacencyLists[i]) {
                if (adjacentVertex == vertex) {
                    vertices.push_back(i);
                }
            }
        }
    }

private:
    std::vector<std::unordered_set<int>> adjacencyLists;
};

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int numVertices) : adjacencyMatrix(numVertices, std::vector<bool>(numVertices, false)) {}

    void AddEdge(int from, int to) override {
        adjacencyMatrix[from][to] = true;
    }

    int VerticesCount() const override {
        return adjacencyMatrix.size();
    }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override {
        vertices.clear();
        for (int i = 0; i < adjacencyMatrix[vertex].size(); ++i) {
            if (adjacencyMatrix[vertex][i]) {
                vertices.push_back(i);
            }
        }
    }

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override {
        vertices.clear();
        for (int i = 0; i < adjacencyMatrix.size(); ++i) {
            if (adjacencyMatrix[i][vertex]) {
                vertices.push_back(i);
            }
        }
    }

private:
    std::vector<std::vector<bool>> adjacencyMatrix;
};

int main() {
    // Test ListGraph
    ListGraph listGraph(5);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(2, 3);
    listGraph.AddEdge(3, 4);

    std::vector<int> nextVertices;
    listGraph.GetNextVertices(2, nextVertices);
    std::cout << "Next vertices for 2: ";
    for (const auto& vertex : nextVertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::vector<int> prevVertices;
    listGraph.GetPrevVertices(2, prevVertices);
    std::cout << "Prev vertices for 2: ";
    for (const auto& vertex : prevVertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    // Test MatrixGraph
    MatrixGraph matrixGraph(5);
    matrixGraph.AddEdge(0, 1);
    matrixGraph.AddEdge(1, 2);
    matrixGraph.AddEdge(2, 3);
    matrixGraph.AddEdge(3, 4);

    matrixGraph.GetNextVertices(2, nextVertices);
    std::cout << "Next vertices for 2: ";
    for (const auto& vertex : nextVertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    matrixGraph.GetPrevVertices(2, prevVertices);
    std::cout << "Prev vertices for 2: ";
    for (const auto& vertex : prevVertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    return 0;
}
