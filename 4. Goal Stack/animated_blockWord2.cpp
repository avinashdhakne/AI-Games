#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

// define block limit
const int BLOCK_LIMIT = 10;
const int SLEEP_TIME = 1;
int maxHeight = 0;
int maxWidth = 0;
char var;

pair<int, int> armContain = {-1, -1};

// define vectors for initial and final state
vector<vector<int>> initialState(BLOCK_LIMIT, {-1});
vector<vector<int>> goalState(BLOCK_LIMIT, {-1});

vector<vector<int>> currVector;
vector<vector<int>> goalVector;

void pickup(int block);
void putdown(int source, int destination);
void clear(int block);

// assign childs to respective parents
void puton(int child, int parent, vector<vector<int>> &state)
{
    if (parent == 0)
        state[parent].push_back(child);
    else
        state[parent][0] = child;
}

// check weather the stack contains block or not
bool isContain(vector<int> vect, int num)
{
    for (auto i : vect)
    {
        if (i == num)
            return true;
    }
    return false;
}

// convert the state vector into stacks
vector<vector<int>> construct(vector<vector<int>> state)
{
    vector<vector<int>> result;
    for (int i = 1; i < state[0].size(); i++)
    {
        vector<int> temp_st;
        int curr = state[0][i];
        while (curr != -1)
        {
            temp_st.push_back(curr);
            curr = state[curr][0];
        }
        result.push_back(temp_st);
    }
    return result;
}

// print stack in vertical order
void printStack(vector<vector<int>> stacks)
{
    if (maxWidth < stacks.size())
        maxWidth = stacks.size();

    for (int i = 0; i < currVector.size() || i <= maxWidth; i++)
    {
        if (armContain.second == i)
            cout << " ----- ";
        else
            cout << "         ";
    }
    cout << endl;

    for (int i = 0; i < currVector.size() || i <= maxWidth; i++)
    {
        if (armContain.second == i)
            cout << "-| " << armContain.first << " |-";
        else
            cout << "---------";
    }
    cout << endl;

    for (int i = 0; i < currVector.size() || i <= maxWidth; i++)
    {
        if (armContain.second == i)
            cout << " ----- ";
        else
            cout << "         ";
    }
    cout << endl;

    for (auto stack : stacks)
    {
        if (maxHeight < stack.size())
            maxHeight = stack.size();
    }

    for (int i = maxHeight - 1; i >= 0; i--)
    {
        for (auto stack : stacks)
        {
            if (i < stack.size())
                cout << "  -----  ";
            else
                cout << "         ";
        }
        cout << endl;
        for (auto stack : stacks)
        {
            if (i < stack.size())
                cout << "  | " << stack[i] << " |  ";
            else
                cout << "         ";
        }
        cout << endl;
    }

    for (int i = 0; i < currVector.size() || i <= maxWidth; i++)
        cout << "---------";
    cout << endl;
}

// check weather the upper block is on lower or floor or not
bool on(int upper, int lower, vector<vector<int>> state)
{
    for (auto st : state)
    {
        if (lower == 0)
        {
            if (st[0] == upper)
            {
                cout << "\t[IS ON] " << upper << " " << lower << endl;
                return true;
            }
        }

        for (int i = 0; i < st.size() - 1; i++)
        {
            if (st[i] == lower && st[i + 1] == upper)
            {
                cout << "\t[IS ON] " << upper << " " << lower << endl;
                return true;
            }
        }
    }
    cout << "\t[NOT ON] " << upper << " " << lower << endl;
    return false;
}

// check arm is empty or not
bool armEmpty()
{
    if (armContain.first == -1)
    {
        cout << "\t[ARM IS EMPTY]" << endl;
        return true;
    }
    cout << "\t[ARM IS NOT EMPTY]" << endl;
    return false;
}

// check weather the block is ready to pick or not
bool clean(int block, vector<vector<int>> state)
{

    if (block == 0)
    {
        cout << "\t[BLOCK [" << block << "] IS CLEAR: ON FLOOR]" << endl;
        return true;
    }
    else
    {
        for (auto st : state)
        {
            if (st.size() == 0)
                continue;
            else if (st.back() == block)
            {
                cout << "\t[BLOCK [" << block << "] IS CLEAR]" << endl;
                return true;
            }
        }
    }
    cout << "\t[BLOCK [" << block << "] IS NOT CLEAR]" << endl;
    return false;
}

// check weather the arm is holding
bool holding(int block)
{
    if (block == armContain.first)
    {
        cout << "\t[HOLDING BLOCK] [" << block << "] " << endl;
        return true;
    }
    cout << "\t[NOT HOLDING ANY BLOCK] " << endl;
    return false;
}

