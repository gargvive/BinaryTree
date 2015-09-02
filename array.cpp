#include<stdio.h>
#include<stdlib.h>
#include "iostream"
#include<bits/stdc++.h>
using namespace std;
#define R 4
#define C  4

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int l, int h)
{
    int x = arr[h];    // pivot
    int i = (l - 1);  // Index of smaller element

    for (int j = l; j <= h- 1; j++)
    {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= x)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);  // Swap current element with index
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void matrixRotByOneElement(int matrix[][C],int m,int n)
{
   int row = 0;
   int col = 0;

   while(row<m && col <n ){

    if(row==m-1 && col ==n-1)
        break;

    int prev = matrix[row+1][col];
   
   for(int j= col; j<n; j++){
    int curr = matrix[row][j];
    matrix[row][j] = prev;
    prev = curr;
   }

   for(int i= row+1; i<m ; i++){
    int curr = matrix[i][n-1];
    matrix[i][n-1] = prev;
    prev = curr;
   }

   for(int j =n-2; j>=col; j--){
    int curr = matrix[m-1][j];
    matrix[m-1][j] = prev;
    prev = curr;
   }

   for(int i= m-2; i>=row ; i--){
    int curr = matrix[i][col];
    matrix[i][col] = prev;
    prev = curr;
   }

   row++;
   col++;
   n--;
   m--; 
   }
   
   

}

void matrixByNinety(int matrix[][C],int m, int n)
{
    for(int i=0;i<m-1;i++)
        matrixRotByOneElement(matrix,m,n);

    for (int i=0; i<R; i++)
    {
        for (int j=0; j<C; j++)
          cout << matrix[i][j] << " ";
        cout << endl;
    }
    
}

void spiralPrintMatrix(int matrix[][C],int n,int m)
{
    int row = 0;
   int col = 0;

   while(row<m && col <n ){

    if(row==m-1 && col ==n-1)
        break;

    
   
   for(int j= col; j<n; j++){
    cout<<matrix[row][j]<<" ";
   }

   for(int i= row+1; i<m ; i++){
    cout<<matrix[i][n-1]<<" ";
   }

   for(int j =n-2; j>=col; j--){
    cout<<matrix[m-1][j]<<" ";
   }

   for(int i= m-2; i>=row ; i--){
    cout<<matrix[i][col]<<" ";
   }

   row++;
   col++;
   n--;
   m--; 
   }
}
/*
bool compare(int[2] *a,int [2] *b)
{
    return ((*a)[1]<(*b)[1]);
}
*/

class freq
{
public:
  int data;
  int count;
};


class array
{
public:
  int data;
  int index;
};

inline bool operator<(const freq& a, const freq& b)
{
  return a.count <= b.count;
}


inline bool operator<(const array& a, const array& b)
{

  return a.data < b.data;
}


void sortElementsByfrequency(int a[],int n)
{
  array ar[n];
  for(int i=0;i<n;i++){
    ar[i].data = a[i];
    ar[i].index =i;
  }
  sort(ar,ar+n);

  freq f[n];
  int fIndex = 0;
  for(int i=0;i<n;i++){
    
    if(i>0)
    {
      if(ar[i].data==ar[i-1].data) f[fIndex].count++;
      else {
        f[++fIndex].data = ar[i].index;
        f[fIndex].count = 1;
      }
    }
    else{
      f[fIndex].data = ar[i].index;
      f[fIndex].count = 1;;
    }
  }

  sort(f,f+n);

  for(int i=0;i<=fIndex;i++)
    cout<<f[i].data<<" "<<f[i].count<<endl;

}


int findMaximumIncDec(int a[],int low,int high)
{
  int mid = (low+high)/2;

  if(low==high) return low;

  if(high-low==1){
    if(a[high]>= a[low]) return high;
    else return low; 
  }
  
  if(a[mid]> a[mid-1] && a[mid] > a[mid+1]) return mid;

  if(a[mid]> a[mid-1] && a[mid]< a[mid+1]) 
    return findMaximumIncDec(a,mid+1,high);
  else
    return findMaximumIncDec(a,low,mid-1);

} 

// (Longest Bitonic Subsequence)

