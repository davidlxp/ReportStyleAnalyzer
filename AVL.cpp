//
// Created by Xinpeng Liu on 4/30/22.
//

#include "AVL.h"

template <class xtype>
void AVLtree<xtype> :: Delete( xtype item)
{
    Delete (root,item);
}
template <class xtype>
void AVLtree<xtype> :: Delete( tnode<xtype> *&p, xtype item)
{
    if (p == NULL)
        cout<<"ITEM NOT IN TREE";
    else
    {
        if ( item < p->info)
            Delete (p->left,item);
        else if ( item > p->info)
            Delete (p->right,item);
        else
        {
            DeleteNode (p);

        }


    }
}
template <class xtype>
void AVLtree<xtype> :: DeleteNode( tnode<xtype> *&p)
{
    tnode<xtype> *s =p;

    if (p->left == NULL)
        p = p->right;

    else if (p->right == NULL )
        p = p->left;
    else
    {
        s= p->left;
        tnode<xtype> *r= NULL;

        while (s->right != NULL)
        {
            r = s;
            s = s->right;
        }
        p->info = s->info;

        if ( r != NULL )
            r->right = s->left;
        else p->left = s->left;

    }

    delete s;
}

template <class xtype>
AVLtree<xtype> :: AVLtree()
{
    root = NULL;
}

template <class xtype>
AVLtree<xtype> :: ~AVLtree()
{
    destroy (root);
}
template <class xtype>
void AVLtree<xtype> :: destroy()
{
    destroy (root);
}

template <class xtype>
void AVLtree<xtype> :: destroy( tnode<xtype> * &p)
{
    if ( p != NULL )
    {
        destroy (p->left);
        destroy (p->right);
        delete p;
        p = NULL;
    }
}

template <class xtype>
void AVLtree<xtype> :: copyAVL(tnode<xtype>* & troot, tnode<xtype> *croot)
{
    if ( croot == NULL )
        troot = NULL;
    else
    {
        troot = new tnode<xtype>;
        troot->info = croot->info;
        copyAVL (troot->left, croot->left);
        copyAVL (troot->right, croot->right);
    }
}

template <class xtype>
AVLtree<xtype> :: AVLtree(const AVLtree<xtype> & other)
{
    if ( other.root == NULL )
        root = NULL;
    else
    {    destroy(root);
        copyAVL (root, other.root);
    }
}

template <class xtype>
bool AVLtree<xtype> :: isEmpty()
{
    return root == NULL;
}

template <class xtype>
void AVLtree<xtype>:: rotateLeft ( tnode<xtype> * &p)
{
    // holds  right of p
    tnode<xtype> * q;

    if ( p == NULL || p->right == NULL )
        cout <<"ERROR – TREE EMPTY OR NO RIGHT CHILD";
    else
    {
        q = p->right;
        // make left become right
        p->right = q->left;
        q->left = p;
        // p is new root
        p = q;
    }
}

template <class xtype>
void AVLtree<xtype>:: rotateRight ( tnode<xtype> * &p)
{
    // holds left of p
    tnode<xtype> * q;

    if ( p == NULL || p->left == NULL )
        cout <<"ERROR – TREE EMPTY OR NO LEFT CHILD";
    else
    {
        q = p->left;
        // make left become right
        p->left = q->right;
        q->right = p;
        // p is new root
        p = q;
    }
}

template <class xtype>
void AVLtree<xtype> :: balanceLeft ( tnode<xtype> * &p)
{
    tnode<xtype> *l;
    tnode<xtype> *r;

    l = p->left;

    if ( l->balance == -1 )
    {
        p->balance = 0;
        l->balance = 0;
        rotateRight (p);
    }
    else if ( l->balance == 1 )
    {
        r = l->right;
        if ( r->balance == -1 )
        {
            p->balance = 1;
            l->balance = 0;
        }
        else if ( r->balance == 1 )
        {
            p->balance = 0;
            l->balance = -1;
        }
        else if ( r->balance == 0 )
        {
            p->balance = 0;
            l->balance = 0;
        }
        r->balance = 0;
        rotateLeft (l);
        p->left = l;
        rotateRight (p);
    }
    else  cout <<"ERROR";
}

template <class xtype>
void AVLtree<xtype> :: balanceRight ( tnode<xtype> * &p)
{
    tnode<xtype> *l;
    tnode<xtype> *r;

    r = p->right;

    if ( r->balance == -1 )
    {
        l = r->left;
        if ( l->balance == -1 )
        {
            p->balance = 0;
            r->balance = 1;
        }
        else if ( l->balance == 1 )
        {
            p->balance = -1;
            r->balance = 0;
        }
        else if ( l->balance == 0 )
        {
            p->balance = 0;
            r->balance = 0;
        }
        l->balance = 0;
        rotateRight (r);
        p->right = r;
        rotateLeft (p);
    }
    else if ( r->balance == 1 )
    {
        p->balance = 0;
        r->balance = 0;
        rotateLeft(p);
    }
    else  cout <<"ERROR";
}

