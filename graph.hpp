#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>
#include <iomanip> 
#include <cstdio>
#include <chrono>
#include <numeric>

using namespace std;

struct Node{
    int index;
    float cost;
};

struct GreaterNode {
    bool operator()(const Node& node1, const Node& node2) const {
        return node1.cost > node2.cost;
    }
};


class Graph{
private:
    int vertices_number;
    vector<vector<Node>> adj_list;
    // Dijkstra attributes
    int source;
    vector<float> distance;
    vector<int> predecessor;
    float eccentricity;
    // Primm attributes
    vector<int> parent;
    vector<float> key;
    unordered_set<int> inMST;
    int getMinKeyVertex();
public:
    Graph(int n);
    void addEdge(int v1, int v2, float weight);
    vector<vector<Node>> getAdjList();
    float getEccentricity();
    friend ostream& operator<<(ostream& os, Graph obj);
    void dijkstra(int source);
    float distanceTo(int v);
    vector<int> pathTo(int v);
    void primMST();
    void printMST(ostream& os);
    float getMSTWeight();
};

#endif