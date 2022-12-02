#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

    Graph::Graph(){
    }
    
    /* Adds a vertex to the graph.
       Returns the ID of the added vertex. */
    int Graph::addVertex(){
      int num = getNumVertices();
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
         weights.insert(pair<directedEdge, int>(newEdge,weight));
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
      f.open(fileName);
      
      string text1, text2;
      int count = 0;
      int vertnum;
      int edgenum;
      int weight, source, dest, prevsource=0;
      directedEdge newEdge;
      set<int> adjverts;
   
      

      if(f.is_open()){
         while(!f.eof()){
            if(count==0){
               f >> vertnum >> edgenum >> text1 >> text2;
               for(int i = 0; i<vertnum; i++){
                  addVertex();
               }
               count++;
            }else{
               count++;
               f >> source >> dest >> weight;
               newEdge.first = source;
               newEdge.second = dest;
               if(!isEdge(newEdge)){
               addEdge(newEdge,weight);
                  if(source!=prevsource && count!=1){
                     adjList.push_back(adjverts);
                     adjverts.clear();
                  }
                adjverts.insert(dest);
                if(count==edgenum+1){
                  adjList.push_back(adjverts);
                }
            }
            prevsource = source;
         }
         int diff = adjList.size()-vertnum;
         if(diff!=0){
            for(int j = 0; j<diff;j++){
               adjverts.clear();
               adjList.push_back(adjverts);
            }
            
         }
      }
      }else {
      cout<<"Error! File Not Opened!"<<endl;
      }
   }

   bool Graph::isReachable(int s, int d){ //using BFS to find if theres a path between two vertices
   int vertnum = vertices.size();
   bool *visited = new bool[vertnum];
    for (int i = 0; i < vertnum; i++)
        visited[i] = false;
    list<int> queue;
    visited[s] = true;
    queue.push_back(s);
   
    while (!queue.empty()){
       s = queue.front();
        for (auto x:adjList[s]){
           if(adjList[s].empty())
           queue.pop_front();
            if (x == d)
                return true;
            if (!visited[x])
            {
                visited[x] = true;
                queue.push_back(x);
                if(adjList[x].empty())
                queue.pop_back();
            }
        } 
    queue.pop_front();
    }
   
    return false;
}


   void Graph::lowestReachable(){
      //Found the lowest reachable using a nested for loop to check possibility of all paths 
      //If the adjacency is is empty for given vertex it prints that the lowest reachable doesn't exist
      int vertnum = vertices.size();
      int sum = 0;
      bool reached = false;
      
      int min=0;
         
         cout<< adjList.size();
         for(int i = 0; i<vertnum;i++){
            
            for(int j = 0; j<vertnum;j++){
               if(adjList[i].empty()){
                  cout<<"The lowest reacheable vertex for "<<i<<" doesn't exist"<<endl;
                  break;
               }else{
               reached = isReachable(i,j);
            
               if(reached && j!=i){ //because the loop increments from zero the first vertex to be reached that's not the source is the lowest reachable
                  sum++;
                  min = j;
                  cout<<"The lowest reacheable vertex for "<<i<<" is "<<min<<endl;
                  break;
               } 
               }
               min = 0;
            } 
           
         } 
   }
