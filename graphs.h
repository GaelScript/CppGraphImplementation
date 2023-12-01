#ifndef GRAPHS_H
#define GRAPHS_H
#include <iostream>
#include <vector>

class Edge
{
public:
    Edge* nextEdge;
    int sourceIndex;
    int destIndex;
    int weight;

    Edge(int source, int destination, int weight)
    {
        this->sourceIndex = source;
        this->destIndex = destination;
        this->weight = weight;
        nextEdge = nullptr;
    }

    int opposite(int vertexIndex)
    {
        if(vertexIndex==sourceIndex) {
            return destIndex;
        }
        else {
            return sourceIndex;
        }
    }

    std::vector<int> endVertices()
    {
        std::vector<int> endVertices;
        endVertices.push_back(sourceIndex);
        endVertices.push_back(destIndex);
        return endVertices;
    }

};

class Vertex
{
public:
    Edge* firstEdge; //Pointer to the first edge in the linked list of edges
    int data;

    explicit Vertex(int data) //explicit prevents implicit conversion
    {
        this-> data = data;
        firstEdge = nullptr;
    }

    Vertex()
    {
        data = -1;
        firstEdge = nullptr;
    }

    bool isAdjacentTo(int vertexIndex)
    {
        Edge* iterator = firstEdge;
        while(iterator!=nullptr)
        {
            if (iterator->destIndex == vertexIndex)
            {
                return true;
            }
            iterator=iterator->nextEdge;
        }
        return false;
    }
};

class Graph
{
private:
    std::vector<Vertex*> AdjList;
    int graphSize;
    void DFSTool(int vertex, std::vector<bool>& visited, std::vector<int>& result) //utility function for DFS. Used recursively
    {
        visited[vertex] = true;//sets the respective index in the bool vector to true
        result.push_back(vertex); //the visited vertex is added to the result vector to return in the DFS function in the public section of the class

        for (Edge* edge = AdjList[vertex]->firstEdge; edge != nullptr; edge = edge->nextEdge) //iterates through the edges at the vertex
        {
            int adjacentVertex = edge->opposite(vertex); //gets vertex opposite of the one from the argument on a specific edge
            if (!visited[adjacentVertex]) //if the vertex isn't visited
            {
                DFSTool(adjacentVertex, visited, result); //recursive call
            }
        }
    }
public:
    Graph(int vertices)
    {
        for(int i =0; i<vertices;i++)
        {
            auto* newVertex = new Vertex();
            AdjList.push_back(newVertex);
        }
        graphSize = vertices;
    }
    Graph()
    {
        graphSize = 0;
    }

    /*void insertVertex(int data)
    {
        Vertex* newVertex = new Vertex(data);
        AdjList.push_back(newVertex);
        graphSize++;
   }*/

   void insertVertex(int index)
   {
        if(index>=AdjList.size()) 
        {
            AdjList.resize(index+1,nullptr);
        }

        if(AdjList.at(index)==nullptr)
        {
            Vertex* newVertex = new Vertex();
            AdjList.at(index) = newVertex;
            graphSize++;
        }
        else{
            std::cout << "This vertex already exists!" << std::endl;
            return;
        }

        if(index<0)
        {
            std::cout << "Invalid vertex!" << std::endl;
            return;
        }
   }

    void insertEdge(int source, int destination, int weight)
    {
        if((AdjList[source]==nullptr||source>=AdjList.size())||(AdjList[destination]==nullptr || destination>=AdjList.size()))
        {
            std::cout << "Invalid index!" << std::endl;
            return;
        }
        Edge* newEdgeFirst = new Edge(source, destination, weight);
        Edge* newEdgeSecond = new Edge(destination, source, weight);
        if (AdjList.at(source)->firstEdge == nullptr) {
            AdjList.at(source)->firstEdge = newEdgeFirst;
        }
        else {
            Edge *iterator = AdjList.at(source)->firstEdge;
            while (iterator->nextEdge != nullptr) {
                iterator = iterator->nextEdge;
            }
            iterator->nextEdge = newEdgeFirst;
        }
        if (AdjList.at(destination)->firstEdge == nullptr) {
            AdjList.at(destination)->firstEdge = newEdgeSecond;
        }
        else {
            Edge *iterator = AdjList.at(destination)->firstEdge;
            while (iterator->nextEdge != nullptr) {
                iterator = iterator->nextEdge;
            }
            iterator->nextEdge = newEdgeSecond;
        }
    }

