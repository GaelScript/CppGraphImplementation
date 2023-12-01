#include "graphs.h"
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    ifstream inputFile("graph.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int numberOfVerts, numberOfEdges;
    int source,destination,weight;
    inputFile >> numberOfVerts >> numberOfEdges;

    Graph graph(numberOfVerts);

    for(int i=0;i<numberOfEdges;i++)
    {
        inputFile>>source>>destination>>weight;
        graph.insertEdge(source,destination,weight);
    }
    cout << graph.numOfIncidentEdges(0) << endl;
    cout << graph.numOfIncidentEdges(3) << endl;
    if(graph.isAdjacentTo(0,3))
    {
        cout << "0 and 3 are adjacent." << endl;
    }
    else
        cout << "0 and 3 are not adjacent." << endl;

    cout << "break\n" << endl;

    const vector<int>dfsResult = graph.DFS(0);
    cout << "Results of DFS: ";
    for (const int vertex:dfsResult)
    {
        cout << vertex << " ";
    }
    cout << endl;

    cout << "break\n" << endl;

    // cout <<"Size of graph.txt graph: " << graph.size() << endl;

    // graph.eraseVertex(0);
    // cout <<"Size of graph.txt graph: " << graph.size() << endl;
    // cout << graph.numOfIncidentEdges(2) << " edges are incident on 2, while there used to be 3 (expected:2)" << endl; //NOTE: erasing a vertex makes it so that the index of every
    // //vertex after the erased vertex is subtracted by one. So here, calling this function with argument 2 is really
    // //asking for what used to be at index 3. As long as we're using indices to identify vertices, this erasure method
    // //can complicate the order of the adjacency list. EDIT: No longer applies after editing erasure and insertion method.

    // //testing behavior after eraseVertex is called
    // if(graph.isAdjacentTo(0,3))
    // {
    //     cout << "0 and 3 (formerly 3) are adjacent after erasure." << endl;
    // }
    // else
    //     cout << "0 and 3 (formerly 3) are not adjacent after erasure. (expected outcome)" << endl;

    // graph.insertEdge(0,3,1);
    // cout << "Now, we've inserted an edge between 0 and 3." << endl;
    // if(graph.isAdjacentTo(0,3))
    // {
    //     cout << "0 and 3 (formerly 3) are adjacent after erasure. (expected outcome)" << endl;
    // }
    // else
    //     cout << "0 and 3 (formerly 3) are not adjacent after erasure." << endl;

    // cout << "Number of edges incident on 0: " << graph.numOfIncidentEdges(0) << ". Expected:1" << endl;
    // cout << "Now we will delete this edge." << endl;
    // graph.eraseEdge(0,3);
    // if(graph.isAdjacentTo(0,3))
    // {
    //     cout << "0 and 3 (formerly 3) are adjacent after erasure." << endl;
    // }
    // else
    //     cout << "0 and 3 (formerly 3) are not adjacent after erasure. (Expected outcome)" << endl;
    // cout << "Now we'll add a vertex (8) that isn't in order with respect to the last vertex 3 and connect it to vertex 0." << endl;
    // graph.insertVertex(8);
    // graph.insertEdge(0,8,1);
    // cout << endl;
    // if(graph.isAdjacentTo(0,8))
    // {
    //     cout << "0 and 8 are adjacent. (Expected outcome)" << endl;
    // }
    // else
    //     cout << "0 and 8 are not adjacent. " << endl;

    // //below is testing errors. Should all ouput "Invalid index!"
    // if(graph.isAdjacentTo(0,15))
    // {
    //     cout << "0 and 15 are adjacent." << endl;
    // }
    // else
    //     cout << "0 and 15 are not adjacent. (Expected outcome)" << endl;
    // graph.eraseEdge(45,67);
    // graph.insertEdge(45,67,1);
    // graph.numOfIncidentEdges(56);
    // graph.incidentEdges(67);
    // graph.eraseVertex(54);
    // graph.isAdjacentTo(0,69);
    // graph.DFS(44);
    // graph.insertVertex(8);
    // graph.returnData(88);
    // //final tests of adding vertex,edge, then erasing vertex and edge
    // graph.insertVertex(6);
    // graph.insertEdge(2,6,1); //two from graph.txt plus this new edge is 3 edges incident on 2
    // cout << "Number of edges incident on new vertex 6 (expected:1) " << graph.numOfIncidentEdges(6) << endl;
    // cout << "Number of edges incident on new vertex 2 (expected:3) " << graph.numOfIncidentEdges(2) << endl;
    // graph.eraseVertex(6);
    // cout << "Number of edges incident on new vertex 6 (expected:-1[error]) " << graph.numOfIncidentEdges(6) << endl;
    // cout << "Number of edges incident on new vertex 2 (expected:2) " << graph.numOfIncidentEdges(2) << endl;


    inputFile.close();
    return 0;
}