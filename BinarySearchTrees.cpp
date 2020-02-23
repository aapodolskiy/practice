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
            if (i != h-1) {
                cout << endl;
            }
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
        
            if (i != 1) {
                cout << endl;
            }
        }
    }
    
    void increasingPrint() {
        SearchTree::increasingPrint(root);
    }
    
    void decreasingPrint() {
        SearchTree::decreasingPrint(root);
    }
    
    ~SearchTree() {
        SearchTree::freeMemory(root);
    }
};

int main() {
    int t[10] = {3, 5, 1, 2, 4, 7, 8, 0, 11, 6};
    SearchTree a(t, 10);
    
    cout << endl << "print tiers: " << endl;
    a.printTiers();
    cout << endl;
    
    cout << endl << "print tiers more beautiful: " << endl;
    a.printTiersMoreBeautiful();
    cout << endl;
    
    cout << endl << "print in increasing order: " << endl;
    a.increasingPrint();
    cout << endl;
    
    cout << endl << "print in decreasing order: " << endl;
    a.decreasingPrint();
    cout << endl;
    
    return 0;
}
