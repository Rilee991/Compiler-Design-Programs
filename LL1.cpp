#include<bits/stdc++.h>

using namespace std;

struct prod
{
	string l;
	string r[10];
	int n;
};

struct prod p[10];
set<char> s[10],f[10];
int k,m;

void findFollow(char c,int i)
{
	int j,a,b;
	for(j=0;j<k;j++)
		for(a=0;a<=p[j].n;a++)
		{
			for(b=0;b<p[j].r[a].length();b++)
			{
				if(p[j].r[a][b]==c)
				{
					start2:
					if(b<p[j].r[a].length()-1 && (p[j].r[a][b+1]<65 || p[j].r[a][b+1]>90))
					{
						f[m].insert(p[j].r[a][b+1]);
					}
					else if(b<p[j].r[a].length()-1 && (p[j].r[a][b+1]>=65 && p[j].r[a][b+1]<=90))
					{
						int t=0;
						for(t=0;t<k;t++)
						{
							if(p[t].l[0]==p[j].r[a][b+1])
							{
								set<char> :: iterator it;
								for(it=s[t].begin();it!=s[t].end();it++)
								{
									if(*it!='e')
										f[m].insert(*it);
									else
									{
										b++;
										goto start2;
									}
								}
								break;
							}
						}
					}
					else if(b==p[j].r[a].length()-1)
					{
						int t=0;
						for(t=0;t<k;t++)
						{
							if(p[t].l[0]==p[j].l[0])
							{
								set<char> :: iterator it;
								for(it=f[t].begin();it!=f[t].end();it++)
								{
									if(*it!='e')
										f[m].insert(*it);
								}
								break;
							}
						} 
					}
				}
			}
		}
}

int findFirst(char c,int i)
{
	int j=0,t;
	for(j=0;j<=p[i].n;j++)
	{
		int z=0;
		start:
		if(isupper(p[i].r[j][z]))
		{
			
			for(t=0;t<k;t++)
			if(p[t].l[0]==p[i].r[j][z])
			{
				if(findFirst(p[t].l[0],t)==1)
				{
					z++;
					goto start;
				}
			}
		}
		else if(p[i].r[j][z]!='e' && (p[i].r[j][z]<65 || p[i].r[j][z]>90))
			s[m].insert(p[i].r[j][0]);
		else if(p[i].r[j][z]=='e')
		{
			s[m].insert('e');
			return 1;
		}
	}
	return 0;
}

