#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<int, vector<vector<int>>> win_table =
    {{1, {{1, 4, 7}, {1, 2, 3}, {1, 5, 9}}},
     {2, {{2, 5, 8}, {1, 2, 3}}},
     {3, {{1, 2, 3}, {3, 6, 9}, {3, 5, 7}}},
     {4, {{1, 4, 7}, {4, 5, 6}}},
     {5, {{4, 5, 6}, {8, 5, 2}, {1, 5, 9}, {3, 5, 7}}},
     {6, {{3, 6, 9}, {4, 5, 6}}},
     {7, {{1, 4, 7}, {7, 8, 9}, {7, 5, 3}}},
     {8, {{2, 5, 8}, {7, 8, 9}}},
     {9, {{3, 6, 9}, {7, 8, 9}, {1, 5, 9}}}};

void printGrid(vector<int> X_player, vector<int> O_player)
{
    string pos1 = (X_player[1] == 1) ? "X" : (O_player[1] == 1) ? "O"
                                                                : "1";
    string pos2 = (X_player[2] == 1) ? "X" : (O_player[2] == 1) ? "O"
                                                                : "2";
    string pos3 = (X_player[3] == 1) ? "X" : (O_player[3] == 1) ? "O"
                                                                : "3";
    string pos4 = (X_player[4] == 1) ? "X" : (O_player[4] == 1) ? "O"
                                                                : "4";
    string pos5 = (X_player[5] == 1) ? "X" : (O_player[5] == 1) ? "O"
                                                                : "5";
    string pos6 = (X_player[6] == 1) ? "X" : (O_player[6] == 1) ? "O"
                                                                : "6";
    string pos7 = (X_player[7] == 1) ? "X" : (O_player[7] == 1) ? "O"
                                                                : "7";
    string pos8 = (X_player[8] == 1) ? "X" : (O_player[8] == 1) ? "O"
                                                                : "8";
    string pos9 = (X_player[9] == 1) ? "X" : (O_player[9] == 1) ? "O"
                                                                : "9";

    cout << " " << pos1 << " | " << pos2 << " | " << pos3 << " " << endl;
    cout << "---|---|---" << endl;
    cout << " " << pos4 << " | " << pos5 << " | " << pos6 << " " << endl;
    cout << "---|---|---" << endl;
    cout << " " << pos7 << " | " << pos8 << " | " << pos9 << " " << endl;
}

int checkWinner(vector<int> X_player, vector<int> O_player)
{
    vector<vector<int>> win_indices = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {7, 8, 9}, {4, 5, 6}, {1, 2, 3}, {7, 5, 3}, {9, 5, 1}};
    for (auto index : win_indices)
    {
        if ((X_player[index[0]] + X_player[index[1]] + X_player[index[2]]) == 3)
            return 1;
        else if ((O_player[index[0]] + O_player[index[1]] + O_player[index[2]]) == 3)
            return 2;
    }
    return 0;
}
