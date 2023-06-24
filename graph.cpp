#include "graph.hpp"

Graph::Graph(int vertices_number) : vertices_number(vertices_number),
    adj_list(vertices_number+5), distance(vertices_number + 5),
    predecessor(vertices_number + 5){}
vector<vector<Node>> Graph::getAdjList(){ return adj_list;};
void Graph::addEdge(int v1, int v2, float weight){
    if(weight < 0) throw invalid_argument("Negative weight is not allowed.");
    if (v1 <= 0 || v1 > vertices_number || v2 <= 0 || v2 > vertices_number) {
        throw std::out_of_range("Vertex index is out of range.");
    }

    Node nd1 = {v1, weight}, nd2 = {v2, weight};
    adj_list[v1].push_back(nd2);
    adj_list[v2].push_back(nd1);
}

ostream& operator<<(ostream& os, Graph obj){
    vector<vector<Node>> vec = obj.getAdjList();
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].size()){
            os << i << " :\n";
            for(const auto& nd : vec[i]){
                os << nd.index << ", "<< nd.cost << "\n";
            }
        }
    }
    return os;
    
}

void Graph::dijkstra(int source){
    this->source = source;
    fill(distance.begin(), distance.end(),numeric_limits<float>::max());
    fill(predecessor.begin(), predecessor.end(), -1);
    distance[source] = 0;
    priority_queue<Node, vector<Node>, GreaterNode> pq;
    pq.push({source, 0});
    int u;
    while(!pq.empty()){
        u = pq.top().index;
        // cout << "atual: " << u << "\n";
        pq.pop();
        for(const auto& nd : adj_list[u]){
            int v = nd.index;
            float weight = nd.cost;
            //cout << "vizinho: " << v << " ";
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                predecessor[v] = u;
                pq.push({v, distance[v]});
              //  cout << "foi "<< distance[v] <<"\n";
            } // else cout << "nao foi\n";
        }
    }
}

float Graph::distanceTo(int v){
    return distance[v];
}

vector<int> Graph::pathTo(int v){
    vector<int> path;
    while (v != -1) {
        path.push_back(v);
        v = predecessor[v];
    }

    reverse(path.begin(), path.end());
    return path;
}