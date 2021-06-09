#pragma once
/*
A red-black tree (RB-Tree) is a self-balancing binary search tree that guarantees logarithmic growth of the tree
height with the number of nodes and quickly performs the basic operations of the search tree: add, 
remove and find a node. Balance is achieved through the introduction of an additional attribute 
of the tree node - "colors". This attribute can take one of two possible values - "black" or "red".
*/
#include <iostream>
#include "List.h"

using namespace std;

template<class T>
class RB_Tree {
private:
    template<class T>
    class Node {
    public:
        Node(T key, T value, Node<T> *leftChild = nullptr, Node<T> *rightChild = nullptr, Node<T> *parent = nullptr,
             bool color = true) { // Red color = true, black = false
            this->key = key;
            this->value = value;
            this->leftChild = leftChild;
            this->rightChild = rightChild;
            this->parent = parent;
            this->color = color;
        };

        ~Node() {};

        T key;
        T value;
        Node<T> *leftChild;
        Node<T> *rightChild;
        Node<T> *parent;
        bool color;
    };

    Node<T> *root;
    Node<T> *nil;
public:
    RB_Tree();

    ~RB_Tree();

    void left_rotate(Node<T> *);

    void right_rotate(Node<T> *);

    void insert(T, T); // adding an item with key and value

    void recover_tree_insert(Node<T> *);

    Node<T> *find(T); // item search by key

    void remove(T); // deleting a tree element by key

    void recover_tree_remove(Node<T> *);

    void clear(); // clearing an associative array

    List<T> get_keys(); // returns a list of keys

    void get_next_key(List<T> *, Node<T> *);

    List<T> get_values(); // returns a list of values

    void get_next_value(List<T> *, Node<T> *);

    void print(Node<T> *current = nullptr);
};

template<typename T>
RB_Tree<T>::RB_Tree() { // constructor
    nil = new Node<T>(' ', ' ', nullptr, nullptr, nullptr,
                      false); // this link is needed to combine all links to the missing element
    root = nil;
}

template<typename T>
RB_Tree<T>::~RB_Tree() { //deconstructor
    clear();
    root = nullptr;
    nil = nullptr;
}

template<typename T>
void RB_Tree<T>::left_rotate(Node<T> *x) {
    Node<T> *y;
    Node<T> *p;
    if (x->rightChild == nil) {
        return;
    } else {
        y = x->rightChild;
        p = x->parent;
        if (y->leftChild != nil) {
            x->rightChild = y->leftChild;
            x->rightChild->parent = x;
        } else
            x->rightChild = nil;
        if (x->parent == nullptr) {
            y->parent = nullptr;
            root = y;
        } else if (p->leftChild == x) {
            p->leftChild = y;
            y->parent = p;
        } else {
            p->rightChild = y;
            y->parent = p;
        }
        x->parent = y;
        y->leftChild = x;
    }
}

template<typename T>
void RB_Tree<T>::right_rotate(Node<T> *y) {
    Node<T> *x;
    Node<T> *p;
    if (y->leftChild == nil) {
        return;
    } else {
        x = y->leftChild;
        p = y->parent;
        if (x->rightChild != nil) {
            y->leftChild = x->rightChild;
            x->rightChild->parent = y;
        } else
            y->leftChild = nil;
        if (y->parent == nullptr) {
            root = x;
            x->parent = nullptr;
        } else if (y == p->rightChild) {
            p->rightChild = x;
            x->parent = p;
        } else {
            p->leftChild = x;
            x->parent = p;
        }
        x->rightChild = y;
        y->parent = x;
    }
}

// adding an item with key and value
template<typename T>
void RB_Tree<T>::insert(T key, T value) {
    Node<T> *current;
    Node<T> *newNode;
    bool to_right;
    if (key == ' ') {
        throw "Key error: the key cannot have the given value";
    }
    newNode = new Node<T>(key, value, nil, nil); // create new node
    if (root == nil) {
        root = newNode;
        root->color = false; //repaint root color in black
    } else {
        to_right = false; //set value for right child as false
        current = root;
        while (true) { // run for a tree to find a leaf for insert
            if (newNode->key > current->key && current->rightChild != nil) {
                current = current->rightChild;
            } else if (newNode->key <= current->key && current->leftChild != nil) {
                current = current->leftChild;
            } else if (newNode->key <= current->key && current->leftChild == nil) {
                break;
            } else {
                to_right = true;
                break;
            }
        }
        if (to_right) { // set a new node as a right child
            current->rightChild = newNode;
        } else { // set a new node as a left child
            current->leftChild = newNode;
        }
        newNode->parent = current;
        recover_tree_insert(newNode); // call method for recover tree properties
    }
}

