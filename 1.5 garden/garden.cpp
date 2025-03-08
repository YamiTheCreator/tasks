#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>

struct Rect
{
    int x1, y1, x2, y2;
    long long area() const
    {
        return static_cast<long long>(x2 - x1) * static_cast<long long>(y2 - y1);
    }
};

bool intersects(const Rect& a, const Rect& b)
{
    bool x_overlap = a.x1 < b.x2 && a.x2 > b.x1;
    bool y_overlap = a.y1 < b.y2 && a.y2 > b.y1;
    return x_overlap && y_overlap;
}

void readInput(int& n, int& m, int& a, int& b, std::vector<Rect>& buildings,
               std::set<int>& x_set, std::set<int>& y_set, std::ifstream& input)
{
    input >> n >> m >> a >> b;
    
    x_set.insert(0);
    x_set.insert(a);
    y_set.insert(0);
    y_set.insert(b);
    for (int i = 0; i < n; ++i)
    {
        int x1, y1, x2, y2;
        input >> x1 >> y1 >> x2 >> y2;
        buildings.push_back(Rect{x1, y1, x2, y2});
        x_set.insert(x1);
        x_set.insert(x2);
        y_set.insert(y1);
        y_set.insert(y2);
    }
}

std::vector<Rect> findFreeRectangles(const std::vector<int>& x_coords,
                                    const std::vector<int>& y_coords,
                                    const std::vector<Rect>& buildings)
{
    std::vector<Rect> free_rects;
    
    for (int i = 0; i < x_coords.size(); ++i)
    {
        for (int j = i + 1; j < x_coords.size(); ++j)
        {
            int x1 = x_coords[i];
            int x2 = x_coords[j];
            for (int k = 0; k < y_coords.size(); ++k)
            {
                for (int l = k + 1; l < y_coords.size(); ++l)
                {
                    int y1 = y_coords[k];
                    int y2 = y_coords[l];
                    Rect r{x1, y1, x2, y2};
                    bool free = true;
                    for (const auto& b : buildings)
                    {
                        if (intersects(r, b))
                        {
                            free = false;
                            break;
                        }
                    }
                    if (free)
                    {
                        free_rects.push_back(r);
                    }
                }
            }
        }
    }
    return free_rects;
}

void handleSingleRectangle(const std::vector<Rect>& free_rects, std::ofstream& output)
{
    Rect best = free_rects[0];
    output << best.area() << "\n";
    output << best.x1 << " " << best.y1 << " " << best.x2 << " " << best.y2 << "\n";
}

std::pair<Rect, Rect> findBestPair(const std::vector<Rect>& free_rects, long long& max_sum)
{
    std::pair<Rect, Rect> best = {free_rects[0], Rect{0,0,0,0}};
    max_sum = free_rects[0].area();
    
    for (int i = 0; i < free_rects.size(); ++i)
    {
        for (int j = i + 1; j < free_rects.size(); ++j)
        {
            long long current_sum = free_rects[i].area() + free_rects[j].area();
            if (current_sum <= max_sum)
            {
                break;
            }
            if (!intersects(free_rects[i], free_rects[j]))
            {
                max_sum = current_sum;
                best = {free_rects[i], free_rects[j]};
            }
        }
    }
    return best;
}

void printOutput(const std::vector<Rect>& output, int m, std::ofstream& out)
{
    for (int i = 0; i < m; ++i)
    {
        if (i < output.size() && output[i].area() > 0)
        {
            out << output[i].x1 << " " << output[i].y1 << " "
                << output[i].x2 << " " << output[i].y2 << "\n";
        }
        else
        {
            out << "0 0 0 0\n";
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " input_file output_file\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input || !output)
    {
        std::cout << "Error opening files\n";
        return 1;
    }

    int n, m, a, b;
    std::vector<Rect> buildings;
    std::set<int> x_set, y_set;
    
    readInput(n, m, a, b, buildings, x_set, y_set, input);
    
    std::vector<int> x_coords(x_set.begin(), x_set.end());
    std::vector<int> y_coords(y_set.begin(), y_set.end());
    std::sort(x_coords.begin(), x_coords.end());
    std::sort(y_coords.begin(), y_coords.end());
    
    std::vector<Rect> free_rects = findFreeRectangles(x_coords, y_coords, buildings);
    
    if (free_rects.empty())
    {
        output << "0\n";
        for (int i = 0; i < m; ++i)
        {
            output << "0 0 0 0\n";
        }
        return 0;
    }
    
    std::sort(free_rects.begin(), free_rects.end(),
              [](const Rect& a, const Rect& b) { return a.area() > b.area(); });
    
    if (m == 1)
    {
        handleSingleRectangle(free_rects, output);
    }
    else
    {
        long long max_sum = 0;
        std::pair<Rect, Rect> best = findBestPair(free_rects, max_sum);
        
        output << max_sum << "\n";
        std::vector<Rect> result;
        
        if (max_sum == 0)
        {
            result.resize(2, Rect{0,0,0,0});
        }
        else
        {
            result.push_back(best.first);
            result.push_back(best.second);
            while (result.size() < 2)
            {
                result.push_back(Rect{0,0,0,0});
            }
        }
        
        printOutput(result, m, output);
    }

    input.close();
    output.close();
    return 0;
}