    /*int numOfIncidentEdges(int vertex)
    {
        int numOfEdges=0;
        if(AdjList.at(vertex)->firstEdge==nullptr)
        {
            std::cout << "No edges incident." << std::endl;
            return -1;
        }
        else {
            Edge* iterator = AdjList.at(vertex)->firstEdge;
            while(iterator->nextEdge!=nullptr)
            {
                numOfEdges++;
                iterator = iterator->nextEdge;
            }
            return numOfEdges;
        }
    }*/
    int numOfIncidentEdges(int vertex) //Improved
    {
        if(AdjList[vertex]==nullptr||vertex>=AdjList.size())
        {
            std::cout << "Invalid index!" << std::endl;
            return -1;
        }
        int numOfEdges = 0;
        Edge *iterator = AdjList.at(vertex)->firstEdge;

        while (iterator != nullptr)
        {
            numOfEdges++;
            iterator = iterator->nextEdge;
        }

        return numOfEdges;
    }

    void eraseEdge(int source, int destination)
    {
        if((AdjList[source]==nullptr||source>=AdjList.size())||(AdjList[destination]==nullptr || destination>=AdjList.size()))
        {
            std::cout << "Invalid index!" << std::endl;
            return;
        }
        Edge* temp = AdjList[source]->firstEdge;
        Edge* prev = nullptr;

        while(temp!= nullptr)
        {
            if(temp->destIndex == destination)
            {
                Edge* temp2 = AdjList[destination]->firstEdge;
                Edge* prev2 = nullptr;
                while(temp2!= nullptr)
                {
                    if (temp2->destIndex == source)
                    {
                        if(prev2 == nullptr) {
                            AdjList[destination]->firstEdge = temp2->nextEdge;
                        }
                        else
                        {
                            prev2->nextEdge = temp2->nextEdge;
                        }
                        delete temp2;
                        break;
                    }
                    prev2 = temp2;
                    temp2 = temp2->nextEdge;
                }
                if(prev == nullptr)
                {
                    AdjList[source]->firstEdge = temp->nextEdge;
                }
                else
                {
                    prev->nextEdge = temp->nextEdge;
                }
                delete temp;
                break;
            }
            prev  = temp;
            temp = temp->nextEdge;
        }
    }

    void eraseVertex(int vertexIndex)
    {
        if(AdjList[vertexIndex]==nullptr||vertexIndex>=AdjList.size())
        {
            std::cout << "Invalid index!" << std::endl;
            return;
        }
        Edge* iterator = AdjList.at(vertexIndex)->firstEdge;
        while(iterator!=nullptr)
        {
            int adjacentVertex = opposite(iterator, vertexIndex);
            eraseEdge(vertexIndex, adjacentVertex);
            iterator = AdjList[vertexIndex]->firstEdge;
        }

        //AdjList.erase(AdjList.begin() + vertexIndex); //Vertex indices after the vertex we delete get shifted!
        AdjList.at(vertexIndex) = nullptr;
        graphSize--;

        /*for(Vertex* & vertex : AdjList) //ensure that destIndex's in the rest of the edges are modified to they don't go out of scope
        {
            Edge* edgeIterator = vertex->firstEdge;
            while(edgeIterator!=nullptr)
            {
                if(edgeIterator->destIndex > vertexIndex) //if destIndex > vertexIndex, then it needs to be modified because we made the vector smaller.
                    //otherwise, it doesn't have to be changed.
                {
                    edgeIterator->destIndex--;
                }
                edgeIterator= edgeIterator->nextEdge;
            }
        }*/
    }

