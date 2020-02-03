#include <iostream>
#include <string>

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
public:
    SearchTree() {
        root = NULL;
    }
    SearchTree(PElem r) {
        root = r;
    }
    
    bool isEmpty() {
        return root == NULL;        
    }
    
    PElem addElement(int a) {
        if (this->isEmpty()) {
            root = new Elem;
            root->data = a;
            return root;
        } else {
            if (a == root->data) {
                return NULL;
            }
            


            
            if (a < root->data) {
                root->left = SearchTree(root->left).addElement(a);
                return root;
            } else {
                root->right = SearchTree(root->right).addElement(a);
                return root;
            }
        }
    }
    
    SearchTree(int a[], int length) {
        for(int i = 0; i < length; i++) {
            cout << endl << i << ": ";
            addElement(a[i]);
        }
    }
    
    void print() {
        if (this->isEmpty()) {
            return;
        }
        cout << root -> data << " ";
        SearchTree(root->left).print();
        SearchTree(root->right).print();
    }
    
    ~SearchTree() {
    }
};

int main() {
    cout << "aa";
    int t[6] = {1, 2, 3, 4, 5};
    SearchTree a(t, 4);
    cout << endl << "print: " << endl;
    a.print();
    return 0;
}
