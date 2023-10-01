# 2D-RankingFinding A1105534 張宏宇

## 1. 介紹

2D-RankingFinding 是一種基於分治法（Divide and Conquer）的演算法，用於在二維數據集中查找元素的排名。

## 2. 步驟

1. 將二維數據集分割為更小的子問題。通常是將數據集分成四個相等的區域。
2. 對每個子問題遞迴地 2DRankingFinding。
3. 在每個子問題中，通過比較元素的值來確定它的排名。
4. 根據子問題的排名結果，選擇適當的子問題進行進一步的遞迴，直到找到所有元素的排名。

## 3. 程式碼

```cpp
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
    for (leftIndex = left, rightIndex = mid, k = left; leftIndex < mid && rightIndex < right; ++k) {
        if (points[leftIndex].y < points[rightIndex].y) {
            buffer[k] = points[leftIndex];
            ++counts;
            ++leftIndex;
        } else if (points[leftIndex].y >= points[rightIndex].y)  {
            buffer[k] = points[rightIndex];
            buffer[k].rank += counts;
            ++rightIndex;
        }
    }

    for (; leftIndex < mid; ++leftIndex, ++k) {
        buffer[k] = points[leftIndex];
    }

    for (; rightIndex < right; ++rightIndex, ++k) {
        buffer[k] = points[rightIndex];
        buffer[k].rank += counts;
    }

    // cp buffer to points
    for (int i = left; i < right; ++i) {
        points[i] = buffer[i];
    }
};

```

## 4. 執行結果

```
> g++ Main.cpp -o Main ; .\Main
After sorting: 0 0 1 0 2 2 0 5 6 8 1 3 9 3 4 1 7
```

## 5. Analysis
![lagrida_latex_editor (2)](https://github.com/henry753951/NUK-Course/assets/31657781/753826ca-ac59-48ce-829b-90ad28b6b613)


**LaTex在註解裡面**
<!-- \begin{aligned}
T(n)&=O(n)+2T(\frac{n}{2})+O(nlogn)\\
&\le 2T(\frac n2)+c_1nlogn+c_2n \\
&\le 2T(\frac n2) + cnlogn \\
&\le 4T(\frac n4) + cnlog\frac n2 + cnlogn \\
&\le nT(1)+c\left( nlogn+nlog \frac n2 + nlog \frac n4 +....+nlog2 \right) \\ \\  \\

&\left( nlogn+nlog \frac n2 + nlog \frac n4 +....+nlog2 \right) \\
&=nlogn+nlog \frac n2 + nlog \frac n4 +....+nlog\frac{\frac{n}{n}}{2} \\
&=logn + (logn - log2)+(logn - log4)+....+(logn - log\frac n2)\\
&=logn \times logn-(1+2+3+...+log\frac n2)\\
&=logn \times logn-\frac{(1+log\frac n2)\times log\frac n2}{2} \\
&=\frac {logn}2(2logn-logn \frac n2) \\
&=\frac {logn}2(2logn-logn + log2) \\
&=\frac {logn}2(logn+log2) \\ \\ \\


&nT(1)+c\left( nlogn+nlog \frac n2 + nlog \frac n4 +....+nlog2 \right)\\
&=nT(1)+\frac{cnlogn(logn+log2)}{2} \\
&=O(nlog^2n)
\end{aligned} -->

