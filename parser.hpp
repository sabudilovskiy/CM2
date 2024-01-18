#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

class Parser {
public:
    using State = std::string;
    using SymbolCategory = std::function<bool(char)>;

private:
    std::map<State, std::vector<std::pair<SymbolCategory, State>>> transitions;
    State initialState;
    State currentState;
    State invalidState;
    State finalState;

public:
    Parser(const State& start, const State& invalid, const State& final) :
            initialState(start),
            currentState(start),
            invalidState(invalid),
            finalState(final) {}

    // Принимает начальное состояние, функцию категории символа и конечное состояние
    void addTransition(const State& from, SymbolCategory symbolCat, const State& to) {
        transitions[from].emplace_back(symbolCat, to);
    }

    // Проверяет, является ли входная строка валидной согласно заданным переходам
    bool parse(const std::string& input) {
        currentState = initialState; // Начинаем с начального состояния

        for (char ch : input) {
            bool transitionFound = false;

            // Поиск перехода для текущего символа
            for (const auto& trans : transitions[currentState]) {
                if (trans.first(ch)) {
                    currentState = trans.second;
                    transitionFound = true;
                    break;
                }
            }

            if (!transitionFound) {
                currentState = invalidState;
                break;
            }
        }

        return currentState == finalState;
    }
};

template <char ch>
auto matcher = [](char s){
    return s == ch;
};

auto create_default_parser(){
    Parser parser("EMPTY", "INVALID", "CURLY_CLOSE");
    parser.addTransition("EMPTY", matcher<'{'>, "CURLY_OPEN");

    parser.addTransition("CURLY_OPEN", matcher<'{'>, "CURLY_OPEN");
    parser.addTransition("CURLY_OPEN", matcher<'['>, "SQ_OPEN");
    parser.addTransition("CURLY_OPEN", matcher<'}'>, "CURLY_CLOSE");

    parser.addTransition("CURLY_CLOSE", matcher<']'>, "SQ_CLOSE");
    parser.addTransition("CURLY_CLOSE", matcher<'}'>, "CURLY_CLOSE");
    parser.addTransition("CURLY_CLOSE", matcher<'{'>, "CURLY_OPEN");

    parser.addTransition("SQ_OPEN", matcher<']'>, "SQ_CLOSE");
    parser.addTransition("SQ_OPEN", matcher<'{'>, "CURLY_OPEN");

    parser.addTransition("SQ_CLOSE", matcher<']'>, "SQ_CLOSE");
    parser.addTransition("SQ_CLOSE", matcher<'}'>, "CURLY_CLOSE");
    return parser;
}

