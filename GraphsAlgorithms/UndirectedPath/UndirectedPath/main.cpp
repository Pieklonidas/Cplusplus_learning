#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <queue>


bool undirectedPath(std::vector<std::tuple<std::string, std::string>> edges, std::string src, std::string dst) {
  std::map<std::string, std::vector<std::string>> graph;
  std::map<std::string, bool> visited;
  for(const auto& edge : edges)
  {
      std::string node1 = std::get<0>(edge);
      std::string node2 = std::get<1>(edge);
      graph[node1].push_back(node2);
      graph[node2].push_back(node1);
  }

  std::queue<std::string> q;
  q.push(src);
  visited[src] = true;

  while (!q.empty())
  {
      std::string current = q.front();
      q.pop();
      if(current == dst)
      {
          return true;
      }
      for(auto& neigh : graph[current])
      {
          if(!visited[neigh])
          {
              q.push(neigh);
              visited[neigh] = true;
          }
      }
  }

  return false;
}

int main()
{
    std::vector<std::tuple<std::string, std::string>> edges1 {
      {"i", "j"},
      {"k", "i"},
      {"m", "k"},
      {"k", "l"},
      {"o", "n"}
    };

    std::vector<std::tuple<std::string, std::string>> edges2 {
      {"i", "j"},
      {"k", "i"},
      {"m", "k"},
      {"k", "l"},
      {"o", "n"}
    };

    std::vector<std::tuple<std::string, std::string>> edges3 {
      {"i", "j"},
      {"k", "i"},
      {"m", "k"},
      {"k", "l"},
      {"o", "n"}
    };

    std::vector<std::tuple<std::string, std::string>> edges4 {
      {"i", "j"},
      {"k", "i"},
      {"m", "k"},
      {"k", "l"},
      {"o", "n"}
    };

    std::vector<std::tuple<std::string, std::string>> edges5 {
      {"i", "j"},
      {"k", "i"},
      {"m", "k"},
      {"k", "l"},
      {"o", "n"}
    };

    std::vector<std::tuple<std::string, std::string>> edges6 {
      {"b", "a"},
      {"c", "a"},
      {"b", "c"},
      {"q", "r"},
      {"q", "s"},
      {"q", "u"},
      {"q", "t"}
    };

    std::vector<std::tuple<std::string, std::string>> edges7 {
      {"s", "r"},
      {"t", "q"},
      {"q", "r"}
    };

    if(undirectedPath(edges1, "j", "m"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges2, "m", "j"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges3, "l", "j"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges4, "k", "o"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges5, "i", "o"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges6, "a", "b"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges6, "a", "c"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges6, "r", "t"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges6, "r", "b"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(undirectedPath(edges7, "r", "t"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    return 0;
}
