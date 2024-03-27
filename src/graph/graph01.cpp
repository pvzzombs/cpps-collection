#include <iostream>
#include <algorithm>
#include <vector>

class Edge{
  public:
  int dest;
  int weight;
};

class Vertex{
  public:
  std::string name;
  std::vector<Edge> edges;
};

class Graph{
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
    bool exists = false;
    for(int i=0; i<vertices.at(src).edges.size(); i++){
      if(vertices.at(src).edges.at(i).dest == dest){
        exists = true;
        break;
      }
    }
    if(!exists){
      vertices.at(src).edges.push_back(temp);
    }
    exists = false;
    temp.dest = src;

    for(int i=0; i<vertices.at(dest).edges.size(); i++){
      if(vertices.at(dest).edges.at(i).dest == src){
        exists = true;
        break;
      }
    }
    if(!exists){
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
  static bool sorter(Edge a, Edge b){
    return a.dest < b.dest;
  }
  void sort(){
    for(int i=0; i<vertices.size(); i++){
      std::sort(vertices.at(i).edges.begin(), vertices.at(i).edges.end(), sorter);
    }
  }
};

int main(){
  Graph a;
  a.add_vertex("0");
  a.add_vertex("1");
  /*a.add_vertex("2");
  a.add_vertex("3");*/
  a.add_edge(0, 1);
  /*a.add_edge(1, 2);
  a.add_edge(2, 3);
  a.add_edge(3, 0);
  a.add_edge(0, 2);
  a.add_edge(1, 3);*/
  a.sort();
  a.print();
  return 0;
}
