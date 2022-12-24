#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>

void depthFirstPrintStack(std::map<char, std::vector<char>>& graph, char source)
{
    std::stack<char> st;
    st.push(source);

    while (!st.empty())
    {
        char current = st.top();
        st.pop();
        std::cout << current << std::endl;
        for(auto& neigh : graph[current])
        {
            st.push(neigh);
        }
    }
}

void depthFirstPrintRecurrence(std::map<char, std::vector<char>>& graph, char source)
{
    std::cout << source << std::endl;
    for(auto& neigh : graph[source])
    {
        depthFirstPrintRecurrence(graph, neigh);
    }
}

void breadthFirstPrint(std::map<char, std::vector<char>>& graph, char source)
{
    std::queue<char> q;
    q.push(source);

    while (!q.empty())
    {
        char current = q.front();
        q.pop();
        std::cout << current << std::endl;
        for(auto& neigh : graph[current])
        {
            q.push(neigh);
        }
    }
}

int main()
{
    std::map<char, std::vector<char>> graph = {
            std::make_pair('a', std::vector<char>{'c', 'b'}),
            std::make_pair('b', std::vector<char>{'d'}),
            std::make_pair('c', std::vector<char>{'e'}),
            std::make_pair('d', std::vector<char>{'f'}),
            std::make_pair('e', std::vector<char>{}),
            std::make_pair('f', std::vector<char>{})
        };

    char source = 'a';

//    depthFirstPrintStack(graph, source);
//    depthFirstPrintRecurrence(graph, source);
    breadthFirstPrint(graph, source);
    return 0;
}
