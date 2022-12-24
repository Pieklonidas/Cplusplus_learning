#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

//bool hasPath(std::unordered_map<std::string, std::vector<std::string>> graph, std::string src, std::string dst) {
//  if(src == dst) return true;

//  for(auto& neigh : graph[src])
//  {
//      if(hasPath(graph, neigh, dst))
//      {
//          return true;
//      }
//  }

//  return false;
//}

bool hasPath(std::unordered_map<std::string, std::vector<std::string>> graph, std::string src, std::string dst) {
  std::queue<std::string> q;
  q.push(src);
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
            q.push(neigh);
      }
  }

  return false;
}

int main()
{
    std::unordered_map<std::string, std::vector<std::string>> graph1 {
      { "f", {"g", "i"} },
      { "g", {"h"} },
      { "h", {} },
      { "i", {"g", "k"} },
      { "j", {"i"} },
      { "k", {} }
    };

    std::unordered_map<std::string, std::vector<std::string>> graph2 {
      { "f", { "g", "i" } },
      { "g", {"h"} },
      { "h", {} },
      { "i", {"g", "k"} },
      { "j", {"i"} },
      { "k", {} }
    };

    std::unordered_map<std::string, std::vector<std::string>> graph3 {
      { "f", {"g", "i"} },
      { "g", {"h"} },
      { "h", {} },
      { "i", {"g", "k"} },
      { "j", {"i"} },
      { "k", {} }
    };

    std::unordered_map<std::string, std::vector<std::string>> graph4 {
      { "v", {"x", "w"} },
      { "w", {} },
      { "x", {} },
      { "y", {"z"} },
      { "z", {} }
    };

    std::unordered_map<std::string, std::vector<std::string>> graph5 {
      { "v", {"x", "w"} },
      { "w", {} },
      { "x", {} },
      { "y", {"z"} },
      { "z", {} }
    };

    if(hasPath(graph1, "f", "k"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(hasPath(graph2, "f", "j"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(hasPath(graph3, "i", "h"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(hasPath(graph4, "v", "w"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if(hasPath(graph5, "v", "z"))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    return 0;
}
