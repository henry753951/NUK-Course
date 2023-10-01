# Qucik Sort

## 1. 介紹

快速排序法（Quick Sort）是一種常見的排序演算法，也是一種分治法（Divide and Conquer）的典型例子。

## 2. 步驟

1. 選擇一個基準元素（pivot）。可以選擇未排序序列的第一個元素作為基準元素。
2. 將序列分割為兩個子序列：一個小於等於基準元素的子序列和一個大於基準元素的子序列。
3. 對於兩個子序列，分別遞迴地使用快速排序算法。即對小於等於基準元素的子序列和大於基準元素的子序列分別執行步驟 1 和步驟 2。
4. 當遞迴的子序列的 left 和 right 相等時，結束遞迴。

## 3. 程式碼

```cpp
static void quicksort(vector<int>& nums, int low, int high) {
    if (low >= high) return;
    int i = low, j = high;
    int standard = nums[low];

    while (i < j) {
        while (i < j && nums[j] >= standard) j--;
        while (i < j && nums[i] <= standard) i++;
        if (i < j) swap(nums[i], nums[j]);
    }
    swap(nums[low], nums[i]);

    quicksort(nums, low, i - 1);
    quicksort(nums, i + 1, high);

}
```

## 4. 執行結果

```
> g++ Main.cpp -o Main ; .\Main
Before sorting: 19 29 2 27 3 23 5 9 8 0
After sorting: 0 2 3 5 8 9 19 23 27 29
```

## 5. Analysis


#### Best case | **O(nlogn)**
當每次找到的基準元素都是該序列的中間，每次遞迴都可以將序列分成兩個相等的子序列，此時時間複雜度為**O(nlogn)**。
這樣每一次遞迴都可以將序列分成兩個相等的子序列，遞迴深度為**logn**。
每一層遞迴的要處理的元素為n格，所以時間複雜度為**O(n)**。
所以時間複雜度為**O(nlogn)**。

#### Worst case | **O(n^2)**
當每次找到的基準元素都是該序列的**最大**或**最小**。
每次遞迴都只能將序列分成一個元素和其他元素的子序列，也就是只能排左半邊和右半邊。
此時時間複雜度為**O(n^2)**。

#### Average case | **O(nlogn)**
s 是基準元素將序列分成大小為 s 和 n-s 的兩個子序列
$T(n)$ 表示對 n 個元素進行快速排序的平均時間複雜度


