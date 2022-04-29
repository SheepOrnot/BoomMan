#pragma once

#include"setting.h"
#include"people.h"
#include"mcts2.h"
#include<vector>
#include"gamewidget.h"
#include <cstdarg>
#include <cmath>
#include <QVector>
#include <sstream>

class AIState;

class AIBoom
{
public:
    AIBoom() { x = 0, y = 0, tnow = 0; }
    AIBoom(Boom& boom);
    int x, y;
    static int tmin, tmax;
    int tnow;
};

class AIPlayer
{
public:
    AIPlayer(people* P);
    AIPlayer(const AIPlayer& rhs);
    AIPlayer& operator = (const AIPlayer& rhs);
    void Walk(AIState &state, int type);

    int X, Y;
    int blood;
    enum Walk_Type{ Right = 1, Up, Left, Down };

};

class AIState
{
public:
    AIState();
    AIState(people* _AI, people* _P1, QVector<Boom*> _BoomV);
    AIState(const AIState& rhs);
    AIState& operator = (const AIState& rhs);
    ~AIState();

	typedef int Move;
	static const Move no_move = -1;

    bool Check(int type) const;
    void do_move(Move move);
	template<typename RandomEngine>
    void do_random_move(RandomEngine *engine);
	bool has_moves() const;
    std::vector<Move> get_moves() const;

    double get_result(int current_player_to_move);

    int player_to_move;
    int Target;
    int empty;
    int pepCnt;

    AIPlayer AI, P1;

	std::vector<std::vector<int>> mapdata_ai;
    QVector<AIBoom> BoomV;
    //std::unique_ptr<AIPlayer> player_markers[2];
    AIPlayer* player_markers[2];

    double D0, N, DTarget;
    static double C1, C2, C3, C4;



    /*

移动加权C1

放置加权C2

最近道具曼哈顿D0 = d * ri  （道具类型加权ri）

人物曼哈顿di

敌军/盟军人物加权C3 C4

最近可破坏物体曼哈顿D5

一次可破坏多少物体N
    */

private:
    double ManhattanDistance(QPoint a, QPoint b);
    double ManhattanDistance(QPoint ai);
    int DestoryAtOnce(QPoint BoomLocate);
};

AIState::Move ComputeMove(QVector<Boom*>& BoomV, people* AI, people* P1);

/*
class GameState
{
public:
	typedef int Move;
	static const Move no_move = ...

		void do_move(Move move);
	template<typename RandomEngine>
	void do_random_move(*engine);
	bool has_moves() const;
	std::vector<Move> get_moves() const;

	// Returns a value in {0, 0.5, 1}.
	// This should not be an evaluation function, because it will only be
	// called for finished games. Return 0.5 to indicate a draw.
	double get_result(int current_player_to_move) const;

	int player_to_move;

	// ...
private:
	// ...
};

*/
