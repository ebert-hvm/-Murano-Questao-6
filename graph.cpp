#include "graph.hpp"

Graph::Graph(int vertices_number) : adj_list(vertices_number+5),
    vertices_number(vertices_number), distance(vertices_number + 5){}
vector<vector<Node>> Graph::getAdjList(){ return adj_list;};
void Graph::addEdge(int v1, int v2, float weight){
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
    fill(distance.begin(), distance.end(),numeric_limits<float>::max());
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
    return vector<int>();
}