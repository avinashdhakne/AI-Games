#include <iostream>
#include <bits/stdc++.h>
#include "selectThree.cpp"
using namespace std;

bool isFound = false;
void printVector(unordered_map<char, int> vect)
{
    for (auto i : vect)
        cout << i.first << " " << i.second << " | ";
    cout << ""
         << endl;
}

// To check whether all the characters assigned values or not
bool allAssigned(unordered_map<char, int> result)
{
    for (auto chars : result)
    {
        if (chars.second == -1)
            return false;
    }
    return true;
}

// convert the string into integer
int cryptToArithmetic(string str, unordered_map<char, int> result)
{
    int output = 0;
    for (auto chars : str)
        output = (output * 10) + result[chars];
    return output;
}

// validate the equation with the help of map
bool isValid(string str1, string str2, string ans, unordered_map<char, int> result, vector<char> nonZeroChars)
{
    for (auto chars : nonZeroChars)
    {
        if (result[chars] == 0)
            return false;
    }

    int a = cryptToArithmetic(str1, result);
    int b = cryptToArithmetic(str2, result);
    int c = cryptToArithmetic(ans, result);
    if (a + b == c)
        return true;
    return false;
}

int combinations = 0;

void solveIt(string str1, string str2, string ans, unordered_map<char, int> &result, unordered_map<char, int>::iterator iter, vector<int> &v, vector<char> nonZeroChars, bool isConstrain)
{
    if (allAssigned(result))
    {
        combinations++;
        if (isValid(str1, str2, ans, result, nonZeroChars))
        {
            printVector(result);
            isFound = true;
        }
        return;
    }

    if ((isConstrain && (*iter).first == ans[0]))
    {
        auto temp = iter;
        temp = ++temp;
        solveIt(str1, str2, ans, result, temp, v, nonZeroChars, isConstrain);
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (!v[i])
            {
                (*iter).second = i;
                v[i] = 1;
                auto temp = iter;
                temp = ++temp;
                solveIt(str1, str2, ans, result, temp, v, nonZeroChars, isConstrain);
                v[i] = 0;
                (*iter).second = -1;
            }
        }
    }
}

void solve(string str1, string str2, string ans)
{
    unordered_map<char, int> result;
    vector<int> v(10);

    // add char to map
    for (int chars : str1)
        result[chars] = -1;
    for (int chars : str2)
        result[chars] = -1;
    for (int chars : ans)
        result[chars] = -1;

    int isConstrain = false;
    int maxLen = max({str1.size(), str2.size(), ans.size()});
    if (ans.size() == maxLen && str1.size() < maxLen && str2.size() < maxLen)
    {
        isConstrain = true;
        result[ans[0]] = 1;
        v[1] = 1;
    }

    vector<char> noZeroChars = {str1[0], str2[0], ans[0]};
    combinations = 0;
    solveIt(str1, str2, ans, result, result.begin(), v, noZeroChars, isConstrain);
    if (!isFound)
        cout << "Solution Not found" << endl;

    int output = 1;
    for (int i = 0; i < result.size(); i++)
    {
        output *= (10 - i);
    }
    cout << output << endl;

    cout << combinations << endl;

    return;
}

int main()
{
    // solve("INDIA", "CHINA", "ASIAN");
    // solve("TWO", "TWO", "FOUR");
    // solve("USA", "USSR", "PEACE");
    // solve("THREE", "FOUR", "SEVEN");
    // solve("CROSS", "ROADS", "DANGER");

    // vector<string> names = {"CHAD", "FIJI", "CUBA", "OMAN", "IRAN", "IRAQ"};
    // vector<string> names = {"INDIA", "JAPAN", "ISRAEL", "CHINA", "EGYPT", "ITALY", "FRANCE"};
    // vector<string> names = {"MUMBAI", "NAGPUR", "BHARAT", "AKSHAY", "KUSHAL"};


    // vector<string> temp;
    // vector<vector<string>> result;
    // vector<int> v(names.size());
    // selectThree(names, temp, result, v);

    // for (auto i : result)
    // {
    //     cout << i[0] << " + " << i[1] << " = " << i[2] << endl;
    //     solve(i[0], i[1], i[2]);
    //     cout << "----------------------------------------------"<<endl;
    // }
    solve("AC", "DA", "AAA");
    // cout<<result.size();

    return 0;
}