int main()
{
	cout<<"Enter the productions \n";
	int	i=1,j=0;
	string str;
	k=0;
	while(i==1)
	{
		cout<<"Enter the non-terminal of production \n";
		
		cin>>str;
		if(k>0 && p[k-1].l==str)
		{
			p[k-1].n+=1;
			k--;
		}
		else
		{
			p[k].l=str;
			p[k].n=0;
		}
		cout<<"Enter the RHS of production \n";
		cin>>str;
		p[k].r[p[k].n]=str;
		k++;
		cout<<"Do you want to give new production: y/n \n";
		cin>>str;
		if(str=="y")
		{
			i=1;
		}
		else break;
		
	}
	
	cout<<"The grammar is \n";
	for(i=0;i<k;i++)
	{
		for(j=0;j<=p[i].n;j++)
		{
			cout<<p[i].l<<" -> "<<p[i].r[j]<<"\n";
		}
	}
	cout<<"\n The first for variables is \n";
	for(i=0;i<k;i++)
	{
		
		m=i;
		findFirst(p[i].l[0],i);
		
	}
	set<char> :: iterator it;
	for(i=0;i<k;i++)
	{
		cout<<"\n";
		cout<<p[i].l[0]<<" -> ";
		cout<<"{ ";
		for(it=s[i].begin();it!=s[i].end();it++)
			cout<<*it<<" , ";
		cout<<" } \n";
	}
	
	cout<<"\n The follow for variables is \n";
	f[0].insert('$');
	for(i=0;i<k;i++)
	{
		m=i;
		findFollow(p[i].l[0],i);
	}
	for(i=0;i<k;i++)
	{
		cout<<"\n";
		cout<<p[i].l[0]<<" -> ";
		cout<<"{ ";
		for(it=f[i].begin();it!=f[i].end();it++)
			cout<<*it<<" , ";
		cout<<" } \n";
	}
	
	
	//Code for Parsing Table
	
	map<char,int> mp1,mp2;
	for(i=0;i<k;i++)
	{
		mp1[p[i].l[0]]=i;
	}
	int terminals=0,a,b;
	for(i=0;i<k;i++)
	{
		for(j=0;j<=p[i].n;j++)
		{
			for(a=0;a<p[i].r[j].length();a++)
			{
				//cout<<"char is "<<p[i].r[j][a]<<endl;
				if(p[i].r[j][a]!='e' && (p[i].r[j][a]<65 || p[i].r[j][a]>90))
				{
					
					if(mp2.find(p[i].r[j][a])==mp2.end())
					{
						mp2[p[i].r[j][a]]=terminals;
						terminals++;
					}
				}
			}
		}
	}
	mp2['$']=terminals;
	terminals++;
	
	map<char,int> :: iterator it1,it2;
//	for(it1=mp1.begin();it1!=mp1.end();it1++)
//	{
//		cout<<it1->first<<" "<<it1->second<<endl;
//	}
//	for(it2=mp2.begin();it2!=mp2.end();it2++)
//	{
//		cout<<it2->first<<" "<<it2->second<<endl;
//	}

cout<<" \n\nParsing Table \n\n";

	string table[k][terminals];
	for(i=0;i<k;i++)
		for(j=0;j<terminals;j++)
			table[i][j]="";
	for(i=0;i<k;i++)
	{
		for(j=0;j<=p[i].n;j++)
		{
			int temp;
			char ch=p[i].r[j][0];
			if(ch>=65 && ch<=90)
			{
				temp=mp1[ch];
				for(it=s[temp].begin();it!=s[temp].end();it++)
				{
					table[i][mp2[*it]]=p[i].r[j];
				}
			}
			else if(ch=='e')
			{
				temp=mp1[p[i].l[0]];
				for(it=f[temp].begin();it!=f[temp].end();it++)
				{
					table[i][mp2[*it]]=p[i].r[j];
				}
			}
			else
			{
				temp=mp2[ch];
				table[i][temp]=p[i].r[j];
			}
		}
	}
	printf("%5c%5c",' ',' ');
	for(it2=mp2.begin();it2!=mp2.end();it2++)
	{
		printf("|%5c%5c",it2->first,' ');
	}
	printf("\n");
	for(i=0;i<k;i++)
	{
		j=mp1[p[i].l[0]];
		cout<<setw(10)<<p[i].l[0];
		for(it2=mp2.begin();it2!=mp2.end();it2++)
		{
			cout<<"|"<<setw(10)<<table[i][it2->second];
		}
		cout<<endl;
	}
	
	stack<char> s1;
	string s2="";
	s1.push('$');
	s1.push(p[0].l[0]);
	cout<<"Enter the input string to check: \n";
	cout<<setw(20)<<"TOP OF STACK"<<setw(20)<<"CURRENT STRING"<<setw(20)<<"STRING LENGTH"<<endl;
	cin>>s2;
	s2+="$";
	int curr=0;
	while(s1.top()!='$')
	{
		cout<<setw(20)<<s1.top()<<setw(20)<<s2.substr(curr,s2.length()-curr);
		char ch1=s1.top(),ch2=s2[curr];
		if(ch1>=65 && ch1<=90)
		{
			int t1=mp1[ch1];
			int t2=mp2[ch2];
			if(table[t1][t2]!="")
			{
				s1.pop();
				for(i=table[t1][t2].length()-1;i>=0 && table[t1][t2][i]!='e';i--)
				{
					s1.push(table[t1][t2][i]);
				}
				cout<<setw(20)<<ch1<<"->"<<table[t1][t2];
			}
			else
			{
				break;
			}
				
		}
		else
		{
			if(ch1!=ch2)
			{
				break;
			}		
			else
			{
				s1.pop();
				curr++;
			}
		}
		cout<<endl;		
	}
	if(s2[curr]=='$' && s1.top()=='$')
	{
		printf("\nString Accepted\n");
	}
	else printf("\nString not accepted\n");
}
