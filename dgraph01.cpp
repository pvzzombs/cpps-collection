#include <iostream>
#include <algorithm>
#include <vector>
//#include <cassert>
#define MAX_VERTEX_COST 987654321

class Edge{
  public:
  int dest;
  int weight;
  bool operator==(const Edge& rhs) const {
    return dest == rhs.dest;
  }
  bool operator<(Edge const &rhs) const {
    return dest < rhs.dest;
  }
};

class Vertex{
  public:
  int cost;
  std::string name;
  std::vector<Edge> edges;
};

class EdgeNode{
  public:
  int src;
  int dest;
  int weight;
  bool operator<(const EdgeNode& rhs) const {
    return weight < rhs.weight;
  }
};

class DirectedGraph{
  public:
  std::vector<Vertex> vertices;
  int id=0;
  void add_vertex(std::string name, int cost=0){
    vertices.push_back(Vertex());
    vertices.at(id).name = name;
    vertices.at(id).cost = cost;
    std::cout << "Vertex " << id << " added successfully" << std::endl;
    ++id;
  }
  void add_edge(int src, int dest, int weight=0){
    Edge temp;
    temp.dest = dest;
    temp.weight = weight;
    
    auto it = std::find(vertices.at(src).edges.begin(), vertices.at(src).edges.end(), temp);
    if(it == vertices.at(src).edges.end()){
      vertices.at(src).edges.push_back(temp);
    }
    
    /*temp.dest = src;

    it = std::find(vertices.at(dest).edges.begin(), vertices.at(dest).edges.end(), temp);
    if(it == vertices.at(dest).edges.end()){
      vertices.at(dest).edges.push_back(temp);
    }*/
  }
  void add_edge(std::string src, std::string dest, int weight=0){
    Edge temp;
    temp.weight = weight;
    for(int i=0; i<vertices.size(); i++){
      if(vertices.at(i).name == dest){
        temp.dest = i;
        break;
      }
    }
    int srcid;
    for(int i=0; i<vertices.size(); i++){
      if(vertices.at(i).name == src){
        srcid = i;
      }
    }
    auto it = std::find(vertices.at(srcid).edges.begin(), vertices.at(srcid).edges.end(), temp);
    if(it == vertices.at(srcid).edges.end()){
      vertices.at(srcid).edges.push_back(temp);
    }
  }
  void print(){
    for(int i=0; i<vertices.size(); i++){
      std::cout << vertices.at(i).name << " = { ";
      for(int j=0; j<vertices.at(i).edges.size(); j++){
        std::cout << "[" << vertices.at(i).edges.at(j).dest << ", " << vertices.at(i).edges.at(j).weight << "] ";
      }
      std::cout << "}" << std::endl;
    }
  }
  void sort(){
    for(int i=0; i<vertices.size(); i++){
      std::sort(vertices.at(i).edges.begin(), vertices.at(i).edges.end());
    }
  }
  void bellmanFord(int start=0){
    std::vector<EdgeNode> edges;
    std::vector<int> previous;
    
    previous.resize(vertices.size());
    
    for(int i=0; i<vertices.size(); i++){
      for(int j=0; j<vertices.at(i).edges.size(); j++){
        EdgeNode temp;
        temp.src = i;
        temp.dest = vertices.at(i).edges.at(j).dest;
        temp.weight = vertices.at(i).edges.at(j).weight;
        edges.push_back(temp);
      }
    }
    
    /*for(auto &x : edges){
      std::cout << x.src << " -> " << x.dest << " (w) -> " << x.weight << std::endl;
    }*/
    
    for(int i=0; i<vertices.size(); i++){
      vertices.at(i).cost = MAX_VERTEX_COST;
      previous.at(i) = -1;
    }
    vertices.at(start).cost = 0;
    
    // N = vertices.size()
    // Traverse N-1 times
    for(int i=0; i<vertices.size()-1; i++){
      for(int j=0; j<edges.size(); j++){
        //u.src + (u,v).weight < v.dest
        //then v.dest = u.src + (u,v).weight
        auto e = edges.at(j);
        //std::cout << e.src << ", " << e.dest << ", " << e.weight << std::endl;
        if(vertices.at(e.src).cost != MAX_VERTEX_COST && vertices.at(e.src).cost + e.weight < vertices.at(e.dest).cost){
          vertices.at(e.dest).cost = vertices.at(e.src).cost + e.weight;
          previous.at(e.dest) = e.src;
        }
      }
    }
    
    for(int j=0; j<edges.size(); j++){
      auto e = edges.at(j);
      if(vertices.at(e.src).cost != MAX_VERTEX_COST && vertices.at(e.src).cost + e.weight < vertices.at(e.dest).cost){
        std::cout << "Negative cycle detected" << std::endl;
        return;
      }
    }
    
    for(int i=0; i<vertices.size(); i++){
      std::cout << "vertex: " << i << ", previous vertex: " << previous.at(i) << ", cost: " << vertices.at(i).cost << std::endl;
    }
  }
  void bellmanFord(int start, int end){
    std::vector<EdgeNode> edges;
    std::vector<int> previous;
    std::vector<int> path;
    
    previous.resize(vertices.size());
    
    for(int i=0; i<vertices.size(); i++){
      for(int j=0; j<vertices.at(i).edges.size(); j++){
        EdgeNode temp;
        temp.src = i;
        temp.dest = vertices.at(i).edges.at(j).dest;
        temp.weight = vertices.at(i).edges.at(j).weight;
        edges.push_back(temp);
      }
    }
    
    for(int i=0; i<vertices.size(); i++){
      vertices.at(i).cost = MAX_VERTEX_COST;
      previous.at(i) = -1;
    }
    vertices.at(start).cost = 0;
    
    for(int i=0; i<vertices.size()-1; i++){
      for(int j=0; j<edges.size(); j++){
        auto e = edges.at(j);
        if(vertices.at(e.src).cost != MAX_VERTEX_COST && vertices.at(e.src).cost + e.weight < vertices.at(e.dest).cost){
          vertices.at(e.dest).cost = vertices.at(e.src).cost + e.weight;
          previous.at(e.dest) = e.src;
        }
      }
    }
    
    for(int j=0; j<edges.size(); j++){
      auto e = edges.at(j);
      if(vertices.at(e.src).cost != MAX_VERTEX_COST && vertices.at(e.src).cost + e.weight < vertices.at(e.dest).cost){
        std::cout << "Negative cycle detected" << std::endl;
        return;
      }
    }
    
    /*for(int i=0; i<vertices.size(); i++){
      std::cout << "vertex: " << i << ", previous vertex: " << previous.at(i) << ", cost: " << vertices.at(i).cost << std::endl;
    }*/
    
    int k = end;
    /*while(k != start){
      path.push_back(k);
      k = previous.at(k);
    }
    path.push_back(start);*/
    while(k != -1){
      path.push_back(k);
      k = previous.at(k);
    }
    std::reverse(path.begin(), path.end());
    for(int i=0; i<path.size(); i++){
      std::cout << path.at(i);
      if(i+1<path.size()){
        std::cout << " -> ";
      }
    }
    std::cout << std::endl;
  }
};

