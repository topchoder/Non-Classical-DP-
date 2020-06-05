#include <bits/stdc++.h>
using namespace std;

#define mx 151 
#define thres -15100000
long a[mx],dp[mx][mx],dp1[mx][mx][mx],n;
string palin;

void init(int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			dp[i][j]=LONG_MIN;
		}
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				dp1[i][j][k]=LONG_MIN;
			}
		}
	}
}

long str_recur(int low,int high,int len)
{
	// cout<<"len "<<len<<endl;
	// cout<<palin[low]<<" "<<palin[high]<<endl;
	// cout<<"low high len "<<low<<" "<<high<<" "<<len<<endl;
	if(low==high)
	{
		// cout<<"inside "<<endl;
		return a[len];
	}
	if(low>high)
	{
		if(len>0)
		{
			// cout<<"inside i"<<endl;
			return thres;
		}
		return 0;
	}
	if(dp1[low][high][len]!=LONG_MIN)
	{
		return dp1[low][high][len];
	}
    long ans=LONG_MIN;
    if(palin[low]==palin[high])
    {
    	// cout<<"hello "<<palin[low]<<" "<<palin[high]<<endl;
    	long x=str_recur(low+1,high-1,len+2);
    	long y=str_recur(low+1,high-1,0)+a[len+1];
    	// cout<<"x  y "<<x<<" "<<y<<endl;
        ans=max(x,y);
    }
    // cout<<"ans "<<ans<<endl;
    for(int i=low;i<high;i++)
    {
    	long x_=str_recur(low,i,len);
    	long y_=str_recur(i+1,high,0);
    	ans=max(ans,x_+y_);
    	// cout<<"x_  y_ "<<x_<<" "<<y_<<endl;
    	long z=str_recur(low,i,0);
    	long w=str_recur(i+1,high,len);
    	// cout<<"z  w "<<z<<" "<<w<<endl;
    	ans=max(ans,z+w);
    	// cout<<"ans i "<<ans<<endl;
    }
    return dp1[low][high][len]=ans;
}

long tot(int low,int high)
{
	 if(dp[low][high]!=LONG_MIN)
	 {
	 	return dp[low][high];
	 }
	 long sx=0;
     long tem=max(str_recur(low,high,0),sx);
     // cout<<"tem "<<tem<<endl;
     for(int i=low;i<high;i++)
     {
     	long a=tot(low,i);
     	long b=tot(i+1,high);
        // cout<<"a b "<<a<<" "<<b<<endl;
     	tem=max(tem,a+b);
     }
     return dp[low][high]=tem;
}


long mymax(long a,long b)
{
	return (a>b?a:b);
}

signed main()
{
	cin>>n;
	init(n);
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]==-1)
		{
			a[i]=thres;
		}
	}
    cin>>palin;
    long t=0;
    cout<<mymax(tot(0,n-1),t)<<endl;
	return 0;
}
