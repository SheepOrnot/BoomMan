#ifndef MCTS_HEADER_PETTER
#define MCTS_HEADER_PETTER
#endif

#pragma once
#include<QDebug>

namespace MCTS
{

struct ComputeOptions
{
    int number_of_threads;
    int max_iterations;
    double max_time;
    bool verbose;

    ComputeOptions() :
        number_of_threads(8),
        max_iterations(10000),
        max_time(-1.0),
        verbose(false)
    { }
};

template<typename State>
typename State::Move compute_move(
    const State root_state,
    const ComputeOptions options = ComputeOptions());
}

#include <future>				//多线程支持
#include <iomanip>				//输出规范
#include <memory>				//主要是unique_ptr
#include <thread>				//多线程支持
#include <random>				//更多随机数支持
#include <algorithm>
#include <cstdlib>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

namespace MCTS
{
    using std::cerr;			//错误流
    using std::endl;
    using std::vector;
    using std::size_t;

    static void check(bool expr, const char* message);
    static void assertion_failed(const char* expr, const char* file, int line);


    /*
    https://zh.cppreference.com/w/cpp/preprocessor/replace
    仿函数宏中，如果替换列表 中一个标识符前有 # 运算符，那么该标识符在运行形参替换的基础上以引号包围，实际上创建一个字符串字面量。
    另外，预处理器为内嵌的字符串字面量（如果存在）外围的引号添加反斜杠以进行转义，并按需要双写字符串中的反斜杠。
    移除所有前导和尾随空白符，并将文本中间（除内嵌字符串字面量中间外）的任何空白符序列缩减成单个空格。
    此操作被称为“字符串化”，如果字符串化的结果不是合法的字符串字面量，那么行为未定义。

    __FILE__展开成当前文件名，作为字符串字面量，可用 #line 指令更改(宏常量)
    __LINE__展开成源文件行号，整数常量，可用 #line 指令更改(宏常量)
    */
#define attest(expr) if(!(expr)) { ::MCTS::assertion_failed(#expr, __FILE__, __LINE__); }
#ifndef NDEBUG
#define dattest(expr) if (!(expr)) { ::MCTS::assertion_failed(#expr, __FILE__, __LINE__); }
#else
#define dattest(expr) ((void)0)
#endif

template<typename State>
class Node
{
public:
    typedef typename State::Move Move;

    Node(const State& state);
    ~Node();

    bool has_untried_moves() const;

    template<typename RandomEngine>
    Move get_untried_move(RandomEngine* engine) const;

    Node* best_child() const;

    bool has_children() const
    {
        return !children.empty();
    }

    Node* select_child_UCT() const;
    Node* add_child(const Move& move, const State& state);

    void update(double result);

    const Move move;
    Node* const parent;
    const int player_to_move;

    double wins;
    int visits;

    std::vector<Move> moves;
    std::vector<Node*> children;

private:
    Node(const State& state, const Move& move, Node* parent);

    Node(const Node&);
    Node& operator = (const Node&);