/*
This algorithm is used to maintain the red-black tree property
if inserting a new node violates this property
*/
template<typename T>
void RB_Tree<T>::recover_tree_insert(Node<T> *newNode) {
    Node<T> *p; //parent
    Node<T> *grandParent;
    if (newNode == nil) {
        throw "Unexpected node recieved";
    } else {
        p = newNode->parent;
        grandParent = p->parent;
        while (p->color && p) { // the algorithm is executed while the color of the node is red
            if (p == grandParent->leftChild) {
                // case 1
                if (grandParent->rightChild->color) {
                    grandParent->leftChild->color = false;
                    grandParent->rightChild->color = false;
                    grandParent->color = true;
                    newNode = grandParent;
                } else {
                    // case 2
                    if (newNode == p->rightChild) {
                        newNode = p;
                        left_rotate(newNode);
                    }
                    // case 3
                    p->color = false;
                    grandParent->color = true;
                    right_rotate(grandParent);
                }
            } else {
                // case 1
                if (grandParent->leftChild->color) {
                    grandParent->leftChild->color = false;
                    grandParent->rightChild->color = false;
                    grandParent->color = true;
                    newNode = grandParent;
                } else {
                    // case 2
                    if (newNode == p->leftChild) {
                        newNode = p;
                        right_rotate(newNode);
                    }
                    // case 3
                    p->color = false;
                    grandParent->color = true;
                    left_rotate(grandParent);
                }
            }
            root->color = false;
        }
    }
}

// item search by key
template<typename T>
RB_Tree<T>::Node<T> *RB_Tree<T>::find(T key) {
    Node<T> *current = root;
    while (current != nil) {
        if (current->key == key)
            return current;
        else if (current->key > key)
            current = current->leftChild;
        else current = current->rightChild;
    }
    return nullptr;
}

/*
Removing a node may or may not violate the red-black properties of the tree
If this happens, then the algorithm for restoring the properties of red-black is used.
*/
template<typename T>
void RB_Tree<T>::remove(T key) {
    Node<T> *nodeToBeDeleted;
    Node<T> *min;
    Node<T> *x;
    bool originalColor;
    nodeToBeDeleted = find(key); // looking for an node to delete by key
    if (nodeToBeDeleted) { // if the search was successful
        originalColor = nodeToBeDeleted->color; // Store the nodeToBeDeleted color to origrinalColor
        if (nodeToBeDeleted->leftChild == nil) { // if left child of nodeToBeDeleted is nil
            x = nodeToBeDeleted->rightChild; // then swap nodeToBeDeleted with right child
            if (nodeToBeDeleted->parent == nullptr) {
                root = nodeToBeDeleted->rightChild;
            } else if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild) {
                nodeToBeDeleted->parent->leftChild = nodeToBeDeleted->rightChild;
            } else {
                nodeToBeDeleted->parent->rightChild = nodeToBeDeleted->rightChild;
            }
            nodeToBeDeleted->rightChild->parent = nodeToBeDeleted->parent;
        } else if (nodeToBeDeleted->rightChild == nil) { // if right child of nodeToBeDeleted is nil
            x = nodeToBeDeleted->leftChild; // then swap nodeToBeDeleted with left child
            if (nodeToBeDeleted->parent == nullptr) {
                root = nodeToBeDeleted->leftChild;
            } else if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild) {
                nodeToBeDeleted->parent->leftChild = nodeToBeDeleted->leftChild;
            } else {
                nodeToBeDeleted->parent->rightChild = nodeToBeDeleted->leftChild;
            }
            nodeToBeDeleted->leftChild->parent = nodeToBeDeleted->parent;
        } else {
            min = nodeToBeDeleted->rightChild; // assign the minimum of right subtree of noteToBeDeleted into min
            while (min->leftChild != nil)
                min = min->leftChild;
            originalColor = min->color; // save the color of min in originalColor
            x = min->rightChild; // assign the rightChild of min into x
            if (min->parent == nodeToBeDeleted) { // if y is a child of nodeToBeDeleted 
                x->parent = min; // then set the parent of x as min
            } else { // else, transplant min with rightChild of min
                if (min->parent == nullptr) {
                    root = min->rightChild;
                } else if (min == min->parent->leftChild) {
                    min->parent->leftChild = min->rightChild;
                } else {
                    min->parent->rightChild = min->rightChild;
                }
                min->rightChild->parent = min->parent;
                min->rightChild = nodeToBeDeleted->rightChild;
                min->rightChild->parent = min;
            }
            // transplant nodeToBeDeleted with min
            if (nodeToBeDeleted->parent == nullptr) {
                root = min;
            } else if (nodeToBeDeleted == nodeToBeDeleted->parent->leftChild) {
                nodeToBeDeleted->parent->leftChild = min;
            } else {
                nodeToBeDeleted->parent->rightChild = min;
            }
            min->parent = nodeToBeDeleted->parent;
            min->leftChild = nodeToBeDeleted->leftChild;
            min->leftChild->parent = min;
            min->color = nodeToBeDeleted->color; // set the color of min with originalColor
        }
        delete nodeToBeDeleted;
        if (!originalColor) { // calling the recovery algorithm if a node with black color has been deleted
            recover_tree_remove(x);
        }
    } else {
        throw "There is no such element!";
    }
}

