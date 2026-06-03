#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        // Need at least 3 bars to trap any water.
        if (n <= 2) return 0;

        int water = 0;
        int i = 0;

        while (i < n - 1) {
            // 1) Climb to the top of the current left wall (a local peak).
            while (i < n - 1 && height[i + 1] >= height[i]) {
                i++;
            }
            int left  = height[i];   // height of the left wall
            int start = i;           // index of the left wall
            i++;

            // 2) Scan right for a wall >= left, while remembering the tallest
            //    interior bar (our fallback right boundary).
            int max_right = 0, max_right_idx = i;
            while (i < n && height[i] < left) {
                if (height[i] > max_right) {
                    max_right     = height[i];
                    max_right_idx = i;
                }
                i++;
            }

            if (i < n) {
                // 3a) Found a real right wall (>= left). The fill level is `left`
                //     because every bar strictly between start and i is < left.
                for (int j = start + 1; j < i; j++) {
                    water += left - height[j];
                }
                // Leave i on the right wall: it becomes the next left wall.
            } else if (max_right > 0) {
                // 3b) No wall as tall as `left` exists to the right. Fill only up
                //     to the tallest interior bar, then RESTART from that bar,
                //     treating it as a new left wall. This restart is the part the
                //     original version was missing.
                int level = min(left, max_right);
                for (int j = start + 1; j <= max_right_idx; j++) {
                    water += max(0, level - height[j]);
                }
                i = max_right_idx;   // <-- the critical fix
            }
            // else: nothing taller than a flat/descending tail remains; loop ends.
        }
        return water;
    }
};

int main() {
    Solution solution;
    vector<int> height = {0,2,3,1,0,1,2,1,0,3,1};
    cout << "Trapped water: " << solution.trap(height) << endl;  // 13
    return 0;
}
