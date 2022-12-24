#include <iostream>
#include <unordered_map>
#include <vector>

int sumAllNodes(std::unordered_map<int, std::vector<int>> graph, int node, std::unordered_map<int, bool>& visited)
{
    if(visited[node]) return 0;
    int current_sum = 1;
    visited[node] = true;
    for(auto& neigh : graph[node])
    {
        current_sum += sumAllNodes(graph, neigh, visited);
    }
    return current_sum;
}

int largestComponent(std::unordered_map<int, std::vector<int>> graph) {
  int largest = 0;
  std::unordered_map<int, bool> visited;
  for(auto& node : graph)
  {
      int current = sumAllNodes(graph, node.first, visited);
      if(current > largest)
      {
          largest = current;
      }
  }

  return largest;
}

int main()
{
    std::unordered_map<int, std::vector<int>> graph1 {
      { 0, {8, 1, 5} },
      { 1, {0} },
      { 5, {0, 8} },
      { 8, {0, 5} },
      { 2, {3, 4} },
      { 3, {2, 4} },
      { 4, {3, 2} }
    };

    std::cout << largestComponent(graph1) << std::endl;

    std::unordered_map<int, std::vector<int>> graph2 {
      { 1, {2} },
      { 2, {1, 8} },
      { 6, {7} },
      { 9, {8} },
      { 7, {6, 8} },
      { 8, {9, 7, 2} }
    };

    std::cout << largestComponent(graph2) << std::endl;

    std::unordered_map<int, std::vector<int>> graph3 {
      { 3, {} },
      { 4, {6} },
      { 6, {4, 5, 7, 8} },
      { 8, {6} },
      { 7, {6} },
      { 5, {6} },
      { 1, {2} },
      { 2, {1} }
    };

    std::cout << largestComponent(graph3) << std::endl;

    std::unordered_map<int, std::vector<int>> graph4;

    std::cout << largestComponent(graph4) << std::endl;

    std::unordered_map<int, std::vector<int>> graph5 {
      { 0, {4, 7} },
      { 1, {} },
      { 2, {} },
      { 3, {6} },
      { 4, {0} },
      { 6, {3} },
      { 7, {0} },
      { 8, {} }
    };

    std::cout << largestComponent(graph5) << std::endl;

    return 0;
}
