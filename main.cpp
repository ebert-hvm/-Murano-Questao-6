#include "graph.hpp"

int main(){
    int n;
    fstream file;

    file.open("grafo_W_2.txt", ios::in);
    file >> n;
    Graph graph(n);

    int v1, v2;
    float weight;
    while(!file.eof()){
        file >> v1 >> v2 >> weight;
        graph.addEdge(v1, v2, weight);
    }
    // cout << graph;
    int source, dest;
    cin >> source >> dest;
    graph.dijkstra(source);

    cout << "distance: " << graph.distanceTo(dest) << "\n";
    cout << "path: ";
    for(const int & v : graph.pathTo(dest)) cout << v << " ";
    cout << "\n";

    file.close();
    return 0;
}