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
}
