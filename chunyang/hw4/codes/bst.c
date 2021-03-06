/* CS261- Assignment 4 - Part1
 * Name: Li, Tingzhi & Zhang, Chunyang
 * Date: 5/11/2015
 * Development Environment: Xcode & MSVC
 * Solution description: Implement a binary search tree that can store any arbitrary struct in its nodes.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
 function to initialize the binary search tree.
 param tree
 pre: tree is not null
 post:		tree cnt is 0
		tree root is null
 */

void initBSTree(struct BSTree *tree)
{

	/* Write This */
	assert(tree);
	tree->root = NULL;
	tree->cnt = 0;
}

/*
 function to create a binary search tree.
 param: none
 pre: none
 post: 	
		tree != 0	
		tree->count = 0
		tree->root = 0;
 */

struct BSTree*  newBSTree()
{
	/* Write This */
	struct BSTree *newBSTree = malloc(sizeof(struct BSTree));
	assert(newBSTree);
	initBSTree(newBSTree);
	return newBSTree;  /* temporary return*/	
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	
	/* Write This */
	if (node->left == NULL)
	{
		if (node->right == NULL)
		{
			free(node->val);
			free(node);
			return;
		}
		else
		{
			_freeBST(node->right);
			node->right = NULL;
		}
	}
	else
	{
		_freeBST(node->left);
		node->left = NULL;
	}
	_freeBST(node);
   
}

/*
 function to clear the nodes of a binary search tree
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		tree->root = 0;
		tree->cnt = 0
 */
void clearBSTree(struct BSTree *tree)
{

	/* Write This */
	assert(tree != NULL);
	_freeBST(tree->root);
	tree->root = 0;
	tree->cnt = 0;
}

/*
 function to deallocate a dynamically allocated binary search tree
 param: tree   the binary search tree
 pre: tree != null;
 post: all nodes and the tree structure itself are deallocated.
 */
void deleteBSTree(struct BSTree *tree)
{

	/* Write This */
	assert(tree != NULL);
	clearBSTree(tree);
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
 function to determine if  a binary search tree is empty.

 param: tree    the binary search tree
 pre:  tree is not null
 */
int isEmptyBSTree(struct BSTree *tree) { 
	/* Write This */
	assert(tree != NULL);
	return (!tree->cnt); /* temporary return val */
}


/*
 function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) { 
	/* Write This */
	assert(tree != NULL);
	return (tree->cnt);    /* Temporary return valu */
}



/*----------------------------------------------------------------------------*/
/*
 recursive helper function to add a node to the binary search tree.
 HINT: You have to use the compare() function to compare values.
 param:  cur	the current root node
		 val	the value to be added to the binary search tree
 pre:	val is not null
 */
struct Node *_addNode(struct Node *cur, TYPE val)
{
	/*write this*/
	assert(val != NULL);
	if (cur == NULL)
	{
		struct Node *newNode = malloc(sizeof(struct Node));
		newNode->val = val;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	if (compare(cur->val, val) == 1 || compare(cur->val, val) == 0)
		cur->left = _addNode(cur->left, val);
	else    //(compare(cur->val, val) == -1)
		cur->right = _addNode(cur->right, val);
    return cur;
}

/*
 function to add a value to the binary search tree
 param: tree   the binary search tree
		val		the value to be added to the tree

 pre:	tree is not null
	val is not null
 
pose:  tree size increased by 1
	tree now contains the value, val
 */
void addBSTree(struct BSTree *tree, TYPE val)
{
    assert(tree != NULL);
    assert(val != NULL);
	tree->root = _addNode(tree->root, val);
	tree->cnt++;
}

/*
 function to determine if the binary search tree contains a particular element
 HINT: You have to use the compare() function to compare values.
 param:	tree	the binary search tree
		val		the value to search for in the tree
 pre:	tree is not null
		val is not null
 post:	none
 */

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
	/*write this*/
	assert(tree != NULL);
	assert(val != NULL);
	struct Node *temp = tree->root;
	while (temp != NULL)
	{
		if (compare(temp->val, val) == 0)
			return 1;
		else if (compare(temp->val, val) == -1)
			temp = temp->right;
		else    // (compare(temp->val, val) == 1)
			temp = temp->left;
	}
	//printf("No such value contained in this Tree!\n");
	return 0;
}

