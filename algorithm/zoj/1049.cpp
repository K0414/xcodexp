#include <iostream>
using namespace std;
#define PI 3.1415926

int main()
{
	int i,n,year,num;
	float x,y,area;
	int *ptr;
	cin>>n;
	num=n;
	ptr=new int[n];
	i=0;
	while(n--)
	{
		cin>>x>>y;
		area=PI*(x*x+y*y)/2;
		year=area/50+1;
		ptr[i++]=year; 
		//cout<<"Property "<<++i<<": This property will begin eroding in year "<<year<<"."<<endl;
	}
	for(i=0;i<num;i++)
		cout<<"Property "<<i+1<<": This property will begin eroding in year "<<ptr[i]<<"."<<endl;
	cout<<"END OF OUTPUT."<<endl;
	
	return 0;	
}
