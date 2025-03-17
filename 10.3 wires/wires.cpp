//10.3. Провода (5)
//Дано N отрезков провода длиной L1, L2, ..., LN сантиметров. Требуется с помощью разрезания получить из них K равных отрезков как можно большей длины, выражающейся целым числом сантиметров. Если нельзя получить K отрезков длиной даже 1 см, вывести 0.
//Ограничения: 1 ≤ N ≤ 10 000, 1 ≤ K ≤ 10 000, 100 ≤ Li ≤ 10 000 000, все числа целые, время 1 с.
//Ввод из файла INPUT.TXT. В первой строке находятся через пробел числа N и К. В следующих N строках - L1, L2, ..., LN, по одному числу в строке.
//Вывод в файл INPUT.TXT. Вывести одно число - полученную длину отрезков.
//Пример
//Ввод
//4 11
//802
//743
//457
//539
//Вывод
//200


#include <iostream>
#include <fstream>
#include <vector>

bool openFiles(const char* inputPath, const char* outputPath, std::ifstream& in, std::ofstream& out)
{
    in.open(inputPath);
    out.open(outputPath);
    
    if (!in.is_open())
    {
        std::cerr << "Error: cannot open input file " << inputPath << std::endl;
        return false;
    }
    if (!out.is_open())
    {
        std::cerr << "Error: cannot open output file " << outputPath << std::endl;
        return false;
    }
    return true;
}

std::vector<int> readInput(std::ifstream& in, int& N, int& K, long long& sum_all)
{
    in >> N >> K;
    std::vector<int> lengths(N);
    sum_all = 0;
    
    for (int i = 0; i < N; ++i)
    {
        in >> lengths[i];
        sum_all += lengths[i];
    }
    
    return lengths;
}

long long countPieces(const std::vector<int>& lengths, long long pieceLength, int K)
{
    long long cnt = 0;
    for (int l : lengths)
    {
        cnt += l / pieceLength;
        if (cnt >= K) break;
    }
    return cnt;
}

long long binarySearch(const std::vector<int>& lengths, long long sum_all, int K)
{
    long long left = 1;
    long long right = sum_all / K;
    long long ans = 0;
    
    while (left <= right)
    {
        long long mid = (left + right) / 2;
        long long cnt = countPieces(lengths, mid, K);
        
        if (cnt >= K)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    
    return ans;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Using: " << argv[0] << " <input.txt> <output.txt>" << std::endl;
        return 1;
    }

    std::ifstream in;
    std::ofstream out;
    
    if (!openFiles(argv[1], argv[2], in, out))
    {
        return 1;
    }

    int N, K;
    long long sum_all;
    std::vector<int> lengths = readInput(in, N, K, sum_all);
    
    if (sum_all < K)
    {
        out << 0 << std::endl;
        return 0;
    }

    long long result = binarySearch(lengths, sum_all, K);
    out << result << std::endl;
    
    in.close();
    out.close();
    return 0;
}
