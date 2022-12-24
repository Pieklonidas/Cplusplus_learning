#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <unordered_map>
#include <queue>

std::unordered_map<std::string, std::vector<std::string>> create_graph(std::vector<std::tuple<std::string, std::string>>& edges)
{
    std::unordered_map<std::string, std::vector<std::string>> graph;
    for(const auto& node : edges)
    {
        std::string node1 = std::get<0>(node);
        std::string node2 = std::get<1>(node);
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    return graph;
}

int shortestPath(std::vector<std::tuple<std::string, std::string>> edges, std::string src, std::string dst) {
  std::unordered_map<std::string, std::vector<std::string>> graph = create_graph(edges);
  std::unordered_map<std::string, bool> visited;
  std::queue<std::pair<std::string, int>> q;
  q.push(std::make_pair(src, 0));
  visited[src] = true;
  while (!q.empty()) {
      std::pair<std::string, int> current = q.front();
      q.pop();
      if(current.first == dst)
      {
          return current.second;
      }
      for(auto& neigh : graph[current.first])
      {
          if(!visited[neigh])
          {
              visited[neigh] = true;
              q.push(std::make_pair(neigh, current.second+1));
          }
      }
  }

  return -1;
}

int main()
{
    std::vector<std::tuple<std::string, std::string>> edges1 {
      {"w", "x"},
      {"x", "y"},
      {"z", "y"},
      {"z", "v"},
      {"w", "v"}
    };

    std::cout << shortestPath(edges1, "w", "z") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges2 {
      {"w", "x"},
      {"x", "y"},
      {"z", "y"},
      {"z", "v"},
      {"w", "v"}
    };

    std::cout << shortestPath(edges2, "y", "x") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges3 {
      {"a", "c"},
      {"a", "b"},
      {"c", "b"},
      {"c", "d"},
      {"b", "d"},
      {"e", "d"},
      {"g", "f"}
    };

    std::cout << shortestPath(edges3, "a", "e") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges4 {
      {"a", "c"},
      {"a", "b"},
      {"c", "b"},
      {"c", "d"},
      {"b", "d"},
      {"e", "d"},
      {"g", "f"}
    };

    std::cout << shortestPath(edges3, "e", "c") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges5 {
      {"a", "c"},
      {"a", "b"},
      {"c", "b"},
      {"c", "d"},
      {"b", "d"},
      {"e", "d"},
      {"g", "f"}
    };

    std::cout << shortestPath(edges5, "b", "g") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges6 {
      {"c", "n"},
      {"c", "e"},
      {"c", "s"},
      {"c", "w"},
      {"w", "e"},
    };

    std::cout << shortestPath(edges6, "w", "e") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges7 {
      {"c", "n"},
      {"c", "e"},
      {"c", "s"},
      {"c", "w"},
      {"w", "e"},
    };

    std::cout << shortestPath(edges7, "n", "e") << std::endl;

    std::vector<std::tuple<std::string, std::string>> edges8 {
      {"m", "n"},
      {"n", "o"},
      {"o", "p"},
      {"p", "q"},
      {"t", "o"},
      {"r", "q"},
      {"r", "s"}
    };

    std::cout << shortestPath(edges8, "m", "s") << std::endl;

    return 0;
}
