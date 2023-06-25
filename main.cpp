#include "graph.hpp"

int main(int argc, char *argv[]){
    if(argc <= 1){
        cout << "Please add some graph input files\n";
        return 0;
    }
    int n, v1, v2, source = 1;
    float weight;
    fstream file;
    ofstream result_stream, mst_stream;
    vector<string> filePath = {"grafo_W_1", "grafo_W_2", "grafo_W_3"};
    vector<int> destVertices = {10, 20, 30, 40, 50};
    chrono::steady_clock sc;
    auto start = sc.now();
    auto end = sc.now();
    chrono::duration<float> time_span;
    result_stream.open("result.txt", ios::out);
    for(int i=1;i<argc;i++){
        string filename(argv[i]);
        file.open(filename, ios::in);
        if (file.bad() || !file.is_open()){
            cout << "Invalid path to file\n";
            return 0;
        }

        size_t dotPos = filename.find('.');
        if (dotPos != std::string::npos) filename = filename.substr(0, dotPos);

        result_stream << filename << ":\n";
        file >> n;
        Graph graph(n);
        while(!file.eof()){
            file >> v1 >> v2 >> weight;
            graph.addEdge(v1, v2, weight);
        }
        file.close();

        start = sc.now();
        graph.dijkstra(source);
        end = sc.now();
        time_span = end - start;

        result_stream << "Source: "<< source << "\n";
        result_stream << "Dijkstra execution time: " << setprecision(6) << time_span.count() << "\n\n";
        if(n >= *max_element(destVertices.begin(), destVertices.end())){
            for(const int& dest : destVertices){
                result_stream << "Destiny: " << dest << "\n";
                result_stream << "Distance: " << graph.distanceTo(dest) << "\n";
                result_stream << "Path: ";
                bool first = true;
                for(const int & v : graph.pathTo(dest)){
                    if(!first) result_stream << "->";
                    else first = false;
                    result_stream << v;
                }
                result_stream << "\n\n";
            }
        }
        string mst_file = filename + "_MST.txt" ;
        result_stream << "Minimum spanning tree: \nOn file " << mst_file << "\n";
        start = sc.now();
        graph.primMST();
        end = sc.now();
        time_span = end - start;
        result_stream << "Prim execution time: " << setprecision(6) << time_span.count() << "\n";
        mst_stream.open(mst_file, ios::out);
        graph.printMST(mst_stream);
        mst_stream.close();
        result_stream << "MST weight: " << graph.getMSTWeight() << "\n\n";
        if(n >= *max_element(destVertices.begin(), destVertices.end())){
            for(const int& v : destVertices){
                start = sc.now();
                graph.dijkstra(v);
                end = sc.now();
                time_span = end - start;
                result_stream << "Eccentricity of vertex " << v  << ": "<< graph.getEccentricity()<< "\n";
                result_stream << "Eccentricity execution time: " << setprecision(6) << time_span.count() << "\n\n";
            }
        }
    }
    result_stream.close();

    return 0;
}