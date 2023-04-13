#include <iostream>
#include <bits/stdc++.h>
#include "functions.h"
#include <unistd.h>

using namespace std;

vector<pair<int, int>> neighbour = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void displayConsole(vector<vector<string>> maze)
{
    sleep(1);
    system("cls");
    printMaze(maze);
}

int aStar(vector<vector<string>> maze, map<pair<int, int>, pair<int, int>> &mp, pair<int, int> source, pair<int, int> destination)
{
    priority_queue<pair<int, vector<pair<int, int>>>, vector<pair<int, vector<pair<int, int>>>>, greater<pair<int, vector<pair<int, int>>>>> q;
    vector<vector<int>> visited(maze.size(), vector<int>(maze[0].size()));

    pair<int, vector<pair<int, int>>> curr = {0, {source, {0, 0}}};
    q.push(curr);

    while (curr.second[0] != destination)
    {
        if (q.empty())
            return 0;

        curr = q.top();
        q.pop();
        visited[curr.second[0].first][curr.second[0].second] = 1;
        string score = intToString(curr.first, 3);
        maze[curr.second[0].first][curr.second[0].second] = score;
        displayConsole(maze);

        cout << q.size() << " "
             << " " << curr.second[0].first << " " << curr.second[0].second << endl;

        for (auto point : neighbour)
        {
            int row = curr.second[0].first + point.first;
            int col = curr.second[0].second + point.second;
            if (row >= 0 && row < maze.size() && col >= 0 && col < maze[0].size() && !visited[row][col] && maze[row][col] != " X ")
            {
                int f_H = manhattanDistance({row, col}, destination) + curr.second[1].first + 1;
                q.push({f_H, {{row, col}, {curr.second[1].first + 1, 0}}});
                mp[{row, col}] = {curr.second[0].first, curr.second[0].second};
            }
        }
    }
    return 1;
}


int main()
{
    vector<vector<string>> maze =
        {{"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "},
         {"   ", " X ", "   ", "   ", "   ", " X ", " X ", " X ", " X ", " X ", "   "},
         {"   ", " X ", " X ", "   ", "   ", "   ", "   ", "   ", "   ", " X ", "   "},
         {"   ", "   ", " X ", " X ", " X ", " X ", " X ", " X ", " X ", " X ", "   "},
         {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "}};

    map<pair<int, int>, pair<int, int>> mp;
    pair<int, int> source = {3, 0};
    pair<int, int> destination = {2, 5};

    maze[source.first][source.second] = " ^ ";
    maze[destination.first][destination.second] = " O ";

    if (!aStar(maze, mp, source, destination))
        cout << "\n Sorry, Unable to reach the destination \n\n";
    else
        drawPath(maze, mp, source, destination);

    return 0;
}