#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int trap(vector<int>& height) {
        // If the height vector is empty, no water can be trapped.
        if (height.empty()) return 0;

        int left = 0, right = height.size() - 1, leftMax = 0, rightMax = 0, trappedWater = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    trappedWater += leftMax - height[left];
                }
                left++;
            } else {

                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    trappedWater += rightMax - height[right];
                }
                right--;
            }
        }
        return trappedWater;
    }
};



int main() {
    Solution solution;
    vector<int> height = {0,2,3,1,0,1,2,1,0,3,1};
    int result = solution.trap(height);
    cout << "Trapped water: " << result << endl;
    return 0;
}
