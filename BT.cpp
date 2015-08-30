#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include "iostream"
using namespace std;

struct node
{
    int data;
    struct node *left,*right,*random;
    bool isThreaded ;
};

struct node* newNode(int data)
{

    node* neNode = new node;
    neNode->data = data;
    neNode->left = NULL;
    neNode->right = NULL;
    neNode->isThreaded  =false;
    return neNode;
}

void inorder(node* root)
{
    if(!root) return;
    inorder(root->left);
    cout<<root->data<<"  ";
    inorder(root->right);
}


int height(node* root){
	if(!root) return 0;

	return max(height(root->left),height(root->right))+1;
}

int size(node* root){
	if(! root) return 0;
	return size(root->left)+1+size(root->right);
}

void deletetheTree(node* &root){
	if(!root) return;

	deletetheTree(root->left);
	deletetheTree(root->right);
	root = NULL;
	free(root);
}

void maximumElementInBTUtil(node* root, int *max)
{
	if(! root) return ;
	maximumElementInBTUtil(root->left,max);
	if(*max<root->data) *max= root->data;
	maximumElementInBTUtil(root->right,max);
}

int maximumElementInBT(node* root)
{
	int max = INT_MIN;
	maximumElementInBTUtil(root,&max);
	return max;
}


void printLevel(node* root,int d)
{
	if(root==NULL) return;
	if(d==1) cout<<root->data<<" ";
	printLevel(root->left,d-1);
	printLevel(root->right,d-1);
}

void levelorder(node* root)
{
	for(int d =1; d<=height(root) ;d++)
		printLevel(root,d);
}

void iterativeLevelorder(node* root)
{
	queue<node*> q;

	node* temp = root;


	while(temp)
	{
		cout<<temp->data<<" ";
		if(temp->left)
			q.push(temp->left);
		
		//if(temp->right)
			q.push(temp->right);
		temp= q.front();
		q.pop();
		
	}
}

void sumOfAllLeftLeaves(node* root,int *sum)
{
	if(!root) return;
	sumOfAllLeftLeaves(root->left,sum);
	if(root->left && root->left->left==NULL)
		*sum+=root->left->data;
	sumOfAllLeftLeaves(root->right,sum);
}

/*Given A binary Tree, how do you remove all the half nodes (which has only one child)? 
Note leaves should not be touched as they have both children as NULL.*/
node* removeHalf(node* root)
{
	if(root==NULL) return NULL;

	root->left = removeHalf(root->left);
	root->right = removeHalf(root->right);

	if((root->left && root->right) || !root->left&&!root->right){
		return root;
	}
	else if(root->left && !root->right){
		node* newN = root->left;
		free(root);
		return newN;
	}
	else if(root->right && !root->left){
		node* newN = root->right;
		free(root);
		return newN;
	}
}


bool isBTComplete(node* root)
{
	node* curr = root;
	queue<node*> q;

	while(curr){
		
		if(! curr->left && curr->right) return false;
		else
			if((curr->left && !curr->right )|| (!curr->left &&!curr->right)) break;
		if(curr->left) q.push(curr->left);
		if(curr->right) 
			q.push(curr->right);

		curr = q.front();
		q.pop();
	}

	while(!q.empty()){
		node* newcurr = q.front();
		if(newcurr->left || newcurr->right) return false;
		q.pop();
	}

	return true;
}

void cloneABTWithRandomPointers(node* root){

	if(root==NULL) return;
	cloneABTWithRandomPointers(root->left);
	cloneABTWithRandomPointers(root->right);

	node* newNod = newNode(root->data);
	//cout<<newNod->data<<endl;
	node* left,*right;
	left = root->left;
	right = root->right;
	root->left = newNod;
	//cout<<root->left->data<<endl;
	if(left)
		newNod->left = left;
	//if(right)
	//newNod->right = right->left;
	
	//cout<<newNod->data<<" ";
}

int iterativeHeight(node* root)
{
	node* curr = root;
	queue<node*> q;
	q.push(curr);
	int h=0,levelNode;
	while(!q.empty()){
		levelNode = q.size();
		h++;
		while(levelNode--){
			curr = q.front();
			q.pop();
			if(curr->left) q.push(curr->left);
			if(curr->right) q.push(curr->right);
		}
	}
	return h;
}


int vertexCover(node* root){
	if(root==NULL) return 0;

	if(root->left==NULL && root->right==NULL) return 0;

	int a= vertexCover(root->left);
	int b = vertexCover(root->right);

	int c=0;
	if(root->left) c+=(1+vertexCover(root->left->left)+vertexCover(root->left->right));
	if(root->right) c+=(1+vertexCover(root->right->right)+vertexCover(root->right->left));

	return min(a+b+1,c);
}

