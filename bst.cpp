#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include "iostream"
using namespace std;

struct node
{
    int data;
    struct node *left,*right;
};

struct node* newNode(int data)
{
    node* neNode = new node;
    neNode->data = data;
    neNode->left = NULL;
    neNode->right = NULL;
    return neNode;
}

node* insert(node* nd, int data)
{
    if(nd==NULL) return newNode(data);

    if(nd->data>data)
        nd->left = insert(nd->left,data);
    else
        nd->right  = insert(nd->right,data);

    return nd;
}

void inorder(node* root)
{
    if(!root) return;
    inorder(root->left);
    cout<<root->data<<"  ";
    inorder(root->right);
}

struct node* search(node* root,int data)
{
    if(root->data==data || root==NULL) return root;

    if(root->data>data)
    return search(root->left,data);
    else
    return search(root->right,data);
}


void findPreSuc(node* root,node** pre, node**suc,int data)
{
    if(!root) return;

    if(root->data == data)
    {
        if(root->left)
        {
            node *temp = root->left;
            while(temp->right)
            temp = temp->right;
            *pre = temp;
        }
        if(root->right)
        {
            node* temp = root->right;
            while(temp->left)
            temp = temp->left;
            *suc = temp;
        }
        return;
    }

    if(root->data> data)
    {
        *suc = root;
        findPreSuc(root->left,pre,suc,data);
    }
    else
    {
        *pre = root;
        findPreSuc(root->right,pre,suc,data);
    }
}

bool isBSTUtil(node* root,node** prev)
{
    if(!root) return true;

    if(! isBSTUtil(root->left,prev)) return false;

    if(*prev && (*prev)->data> root->data) return false;
    *prev= root;

    return isBSTUtil(root->right,prev);
}

bool isBST(node*root)
{
   node* prev= NULL;
    return isBSTUtil(root,&prev);
}


bool isSameBSTUtil(int a[],int b[],int n,int *i1,int *i2)
{
   // int nextS = nextSmallerElement(a,n,i1);
}

bool isSameBST(int a[],int b[])
{
    int n = sizeof(a)/sizeof(int);
    int i1=0;
    int i2=0;
    return isSameBSTUtil(a,b,n,&i1,&i2);
}

void addAllGreater(node* root,int *sum)
{
    if(!root) return;
    addAllGreater(root->right,sum);
    (*sum)=(*sum)+root->data;
    root->data= *sum;
    addAllGreater(root->left,sum);
}

node* sortedArrayToBST(int arr[],int low, int high)
{

    if(low>high) return NULL;
    int mid = ((low+high)/2);
    node* root = newNode(arr[mid]);

    root->left = sortedArrayToBST(arr,low,mid-1);
    root->right = sortedArrayToBST(arr,mid+1,high);
    return root;
}

node* lca(node* root,int n1,int n2)
{
    if(root->data== n1 || root->data==n2 || (root->data>n1 && root->data<n2) )
        return root;

    if(root->data<n1 && root->data<n2)
        return lca(root->right,n1,n2);
    if(root->data>n1 && root->data>n2)
        return lca(root->left,n1,n2);
}

void findKthSmallestUtil(node* root,int k,int *counter,int *result)
{
    if(! root) return;
    findKthSmallestUtil(root->left,k,counter,result);
    (*counter)+=1;
    if(*counter ==k) *result = root->data;
    findKthSmallestUtil(root->right,k,counter,result);
}

int findKthSmallest(node* root,int k)
{
    int counter = 0,result;
    findKthSmallestUtil(root,k,&counter,&result);
    return result;
}

void printList(node *node)
{
    while (node!=NULL)
    {
        cout << node->data << " ";
        node = node->right;
    }
}


void balancedBSTToDLL(node* root,node** head)
{
    static node* prev = NULL;
    if(! root) return;
    balancedBSTToDLL(root->left,head);
    if(prev==NULL)
    {
        *head = root;
        prev = root;
    }
    else
    {
        prev->right = root;
        root->left = prev;
        prev = root;
    }

    balancedBSTToDLL(root->right,head);
}

bool isPairWithGivenSum(node* head,node* tail,int sum,int *data1,int *data2)
{

    while(head!=tail)
    {
         int curr = head->data+tail->data;
        if(curr==sum)
    {
        *data1 = head->data;
        *data2 = tail->data;
        return true;
    }
    else
        if(curr>sum)
        {
            tail = tail->left;
        }
        else
            head = head->right;
    }
    return false;

}

bool isTriplet(node* root)
{

    node *head = NULL;
    balancedBSTToDLL(root, &head);
    printList(head);
    node* curr = head;
    node* tail = curr;
    while(curr->right)
    {
        tail = curr->right;
        curr = curr->right;
    }
    curr = head;
    int data1,data2;
    while(curr->right!=tail && curr->data<0)
    {
        if(isPairWithGivenSum(curr,tail,-1*(curr->data),&data1,&data2))
        {
            cout<<(curr->data)<<" "<<data1<<" "<<data2<<endl;
            return true;
        }
        else
            curr = curr->right;
    }
    return false;
}

