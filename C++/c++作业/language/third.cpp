#include <iostream>
#include <vector>
using namespace std;

class LongestIncreasingSubsequence
{
public:
    static pair<int, vector<int>> findLongestIncreasingSubsequence(const vector<int> &nums)
    {

        int maxLength = 0;
        vector<int> longestSubsequence;

        int len = size(nums);
        int longest[len];
        for (int i = 0; i < len; i++)
            longest[i] = 1;
        for (int i = 1; i < len; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j] && longest[i] < longest[j] + 1)
                {
                    longest[i] = longest[j] + 1;
                }
            }
        }
        for (int i = 0; i < len; i++)
        {
            if (longest[i] > maxLength)
                maxLength = longest[i];
        }
        for(int i=1;i<=maxLength;i++){
            for(int j=0;j<len;j++){
                if(longest[j]==i){
                    longestSubsequence. push_back(nums[j]);
                    break;
                }
            }
        }
        return {maxLength, longestSubsequence};
    }
};

int main()
{
    vector<int> input = {10, 22, 9, 33, 21, 50, 41, 60, 80};

    auto result = LongestIncreasingSubsequence::findLongestIncreasingSubsequence(input);

    cout << "Longest Increasing Subsequence: ";
    for (int num : result.second)
    {
        cout << num << " ";
    }
    cout << endl;

    cout << "Length of Longest Increasing Subsequence: " << result.first << endl;

    return 0;
}
