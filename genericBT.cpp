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



int main()
{
  char in[] = {'D', 'B', 'E', 'A', 'F', 'C'};
  char pre[] = {'A', 'B', 'D', 'E', 'C', 'F'};
  postorder(inPreToTree(in,pre,0,5,5));
}