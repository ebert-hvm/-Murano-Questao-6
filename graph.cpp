#include "graph.hpp"


Graph::Graph(int vertices_number) : vertices_number(vertices_number),
    adj_list(vertices_number+5), distance(vertices_number + 5),
    predecessor(vertices_number + 5), key(vertices_number + 5),
    parent(vertices_number + 5){}
vector<vector<Node>> Graph::getAdjList(){ return adj_list;};
void Graph::addEdge(int v1, int v2, float weight){
    if(weight < 0) throw invalid_argument("Negative weight is not allowed.");
    if (v1 <= 0 || v1 > vertices_number || v2 <= 0 || v2 > vertices_number) {
        throw out_of_range("Vertex index is out of range.");
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
                eccentricity = max(eccentricity, distance[v]);
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

float Graph::getEccentricity(){
    return eccentricity;
}

void Graph::printMST(ostream& os){
    float total = 0;
    os << "Edge" << setw(10) << "Weight" << "\n";
    for (int i = 2; i <= vertices_number; i++) {
        os << parent[i] << " - " << i << setw(10) << fixed << setprecision(2) << key[i] << "\n";
        total += key[i];
    }
    os << "total weight: " << total << "\n";
}

float Graph::getMSTWeight(){
    return accumulate(key.begin() + 2, key.begin() + vertices_number + 1, 0.0f);
}

void Graph::primMST() {
    fill(key.begin(), key.end(), numeric_limits<float>::max());
    fill(parent.begin(), parent.end(), -1);
    // vertex 1 is the root
    key[1] = 0;

    priority_queue<Node, vector<Node>, GreaterNode> pq;
    pq.push({1, 0});

    while (!pq.empty()) {
        int u = pq.top().index;
        pq.pop();
        inMST.insert(u);

        for (const auto& nd : adj_list[u]) {
            int v = nd.index;
            float weight = nd.cost;

            if (!inMST.count(v) && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push({v, key[v]});
            }
        }
    }
}

int Graph::getMinKeyVertex(){
    float min_key = numeric_limits<float>::max();
    int min_index = -1;

    for (int v = 1; v <= vertices_number; v++) {
        if (!inMST.count(v) && key[v] < min_key) {
            min_key = key[v];
            min_index = v;
        }
    }

    return min_index;
}