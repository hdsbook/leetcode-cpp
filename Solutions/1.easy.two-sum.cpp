#include "gtest/gtest.h"
using namespace std;

// 暴力解
class ViolentSolution
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    return vector<int>{i, j};
                }
            }
        }
        return vector<int>{};
    }
};

// 較佳解
class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
        map<int, int> dict;

        for (int i = 0; i < nums.size(); i++)
        {
            int current_num = nums[i];
            int complement = target - current_num;
            if (dict.count(current_num))
            {
                return vector<int>{dict[current_num], i};
            }

            dict[complement] = i; // 紀錄對應補數需要的索引為 current_num 的索引
        }
        return vector<int>{};
    }
};


// Test fixture
class test_fixture_1 : public ::testing::TestWithParam<tuple<vector<int>, int, vector<int>>>
{
protected:
    // ViolentSolution sut;
    Solution sut; // system under test (SUT) 待測物件
};


// Test Method
TEST_P(test_fixture_1, solution_test)
{
    // given 測資
    auto params = GetParam();
    vector<int> nums = get<0>(params);
    auto target = get<1>(params);
    auto expected = get<2>(params);

    // when 執行 solution
    auto result = sut.twoSum(nums, target);

    // then 驗證結果正確
    ASSERT_EQ(expected, result);
}


// Test Cases
INSTANTIATE_TEST_CASE_P(
    TestCases,
    test_fixture_1,
    ::testing::Values(
        make_tuple(vector<int> {2, 7, 11, 15}, 9, vector<int> {0, 1}),
        make_tuple(vector<int> {3, 2, 4}, 6, vector<int> {1, 2})
    ));
