#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

    Graph::Graph(){

    }
    
    /* Adds a vertex to the graph.
       Returns the ID of the added vertex. */
    int Graph::addVertex(){
      int num = vertices.size();
      vertices.insert(num);
      return num;
    }
    
    /* Adds the given edge with the provided weight to the graph.
     The vertices of <newEdge> must currently exist in the graph. */
    void Graph::addEdge(directedEdge newEdge, int weight){
      bool isVertex1 = false;
      bool isVertex2 = false;
      set<int>::iterator i ;
      
      for (i = vertices.begin(); i != vertices.end(); i++){
         if( *i == newEdge.first){
            isVertex1 = true;
         }else if(*i == newEdge.second){
            isVertex2 = true;
         }
      }
      if(isVertex1 && isVertex2){
         edges.insert(newEdge);
         weights.insert(make_pair(newEdge,weight));
      } else 
      cout<<"Error! Corresponding Vertices Not Found!"<<endl;

    }
    
    /* Returns the number of vertices in the graph */
    int Graph::getNumVertices(){
      return vertices.size();
    }
    
    /* Returns the weight of the provided edge. The edge must exist in the graph. */
    int Graph::getWeight(directedEdge edge){
      auto p = edges.find(edge);
      map<directedEdge, int>::iterator i;
      if(p != edges.end()){
         i = weights.find(edge);
            if(i != weights.end()){
               return weights.find(edge)->second;
            }
      } else 
         cout<<"Error! Corresponding Edge Not Found!"<<endl;
         return 0;

    }

    /* Returns true iff there is an edge in the graph with the same vertices as newEdge */
    bool Graph::isEdge(directedEdge newEdge){
      auto p = edges.find(newEdge);
      if(p!= edges.end()){
         return true;
      } else 
         return false;
    }
    
    /* Prints a human-readable version of the adjacency list of the graph.
     Format is: vertex: adjacent_vertex_1 (weight_1) adjacent_vertex_2 (weight_2) ... */
    void Graph::printGraph(){
      
      map<directedEdge, int>::iterator im;
      for(int i = 0; i<vertices.size(); i++){
         cout<< i<< ":";
         for(im = weights.begin(); im != weights.end(); im++){
            directedEdge edg = im->first;
            int val= im ->second;
            if(edg.first == i){
               cout<<" "<< edg.second <<" ("<<val<<")" ;
            }
         }
         cout<<endl;
      }

    }
    
    /* Constructs a graph from the file with the provided name.
       The file format is as follows:
       The first line contains the number of vertices and the number of edges, separated by a space,
        followed by optional additional text.
       The graph is assumed to contain vertices numbered 0 to 'number of vertices' - 1.
       Each of the remaining lines contain one edge specified by the source and destination vertices
         followed by the weight, and separated by spaces.
       Returns the constructed graph. */
    void Graph::generateGraph(string fileName){
      ifstream f;
      string text;
      int count = 0;
      int vertnum;
      directedEdge newEdge;
      int weight;
      f.open(fileName);
      if(f.is_open()){
         while(getline(f,text)){
            if(count==0){
               vertnum = text[0];
               for(int i = 0; i<vertnum; i++){
                  addVertex();
               }
               count++;
            }else{
               newEdge.first = (int)text[0];
               newEdge.second = (int)text[2];
               weight = text[4];
               if(!isEdge(newEdge)){
               addEdge(newEdge,weight);
               adjList[newEdge.first].insert(newEdge.second);
               }

            }

         }

      }else 
      cout<<"Error! File Not Opened!"<<endl;

    }
    bool Graph::isReachable(int s, int d){
    bool *visited = new bool[vertices.size()];
    for (int i = 0; i < vertices.size(); i++)
        visited[i] = false;
 
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // it will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
 
    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for (auto x:adjList[s]){
            // If this adjacent node is the destination node, then
            // return true
            if (x == d)
                return true;
 
            // Else, continue to do BFS
            if (!visited[x])
            {
                visited[x] = true;
                queue.push_back(x);
            }
        }
    }
     
    // If BFS is complete without visiting d
    return false;
}


    void Graph::lowestReachable(){
      bool reached;
      int min;
         for(int i = 0; i<vertices.size();i++){
            for(int j = vertices.size(); j>0;i--){
               reached = isReachable(i,j);
               if(j!=i && reached){
                  min = j;
               }
               if(min!=0){
               cout<<"The lowest reacheable vertex for "<<i<<" is "<<min<<endl;
               } else 
               cout<<"The lowest reachable vertext for "<<i<<" doesn't exist";
            }
         }
         
      

        
    }