/*
Given an array arr[0 … n-1] containing n positive integers, a subsequence of arr[] is called Bitonic if it is first increasing,
 then decreasing. Write a function that takes an array as argument and returns the length of the longest bitonic subsequence.
*/

int longestBitonic(int a[],int n)
{
  int dpLtoR[n+1];
  int dpRtoL[n+1];

  dpLtoR[0] = 1;
  for(int i=1;i<n;i++){
    dpLtoR[i]=0;
    for(int j=0; j<i;j++){
      if(a[j]<a[i]) dpLtoR[i] = max(dpLtoR[i],dpLtoR[j]);
    }
    dpLtoR[i]++;
  }

  dpRtoL[0] = 1;
  for(int i=n-1;i>=0;i--){
    dpRtoL[i]=0;
    for(int j=n-1; j>i;j--){
      if(a[j]<a[i]) dpRtoL[i] = max(dpRtoL[i],dpRtoL[j]);
    }
    dpRtoL[i]++;
  }

  int maxi = 0;
  for(int i=0;i<n;i++)
    maxi = max(maxi,dpLtoR[i]+dpRtoL[i]-1);

  return maxi;

}

// Dynamic Programming | Set 12 (Longest Palindromic Subsequence)


void lonestPalindromicSubsequence(string str, int len){

  int L[len][len];

  for(int i=0;i<len;i++)
    L[i][i] =1;

  for(int i=0;i<len;i++)
    for(int j=0;j<len;j++)
      {
        if(i>j) L[i][j] = 0;
        else
        if(str[i]==str[j] && j-i==1) L[i][j]=2; // if length is 2 and start =end 
        else if(str[i]!=str[j] && j-i==1) L[i][j]=0;
      }



  for(int i=len-1;i>=0;i--){
    for(int j=len-1;j>i;j--){
      if(str[i]==str[j]){
        L[i][j] = L[i+1][j-1] + 2;
        cout<<i<<" "<<j<<" "<<L[i][j]<<" Equal"<<endl;
      }
      else{
        L[i][j] = min(L[i+1][j],L[i][j-1]);
        cout<<i<<" "<<j<<" "<<L[i][j]<<endl;
    }
      }
  }

  cout<<L[0][len-1];
}


// Online algorithm for checking palindrome in a stream

int hash(string s){
  int q = 17;
  int ans = 0;
  for(int i=0;i<s.length();i++)
    ans = (ans+s[i])%q;
  return ans;
}

void checkingPalindromeInStream(string s){
  
    int n = s.length();
  
    cout<<s[0]<<" Yes\n";
    if(n==1){
      return;
    } 
    string reverse[n];
    reverse[0] = s[0];
  
    for(int i=1;i<n;i++){

      reverse[i] = s[i]+reverse[i-1];
      //cout<<reverse[i];
      if(i%2!=0){
        if(hash(reverse[i/2])==hash(s.substr(i/2+1,i/2+1))){
          for(int j=0;j<=i/2;j++){
            if(reverse[i/2][j]!=s[i/2+1+j]) {
              cout<<s.substr(0,i+1)<<" No\n";
              break;
            }
            else{
              if(j==i/2) cout<<s.substr(0,i+1)<<" Yes\n";
            } 
          }
        }
        else   cout<<s.substr(0,i+1)<<" No\n";
      }
      else{
       if(hash(reverse[i/2-1])==hash(s.substr(i/2+1,i/2))){
          for(int j=0;j<i/2;j++){
            if(reverse[i/2-1][j]!=s[i/2+1+j]) {
              cout<<s.substr(0,i+1)<<" No\n";
              break;
            }
            else{
              if(j==i/2-1) cout<<s.substr(0,i+1)<<" Yes\n";
            } 
          }
        }
        else  cout<<s.substr(0,i+1)<<" No\n";
      }
      
    }

}


//Maximum profit by buying and selling a share at most twice

int getMaxMinDifference(int *arr,int start,int end){

  int min_so_far = arr[start];
  int max_diff_so_far = INT_MIN;
  for(int i=start+1;i<=end;i++){
    if(min_so_far>arr[i]) min_so_far =  arr[i];

    if(arr[i]-min_so_far>max_diff_so_far) 
      max_diff_so_far = arr[i]-min_so_far;

  }

  return max_diff_so_far;
}

