#include "gtest/gtest.h"
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* head = new ListNode();
        ListNode* current = head;

        int carry = 0;
        while (l1 != NULL || l2 != NULL)
        {
            int val1 = l1 == NULL ? 0 : l1->val;
            int val2 = l2 == NULL ? 0 : l2->val;
            int sum = val1 + val2 + carry;
            carry = sum / 10;

            current->next = new ListNode(sum % 10);
            current = current->next;

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        if (carry > 0)
        {
            current->next = new ListNode(carry);
        }

        return head->next;
    }
};



ListNode* array_to_list_node(vector<int> arr)
{
    ListNode* node = new ListNode();
    ListNode* head = node;
    
    for (int value : arr)
    {
        node->next = new ListNode(value);
        node = node->next;
    }
    return head->next;
}

vector<int> list_node_to_array(ListNode* list)
{
    vector<int> arr;
    while (list != NULL)
    {
        arr.push_back(list->val);
        list = list->next;
    }
    return arr;
}


// Test fixture
class test_fixture_2 : public ::testing::TestWithParam<tuple<vector<int>, vector<int>, vector<int>>>
{
protected:
    Solution sut; // system under test (SUT) 待測物件
};


// Test Method
TEST_P(test_fixture_2, solution_test)
{
    // given 測資
    auto params = GetParam();
    vector<int> arr1 = get<0>(params);
    vector<int> arr2 = get<1>(params);
    vector<int> expectedArr = get<2>(params);

    auto l1 = array_to_list_node(arr1);
    auto l2 = array_to_list_node(arr2);

    // when 執行 solution
    auto result = sut.addTwoNumbers(l1, l2);
    auto resultArr = list_node_to_array(result);

    // then 驗證結果正確
    EXPECT_EQ(expectedArr, resultArr);
}




// Test Cases
INSTANTIATE_TEST_CASE_P(
    TestCases,
    test_fixture_2,
    ::testing::Values(
        make_tuple(vector<int> {2, 4, 3}, vector<int> {5, 6, 4}, vector<int> {7, 0, 8}),
        make_tuple(vector<int> {0}, vector<int> {0}, vector<int> {0}),
        make_tuple(vector<int> {9,9,9,9,9,9,9}, vector<int> {9,9,9,9}, vector<int> {8,9,9,9,0,0,0,1})
    ));
