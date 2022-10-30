#include "gtest/gtest.h"
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.length() <= 1)
        {
            return s.length();
        }

        int longest = 0;
        int start = 0;
        int end = 0;
        map<char, int> last_index_map;
        
        const char* char_array = s.c_str();

        while (end < s.length())
        {
            char current_char = s[end];

            if (last_index_map.count(current_char) && last_index_map[current_char] >= start)
            {
                start = last_index_map[current_char] + 1;
            }
            last_index_map[current_char] = end;

            longest = max(longest, end - start + 1);
            end++;
        }
        
        return longest;
    }
};






// Test fixture
class test_fixture_3 : public ::testing::TestWithParam<tuple<string, int>>
{
protected:
    Solution sut; // system under test (SUT) 待測物件
};


// Test Method
TEST_P(test_fixture_3, solve_test)
{
    // given 測資
    auto params = GetParam();
    string s = get<0>(params);
    int expected = get<1>(params);
    
    // when 執行 solution
    auto result = sut.lengthOfLongestSubstring(s);
    
    // then 驗證結果正確
    EXPECT_EQ(expected, result);
}


// Test Cases
INSTANTIATE_TEST_CASE_P(
    TestCases,
    test_fixture_3,
    ::testing::Values(
        make_tuple("abba", 2),
        make_tuple("abcdefg", 7),
        make_tuple("abcabcbb", 3),
        make_tuple("bbbbb", 1),
        make_tuple("aab", 2),
        make_tuple("pwwkew", 3)
    ));
