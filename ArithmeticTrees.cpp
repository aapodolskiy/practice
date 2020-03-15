#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <queue>
#include <cctype>

using namespace std;


static const char EMPTY = ' ';
static const char MINUS = '-';
static const char PLUS = '+';
static const char MULTIPLY = '*';
static const char DIVIDE = ':';
static const char DIVIDE_2 = '/';
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
        case DIVIDE_2:
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
        || c == DIVIDE_2
        || c == OPEN_BRACKET
        || c == CLOSE_BRACKET;
}

void print_data(data d, bool end_trailing_whitespace = true) {
    if (d.is_number) {
        cout << d.data;
    } else {
        cout << d.sign;
    }
    if (end_trailing_whitespace) {
        cout << " ";
    }
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

stack<data> postfixFromInfix(string infix) {
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
    
    // 2. создаем итоговый queue<data> result с постфиксной записью
    stack<data> result;
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


struct Elem {
    data d;
    Elem * left, * right;
};

typedef Elem * PElem;

class SearchTree {
private:
    PElem root;
    
    static void addElements(PElem &p, stack<data> &s) {
        if (p == NULL) {
            p = new Elem;
            p->d = s.top();
            p->left = NULL;
            p->right = NULL;
            s.pop();
            if (!p->d.is_number) {
                SearchTree::addElements(p->right, s);
                SearchTree::addElements(p->left, s);
            }
            return;
        }
    }
    
    static bool isLeaf(const PElem &p) {
        return p->left == NULL && p->right == NULL;
    }
    
    static int getHeight(const PElem &p) {
        if (p == NULL) {
            return 0;
        }
        
        return 1 + max(SearchTree::getHeight(p->left), SearchTree::getHeight(p->right));
    }

    static void fillTiers(const PElem &p, int shift, int height, data * array_of_tiers) {
        if (p == NULL) {
            return;
        }
        int p_position = shift + pow(2, height-1);
        array_of_tiers[p_position] = p->d;
        SearchTree::fillTiers(p->left, shift, height-1, array_of_tiers);
        SearchTree::fillTiers(p->right, p_position, height-1, array_of_tiers);
    }
    
    static void printPrefix(const PElem &p) {
        if (p == NULL || isDataEmpty(p->d)) {
            return;
        }
        print_data(p->d);
        SearchTree::printPrefix(p->left);
        SearchTree::printPrefix(p->right);
    }
    
    static void printInfix(const PElem &p) {
        if (p == NULL || isDataEmpty(p->d)) {
            return;
        }
        if (p->d.is_number) {
            print_data(p->d);
            return;
        }
        cout << "( ";
        SearchTree::printInfix(p->left);
        cout << ") ";
        
        print_data(p->d);
        
        cout << "( ";
        SearchTree::printInfix(p->right);
        cout << ") ";
    }
    
    static void printPostfix(const PElem &p) {
        if (p == NULL || isDataEmpty(p->d)) {
            return;
        }
        SearchTree::printPostfix(p->left);
        SearchTree::printPostfix(p->right);
        print_data(p->d);
    }
    
    static double calcResult(const PElem &p) {
        if (p->d.is_number){
            return p->d.data;
        }
        
        switch (p->d.sign) {
            case MINUS:
                return SearchTree::calcResult(p->left) - SearchTree::calcResult(p->right);
            case PLUS:
                return SearchTree::calcResult(p->left) + SearchTree::calcResult(p->right);
            case MULTIPLY:
                return SearchTree::calcResult(p->left) * SearchTree::calcResult(p->right);
            case DIVIDE:
            case DIVIDE_2:
                return SearchTree::calcResult(p->left) / (SearchTree::calcResult(p->right) + 0.0);
        }
        
        return 0;
    }

    static void freeMemory(PElem &p) {
        if (p == NULL) {
            return;
        }
        freeMemory(p->left);
        freeMemory(p->right);
        delete p;
    }
public:
    SearchTree() {
        root = NULL;
    }
    
    bool isEmpty() {
        return root == NULL;
    }
    
    SearchTree(stack<data> elements) {
        root = NULL;
        SearchTree::addElements(root, elements);
    }
    
    void printTiers() {
        int h = SearchTree::getHeight(root);
        if (h == 0) {
            cout << "tree is empty" << endl;
        }
        
        int total_length = pow(2, h);
        data tiers[total_length];
        for (int i = 0; i < total_length; i++) {
            refreshData(tiers[i]);
        }
        
        SearchTree::fillTiers(root, 0, h, tiers);
        
        const char free_space_character = ' ';

        for (int i = h; i > 0; i--) {
            int step = pow(2, i);
            int position = step / 2;
            while (position < total_length) {
                cout << string(min(position, step)-1, free_space_character);
                if (!isDataEmpty(tiers[position])) {
                    print_data(tiers[position], false);
                } else {
                    cout << free_space_character;
                }
                position += step;
            }
            cout << endl;
        }
    }
    
    void printPrefix() {
        SearchTree::printPrefix(root);
    }
    
    void printInfix() {
        SearchTree::printInfix(root);
    }
    
    void printPostfix() {
        SearchTree::printPostfix(root);
    }
    
    double calcResult() {
        return SearchTree::calcResult(root);
    }
    
    ~SearchTree() {
        SearchTree::freeMemory(root);
    }
};

int main() {
    cout << "enter formulae and press enter:" << endl;
    string input;
    getline(cin, input);
    
    stack<data> s = postfixFromInfix(input);
    SearchTree t(s);
    
    cout << endl << "Here is a tree of your formulae:" << endl;
    t.printTiers();
    cout << endl;
    
    cout << endl << "Here is a prefix (+34) representation:" << endl;
    t.printPrefix();
    cout << endl;
    
    cout << endl << "Here is a postfix (34+) representation:" << endl;
    t.printPostfix();
    cout << endl;
    
    cout << endl << "Here is a infix (3+4) representation:" << endl;
    t.printInfix();
    cout << endl;
    
    cout << endl << "And, finally, calculated result:" << endl;
    cout << t.calcResult();
    cout << endl;
    
    cout << endl << "Goodbye!" << endl;
    
    return 0;
}
