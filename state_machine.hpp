#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <ranges>

constexpr std::string_view kCurlyOpen = "CURLY_OPEN";
constexpr std::string_view kCurlyClose = "CURLY_CLOSE";
constexpr std::string_view kSquareOpen = "SQUARE_OPEN";
constexpr std::string_view kSquareClose = "SQUARE_CLOSE";
constexpr std::string_view kNone = "NONE";
constexpr std::string_view kFailed = "FAILED";
using State = std::vector<std::string>;
using StateChecker = std::function<bool(const State& state)>;
using StateModifier = std::function<void(State& state)>;
struct Transition {
    StateChecker state_checker;
    StateModifier state_modifier;
};

struct RemoveLast{};
struct PushNew{};
struct Nothing{};

struct StateMachine {
    void clear();

    void parse_token(char token);

    bool parse(const std::string& expression);

    StateMachine( std::string_view start_state, std::string_view failed_state, std::string_view end_state);

    void AddTransition(char token, StateChecker state_checker, StateModifier state_modifier);

    void AddTransition(char token, StateChecker state_checker, Nothing);

    void AddTransition(char token, StateChecker state_checker, PushNew, std::string_view pushed_status);

    void AddTransition(char token, StateChecker state_checker, RemoveLast);

private:
    State state;
    StateChecker is_end;
    std::string start_state;
    std::string failed_state;
    std::string end_state;
    std::map<char, std::vector<Transition>> transitions_;
};

inline bool AlwaysTrue(const State& state) {
    return true;
}

bool IsOpenOnlyCurly(const State& state);

bool LastOpenedCurly(const State& state);

bool LastOpenedSquare(const State& state);

bool IsOpenedCurly(const State& state);

StateMachine create_default();
