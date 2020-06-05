#include <bits/stdc++.h>
using namespace std;

#define mx 82
int n,arr[mx],cost[mx],dp[mx][mx],dp1[mx][mx][mx][mx];
void init()
{
	for(int i=0;i<mx;i++)
	{
		for(int j=0;j<mx;j++)
		{
			dp[i][j]=-1;
		}
	}
	for(int i=0;i<mx;i++)
	{
		for(int j=0;j<mx;j++)
		{
			for(int k=0;k<mx;k++)
			{
				for(int w=0;w<mx;w++)
				{
					dp1[i][j][k][w]=-1;
				}
			}
		}
	}
}

int solve_recur(int low,int high,int len,int pre)
{
	if(low>high)
	{
		return 0;
	}
	if(dp1[low][high][len][pre]!=-1)
	{
		return dp1[low][high][len][pre];
	}
	int ans=cost[len]+solve_recur(low+1,high,0,pre);
	for(int i=low+1;i<=high;i++)
	{
		if(abs(arr[low]-arr[i])==1&&len==0)
		{
			ans=max(ans,solve_recur(low+1,i-1,0,81)+solve_recur(i,high,len+1,low));
		}
		else if(abs(arr[low]-arr[i])==1&&len>0&&(2*arr[low]-arr[i]-arr[pre])>=0)
		{
			ans=max(ans,solve_recur(low+1,i-1,0,81)+solve_recur(i,high,len+1,low));
		}
	}
	return dp1[low][high][len][pre]=ans;
}

int solve(int low,int high)
{
	if(low>high)
	{
		return 0;
	}
	if(dp[low][high]!=-1)
	{
		return dp[low][high];
	}
	int x=solve(low+1,high);
	int y=solve(low,high-1);
	int z=solve_recur(low,high,0,81);
	return dp[low][high]=max(x,max(y,z));
}

signed main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>cost[i];
	}
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	init();
	cout<<solve(0,n-1)<<endl;
	return 0;
}
