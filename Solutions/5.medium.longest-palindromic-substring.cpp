#include "gtest/gtest.h"
using namespace std;

/**
 * Manacher's algorithm
 * @see https://blog.crimx.com/2017/07/06/manachers-algorithm/
 */
class Solution
{
public:
    vector<char> preProcessingString(string s)
    {
        vector<char> new_string {'^', '#'};
        for (char c : s)
        {
            new_string.push_back(c);
            new_string.push_back('#');
        }
        new_string.push_back('$');
        return new_string;
    }

    string longestPalindrome(string s) {

        if (s.length() <= 1)
        {
            return s;
        }

        // T：處理過的字串，如：babad => ^#b#a#b#a#d#$
        auto T = preProcessingString(s);
        int n = T.size();

        // P：紀錄以各節點為中心時的LPS長度 (Longest Palindrome String)
        int *P = new int[n];

        int C = 0; // 紀錄目前最右方迴文的中心索引
        int R = 0; // 紀錄目前最右方迴文的最右端點索引
        
        /**
         * ^#a#b#c#c#b#a#m#k$
         *     m  C  i  R
         */
        for (int i = 1; i < n - 1; i++)
        {
            P[i] = 0;

            // 根據 Manacher 理論，若i在以C為中心的迴文範圍中，預先取得 P[i] 最小值
            // 也就是以i為中心的迴文，至少會有多長
            if (i < R)
            {
                // mirror: i 相對C的鏡射位置索引
                int mirror = 2 * C - i; // C - (i - C)
                P[i] = min(R - i, P[mirror]);
            }

            // 記算以該節點為中心時的 LPS 長度
            while (T[i + P[i] + 1] == T[i - P[i] - 1])
            {
                P[i]++;
            }

            // 若此迴文範圍超過最右端點 => 將C改至此位置
            if (i + P[i] > R)
            {
                C = i;
                R = i + P[i];
            }
        }

        int maxLen = 0;
        int centerIndex = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (P[i] > maxLen)
            {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        return s.substr((centerIndex - 1) / 2 - (maxLen / 2), maxLen);
    }
};






// Test fixture
class test_fixture_5 : public ::testing::TestWithParam<tuple<string, string>>
{
protected:
    Solution sut; // system under test (SUT) 待測物件
};


// Test Method
TEST_P(test_fixture_5, solution_test)
{
    // given 測資
    auto params = GetParam();
    string s = get<0>(params);
    string expected = get<1>(params);
    
    // when 執行 solution
    auto result = sut.longestPalindrome(s);
    
    // then 驗證結果正確
    EXPECT_EQ(expected, result);
}


// Test Cases
INSTANTIATE_TEST_CASE_P(
    TestCases,
    test_fixture_5,
    ::testing::Values(
        make_tuple("babad", "bab"),
        make_tuple("cbbd", "bb")
    ));
