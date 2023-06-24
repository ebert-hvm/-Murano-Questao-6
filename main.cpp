#include "graph.hpp"

int main(){
    int n;
    fstream file;

    file.open("grafo_W_3.txt", ios::in);
    file >> n;
    Graph graph(n);

    int v1, v2;
    float weight;
    while(!file.eof()){
        file >> v1 >> v2 >> weight;
        graph.addEdge(v1, v2, weight);
    }
    // cout << graph;
    graph.dijkstra(2);

    cout << setprecision(2) << graph.distanceTo(3) << "\n";
    file.close();
    return 0;
}