void getMinMaxDistance(node* root,int *min,int *max,int distance)
{
	if(!root) return;
	getMinMaxDistance(root->left,min,max,distance-1);
	getMinMaxDistance(root->right,min,max,distance+1);

	if(distance<*min) *min = distance;
	if(distance> *max) *max = distance; 
}

void btInVerticalOrderUtil(node* root,int dist,int counterNegative,list<int> *array)
{
	if(! root) return;
	
	
	//array[2].push_back(3);
	array[(dist+counterNegative)].push_back(root->data) ;
	btInVerticalOrderUtil(root->left,dist-1,counterNegative,array);
	btInVerticalOrderUtil(root->right,dist+1,counterNegative,array);
	
}

void btInVerticalOrder(node* root)
{

	int min  = INT_MAX;
	int max = INT_MIN;
	
	getMinMaxDistance(root,&min,&max,0);

	int counterNegative = -1*min;
	list<int> *array = new list<int>[100];

	btInVerticalOrderUtil(root,0,counterNegative,array);

	for(int j = min;j<=max;j++){
		cout<<"At distance "<<j<<"->";
		for(list<int>::iterator i = array[j+counterNegative].begin(); i!= array[j+counterNegative].end(); ++i){
			cout<<*i<<" ";
		}	
		cout<<endl;
	}
	
}

void topViewWithoutDSModification(node* root){

	node* curr = root;
	queue<node*> q;
	queue<int> hd;
	q.push(curr);
	hd.push(0);
	int dist;
	vector<int> visited;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		dist = hd.front();
		hd.pop();
		if (std::find(visited.begin(), visited.end(), dist) == visited.end())
		{
  			visited.push_back(dist);
			cout<<curr->data<<" ";
		}
		

		if(curr->left) {q.push(curr->left);hd.push(dist-1);}
		if(curr->right) {q.push(curr->right); hd.push(dist+1);};

	}

}

void leftViewUtil(node* root,int level,int *maximum_so_far)
{
	if(! root) return;

	if(level>*maximum_so_far){
		*maximum_so_far = level;
		cout<<root->data;
	}
	leftViewUtil(root->left,level+1,maximum_so_far);
	leftViewUtil(root->right,level+1,maximum_so_far);
}


void leftView(node* root){

	int level = 0, maximum_so_far = -1;
	node* prev= NULL;
	leftViewUtil(root,level,&maximum_so_far);	
}

void rightViewUtil(node* root,int level,int *maximum_so_far)
{
	if(! root) return;

	if(level>*maximum_so_far){
		*maximum_so_far = level;
		cout<<root->data;
	}
	rightViewUtil(root->right,level+1,maximum_so_far);
	rightViewUtil(root->left,level+1,maximum_so_far);
}


void rightView(node* root){

	int level = 1, maximum_so_far = 0;
	rightViewUtil(root,level,&maximum_so_far);	
}


void bottomView(node* root)
{

	node* curr = root;
	queue<node*> q;
	queue<int> hd;
	q.push(curr);
	hd.push(0);
	int dist;
	map<int,int> m;
	vector<int> visited;
	while(!q.empty()){
		curr = q.front();
		q.pop();
		dist = hd.front();
		hd.pop();
		m[dist]= curr->data;
		if(curr->left) {q.push(curr->left);hd.push(dist-1);}
		if(curr->right) {q.push(curr->right); hd.push(dist+1);};

	}

	for(map<int,int>::iterator it = m.begin() ; it != m.end(); it++){
		cout<<it->second<<" ";
	}
}

