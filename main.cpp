#include <fstream>
// #include <iostream>
// #include <iomanip>
#include <bits/stdc++.h>

using namespace std;

bool sortinrev(const pair<int,int> &a, const pair<int,int> &b){ 
       return (a.first > b.first); 
}

int main(int argc, char** argv){

    ifstream inFile;
    
    inFile.open(argv[1]);

    ofstream outFile (argv[2]);

    if(!inFile){
        cout << "Error" << endl;
        exit(1);
    }

    int max_slices, types_of_pizza;
    inFile >> max_slices;
    inFile >> types_of_pizza;
    // inFile >> max_slices >> types_of_pizza;
    vector<pair<int,int> > A(types_of_pizza);
    for(int i=0;i<types_of_pizza;i++){
        int a;
        inFile >> a;
        A[i].first = a;
        A[i].second = i;
    }

    sort(A.begin(),A.end(), sortinrev);

    // vector<int> result;

    // for(int i=0;i<A.size();i++){
    //     if(A[i].first <= max_slices){
    //         result.push_back(A[i].second);
    //         max_slices-=A[i].first;
    //     }
    //     // else break;
    // }

    vector<vector<bool> > dp(types_of_pizza, vector<bool>(max_slices+1, 0));
	
	dp[0][A[0].first]=1;
	for(int i=0; i<types_of_pizza; i++) dp[i][0]=1;
	
	for(int i=1; i<types_of_pizza; i++)
	{
	    for(int j=1; j<=max_slices; j++)
	    {
	        if(A[i].first<=j) dp[i][j]=dp[i-1][j] || dp[i-1][j-A[i].first];
	        else dp[i][j]=dp[i-1][j];
	    }
	}
	int max_possible;
	for(max_possible=max_slices; max_possible>=0; max_possible--)
	{
	    if(dp[types_of_pizza-1][max_possible]) 
	    {
	        break;
	    }
	    
	}
	//cout<<max_possible<<endl;
	vector<int> ans;
	int p=types_of_pizza-1;
	while(max_possible>0)
	{
	    if(dp[p-1][max_possible] && max_possible>=A[p-1].first){
	        ans.push_back(A[p-1].second);
	        max_possible-=A[p-1].first;
	        p--;
	    }
	    else if(dp[p][max_possible] && max_possible>=A[p-1].first)
	    {
	        ans.push_back(A[p].second);
	        max_possible-=A[p].first;
	        p--;
	    }
	    else p--;
	}
	

    sort(ans.begin(),ans.end());
    outFile << ans.size() << "\n";

    for(int i=0;i<ans.size();i++){
        outFile << ans[i] << " ";
    }
    // cout << endl;

    // outFile.write(ans, ans.size());

    // cout.write("output.out");
    inFile.close();
    outFile.close();
}
