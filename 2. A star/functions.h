#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;


void printMaze(vector<vector<string>> maze)
{
    vector<string> temp(maze[0].size(), "-----");
    cout << endl;
    for (auto border : temp)
        cout << border << " ";
    cout << endl;
    for (auto row : maze)
    {
        cout << "| ";
        for (auto box : row)
            cout << box << " | ";
        cout << endl;
        for (auto border : temp)
            cout << border << " ";
        cout << endl;
    }
    cout << endl;
}

string intToString(int num, int len)
{
    int divisor = 1000;
    string temp;
    while (num != 0)
    {
        int digit = num % 10;
        num /= 10;
        temp.push_back(char(digit + '0'));
    }
    reverse(temp.begin(), temp.end());

    while (temp.size() < len)
    {
        temp.insert(temp.begin(), '0');
    }

    return temp;
}

int manhattanDistance(pair<int, int> source, pair<int, int> destination)
{
    int distance = abs(source.first - destination.first) + abs(source.second - destination.second);
    return distance;
}

void drawPath(vector<vector<string>> maze, map<pair<int, int>, pair<int, int>> mp, pair<int, int> source, pair<int, int> destination)
{
    pair<int, int> prev = destination;
    pair<int, int> curr = destination;
    while (curr != source)
    {

        curr = mp[{curr.first, curr.second}];
        if (prev == curr)
            maze[curr.first][curr.second] = " O ";
        else if (curr == source)
            maze[curr.first][curr.second] = " O ";
        else if (prev.first < curr.first)
            maze[curr.first][curr.second] = " \\/ ";
        else if (prev.first > curr.first)
            maze[curr.first][curr.second] = " ^ ";
        else if (prev.second < curr.second)
            maze[curr.first][curr.second] = " > ";
        else if (prev.second > curr.second)
            maze[curr.first][curr.second] = " < ";

        system("cls");
        printMaze(maze);
        cout << prev.first << " " << prev.second << endl;
        cout << curr.first << " " << curr.second << endl;
        sleep(1);
        prev = curr;
    }
    
}

// vector<vector<string>> maze =
//         {{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
//          {"   ", " X ", "   ", "   ", "   ", " X ", " X ", " X ", " X ", " X ", "   "},
//          {"   ", " X ", " X ", "   ", "   ", "   ", "   ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", " X ", " X ", " X ", " X ", " X ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", "   ", "   "},
//          {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", "   ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", "   ", "   ", "   ", " X ", "   ", "   ", " X ", "   "},
//          {"   ", "   ", " X ", " X ", "   ", " X ", " X ", "   ", " X ", " X ", "   "},
//          {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "}};

// pair<int, int> source = {3, 0};
// pair<int, int> destination = {6, 5};

