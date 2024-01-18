#include "state_machine.hpp"

void StateMachine::clear() {
    state.clear();
    state.push_back(start_state);
}

void StateMachine::parse_token(char token) {
    if (!transitions_.contains(token)) {
        state.emplace_back(failed_state);
        return;
    }
    auto& transitions = transitions_[token];
    bool founded_tr = false;
    for (auto& tr : transitions) {
        if (tr.state_checker(state)) {
            tr.state_modifier(state);
            founded_tr = true;
            break;
        }
    }
    if (!founded_tr) {
        state.emplace_back(failed_state);
    }
}

bool StateMachine::parse(const std::string& expression) {
    auto it = expression.begin();
    auto end = expression.end();
    while (it != end && state.back() != failed_state) {
        parse_token(*it);
        ++it;
    }
    bool result = state.back() == end_state;
    clear();
    return result;
}

StateMachine::StateMachine(std::string_view start_state, std::string_view failed_state,
    std::string_view end_state): start_state(start_state),
                                 failed_state(failed_state),
                                 end_state(end_state) {
    state.emplace_back(start_state);
}

void StateMachine::AddTransition(char token, StateChecker state_checker, StateModifier state_modifier) {
    transitions_[token].emplace_back(std::move(state_checker), std::move(state_modifier));
}

void StateMachine::AddTransition(char token, StateChecker state_checker, Nothing) {
    transitions_[token].emplace_back(std::move(state_checker), [](auto&){});
}

void StateMachine::AddTransition(char token, StateChecker state_checker, PushNew,
    std::string_view pushed_status) {
    auto transition = [pushed_status = std::string(pushed_status)](State& state) {
        state.push_back(pushed_status);
    };
    transitions_[token].emplace_back(std::move(state_checker), std::move(transition));
}

void StateMachine::AddTransition(char token, StateChecker state_checker, RemoveLast) {
    auto transition = [](State& state) {
        state.pop_back();
    };
    transitions_[token].emplace_back(std::move(state_checker), std::move(transition));
}

bool IsOpenOnlyCurly(const State& state) {
    bool opened_curly = false;
    for (std::string_view s : state) {
        if (s == kCurlyOpen) {
            opened_curly = true;
        }
        else if (s == kSquareOpen) {
            return false;
        }
    }
    return opened_curly;
}

bool LastOpenedCurly(const State& state) {
    for (auto it = state.rbegin(), end = state.rend(); it != end; ++it) {
        if (*it == kCurlyOpen) {
            return true;
        }
        if (*it == kSquareOpen) {
            return false;
        }
    }
    return false;
}

bool LastOpenedSquare(const State& state) {
    for (auto& s : std::ranges::reverse_view(state)) {
        if (s == kSquareOpen) {
            return true;
        }
        if (s == kCurlyOpen) {
            return false;
        }
    }
    return false;
}

bool IsOpenedCurly(const State& state) {
    return std::find(state.rbegin(), state.rend(), kCurlyOpen) != state.rend();
}

StateMachine create_default() {
    StateMachine sm(kNone, kFailed, kNone);
    sm.AddTransition('{', AlwaysTrue, PushNew{}, kCurlyOpen);
    sm.AddTransition('}', LastOpenedCurly, RemoveLast{});
    sm.AddTransition('[', IsOpenedCurly, PushNew{}, kSquareOpen);
    sm.AddTransition(']', LastOpenedSquare, RemoveLast{});
    sm.AddTransition(' ', AlwaysTrue, Nothing{});
    return sm;
}