int maxProfit(int* arr,int n){

  int profit = 0 ; 
  for(int i=1;i<n-2;i++){

    int a = getMaxMinDifference(arr,0,i);
    int b = getMaxMinDifference(arr,i+1,n-1);

    if(a<0) a=0;
    if(b<0) b=0;

    profit = max(profit,a+b);
  }
  return profit;
}

// Maximum Path Sum in Two Arrays
//O(m+n)
//return size of intersection array
int intersectionOfTwoArrays(int *a1,int *a2,int n1,int n2,int *intersection)
{
  int i=0,j=0;
  int counter = 0;

  while(i< n1 && j<n2 ){
   // cout<<i<<" "<<j<<endl;
    if(a1[i]<a2[j]) i++;
    else 
      if(a1[i]>a2[j]) j++;
      else{
         intersection[counter++] = a1[i];
        i++;
        j++;
      }
  }
  return counter;
}


int maxPathSum(int *a1,int *a2,int n1,int n2){

  int intersection[100];
   int n = intersectionOfTwoArrays(a1,a2,n1,n2,intersection);
 //  for(int i=0;i<n;i++)
  //  cout<<intersection[i]<<endl;
   // Add Ending dummy variable
   intersection[n++] = 0;


   int counter = 0;
   int sum1[100];
   int sum2[100];
   int sum=0;
   for(int i=0;i<n1;i++){

    if(a1[i]==intersection[counter] ){
      sum1[counter] = sum;
      counter++;
      sum = 0;
    }
    else if(i==n1-1){
      sum1[counter] = sum+a1[i];
      counter++;
      sum = 0;
    }
    else{
      sum+=a1[i];
    }
   }

   //for(int i=0;i<counter;i++)
   // cout<<intersection[i]<<" "<<sum1[i]<<endl;

   counter = 0;
   sum = 0;
   for(int i=0;i<n2;i++){

    if(a2[i]==intersection[counter] ){
      sum2[counter] = sum;
      counter++;
      sum = 0;
    }
    else if(i==n2-1){
      sum2[counter] = sum+a2[i];
      counter++;
      sum = 0;
    }
    else{
      sum+=a2[i];
    }
   }

   // for(int i=0;i<counter;i++)
   // cout<<intersection[i]<<" "<<sum2[i]<<endl;

   int maxpathsum = 0;
   for(int i=0;i<counter;i++)
    {
      maxpathsum+=(max(sum1[i],sum2[i])+intersection[i]);
    }

    return maxpathsum;
}

// Sort an array according to the order defined by another array
// Size of both may be different

int order[100]={2,1,8,3,4};
int size_orderArray;

int searchInOrderArray(int key){

  for(int i=0;i<size_orderArray;i++)
    if(order[i]==key) return i;

  return -1;
}

int comparator(const void* a, const void *b){

  int index1 = searchInOrderArray(*(const int*)a);
  int index2 = searchInOrderArray(*(const int*)b);
  //cout<<index1<<" "<<index2<<endl;
  if(index1!=-1 && index2!=-1)
    return index1-index2;

  if(index1!=-1 && index2==-1)
    return -1;

  if(index2!=-1 && index1==-1)
    return 1;

  return *(const int*)a-*(const int*)b;

}


void sortArrayByAnotherArray(int *arr,int n1){

  qsort((void*) arr,n1,sizeof(int),comparator);
}


// Given a sequence of words, print all anagrams together 

int comparatorForAnagram(const void* a,const void *b)
{
  string s1 = *(const string*)a;
  string s2 = *(const string*)b;
  

  sort(s1.begin(),s1.end());
  sort(s2.begin(),s2.end());
  

  if(s1==s2)
    return 0;
  else
    if(s1.compare(s2)>0)
      return 1;
    else
      return -1; 
}

void sortAccordingToAnagram(string *words,int n)
{
  qsort((void*)words,n,sizeof(string),comparatorForAnagram);

  for(int i=0;i<n;i++)
    cout<<words[i]<<" ";
}


// Finding subarray with given sum

