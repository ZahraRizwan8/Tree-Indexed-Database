#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

class Info {
public:
    int id;
    int year;
    string cause113;
    string cause_name;
    string state;
    string death;
    string death_rate;

    Info() {
        id = 0;
        year = 0;
    }

    Info(int id, int yr, string cause113, string cause, string st, string d, string rate) {
        id = id;
        year = yr;
        cause113 = cause113;
        cause_name = cause;
        state = st;
        death = d;
        death_rate = rate;
    }
};

struct node {
    Info key;
    node* left;
    node* right;
    node* parent;
};

struct RBNode {
    Info data;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    int color;
};

//for red black trees

class Node {
public:
    Info* keys;
    int temp;
    Node** child;
    int num;
    bool leaf;

    Node() {
        //default constructor
    }

    Node(int temp, bool bool_leaf);

    void insert(int k);						//for b trees
    void splitChild(int x, Node* y);
    void traverse();

    Node* searchKey(int k);
};

class AVL {
public:
    node* root;
    AVL() {
        root = NULL;
    }
    int getHeight(node*);
    int difference(node*);
    node* insert(node*, Info);
    void display(node*, int);
    void InOrderTraversal(node*);
    void PreOrderTraversal(node*);
    void PostOrderTraversal(node*);
    node* rr(node*);
    node* ll(node*);
    node* lr(node*);
    node* rl(node*);
    node* balance(node*);
    int maximum(int, int);
    void CurrentLevelOrder(node*);
    void LevelOrder(node*, int);

};

node* AVL::insert(node* r, Info d) {
    if (r == NULL) {
        r = new node;
        r->key.id = d.id;
        r->left = NULL;
        r->right = NULL;
        return r;
    }
    else if (d.id < r->key.id) {
        r->left = insert(r->left, d);
        r = balance(r);
    }
    else if (d.id >= r->key.id) {
        r->right = insert(r->right, d);
        r = balance(r);
    } return r;
}

int AVL::getHeight(node* h) {
    int temp = 0;
    if (h != NULL) {
        int leftHeight = getHeight(h->left);
        int rightHeight = getHeight(h->right);
        int maxHeight = maximum(leftHeight, rightHeight);
        temp = maxHeight + 1;

    }
    return temp;
}

int AVL::maximum(int num1, int num2)
{
    if (num1 > num2)
        return num1;
    else
        return num2;
}
int AVL::difference(node* h) {
    int leftHeight = getHeight(h->left);
    int rightHeight = getHeight(h->right);
    int bFactor = leftHeight - rightHeight;
    return bFactor;
}
node* AVL::rr(node* r) {
    node* p;
    p = r->right;
    r->right = p->left;
    p->left = r;
    //cout << "Right-Right Rotation" << " ";
    return p;
}
node* AVL::ll(node* r) {
    node* p;
    p = r->left;
    r->left = p->right;
    p->right = r;
    //cout << "Left-Left Rotation" << " ";
    return p;
}
node* AVL::lr(node* r) {
    node* p;
    p = r->left;
    r->left = rr(p);
    //cout << "Left-Right Rotation" << " ";
    return ll(r);
}
node* AVL::rl(node* r) {
    node* p;
    p = r->right;
    r->right = ll(p);
    //cout << "Right-Left Rotation" << " ";
    return rr(r);
}
node* AVL::balance(node* b) {
    int b_fact = difference(b);
    if (b_fact > 1) {
        if (difference(b->left) > 0)
            b = ll(b);
        else
            b = lr(b);
    }
    else if (b_fact < -1) {
        if (difference(b->right) > 0)
            b = rl(b);
        else
            b = rr(b);
    }
    return b;
}