int main(){
  DirectedGraph a;
  a.add_vertex("A");
  a.add_vertex("B");
  a.add_vertex("C");
  a.add_vertex("D");
  a.add_vertex("E");
  
  //a.add_vertex("F");
  
  /*a.add_edge("A", "B", 4);
  a.add_edge("B", "C", 5);
  a.add_edge("C", "F", 6);
  a.add_edge("A", "D", 1);
  a.add_edge("D", "E", 2);
  a.add_edge("E", "F", 3);*/
  a.add_edge(0, 1, 1);
  a.add_edge(1, 4, 2);
  a.add_edge(0, 2, 4);
  a.add_edge(2, 4, 3);
  a.add_edge(0, 3, 10);
  a.add_edge(3, 4, 11);
  /*a.add_edge(0,1,2);
  a.add_edge(0,2,1);
  a.add_edge(0,4,3);
  a.add_edge(1,3,1);
  a.add_edge(2,3,1);
  a.add_edge(4,3,3);*/
  /*a.add_edge(0, 1);
  a.add_edge(1, 2);
  a.add_edge(1, 4);
  a.add_edge(2, 3);
  a.add_edge(4, 3);*/
  /*a.add_edge(0,1,5);
  a.add_edge(0,2,4);
  a.add_edge(1,3,3);
  a.add_edge(2,1,-6);
  a.add_edge(3,2,2);*/
  a.sort();
  a.print();
  a.bellmanFord();
  a.bellmanFord(0,4);
  return 0;
}
