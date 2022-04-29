#include "AI.h"

double AIState::C1 = 3.0, AIState::C2 = 1.0, AIState::C3 = 1.0, AIState::C4 = 1.0;
int AIBoom::tmin = 0, AIBoom::tmax = 8;

AIState::AIState() : AI(NULL), P1(NULL)
{
    player_markers[0] = NULL;
    player_markers[1] = NULL;
    BoomV.clear();
}

AIState::AIState(people* _AI, people* _P1, QVector<Boom*> _BoomV) : AI(_AI), P1(_P1)
{
    player_markers[0] = NULL;
    player_markers[1] = NULL;
    BoomV.clear();
    //if(!AI || !P1) {empty = 1; return;}
    //else empty = 0;

    player_to_move = 0;
    Target = 1;
    pepCnt = 2;

    //player_markers[0] = std::unique_ptr<AIPlayer>(new AIPlayer(AI));
    //player_markers[1] = std::unique_ptr<AIPlayer>(new AIPlayer(P1));

    player_markers[0] = &AI;
    player_markers[1] = &P1;


    for (int i = 0; i < 16; i++)
    {
        std::vector<int> v;
        for (int j = 0; j < 16; j++)
        {
            v.push_back(Map[0][i][j]);
        }
        mapdata_ai.push_back(v);
    }

    for(int i = 0; i < _BoomV.size(); i ++ )
    {
        BoomV.push_back(AIBoom(*_BoomV[i]));
    }
}

AIState::AIState(const AIState& rhs) :
    player_to_move(rhs.player_to_move),
    Target(rhs.Target),
    empty(rhs.empty),
    pepCnt(rhs.pepCnt),
    AI(rhs.AI),
    P1(rhs.P1),
    mapdata_ai(rhs.mapdata_ai),
    BoomV(rhs.BoomV)
{
    player_markers[0] = &AI;
    player_markers[1] = &P1;
}

AIState& AIState::operator = (const AIState& rhs)
{
    player_to_move = rhs.player_to_move;
    Target = rhs.Target;
    empty = rhs.empty;
    pepCnt = rhs.pepCnt;
    AI = rhs.AI;
    P1 = rhs.P1;
    mapdata_ai = rhs.mapdata_ai;
    BoomV = rhs.BoomV;
    player_markers[0] = &AI;
    player_markers[1] = &P1;
    return *this;
}

AIState::~AIState()
{

}

bool AIState::Check(int TYPE) const
{
    int X = player_markers[player_to_move]->X;
    int Y = player_markers[player_to_move]->Y;
    if((TYPE==1&& X>=15)||(TYPE==2&& Y<=1)||(TYPE==3&& X<=1)||(TYPE==4&& Y>=15)) return 0;//判边界
    if(TYPE==1&&mapdata_ai[Y][X+1]>0) return 0;
    if(TYPE==2&&mapdata_ai[Y-1][X]>0) return 0;
    if(TYPE==3&&mapdata_ai[Y][X-1]>0) return 0;
    if(TYPE==4&&mapdata_ai[Y+1][X]>0) return 0;
    return 1;
}

void AIState::do_move(Move move)
{
    if(move >= 1 && move <= 4) this->player_markers[player_to_move]->Walk(*this, move);

    player_to_move = (player_to_move + 1) % pepCnt;
}

template<typename RandomEngine>
void AIState::do_random_move(RandomEngine* engine)
{
    std::uniform_int_distribution<Move> moves(1, 4);

	auto move = moves(*engine);
	//合法？合法就执行此move
    while(!this->Check(move)) move = moves(*engine);
    do_move(move);

}

bool AIState::has_moves() const
{
	//死了？  return false;
	//还活着，敌人也没死  return true;


    if(AI.blood > 0) return true;

    //实在没法运行
    return false;
}

std::vector<AIState::Move> AIState::get_moves() const
{
    //走路合法判断
    std::vector<AIState::Move> moves;
    for(int i = 1; i <= 4; i ++ )
        if(this->Check(i))
            moves.push_back(i);
	//炸弹放置判断
	//合法放进   moves.push_back(op);
	//return moves;

    return moves;
}

double AIState::ManhattanDistance(QPoint a, QPoint b)
{
    return abs(a.x() - b.x()) + abs(a.y() - b.y());
}

double AIState::get_result(int current_player_to_move)
{
    //寄了返回-100
    //对于这个人物，执行评估函数h(x);  return h(x);

    QPoint ai = { player_markers[0]->X, player_markers[0]->Y };
    QPoint p = { player_markers[1]->X, player_markers[1]->Y };

    //N = DestoryAtOnce();
    DTarget = ManhattanDistance(ai, p);
    D0 = 0;
    if(BoomV.size() != 0)
        for(int i = 0; i < BoomV.size(); i ++ )
        {
            int dist = ManhattanDistance(ai, {BoomV[i].x, BoomV[i].y});
            D0 += -10 * -dist;
        }

    N = 0;

    //double hx = 1;
    //double hx = C1 * (10.0 * exp(-D0) + 15.0 * exp(-DTarget) * C3) + C2 * (15.0 * exp(-D0) * C3 + 20.0 * exp(-D0) * N);

    double hx = 20 / (1 + DTarget) + D0;
    //std::cerr << hx << std::endl;
    //MIN/MAX策略
    //if(current_player_to_move != 0) hx = -hx;
    return hx;
}

AIPlayer::AIPlayer(people* P)
{
    if(!P) return;
    blood = P->blood;
    X = P->X;
    Y = P->Y;
}

AIPlayer::AIPlayer(const AIPlayer& rhs)
{
    X = rhs.X;
    Y = rhs.Y;
    blood = rhs.blood;
}

AIPlayer& AIPlayer::operator = (const AIPlayer& rhs)
{
    X = rhs.X;
    Y = rhs.Y;
    blood = rhs.blood;
    return *this;
}

void AIPlayer::Walk(AIState& state, int type)
{
    if(!state.Check(type)) return;

    if (type == Right) ++state.player_markers[state.player_to_move]->X;
    if (type == Up)    --state.player_markers[state.player_to_move]->Y;
    if (type == Left)  --state.player_markers[state.player_to_move]->X;
    if (type == Down)  ++state.player_markers[state.player_to_move]->Y;

    return;
}

AIBoom::AIBoom(Boom& boom)
{
    x = boom.X;
    y = boom.Y;
    tnow = tmax;
}

AIState::Move ComputeMove(QVector<Boom*>& BoomV, people* AI, people* P1)
{
    std::cerr << "AI:(" << AI->X << "," << AI->Y << ")" << std::endl;
    std::cerr << "P1:(" << P1->X << "," << P1->Y << ")" << std::endl;
    AIState state(AI, P1, BoomV);
    MCTS::ComputeOptions player1_options;
    player1_options.max_iterations = 1000;
    player1_options.number_of_threads = 32;
    player1_options.verbose = true;

    auto move = MCTS::compute_move(state, player1_options);

    return move;
}