    std::vector<Vertex*> vertices()
    {
        std::vector<Vertex*> onlyVertices;
        onlyVertices.reserve(AdjList.size()); //CLion (my IDE) recommended I do this
        for(Vertex* i : AdjList) //CLion recommended I use a range-based for loop. Decided to implement to practice them
        {
            onlyVertices.push_back(i);
        }
        if (onlyVertices.empty())
        {
            std::cout<< "There are no vertices in this graph." << std::endl;
            Vertex* errorVertex = new Vertex(-1);
            onlyVertices.push_back(errorVertex);
            return onlyVertices;
        }
        return onlyVertices;
    }

    std::vector<Edge*> edges()
    {
        std::vector<Edge*> edgeList;
        for(const Vertex* vertex:AdjList) //range-based for loop because I want to practice using these
            //rather than the usual syntax
        {
            Edge* iterator = vertex->firstEdge;
            while(iterator!=nullptr)
            {
                edgeList.push_back(iterator);
                iterator = iterator->nextEdge;
            }
        }
        if(edgeList.empty()) //If there were no edges in the whole graph, the vector should be empty.
        {
            std::cout << "There are no edges in this graph." << std::endl;
            Edge* errorEdge = new Edge(-1,-1,-1);
            edgeList.push_back(errorEdge);
            return edgeList;
        }
        return edgeList;
    }

    std::vector<Edge*> incidentEdges(int vertexIndex)
    {
        std::vector<Edge*> incidentEdges;
        if(AdjList[vertexIndex]==nullptr||vertexIndex>=AdjList.size())
        {
            std::cout<< "Invalid index! " << std::endl;
            Edge* errorEdge = new Edge(-1,-1,-1); //dummy edge meant to signify an error
            incidentEdges.push_back(errorEdge);
            return incidentEdges;
        }
        if(AdjList.at(vertexIndex)->firstEdge==nullptr)
        {
            std::cout<< "No edges incident on this vertex." << std::endl;
            Edge* errorEdge = new Edge(-1,-1,-1); //dummy edge meant to signify an error
            incidentEdges.push_back(errorEdge);
            return incidentEdges;
        }
        Edge* iterator = AdjList.at(vertexIndex)-> firstEdge;
        while(iterator!=nullptr)
        {
            incidentEdges.push_back(iterator);
            iterator = iterator->nextEdge;
        }
        return incidentEdges;
    }

    int opposite(Edge* edge, int vertexIndex)
    {
        if(AdjList[vertexIndex]==nullptr || vertexIndex>=AdjList.size())
        {
            std::cout<< "Invalid index! " << std::endl;
            return -1;
        }
        return edge->opposite(vertexIndex); //uses opposite function counterpart from edge class
    }

    bool isAdjacentTo(int vertexIndex, int adjIndex) //There exists a similar function in the vertex class, only taking one argument
    {
        if((AdjList[vertexIndex]==nullptr || AdjList[adjIndex] == nullptr)||(vertexIndex>=AdjList.size()||adjIndex>=AdjList.size()))
        {
            std::cout<< "Invalid index! " << std::endl;
            return false;
        }
        Edge* iterator = AdjList.at(vertexIndex)->firstEdge;
        while(iterator!=nullptr)
        {
            if(iterator->destIndex == adjIndex)
            {
                return true;
            }
            iterator = iterator->nextEdge;
        }
        return false;
    }

    std::vector<int> endVertices(Edge* Edge)
    {
        return Edge->endVertices(); //uses counterpart from edge class
    }

    int size() const
    {
        return graphSize;
    }

    bool isEmpty()
    {
        if(graphSize!=0)
        return false;
        else
        return true;
    }

    int returnData(int vertexIndex)
    {
        if(AdjList[vertexIndex]==nullptr||vertexIndex>=AdjList.size())
        {
            std::cout << "Invalid index!" << std::endl;
            return -1;
        }
        return AdjList.at(vertexIndex)->data;
    }
    std::vector<int> DFS(int startVertex)
    {
        std::vector<bool> visited(graphSize, false); //vector of bools initially set to false
        std::vector<int> result; //Vector that returns the order in which the vertices are visited
        if(AdjList[startVertex]==nullptr||startVertex>=AdjList.size())
        {
            std::cout << "Invalid index!" << std::endl;
            return result;
        }
        DFSTool(startVertex, visited, result); //Starting index and the two vectors passed to the tool in private section

        return result;
    }
};

#endif // GRAPHS_H