/*
 helper function to find the left most child of a node
 return the value of the left most child of cur
 param: cur		the current node
 pre:	cur is not null
 post: none
 */

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{
	/*write this*/
	assert(cur != NULL);
	struct Node *temp = cur;
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp->val;
}


/*
 recursive helper function to remove the left most child of a node
 HINT: this function returns cur if its left child is NOT NULL. Otherwise,
 it returns the right child of cur and free cur.

Note:  If you do this iteratively, the above hint does not apply.

 param: cur	the current node
 pre:	cur is not null
 post:	the left most node of cur is not in the tree
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
	/*write this*/
	assert(cur != NULL);
	if (cur->left != NULL)
	{
		cur->left = _removeLeftMost(cur->left);
	}
	else
	{
		struct Node *temp = cur;
		cur = cur->right;
		free(temp->val);
		free(temp);
	}
	return cur;
}


/*
 recursive helper function to remove a node from the tree
 HINT: You have to use the compare() function to compare values.
 param:	cur	the current node
		val	the value to be removed from the tree
 pre:	val is in the tree
		cur is not null
		val is not null
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
	/*write this*/
	assert(val != NULL);
    
	if (cur != NULL)
	{
		if (compare(cur->val, val) == 0)
		{
			cur->val = _leftMost(cur);
			cur = _removeLeftMost(cur);
		}
		else if (compare(cur->val, val) == 1)
		{
			cur->left = _removeNode(cur->left, val);
		}
		else    // (compare(cur->val, val) == -1)
		{
			cur->right = _removeNode(cur->right, val);
		}
	}
	else
		printf("The Value is not in this BSTree!\n");
	return cur;
}


/*
 function to remove a value from the binary search tree
 param: tree   the binary search tree
	val		the value to be removed from the tree
 pre:	tree is not null
	val is not null
	val is in the tree
 
pose:	tree size is reduced by 1
 */
void removeBSTree(struct BSTree *tree, TYPE val)
{

	/* Write This */
	assert(tree != NULL);
	assert(val != NULL);
	tree->root = _removeNode(tree->root, val);
	tree->cnt--;
}



/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used 
  in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	 if (cur == 0) return;
	 printf("(");
	 printNode(cur->left);	 
	 /*Call print_type which prints the value of the TYPE*/
	 print_type(cur->val);
	 printNode(cur->right);
	 printf(")");
}

void printTree(struct BSTree *tree) {
	 if (tree == 0) return;	 
	 printNode(tree->root);	 
}
/*----------------------------------------------------------------------------*/

#endif


/************************************************************************************************************************
from here to the end of this file are a set of fucntions for testing the fucntions of the BST
***************************************************************************************************************************/
/*
function to built a Binary Search Tree (BST) by adding numbers in this specific order
the graph is empty to start: 50, 13, 110 , 10

*/


struct BSTree *buildBSTTree_1() {
    /*     50
         13  110
        10 
    */
    struct BSTree *tree	= newBSTree();		
		
	/*Create value of the type of data that you want to store*/
	struct data *myData1 = (struct data *) malloc(sizeof(struct data));
	struct data *myData2 = (struct data *) malloc(sizeof(struct data));
	struct data *myData3 = (struct data *) malloc(sizeof(struct data));
	struct data *myData4 = (struct data *) malloc(sizeof(struct data));
		
	myData1->number = 50;
	myData1->name = "rooty";
	myData2->number = 13;
	myData2->name = "lefty";
	myData3->number = 110;
	myData3->name = "righty";
	myData4->number = 10;
	myData4->name = "lefty of lefty";
	
	/*add the values to BST*/
	addBSTree(tree, myData1);
	addBSTree(tree, myData2);
	addBSTree(tree, myData3);
	addBSTree(tree, myData4);
    
    return tree;
}