template <class xtype>
void AVLtree<xtype>:: insertNode (tnode<xtype> * &p, xtype item, bool &taller)
{
    if (p == NULL )
    {
        p = new tnode<xtype>;
        p->info = item;
        p->left = NULL;
        p->right =NULL;
        p->balance = 0;
        taller = true;
    }
    else if ( p->info == item )
        cout<<"ERROR NO DUPLICATES";
    else if ( p->info > item)
    {
        insertNode (p->left,item,taller);

        if (taller)
        {
            if ( p->balance == -1)
            {
                balanceLeft(p);
                taller = false;
            }
            else if (p->balance == 1)
            {
                p->balance = 0;
                taller = false;
            }
            else
                p->balance = -1;
        }
    }
    else
    {
        insertNode (p->right,item,taller);

        if (taller)
        {
            if ( p->balance == -1)
            {
                p->balance = 0;
                taller = false;
            }
            else if (p->balance == 1)
            {
                balanceRight(p);
                taller = false;
            }
            else
                p->balance = 1;
        }
    }
}

template <class xtype>
void AVLtree<xtype> :: insert (xtype item )
{
    bool taller = false;
    insertNode (root,item,taller);
}

template <class xtype>
int AVLtree<xtype> :: maxH(tnode<xtype> *p)
{

    if (p == NULL)
        return 0;

    int leftH = maxH(p->left);
    int rightH = maxH(p->right);

    return (leftH > rightH) ? leftH + 1: rightH + 1;

}

template <class xtype>
void AVLtree<xtype>:: printB(int bLen, int nSpLen, int sLen, int nLevel, const deque<tnode<xtype>*>& nQ)
{

    typename deque<tnode<xtype>*>::const_iterator it = nQ.begin();

    for (int i = 0; i < nLevel / 2; i++)
    {
        cout << ((i == 0) ? setw(sLen-1) : setw(nSpLen-2)) << "" << ((*it++) ? "/" : " ");
        cout << setw(2*bLen+2) << "" << ((*it++) ? "\\" : " ");
    }
    cout << endl;
}


template <class xtype>
void AVLtree<xtype> :: printN(int bLen, int nSpLen, int sLen, int nLevel, const deque<tnode<xtype>*>& nQ)
{

    typename deque<tnode<xtype>*>::const_iterator it = nQ.begin();

    for (int i = 0; i < nLevel; i++, it++)
    {
        cout << ((i == 0) ? setw(sLen) : setw(nSpLen)) << "" << ((*it && (*it)->left) ?  setfill('_') : setfill(' '));

        cout << setw(bLen+2);
        if ((*it) != NULL )
            cout<< (*it)->info;
        else cout<< "";

        cout << ((*it && (*it)->right) ? setfill('_') : setfill(' ')) << setw(bLen) << "" << setfill(' ');
    }
    cout << endl;
}

template <class xtype>
void AVLtree<xtype> :: printL(int nLevel, const deque<tnode<xtype>*>& nQ)
{

    typename deque<tnode<xtype>*>::const_iterator it = nQ.begin();

    for (int i = 0; i < nLevel; i++, it++)
    {
        cout << ((i == 0) ? setw(2) : setw(4));
        if ((*it) != NULL )
            cout<< (*it)->info;
        else cout<< "";

    }
    cout << endl;
}

template <class xtype>
void AVLtree<xtype> :: printAVL(tnode<xtype> *p)
{
    int h = maxH(p);
    int nLevel = 1;

    int bLen = 2*((int)pow(2.0,h)-1) - 2*(int)pow(2.0,h-1);

    int nSpaceLen = 2 + 2*(int)pow(2.0,h);

    int sLen = bLen + 2;

    deque<tnode<xtype>*> nQ;
    nQ.push_back(p);

    for (int r = 1; r < h; r++)
    {
        printB(bLen, nSpaceLen, sLen, nLevel, nQ);
        bLen = bLen/2 - 1;
        nSpaceLen = nSpaceLen/2 + 1;
        sLen = bLen + 2 ;
        printN(bLen, nSpaceLen, sLen, nLevel, nQ);

        for (int i = 0; i < nLevel; i++)
        {
            tnode<xtype> *q = nQ.front();
            nQ.pop_front();

            if (q != NULL)
            {
                nQ.push_back(q->left);
                nQ.push_back(q->right);
            }
            else
            {
                nQ.push_back(NULL);
                nQ.push_back(NULL);
            }
        }
        nLevel *= 2;
    }
    printB(bLen, nSpaceLen, sLen, nLevel, nQ);
    printL(nLevel, nQ);
}

template <class xtype>
void AVLtree<xtype> :: print()
{
    cout<<"\n\n\n   ";
    printAVL(root);
}
