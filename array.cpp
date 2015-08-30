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




int main()
{
    string s  = "BBABCBCAB";
    lonestPalindromicSubsequence(s,s.length());
   
}
