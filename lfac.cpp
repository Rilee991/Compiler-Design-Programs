#include<bits/stdc++.h>
using namespace std;
vector<string>le;
vector<string>rig[10];
int pro;
int detect_non(int non_ter)
{
        int i,j,k;
        string s1,s2,s3;
        for(i=0;i<non_ter;i++)
        {
                s1 = le[i];
                for(j=0;j<rig[i].size();j++)
                {
                        s2 = rig[i][j];
                        s3 = s2[0];
                        if(s1 == s3)
                                return i;
                }
        }
        return -1;
}
void removing_rec(int p,int non_ter)
{
        int i,j,k;
        string s1,s2,s3,s4;
        s1 = le[p];
        le.push_back("Z");
        for(i=0;i<rig[p].size();i++)
        {
                s2 = rig[p][i];
                s4 = s2[0];
                if(s4 == s1)
                {
                        s3 = s2.substr(1,s2.length()-1);
                        s3 += "Z";
                        rig[non_ter].push_back(s3);
                }
                else
                {
                         s3 = s2+"Z";
                         rig[non_ter+1].push_back(s3);
                }
        }
        rig[p].clear();
        for(i=0;i<rig[non_ter+1].size();i++)
        {
                rig[p].push_back(rig[non_ter+1][i]);
        }
        rig[non_ter].push_back("$");
        rig[non_ter+1].clear();
}
void print_grammar(int non_ter)
{
	for(int i=0;i<non_ter;i++)
	{
		cout<<le[i]<<" -> ";
		for(int j=0;j<rig[i].size();j++)
		{
			cout<<rig[i][j];
			if(j!=rig[i].size()-1)
				cout<<" | ";
		}
		cout<<"\n";
	}
}
void remove_left_factoring(int non_ter,int pos,string start)
{
	le.push_back("A'");
	cout<<"Removing Left Factoring...."<<start<<"\n";
	for(int i=0;i<rig[pos].size();i++)
	{
		string s1 = rig[pos][i];
		string s2;
		s2 = s1[0];
		if(s2==start)
		{
			rig[non_ter].push_back(s1.substr(1,s1.length()-1));
			rig[pos].erase(rig[pos].begin()+i);
			i--;
		}
	}
	rig[pos].push_back(start+"A'");
	print_grammar(non_ter+1);
}
void find_non_terminal(int non_ter)
{
	int ans=-1;string s1;
	for(int i=0;i<non_ter;i++)
	{
		for(int j=0;j<rig[i].size();j++)
		{	
			string s2 = rig[i][j];
			string start;
			start = s2[0];
			int num=0,val=0;
			for(int k=0;k<rig[i].size() & k!=j;k++)
			{
				string s3 = rig[i][k];
				string new1;
				new1 = s3[0];
				if(start == new1)
					num++;
			}
			if(num>val)
			{
				val = num;
				ans = i;
				s1 = start;
			}
		} 
	}
	if(ans!=-1)
	{
	cout<<"There is left factoring in non-terminal "<<left[ans]<<"\n";
	remove_left_factoring(non_ter,ans,s1);
	}
	else
	{
	cout<<"No left factoring found...\n";
	}
}
int main()
{

	int non_ter;
 	cout<<"Enter the number of non-terminals:\n";
 	cin>>non_ter;
 	string s1,s2,s3;
 	for(int i=0;i<non_ter;i++)
 	{
 		int prod;
 		cout<<"   Enter the non-terminal -"<<i+1<<" : ";
 		cin>>s1;
 		le.push_back(s1);
 		cout<<"      Enter the number of productions that "<<s1<<" give : ";
 		cin>>prod;
 		for(int j=0;j<prod;j++)
 		{
 			cout<<"         Enter the production "<<j+1<<" : ";
 			cin>>s2;
 			rig[i].push_back(s2);
 		}
 	}
 	cout<<"\n Given Grammar is: \n";
 	print_grammar(non_ter);
 	// Code for removing left recursion first
 	int k = detect_non(non_ter);
        if(k!=-1)
                {
                        cout<<"Variable "<<le[k]<<" has recursion in it.\n";
                        cout<<"Removing recursion....\n";
                        removing_rec(k,non_ter);
                        print_grammar(non_ter+1);   
                        non_ter++;                   
                        
                }
        else
                {
                        cout<<"Given language has non-recursion.\n";
                }
 	// Code for removing left factoring
 	find_non_terminal(non_ter);
 	return 0;
}
