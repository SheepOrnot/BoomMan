#include"AI.h"

AIPlayer* AI = NULL;
int AIPlayer::AISpeed = 100;
ActionA_Type AIPlayer::actionA[6] = { GetItem, DWall, GetItem, DWall, GetItem, DWall };

bool CheckTarget(const int x, const int y, const AITarget& target, const AIPlayer& player)
{
    if (target.type == Point) return x == target.x && y == target.y;
    else if (target.type == Wall_D) return Map[0][y][x] == 1;
    else if (target.type == Boom) return Map[0][y][x] == 2;
    else if (target.type == SafeArea) return Map[0][y][x] == 0 && player.danger[y][x] == 0;
    else if (target.type == Item) return (Map[0][y][x]==0)&&(Map[1][y][x]);

    return 0;
}

bool CheckAccess(const int x, const int y)
{
    if(x <= 0 || x >= 16 || y <= 0 || y >= 16) return 0;
    return Map[0][y][x] == 0;
}

bool AIPlayer::CANBOOM()
{
    if(GMode==0) return 0;
    if(blood<=0) return 0;
    if(Map[0][Y][X]>0) return 0;
    if(BoomTime.front().secsTo(QTime::currentTime())<8) return 0;
    return 1;
}
AIWalk_Type reserveWalk(AIWalk_Type type)
{
    if (type == Up) return Down;
    if (type == Right) return Left;
    if (type == Left) return Right;
    if (type == Down) return Up;
    return Stay;
}

inline bool operator < (const Node& a, const Node& b) {
    return a.type < b.type;
}

QVector<AIAction> AIPlayer::Search(const QPoint& src, const AITarget& dst)
{
    QQueue<Node> q;
    //QMap<Node, int> vis;
    QVector<AIAction> moves;

    int vis[17][17];
    memset(vis, 0, sizeof(vis));

    q.append({ 1, src.x(), src.y(), AIWalk_Type::Stay, NULL});
    vis[src.y()][src.x()] = 1;

    while (q.size())
    {
        Node p = q.front();
        q.pop_front();

        //std::cerr << "Node:(" << p.x <<"," << p.y <<")  " << p.type << "  Extending  Map:" << Map[0][p.x][p.y] << std::endl;

        for (int i = 1; i <= 4; i++)
        {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            if(nx <= 0 || nx >= 16 || ny <= 0 || ny >= 16) continue;

            Node n = { p.t + 1, nx, ny, AIWalk_Type(i), &p };

            //std::cerr << "----Node:(" << n.x <<"," << n.y <<")  " << n.type << "  Waitting  Map:" << Map[0][n.x][n.y] << std::endl;

            if (CheckTarget(nx, ny, dst, *this))
            {

                std::cerr << "Node:(" << n.x <<"," << n.y <<")  " << n.type << "  TargetType:"<< dst.type << "  Founded   Map:" << Map[0][n.y][n.x] << std::endl;

                if (dst.type == Wall_D)
                {
                    if(this->CANBOOM()) moves.push_back(AIAction(p.x, p.y, SetBoom));
                    else moves.push_back(AIAction(p.x, p.y, DoNothing));
                }
                else if(dst.type == SafeArea)
                {
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                }
                else if(dst.type == Item)
                {
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                    moves.push_back(AIAction(nx, ny, Action_Type(i)));
                }


                while (p.t != 1)
                {

                    moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                    moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                    moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                    moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                    moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                    std::cerr << "----Node:(" << p.x <<"," << p.y <<")  Walk_Type:" << p.type << "  MoveLoad  Map:" << Map[0][p.y][p.x] << std::endl << std::endl;

                    //p = { p.t - 1, p.x - dx[p.type], p.y - dy[p.type], p.type };

                    for (int i = 1; i <= 4; i++)
                    {
                        int nx = p.x + dx[i];
                        int ny = p.y + dy[i];

                        //std::cerr <<"----Test:(" << nx << "," << ny << ")  Vis:" << vis[ny][nx] << "  p.t:" << p.t << "  Map:" << Map[0][ny][nx] << std::endl;

                        if (vis[ny][nx] == p.t - 1)
                        {
                            p = { p.t - 1, p.x + dx[i], p.y + dy[i], p.type, NULL };
                            p.type = reserveWalk(AIWalk_Type(i));
                            std::cerr <<"----Node:(" << p.x << "," << p.y << ")  Vis:" << vis[p.y][p.x] << "  p.t:" << p.t << "   Confirmed  Map:" << Map[0][p.y][p.x] << std::endl;
                            break;
                        }

                    }
                }

                if(p.type != Stay) moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                if(p.type != Stay) moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                if(p.type != Stay) moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                if(p.type != Stay) moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                if(p.type != Stay) moves.push_back(AIAction(p.x, p.y, Action_Type(p.type)));
                if(moves.empty())
                {
                    moves.push_back(AIAction(p.x, p.y, DoNothing));
                    moves.push_back(AIAction(p.x, p.y, DoNothing));
                    moves.push_back(AIAction(p.x, p.y, DoNothing));
                    moves.push_back(AIAction(p.x, p.y, DoNothing));
                    moves.push_back(AIAction(p.x, p.y, DoNothing));
                }


                std::cerr << "*****Action*****" << this << std::endl;
                for(auto i : moves)
                {
                    std::cerr << i.type << " ";
                }
                std::cerr << std::endl << "****************" << std::endl;


                return moves;
            }

            if (!CheckAccess(nx, ny) || vis[ny][nx]) continue;
            if (dst.type == Wall_D && danger[ny][nx]) continue;

            //std::cerr << "----Node:(" << n.x <<"," << n.y <<")  " << n.type << "  Loading   Map:" << Map[0][n.x][n.y] << std::endl;

            q.append(n);
            vis[ny][nx] = vis[p.y][p.x] + 1;

        }

    }

    /*
    std::cerr << "*****Action*****" << std::endl;
    for(auto i : moves)
    {
        std::cerr << i.type << " ";
    }
    std::cerr << "****************" << std::endl;
    */

    if (moves.empty()) moves.push_back(0);
    return moves;
}