/*
This algorithm is called if a black node has been removed 
because the black height of the tree is violated
*/
template<typename T>
void RB_Tree<T>::recover_tree_remove(Node<T> *x) {
    Node<T> *w;
    while (x != root && !x->color) {
        if (x->parent->leftChild == x) {
            w = x->parent->rightChild;
            // Case 1
            if (w->color) {
                w->color = false;
                x->parent->color = true;
                left_rotate(x->parent);
                w = x->parent->rightChild;
            }
            // Case 2
            if (w->leftChild->color == false && w->rightChild->color == false) {
                w->color = true;
                x = x->parent;
            }
            // Case 3
            else if (w->rightChild->color == false) {
                w->leftChild->color = false;
                w->color = true;
                right_rotate(w);
                w = x->parent->rightChild;
            } else {
            // Case 4
                w->color = x->parent->color;
                x->parent->color = false;
                w->rightChild->color = false;
                left_rotate(x->parent);
                x = root;
            }
        } else {
            w = x->parent->leftChild;
            // Case 1
            if (w->color == true) {
                w->color = false;
                x->parent->color = true;
                right_rotate(x->parent);
                w = x->parent->leftChild;
            }
            // Case 2
            if (w->leftChild->color == false && w->rightChild->color == false) {
                w->color = true;
                x = x->parent;
            }
            // Case 3
            else if (w->leftChild->color == false) {
                w->rightChild->color = false;
                w->color = true;
                left_rotate(w);
                w = x->parent->leftChild;
            }
            // Case 4
            else {
                w->color = x->parent->color;
                x->parent->color = false;
                w->leftChild->color = false;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false;
    root->color = false;
}

// clearing an associative array
template<typename T>
void RB_Tree<T>::clear() {
    while (root != nil)
        remove(root->key);
}

// returns a list of keys
template<typename T>
List<T> RB_Tree<T>::get_keys() {
    List<T> keys;
    Node<T> *current = root;
    get_next_key(&keys, current);
    return keys;
}

// using recursion to collect an array of keys
template<typename T>
void RB_Tree<T>::get_next_key(List<T> *keys, Node<T> *current) {
    if (current != nil) {
        keys->push_back(current->key);
        get_next_key(&*keys, current->leftChild);
        get_next_key(&*keys, current->rightChild);
    }
}

// returns a list of values
template<typename T>
List<T> RB_Tree<T>::get_values() {
    List<T> values;
    Node<T> *current = root;
    get_next_value(&values, current);
    return values;
}

// using recursion to collect an array of values
template<typename T>
void RB_Tree<T>::get_next_value(List<T> *values, Node<T> *current) {
    if (current != nil) {
        values->push_back(current->value);
        get_next_value(&*values, current->leftChild);
        get_next_value(&*values, current->rightChild);
    }
}

// print to console
template<typename T>
void RB_Tree<T>::print(Node<T> *current) {
    if (root != nil) {
        if (current == nullptr)
            current = root;
        cout << "Key: " << current->key << " |Value: " << current->value << " |Color: ";
        if (current->color)
            cout << "Red";
        else
            cout << "Black";
        if (!current->parent)
            cout << " |Parent: No";
        else
            cout << " |Parent: " << current->parent->key;
        if (current->leftChild == nil)
            cout << " |Left : nil";
        else
            cout << " |Left : " << current->leftChild->key;
        if (current->rightChild == nil)
            cout << " |Right : nil";
        else
            cout << " |Right : " << current->rightChild->key;
        cout << endl;
        if (current->leftChild != nil)
            print(current->leftChild);
        if (current->rightChild != nil)
            print(current->rightChild);
    } else
        cout << "Tree is empty" << endl;
}