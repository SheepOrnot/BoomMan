#include<QVector>
#include<QQueue>
#include<QMap>
#include<QString>
#include<iostream>
#include<qalgorithms.h>
#include"people.h"
#include"boom.h"
#include"setting.h"

enum Action_Type { DoNothing = 0, Walk_R, Walk_U, Walk_L, Walk_D, SetBoom };
enum Target_Type { Point = 1, Item, Wall_D, Wall_ND, Boom, SafeArea };
enum AIWalk_Type { Stay = 0, Right, Up, Left, Down };
enum ActionA_Type{ DWall = 1, Attack, GetItem };

static int dx[5] = { 0, 1,  0, -1, 0 };
static int dy[5] = { 0, 0, -1,  0, 1 };

typedef struct Node
{
    int t, x, y;
    AIWalk_Type type;
    Node* parent;
}Node;

class AITarget
{
public:
    AITarget(int x = 0, int y = 0, Target_Type type = Point) : x(x), y(y), type(type) {}

    Target_Type type;
    int x, y;
};

class AIAction
{
public:
    AIAction(int x = 0, int y = 0, Action_Type type = DoNothing) : x(x), y(y), type(type) {}

    Action_Type type;
    int x, y;
};

class AIPlayer : public people
{
public:
    AIPlayer(int TYPE, int XX, int YY, QString NAME = "Unnamed", QWidget* parent = NULL);
    QVector<AIAction> Search(const QPoint& src, const AITarget& dst);
    bool TestSafe();

    bool isNeedUpdate;
    int actionIndex;
    int danger[17][17];

    static ActionA_Type actionA[6];
    int actionAIndex;

    QVector<AIAction> moves;

    void update(const AITarget& dst);
};

int ComputeMove(AIPlayer& ai);
bool CheckAccess(const int x, const int y);
bool CheckTarget(const int x, const int y, const AITarget& target, const AIPlayer& player);

extern AIPlayer* AI;
