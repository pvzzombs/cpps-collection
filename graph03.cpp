#include <iostream>
#include <algorithm>
#include <vector>
//#include <cassert>

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
  std::string name;
  std::vector<Edge> edges;
};

class VertexNode{
  public:
  int src;
  int dest;
  int weight;
  int flag;
  bool operator<(const VertexNode& rhs) const {
    return weight < rhs.weight;
  }
};

class UndirectedGraph{
  public:
  std::vector<Vertex> vertices;
  int id=0;
  void add_vertex(std::string name){
    vertices.push_back(Vertex());
    vertices.at(id).name = name;
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
    
    temp.dest = src;

    it = std::find(vertices.at(dest).edges.begin(), vertices.at(dest).edges.end(), temp);
    if(it == vertices.at(dest).edges.end()){
      vertices.at(dest).edges.push_back(temp);
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
  void pushNoDuplicate(std::vector<VertexNode> &arr, VertexNode &e){
    for(int i=0; i<arr.size(); i++){
      if((arr.at(i).src == e.src &&
          arr.at(i).dest == e.dest) ||
         (arr.at(i).src == e.dest &&
          arr.at(i).dest == e.src)){
        return;
      }
    }
    arr.push_back(e);
  }
  void populateChildNodes(std::vector<VertexNode> &nodes, VertexNode &e){
    for(int i=0; i<vertices.at(e.dest).edges.size(); i++){
      VertexNode temp;
      temp.src = e.dest;
      temp.dest = vertices.at(e.dest).edges.at(i).dest;
      temp.weight = vertices.at(e.dest).edges.at(i).weight;
      pushNoDuplicate(nodes, temp);
    }
  }
  void primMST(){
    std::vector<int> parent(vertices.size());
    std::vector<bool> visited(vertices.size());
    parent.at(0) = -1;
    for(int i=0; i<visited.size(); i++){
      visited.at(i) = false;
    }
    visited.at(0) = true;
    
    std::vector<VertexNode> nodes;
    
    for(auto e: vertices.at(0).edges){
      VertexNode temp;
      temp.src = 0;
      temp.dest = e.dest;
      temp.weight = e.weight;
      nodes.push_back(temp);
    }
    
    for(int i=0; i<vertices.size()-1; i++){
      bool cont = true;
      while(cont){
        std::sort(nodes.begin(), nodes.end());
        cont = false;
        auto e = nodes.front();
        if(visited.at(e.dest)){
          nodes.erase(nodes.begin());
          cont = true;
        }else{
          populateChildNodes(nodes, e);
          parent.at(e.dest) = e.src;
          visited.at(e.dest) = true;
          nodes.erase(nodes.begin());
          cont = false;
        }
      }
    }
    
    for(int i=1; i<parent.size(); i++){
      std::cout << i << " -> " << parent.at(i) << std::endl;
    }
  }
  void hasCycle(){
    std::vector<int> q;
    std::vector<int> visited;
    
    q.push_back(0);
    
    while(q.size()){
      auto e = q.front();
      for(int i=0; i<vertices.at(e).edges.size(); i++){
        if(std::find(visited.begin(), visited.end(), vertices.at(e).edges.at(i).dest) == visited.end()){
          q.push_back(vertices.at(e).edges.at(i).dest);
        }
      }
      
      for(int i=0; i<q.size(); i++){
        for(int j=i+1; j<q.size(); j++){
          if(q.at(i) == q.at(j)){
            std::cout << "Has a cycle" << std::endl;
            return;
          }
        }
      }
      
      visited.push_back(e);
      q.erase(q.begin());
    }
    
    std::cout << "Has no cycle" << std::endl;
  }
  void BFS(int v=0){
    std::vector<int> q;
    std::vector<int> visited;
    
    q.push_back(v);
    
    while(q.size()){
      auto e = q.front();
      for(int i=0; i<vertices.at(e).edges.size(); i++){
        auto &d = vertices.at(e).edges.at(i).dest;
        if(std::find(visited.begin(), visited.end(), d) == visited.end() && std::find(q.begin(), q.end(), d) == q.end()){
          q.push_back(vertices.at(e).edges.at(i).dest);
        }
      }
      
      visited.push_back(e);
      q.erase(q.begin());
    }
    
    for(int i=0; i<visited.size(); i++){
      std::cout << visited.at(i);
      if(i+1<visited.size()){
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
  void DFSBT(std::vector<int> &s, std::vector<int> &visited){
    for(int i=0; i<vertices.at(s.back()).edges.size(); i++){
      auto e = vertices.at(s.back()).edges.at(i).dest;
      if(std::find(visited.begin(), visited.end(), e) == visited.end()){
        s.push_back(e);
        visited.push_back(e);
        DFSBT(s, visited);
        s.pop_back();
      }
    }
  }
  void DFS(int v=0){
    std::vector<int> s;
    std::vector<int> visited;
    
    s.push_back(v);
    visited.push_back(v);
    DFSBT(s, visited);
    s.pop_back();
    
    for(int i=0; i<visited.size(); i++){
      std::cout << visited.at(i);
      if(i+1<visited.size()){
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
};

int main(){
  UndirectedGraph a;
  a.add_vertex("0");
  a.add_vertex("1");
  a.add_vertex("2");
  a.add_vertex("3");
  a.add_vertex("4");
  a.add_edge(0, 1, 1);
  a.add_edge(1, 4, 2);
  a.add_edge(0, 2, 4);
  a.add_edge(2, 4, 3); //
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
  a.sort();
  a.print();
  a.primMST();
  a.hasCycle();
  a.BFS();
  a.DFS();
  return 0;
}
