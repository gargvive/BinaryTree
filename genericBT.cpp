#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include "iostream"
using namespace std;

template <class T>
class node
{
public:
    T data;
    node<T> *left,*right,*random;
    bool isThreaded ;
};

template <typename T>
node<T>* newNode(T data)
{

    node<T>* neNode = new node<T>;
    neNode->data = data;
    neNode->left = NULL;
    neNode->right = NULL;
    neNode->isThreaded  =false;
    return neNode;
}

template <typename T>
void inorder(node<T>* root)
{
    if(!root) return;
    inorder(root->left);
    cout<<root->data<<"  ";
    inorder(root->right);
}


// Inorder Preorder to tree
template <typename T>
int findIndexInInorder(T* in, T tofind, int n){

	for(int i=0;i<n;i++){
		if(in[i]==tofind) return i;
	}
}

template <typename T>
node<T>* inPreToTree(T* in,T* pre,int inS,int inE,int n){

	static int preIndex = 0;
	
	if(preIndex==n+1) return NULL;
	node<T>* root = newNode(pre[preIndex++]);
	
	if(inS>=inE) return root;

	
	int index = findIndexInInorder(in,root->data,n);

	root->left = inPreToTree(in,pre,inS,index-1,n);
	root->right = inPreToTree(in,pre,index+1,inE,n);

	return root;
}

template <typename T>
void postorder(node<T>* root)
{
	if(!root) return;
	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<"  ";
}

template <typename T>
void preorder(node<T>* root)
{
	if(!root) return;
	cout<<root->data<<"  ";
	postorder(root->left);
	postorder(root->right);
}

// Construct Special Binary Tree from given Inorder traversal

/*Given Inorder Traversal of a Special Binary Tree in which key of every node is 
greater than keys in left and right children, construct the Binary Tree and return root.*/

template <typename T>
int findMaximum(T* in,int s,int e){
	int maxi = in[s];
	int index = s;
	for(int i=s+1;i<=e;i++){
		if(maxi<in[i]){
			maxi = in[i];
			index = i;
		}
	}
	return index;
}

template <typename T>
node<T>* SpecialBTFormation(T* in,int inS,int inE){

	if(inS>inE) return NULL;
	int maxIndex  = findMaximum(in,inS,inE);
	node<T>* root = newNode(in[maxIndex]);
	if(inS==inE) return root;
	root->left = SpecialBTFormation(in,inS,maxIndex-1);
	root->right = SpecialBTFormation(in,maxIndex+1,inE);
	return root;
}

// Construct Full Binary Tree from given preorder and postorder traversals

template <typename T>
int searchIndexInPost(T* post,int tofind,int s,int e){
	for(int i=s;i<=e;i++){
		if(post[i]==tofind) return i;	
	}

}

template <typename T>
node<T>* prePostToFullBT(T* pre,T* post,int postS,int postE,int n)
{
	static int preI = 0;
	if(preI==n+1 || postS>postE ) return NULL;
	node<T>* root = newNode(pre[preI++]);
	if(postS==postE) return root;
	int index = searchIndexInPost(post,pre[preI],postS,postE);
	root->left = prePostToFullBT(pre,post,postS,index,n);
	root->right = prePostToFullBT(pre,post,index+1,postE-1,n);

	return root;
}

int main()
{
  //char in[] = {'D', 'B', 'E', 'A', 'F', 'C'};
  //char pre[] = {'A', 'B', 'D', 'E', 'C', 'F'};
  //postorder(inPreToTree(in,pre,0,5,5));

	int pre[]={1, 2, 4, 8, 9, 5, 3, 6, 7};
	int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};
	inorder(prePostToFullBT(pre,post,0,8,8));

  int ino[] = {5, 10, 40, 30, 28};
  cout<<endl;
  node<int>* root = SpecialBTFormation(ino,0,4);
  //inorder(root);
}