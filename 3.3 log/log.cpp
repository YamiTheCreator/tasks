#include <iostream>
#include <vector>
#include <span>
#include <fstream>
 
int GetSum(std::span<int> cutters)
{
    size_t n = cutters.size() - 1;
    if (n == 1) return 0;
 
    int cur = cutters[n] - cutters[0];
    int buf  = 0;
    for (int i = 1; i < n; i++)
    {
        int l = GetSum(cutters.first(i + 1));
        int r = GetSum(cutters.last(n - i + 1));
        int p = l + r;
 
        if (!buf || buf > p)
            buf = p;
    }
 
    return cur + buf;
}

std::vector<int> FillVector (std::ifstream& input, const int& l, const int& n)
{
    std::vector<int> vector = {0};
    int num;
    
    while (input >> num)
    {
        vector.push_back(num);
    };
    
    vector.push_back(l);
    
    return vector;
}
 
int main(int argc, char* argv[])
{
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    
    if (argc != 3)
    {
        std::cout << "Use: ./log input.txt output.txt" << std::endl;
        return EXIT_FAILURE;
    }
    
    if (!input)
    {
        std::cout << "Cannot open input file!" << std::endl;
        return EXIT_FAILURE;
    }
    
    if (!output)
    {
        std::cout << "Cannot open output file!" << std::endl;
        return EXIT_FAILURE;
    }
    
    int l, n;
    
    input >> l >> n;
    
    std::vector<int> cutters = FillVector(input, l, n);
    output << GetSum(cutters) << std::endl;
    
    input.close();
    output.close();
    return EXIT_SUCCESS;
}
