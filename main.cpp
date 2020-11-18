#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

class Thing {
private:

public:
    virtual void action(){};

    virtual string getIdStr() { return "Thing"; }
    virtual int getIdInt() { return -1; }
};

class Milk : public Thing {
private:

public:
    string getIdStr() override { return "Milk"; }
    int getIdInt() override { return 4; }

    void action() override
    {
        cout << "drink\n";
    }
};

class Space : public Thing {
private:

public:
    string getIdStr() override { return "Space"; }
    int getIdInt() override { return 0; }

    void action() override
    {

    }
};

class Wall : public Thing {
private:

public:
    string getIdStr() override { return "Wall"; }
    int getIdInt() override { return 1; }

    void action() override
    {

    }
};

class Enter : public Thing {
private:

public:
    string getIdStr() override { return "Enter"; }
    int getIdInt() override { return 2; }

    void action() override
    {

    }
};

class Exit : public Thing {
private:

public:
    string getIdStr() override { return "Exit"; }
    int getIdInt() override { return 3; }

    void action() override
    {

    }
};


class ServiceHere : public Thing {
public:
    string getIdStr() override { return "ServiceHere"; }
};

struct Point
{
    int x;
    int y;
    Point()= default;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

void printLab(vector<vector<Thing*>> &lab, int r, int c) {
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << lab[i][j]->getIdInt() << " ";
        }
        cout << endl;
    }
}

vector<vector<Thing*>> createTemplateMaze(int r, int c) {
    vector<vector<Thing*>> lab(r, vector<Thing*>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            auto* w = new Wall;
            lab[i][j] = w;
        }
    }

    for (int i = 0; i < r; i++)
    {
        if ((i % 2) != 0) {

            for (int j = 0; j < c; j++)
            {
                if ((j % 2) != 0) {
                    auto* s = new Space;
                    lab[i][j] = s;
                }
            }
        }
    }
    return lab;
}

bool IsInside(Point p, int r, int c) {
    if (p.x < 0) return false;
    if (p.x >= c) return false;
    if (p.y < 0) return false;
    if (p.y >= r) return false;
    return true;
}

vector<Point> findNeighbors(int nowX, int nowY, int r, int c, const vector<vector<Thing*>>& lab) {
    vector<Point> neighbors;

    int x = nowX;
    int y = nowY;

    Point doubleU(x + 0, y - 2);
    Point doubleR(x + 2, y + 0);
    Point doubleD(x + 0, y + 2);
    Point doubleL(x - 2, y + 0);
    vector<Point> coor = { doubleU, doubleR, doubleD, doubleL };

    for (int i = 0; i < 4; i++)
    {
        if (IsInside(coor[i], r, c)) {

            if (lab[coor[i].y][coor[i].x]->getIdStr() == "Space") neighbors.emplace_back( coor[i].x, coor[i].y );
        }
    }

    return neighbors;
}

void breakWall(int oldX, int oldY, vector<Point>& path, vector<vector<Thing*>> &labirinth, vector<Point> &neighbors, int &allUnvisited) {

    Point temp = neighbors[rand() % neighbors.size()];

    int newX = temp.x;
    int newY = temp.y;
    Point vec = { (newX - oldX) / 2, (newY - oldY) / 2 };

    auto* iHere = new ServiceHere;
    labirinth[newY][newX] = iHere;
    auto* s0 = new Space;
    labirinth[oldY][oldX] = s0;
    auto* s1 = new Space;
    labirinth[oldY + vec.y][oldX + vec.x] = s1;
    path.emplace_back( oldX + vec.x, oldY + vec.y );
    path.push_back(temp);
    allUnvisited--;

    neighbors.clear();
}


void makeMaze(vector<vector<Thing*>>& labirinth, int r, int c) {
    int allUnvisited = ((r - 1) / 2) * ((c - 1) / 2) - 1;

    auto* iHere = new ServiceHere;
    labirinth[1][1] = iHere;
    vector<Point> path = { {1, 1} };
    vector<Point> coorNeighbors;

    int nowX;
    int nowY;
    while (allUnvisited > 0)
    {
        nowX = path[path.size() - 1].x;
        nowY = path[path.size() - 1].y;
        coorNeighbors = findNeighbors(nowX, nowY, r, c, labirinth);

        if (coorNeighbors.empty() && (allUnvisited > 0)) {

            for (int i = 2; i <= path.size(); i++)
            {
                nowX = path[path.size() - i].x;
                nowY = path[path.size() - i].y;
                coorNeighbors = findNeighbors(nowX, nowY, r, c, labirinth);

                if (!coorNeighbors.empty()) {

                    breakWall(nowX, nowY, path, labirinth, coorNeighbors, allUnvisited);
                }
            }
        }
        else {
            breakWall(nowX, nowY, path, labirinth, coorNeighbors, allUnvisited);
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            Space s;
            if (labirinth[i][j]->getIdStr() == "serviceHere") labirinth[i][j] = &s;
        }
    }
    Enter en;
    labirinth[1][0] = &en;
    Exit ex;
    labirinth[r - 2][c - 1] = &ex;

    //milkGenerator(labirinth, r, c);
}



struct Hero
{
    // possible add Point


    int countOfmilk = 0;
};



int main() {
    srand(time(0));

    // r and c must be odd
    const int r = 3;
    const int c = 3;
    vector<vector<Thing*>> labirinth = createTemplateMaze(r, c);
    //makeMaze(labirinth, r, c);
    printLab(labirinth, r, c);

    return 0;
}