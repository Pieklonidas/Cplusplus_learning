#include <iostream>
#include <vector>
#include <map>

int exploreSum(std::vector<std::vector<char>> grid, std::pair<int, int> node, std::map<std::pair<int, int>, bool>& visited)
{
    if(visited[node]) return 0;
    int count = 1;
    auto [y, x] = node;
    visited[node] = true;
    if(y-1 >= 0 && grid[y-1][x] == 'L')
    {
        count += exploreSum(grid, std::make_pair(y-1, x), visited);
    }
    if(y+1 < (int)grid.size() && grid[y+1][x] == 'L')
    {
        count += exploreSum(grid, std::make_pair(y+1, x), visited);
    }
    if(x+1 < (int)grid[y].size() && grid[y][x+1] == 'L')
    {
        count += exploreSum(grid, std::make_pair(y, x+1), visited);
    }
    if(x-1 >= 0 && grid[y][x-1] == 'L')
    {
        count += exploreSum(grid, std::make_pair(y, x-1), visited);
    }

    return count;
}


int minimumIsland(std::vector<std::vector<char>> grid) {
    int smallest = 9999;
    std::map<std::pair<int, int>, bool> visited;
    for(int i = 0; i < (int)grid.size(); i++)
    {
        for(int j = 0; j < (int)grid[i].size(); j++)
        {
            if(grid[i][j] == 'L' && !visited[std::make_pair(i, j)])
            {
                int count = exploreSum(grid, std::make_pair(i, j), visited);
                if(count < smallest)
                {
                    smallest = count;
                }
            }
        }
    }

    return smallest;
}

int main()
{
    std::vector<std::vector<char>> grid1 {
      {'W', 'L', 'W', 'W', 'W'},
      {'W', 'L', 'W', 'W', 'W'},
      {'W', 'W', 'W', 'L', 'W'},
      {'W', 'W', 'L', 'L', 'W'},
      {'L', 'W', 'W', 'L', 'L'},
      {'L', 'L', 'W', 'W', 'W'}
    };

    std::cout << minimumIsland(grid1) << std::endl;

    std::vector<std::vector<char>> grid2 {
      {'L', 'W', 'W', 'L', 'W'},
      {'L', 'W', 'W', 'L', 'L'},
      {'W', 'L', 'W', 'L', 'W'},
      {'W', 'W', 'W', 'W', 'W'},
      {'W', 'W', 'L', 'L', 'L'}
    };

    std::cout << minimumIsland(grid2) << std::endl;

    std::vector<std::vector<char>> grid3 {
      {'L', 'L', 'L'},
      {'L', 'L', 'L'},
      {'L', 'L', 'L'}
    };

    std::cout << minimumIsland(grid3) << std::endl;

    std::vector<std::vector<char>> grid4 {
      {'W', 'W'},
      {'L', 'L'},
      {'W', 'W'},
      {'W', 'L'}
    };

    std::cout << minimumIsland(grid4) << std::endl;

    return 0;
}
