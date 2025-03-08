#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>

std::vector<int> readInput(int& N, std::ifstream& input)
{
    input >> N;
    std::vector<int> a(N);
    for (int i = 0; i < N; ++i)
    {
        input >> a[i];
    }
    return a;
}

std::vector<int> buildNextArray(const std::vector<int>& a)
{
    int N = a.size();
    std::unordered_map<int, std::vector<int>> pos_map;
    
    for (int i = N - 1; i >= 0; --i)
    {
        pos_map[a[i]].push_back(i);
    }
    
    std::vector<int> next(N, -1);
    for (int i = 0; i < N; ++i)
    {
        auto& positions = pos_map[a[i]];
        while (!positions.empty() && positions.back() <= i)
        {
            positions.pop_back();
        }
        if (!positions.empty())
        {
            next[i] = positions.back();
        }
    }
    return next;
}

std::pair<std::vector<int>, std::vector<int>> performBFS(const std::vector<int>& next)
{
    int N = next.size();
    std::vector<int> distance(N, -1);
    std::vector<int> parent(N, -1);
    std::queue<int> q;
    
    q.push(0);
    distance[0] = 0;
    int current_max = 0;
    
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        
        if (u == N - 1) break;
        
        int reach = (next[u] == -1) ? u : next[u];
        if (reach > current_max)
        {
            for (int v = current_max + 1; v <= reach && v < N; ++v) {
                if (distance[v] == -1)
                {
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
            }
            current_max = std::max(current_max, reach);
        }
    }
    
    return {distance, parent};
}

void printPath(const std::vector<int>& parent, int N, std::ofstream& output)
{
    if (parent[N - 1] == -1)
    {
        output << "0" << std::endl;
        return;
    }
    
    std::vector<int> path;
    for (int v = N - 1; v != -1; v = parent[v])
    {
        path.push_back(v + 1);
    }
    std::reverse(path.begin(), path.end());
    
    output << path.size() - 1 << std::endl;
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        output << path[i] << " ";
    }
    output << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cout << "Cannot open input file: " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output)
    {
        std::cout << "Cannot open output file: " << argv[2] << std::endl;
        return 1;
    }

    int N;
    std::vector<int> a = readInput(N, input);
    std::vector<int> next = buildNextArray(a);
    auto [distance, parent] = performBFS(next);
    printPath(parent, N, output);

    input.close();
    output.close();
    
    return 0;
}