node *leftMost(node *root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

void inorderForThreadedBT(node *root)
{
	
}
void btToBinaryThreadedTree(node* root)
{
	if(! root) return;
	static node* prev = NULL;
	static bool b= false;
	btToBinaryThreadedTree(root->left);

	if(root->right==NULL && root->left==NULL){
		prev = root;
		b= true;
	}
	else if(b) {
		prev->right = root;
		prev->isThreaded = true;
		b=false;
	}
	btToBinaryThreadedTree(root->right);
}

void btToMirrorBT(node* root){
	if(!root) return;

	node* temp = root->left;
	root->left = root->right;
	root->right = temp;
	btToMirrorBT(root->left);
	btToMirrorBT(root->right);
}

void spiralLevelOrder(node* root){

	queue<node*> q,ans;
	stack<node*> st;
	node* temp = root;
	q.push(root);
	int h = 1;
	while(!q.empty())
	{
		int totalNodes = q.size();
		h++;
		//cout<<h<<" ";
		while(totalNodes--){
			q.pop();
			ans.push(temp);
			if(temp->left)
			q.push(temp->left);
			if(temp->right)
			q.push(temp->right);
			temp = q.front();
		}
		while(! ans.empty()){
			if(h%2){
			cout<<ans.front()->data<<" ";
			ans.pop();
			}
			else{
				st.push(ans.front());
				ans.pop();
			}	
		}

		while(!st.empty()){
			cout<<st.top()->data<<" ";
			st.pop();
		}
	}

}

bool isChildrenSumProp(node* root){
	
	if(!root) return true;
	if(! root->left && ! root->right)
		return true;

	int sum = 0;
	if(root->left) sum+=root->left->data;
	if(root->right) sum+=root->right->data;
	if(root->data!=sum) return false;

	return isChildrenSumProp(root->left) && isChildrenSumProp(root->right);
}

/*
Given an arbitrary binary tree, convert it to a binary tree that 
holds Children Sum Property. You can only increment data 
values in any node (You cannot change structure of tree and cannot decrement value of any node). 
*/
void btToChildSumTree(node* root)
{
	if(! root) return;

	if(!root->left && !root->right){
		return;
	}

	btToChildSumTree(root->left);
	btToChildSumTree(root->right);
	int sum = 0;
	if(root->left) sum += root->left->data;
	if(root->right) sum += root->right->data;
	if(sum >= root->data) root->data = sum;
	else {
		if(root->left){
			root->left->data = root->data - root->right->data;
			btToChildSumTree(root->left);
		}
		else{
			root->right->data = root->data;
			btToChildSumTree(root->right);
		}
	}
}

// Diameter of a binary tree

int diameter(node* root){

	if(root==NULL) return 0;
	if(root->left==NULL && root->right==NULL) return 1;
	int left = diameter(root->left);
	int right = diameter(root->right);

	int lheight = height(root->left);
	int rheight = height(root->right);

	return max(max(left,right),1+lheight+rheight);
}


//Optimized Version Of Diameter ...Complexity O(n)

int lheight=0;
int rheight = 0;
int dia(node* root,int* height){

	if(root==NULL) {
		*height = 0;
		return 0;
	}

	int left = dia(root->left,&lheight);
	int right = dia(root->right,&rheight);

	*height = max(lheight,rheight)+1;

	//TODO
}


//How to determine if a binary tree is height-balanced?

bool isheightBalanced(node* root,int *height)
{
	if(!root) return true;
	int lheight = 0, rheight = 0;
	bool left = isheightBalanced(root->left,&lheight);
	bool right = isheightBalanced(root->right,&rheight);

	*height = max(lheight,rheight)+1;

	return left && right && (abs(lheight-rheight)==1 || abs(lheight-rheight)==0); 
}


//Root to leaf path sum equal to a given number

bool rootToLeafEqualToSum(node* root,int sum,int curr)
{
	
	if(root==NULL) return false;
	curr+=root->data;
	if(!root->left && !root->right) {
		cout<<curr<<endl;
		if(curr == sum ) return true;
		else return false;
	}

	return rootToLeafEqualToSum(root->left,sum,curr) || rootToLeafEqualToSum(root->right,sum,curr);

	return false;
}

void treeToDoubleTree(node* root)
{
	if(root==NULL) return ;

	
		node* newN = newNode(root->data);
		node* left = root->left;
		root->left = newN;
		newN->left = left;
		treeToDoubleTree(left);
		treeToDoubleTree(root->right);
}

bool isfoldableUtil(node* root1, node* root2)
{
	if((root1 && !root2)||(root2 && !root1)) return false;
	else if(!root1 && ! root2) return true;

	return isfoldableUtil(root1->left,root2->right) && isfoldableUtil(root1->right,root2->left); 
}


bool isfoldable(node* root)
{
	return isfoldableUtil(root->left,root->right);
}

// Inorder Preorder to tree

int findIndexInInorder(int* in, int tofind, int n){

	for(int i=0;i<n;i++){
		if(in[i]==tofind) return i;
	}
}

node* inPreToTree(int* in,int* pre,int inS,int inE,int n){

	static int preIndex = 0;
	
	if(preIndex==n+1) return NULL;
	node* root = newNode(pre[preIndex++]);
	
	if(inS>=inE) return root;

	
	int index = findIndexInInorder(in,root->data,n);

	root->left = inPreToTree(in,pre,inS,index-1,n);
	root->right = inPreToTree(in,pre,index+1,inE,n);

	return root;
}

void postorder(node* root)
{
	if(!root) return;
	postorder(root->left);
	postorder(root->right);
	cout<<root->data<<"  ";
}

int main()
{
	
  node *root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->right  = newNode(4);
  root->right->left = newNode(5);
  root->right->right = newNode(6);
    //cout<<"Before Any change\n";
    ///levelorder(root);
 	//btToChildSumTree(root);
	//cout<<endl<<"After Change\n";
 	//levelorder(root);
  	//if(isfoldable(root)) cout<<"Yes\n";
  	//else cout<<"No\n";

  int in[]= {4,2,5,1,6,3};
  int pre[]={1,2,4,5,3,6};
  node* root1 = inPreToTree(in,pre,0,5,5);
  inorder(root1);
  cout<<endl;
  postorder(root1);
}