void AVL::display(node* p, int l) {
    int i;
    if (p != NULL) {
        display(p->right, l + 1);
        cout << " ";
        if (p == root)
            cout << "Root -> ";
        for (i = 0; i < l && p != root; i++)
            cout << " ";
        cout << p->key.id;
        display(p->left, l + 1);
    }
}
void AVL::InOrderTraversal(node* root) {
    if (root == NULL) {
        return;
    }
    else {
        InOrderTraversal(root->left);
        cout << root->key.id << " ";
        InOrderTraversal(root->right);
    }
}
void AVL::PreOrderTraversal(node* root) {
    if (root == NULL) {
        return;
    }
    else {
        cout << root->key.id << " ";
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

void AVL::PostOrderTraversal(node* root) {
    if (root == NULL) {
        return;
    }
    else {
        PostOrderTraversal(root->left);
        PostOrderTraversal(root->right);
        cout << root->key.id << " ";
    }
}


void AVL::CurrentLevelOrder(node* root) {
    int h = getHeight(root);
    for (int i = 0; i < h; i++) {

        LevelOrder(root, i);
    }
    cout << "\n";
}


void AVL::LevelOrder(node* root, int level) {
    if (!root)
        return;
    if (level == 0) {
        cout << root->key.id << ' ';
    }
    else {
        LevelOrder(root->left, level - 1);
        LevelOrder(root->right, level - 1);
    }

}

class BTree {
public:
    Node* root;
    int temp;

    BTree(int t) {
        root = NULL;
        temp = t;
    }

    void traverse() {
        if (root != NULL) {
            root->traverse();
        }
    }

    Node* searchKey(int k) {
        return (root == NULL) ? NULL : root->searchKey(k);
    }
    void insertion(Info k);
};

Node::Node(int t, bool l) {
    temp = t;
    leaf = l;

    keys = new Info[2 * t - 1];
    child = new Node * [2 * t];

    num = 0;
}

void Node::traverse() {
    int i;
    for (i = 0; i < num; i++) {
        if (leaf == false)
            child[i]->traverse();
        cout << " " << keys[i].id;
    }

    if (leaf == false)
        child[i]->traverse();
}

Node* Node::searchKey(int k) {
    int i = 0;
    while (i < num && k > keys[i].id)
        i++;

    if (keys[i].id == k)
        return this;

    if (leaf == true)
        return NULL;

    return child[i]->searchKey(k);
}

void BTree::insertion(Info k) {
    if (root == NULL) {
        root = new Node(temp, true);
        root->keys[0] = k;
        root->num = 1;
    }
    else {
        if (root->num == 2 * temp - 1) {
            Node* s = new Node(temp, false);

            s->child[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].id < k.id)
                i++;
            s->child[i]->insert(k.id);

            root = s;
        }
        else
            root->insert(k.id);
    }
}

void Node::insert(int k) {
    int i = num - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i].id > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1].id = k;
        num += 1;
    }
    else {
        while (i >= 0 && keys[i].id > k)
            i--;

        if (child[i + 1]->num == 2 * temp - 1) {
            splitChild(i + 1, child[i + 1]);

            if (keys[i + 1].id < k)
                i++;
        }
        child[i + 1]->insert(k);
    }
}

