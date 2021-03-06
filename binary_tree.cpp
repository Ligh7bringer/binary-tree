#include "binary_tree.h"

// Creates an empty binary tree
binary_tree::binary_tree()
{
    tree = nullptr;
    return;
}


// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value)
{
    tree = new node;
    tree->data = value;
    tree->left = nullptr;
    tree->right = nullptr;
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values)
{
    for(int i = 0; i < values.size(); ++i) 
        insert(values[i]);
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{

}

// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{
    //clearTree(tree);
}


// Adds a value to the tree
void binary_tree::insert(int value)
{
    node* t = new node;
    node* parent;
    t->data = value;
    t->left = nullptr;
    t->right = nullptr;
    parent = nullptr;
    // tree is empty
    if(tree == nullptr) 
        tree = t;
    else {
        node* curr;
        curr = tree;
        // Find the Node's parent
        while(curr) {
            parent = curr;
            if(t->data > curr->data) curr = curr->right;
            else curr = curr->left;
        }
        if(t->data < parent->data) 
            parent->left = t;            
        else
            parent->right = t;
    }
}

// Removes a value from the tree
void binary_tree::remove(int value) {
    node* curr;
    node *prev = new node;
    curr = tree;
    while(curr) {
        if(value > curr->data) {
            //go right
            prev = curr;
            curr = curr->right;
        } else if(value < curr->data) {
            //go left
            prev = curr;
            curr = curr->left;
        } else if(value == curr->data) {
            if(curr->left == nullptr && curr->right == nullptr) { //the node has no other nodes attached to it
                if(prev->right == curr)
                    prev->right = nullptr; //delete links
                if(prev->left == nullptr)
                    prev->left = nullptr; //delete links
                //delete node
                delete curr;
                curr = nullptr;
            } else if(curr->left != nullptr && curr->right == nullptr) { //the node has a node attached to its left
                if(prev->left == curr) {
                    prev->left = curr->left;
                    delete curr;
                    curr = nullptr;                    
                } else {
                    prev->right=curr->left;
                    delete curr;
                    curr = nullptr;                    
                }
            } else if(curr->left == nullptr && curr->right != nullptr) { // the node has a node attached to its right
                if(prev->left==curr) {                                   //not relevant for tests.cpp (?) but should be included as a case
                    prev->left=curr->right;
                    delete curr;
                    curr=nullptr;                    
                } else {              
                    prev->right=curr->right;
                    delete curr;
                    curr=nullptr;                    
                }
            } else if(curr->left != nullptr && curr->right != nullptr) { // the node has 2 nodes attached to it
                node* check=curr->right;
                if((curr->left==nullptr)&&(curr->right==nullptr)) {
                    curr=check;
                    delete check;
                    curr->right=nullptr;                           
                } else {// righ branch has nodes attached to itself                     
                    if((curr->right)->left!=nullptr) {
                        node* leftcurr;
                        node* leftcurrPrev;
                        leftcurrPrev=curr->right;
                        leftcurr=(curr->right)->left;
                        while(leftcurr->left != nullptr) {
                            leftcurrPrev=leftcurr;
                            leftcurr=leftcurr->left;
                        }
                        curr->data=leftcurr->data;
                        delete leftcurr;
                        leftcurrPrev->left=nullptr;                
                    } else {
                        node* temp=curr->right;
                        curr->data=temp->data;
                        curr->right=temp->right;
                        delete temp;                
                    }
                }
            }
        } else return;
    }
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
    if(tree == nullptr) // if tree is empty return false
        return false;
    else { //tree has elements, find value in it
        node* curr;
        curr = tree;
        while(curr) {
            if(value > curr->data) //value greater than node's value, go right
                curr = curr->right; 
            else if(value < curr->data) //value lower than node's value, go left
                curr = curr->left;
            else if(value == curr->data) //value was found in tree
                return true;
        }
    }
    return false; //value was not found in tree, return false
}

// Prints the tree to standard out in numerical order
std::string binary_tree::inorder() const
{ 
    node *current = new node;
    node *pre = new node;
    string str = "";
     
    if(tree == nullptr)
        return string(""); 
     
    current = tree;
    while(current != nullptr) {                 
        if(current->left == nullptr){
            str += to_string(current->data) + " ";
            current = current->right;      
        } else {
            pre = current->left;
            while(pre->right != nullptr && pre->right != current)
                pre = pre->right;
     
            if(pre->right == nullptr) {
                pre->right = current;
                current = current->left;
            } else {
                pre->right = nullptr;
                str += to_string(current->data) + " ";
                current = current->right;      
            } 
        }
    } 
    string result = str.substr(0, str.size()-1);
    return str;
}

// Prints the tree in pre-order
std::string binary_tree::preorder() const
{
    node *curr = new node;
    node *prev = new node;
    node *next = new node;
    string str = "";
    node *stack[50];
    int pos = 0;
    int pop = 0;
     
    if(tree == nullptr)
        return string(""); 
     
    curr = tree;
    while(curr != nullptr) {                 
        if(curr->left != nullptr && curr->right != nullptr) { //node attached to the left and right
            str += to_string(curr->data) + " ";
            stack[pos] = new node;
            stack[pos] = curr->right;            
            curr = curr->left;            
            pos++;                     
        } else if(curr->left != nullptr && curr->right == nullptr) { //node attached to the left
            str += to_string(curr->data) + " ";
            curr = curr->left;
       } else if(curr->left == nullptr && curr->right != nullptr) { //node attached to the right
            str += to_string(curr->data) + " ";
            curr = curr->right;
        } else if(curr->left == nullptr && curr->right == nullptr) { //no nodes attached, go to 'next'
            str += to_string(curr->data) + " ";
            if(pop < pos) {
                curr = stack[pop];
                pop++;                              
            } else break;
        }       
    }
    
    for (int i = 0; i < pos; i++) {
        delete stack[i];
        stack[i] = nullptr;
    }
    string result = str.substr(0, str.size()-1);    
    return result;
}

// Prints the tree in post-order
std::string binary_tree::postorder() const
{
    return std::string("");
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{
    return binary_tree();
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
    return true;
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
    return true;
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
    return binary_tree();
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{

    return binary_tree();
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value)
{
    return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value)
{
    return out;
}

