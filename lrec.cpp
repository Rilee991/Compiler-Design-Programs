#include<bits/stdc++.h>
using namespace std;


vector<string>s[10];
vector<string>non_ter;
int pro,non;

void print_lang()
{
        int i,j;
        for(i=0;i<non;i++)
        {
                cout<<non_ter[i]<<" -> ";
                for(j=0;j<s[i].size();j++)
                {
                        cout<<s[i][j];
                        if(j!=s[i].size()-1)
                                cout<<" | ";
                }
                cout<<"\n";
        }
}

int detect_non()
{
        int i,j,k;
        string s1,s2,s3;
        for(i=0;i<non;i++)
        {
                s1 = non_ter[i];
                for(j=0;j<s[i].size();j++)
                {
                        s2 = s[i][j];
                        s3 = s2[0];
                        if(s1 == s3)
                                return i;
                }
        }
        return -1;
}

void removing_rec(int p)
{
        int i,j,k;
        string s1,s2,s3,s4;
        s1 = non_ter[p];
        non_ter.push_back("Z");
        for(i=0;i<s[p].size();i++)
        {
                s2 = s[p][i];
                s4 = s2[0];
                if(s4 == s1)
                {
                        s3 = s2.substr(1,s2.length()-1);
                        s3 += "Z";
                        s[non].push_back(s3);
                }
                else
                {
                         s3 = s2+"Z";
                         s[non+1].push_back(s3);
                }
        }
        s[p].clear();
        for(i=0;i<s[non+1].size();i++)
        {
                s[p].push_back(s[non+1][i]);
        }
        s[non].push_back("$");
}

int main()
{
        string s1,s2;
        int i,j,k;
        cout<<"Enter the number of non-terminal symbols: ";
        cin>>non;
        for(i=0;i<non;i++)
        {
                cout<<"Enter the non-terminal "<<i<<" : ";
                cin>>s1;
                non_ter.push_back(s1);
                cout<<"Enter the number of productions for "<<s1<<" :";
                cin>>pro;
                for(j=0;j<pro;j++)
                {
                        cout<<"Enter the production "<<j+1<<" :";
                        cin>>s2;
                        s[i].push_back(s2);
                }
        }
        
        cout<<"Given Grammar is :\n";
        print_lang();
        
        k = detect_non();
        if(k!=-1)
                {
                        cout<<"Variable "<<non_ter[k]<<" has recursion in it.\n";
                        cout<<"Removing recursion....\n";
                        removing_rec(k);
                        non = non + 1;
                        print_lang();                        
                        
                }
        else
                {
                        cout<<"Given language has non-recursion.\n";
                }
        return 0;
}

