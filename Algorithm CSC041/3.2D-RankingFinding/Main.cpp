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
    int rank;
    point() {
    }
    point(int index, int x, int y) {
        this->x = x;
        this->y = y;
        this->index = index;
        this->rank = 0;
    }
    string to_string() {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ") ";
    }
    bool operator<(const point &other) const {
        return this->x == other.x ? this->y > other.y : this->x < other.x;
    }
};

class PointContainer {
   public:
    vector<point> points;
    void add(point p) {
        points.push_back(p);
    }
    void remove(int index) {
        points.erase(points.begin() + index);
    }
    int size() {
        return points.size();
    }

    void Ranking(int lower, int upper) {
        if (upper - lower <= 1)
            return;
        int middle = (lower + upper) / 2;
        Ranking(lower, middle);
        Ranking(middle, upper);
        merge(lower, middle, upper);
    }
    void merge(int left, int mid, int right) {
        int leftIndex = left, rightIndex = mid + 1;
        int top = 0, d = 0, i;
        while(leftIndex <= mid && rightIndex <= right ){
            if(points[leftIndex].y < points[rightIndex].y){}
        }
    };
};

int main() {
    string input = "(0, 5) (1, 3) (1, 8) (2, 1) (2, 6) (3, 5) (4, 0) (4, 7) (5, 7) (5, 9) (6, 1) (7, 2) (7, 8) (8, 2) (8, 3) (9, 1) (9, 4) ";
    PointContainer container;
    int index = 0;
    while (input.length() > 0) {
        int x = stoi(input.substr(1, input.find(",") - 1));
        int y = stoi(input.substr(input.find(",") + 1, input.find(")") - input.find(",") - 1));
        point p(index++, x, y);
        container.add(p);
        input = input.substr(input.find(")") + 2);
    }
    if (container.size() <= 0) throw "No points inputted";

    // Find middle line for x
    sort(container.points.begin(), container.points.end());
    container.Ranking(0, container.size());

    sort(container.points.begin(), container.points.end(), [](point a, point b) { return a.index <= b.index; });
    for (point p : container.points) {
        cout << p.to_string() + ":" + to_string(p.rank) << endl;
    }

    return 0;
}