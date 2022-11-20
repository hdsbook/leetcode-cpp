#include "gtest/gtest.h"
using namespace std;

/**
 * 最佳解 O(n) 但用到最少的記憶體
 */
class Solution
{
public:
    int reverse(int x)
    {
        int sign = x > 0 ? 1 : -1;
        x = abs(x);

        int ans = 0;
        int limit_max = INT_MAX / 10;
        int limit_min = INT_MIN / 10;
        while (x != 0)
        {
            if (ans > limit_max || ans < limit_min) return 0;
            
            ans = ans * 10 + x % 10;
            x = x / 10;
        }

        return ans * sign;
    }
};


// Test fixture
class test_fixture_7 : public ::testing::TestWithParam<tuple<int, int>>
{
protected:
    Solution sut; // system under test (SUT) 待測物件
};


// Test Method
TEST_P(test_fixture_7, solution_test)
{
    // given 測資
    auto params = GetParam();
    int x = get<0>(params);
    int expected = get<1>(params);

    // when 執行 solution
    auto result = sut.reverse(x);

    // then 驗證結果正確
    EXPECT_EQ(expected, result);
}


// Test Cases
INSTANTIATE_TEST_CASE_P(
    TestCases,
    test_fixture_7,
    ::testing::Values(
        make_tuple(123, 321),
        make_tuple(-123, -321),
        make_tuple(120, 21),
        make_tuple(10, 1)
    ));
