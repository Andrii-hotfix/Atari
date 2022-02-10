#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0)
            return -1;

        int subarraySize = nums.size();
        int startingPoint = 0;
        int currIndex = static_cast<int>(floor(subarraySize / 2));
        
        while (true) {
            if (currIndex < nums.size() and nums[currIndex] == target)
                return currIndex;
            if (subarraySize == 0)
                return -1;
            
            subarraySize = static_cast<int>(floor((subarraySize - 1) / 2));
            if (target > nums[currIndex])
                startingPoint = currIndex + 1;

            currIndex = startingPoint + static_cast<int>(floor(subarraySize / 2));
        }
    }
};

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> toSearchIn = {-1};
    cout << sol.search(toSearchIn, 2) << endl;
    return 0;
}
