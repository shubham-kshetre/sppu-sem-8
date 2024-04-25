#include <iostream> // Include the input/output stream library
#include <vector> // Include the vector container library (for adjacency list)
#include <queue> // Include the queue container library (for BFS traversal)
#include <omp.h> // Include the OpenMP library for parallel processing

using namespace std; // Using the standard namespace

// Graph class representing the adjacency list
class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) : V(V + 1), adj(V + 1) {} // Constructor to initialize the number of vertices and adjacency list, increase by 1 for 1-based indexing

    // Add an edge to the graph
    void addEdge(int v, int w) { // Method to add an edge between vertices
        adj[v].push_back(w); // Add the edge to the adjacency list
    }

    // Parallel Depth-First Search
    void parallelDFS(int startVertex) { // Method to perform parallel depth-first search
        vector<bool> visited(V, false); // Create a boolean vector to keep track of visited vertices, initialized to false
        parallelDFSUtil(startVertex, visited); // Call the utility function to perform parallel DFS
    }

    // Parallel DFS utility function
    void parallelDFSUtil(int v, vector<bool>& visited) { // Utility function to perform parallel DFS recursively
        visited[v] = true; // Mark the current vertex as visited
        cout << v << " "; // Print the current vertex

        #pragma omp parallel for // OpenMP directive to parallelize the loop
        for (int i = 0; i < adj[v].size(); ++i) { // Loop through the adjacent vertices
            int n = adj[v][i]; // Get the next adjacent vertex
            if (!visited[n]) // If the vertex is not visited
                parallelDFSUtil(n, visited); // Recursively call the utility function for the adjacent vertex
        }
    }

    // Parallel Breadth-First Search
    void parallelBFS(int startVertex) { // Method to perform parallel breadth-first search
        vector<bool> visited(V, false); // Create a boolean vector to keep track of visited vertices, initialized to false
        queue<int> q; // Create a queue to store vertices for BFS traversal

        visited[startVertex] = true; // Mark the start vertex as visited
        q.push(startVertex); // Push the start vertex to the queue

        while (!q.empty()) { // While the queue is not empty
            int v = q.front(); // Get the front element of the queue
            q.pop(); // Remove the front element from the queue
            cout << v << " "; // Print the current vertex

            #pragma omp parallel for // OpenMP directive to parallelize the loop
            for (int i = 0; i < adj[v].size(); ++i) { // Loop through the adjacent vertices
                int n = adj[v][i]; // Get the next adjacent vertex
                if (!visited[n]) { // If the vertex is not visited
                    visited[n] = true; // Mark the vertex as visited
                    q.push(n); // Push the vertex to the queue for further traversal
                }
            }
        }
    }
};

int main() {
    int vertices, edges; // Declare variables to store the number of vertices and edges
    cout << "Enter the number of vertices: "; // Prompt the user to enter the number of vertices
    cin >> vertices; // Read the number of vertices from the user
    cout << "Enter the number of edges: "; // Prompt the user to enter the number of edges
    cin >> edges; // Read the number of edges from the user

    // Create a graph
    Graph g(vertices); // Instantiate a Graph object with the specified number of vertices

    cout << "Enter edges in the format (source destination):\n"; // Prompt the user to enter edges
    for (int i = 0; i < edges; ++i) { // Loop to read edges from the user
        int source, destination; // Declare variables to store the source and destination of an edge
        cin >> source >> destination; // Read the source and destination of an edge from the user
        g.addEdge(source, destination); // Add the edge to the graph
    }
    
    cout << "Depth-First Search (DFS): "; // Print the message for DFS traversal
    g.parallelDFS(1); // Start DFS from vertex 1
    cout << endl; // Print newline after DFS traversal

    cout << "Breadth-First Search (BFS): "; // Print the message for BFS traversal
    g.parallelBFS(1); // Start BFS from vertex 1
    cout << endl; // Print newline after BFS traversal

    return 0; // Return 0 to indicate successful execution
}

