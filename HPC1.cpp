#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;
// Define the graph structure
class Graph {
public:
    vector<vector<int>> adj_list;
    Graph(int num_nodes) {
        adj_list.resize(num_nodes);
    }
    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
};
// Breadth First Search (BFS) algorithm
void bfs(Graph& graph, int start_node, vector<bool>& visited) {
    queue<int> q;
    visited[start_node] = true;
    q.push(start_node);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph.adj_list[u].size(); i++) {
            int v = graph.adj_list[u][i];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
// Depth First Search (DFS) algorithm
void dfs(Graph& graph, int start_node, vector<bool>& visited) {
    stack<int> s;
    visited[start_node] = true;
    s.push(start_node);
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        cout << u << " ";
        
        #pragma omp parallel for
        for (int i = 0; i < graph.adj_list[u].size(); i++) {
            int v = graph.adj_list[u][i];
            if (!visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }
}
int main() {
    int num_nodes = 7;
    Graph graph(num_nodes);
    // Add edges to the graph
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);
    graph.add_edge(2, 5);
    graph.add_edge(2, 6);
    vector<bool> visited(num_nodes, false);
    // Run BFS algorithm in parallel
    #pragma omp parallel
    {
        #pragma omp single nowait
        bfs(graph, 0, visited);
    }
    cout << endl;
    visited.assign(num_nodes, false);
    // Run DFS algorithm in parallel
    #pragma omp parallel
    {
        #pragma omp single nowait
        dfs(graph, 0, visited);
    }
    return 0;
}

