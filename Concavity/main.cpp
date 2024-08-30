#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        //initial state :  If there are less than 3 bars, no water can be trapped.
        if (n <= 2)
            return 0;

        int water = 0, left = 0, start = 0, min_height = 0, max_right = 0, max_right_idx = 0;
        int i = 0;

        while (i < n - 1) {
            // Find the start of a concavity.
            while (i < n - 1 && height[i + 1] >= height[i]) {
                i++;
            }

            left = height[i];
            start = i;
            i++;

            // Find the end of the concavity.
           max_right = 0, max_right_idx = i;
            while (i < n && height[i] < left) {
                if (height[i] > max_right) {
                    max_right = height[i];
                    max_right_idx = i;
                }
                i++;
            }

            // If we found a valid right boundary, calculate trapped water.
            if (i < n) {
                min_height = min(left, height[i]);
                for (int j = start + 1; j < i; j++) {
                    water += max(0, min_height - height[j]);
                }
            } else {
                // If no valid right boundary found, use the maximum height inside the concavity.
                if (max_right > 0) {
                    min_height = min(left, max_right);
                    for (int j = start + 1; j <= max_right_idx; j++) {
                        water += max(0, min_height - height[j]);
                    }
                }
            }
        }

        return water;
    }
};


int main() {
    Solution solution;
    vector<int> height = {0,2,3,1,0,1,2,1,0,3,1};
    int result = solution.trap(height);
    cout << "Trapped water: " << result << endl;
    return 0;
}
