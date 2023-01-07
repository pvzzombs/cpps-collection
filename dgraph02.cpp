#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
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

class DijkstraNode{
  public:
  int src;
  int dest;
  int cost;
  bool operator<(const DijkstraNode& rhs) const {
    return cost < rhs.cost;
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
  void bellmanFord(){
    std::vector<int> distance(vertices.size());
    std::vector<int> previous(vertices.size());
    for(int i=0; i<vertices.size(); i++){
      distance.at(i) = MAX_VERTEX_COST;
      previous.at(i) = -1;
    }
    
    distance.at(0) = 0;
    
    for(int x=0; x<vertices.size()-1; x++){
      for(int i=0; i<vertices.size(); i++){
        for(int j=0; j<vertices.at(i).edges.size(); j++){
          int u = i;
          int v = vertices.at(u).edges.at(j).dest;
          int w = vertices.at(u).edges.at(j).weight;
          int temp = distance.at(u) + w;
          if(temp < distance.at(v)){
            distance.at(v) = temp;
            previous.at(v) = u;
          }
        }
      }
    }
    
    for(int i=0; i<vertices.size(); i++){
      for(int j=0; j<vertices.at(i).edges.size(); j++){
        int u = i;
        int v = vertices.at(u).edges.at(j).dest;
        int w = vertices.at(u).edges.at(j).weight;
        int temp = distance.at(u) + w;
        if(temp < distance.at(v)){
          std::cerr << "Negative Cycle Exists" << std::endl;
          return;
        }
      }
    }
    
    for(int i=0; i<previous.size(); i++){
      std::cout << i << ", " << previous.at(i) << std::endl;
    }
  }
  int extract_min(std::vector<int> &distance, std::vector<bool> &visited){
    int index = -1;
    int current_min = MAX_VERTEX_COST;
    
    for(int i=0; i<vertices.size(); i++){
      if(!visited.at(i) && distance.at(i) < current_min){
        current_min = distance.at(i);
        index = i;
      }
    }
    return index;
  }
  void dijkstra(){
    std::vector<int> distance(vertices.size());
    std::vector<int> previous(vertices.size());
    std::vector<bool> visited(vertices.size());
    for(int i=0; i<vertices.size(); i++){
      distance.at(i) = MAX_VERTEX_COST;
      previous.at(i) = -1;
      visited.at(i) = false;
    }
    
    distance.at(0) = 0;
    
    while(true){
      int u = extract_min(distance, visited);
      if(u == -1){ break; }
      visited.at(u) = true;
      for(int i=0; i<vertices.at(u).edges.size(); i++){
        int v = vertices.at(u).edges.at(i).dest;
        int w = vertices.at(u).edges.at(i).weight;
        int temp = distance.at(u) + w;
        if(temp < distance.at(v)){
          distance.at(v) = temp;
          previous.at(v) = u;
        }
      }
    }
    
    for(int i=0; i<previous.size(); i++){
      std::cout << i << ", " << previous.at(i) << std::endl;
    }
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
  a.add_edge("A", "B", 2);
  a.add_edge("A", "C", 3);
  a.add_edge("B", "C", 3);
  a.add_edge("B", "D", 2);
  a.add_edge("C", "E", 1);
  a.add_edge("E", "D", 4);
  /*a.add_edge(0, 1, 1);
  a.add_edge(1, 4, 2);
  a.add_edge(0, 2, 4);
  a.add_edge(2, 4, 3);
  a.add_edge(0, 3, 10);
  a.add_edge(3, 4, 11);*/
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
  //a.bellmanFord();
  a.bellmanFord();
  a.dijkstra();
  return 0;
}
