#include <iostream>
#include <unordered_map>
#include <vector>

bool explore(std::unordered_map<int, std::vector<int>> graph, int current,std::unordered_map<int, bool>& visited)
{
    if(visited[current]) return false;

    visited[current] = true;

    for(auto& neigh : graph[current])
    {
        explore(graph, neigh, visited);
    }

    return true;
}

int connectedComponentsCount(std::unordered_map<int, std::vector<int>> graph) {
  std::unordered_map<int, bool> visited;
  int count = 0;

  for(auto& node : graph)
  {
      if(explore(graph, node.first, visited))
      {
          count++;
      }
  }
  return count;
}

int main()
{
    std::unordered_map<int, std::vector<int>> graph1 {
      { 0, { 8, 1, 5 } },
      { 1, { 0 } },
      { 5, { 0, 8 } },
      { 8, { 0, 5 } },
      { 2, { 3, 4 } },
      { 3, { 2, 4 } },
      { 4, { 3, 2 } }
    };

    std::cout << connectedComponentsCount(graph1) << std::endl;

    std::unordered_map<int, std::vector<int>> graph2 {
      { 1, { 2 } },
      { 2, { 1, 8 } },
      { 6, { 7 } },
      { 9, { 8 } },
      { 7, { 6, 8 } },
      { 8, { 9, 7, 2 } }
    };

    std::cout << connectedComponentsCount(graph2) << std::endl;

    std::unordered_map<int, std::vector<int>> graph3 {
      { 3, { } },
      { 4, { 6 } },
      { 6, { 4, 5, 7, 8 } },
      { 8, { 6 } },
      { 7, { 6 } },
      { 5, { 6 } },
      { 1, { 2 } },
      { 2, { 1 } }
    };

    std::cout << connectedComponentsCount(graph3) << std::endl;

    std::unordered_map<int, std::vector<int>> graph4;

    std::cout << connectedComponentsCount(graph4) << std::endl;

    std::unordered_map<int, std::vector<int>> graph5 {
      { 0, { 4, 7 } },
      { 1, { } },
      { 2, { } },
      { 3, { 6 } },
      { 4, { 0 } },
      { 6, { 3 } },
      { 7, { 0 } },
      { 8, { } },
    };

    std::cout << connectedComponentsCount(graph5) << std::endl;

    return 0;
}