void Node::splitChild(int i, Node* y) {
    Node* d = new Node(y->temp, y->leaf);
    d->num = temp - 1;

    for (int j = 0; j < temp - 1; j++)
        d->keys[j] = y->keys[j + temp];

    if (y->leaf == false) {
        for (int j = 0; j < temp; j++)
            d->child[j] = y->child[j + temp];
    }

    y->num = temp - 1;
    for (int j = num; j >= i + 1; j--)
        child[j + 1] = child[j];

    child[i + 1] = d;

    for (int j = num - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[temp - 1];
    num += 1;
}

class RedBlackTree {
public:

    RBNode* root;
    RBNode* temp;

    RedBlackTree();
    void red_black(RBNode* p, RBNode* q);
    void blackInsert(RBNode* bl);
    void  print(RBNode* root, string str, bool v);
    void  insert(Info d);
    void  balanced(RBNode* b);
    void  deletetion(RBNode* p, int d);
    RBNode* minimum(RBNode* m);
    RBNode* getRoot();
    void rr(RBNode* r);
    void ll(RBNode* r);
};

RedBlackTree::RedBlackTree() {
    temp = new RBNode;
    temp->color = 0;
    temp->left = NULL;
    temp->right = NULL;
    root = temp;
}

void  RedBlackTree::red_black(RBNode* p, RBNode* q) {
    if (p->parent == NULL) {
        root = q;
    }
    else if (p == p->parent->right) {
        p->parent->right = q;
    }
    else {
        p->parent->left = q;
    }
    q->parent = p->parent;
}

void  RedBlackTree::balanced(RBNode* b) {
    RBNode* p;

    while (b != root && b->color == 0) {
        if (b == b->parent->left) {
            p = b->parent->right;
            if (p->color == 1) {
                p->color = 0;
                b->parent->color = 1;
                ll(b->parent);
                p = b->parent->right;
            }
            else if (p->left->color == 0 && p->right->color == 0) {
                p->color = 1;
                b = b->parent;
            }
            else {
                if (p->right->color == 0) {
                    p->left->color = 0;
                    p->color = 1;
                    rr(p);
                    p = b->parent->right;
                }

                p->color = b->parent->color;
                b->parent->color = 0;
                p->right->color = 0;
                ll(b->parent);
                b = root;
            }
        }
        else {
            p = b->parent->left;
            if (p->color == 1) {
                p->color = 0;
                b->parent->color = 1;
                rr(b->parent);
                p = b->parent->left;
            }
            else if (p->right->color == 0) {
                p->color = 1;
                b = b->parent;
            }
            else {
                if (p->left->color == 0) {
                    p->right->color = 0;
                    p->color = 1;
                    ll(p);
                    p = b->parent->left;
                }

                p->color = b->parent->color;
                b->parent->color = 0;
                p->left->color = 0;
                rr(b->parent);
                b = root;
            }
        }
    }
    b->color = 0;
}


void RedBlackTree::deletetion(RBNode* p, int d) {
    RBNode* x = temp;
    RBNode* y;
    RBNode* z;
    while (p != temp) {
        if (p->data.id == d) {
            x = p;
        }

        if (p->data.id >= d) {
            p = p->left;
        }
        else {
            p = p->right;
        }
    }

    if (x == temp) {
        cout << "Key not found " << endl;
        return;
    }

    z = x;
    int colour = z->color;
    if (x->left == temp) {
        y = x->right;
        red_black(x, x->right);
    }
    else if (x->right == temp) {
        y = x->left;
        red_black(x, x->left);
    }
    else {

        RBNode* a = x->right;
        while (a->left != temp) {
            a = a->left;
        }
        z = a;
        colour = z->color;
        y = z->right;
        if (z->parent == x) {
            y->parent = z;
        }
        else {
            red_black(z, z->right);
            z->right = x->right;
            z->right->parent = z;
        }

        red_black(x, z);
        z->left = x->left;
        z->left->parent = z;
        z->color = x->color;
    }
    delete x;
    if (colour == 0) {
        balanced(y);
    }
}

RBNode* RedBlackTree::minimum(RBNode* m) {
    while (m->left != temp) {
        m = m->left;
    }
    return m;
}

void RedBlackTree::blackInsert(RBNode* bl) {
    RBNode* p;
    while (bl->parent->color == 1) {
        if (bl->parent == bl->parent->parent->right) {
            p = bl->parent->parent->left;
            if (p->color == 1) {
                p->color = 0;
                bl->parent->color = 0;
                bl->parent->parent->color = 1;
                bl = bl->parent->parent;
            }
            else {
                if (bl == bl->parent->left)
                {
                    bl = bl->parent;
                    rr(bl);
                }
                bl->parent->color = 0;
                bl->parent->parent->color = 1;
                ll(bl->parent->parent);
            }
        }
        else {
            p = bl->parent->parent->right;

            if (p->color == 1) {
                p->color = 0;
                bl->parent->color = 0;
                bl->parent->parent->color = 1;
                bl = bl->parent->parent;
            }
            else {
                if (bl == bl->parent->right) {
                    bl = bl->parent;
                    ll(bl);
                }
                bl->parent->color = 0;
                bl->parent->parent->color = 1;
                rr(bl->parent->parent);
            }
        }
        if (bl == root) {
            break;
        }
    }
    root->color = 0;
}

void RedBlackTree::print(RBNode* root, string str, bool v) {
    if (root != temp) {
        cout << str;
        if (v) {
            cout << "Right:     ";
            str += "   ";
        }
        else {
            cout << "Left:     ";
            str += "|  ";
        }

        string Color = root->color ? "red" : "black";

        cout << root->data.id << "(" << Color << ")" << "\n";
        print(root->left, str, false);
        print(root->right, str, true);
    }
}

void RedBlackTree::insert(Info d) {
    RBNode* p = new RBNode;
    p->parent = NULL;
    p->data = d;
    p->left = temp;
    p->right = temp;
    p->color = 1;

    RBNode* y = NULL;
    RBNode* x = root;

    while (x != temp) {
        y = x;
        if (p->data.id < x->data.id) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    p->parent = y;
    if (y == NULL) {
        root = p;
    }
    else if (p->data.id < y->data.id) {
        y->left = p;
    }
    else {
        y->right = p;
    }

    if (p->parent == NULL) {
        p->color = 0;
        return;
    }

    if (p->parent->parent == NULL) {
        return;
    }

    blackInsert(p);
}

RBNode* RedBlackTree::getRoot() {
    return root;
}


void RedBlackTree::ll(RBNode* r) {
    RBNode* p = r->right;
    r->right = p->left;
    if (p->left != temp) {
        p->left->parent = r;
    }
    p->parent = r->parent;
    if (r->parent == NULL) {
        root = p;
    }
    else if (r == r->parent->left) {
        r->parent->left = p;
    }
    else
    {
        r->parent->right = p;
    }
    r->left = p;
    r->parent = p;
}

void RedBlackTree::rr(RBNode* r)
{
    RBNode* p = r->left;
    r->left = p->right;
    if (p->right != temp)
    {
        p->right->parent = r;
    }
    p->parent = r->parent;
    if (r->parent == NULL)
    {
        root = p;
    }
    else if (r == r->parent->right)
    {
        r->parent->right = p;
    }
    else
    {
        r->parent->left = p;
    }
    p->right = r;
    r->parent = p;
}

Info separateString(string str) {
    string array[7];
    int j = 0;
    Info obj;
    string b = "";
    bool spmarks = false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ',' && !spmarks)
        {
            array[j] = b;
            j++;
            b = "";

        }
        else if (str[i] == '"') {
            spmarks = !spmarks;
        }
        else {
            b += str[i];
        }
    }
    array[6] = b;
    obj.id = stoi(array[0]);
    obj.year = stoi(array[1]);
    obj.cause113 = array[2];
    obj.cause_name = array[3];
    obj.state = array[4];
    obj.death = array[5];
    obj.death_rate = array[6];

    return obj;
}

