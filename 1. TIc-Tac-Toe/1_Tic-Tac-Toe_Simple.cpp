#include <iostream>
#include <vector>
#include "common_functions.h"
#include <windows.h>

using namespace std;

int predict_position(vector<int> X_player, vector<int> O_player)
{
    vector<vector<int>> win_indices = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {7, 8, 9}, {4, 5, 6}, {1, 2, 3}, {7, 5, 3}, {9, 5, 1}};
    for (auto index : win_indices)
    {
        if ((O_player[index[0]] + O_player[index[1]] + O_player[index[2]]) == 2)
        {
            if (O_player[index[0]] == 0 && X_player[index[0]] == 0)
                return index[0];
            else if (O_player[index[1]] == 0 && X_player[index[1]] == 0)
                return index[1];
            else if (O_player[index[2]] == 0 && X_player[index[2]] == 0)
                return index[2];
        }

        else if ((X_player[index[0]] + X_player[index[1]] + X_player[index[2]]) == 2)
        {
            if (O_player[index[0]] == 0 && X_player[index[0]] == 0)
                return index[0];
            else if (O_player[index[1]] == 0 && X_player[index[1]] == 0)
                return index[1];
            else if (O_player[index[2]] == 0 && X_player[index[2]] == 0)
                return index[2];
        }
    }

    int position;
    do
    {
        position = rand() % 10;
    } while (position > 9 || position < 1 || X_player[position] != 0 || O_player[position] != 0);

    return position;
}

int main()
{
    cout << "\nTic-Tac-Toe" << endl;
    cout << "For player 1 -> X" << endl;
    cout << "For player 2 -> O\n"
         << endl;

    while (true)
    {
        cout << "1. play with other player" << endl;
        cout << "2. play with easy bot" << endl;
        cout << "3. play with medium bot" << endl;

        int choice;
        cout << "\nEnter your preferred number: ";
        cin >> choice;

        vector<int> X_player(10, 0);
        vector<int> O_player(10, 0);
        int player = 1;
        printGrid(X_player, O_player);
        bool winner = 0;
        char replay = 'y';

        switch (choice)
        {
        case 1:
            for (int steps = 1; steps <= 9; steps++)
            {
                if (player)
                {
                    int position;
                    cout << "Player 1: Enter your position... ";
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
                    int position;
                    cout << "Player 2: Enter your position... ";
                    cin >> position;
                    while (position > 9 || position < 1 || X_player[position] != 0 || O_player[position] != 0)
                    {
                        cout << "Invalid position" << endl;
                        cout << "Enter appropriate position -> ";
                        cin >> position;
                        cout << endl;
                    }
                    O_player[position] = 1;
                }

                cout << "\n\nMatrix at " << steps << "th Turn" << endl;
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
            break;
        case 2:

            for (int step = 1; step <= 10; step++)
            {
                if (player)
                {
                    int position;
                    cout << "Player 1: Enter your position... ";
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
                    cout << "\nWait for a computer... " << endl;
                    int position;

                    do
                    {
                        position = rand() % 10;
                    } while (position > 9 || position < 1 || X_player[position] != 0 || O_player[position] != 0);

                    O_player[position] = 1;
                }

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

            break;
        case 3:

            for (int step = 1; step <= 9; step++)
            {
                if (player)
                {
                    int position;
                    cout << "Player 1: Enter your position... ";
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
                    cout << "\nWait for a computer... " << endl;
                    int position = predict_position(X_player, O_player);
                    cout << "predicted position: " << position << "\n" <<endl;
                    O_player[position] = 1;
                }

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

            break;
        default:
            cout << "Invalid Choice" << endl;
        }

        if (!winner)
            cout << "Match is Draw...  :(" << endl;

        cout << "Want to play again!  or press 'n' to terminate" << endl;
        cin >> replay;

        if (replay == 'n' || replay == 'N')
            break;
        else
            cout << " \n\nStarting New Game..." << endl
                 << endl;
    }

    cout << "\n\nNice to see you :)\n\n";
    return 0;
}