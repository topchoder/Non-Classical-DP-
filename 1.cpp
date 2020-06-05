#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define mx 252
#define nx 40
bool full[mx][mx],vis[mx][mx],full_recur[mx][mx][nx][nx];
int ans[mx];

void init()
{
   	for(int i=0;i<mx;i++)
   	{
   		for(int j=0;j<mx;j++)
   		{
   			full[i][j]=false,vis[i][j]=false;
   		}
   	}

   	for(int i=0;i<mx;i++)
   	{
   		ans[i]=-1;
   	}

   	for(int i=0;i<mx;i++)
   	{
   		for(int j=0;j<mx;j++)
   		{
   			for(int k=0;k<nx;k++)
   			{
   				for(int l=0;l<nx;l++)
   				{
   					full_recur[i][j][k][l]=false;
   				}
   			}
   		}
   	}

}

bool compute_full_recur(string str,int low,int high,vector<string> pat,int idx,int len)
{
	if(low>high&&len==pat[idx].length())
	{
		return true;
	}
	if(low>high&&len<pat[idx].length())
	{
		full_recur[low][high][idx][len]=false;
		return false;
	}
	if(str[low]==pat[idx][len]&&compute_full_recur(str,low+1,high,pat,idx,len+1))
	{
		return full_recur[low][high][idx][len]=true;
	}
	for(int i=low+1;i<=high;i++)
	{
		if(str[low]==pat[idx][len]&&full[low+1][i]&&compute_full_recur(str,i+1,high,pat,idx,len+1))
		{
			return full_recur[low][high][idx][len]=true;
		}
	}
	full_recur[low][high][idx][len]=false;
	return false;
}

void compute_full(string str,int low,int high,vector<string> pats)
{
	if(low>high)
	{
		return;
	}
	if(vis[low][high])
	{
		return;
	}
	vis[low][high]=true;
	compute_full(str,low+1,high,pats);
	compute_full(str,low,high-1,pats);
	for(int i=0;i<pats.size();i++)
	{
		if(!full[low][high])
		full[low][high]=compute_full_recur(str,low,high,pats,i,0);
	}
}

int compute_ans(string str,int low,int high)
{
	if(low>high)
	{
		return 0;
	}
	if(ans[low]!=-1)
	{
		return ans[low];
	}
	int sol=1+compute_ans(str,low+1,high);
	for(int i=low+1;i<=high;i++)
	{
		if(full[low][i]==true)
		{
			sol=min(sol,compute_ans(str,i+1,high));
		}
	}
	return ans[low]=sol;
}

signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string str;
		int n;
		vector<string> pats;
		cin>>n>>str;
		for(int i=0;i<n;i++)
		{
			string tem;
			cin>>tem;
			pats.push_back(tem);
		}
		init();
		compute_full(str,0,str.length()-1,pats);
		cout<<compute_ans(str,0,str.length()-1)<<endl;
	}
	return 0;
}
