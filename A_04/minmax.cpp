#include <bits/stdc++.h>

using namespace std;

void minMax(vector<int> v,int low, int high, int &maxNum, int &minNum){
    if(v.size() == 0){
        cout<<"No element present in vector !!"<<endl;
        return;
    }
    if(v.size() == 1){
        cout<<"Max : "<<v[0]<<" "<<"Min : "<<v[0]<<endl;
        return;
    }
    if(high<=low){
        maxNum = max(maxNum,v[low]);
        minNum = min(minNum,v[low]);
        cout<<"Max : "<<maxNum<<" "<<"Min : "<<minNum<<endl;
        return;
    }
    minMax(v, low, (((double)low + (double)high)/2), maxNum, minNum);
    minMax(v, ceil(((double)low + (double)high)/2), high, maxNum, minNum);
    return;
}

int main()
{
    vector<int>v{2,1,3,4,7};
    int low = 0, high = v.size()-1, maxNum = 0, minNum = INT_MAX;
    minMax(v,low,high,maxNum,minNum);
    return 0;
}

/*
Max : 2 Min : 2
Max : 2 Min : 1
Max : 2 Min : 1
Max : 3 Min : 1
Max : 3 Min : 1
Max : 4 Min : 1
Max : 4 Min : 1
Max : 7 Min : 1
*/