AIPlayer::AIPlayer(int TYPE, int XX, int YY, QString NAME, QWidget* parent) : people(TYPE, XX, YY, NAME, parent)
{
    isNeedUpdate = 1;
    actionIndex = 0;
    actionAIndex = 0;
    moves.clear();

    fa = parent;

    AITime = new QTimer;
    AITime->start(AISpeed);

    connect(AITime,&QTimer::timeout,[=](){
        if(AIComputing) return;
        AIComputing = 1;
        try{
            int move = ComputeMove(*this);

            qDebug() << "receiveMoveCtrl:" << move << "  " << this->name;
            if(move >= 1 && move <= 4)
                if(this->Check(move))
                {
                    this->Walk(move);
                    this->isWalk=0;
                }
<<<<<<< HEAD
            if(move == 5&& (this->CanBoom())) {BoomV.push_back(new BoomA(this->BoomLv, this->X, this->Y, fa)); this->raise();}
=======
            if(move == 5 && (this->CanBoom())) {
                BoomV.push_back(new BoomA(this->BoomLv, this->X, this->Y, fa)); this->raise();
                std::cerr<<"1212"<<std::endl;
            }
>>>>>>> 71f392f9cdcac32ad582150e6714b9e5bcf53022
        }catch(int e)
        {
            qDebug() << e << endl;
        }
        AIComputing = 0;
    });
}

void AIPlayer::update(const AITarget& dst)
{
    this->moves = Search({ this->X, this->Y }, dst);
    this->isNeedUpdate = 0;
    this->actionIndex = this->moves.size() - 1;
}

bool AIPlayer::TestSafe()
{
    memset(danger, 0, sizeof(danger));
    for (auto boom : BoomV)
    {
        int x = boom->X;
        int y = boom->Y;
        int r = boom->R;

        danger[y][x] = 1;

        for (int i = 1; i <= 4; i++)
        {
            int nx = x;
            int ny = y;
            for (int j = 1; j <= r; j++)
            {
                nx = nx + dx[i];
                ny = ny + dy[i];
                danger[ny][nx] = 1;
            }
        }
    }
    return !danger[this->Y][this->X];
}

int ComputeMove(AIPlayer& ai)
{
    if (!ai.TestSafe())
    {
        ai.isNeedUpdate = 1;
        ai.moves.clear();
        ai.actionIndex = 0;
        ai.update(AITarget(0, 0, SafeArea));
    }
    else if (ai.isNeedUpdate)
    {
        if(ai.actionA[ai.actionAIndex] == DWall) ai.update(AITarget(0, 0, Wall_D));
        else if(ai.actionA[ai.actionAIndex] == GetItem) ai.update(AITarget(0, 0, Item));
        ai.actionAIndex = (ai.actionAIndex + 1) % 6;
    }

    if (ai.actionIndex == -1)
    {
        ai.isNeedUpdate = 1;
        ai.moves.clear();
        ai.actionIndex = 0;
        return int(DoNothing);
    }

    //int move = ai.moves[ai.actionIndex].type;
    return ai.moves[ai.actionIndex --].type;

    //return int(Stay);
}
