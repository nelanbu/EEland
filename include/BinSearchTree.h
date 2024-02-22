#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H
#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include <queue>

using namespace std;


class BinSearchTree //this class is to store flights including occupancy state and right and left pointers
{
private:
    BinSearchTree *left;
    BinSearchTree *right;
    int OccupancyState;
public:
    string key; // key is the data (flight numbers in string form) stored in binary search tree
    BinSearchTree(string &item,BinSearchTree* lptr=NULL,BinSearchTree* rptr=NULL) //constructor
    {
        key=item;
        left=lptr;
        right=rptr;

    }
    BinSearchTree * Left()
    {
        return left;
    }
    BinSearchTree * Right()
    {
        return right;
    }
    ~BinSearchTree();
//all methods will be explained after class declaration
    void AddTFlight(string flight, BinSearchTree *root);
    BinSearchTree* SearchTFlight(string search_key,BinSearchTree *root);
    void PrintTree(BinSearchTree *root) const;
    BinSearchTree *clone(BinSearchTree *root);
    int GetOccupancyState();
    void SetOccupancyState();
    void printLevelOrder(BinSearchTree *root);
    BinSearchTree* RemoveTFlight(string key, BinSearchTree *root);
    BinSearchTree* deleteRoot(BinSearchTree* root);

};

BinSearchTree* BinSearchTree::clone(BinSearchTree *root) //it clones the input flight plan and it adds occupancy state to each flight.
{
    if(root==NULL)
    {
        return NULL;
    }
    BinSearchTree *newRoot;
    newRoot= new BinSearchTree(root->key);
    newRoot->SetOccupancyState();
    newRoot->left=clone(root->left);
    newRoot->right=clone(root->right);
    return newRoot;
}

BinSearchTree* BinSearchTree::RemoveTFlight(string key, BinSearchTree *root) //this method removes the input flight number from the tree
{
    if(root == NULL || root->key.compare(key)==0)
        return deleteRoot(root);
    BinSearchTree* curr = root;
    while(1) {
         string x = curr->key;
         if(key.compare(x) < 0){ //compare is used here to check whether input key and current node's key is equal or not
            if(curr->left == NULL || curr->left->key.compare(key) == 0)
            {
               curr->left = deleteRoot(curr->left);
               break;
            }
            curr = curr->left;
         }
         else
        {
            if(curr->right == NULL || curr->right->key.compare(key) == 0)
            {
               curr->right = deleteRoot(curr->right);
               break;
            }
            curr = curr->right;
         }
      }
      return root;
}
BinSearchTree* BinSearchTree::deleteRoot(BinSearchTree* root) //this method is used above method to remove a node from binary search tree
{
    if(root==NULL)
        return NULL;
    if(root->right == NULL)
        return root->left;
    BinSearchTree* x = root->right;
    while(x->left!=NULL)
    {
        x = x->left;
    }

    x->left = root->left;
    return root->right;
}


void BinSearchTree::AddTFlight(string flight, BinSearchTree *root) //this method adds new flights to the tree after finding the suitable place for it
{
    BinSearchTree* newNode= new BinSearchTree(flight); //a new node is created
    BinSearchTree *current=root;
    BinSearchTree *parent=NULL;


     while (current != NULL) {
        parent= current;
        int res1= flight.compare(current->key); // we compare the keys
        if (res1<0)
            current = current->left;
        else
            current = current->right;
    }
    int res2= flight.compare(parent->key);
    if (res2<0)
        parent->left = newNode;
    else
        parent->right = newNode;

}
void BinSearchTree::printLevelOrder(BinSearchTree *root) // this method uses queue to search level order of the tree and it prints the tree
{
    // Base Case
    if (root == NULL) return;

    // Create an empty queue for level order traversal
    Queue <BinSearchTree *> q;

    // Enqueue Root and initialize height
    q.Qinsert(root);

    while (q.QEmpty() == false)
    {
        // nodeCount (queue size) indicates number
        // of nodes at current level.
        int nodeCount = q.Qlength();

        // Dequeue all nodes of current level and
        // Enqueue all nodes of next level
        while (nodeCount > 0)
        {
            BinSearchTree *node = q.Qfront();
            cout << node->key << " ";
            q.Qdelete();
            if (node->left != NULL)
                q.Qinsert(node->left);
            if (node->right != NULL)
                q.Qinsert(node->right);
            nodeCount--;
        }
        cout << endl;
    }
}

void BinSearchTree::PrintTree(BinSearchTree *root) const //this method prints the tree and the occupancy state of each flight
{
    if(root==NULL)
    {
        return;
    }
    cout<<"Flight no: "<<root->key<<" Occupancy state: "<<root->OccupancyState<<endl;
    PrintTree(root->left);
    PrintTree(root->right);
}
int BinSearchTree::GetOccupancyState() //returns occupancy state
{
    return OccupancyState;
}
void BinSearchTree::SetOccupancyState() //sets occupancy state as a random number between 0-100
{
    int occ=rand()%101;
    OccupancyState=occ;
}
BinSearchTree* BinSearchTree::SearchTFlight(string search_key, BinSearchTree *root) //this method searches input flight number in the binary search tree
{                                                                                   //by doing recursive to traverse all nodes
    if(root==NULL)
        return NULL;
    int res = root->key.compare(search_key);
    if(res==0)
        return root;

    if(res>0)
    {
        return SearchTFlight(search_key, root->left);
    }
    else
    {
        return SearchTFlight(search_key, root->right);
    }
}




#endif // BINSEARCHTREE_H
