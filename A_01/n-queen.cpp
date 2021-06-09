
#include <bits/stdc++.h>
using namespace std;


class Solution{
public:

    bool isSafe(vector<vector<int>> board, int row, int col)
    {
        int n = board[0].size();
        int i, j;
        //check if any queen in that row
        for(i=0; i<col; i++)
            if(board[row][i] == 1)
                return false;
        
        //check if any queen in left upper diagonal
        for(i=row, j=col; i>=0 && j>=0; i--, j--)
            if(board[i][j] == 1)
                return false;
                
        //check if any queen in left lower diagonal
        for(i=row, j=col; i<n && j>=0; i++, j--)
            if(board[i][j] == 1)
                return false;
            
        return true;
    }

    void getPosition(vector<vector<int>> &ans, vector<vector<int>> &board, int col)
    {
        int n = board[0].size();
        // output formatting
        if(col == n)
        {
            cout<<endl<<"------SOLUTION ABOVE!!------"<<endl;
            vector<int> result;
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    if(board[i][j] == 1)
                        result.push_back(j);    //Only pushing the queen's column values in the array
            ans.push_back(result);
            return;
        }
        
        for(int i=0; i<n; i++)
        {
            if(isSafe(board, i, col))
            {
                // place queen
                board[i][col] = 1;
                cout<<endl;
                cout<<"Chess Board: "<<endl;
                for(int i=0; i<n; i++)
                {
                    for(int j=0; j<n; j++)
                    {
                        cout<<board[i][j]<<" ";
                    }
                    cout<<endl;
                }

                // recurse
                getPosition(ans, board, col+1);

                // backtrack
                board[i][col] = 0;


                cout<<endl;
                cout<<"Backtracking..."<<endl;
                for(int i=0; i<n; i++)
                {
                    for(int j=0; j<n; j++)
                    {
                        cout<<board[i][j]<<" ";
                    }
                    cout<<endl;
                }
            }
        }
        
    }
    vector<vector<int>> nQueen(int n) {
        // code here
        vector<vector<int>> ans;
        vector<vector<int>> board(n, vector<int> (n, 0));
        
        getPosition(ans, board, 0);
        sort(ans.begin(), ans.end());
        return ans;
    }
};

// { Driver Code Starts.

int main(){
    cout<<"Enter the square root of the no. of squares: ";
    int n;
    cin>>n;
    
    Solution ob;
    vector<vector<int>> ans = ob.nQueen(n);
    cout<<endl;
    if(ans.size() == 0)
        cout<<"Solution not possible!!!!"<<"\n";
    else {
        for(int i = 0;i < ans.size();i++)
        {
            cout<<"Solution "<<i+1<<endl;
            for(int j=0; j<ans[i].size(); j++)
            {
                for(int k=0; k<n; k++)
                {
                    if(ans[i][j] == k)
                        cout<<"Q"<<" ";
                    else
                        cout<<"."<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    return 0;
}  // } Driver Code Ends


/*


PS D:\Projects\DSA\SL5_JKK> g++ nQueen.cpp
PS D:\Projects\DSA\SL5_JKK> ./a.exe       
4

Chess Board :
1 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0

Chess Board :
1 0 0 0
0 0 0 0
0 1 0 0
0 0 0 0

Backtracking...
1 0 0 0 
0 0 0 0
0 0 0 0
0 0 0 0

Chess Board :
1 0 0 0
0 0 0 0
0 0 0 0
0 1 0 0

Chess Board :
1 0 0 0
0 0 1 0 
0 0 0 0
0 1 0 0

Backtracking...
1 0 0 0
0 0 0 0
0 0 0 0
0 1 0 0

Backtracking...
1 0 0 0
0 0 0 0
0 0 0 0 
0 0 0 0

Backtracking...
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0

Chess Board :
0 0 0 0
1 0 0 0
0 0 0 0
0 0 0 0 

Chess Board :
0 0 0 0
1 0 0 0
0 0 0 0
0 1 0 0

Chess Board :
0 0 1 0
1 0 0 0
0 0 0 0
0 1 0 0

Chess Board : 
0 0 1 0
1 0 0 0
0 0 0 1
0 1 0 0

------SOLUTION ABOVE!!------

Backtracking...
0 0 1 0
1 0 0 0
0 0 0 0
0 1 0 0 

Backtracking...
0 0 0 0
1 0 0 0
0 0 0 0
0 1 0 0

Backtracking...
0 0 0 0
1 0 0 0
0 0 0 0
0 0 0 0

Backtracking...
0 0 0 0 
0 0 0 0
0 0 0 0
0 0 0 0

Chess Board :
0 0 0 0
0 0 0 0
1 0 0 0
0 0 0 0

Chess Board :
0 1 0 0
0 0 0 0
1 0 0 0
0 0 0 0 

Chess Board :
0 1 0 0
0 0 0 0
1 0 0 0
0 0 1 0

Chess Board :
0 1 0 0
0 0 0 1
1 0 0 0 
0 0 1 0

------SOLUTION ABOVE!!------

Backtracking...
0 1 0 0
0 0 0 0
1 0 0 0
0 0 1 0

Backtracking...
0 1 0 0 
0 0 0 0
1 0 0 0
0 0 0 0

Backtracking...
0 0 0 0
0 0 0 0
1 0 0 0
0 0 0 0

Backtracking...
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0 

Chess Board :
0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 0

Chess Board :
0 1 0 0
0 0 0 0
0 0 0 0
1 0 0 0

Chess Board :
0 1 0 0 
0 0 0 0
0 0 1 0
1 0 0 0

Backtracking...
0 1 0 0
0 0 0 0
0 0 0 0
1 0 0 0

Backtracking...
0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 0

Chess Board :
0 0 0 0
0 1 0 0
0 0 0 0
1 0 0 0

Backtracking...
0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 0

Backtracking...
0 0 0 0 
0 0 0 0
0 0 0 0
0 0 0 0

Solution 1
. Q . .
. . . Q
Q . . .
. . Q .

Solution 2
. . Q . 
Q . . .
. . . Q
. Q . .




*/