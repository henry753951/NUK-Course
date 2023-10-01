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
    point *buffer;
    void add(point p) {
        points.push_back(p);
    }
    void remove(int index) {
        points.erase(points.begin() + index);
    }
    int size() {
        return points.size();
    }
    void initBuffer() {
        buffer = new point[points.size()];
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
        int leftIndex, rightIndex, k;
        int counts = 0;
        for (leftIndex = left, rightIndex = mid, k = left; leftIndex < mid && rightIndex < right; k++) {
            if (points[leftIndex].y < points[rightIndex].y) {
                buffer[k] = points[leftIndex];
                // 計算左邊有幾個y小於 points[rightIndex].y
                // ppt上的 middle 右側由y值決定 的值
                ++counts;
                ++leftIndex;
            } else if (points[rightIndex].y <= points[leftIndex].y) {
                // 當換右變選中元素比較小時，那就把他排進buffer
                // 也就是說 buffer裡排比他前面的 都是y比他小的元素 += rank
                buffer[k] = points[rightIndex];
                buffer[k].rank += counts;
                ++rightIndex;
            }
        }
        // buffer 會是每一輪由y去從小排到大的結果


        // 下面兩個for 是當某一個子範圍的元素已經全部放入 buffer 但另一個子範圍還有剩
        for (; leftIndex < mid; ++leftIndex, ++k) {
            buffer[k] = points[leftIndex];
        }

        for (; rightIndex < right; ++rightIndex, ++k) {
            buffer[k] = points[rightIndex];
            // 這邊要 count++ 是因為右子範圍的元素 points[rightIndex] 被放入 buffer 前
            // 已經有 counts 個buffer內的元素的 y 值小於它
            buffer[k].rank += counts;
        }

        // cp buffer to points
        for (int i = left; i < right; ++i) {
            points[i] = buffer[i];
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
    container.initBuffer();
    sort(container.points.begin(), container.points.end());

    for (point p : container.points) {
        cout << p.to_string() << " ";
    }
    cout << endl;
    container.Ranking(0, container.size());

    sort(container.points.begin(), container.points.end(), [](point a, point b) { return a.index <= b.index; });
    for (point p : container.points)
        cout << p.rank << " ";
    cout << endl;

    return 0;
}