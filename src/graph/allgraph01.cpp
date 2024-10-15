#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cassert>

class Graph {
  std::unordered_map<std::string, std::vector<std::pair<std::string, long>>> representation;

public:
  bool addVertex(const std::string &VertexName) {
    if(representation.count(VertexName) > 0){
      return false;
    }
    representation[VertexName] = std::vector<std::pair<std::string, long>>();
    return true;
  }
  bool addNode(const std::string &NodeName) {
    return addVertex(NodeName);
  }
  bool addEdge(const std::string &VertexSourceName, const std::string &VertexDestinationName, long weight=0) {
    addVertex(VertexSourceName);
    addVertex(VertexDestinationName);
    // check if vertex dest already esists
    // can be avoided if set is used
    for(auto &p: representation.at(VertexSourceName)) {
      if(p.first == VertexDestinationName) {
        return false;
      }
    }
    // a better way is to store using a unordered set,
    // but I'll stick with vector
    representation.at(VertexSourceName).push_back(std::make_pair(VertexDestinationName, weight));
    return true;
  }
  bool addUndirectedEdge(const std::string &VertexSourceName, const std::string &VertexDestinationName, long weight=0) {
    bool a = addEdge(VertexSourceName, VertexDestinationName, weight);
    bool b = addEdge(VertexDestinationName, VertexSourceName, weight);
    return a || b;
  }
  bool setGraph(const std::unordered_map<std::string, std::vector<std::string>> &graph) {
    for(auto &p: graph) {
      addVertex(p.first);
      for(auto &d: p.second) {
        addEdge(p.first, d);
      }
    }
    return true;
  }
  void print() {
    std::stringstream ss;
    size_t countItems, countKeys = 0;
    ss << "{";
    ss << std::endl;
    for(auto &p: representation) {
      ss << p.first;
      ss << ":{";
      countItems = 0;
      for(auto &item: p.second) {
        ss << "[";
        ss << item.first;
        ss << ", ";
        ss << item.second;
        ss << "]";
        if(countItems + 1 < p.second.size()) {
          ss << ",";
        }
        countItems++;
      }
      ss << "}";
      if(countKeys + 1 < representation.size()) {
        ss << ",";
      }
      ss << std::endl;
      countKeys++;
    }
    ss << "}";
    ss << std::endl;
    std::cout << ss.str();
  }
};

int main() {
  Graph graph;
  graph.setGraph({
    {"a", { "b", "c" }},
    {"b", { "c" }},
    {"c", {}},
    {"d", {}}
  });
  graph.print();
  return 0;
}
