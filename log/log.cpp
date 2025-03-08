#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

size_t Cutter(const int l,const int n)
{
    size_t cost = 0;
    std::priority_queue<int, std::vector<int>, std::greater<>> cutters;
    for (int i = 0; i < n; i++)
    {
        cutters.push(1);
    }
    cutters.push(l - n);

    while (cutters.size() > 1)
    {
        const int left = cutters.top();
        cutters.pop();
        const int right = cutters.top();
        cutters.pop();

        int connectedTimber = left + right;
        cost += connectedTimber;
        cutters.push(connectedTimber);
    }

    return cost;
}

int main(int argc, const char * argv[]) {
    
    if (argc != 3)
    {
        std::cout << "Use: ./log input.txt output.txt" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream input(argv[1]);
    
    if (!input)
    {
        std::cerr << "ERROR" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ofstream output(argv[2]);
    
    if (!output)
    {
        std::cerr << "ERROR" << std::endl;
        return EXIT_FAILURE;
    }

    
    int l, n;
    input >> l >> n;

    size_t sum = Cutter(l, n);
    
    output << sum << std::endl;
    
    input.close();
    output.close();
    
    return EXIT_SUCCESS;
}
