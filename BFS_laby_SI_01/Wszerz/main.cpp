#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

void pokaz_sasiadow(std::map<int, std::vector<int>>& g){
    for(const auto& [key, neigh] : g)
    {
        std::cout << key << " sasiedzi: ";
        for(const auto& sasiad : neigh)
        {
            std::cout << sasiad << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::map<int, std::vector<int>> graf = {
        std::make_pair(1, std::vector<int>{2, 3}),
        std::make_pair(2, std::vector<int>{1, 5}),
        std::make_pair(3, std::vector<int>{1, 4}),
        std::make_pair(4, std::vector<int>{3, 6}),
        std::make_pair(5, std::vector<int>{2, 6, 8}),
        std::make_pair(6, std::vector<int>{4, 5, 7, 8}),
        std::make_pair(7, std::vector<int>{6}),
        std::make_pair(8, std::vector<int>{5, 6})
    }; //numer wierzcholka, sasiedzi

    pokaz_sasiadow(graf);
    std::map<int, bool> visited;
    std::map<int, int> parent;
    std::map<int, int> level;
    std::vector<int> bfs_traversal_output;

    std::queue<int> q;

    for(auto& [key, neigh] : graf)
    {
        visited[key] = false;
        level[key] = -1;
    }

    int s = 1;
    visited[s] = true;
    level[s]++;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        bfs_traversal_output.emplace_back(u);
        //std::cout << u << std::endl;
        for(int i = 0; i < (int)graf[u].size(); i++)
        {
            if(!visited[graf[u][i]])
            {
                visited[graf[u][i]] = true;
                parent[graf[u][i]] = u;
                level[graf[u][i]] = level[u]++;
                q.push(graf[u][i]);
            }
        }
    }

    for(const auto& bfs : bfs_traversal_output)
    {
        std::cout << bfs << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    int g = 8;
    std::vector<int> path;

    while(parent[g])
    {
        path.emplace_back(g);
        g = parent[g];
    }

    path.emplace_back(g); //aby dodac pierwszy wezel

    std::reverse(path.begin(), path.end());

    for(const auto& p : path)
    {
        std::cout << p << " ";
    }
    std::cout << std::endl;

    return 0;
}