    double UCT_score;


};

template<typename State>
Node<State>::Node(const State& state) :
    move(State::no_move),
    parent(nullptr),
    player_to_move(state.player_to_move),
    wins(0),
    visits(0),
    moves(state.get_moves()),
    UCT_score(0)
{ }

template<typename State>
Node<State>::Node(const State& state, const Move& move_, Node* parent_) :
    move(move_),
    parent(parent_),
    player_to_move(state.player_to_move),
    wins(0),
    visits(0),
    moves(state.get_moves()),
    UCT_score(0)
{ }

template<typename State>
Node<State>::~Node()
{
    for (auto child : children)
    {
        delete child;
    }
}

template<typename State>
bool Node<State>::has_untried_moves() const
{
    return !moves.empty();
}

template<typename State>
template<typename RandomEngine>
typename State::Move Node<State>::get_untried_move(RandomEngine* engine) const
{
    attest(!moves.empty());
    std::uniform_int_distribution<std::size_t> moves_distribution(0, moves.size() - 1);
    return moves[moves_distribution(*engine)];
}

template<typename State>
Node<State>* Node<State>::best_child() const
{
    attest(moves.empty());
    attest(!children.empty());

    return *std::max_element(children.begin(), children.end(),
        [](Node* a, Node* b) { return a->visits < b->visits; });
}

template<typename State>
Node<State>* Node<State>::select_child_UCT() const
{
    attest(!children.empty());
    for (auto child : children)
    {
        child->UCT_score = double(child->wins) / double(child->visits)
            + std::sqrt(2.0 * std::log(double(this->visits)) / child->visits);
    }

    return *std::max_element(children.begin(), children.end(),
        [](Node* a, Node* b) { return a->UCT_score < b->UCT_score; });
}


//针对某个特定的Move操作进行拓展操作
template<typename State>
Node<State>* Node<State>::add_child(const Move& move, const State& state)
{
    auto node = new Node(state, move, this);
    children.push_back(node);
    attest(!children.empty());

    auto itr = moves.begin();
    for (; itr != moves.end() && *itr != move; ++itr);
    attest(itr != moves.end());

    //还能这么删除?
    std::iter_swap(itr, moves.end() - 1);
    moves.resize(moves.size() - 1);

    return node;
}

template<typename State>
void Node<State>::update(double result)
{
    visits++;
    wins += result;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

static void check(bool expr, const char* message)
{
    if (!expr)
    {
        throw std::invalid_argument(message);
    }
}

static void assertion_failed(const char* expr, const char* file_cstr, int line)
{
    using namespace std;

    string file(file_cstr);
    auto pos = file.find_last_not_of("/\\");
    if (pos == string::npos)
    {
        pos = 0;
    }

    file = file.substr(pos + 1);

    stringstream sout;
    sout << "Assertion failed: " << expr << " in " << file << ":" << line << ".";
    throw runtime_error(sout.str().c_str());
}


//以下算法核心

template<typename State>
std::unique_ptr<Node<State>> compute_tree(
    const State root_state,
    const ComputeOptions options,
    std::mt19937_64::result_type initial_seed)
{
    std::mt19937_64 random_engine(initial_seed);

    attest(options.max_iterations >= 0);

    attest(root_state.player_to_move == 0 || root_state.player_to_move == 1);
    auto root = std::unique_ptr<Node<State>>(new Node<State>(root_state));

    //抓住一个根，开始多次迭代
    //*
    State state;
    for (int iter = 1; iter <= options.max_iterations || options.max_iterations < 0; ++iter)
    {
        auto node = root.get();
        state = root_state;

        //这节点已经被完全拓展了
        while (!node->has_untried_moves() && node->has_children())
        {
            node = node->select_child_UCT();
            state.do_move(node->move);
        }

        //如果该节点未被完全拓展，则随机拓展一步
        if (node->has_untried_moves())
        {
            auto move = node->get_untried_move(&random_engine);
            state.do_move(move);
            node = node->add_child(move, state);
        }

        int max_step = 100, i = 0;
        while (state.has_moves() && i < max_step)
        {
            //随机策略网络模拟
            state.do_random_move(&random_engine);
            i++;
        }

        //找到终止状态，回溯更新，直到node != nullptr（更新到根节点）
        while (node != nullptr)
        {
            node->update(state.get_result(node->player_to_move));
            node = node->parent;
        }
    }

    return root;

}

template<typename State>
typename State::Move compute_move(
    const State root_state,
    const ComputeOptions options
)
{
    using namespace std;

    attest(root_state.player_to_move == 0 || root_state.player_to_move == 1);

    auto moves = root_state.get_moves();
    attest(moves.size() > 0);
    if (moves.size() == 1) { return moves[0]; }

    vector<future<unique_ptr<Node<State>>>> root_futures;
    ComputeOptions job_options = options;
    job_options.verbose = false;
    for (int t = 0; t < options.number_of_threads; ++t) {
        auto func = [t, &root_state, &job_options] () -> std::unique_ptr<Node<State>>
        {
            return compute_tree(root_state, job_options, 1012411 * t + 12515);
        };

        root_futures.push_back(std::async(std::launch::async, func));
    }


    //unique_ptr<Node<State>> root = compute_tree(root_state, options, 1012411 * 1 + 12511);

    vector<unique_ptr<Node<State>>> roots;
    for (int t = 0; t < options.number_of_threads; ++t) {
        roots.push_back(std::move(root_futures[t].get()));
    }

    map<typename State::Move, int> visits;
    map<typename State::Move, double> wins;
    long long games_played = 0;
    for (int t = 0; t < options.number_of_threads; ++t) {
        auto root = roots[t].get();
        games_played += root->visits;
        for (auto child = root->children.cbegin(); child != root->children.cend(); ++child) {
            visits[(*child)->move] += (*child)->visits;
            wins[(*child)->move]   += (*child)->wins;
        }
    }

    //long long games_played = root->visits;

    //cbegin : const
    /*
    for (auto child = root->children.cbegin(); child != root->children.cend(); ++child)
    {
        visits[(*child)->move] += (*child)->visits;
        wins[(*child)->move] += (*child)->wins;
    }
    */

    double best_score = -1;
    typename State::Move best_move = typename State::Move();
    for (auto itr : visits)
    {
        auto move = itr.first;
        double v = itr.second;
        double w = wins[move];

        double expected_success_rate = (w + 1) / (v + 2);
        if (expected_success_rate > best_score)
        {
            best_move = move;
            best_score = expected_success_rate;
        }

        if (options.verbose) {
            cerr << "Move: " << itr.first
                << " (" << setw(2) << right << int(100.0 * v / double(games_played) + 0.5) << "% visits)"
                << " (" << setw(2) << right << int(100.0 * w / v + 0.5) << "% wins)" << endl;
        }
    }

    if (options.verbose) {
        auto best_wins = wins[best_move];
        auto best_visits = visits[best_move];
        cerr << "----" << endl;
        cerr << "Best: " << best_move
            << " (" << 100.0 * best_visits / double(games_played) << "% visits)"
            << " (" << 100.0 * best_wins / best_visits << "% wins)" << endl;
    }
    std::cerr << "games_player:" << games_played << std::endl;

    return best_move;
}


}