void iterativeinorder(node* root)
{
    node* curr = root;

    stack<node*> st;

    bool done;

    while(!done)
    {
        while(curr)
        {
            st.push(curr);
            curr = curr->left;
        }

        if(! st.empty())
        {
            node* elem = st.top();
            cout<<elem->data<<" ";
            st.pop();
            curr = elem->right;
        }
        else
            done = true;
    }


}


void iterativeInorder(node* root)
{
    stack<node*> st;

    node* curr=  root;


    while(curr)
       {
        st.push(curr);
        curr = curr->left;

        }
    while(! (curr==NULL && st.empty()))
    {
        if(curr==NULL && ! st.empty())
        {
            node* elem = st.top();
            cout<<elem->data<<" ";
            st.pop();
            curr = elem->right;
            if(curr) {
                st.push(curr);
                while(curr)
                    curr = curr->left;
        }
    }
    }

}

void mergeTwoBST(node* root1,node* root2)
{

    stack<node*> st1,st2;

    node* curr1=  root1;
    node* curr2=  root2;

    while(curr1)
       {
        st1.push(curr1);
        curr1 = curr1->left;
        }
    while(curr2)
       {
        st2.push(curr2);
        curr2 = curr2->left;

        }

}

void swap(int *a,int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


void correctBSTUtil(node* root,node* prev,node** node1,node** node2,node** node3)
{
    if(! root ) return ;

    correctBSTUtil(root->left,prev,node1,node2,node3);
    if(prev==NULL) prev= root;
    else
    {
        if(prev->data> root->data)
        {
            if(*node1==NULL && *node2 ==NULL)
            {
                *node1 = prev;
                *node2 = root;
                cout<<prev->data<<" "<<root->data<<endl;
            }
            else
            {
                *node3 = root;
            }
        }
        prev = root;
    }

    correctBSTUtil(root->right,prev,node1,node2,node3);
}

void correctBST(node* root)
{
    node* n1,*n2,*n3,*prev;
    n1=n2=n3=prev = NULL;
    correctBSTUtil(root,prev,&n1,&n2,&n3);
    if(n3)
    {
        swap(n1->data,n3->data);
    }
    else
    {
        swap(n1->data,n2->data);
    }
}

int ceil(node* root, int data)
{
    if(! root) return -1;

    if(root->data==data) return root->data;

    if(root->data<data) return ceil(root->right,data);


        int cl = ceil(root->left,data);
        if(cl>=data) return cl;
        else return root->data;

}


int floor(node* root,int data)
{
    if(! root ) return -1;

    while(root)
    {
        if(root->data==data) return root->data;

       if(root->data>data) return floor(root->left,data);

       int fl = floor(root->right,data);

       if(fl<=data && fl!=-1) return fl;
       else
           return root->data;}

}

bool pairWithGivenSumWithoutModificationTree(node* root1,int sum)
{
    node* curr1 = root1;
    node* curr2 = root1;

    stack<node*> st1,st2;

    bool done1,done2;
    int value1,value2;
    while(1){
    while(!done1)
    {
        while(curr1)
        {
            st1.push(curr1);
            curr1 = curr1->left;
        }

        if(! st1.empty())
        {
            node* elem = st1.top();
            value1 = elem->data;
            st1.pop();
            curr1 = elem->right;
            done1= true;
        }
        else
            done1 = true;
    }
    
    while(!done2)
    {
        while(curr2)
        {
            st2.push(curr2);
            curr2 = curr2->right;
        }

        if(! st2.empty())
        {
            node* elem = st2.top();
            value2 = elem->data;
            st2.pop();
            curr2 = elem->left;
            done2= true;
        }
        else
            done2 = true;
    }
    
    if(value1!=value2 && value2+value1==sum) return true;
    else 
        if(value2+value1>sum) done2 = false;
        else done1 = false;

    if(value1>=value2) return false;}
}

int nextFirstBiggerElement(int *a,int low,int high,int value)
{
    for(int i=low;i<=high;i++)
        if(a[i]>value) return i;
}

node* BSTFromPreOrderUtil(int a[],int low,int high,int n)
{
    if(low==high) return newNode(a[low]);
    if(low>high) return NULL;
    node* root = newNode(a[low]);

    int index = nextFirstBiggerElement(a,low,high,a[low]);
    root->left = BSTFromPreOrderUtil(a,low+1,index-1,n);
    root->right = BSTFromPreOrderUtil(a,index,high,n);

    return root;
}

node* BSTFromPreOrder(int a[],int n)
{
    int low = 0;
    int high = n-1;
    node* root = BSTFromPreOrderUtil(a,low,high,n);
    return root;   
}

int main()
{
   /*node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    node *root1 = NULL;
    root1 = insert(root1, 50);
    insert(root1, 30);
    insert(root1, 20);
    insert(root1, 40);
    insert(root1, 70);
    insert(root1, 60);
    insert(root1, 80);*/

    int pre[] = {10, 5, 1,6,4, 7, 40, 34,50};
    int size = sizeof( pre ) / sizeof( pre[0] );
 
    struct node *root2 = BSTFromPreOrder(pre, size);
 
    printf("Inorder traversal of the constructed tree: \n");
    inorder(root2);

    //iterativeinorder(root);

}
