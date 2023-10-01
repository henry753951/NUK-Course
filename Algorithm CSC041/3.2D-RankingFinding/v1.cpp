#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class point {
   public:
    int x;
    int y;
    int index;
    point() {
    }
    point(int index, int x, int y) {
        this->x = x;
        this->y = y;
        this->index = index;
    }
    string to_string() {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ") ";
    }
    bool operator<(const point &other) const {
        return this->x == other.x ? this->y > other.y : this->x < other.x;
    }
};

class pointContainer {
   public:
    vector<point> points;
    std::vector<int> rank;
    void add(point p) {
        points.push_back(p);
    }
    void remove(int index) {
        points.erase(points.begin() + index);
    }
    int size() {
        return points.size();
    }

    std::vector<point> findRank(std::vector<point> p) {
        if (p.size() <= 1)
            return p;
        size_t i = 0, li = 0, ri = 0;
        std::vector<point> l = findRank(std::vector<point>(p.begin(), p.begin() + p.size() / 2));
        std::vector<point> r = findRank(std::vector<point>(p.begin() + p.size() / 2, p.end()));
        while (true) {
            if (l[li].y < r[ri].y) {
                p[i] = l[li];
                li++;
                if (li >= l.size()) {
                    for (auto tmp = r.begin() + ri; tmp != r.end(); ++tmp, ++i) {
                        rank[tmp->index] += li;
                        p[i + 1] = *tmp;
                    }
                    break;
                }
            } else {
                p[i] = r[ri];
                rank[r[ri].index] += li;
                ri++;
                if (ri >= r.size()) {
                    std::copy(l.begin() + li, l.end(), p.begin() + i + 1);
                    break;
                }
            }
            ++i;
        }
        return p;
    }
};

int main() {
    string input = "(0, 5) (1, 3) (1, 8) (2, 1) (2, 6) (3, 5) (4, 0) (4, 7) (5, 7) (5, 9) (6, 1) (7, 2) (7, 8) (8, 2) (8, 3) (9, 1) (9, 4) ";
    pointContainer container;
    int index = 0;
    while (input.length() > 0) {
        int x = stoi(input.substr(1, input.find(",") - 1));
        int y = stoi(input.substr(input.find(",") + 1, input.find(")") - input.find(",") - 1));
        point p(index++, x, y);
        container.add(p);
        input = input.substr(input.find(")") + 2);
    }
    if (container.size() <= 0) throw "No points inputted";
    container.rank = std::vector<int>(index, 0);
    // Find middle line for x
    sort(container.points.begin(), container.points.end());
    container.findRank(container.points);

    sort(container.points.begin(), container.points.end(), [](point a, point b) { return a.index <= b.index; });
    for (int r : container.rank) {
        cout << r << " " ;
    }
    cout << endl;

    return 0;
}