#include <iostream>
#include <queue>

using namespace std;


class Node {
public:
    int data;   
    Node* next;


    Node(int data) : data(data), next(nullptr) {}
};


class AdjList {
public:
    Node* head; 


    AdjList() : head(nullptr) {}
};


class Graph {
private:
    int maxVertices;
    int numVertices; 
    AdjList* adjLists; 

public:

    Graph(int maxVertices) : maxVertices(maxVertices), numVertices(0) {
        adjLists = new AdjList[maxVertices];
    }


    ~Graph() {
        delete[] adjLists;
    }


    Node* createVertex(int data) {
        Node* newVertex = new Node(data);
        return newVertex;
    }


    void insertEdge(int src, int dest) {

        if (src < 0 || src >= maxVertices || dest < 0 || dest >= maxVertices) {
            cout << "Invalid vertex\n";
            return;
        }

        Node* newNode = createVertex(dest);
        newNode->next = adjLists[src].head;
        adjLists[src].head = newNode;


        newNode = createVertex(src);
        newNode->next = adjLists[dest].head;
        adjLists[dest].head = newNode;
    }


    void showGraphStructure() {
        if (numVertices == 0) {
            cout << "Empty graph\n";
            return;
        }
        for (int i = 0; i < numVertices; ++i) {
            Node* temp = adjLists[i].head;
            cout << "Vertex " << i << ": ";
            while (temp) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }


    void BFS(int startNode) {
        if (startNode < 0 || startNode >= maxVertices) {
            cout << "Invalid start node\n";
            return;
        }

        bool* visited = new bool[maxVertices]();
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            Node* temp = adjLists[current].head;
            while (temp) {
                int neighbor = temp->data;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
                temp = temp->next;
            }
        }

        cout << endl;
        delete[] visited;
    }
};

int main() {
    int maxVertices;
    cout << "Enter the maximum number of vertices: ";
    cin >> maxVertices;

    Graph graph(maxVertices);

    int numInsertions;
    cout << "Enter the number of insertions: ";
    cin >> numInsertions;

    cout << "Enter the source and destination vertices for each insertion:\n";
    for (int i = 0; i < numInsertions; ++i) {
        int src, dest;
        cout << "Insertion " << i + 1 << ": ";
        cin >> src >> dest;
        graph.insertEdge(src, dest);
    }


    cout << "\nGraph Structure:\n";
    graph.showGraphStructure();


    int startNode;
    cout << "\nEnter the starting node for BFS traversal: ";
    cin >> startNode;
    cout << "BFS Traversal:\n";
    graph.BFS(startNode);

    return 0;
}