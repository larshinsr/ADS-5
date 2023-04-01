// Copyright 2021 NNTU-CS
#include <map>
#include <string>
#include "tstack.h"

int getPriority(char c) {
    if (c == ')') {
        return 1;
    } else if (c == '(') {
        return 0;
    } else if (c == '+' || c == '-') {
        return 2;
    } else if (c == '*' || c == '/') {
        return 3;
    } else if (c == ' ') {
        return -2;
    } else {
        return -1;
    }
}
int getPriority4Oper(char c) {
    if (c == '+' || c == '-') {
        return 0;
    }
    if (c == '*' || c == '/') {
        return 1;
    }
    return 0;
}
std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    int len = 0;
    std::string result;
    for (int i = 0; i < inf.size(); ++i) {
        if (-1 == getPriority(inf[i])) {
            result += inf[i];
            result += ' ';
        }
        if (getPriority(inf[i]) == 2 || getPriority(inf[i]) == 3) {
            while (!stack1.isEmpty() && getPriority(stack1.get()) != 0 &&
                   getPriority4Oper(inf[i]) <= getPriority4Oper(stack1.get())) {
                result += stack1.get();
                result += ' ';
                stack1.pop();
            }
            stack1.push(inf[i]);
        }
        if (getPriority(inf[i]) == 0) {
            stack1.push(inf[i]);
        }
        if (getPriority(inf[i]) == 1) {
            while (!stack1.isEmpty() && getPriority(stack1.get()) != 0) {
                result += stack1.get();
                result += ' ';
                stack1.pop();
            }
            if (!stack1.isEmpty() && getPriority(stack1.get()) == 0) {
                stack1.pop();
            }
        }
    }
    while (!stack1.isEmpty()) {
        result += stack1.get();
        result += ' ';
        stack1.pop();
    }
    result.pop_back();
    return result;
}
int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.size(); ++i) {
        if (getPriority(pref[i]) == -1) {
            stack2.push(pref[i] - '0');
        }
        if (getPriority(pref[i]) == 3 || getPriority(pref[i]) == 2) {
            int firstDigit = stack2.get();
            stack2.pop();
            int secondDigit = stack2.get();
            stack2.pop();
            if (pref[i] == '-') {
                stack2.push(secondDigit - firstDigit);
            }
            if (pref[i] == '+') {
                stack2.push(firstDigit + secondDigit);
            }
            if (pref[i] == '/') {
                stack2.push(secondDigit / firstDigit);
            }
            if (pref[i] == '*') {
                stack2.push(firstDigit * secondDigit);
            }
        }
    }
    return stack2.get();
}
