//11.6. Длина линии (6)
//Имеется круг радиуса R с центром в начале координат. Заданы две точки (X1, Y1) и (X2, Y2). Требуется найти минимальную длину линии, соединяющей эти точки, но не пересекающей внутренность круга.
//Ввод из файла INPUT.TXT. В первой строке находится целое число N – количество блоков входных данных. Далее следуют N строк, каждая из которых содержит пять вещественных чисел через пробел – X1, Y1, X2, Y2 и R.
//Вывод в файл OUTPUT.TXT. Для каждого блока входных данных выводится одно вещественное число с тремя знаками после запятой - минимальная длина линии.
//Пример
//Ввод
//2
//1 1 -1 -1 1
//1 1 -1 1 1
//Вывод
//3.571
//2.000


#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>

const double PI = 3.14159265358979323846;
const double EPS = 1e-9;

double distance(double x1, double y1, double x2, double y2)
{
    return std::hypot(x2 - x1, y2 - y1);
}

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Проверка, что прямая между p1 и p2 пересекает круг радиуса r
bool lineIntersectsCircle(Point p1, Point p2, double r)
{
    double a = p2.y - p1.y;
    double b = p1.x - p2.x;
    double c = p2.x * p1.y - p1.x * p2.y;
    double dist = std::abs(c) / std::hypot(a, b);
    return dist < r + EPS;
}

// Найти точки касания из внешней точки к кругу
std::vector<Point> getTangentPoints(Point p, double r)
{
    double d = distance(p.x, p.y, 0, 0);
    if (d < r - EPS) return {}; // Точка внутри круга
    
    double theta = std::atan2(p.y, p.x);
    double phi = std::acos(r/d);
    
    return
    {
        Point(r * std::cos(theta + phi), r * std::sin(theta + phi)),
        Point(r * std::cos(theta - phi), r * std::sin(theta - phi))
    };
}

double solve(double x1, double y1, double x2, double y2, double r)
{
    Point A(x1, y1), B(x2, y2);
    double dA = distance(A.x, A.y, 0, 0);
    double dB = distance(B.x, B.y, 0, 0);
    
    // Обе точки внутри круга
    if (dA < r - EPS && dB < r - EPS) return 0.0;
    
    // Одна точка внутри, другая снаружи
    if ((dA < r - EPS) != (dB < r - EPS)) return 0.0;
    
    // Обе точки снаружи, прямая не пересекает круг
    if (!lineIntersectsCircle(A, B, r))
        return distance(A.x, A.y, B.x, B.y);
    
    // Находим пути через касательные
    auto tangentsA = getTangentPoints(A, r);
    auto tangentsB = getTangentPoints(B, r);
    
    double min_path = INFINITY;
    for (Point ta : tangentsA)
    {
        for (Point tb : tangentsB)
        {
            // Длина пути: A -> ta -> дуга -> tb -> B
            double path = distance(A.x, A.y, ta.x, ta.y) + distance(tb.x, tb.y, B.x, B.y);
            
            // Угол между точками касания
            double angle = std::abs(std::atan2(ta.y, ta.x) - std::atan2(tb.y, tb.x));
            angle = std::min(angle, 2*PI - angle);
            path += r * angle;
            
            min_path = std::min(min_path, path);
        }
    }
    return min_path;
}

int main(int argc, char* argv[])
{
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    fout << std::fixed << std::setprecision(3);
    
    int n;
    fin >> n;
    while (n--)
    {
        double x1, y1, x2, y2, r;
        fin >> x1 >> y1 >> x2 >> y2 >> r;
        double result = solve(x1, y1, x2, y2, r);
        fout << (result < INFINITY ? result : 0.0) << '\n';
    }
}
