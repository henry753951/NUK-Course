
#include <vector>
using namespace std;

class InsertionSort {
   public:
    static void sort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            int j = i - 1;
            int key = nums[i];
            while (j >= 0 && nums[j] > key) {
                nums[j + 1] = nums[j];
                j--;
            }
            nums[j + 1] = key;
        }
    }
};
