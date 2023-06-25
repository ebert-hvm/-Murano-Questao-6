
# Desafio Murano Group: Questão 6
C++ implementation of Dijkstra's minimum path algorithm and Prim's minimum spannning tree algorithm on graphs.
Development environment: Visual Studio Code

## Getting Started

### Prerequisites

- C++14 (or newer) compiler

### Installation

- Clone repository:
```
git clone https://github.com/ebert-hvm/Murano-Questao-6.git
```
- Compile "main.cpp":
```
g++ -std=c++14 graph.cpp main.cpp -o main
```

## Usage

- Run the C++ program with the path to .txt graph files as arguments:
```
./main /path/to/graph_1.txt ... /path/to/graph_n.txt
```
This command will create the "result.txt" file in the same directory of main executable, and will also create a txt file with the generated MST for each graph.
Example command:
```
./main grafo_W_1.txt grafo_W_2.txt grafo_W_3.txt
```

Each .txt graph file must start with the number of the vertices n. The following lines must have 2 integers 0 < u, v <= n and one float w, which represent the end points of an edge and its weight respectively.
Example .txt file:
```
5
1 2 1
2 3 2
2 4 0.5
4 3 1
4 5 0.5
```
In other case, the program will throw an exception and terminate.
obs: In order to answer the question correctly the input graph must have more than 50 vertices.
