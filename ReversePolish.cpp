#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cctype>

using namespace std;

static const char EMPTY = ' ';
static const char MINUS = '-';
static const char PLUS = '+';
static const char MULTIPLY = '*';
static const char DIVIDE = ':';
static const char OPEN_BRACKET = '(';
static const char CLOSE_BRACKET = ')';

struct data {
    bool is_number;
    int data;
    char sign;
};

int operatorPriority(char c) {
    switch (c) {
        case MULTIPLY:
        case DIVIDE:
            return 1;
            break;
        case MINUS:
        case PLUS:
            return 2;
            break;
        default:
            return 999;
            break;
    }
}

bool isCharValidSign(char c) {
    return c == MINUS
        || c == PLUS
        || c == MULTIPLY
        || c == DIVIDE
        || c == OPEN_BRACKET
        || c == CLOSE_BRACKET;
}

void print_data(data d) {
    if (d.is_number) {
        cout << d.data;
    } else {
        cout << d.sign;
    }
    cout << " ";
}

bool isDataEmpty(const data &d) {
    return d.sign == EMPTY;
}

void refreshData(data &d) {
    d.is_number = false;
    d.data = 0;
    d.sign = EMPTY;
}

void fillData(char c, data &d) {
    if (isdigit(c)) {
        d.is_number = true;
        d.data = d.data * 10 + (c - '0');
        d.sign = c;
        return;
    }
    if (!isCharValidSign(c)) {
        return;
    }
    d.is_number = false;
    d.data = 0;
    d.sign = c;
}


queue<data> postfixFromInfix(string infix) {
    data d, o;
    
    // 1. преобразуем входные данные в queue<data> q
    //    это нужно, чтобы убрать лишние символы и чтобы получить многозначные числа
    queue<data> q;
    
    char t;
    refreshData(d);
    
    while (!infix.empty()) {
        t = infix[0];
        
        if (!isdigit(t)) {
            if (!isDataEmpty(d)) {
                q.push(d);
                refreshData(d);
            }
            fillData(t, d);
            if (!isDataEmpty(d)){
                q.push(d);
                refreshData(d);
            }
        } else {
            if (!d.is_number) {
                refreshData(d);
            }
            fillData(t, d);
        }
        
        infix.erase(0, 1);
    }
    
    if (!isDataEmpty(d)) {
        q.push(d);
    }
    
    
    queue<data> copy = q;
    while (!copy.empty()) {
        print_data(copy.front());
        copy.pop();
    }
    cout << endl;
    
    
    
    // 2. создаем итоговый queue<data> result с постфиксной записью
    queue<data> result;
    stack<data> operands;
    
    while (!q.empty()) {
        d = q.front();
        
        if (d.is_number) {
            result.push(d);
        } else if (d.sign == OPEN_BRACKET) {
            operands.push(d);
        } else if (d.sign == CLOSE_BRACKET) {
            while (!operands.empty()) {
                o = operands.top();
                if (o.sign == OPEN_BRACKET) {
                    operands.pop();
                    break;
                }
                result.push(o);
                operands.pop();
            }
        } else {
            while (!operands.empty()) {
                o = operands.top();
                if (operatorPriority(o.sign) >= operatorPriority(d.sign)) {
                    break;
                }
                result.push(o);
                operands.pop();
            }
            operands.push(d);
        }
        
        q.pop();
    }
    
    while (!operands.empty()) {
        o = operands.top();
        result.push(o);
        operands.pop();
    }
    
    return result;
}

int main() {
    string input;
    getline(cin, input);
    
    queue<data> r = postfixFromInfix(input);
    
    while (!r.empty()) {
        print_data(r.front());
        r.pop();
    }
    
    return 0;
}
