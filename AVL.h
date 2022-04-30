//
// Created by Xinpeng Liu on 4/30/22.
//

#ifndef REPORTSTYLEANALYZER_AVL_H
#define REPORTSTYLEANALYZER_AVL_H

#include <iostream>
#include <deque>
#include <iomanip>
#include <cmath>
#include <iterator>

using namespace std;

template <class xtype>
struct tnode
{
    int balance;
    xtype info;
    tnode<xtype> *left;
    tnode<xtype> *right;
    int count;
};

template <class xtype>
class AVLtree
{
private:
    tnode<xtype> *root;
public:
    AVLtree();
    ~AVLtree();
    void destroy();
    void destroy (  tnode<xtype> * &);
    AVLtree (const AVLtree<xtype> &);
    void copyAVL (tnode<xtype>* & , tnode<xtype> *);
    bool isEmpty();
    void rotateLeft (tnode<xtype> * &);
    void rotateRight (tnode<xtype> * &);
    void balanceLeft ( tnode<xtype> * &);
    void balanceRight ( tnode<xtype> * &);
    void insertNode (tnode<xtype> * &, xtype , bool &);
    void insert (xtype );
    int  maxH(tnode<xtype> *);
    void printB(int , int , int , int , const deque<tnode<xtype>*>& );
    void printN(int , int , int , int , const deque<tnode<xtype>*>& );
    void printL(int , const deque<tnode<xtype>*>& );
    void printAVL(tnode<xtype> * );
    void print();
    void Delete( xtype item);
    void Delete( tnode<xtype> *&p, xtype item);
    void DeleteNode( tnode<xtype> *&p);

    /**
     * @Brief Function searches if an item is in the tree or not
     * @Input The item to search
     * @Output If the item in the tree, return TRUE. Otherwise, FALSE
     */
    bool searchItem(xtype item);

    /**
     * @Brief Function searches if an item is in the tree or not
     * @Input The item to search and an integer reference (passed by user)
     * which is used to record the count of the item
     */
    void getCount(xtype item, int& count);
};


#endif //REPORTSTYLEANALYZER_AVL_H
