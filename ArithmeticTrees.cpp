#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Elem {
    int data;
    Elem * left, * right;
};

typedef Elem * PElem;

PElem Create(int x) {
    PElem b = new Elem;
    b->left = NULL;
    b->right = NULL;
    b->data = x;
    return b;
}

PElem Create() {
    return Create(0);
}

class SearchTree {
private:
    PElem root;
    static const int plus_sign = -2;
    static const int minus_sign = -3;
    static const int multiple_sign = -4;
    static const int division_sign = -5;
    
    static void addElement(PElem &p, int a) {
        if (p == NULL) {
            p = new Elem;
            p->data = a;
            p->left = NULL;
            p->right = NULL;
            return;
        }
        
        if (a < p->data) {
            SearchTree::addElement(p->left, a);
            return;
        }
        
        if (p->data < a) {
            SearchTree::addElement(p->right, a);
            return;
        }
    }
    
    static void findElement(int a, PElem &target, PElem &father) {
        if (target == NULL || target->data == a) {
            return;
        }
        
        father = target;
        
        if (a < target->data) {
            target = target->left;
            findElement(a, target, father);
        } else {
            target = target->right;
            findElement(a, target, father);
        }
    }
    
    static void removeElement(PElem &p, int a) {
        PElem &root = p;
        PElem target = p;
        PElem father = NULL;
        SearchTree::findElement(a, target, father);
        
        if (target == NULL) {
            return;
        }
        
        if (SearchTree::isLeaf(target)) {
            if (father == NULL) {
                root = NULL;
                return;
            } else if (father->left == target) {
                father->left = NULL;
            } else if (father->right == target) {
                father->right = NULL;
            }
            SearchTree::freeMemory(target);
            return;
        }
        
        if (target->left == NULL) {
            if (father == NULL) {
                root = target->right;
            } else if (father->left == target) {
                father->left = target->right;
            } else if (father->right == target) {
                father->right = target->right;
            }
            target->right = NULL;
            SearchTree::freeMemory(target);
            return;
        }
        
        if (target->right == NULL) {
            if (father == NULL) {
                root = target->left;
            } else if (father->left == target) {
                father->left = target->left;
            } else if (father->right == target) {
                father->right = target->left;
            }
            target->left = NULL;
            SearchTree::freeMemory(target);
            return;
        }
        
        PElem smallestOnTheRight = target->right;

        PElem fatherOfSmallestOnTheRight = target;

        while (smallestOnTheRight->left != NULL) {

            fatherOfSmallestOnTheRight = smallestOnTheRight;

            smallestOnTheRight = smallestOnTheRight->left;
        }
        
        if (fatherOfSmallestOnTheRight == NULL) {
            
            root->right = smallestOnTheRight->right;

        } else if (fatherOfSmallestOnTheRight->left == smallestOnTheRight) {
            
            fatherOfSmallestOnTheRight->left = smallestOnTheRight->right;

        } else if (fatherOfSmallestOnTheRight->right == smallestOnTheRight) {
            
            fatherOfSmallestOnTheRight->right = smallestOnTheRight->right;

        }
        
        smallestOnTheRight->left = target->left;
        smallestOnTheRight->right = target->right;
        
        if (father == NULL) {
            root = smallestOnTheRight;
        } else if (father->left == target) {
            father->left = smallestOnTheRight;
        } else if (father->right == target) {
            father->right = smallestOnTheRight;
        }
        
        target->left = NULL;
        target->right = NULL;
        SearchTree::freeMemory(target);
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

    static int calcResult(const PElem &p) {
        if (p == NULL){
            cout << "error";
            return 0;
        }
        if (p->data > 0){
            return p->data;
        }
        switch (p->data) {
            case SearchTree::minus_sign:
                return SearchTree::calcResult(p->left) - SearchTree::calcResult(p->right);
            case SearchTree::plus_sign:
                return SearchTree::calcResult(p->left) + SearchTree::calcResult(p->right);
            case SearchTree::multiple_sign:
                return SearchTree::calcResult(p->left) * SearchTree::calcResult(p->right);
            case SearchTree::division_sign:
                return SearchTree::calcResult(p->left) / SearchTree::calcResult(p->right);
        }
        cout << "error 2";
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
    
    SearchTree(int elements[], int length) {
        root = NULL;
        for (int i = 0; i < length; i++) {
            SearchTree::addElement(root, elements[i]);
        }
    }
    
    void appendElement(int n) {
        SearchTree::addElement(root, n);
    }
    
    void removeElement(int n) {
        SearchTree::removeElement(root, n);
    }

    int calcResult() {
        return SearchTree::calcResult(root);
    }
    
    ~SearchTree() {
        SearchTree::freeMemory(root);
    }
};

int main() {
    int n = 0;
    cout << "Please, enter number n: ";
    cin >> n;
    
    cout << "Now enter n positive integers separated by whitespace: ";
    int values[n];
    for(int i = 0; i < n; i++) {
        cin >> values[i];
    }
    
    SearchTree searchTree(values, n);
    
    
    char input = ' ';
    int a = 0;
    bool stop = false;
    do {
        cin >> input;
        switch (input) {
            case 'q':
                stop = true;
                break;
            case 'a':
                cin >> a;
                searchTree.appendElement(a);
                break;
            case 'r':
                cin >> a;
                searchTree.removeElement(a);
                break;
            case 'c':
                cout << searchTree.calcResult();
            default:
                cout << "Can't understand you." << endl;
                break;
        }
    } while (stop == false);
    
    cout << "Goodbye!" << endl;
    
    return 0;
}