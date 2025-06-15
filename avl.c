#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

/****
  Student1 name:Dema Omar
  Student2 name: Samia Sleman

****/

AVLNodePtr Rightrotate(AVLNodePtr t);
AVLNodePtr Balance(AVLNodePtr node);
AVLNodePtr Leftrotate(AVLNodePtr t);
AVLNodePtr minnode(AVLNodePtr node);
AVLNodePtr new_avl_tree(int*arr,int start,int end);
int* merge_two_arrays(int *arr1,int size1,int *arr2,int size2, int* len);
void copy_to_array(AVLNodePtr root, int *arr, int* i);
int avl_sumX(AVLNodePtr newRoot, int x, int y, int summing);
int avl_sumY(AVLNodePtr newRoot, int x, int y, int summing);


int util_max(int x,int y)          /*return the max*/
{
    return x>y?x:y;
}
int util_abs(int x)                /*return the positive value of x*/
{
    return (x>0)?x:-x;
}
int nodeheight( AVLNodePtr node)   /*return the node's height*/
{
    if(node == NULL)
        return -1;
    else
        return node->height;
}
int nodesize(AVLNodePtr node)      /*return the node's size*/
{
    if(node == NULL)
        return 0;
    else
        return node->tree_size;
}
int treeSum(AVLNodePtr node)       /*return the sum of the node*/
{
    if(node == NULL)
        return 0;
    else
        return node->tree_sum;
}
AVLNodePtr avl_search(AVLNodePtr root,int x)
{
    if(root ==  NULL)            /*base case*/
        return NULL;
    if( x == root->key )         /*if x equal to the root key*/
        return root;
    if( x >root->key )
        return avl_search(root->child[RIGHT],x );    /*if x is bigger than the root key ,then we search x in the right subtree*/
    else
        return avl_search(root->child[LEFT],x );     /*else we search in the left subtree*/
}
AVLNodePtr avl_insert(AVLNodePtr root,int x)
{
    if( root == NULL)                      /*make a new node to insert it*/
    {
        return new_avl_node(x);
    }

    else if (x < root->key)                /*if x is smaller than the root key ,then we insert x in the left subtree */
    {
        root->child[LEFT] = avl_insert( root->child[LEFT],x);
    }
    else if (x > root->key)
    {                                      /*if x is bigger than the root key ,then we insert x in the right subtree */
        root->child[RIGHT] = avl_insert(root->child[RIGHT],x);
    }
    else                                  /*in case x is in the root , no need to insert x twice*/
    {
        return root;
    }
    root->height=util_max(nodeheight(root->child[LEFT]),nodeheight(root->child[RIGHT]))+1; /*update the values in the node  */
    root->tree_size= nodesize(root->child[LEFT])+nodesize(root->child[RIGHT]) +1;
    root->tree_sum = root->key;
    if(root->child[LEFT])
        root->tree_sum += root->child[LEFT]->tree_sum;
    if(root->child[RIGHT])
        root->tree_sum += root->child[RIGHT]->tree_sum;
    root= Balance(root);      /*calling balance function to balance the tree after the insertion*/
    return root;
}
AVLNodePtr Balance(AVLNodePtr node)
{
    if(node == NULL ||( !(node->child[LEFT]) && !(node->child[RIGHT]) ))   /*base case*/
    {
        return node;
    }

    if(util_abs(nodeheight(node->child[LEFT]) - nodeheight(node->child[RIGHT]) ) <= 1 )   /*check the difference between the 2 heights*/
    {
        return node;
    }
    else if(nodeheight(node->child[LEFT]) > nodeheight(node->child[RIGHT]))
    {
        if(nodeheight(node->child[LEFT]->child[LEFT]) >= nodeheight(node->child[LEFT]->child[RIGHT]))
        {
            return Rightrotate(node);                                /*right rotate case*/

        }
        node->child[LEFT] = Leftrotate(node->child[LEFT]) ;         /*left & right rotation case */
        return Rightrotate(node);
    }
    else
    {
        if(nodeheight(node->child[RIGHT]->child[LEFT]) > nodeheight(node->child[RIGHT]->child[RIGHT]) )
        {
            node->child[RIGHT] = Rightrotate(node->child[RIGHT]);   /*right & left rotation case */
            return Leftrotate(node);
        }
        return Leftrotate(node);                                    /*left rotate*/
    }
}
AVLNodePtr Rightrotate(AVLNodePtr t)
{
    AVLNodePtr t1;
    t1=t->child[LEFT];                  /*save the left sub tree in t1 */
    t->child[LEFT] = t1->child[RIGHT];  /*update the child of t */
    t1->child[RIGHT] = t;
    t->height = util_max(nodeheight(t->child[LEFT]),nodeheight(t->child[RIGHT]))+1 ; /*update the height and the size of t*/
    t->tree_size = nodesize(t->child[LEFT])+ nodesize(t->child[RIGHT])+1;
    t->tree_sum = t->key;    /*update sum of t*/
    if(t->child[LEFT])
        t->tree_sum += t->child[LEFT]->tree_sum;
    if(t->child[RIGHT])
        t->tree_sum += t->child[RIGHT]->tree_sum;
    t1->height = util_max(nodeheight(t1->child[LEFT]),(t->height))+1;
    t1->tree_size = nodesize(t1->child[LEFT])+ nodesize(t1->child[RIGHT])+1;      /*update the height and the size of t1*/
    t1->tree_sum = t1->key;    /*update sum of t1*/
    if(t1->child[LEFT])
        t1->tree_sum += t1->child[LEFT]->tree_sum;
    if(t1->child[RIGHT])
        t1->tree_sum += t1->child[RIGHT]->tree_sum;

    return t1;
}
AVLNodePtr Leftrotate(AVLNodePtr t)
{
    AVLNodePtr t1;
    t1=t->child[RIGHT];                  /*save the right sub tree in t1 */
    t->child[RIGHT] = t1->child[LEFT];   /*update the child of t */
    t1->child[LEFT] = t;
    t->height =util_max(nodeheight(t->child[LEFT]),nodeheight(t->child[RIGHT]))+1;     /*update the height and the size of t*/
    t->tree_size = nodesize(t->child[LEFT])+ nodesize(t->child[RIGHT])+1;
    t->tree_sum = t->key;                  /*update sum of t*/
    if(t->child[LEFT])
        t->tree_sum += t->child[LEFT]->tree_sum;
    if(t->child[RIGHT])
        t->tree_sum += t->child[RIGHT]->tree_sum;
    t1->height= util_max(nodeheight(t1->child[RIGHT]),nodeheight( t->child[RIGHT]))+1; /*update the height and the size of t1*/
    t1->tree_size = nodesize(t1->child[LEFT])+ nodesize(t1->child[RIGHT])+1;
    t1->tree_sum = t1->key;                 /*update sum of t*/
    if(t1->child[LEFT])
        t1->tree_sum += t1->child[LEFT]->tree_sum;
    if(t1->child[RIGHT])
        t1->tree_sum += t1->child[RIGHT]->tree_sum;

    return t1;

}
AVLNodePtr avl_delete(AVLNodePtr root,int x)
{
    AVLNodePtr tmp;
    if(root == NULL)
        return root;
    if(x > root->key)/*the key of the node small than x */
    {
        /*the node in the right subtree*/
        root->child[RIGHT]=avl_delete(root->child[RIGHT], x );
    }
    else if(x < root->key) /*the node in the left subtree*/
    {
        root->child[LEFT]=avl_delete(root->child[LEFT], x );
    }
    else/*we found the node*/
    {
        if( (root->child[RIGHT])== NULL && (root->child[LEFT])== NULL )/*no child*/
        {
            tmp=root;
            root=NULL;
            free(tmp);
        }
        else if( !root->child[RIGHT] ||  !root->child[LEFT])   /*one child*/
        {
            tmp= root->child[RIGHT] ? root->child[RIGHT]:root->child[LEFT] ;
            *root= *tmp;
            free(tmp);
        }
        else /*two child*/
        {
            tmp=minnode(root->child[RIGHT]);   /*check the min in the right sub tree*/
            root->key = tmp->key ;
            root->child[RIGHT]=avl_delete(root->child[RIGHT], tmp->key );

        }
    }
    if(!root)
    {
        return root;
    }
    root->height = util_max(nodeheight(root->child[LEFT]),nodeheight(root->child[RIGHT]))+1;  /*change the height of the node*/
    root->tree_size= nodesize(root->child[LEFT])+nodesize(root->child[RIGHT]) +1;             /*change the size of the node*/
    root->tree_sum=treeSum(root->child[LEFT])+treeSum(root->child[RIGHT])+ (root->key);       /*change the sum of the node*/
    root= Balance(root);   /* balance the tree*/

    return root;

}
AVLNodePtr minnode(AVLNodePtr node)   /*function to return the min value in the left sub tree to help us with delete function*/
{
    if (node == NULL)
    {
        return node;
    }

    if (node->child[LEFT] == NULL)
    {

        return node;
    }
    else
    {
        return minnode(node->child[LEFT]);
    }
}
AVLNodePtr avl_merge(AVLNodePtr root1,AVLNodePtr root2)
{
    int* newArr;
    int*arr1;
    int*arr2;
    int k,len;
    AVLNodePtr newRoot;

    if(root1==NULL &&root2==NULL)    /* base case */
        return NULL;
    if(root1==NULL&&root2!=NULL)     /* base case */
        return root2;
    if(root1!=NULL&&root2==NULL)     /* base case */
        return root1;

    arr1 = (int*)malloc(root1->tree_size * sizeof(int));
    if (arr1 == NULL)
    {
        return NULL;
    }

    arr2 = (int*)malloc(root2->tree_size * sizeof(int));
    if (arr2 == NULL)
    {
        free(arr1);
        return NULL;

    }
    k = 0, len = 0;
    copy_to_array(root1, arr1, &k);     /*calling the function to copy the tree to the array*/
    k = 0;
    copy_to_array(root2, arr2, &k);     /*calling the function to copy the second tree to the array*/

    newArr = merge_two_arrays(arr1, nodesize(root1), arr2, nodesize(root2), &len);   /*merge the 2 arrays to a new one */
    newRoot = new_avl_tree(newArr, 0, len-1);       /*calling the function to make new tree   */

    free(arr1);
    free(arr2);
    free(newArr);

    return newRoot;
}
AVLNodePtr new_avl_tree(int* arr, int start, int end)
{
    int mid;
    AVLNodePtr node;
    if (start > end)
        return NULL;

    mid = (start + end) / 2;      /*starting from the middle , the middle value in the array is the root of the tree*/
    node = new_avl_node(arr[mid]);
    node->child[LEFT] = new_avl_tree(arr, start, mid-1);
    node->child[RIGHT]= new_avl_tree(arr, mid+1, end);
    if(node->child[LEFT])                             /*update the new size and the new sum*/
    {
        node->tree_size += node->child[LEFT]->tree_size;
        node->tree_sum += node->child[LEFT]->tree_sum;
    }
    if(node->child[RIGHT])                             /*update the new size and the new sum*/
    {
        node->tree_size += node->child[RIGHT]->tree_size;
        node->tree_sum += node->child[RIGHT]->tree_sum;
    }
    return node;

}
int* merge_two_arrays(int *arr1,int size1,int *arr2,int size2, int* len)  /*merge 2 arrays  */
{
    int i = 0, j = 0, k = 0;
    int* newArr=(int*)malloc((size1+size2)* sizeof(int));
    int* reAllArr = NULL;

    if (newArr == NULL)
        return NULL;

    while (i < size1 && j < size2)
    {
        if (arr1[i] < arr2[j])
        {
            newArr[k] = arr1[i];
            i++;
            k++;
        }
        else if(arr1[i] > arr2[j])
        {
            newArr[k] = arr2[j];
            j++;
            k++;
        }
        else
            j++;
    }
    while (i < size1)
    {
        if(newArr[k-1] != arr1[i])
        {
            newArr[k] = arr1[i];
            k++;
        }
        i++;
    }

    while (j < size2)
    {
        if(newArr[k-1] != arr2[j])
        {
            newArr[k] = arr2[j];
            k++;
        }
        j++;
    }

    if (k == size1 + size2)
    {
        *len = k;
        return newArr;
    }

    else                       /*if k not equal we collect new array*/
    {
        reAllArr = (int*)malloc(k * sizeof(int));

        for(i = 0; i < k; i++)
        {
            reAllArr[i] = newArr[i];
        }
        free(newArr);
        *len = k;
        return reAllArr;
    }
}
void copy_to_array(AVLNodePtr root, int *arr, int* i)
{
    if (root == NULL)
        return ;
    copy_to_array(root->child[LEFT],arr,i);   /*in order travel and copy the keys to the array*/
    arr[(*i)++]=root->key;
    copy_to_array(root->child[RIGHT],arr,i);
}
AVLNodePtr avl_LCA(AVLNodePtr root,int x,int y)
{

    if (root==NULL)                                      /*base case*/
        return NULL;

    if(((root->key)==x)||((root->key)==y))               /*base case*/
        return root;
    if((x<=(root->key))&&((root->key)<=y))               /*if the current node key between x and y so we return the node as the LCA*/
        return root;
    if(((root->key)>x)&&((root->key)>y))                 /*if the current node key is bigger than x and y so the LCA must be in the left subtree*/
        return avl_LCA(root->child[LEFT],x,y);
    else
        return avl_LCA(root->child[RIGHT],x,y);          /*else the LCA must be in the right subtree*/
}
int avl_sum(AVLNodePtr root,int x,int y)
{

    AVLNodePtr newRoot = avl_LCA(root, x, y);            /* saving the LCA of x and y in new pointer*/
    if(!newRoot)
        return 0;
    return avl_sumX(newRoot, x, y, 1) + avl_sumY(newRoot, x, y, 1) - newRoot->key; /* calling 2 helper functions and we subtract new root key once because we added it twice*/
}
int avl_sumX(AVLNodePtr newRoot, int x, int y, int summing)
{
    int sum = 0;
    if(!newRoot)
        return 0;

    if(newRoot->key == x)                                       /*if we find x there are 2 options*/
    {
        if(newRoot->child[RIGHT] && !summing)
            return x + newRoot->child[RIGHT]->tree_sum;         /*if we find x and x is a LCA and have a right child this means that the nodes in the rights is >=x and=<y so we add the sum of all the right subtree*/
        return x;                                               /*else it is enough to sum the x */
    }

    if(newRoot->key < x)
        sum += avl_sumX(newRoot->child[RIGHT], x, y, 0);        /*if x > new root key , we call the function by recursion to search in right sub tree*/
    else
    {
        sum += avl_sumX(newRoot->child[LEFT], x, y, 0);         /*else if x in the left sub tree , so we call the function  by recursion to search in left sub tree + we add the current node key*/
        if(newRoot->key <= y && newRoot->key >= x)              /* we sum the node if the key between x and y */
            sum += newRoot->key;

        if(newRoot->child[RIGHT] && !summing)                   /*check if the current node have a right sub tree and if we are not in the LCA so we add the sum of all the right subtree*/
            sum += newRoot->child[RIGHT]->tree_sum;
    }

    return sum;
}
int avl_sumY(AVLNodePtr newRoot,int x, int y, int summing)
{
    int sum = 0;
    if(!newRoot)
        return 0;

    if(newRoot->key == y)                                 /*if we find y there are 2 options*/
    {
        if(newRoot->child[RIGHT] && !summing)             /*if we find y and y is a LCA and have a right child this means that the nodes in the left is >=x and= <y so we add the sum of all the left subtree*/
            return y + newRoot->child[LEFT]->tree_sum;
        return y;                                         /*else it is enough to sum the y*/
    }

    if(newRoot->key > y)
        sum += avl_sumY(newRoot->child[LEFT], x, y, 0);   /*if y< new root key , we call the function by recursion to search in left sub tree*/
    else
    {
        sum += avl_sumY(newRoot->child[RIGHT], x, y, 0);  /*else if y in the right sub tree , so we call the function  by recursion to search in right sub tree + we add the current node key*/
        if(newRoot->key <= y && newRoot->key >= x)        /* we sum the node if the key between x and y */
            sum += newRoot->key;
        if(newRoot->child[LEFT] && !summing)
            sum += newRoot->child[LEFT]->tree_sum;        /*check if the current node have a left sub tree and if we are not in the LCA so we add the sum of all the left subtree*/
    }

    return sum;
}
AVLNodePtr new_avl_node( int x )
{

    AVLNodePtr tmp = (AVLNodePtr)malloc(sizeof(AVLNode));      /*create a new node*/
    if( tmp == NULL)
    {
        return NULL;
    }
    else                                                      /*update the node data*/
    {
        tmp->key = x ;
        tmp->child[LEFT] = NULL;
        tmp->child[RIGHT] = NULL;
        tmp->height=0;
        tmp->tree_size=1;
        tmp->tree_sum=x;
        return tmp;
    }
}
void avl_delete_all (AVLNodePtr root)   /*delete all the node by recursion*/
{
    if(root != NULL)
    {
        avl_delete_all(root->child[LEFT] );
        avl_delete_all(root->child[RIGHT] );
        free(root);
    }
}