// pick the block in arm
void pickup(int block)
{
    printStack(currVector);
    cout << "Let's Proceed: ";
    cin >> var;
    system("cls");

    if (!clean(block, currVector))
        clear(block);

    if (!armEmpty())
        putdown(armContain.first, 0);

    armContain.first = block;
    for (int i = 0; i < currVector.size(); i++)
    {
        if (currVector[i].size() == 0)
            continue;
        else if (currVector[i].back() == block)
        {
            armContain.second = i;
            currVector[i].pop_back();

            cout << "[ACTION]: [PICKED UP BLOCK] " << block << endl;

            printStack(currVector);
            cout << "Let's Proceed: ";
            cin >> var;
            system("cls");

            if (currVector[i].size() == 0)
            {
                auto iter = find(currVector.begin(), currVector.end(), currVector[i]);
                currVector.erase(iter);
            }
        }
    }
}

// put down the block from source to destination
void putdown(int source, int destination)
{
    if (!clean(destination, currVector))
        clear(destination);
    if (!holding(source))
        pickup(source);

    if (!armEmpty())
    {
        if (destination == 0)
        {
            armContain.second = currVector.size();
            printStack(currVector);
            // sleep(SLEEP_TIME);
            cout << "Let's Proceed: ";
            cin >> var;
            // cin>>var;
            system("cls");

            currVector.push_back({armContain.first});
        }
        else
        {
            for (int i = 0; i < currVector.size(); i++)
            {

                if (currVector[i].size() == 0)
                    continue;
                else if (currVector[i].back() == destination)
                {
                    armContain.second = i;
                    printStack(currVector);
                    // sleep(SLEEP_TIME);
                    cout << "Let's Proceed: ";
                    cin >> var;
                    // cin>>var;
                    system("cls");

                    currVector[i].push_back(armContain.first);
                }
            }
        }

        armContain.first = -1;
        armContain.second = -1;
    }
    cout << "[ACTION]: [PUTDOWN DOWN BLOCK] " << source << " [ON] " << destination << endl;

    printStack(currVector);
    cout << "Let's Proceed: ";
    cin >> var;
    cout << "\033[2J\033[H";
}

void unstack(int upper, int lower)
{
    cout << "[START]: [UNSTACKING] " << upper << " [FROM] " << lower << endl;
    if (!clean(upper, currVector))
        clear(lower);
    if (!armEmpty())
        putdown(armContain.first, 0);
    if (on(upper, lower, currVector))
    {
        pickup(upper);
        cout << "[END]: [UNSTACKED] " << upper << " [FROM] " << lower << endl;
    }
    else
        cout << "[ACTION FAILED]: [UNABLE TO UNSTACK]" << endl;
}

void doStack(int upper, int lower)
{
    cout << "[START]: [STACKING] " << upper << " [ON] " << lower << endl;
    if (!clean(lower, currVector))
        clear(lower);
    if (!holding(upper))
    {
        pickup(upper);
    }
    putdown(upper, lower);
    cout << "[END]: [STACKED] " << upper << " [ON] " << lower << endl;
}

// clear the block
void clear(int block)
{
    cout << "[START]: [BLOCK [" << block << "] IS CLEARING]" << endl;
    if (!clean(block, currVector))
    {
        for (auto &st : currVector)
        {
            if (isContain(st, block))
            {
                while (!clean(block, currVector))
                {
                    int upper = st[st.size() - 1];
                    int lower = st[st.size() - 2];
                    unstack(upper, lower);
                }
            }
        }
    }
    cout << "[END]: [BLOCK [" << block << "] IS CLEARED]" << endl;
}

void solve()
{
    for (auto st : goalVector)
    {
        for (int i = 0; i < st.size() - 1; i++)
        {

            if (i == 0)
            {
                // cout << st[i] << " [CHECK] " << 0 << endl;
                if (!on(st[i], 0, currVector))
                    doStack(st[i], 0);
            }
            // cout << st[i + 1] << " [CHECK] " << st[i] << endl;
            if (!on(st[i + 1], st[i], currVector))
                doStack(st[i + 1], st[i]);
        }
    }
}

int main()
{
    // define initial state
    puton(1, 6, initialState);
    puton(2, 1, initialState);
    puton(3, 7, initialState);
    puton(4, 0, initialState);
    puton(5, 4, initialState);
    puton(6, 0, initialState);
    puton(7, 0, initialState);

    // define final state
    puton(3, 1, goalState);
    puton(1, 0, goalState);
    puton(4, 7, goalState);
    puton(2, 4, goalState);
    puton(5, 3, goalState);
    puton(6, 5, goalState);
    puton(7, 0, goalState);

    currVector = construct(initialState);
    goalVector = construct(goalState);

    cout << "\n\nInitial State: " << endl;
    printStack(currVector);

    cout << "\n\nGoal State: " << endl;
    printStack(goalVector);

    cout << "\n\n";

    cout << "Let's Proceed: ";
    cin >> var;
    system("cls");
    solve();

    cout << "\n\nFinal State: " << endl;
    printStack(currVector);

    cout << "\n\nGoal State: " << endl;
    printStack(goalVector);

    return 0;
}