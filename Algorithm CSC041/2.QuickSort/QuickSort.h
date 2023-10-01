#include <vector>
using namespace std;

class QuickSort {
   public:
    static void sort(vector<int>& nums) {
        quicksort(nums, 0, nums.size() - 1);
    }

   private:
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
    static void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};