/*
function to print the result of a test function
param: predicate:  the result of the test 
       nameTestFunction : the name of the function that has been tested
	   message

*/
void printTestResult(int predicate, char *nameTestFunction, char *message){
	if (predicate)
	   printf("%s(): PASS %s\n",nameTestFunction, message);
    else
	   printf("%s(): FAIL %s\n",nameTestFunction, message);        
}

/*
 Function to test _addNode() function
*/

void test_addNode_1() {
    struct BSTree *tree	= newBSTree();
    struct data myData1,  myData2,  myData3,   myData4;
    
    myData1.number = 50;
    myData1.name = "rooty";
    tree->root = _addNode(tree->root, &myData1);
    //check the root node
    if (compare(tree->root->val,&myData1) != 0) {
        printf("_addNode() test: FAIL to insert 50 as root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 50 as root\n");
    
    myData2.number = 13;
    myData2.name = "lefty";
    tree->root = _addNode(tree->root, &myData2);
    
    //check the position of the second element that is added to the BST tree
    if (compare(tree->root->left->val,  &myData2) != 0) {
        printf("_addNode() test: FAIL to insert 13 as left child of root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 13 as left of root\n");
    
    
    myData3.number = 110;
    myData3.name = "righty";
    tree->root = _addNode(tree->root, &myData3);
    
    //check the position of the third element that is added to the BST tree
    if (compare(tree->root->right->val,  &myData3) != 0) {
        printf("_addNode() test: FAIL to insert 110 as right child of root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 110 as right of root\n");
    
    myData4.number = 10;
    myData4.name = "lefty of lefty";
    tree->root = _addNode(tree->root, &myData4);
    
    //check the position of the fourth element that is added to the BST tree
    if (compare(tree->root->left->left->val,  &myData4) != 0) {
        printf("_addNode() test: FAIL to insert 10 as left child of left of root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 10 as left of left of root\n");

}

/*
fucntion to test each node of the BST and their children

*/
void testAddNode_1() {
    struct BSTree *tree	= newBSTree();
    
    struct data myData1,  myData2,  myData3,   myData4;
		
	myData1.number = 50;
	myData1.name = "rooty";
    addBSTree(tree, &myData1);
    //check the root node
    if (compare(tree->root->val,&myData1) != 0) {
        printf("addBSTree() test: FAIL to insert 50 as root\n");
        return;
    }
	//check the tree->cnt value after adding a node to the tree
    else if (tree->cnt != 1) {
        printf("addBSTree() test: FAIL to increase count when inserting 50 as root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 50 as root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");

    
	myData2.number = 13;
	myData2.name = "lefty";
    addBSTree(tree, &myData2);
    
    //check the position of the second element that is added to the BST tree
    if (compare(tree->root->left->val,  &myData2) != 0) {
        printf("addBSTree() test: FAIL to insert 13 as left child of root\n");
        return;
    }
    else if (tree->cnt != 2) {
        printf("addBSTree() test: FAIL to increase count when inserting 13 as left of root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 13 as left of root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");

    
	myData3.number = 110;
	myData3.name = "righty";
    addBSTree(tree, &myData3);
        
    //check the position of the third element that is added to the BST tree    
    if (compare(tree->root->right->val,  &myData3) != 0) {
        printf("addBSTree() test: FAIL to insert 110 as right child of root\n");
        return;
    }
    else if (tree->cnt != 3) {
        printf("addBSTree() test: FAIL to increase count when inserting 110 as right of root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 110 as right of root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");

    
	myData4.number = 10;
	myData4.name = "lefty of lefty";
	addBSTree(tree, &myData4);
    
	//check the position of the fourth element that is added to the BST tree
    if (compare(tree->root->left->left->val,  &myData4) != 0) {
        printf("addBSTree() test: FAIL to insert 10 as left child of left of root\n");
        return;
    }
    else if (tree->cnt != 4) {
        printf("addBSTree() test: FAIL to increase count when inserting 10 as left of left of root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 10 as left of left of root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
}

/*
fucntion to test that the BST contains the elements that we added to it

*/
void testContainsBSTree_1() {
    struct BSTree *tree = buildBSTTree_1();
    
    struct data myData1,  myData2,  myData3,  myData4, myData5;
	
	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    myData5.number = 111;
	myData5.name = "not in tree";
    
    printTestResult(containsBSTree(tree, &myData1), "containsBSTree", "when test containing 50 as root");
        
    printTestResult(containsBSTree(tree, &myData2), "containsBSTree", "when test containing 13 as left of root");
    
	printTestResult(containsBSTree(tree, &myData3), "containsBSTree", "when test containing 110 as right of root");
        
    printTestResult(containsBSTree(tree, &myData4), "containsBSTree", "when test containing 10 as left of left of root");

     //check containsBSTree fucntion when the tree does not contain a node    
    printTestResult(!containsBSTree(tree, &myData5), "containsBSTree", "when test containing 111, which is not in the tree");
    
    deleteBSTree(tree);
}

/*
fucntion to test the left_Most_element 

*/
void testLeftMost_1() {
    struct BSTree *tree = buildBSTTree_1();
    
	struct data myData3, myData4;

	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    
	printTestResult(compare(_leftMost(tree->root), &myData4) == 0, "_leftMost", "left most of root");
    
	printTestResult(compare(_leftMost(tree->root->left), &myData4) == 0, "_leftMost", "left most of left of root");
    
	printTestResult(compare(_leftMost(tree->root->left->left), &myData4) == 0, "_leftMost", "left most of left of left of root");
    
	printTestResult(compare(_leftMost(tree->root->right), &myData3) == 0, "_leftMost", "left most of right of root");
    
    deleteBSTree(tree);

}

void testRemoveLeftMost_1() {
    struct BSTree *tree = buildBSTTree_1();
    struct Node *cur;

    cur = _removeLeftMost(tree->root);
	printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");
    
    cur = _removeLeftMost(tree->root->right);
    printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");
    
   
 	cur = _removeLeftMost(tree->root);
    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");
    
}

void testRemoveNode_1() {
    struct BSTree *tree = buildBSTTree_1();
    struct Node *cur;
    struct data myData1,  myData2,  myData3,  myData4;
		
	myData1.number = 50;
	myData1.name = "rooty";
	myData2.number = 13;
	myData2.name = "lefty";
	myData3.number = 110;
	myData3.name = "righty";
	myData4.number = 10;
	myData4.name = "lefty of lefty";
    
    _removeNode(tree->root, &myData4);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");
	        
    _removeNode(tree->root, &myData3);
	 printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");
	   
    _removeNode(tree->root, &myData2);
	printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove right of root 3st try");
        
    cur = _removeNode(tree->root, &myData1);
    printTestResult(cur == NULL, "_removeNode", "remove right of root 4st try");
    
}

void testRemoveBSTree_1() {
    struct BSTree *tree = buildBSTTree_1();
    struct data myData1,  myData2,  myData3,  myData4;
    
    myData1.number = 50;
    myData1.name = "rooty";
    myData2.number = 13;
    myData2.name = "lefty";
    myData3.number = 110;
    myData3.name = "righty";
    myData4.number = 10;
    myData4.name = "lefty of lefty";
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    removeBSTree(tree, &myData4);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "removeBSTree", "remove left of left of root 1st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    removeBSTree(tree, &myData3);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "removeBSTree", "remove right of root 2st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
	
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    removeBSTree(tree, &myData2);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "removeBSTree", "remove right of root 3st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    removeBSTree(tree, &myData1);
    printTestResult(tree->root == NULL, "removeBSTree", "remove right of root 4st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));

    printTestResult(isEmptyBSTree(tree) == 1, "isEmptyTree", "Whether the tree is empty or not");

}


/*************************************************************************************************/
/*************************************************************************************************/
/*
 function to built a Binary Search Tree (BST) by adding numbers in this specific order
 the graph is empty to start: 50, 13, 110 , 10
 
 */
struct BSTree *buildBSTTree_2() {
    struct BSTree *tree	= newBSTree();
    
    /*Create value of the type of data that you want to store*/
    struct pizza *myData1 = (struct pizza *) malloc(sizeof(struct pizza));
    struct pizza *myData2 = (struct pizza *) malloc(sizeof(struct pizza));
    struct pizza *myData3 = (struct pizza *) malloc(sizeof(struct pizza));
    struct pizza *myData4 = (struct pizza *) malloc(sizeof(struct pizza));
    
    myData1->cost = 9.99;
    myData1->numToppings = 3;
    myData1->name = "Supreme";
    myData2->cost = 5.99;
    myData2->numToppings = 2;
    myData2->name = "MeatLover";
    myData3->cost = 4.50;
    myData3->numToppings = 1;
    myData3->name = "Pepperoni";
    myData4->cost = 12.99;
    myData4->numToppings = 4;
    myData4->name = "BBQ";
    
    /*add the values to BST*/
    addBSTree(tree, myData1);
    addBSTree(tree, myData2);
    addBSTree(tree, myData3);
    addBSTree(tree, myData4);
    
    return tree;
}

/*
 Function to test _addNode() function
 */

void test_addNode_2() {
    struct BSTree *tree	= newBSTree();
    struct pizza myData1,  myData2,  myData3,   myData4;
    
    myData1.cost = 9.99;
    myData1.numToppings = 3;
    myData1.name = "Supreme";
    tree->root = _addNode(tree->root, &myData1);
    //check the root node
    if (compare(tree->root->val,&myData1) != 0) {
        printf("_addNode() test: FAIL to insert 9.99 as root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 9.99 as root\n");
    
    myData2.cost = 5.99;
    myData2.numToppings = 2;
    myData2.name = "MeatLover";
    tree->root = _addNode(tree->root, &myData2);
    
    //check the position of the second element that is added to the BST tree
    if (compare(tree->root->left->val,  &myData2) != 0) {
        printf("_addNode() test: FAIL to insert 5.99 as left child of root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 5.99 as left of root\n");
    
    myData3.cost = 4.50;
    myData3.numToppings = 1;
    myData3.name = "Pepperoni";
    tree->root = _addNode(tree->root, &myData3);
    //check the position of the third element that is added to the BST tree
    if (compare(tree->root->left->left->val,  &myData3) != 0) {
        printf("_addNode() test: FAIL to insert 4.50 as right child of root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 4.50 as right of root\n");
    
    
    myData4.cost = 12.99;
    myData4.numToppings = 4;
    myData4.name = "BBQ";
    tree->root = _addNode(tree->root, &myData4);
    
    //check the position of the fourth element that is added to the BST tree
    if (compare(tree->root->right->val,  &myData4) != 0) {
        printf("_addNode() test: FAIL to insert 12.99 as left child of left of root\n");
        return;
    }
    else printf("_addNode() test: PASS when adding 12.99 as left of left of root\n");
    
}

/*
 fucntion to test each node of the BST and their children
 
 */
void testAddNode_2() {
    struct BSTree *tree	= newBSTree();
    
    struct pizza myData1,  myData2,  myData3,   myData4;
    
    myData1.cost = 9.99;
    myData1.numToppings = 3;
    myData1.name = "Supreme";
    addBSTree(tree, &myData1);
    //check the root node
    if (compare(tree->root->val,&myData1) != 0) {
        printf("addBSTree() test: FAIL to insert 9.99 as root\n");
        return;
    }
    //check the tree->cnt value after adding a node to the tree
    else if (tree->cnt != 1) {
        printf("addBSTree() test: FAIL to increase count when inserting 9.99 as root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 9.99 as root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    myData2.cost = 5.99;
    myData2.numToppings = 2;
    myData2.name = "MeatLover";
    addBSTree(tree, &myData2);
    
    //check the position of the second element that is added to the BST tree
    if (compare(tree->root->left->val,  &myData2) != 0) {
        printf("addBSTree() test: FAIL to insert 5.99 as left child of root\n");
        return;
    }
    else if (tree->cnt != 2) {
        printf("addBSTree() test: FAIL to increase count when inserting 5.99 as left of root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 5.99 as left of root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    
    myData3.cost = 4.50;
    myData3.numToppings = 1;
    myData3.name = "Pepperoni";
    addBSTree(tree, &myData3);
    
    //check the position of the third element that is added to the BST tree
    if (compare(tree->root->left->left->val,  &myData3) != 0) {
        printf("addBSTree() test: FAIL to insert 4.50 as right child of root\n");
        return;
    }
    else if (tree->cnt != 3) {
        printf("addBSTree() test: FAIL to increase count when inserting 4.50 as right of root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 4.50 as right of root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    
    myData4.cost = 12.99;
    myData4.numToppings = 4;
    myData4.name = "BBQ";
    addBSTree(tree, &myData4);
    
    //check the position of the fourth element that is added to the BST tree
    if (compare(tree->root->right->val,  &myData4) != 0) {
        printf("addBSTree() test: FAIL to insert 12.99 as left child of left of root\n");
        return;
    }
    else if (tree->cnt != 4) {
        printf("addBSTree() test: FAIL to increase count when inserting 12.99 as left of left of root\n");
        return;
    }
    else printf("addBSTree() test: PASS when adding 12.99 as left of left of root\n");
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
}

/*
 fucntion to test that the BST contains the elements that we added to it
 
 */
void testContainsBSTree_2() {
    struct BSTree *tree = buildBSTTree_2();
    
    struct pizza myData1,  myData2,  myData3,  myData4, myData5;
    
    myData1.cost = 9.99;
    myData1.numToppings = 3;
    myData1.name = "Supreme";
    myData2.cost = 5.99;
    myData2.numToppings = 2;
    myData2.name = "MeatLover";
    myData3.cost = 4.50;
    myData3.numToppings = 1;
    myData3.name = "Pepperoni";
    myData4.cost = 12.99;
    myData4.numToppings = 4;
    myData4.name = "BBQ";
    myData5.cost = 15.99;
    myData5.numToppings = 5;
    myData5.name = "Cheese";

    printTestResult(containsBSTree(tree, &myData1), "containsBSTree", "when test containing 9.99 as root");
    
    printTestResult(containsBSTree(tree, &myData2), "containsBSTree", "when test containing 5.99 as left of root");
    
    printTestResult(containsBSTree(tree, &myData3), "containsBSTree", "when test containing 4.50 as right of root");
    
    printTestResult(containsBSTree(tree, &myData4), "containsBSTree", "when test containing 12.99 as left of left of root");
    
    //check containsBSTree fucntion when the tree does not contain a node
    printTestResult(!containsBSTree(tree, &myData5), "containsBSTree", "when test containing 15.99 which is not in the tree");
    
    deleteBSTree(tree);
}

/*
 fucntion to test the left_Most_element
 
 */
void testLeftMost_2() {
    struct BSTree *tree = buildBSTTree_2();
    
    struct pizza myData3, myData4;
    
    myData3.cost = 4.50;
    myData3.numToppings = 1;
    myData3.name = "Pepperoni";
    myData4.cost = 12.99;
    myData4.numToppings = 4;
    myData4.name = "BBQ";
    
    printTestResult(compare(_leftMost(tree->root), &myData3) == 0, "_leftMost", "left most of root");
    
    printTestResult(compare(_leftMost(tree->root->left), &myData3) == 0, "_leftMost", "left most of left of root");
    
    printTestResult(compare(_leftMost(tree->root->left->left), &myData3) == 0, "_leftMost", "left most of left of left of root");
    
    printTestResult(compare(_leftMost(tree->root->right), &myData4) == 0, "_leftMost", "left most of right of root");
    
    deleteBSTree(tree);
    
}

void testRemoveLeftMost_2() {
    struct BSTree *tree = buildBSTTree_2();
    struct Node *cur;
    
    cur = _removeLeftMost(tree->root);
    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 1st try");
    
    cur = _removeLeftMost(tree->root->right);
    printTestResult(cur == NULL, "_removeLeftMost", "removing leftmost of right of root 1st try");
    
    
    cur = _removeLeftMost(tree->root);
    printTestResult(cur == tree->root, "_removeLeftMost", "removing leftmost of root 2st try");

}

void testRemoveNode_2() {
    struct BSTree *tree = buildBSTTree_2();
    struct Node *cur;
    struct pizza myData1,  myData2,  myData3,  myData4;
    
    myData1.cost = 9.99;
    myData1.numToppings = 3;
    myData1.name = "Supreme";
    myData2.cost = 5.99;
    myData2.numToppings = 2;
    myData2.name = "MeatLover";
    myData3.cost = 4.50;
    myData3.numToppings = 1;
    myData3.name = "Pepperoni";
    myData4.cost = 12.99;
    myData4.numToppings = 4;
    myData4.name = "BBQ";
    
    _removeNode(tree->root, &myData3);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "_removeNode", "remove left of left of root 1st try");
    
    _removeNode(tree->root, &myData4);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "_removeNode", "remove right of root 2st try");
	   
    _removeNode(tree->root, &myData2);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "_removeNode", "remove left of root 3st try");
    
    cur = _removeNode(tree->root, &myData1);
    printTestResult(cur == NULL, "_removeNode", "remove right of root 4st try");
    
}

void testRemoveBSTree_2() {
    struct BSTree *tree = buildBSTTree_2();
    struct pizza myData1,  myData2,  myData3,  myData4;
    
    myData1.cost = 9.99;
    myData1.numToppings = 3;
    myData1.name = "Supreme";
    myData2.cost = 5.99;
    myData2.numToppings = 2;
    myData2.name = "MeatLover";
    myData3.cost = 4.50;
    myData3.numToppings = 1;
    myData3.name = "Pepperoni";
    myData4.cost = 12.99;
    myData4.numToppings = 4;
    myData4.name = "BBQ";
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    removeBSTree(tree, &myData3);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left->left == NULL, "removeBSTree", "remove left of left of root 1st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    removeBSTree(tree, &myData4);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->right == NULL, "removeBSTree", "remove right of root 2st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    removeBSTree(tree, &myData2);
    printTestResult(compare(tree->root->val, &myData1) == 0 && tree->root->left == 0, "removeBSTree", "remove left of root 3st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    removeBSTree(tree, &myData1);
    printTestResult(tree->root == NULL, "removeBSTree", "remove right of root 4st try");
    
    printf("Calling printTree function...\n");
    printTree(tree);
    printf("\n");
    
    printf("The size of the BSTree now is %d.\n", sizeBSTree(tree));
    
    printTestResult(isEmptyBSTree(tree) == 1, "isEmptyTree", "Whether the tree is empty or not");
    
}

/*************************************************************************************************/


void testFirstDataStructure() {
    printf("\n");
    printf("First data structure test begin...\n");
    
    test_addNode_1();
    printf("\n");
    
    testAddNode_1();
    
    printf("\n");
    testContainsBSTree_1();
    
    printf("\n");
    testLeftMost_1();
    
    printf("\n");
    testRemoveLeftMost_1();
    
    printf("\n");
    testRemoveNode_1();
    
    printf("\n");
    testRemoveBSTree_1();
    
    printf("First data structure test ended!\n\n");

}



void testSecondDataStructure() {
    printf("\n");
    printf("Testing second data structure begin...\n");

    test_addNode_2();
    printf("\n");

    testAddNode_2();

    printf("\n");
    testContainsBSTree_2();

    printf("\n");
    testLeftMost_2();

    printf("\n");
    testRemoveLeftMost_2();

    printf("\n");
    testRemoveNode_2();

    printf("\n");
    testRemoveBSTree_2();
 
    printf("Second data structure test ended!\n\n");
}

/*

Main function for testing different fucntions of the Assignment#4.

*/

int main(int argc, char *argv[]){	

	
   //After implementing your code, please uncommnet the following calls to the test functions and test your code 

    
    //testFirstDataStructure();
    
    testSecondDataStructure();
	
	return 0;


}
