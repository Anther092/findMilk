#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

void milkGenerator(vector<vector<int>>& lab, int r, int c);


struct Point
{
    int x;
    int y;
    Point(){}
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

void printLab(vector<vector<int>> &lab, int r, int c) {
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << lab[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> createMat(int r, int c) {

    vector<vector<int>> lab;

    for (int i = 0; i < r; i++)
    {
        vector<int> temp(c, 1);
        lab.push_back(temp);
    }

    for (int i = 0; i < r; i++)
    {
        if ((i % 2) != 0) {

            for (int j = 0; j < c; j++)
            {
                if ((j % 2) != 0) {

                    lab[i][j] = 0;
                }
            }
        }
    }

    return lab;
}

bool IsInside(int x, int y, int r, int c) {
    if (x < 0) return false;
    if (x >= c) return false;
    if (y < 0) return false;
    if (y >= r) return false;
    return true;
}

vector<vector<int>> findNeighbors(int nowX, int nowY, int r, int c, vector<vector<int>> lab) {
    vector<vector<int>> neighbors;

    int x = nowX;
    int y = nowY;

    Point doubleU(x + 0, y - 2);
    Point doubleR(x + 2, y + 0);
    Point doubleD(x + 0, y + 2);
    Point doubleL(x - 2, y + 0);
    vector<Point> coor = { doubleU, doubleR, doubleD, doubleL };

    for (int i = 0; i < 4; i++)
    {
        if (IsInside(coor[i].x, coor[i].y, r, c)) {

            if (lab[coor[i].y][coor[i].x] == 0) neighbors.push_back({ coor[i].x, coor[i].y });
        }
    }

    return neighbors;
}

void breakWall(int oldX, int oldY, vector<vector<int>> &path, vector<vector<int>> &labirinth, vector<vector<int>> &neighbors, int &allUnvisited) {

    vector<int> temp = neighbors[rand() % neighbors.size()];

    int newX = temp[0];
    int newY = temp[1];
    vector<int> vec = { (newX - oldX) / 2, (newY - oldY) / 2 };

    labirinth[newY][newX] = 3;
    labirinth[oldY][oldX] = 2;
    labirinth[oldY + vec[1]][oldX + vec[0]] = 2;
    path.push_back({ oldX + vec[0], oldY + vec[1] });
    path.push_back(temp);
    allUnvisited--;

    neighbors.clear();
}

void makeMaze(vector<vector<int>>& labirinth, int r, int c) {
    int allUnvisited = ((r - 1) / 2) * ((c - 1) / 2) - 1;

    labirinth[1][1] = 3;
    vector<vector<int>> path = { {1, 1} };
    vector<vector<int>> neighbors;

    int nowX;
    int nowY;
    while (allUnvisited > 0)
    {
        nowX = path[path.size() - 1][0];
        nowY = path[path.size() - 1][1];
        neighbors = findNeighbors(nowX, nowY, r, c, labirinth);

        if ((neighbors.size() == 0) & allUnvisited > 0) {

            for (int i = 2; i <= path.size(); i++)
            {
                nowX = path[path.size() - i][0];
                nowY = path[path.size() - i][1];
                neighbors = findNeighbors(nowX, nowY, r, c, labirinth);

                if (neighbors.size() > 0) {

                    breakWall(nowX, nowY, path, labirinth, neighbors, allUnvisited);
                }
            }
        }
        else {
            breakWall(nowX, nowY, path, labirinth, neighbors, allUnvisited);
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (labirinth[i][j] == 3) labirinth[i][j] = 2;
        }
    }
    labirinth[1][0] = 0;
    labirinth[r - 2][c - 1] = 3;

    milkGenerator(labirinth, r, c);
}

void whereIcanGo(vector<vector<int>>& lab, int r, int c, int x, int y) {

    Point U(x + 0, y - 1);
    Point R(x + 1, y + 0);
    Point D(x + 0, y + 1);
    Point L(x - 1, y + 0);
    vector<Point> coor = { U, R, D, L };
    vector<string> myWhere = { "up", "right", "down", "left" };

    for (int i = 0; i < 4; i++)
    {
        if (IsInside(coor[i].x, coor[i].y, r, c)) {
            if (lab[coor[i].y][coor[i].x] != 1) {
                cout << "you can go to " << myWhere[i] << endl;

            }
        }
    }


}

struct Hero
{
    // possible add Point
    int x = 0;
    int y = 1;

    int countOfmilk = 0;
};

enum thingsInLab
{
    hero,
    wall,
    space,
    exitOutOfLab,
    milk
};

void youFindSomething(Point me, vector<vector<int>>& lab) {

    if (lab[me.y][me.x] == thingsInLab::milk){
        cout << "you find milk \n";
    }
}

void milkGenerator(vector<vector<int>>& lab, int r, int c) {
    int allCells = ((r - 1) / 2) * ((c - 1) / 2) - 1;
    int allMilk = allCells / 10;
    if (allMilk == 0) allMilk++;

    while (allMilk > 0) {
        int x = rand() % c;
        int y = rand() % r;

        if (lab[y][x] == space) {
            lab[y][x] = milk;
            allMilk--;
        }
    }
}


int main() {
    srand(time(0));

    // r and c must be odd
    const int r = 5;
    const int c = 5;
    vector<vector<int>> labirinth = createMat(r, c);
    makeMaze(labirinth, r, c);
    //printLab(labirinth, r, c);
    int allCells = ((r - 1) / 2) * ((c - 1) / 2) - 1;
    int allMilk = allCells / 10;
    if (allMilk == 0) allMilk++;

    Hero me;

    char input = ' ';
    bool isOut = false;
    while (input != 'q')
    {
        whereIcanGo(labirinth, r, c, me.x, me.y);
        cin >> input;
        Point p(0, 0);
        if (input == 'u') {
            p.x = me.x;
            p.y = me.y - 1;
        }
        if (input == 'r') {
            p.x = me.x + 1;
            p.y = me.y;
        }
        if (input == 'd') {
            p.x = me.x;
            p.y = me.y + 1;
        }
        if (input == 'l') {
            p.x = me.x - 1;
            p.y = me.y;
        }

        if (labirinth[p.y][p.x] == exitOutOfLab) {
            if (me.countOfmilk == allMilk) {
                cout << "you find exit \n";
                break;
            }
            else {
                cout << "you find exit, but not all milk \n";
            }
        }
        if (labirinth[p.y][p.x] == thingsInLab::milk) {
            cout << "you find milk \n";
            me.countOfmilk++;
        }

        me.x = p.x;
        me.y = p.y;
    }


    return 0;
}