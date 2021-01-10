#include <bits/stdc++.h>
using namespace std;

#define k_mx 55
#define n_mx 55
int c[k_mx],a[n_mx],t[k_mx][k_mx],n,k;
vector<pair<int,long>> arr[n_mx][n_mx];
bool flag[n_mx][n_mx];
long dp[n_mx];
vector<pair<int,long>> compute(int low,int high)
{
	if(low==high)
	{
		// vector<pair<int,long>> tem;
		arr[low][low].push_back(make_pair(a[low],0));
		return arr[low][low];
	}
	if(flag[low][high])
	{
		return arr[low][high];
	}
	flag[low][high]=true;
	for(int i=low;i<high;i++)
	{
		vector<pair<int,long>> f=compute(low,i);
		vector<pair<int,long>> g=compute(i+1,high);
		for(int j=0;j<f.size();j++)
		{
			for(int k=0;k<g.size();k++)
			{
				arr[low][high].push_back(make_pair(t[f[j].first][g[k].first],f[j].second+g[k].second));
				arr[low][high].push_back(make_pair(t[g[k].first][f[j].first],f[j].second+g[k].second));
				arr[low][high].push_back(make_pair(g[k].first,c[f[j].first]+f[j].second+g[k].second));
				arr[low][high].push_back(make_pair(f[j].first,c[g[k].first]+f[j].second+g[k].second));
			}
		}
	}
	return arr[low][high];
}

long compute1(int low)
{
	if(low>=n)
	{
		return 0;
	}
	if(dp[low]!=-1)
	{
		return dp[low];
	}
	long res=compute1(low+1);
	for(int i=low;i<n;i++)
	{
		for(int j=0;j<arr[low][i].size();j++)
		{
			res=max(res,c[arr[low][i][j].first]+arr[low][i][j].second+compute1(i+1));
		}
	}
	return dp[low]=res;
}

void init()
{
	for(int i=0;i<n_mx;i++)
	{
		for(int j=0;j<n_mx;j++)
		{
			flag[i][j]=false;
			arr[i][j].clear();
		}
	}
	for(int i=0;i<n_mx;i++)
	{
		dp[i]=-1;
	}
}

signed main()
{
	cin>>k>>n;
	for(int i=0;i<k;i++)
	{
		cin>>c[i];
	}
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<k;j++)
		{
			cin>>t[i][j];
		}
	}
	init();
	compute(0,n-1);
  	long ans=compute1(0);
  	cout<<"ans "<<ans<<endl;
	return 0;
}