void subarrayWithGivenSum(int *a,int n,int givenSum)
{
  int prev=0;
  //int curr = 0;
  int sum = 0;
  for(int curr=0;curr<n;curr++)
  {
    sum+=a[curr];
    //cout<<sum<<" ";
    if(sum>givenSum){
      while(prev!=curr){
        sum-=a[prev];
        prev++;
        if(sum==givenSum) break;
        //cout<<sum<<" ";
      }
      if(sum==givenSum){
        cout<<prev<<" "<<curr<<endl;
        return;
        break;
      }
      else sum = a[prev];
    }
    else
      if(sum==givenSum){
        cout<<prev<<" "<<curr<<endl;
        return;
        break;
      }

  }
  cout<<"No subarray Found\n";
  return;
}


// Smallest SubArray With Sum Greater Than Given Value

int smallestSubArraySize(int *a,int n,int givenSum)
{
  int prev=0;
  //int curr = 0;
  int sum = 0;
  int min_length = n+1;
  for(int curr=0;curr<n;curr++)
  {
    sum+=a[curr];
    //cout<<sum<<" ";
    if(sum>givenSum){
      min_length = min(min_length,curr-prev+1);
      while(prev!=curr){
        sum-=a[prev];
        prev++;
        if(sum<=givenSum) break;
        else min_length = min(min_length,curr-prev+1); 
        //cout<<sum<<" ";
      }
    }
  }
  return min_length;
}


// Print all possible combinations of r elements in a given array of size n

void printallPossibleRCombinationUtil(int* arr,int low,int high, int r,int *data,int index){

  if(index==r){
    for(int j=0;j<r;j++)
      cout<<data[j];
    cout<<endl;
    return;
  }
  int i;
  for(i=low;  i<=high && high-i+1 >= r-index;i++){
    //while (arr[i] == arr[i+1])
      //       i++; 
    data[index] = arr[i];
    //cout<<low<<" "<<data[index]<<endl;

    printallPossibleRCombinationUtil(arr,i+1,high,r,data,index+1);
  }

}

void printallPossibleRCombinationUtil2(int* arr,int low,int high, int r,int *data,int index){

  if(index==r){
    for(int j=0;j<r;j++)
      cout<<data[j];
    cout<<endl;
    return;
  }

  if(low>high) return ;

  data[index] = arr[low];
  printallPossibleRCombinationUtil2(arr,low+1,high,r,data,index+1);

  printallPossibleRCombinationUtil2(arr,low+1,high,r,data,index);

}
void  printallPossibleRCombination(int *arr,int n,int r){
    int data[100];
    printallPossibleRCombinationUtil2(arr,0,n-1,r,data,0);
}


// Find a peak element

int findingPeak(int *arr,int low,int high)
{
  int mid = (low+high)/2;

  if((mid==0 && arr[mid]>arr[mid+1]) || (mid>0 && arr[mid]>arr[mid-1] && arr[mid]> arr[mid+1]) )
    return mid;

 if(arr[mid]<arr[mid+1])
        return findingPeak(arr,mid+1,high);
  else 
      return findingPeak(arr,low,mid-1);
}

// QSort Partition Method

int partition(int arr[], int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}
int main()
{
    int arr[] = {101,100,90,10};
    int r = 3;
    int n = sizeof(arr)/sizeof(arr[0]);
    string ans;
    cout<<arr[findingPeak(arr,0,n-1)];
    //string words[] = {"cat", "dog", "tac", "god", "act" };
   // sortAccordingToAnagram(words,5);
    //cout<<sizeof(int)<<" "<<sizeof(string);  

    /*int ar1[]  = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8, 7, 5, 6, 9, 7, 5};
   
    int m = sizeof(ar1)/sizeof(ar1[0]);
    size_orderArray = 5;
    sortArrayByAnotherArray(ar1,m);
    for(int i=0;i<m;i++)
      cout<<ar1[i]<<" ";*/

    // int arr[] = {9,8,7,6,5};
    // cout<<maxProfit(arr,5);
    //string s  = "aabaacaabaa";
    //checkingPalindromeInStream(s);
    //lonestPalindromicSubsequence(s,s.length());
   
}
