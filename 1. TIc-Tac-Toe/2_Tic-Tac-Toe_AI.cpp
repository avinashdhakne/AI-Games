#include <iostream>
#include "common_functions.h"
#include <map>
using namespace std;

int find_score_for_O(vector<int> X_player, vector<int> O_player)
{
    int score = 0;
    vector<vector<int>> win_indices = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {7, 8, 9}, {4, 5, 6}, {1, 2, 3}, {7, 5, 3}, {9, 5, 1}};
    for (auto touple : win_indices)
    {
        int subScore = 0;
        for (auto index : touple)
        {
            if (X_player[index] != 0)
            {
                subScore = 0;
                break;
            }
            else if (O_player[index] != 0)
                subScore = 1;
        }
        score += subScore;
    }
    return score;
}

int find_score_for_X(vector<int> X_player, vector<int> O_player)
{
    int score = 0;
    vector<vector<int>> win_indices = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {7, 8, 9}, {4, 5, 6}, {1, 2, 3}, {7, 5, 3}, {9, 5, 1}};
    for (auto touple : win_indices)
    {
        int subScore = 0;
        for (auto index : touple)
        {
            if (O_player[index] != 0)
            {
                subScore = 0;
                break;
            }
            else if (X_player[index] != 0)
                subScore = 1;
        }
        score += subScore;
    }
    return score;
}

int choose_optimal_step_O(vector<int> X_player, vector<int> O_player)
{
    map<int, int> score_table;

    for (auto position = 1; position <= 9; position++)
    {
        if (X_player[position] == 0 && O_player[position] == 0)
        {
            vector<int> dummy_x = X_player;
            vector<int> dummy_o = O_player;

            dummy_x[position] = 0;
            dummy_o[position] = 1;
            if (checkWinner(dummy_x, dummy_o))
            {
                return position;
            }
        }
    }

    for (auto position = 1; position <= 9; position++)
    {
        if (X_player[position] == 0 && O_player[position] == 0)
        {
            vector<int> dummy_x = X_player;
            vector<int> dummy_o = O_player;

            dummy_x[position] = 1;
            dummy_o[position] = 0;
            if (checkWinner(dummy_x, dummy_o))
            {
                return position;
            }
        }
    }

    for (auto position = 1; position <= 9; position++)
    {
        vector<int> temp_player = O_player;
        if (X_player[position] == 0 && O_player[position] == 0)
        {
            temp_player[position] = 1;
            int x_score = find_score_for_X(X_player, temp_player);
            int o_score = find_score_for_O(X_player, temp_player);
            int score = o_score - x_score;

            cout << "checked ->" << position << " | x -> " << x_score << " | o -> " << o_score << " | score -> " << score << endl;
            score_table[score] = position;
        }
    }

    auto result = score_table.rbegin();
    return (*result).second;
}

int main()
{
    cout << "Tic-Tac-Toe" << endl;
    cout << "For player 1 -> X" << endl;
    cout << "For player 2 -> O\n\n"
         << endl;

    while (true)
    {
        vector<int> X_player(10);
        vector<int> O_player(10);
        int player = 1;
        printGrid(X_player, O_player);
        bool winner = 0;

        for (int step = 1; step <= 9; step++)
        {
            if (player)
            {
                int position;
                cout << "Player 1 (X): Enter your position... ";
                cin >> position;
                while (position > 9 || position < 1 || X_player[position] != 0 || O_player[position] != 0)
                {
                    cout << "Invalid position" << endl;
                    cout << "Enter appropriate position" << endl;
                    cin >> position;
                }
                X_player[position] = 1;
            }
            else
            {
                cout << "Player 2 (O): Enter your position... ";
                int position = choose_optimal_step_O(X_player, O_player);
                cout << position << " -> computer position" << endl;
                O_player[position] = 1;
            }

            cout << "\n\nMatrix at " << step << "th Turn" << endl;

            printGrid(X_player, O_player);

            if (checkWinner(X_player, O_player) == 1)
            {
                cout << "Player 1 Won !!!" << endl;
                winner = 1;
                break;
            }
            else if (checkWinner(X_player, O_player) == 2)
            {
                cout << "Player 2 Won !!!" << endl;
                winner = 1;
                break;
            }
            player = !player;
        }
        if (!winner)
            cout << "Match is Draw...  :(" << endl;

        char decision= 'y';
        cout << "Want to play again!  or press 'n' to terminate" << endl;
        cin >> decision;

        if (decision == 'n' || decision == 'N')
            break;
        else
            cout << "\n\nStarting New Game..." << endl
                 << endl;
    }
}