void saveFile(Info obj) {
    int folder = obj.id / 1000;
    string path = "data\\" + to_string(folder) + "\\" + to_string(obj.id) + ".txt";

    ofstream fout(path);

    fout << obj.id << '\n' << obj.year << '\n' << obj.cause113 << '\n' << obj.cause_name << '\n';
    fout << obj.state << '\n' << obj.death << '\n' << obj.death_rate;

    fout.close();
}

void pointSearch(int id) {
    int folder = id / 1000;
    string path = "data\\" + to_string(folder) + "\\" + to_string(id) + ".txt";

    ifstream fin(path);
    string text;

    while (getline(fin, text)) {
        cout << text << '\n';
    }
    cout << "\n\n";

    fin.close();
}

void rangeSearch(int minID, int maxID) {
    for (int i = minID; i <= maxID; i++) {
        pointSearch(i);
    }
}

void update(int id, string field, string oldvalue, string newvalue) {
    int folder = id / 1000;
    string path = "data\\" + to_string(folder) + "\\" + to_string(id) + ".txt";

    ifstream fin(path);
    string text;
    Info obj;

    getline(fin, text);
    obj.id = stoi(text);
    getline(fin, text);
    obj.year = stoi(text);
    getline(fin, text);
    obj.cause113 = text;
    getline(fin, text);
    obj.cause_name = text;
    getline(fin, text);
    obj.state = text;
    getline(fin, text);
    obj.death = text;
    getline(fin, text);
    obj.death_rate = text;

    fin.close();

    if (field == "year") {
        obj.year = stoi(newvalue);
    }
    else if (field == "cause113") {
        obj.cause113 = newvalue;
    }
    else if (field == "cause_name") {
        obj.cause_name = newvalue;
    }
    else if (field == "state") {
        obj.state = newvalue;
    }
    else if (field == "death") {
        obj.death = newvalue;
    }
    else if (field == "death_rate") {
        obj.death_rate = newvalue;
    }

    ofstream fout(path);
    fout << obj.id << '\n' << obj.year << '\n' << obj.cause113 << '\n' << obj.cause_name << '\n';
    fout << obj.state << '\n' << obj.death << '\n' << obj.death_rate;
    fout.close();
}

void deleteKey(int id) {
    int folder = id / 1000;
    string path = "data\\" + to_string(folder) + "\\" + to_string(id) + ".txt";
    ofstream fout(path);
    fout.close();
}

int main() {

    string var;
    Info obj;
    AVL avl;
    node* avlRoot = NULL;
    BTree btree(3);
    RedBlackTree rb;

    for (int i = 1; i <= 10; i++) {
        cout << i << "\n";
        ifstream file("datafiles/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(i) + ".csv");
        getline(file, var);

        while (getline(file, var)) {
            obj = separateString(var);
            saveFile(obj);
            avlRoot = avl.insert(avlRoot, obj);
            btree.insertion(obj);
            rb.insert(obj);
        }
    }
    cout << "\n\n";

    deleteKey(50);
    pointSearch(50);
    rangeSearch(103, 107);
    update(1, "year", "2016", "2003");

    /*avl.CurrentLevelOrder(avlRoot);
    cout << "\n\n\n\n";
    btree.traverse();
    cout << "\n\n\n\n";
    RBNode* rbRoot = rb.getRoot();
    rb.print(rbRoot, "", true);
    cout << "\n\n\n\n";*/

    return 0;
}