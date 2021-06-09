//Problem is to minimize the Mean Retrievel Time(MRT) for a given tape.
// MRT = 1/n(Σ(i=1 to n)Σ(j=1 to i))Lj

#include<bits/stdc++.h>
using namespace std;

double OptimalStorageFunc(vector<int> &tape, int records){
    sort(tape.begin(),tape.end());
    double MRT;
    for (int i = 0; i < records; i++) {
        int sum = 0;
        for (int j = 0; j <= i; j++)
            sum += tape[j];
        MRT += sum;
    }
    return MRT/records;
}

void OptimalStoragePrint(vector<int> tape, int records){
    cout<<"===== Optimal Storage ====="<<endl;
    for(int i=0; i<records; i++){
        cout<<tape[i]<<" ";
    }
    cout<<endl<<endl;
}

int main(){
    vector<int> tape;
    int records,record_length;
    cout<<"Enter the total number of records on the tape::";
    cin>>records;
    cout<<"Enter length of each record"<<endl<<endl;
    for(int i=0; i<records; i++){
        cout<<"Enter length of record "<<i+1<<":";
        cin>>record_length;
        tape.push_back(record_length);
    }

    double MRT = OptimalStorageFunc(tape, records);
    OptimalStoragePrint(tape,records);
    cout<<"Mean Retrieval Time(MRT) = "<<MRT<<endl;

}

/*
Enter the total number of records on the tape::3
Enter length of each record

Enter length of record 1:2
Enter length of record 2:4
Enter length of record 3:5
===== Optimal Storage =====
2 4 5 

Mean Retrieval Time(MRT) = 6.33333*/