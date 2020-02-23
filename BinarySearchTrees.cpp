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
            } else {
                cout << "error 1582497703";
                return;
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
            } else {
                cout << "error 1582497728";
                return;
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
            } else {
                cout << "error 1582497756";
                return;
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
        } else {
            cout << "error 1582497773";
            return;
        }
        
        smallestOnTheRight->left = target->left;
        smallestOnTheRight->right = target->right;
        
        if (father == NULL) {
            root = smallestOnTheRight;
        } else if (father->left == target) {
            father->left = smallestOnTheRight;
        } else if (father->right == target) {
            father->right = smallestOnTheRight;
        } else {
            cout << "error 1582497779";
            return;
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
    
    static void fillTiers(const PElem &p, int current_position, int * array_of_tiers) {
        if (p == NULL) {
            return;
        }
        array_of_tiers[current_position] = p->data;
        SearchTree::fillTiers(p->left, 2*current_position, array_of_tiers);
        SearchTree::fillTiers(p->right, 2*current_position + 1, array_of_tiers);
    }
    
    static void fillTiersMoreBeautiful(const PElem &p, int shift, int height, int * array_of_tiers) {
        if (p == NULL) {
            return;
        }
        int p_position = shift + pow(2, height-1);
        array_of_tiers[p_position] = p->data;
        SearchTree::fillTiersMoreBeautiful(p->left, shift, height-1, array_of_tiers);
        SearchTree::fillTiersMoreBeautiful(p->right, p_position, height-1, array_of_tiers);
    }
    
    static void increasingPrint(const PElem &p) {
        if (p == NULL) {
            return;
        }
        increasingPrint(p->left);
        cout << p->data << " ";
        increasingPrint(p->right);
    }
    
    static void decreasingPrint(const PElem &p) {
        if (p == NULL) {
            return;
        }
        decreasingPrint(p->right);
        cout << p->data << " ";
        decreasingPrint(p->left);
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
    
    void printTiers() {
        int h = SearchTree::getHeight(root);
        if (h == 0) {
            cout << "tree is empty" << endl;
        }
        
        int total_length = pow(2, h);
        int tiers[total_length];
        int dummy_value = -1;
        for (int i = 0; i < total_length; i++) {
            tiers[i] = dummy_value;
        }
        
        SearchTree::fillTiers(root, 1, tiers);
        
        const char free_space_character = '-';

        for (int i = 0; i < h; i++) {
            int t = pow(2, i);
            for (int j = 0; j < t; j++) {
                if (tiers[t + j] == dummy_value) {
                    cout << free_space_character;
                } else {
                    cout << tiers[t + j];
                }
                cout << string(pow(2, h-i+1)-1, free_space_character);
            }
            cout << endl;
        }
    }
    
    void printTiersMoreBeautiful() {
        int h = SearchTree::getHeight(root);
        if (h == 0) {
            cout << "tree is empty" << endl;
        }
        
        int total_length = pow(2, h);
        int tiers[total_length];
        int dummy_value = -1;
        for (int i = 0; i < total_length; i++) {
            tiers[i] = dummy_value;
        }
        
        SearchTree::fillTiersMoreBeautiful(root, 0, h, tiers);
        
        const char free_space_character = ' ';

        for (int i = h; i > 0; i--) {
            int step = pow(2, i);
            int position = step / 2;
            while (position < total_length) {
                cout << string(min(position, step)-1, free_space_character);
                if (tiers[position] != dummy_value) {
                    cout << tiers[position];
                } else {
                    cout << free_space_character;
                }
                position += step;
            }
            cout << endl;
        }
    }
    
    static void printHelp() {
        cout << "List of commands:" << endl
             << "a <n> - to add positive integer <n> to SearchTree" << endl
             << "r <n> - to remove integer <n> from SearchTree" << endl
             << "p - to print SearchTree in visual form" << endl
             << "i - to print SearchTree in increasing order" << endl
             << "d - to print SearchTree in decreasing order" << endl
             << "u - to print SearchTree in ugly visual form" << endl
             << "h - to see this help message" << endl
             << "q - to quit" << endl
        ;
    }
    
    void increasingPrint() {
        SearchTree::increasingPrint(root);
        cout << endl;
    }
    
    void decreasingPrint() {
        SearchTree::decreasingPrint(root);
        cout << endl;
    }
    
    ~SearchTree() {
        SearchTree::freeMemory(root);
    }
};

int main() {
    int n = 0;
    cout << "Please, enter number n: ";
    cin >> n;
    
    cout << "Now enter n integers separated by whitespace: ";
    int values[n];
    for(int i = 0; i < n; i++) {
        cin >> values[i];
    }
    
    SearchTree searchTree(values, n);
    
    cout << "Cool! We've built SearchTree from your values:" << endl;
    searchTree.printTiersMoreBeautiful();
    
    cout << endl;
    SearchTree::printHelp();
    
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
            case 'p':
                searchTree.printTiersMoreBeautiful();
                break;
            case 'i':
                searchTree.increasingPrint();
                break;
            case 'd':
                searchTree.decreasingPrint();
                break;
            case 'u':
                searchTree.printTiers();
                break;
            case 'h':
                SearchTree::printHelp();
                break;
            default:
                cout << "Can't understand you. Type 'h' to see help message." << endl;
                break;
        }
    } while (stop == false);
    
    cout << "Goodbye!" << endl;
    
    return 0;
}
