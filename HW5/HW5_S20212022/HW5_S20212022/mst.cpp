#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>
#include <chrono>

using namespace std;

struct Edge {
    int u, v;
    long long weight;
    Edge(int u, int v, long long weight) : u(u), v(v), weight(weight) {}
};

class MinHeap {
private:
    vector<Edge> heap;

    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[idx].weight < heap[parent].weight) {
                std::swap(heap[idx], heap[parent]);
                idx = parent;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int idx) {
        int size = (int)heap.size();
        while (true) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;

            if (left < size && heap[left].weight < heap[smallest].weight) {
                smallest = left;
            }
            if (right < size && heap[right].weight < heap[smallest].weight) {
                smallest = right;
            }
            if (smallest != idx) {
                std::swap(heap[idx], heap[smallest]);
                idx = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    MinHeap() {}

    bool empty() const {
        return heap.empty();
    }

    void push(const Edge& e) {
        heap.push_back(e);
        heapifyUp((int)heap.size() - 1);
    }

    Edge pop() {
        if (heap.empty()) {
            throw std::runtime_error("MinHeap is empty - cannot pop");
        }
        Edge top = heap[0];

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }
        return top;
    }
};

class DisjointSet {
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            }
            else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            }
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

struct ComponentInfo {
    int numVerts;
    long long totalWeight;
};

int compareComponents(const void* a, const void* b) {
    const ComponentInfo* c1 = (const ComponentInfo*)a;
    const ComponentInfo* c2 = (const ComponentInfo*)b;

    if (c1->numVerts < c2->numVerts) return -1;
    if (c1->numVerts > c2->numVerts) return 1;

    if (c1->totalWeight < c2->totalWeight) return -1;
    if (c1->totalWeight > c2->totalWeight) return 1;

    return 0;
}

int main() {
    ifstream commandsFile("commands.txt");
    if (!commandsFile.is_open()) {
        cerr << "commands.txt 파일을 열 수 없습니다." << endl;
        return 1;
    }

    string inputDirectory;
    string inputGraphFile;
    string outputFile;

    if (!getline(commandsFile, inputDirectory)) {
        cerr << "commands.txt에서 첫 번째 줄을 읽을 수 없습니다." << endl;
        return 1;
    }
    if (!getline(commandsFile, inputGraphFile)) {
        cerr << "commands.txt에서 두 번째 줄을 읽을 수 없습니다." << endl;
        return 1;
    }
    if (!getline(commandsFile, outputFile)) {
        cerr << "commands.txt에서 세 번째 줄을 읽을 수 없습니다." << endl;
        return 1;
    }

    commandsFile.close();

    string inputFilePath = inputDirectory;
    if (!inputFilePath.empty() &&
        (inputFilePath.back() != '\\' && inputFilePath.back() != '/')) {
        inputFilePath += '\\';
    }
    inputFilePath += inputGraphFile;

    ifstream graphFile(inputFilePath);
    if (!graphFile.is_open()) {
        cerr << "입력 그래프 파일을 열 수 없습니다: " << inputFilePath << endl;
        return 1;
    }

    vector<Edge> edges;
    unordered_set<int> vertexSet;

    int cnt = 0;
    string line;
    while (getline(graphFile, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        int src, dest;
        long long w;
        if (!(iss >> src >> dest >> w)) {
            continue;
        }

        if (!cnt) {
            cnt = 1;
            continue;
        }
        edges.emplace_back(src, dest, w);

        vertexSet.insert(src);
        vertexSet.insert(dest);
    }
    graphFile.close();

    int V = static_cast<int>(vertexSet.size());
    if (V == 0) {
        cerr << "그래프에 정점이 없습니다." << endl;
        return 1;
    }

    int maxVertex = 0;
    for (int v : vertexSet) {
        if (v > maxVertex) maxVertex = v;
    }
    DisjointSet ds(maxVertex + 1);

    auto startTime = std::chrono::steady_clock::now();

    MinHeap minHeap;
    for (auto& e : edges) {
        minHeap.push(e);
    }

    vector<Edge> mstEdges;
    mstEdges.reserve(edges.size());

    int kscanned = 0;

    while (!minHeap.empty()) {
        Edge edge = minHeap.pop();

        int u = edge.u;
        int v = edge.v;
        long long w = edge.weight;

        if (ds.find(u) != ds.find(v)) {
            ds.unionSets(u, v);
            mstEdges.push_back(edge);
            kscanned++;  
        }
    }

    auto endTime = std::chrono::steady_clock::now();
    double elapsedSec = std::chrono::duration<double>(endTime - startTime).count();

    unordered_map<int, vector<int>> components;
    for (int v : vertexSet) {
        int root = ds.find(v);
        components[root].push_back(v);
    }

    unordered_map<int, long long> compWeight;
    for (auto& edge : mstEdges) {
        int rootU = ds.find(edge.u);
        compWeight[rootU] += edge.weight;
    }

    int numComponents = static_cast<int>(components.size());

    vector<ComponentInfo> compInfos;
    compInfos.reserve(numComponents);
    for (auto& kv : components) {
        int root = kv.first;
        int numVerts = (int)kv.second.size();
        long long totalWeight = compWeight[root];
        compInfos.push_back({ numVerts, totalWeight });
    }

    qsort(
        compInfos.data(),
        compInfos.size(),
        sizeof(ComponentInfo),
        compareComponents
    );

    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cerr << "출력 파일을 열 수 없습니다: " << outputFile << endl;
        return 1;
    }

    outFile << numComponents << "\n";
    for (auto& ci : compInfos) {
        outFile << ci.numVerts << " " << ci.totalWeight << "\n";
    }

    outFile.close();

    cout << "MST(혹은 MSF) 결과가 성공적으로 저장되었습니다: " << outputFile << endl;
    cout << "수행 시간 (초): " << elapsedSec << endl;
    cout << "kscanned: " << kscanned << endl;

    return 0;
}
