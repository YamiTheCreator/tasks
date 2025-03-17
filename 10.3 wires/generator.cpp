#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::ofstream out("input.txt");

    std::srand(std::time_t(nullptr));

    int N = 10000;
    int K = 10000;

    out << N << " " << K << std::endl;

    for (int i = 0; i < N; ++i)
    {
        int length = 100 + std::rand() % 10000000;
        out << length << std::endl;
    }

    std::cout << "Test file input.txt created successfully." << std::endl;
    return 0;
}
