#include "gtest/gtest.h"
using namespace std;

/**
 * 一般解
 */
class CommonSolution
{
public:
    string convert(string s, int numRows)
    {
        numRows = min(numRows, int(s.size()));
        if (numRows == 1)
        {
            return s;
        }

        vector<string> rows(numRows); // 初始化具有空值的 rows

        int index = 0;
        int dir = 1;
        for (char c : s)
        {
            rows[index] += c;
            index += dir;
            if (index == 0 || index == numRows - 1) dir *= -1;
        }

        string result = "";
        for (int i = 0; i < numRows; i++)
        {
            result += rows[i];
        }
        return result;
    }
};

/**
 * 最佳解 O(n) 但用到最少的記憶體
 */
class Solution
{
public:
    string convert(string s, int numRows)
    {
        numRows = min(numRows, int(s.size()));
        if (numRows == 1)
        {
            return s;
        }

        int n = int(s.size());
        int cycleNum = numRows * 2 - 2; // 循環到下一個同位置的點需經過的字數

        string result = "";
        for (int index = 0; index < numRows; index++)
        {
            for (int offset = 0; index + offset < n; offset += cycleNum)
            {
                result += s[index + offset];
                if (index != 0 && index != numRows - 1 &&
                    cycleNum - index + offset < n)
                {
                    result += s[cycleNum - index + offset]; // 若非端點，要加入中間斜線上的點
                }
            }
        }
        return result;
    }
};


// Test fixture
class test_fixture_6 : public ::testing::TestWithParam<tuple<string, int, string>>
{
protected:
    Solution sut; // system under test (SUT) 待測物件
};


// Test Method
TEST_P(test_fixture_6, solution_test)
{
    // given 測資
    auto params = GetParam();
    string s = get<0>(params);
    int numRows = get<1>(params);
    string expected = get<2>(params);

    // when 執行 solution
    auto result = sut.convert(s, numRows);

    // then 驗證結果正確
    EXPECT_EQ(expected, result);
}


// Test Cases
INSTANTIATE_TEST_CASE_P(
    TestCases,
    test_fixture_6,
    ::testing::Values(
        make_tuple("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"),
        make_tuple("PAYPALISHIRING", 4, "PINALSIGYAHRPI"),
        make_tuple("AB", 1, "AB")
    ));
