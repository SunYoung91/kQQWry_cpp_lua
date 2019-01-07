#include "ip_finder.h"
#include "iostream"
using namespace std;
int main()
{
	CIpFinder finder;
	bool ok = finder.Open("qqwry.dat");
	if (ok){	
		int i = 0;
		while (i < 1000)
		{			
			std::string strCountry;
			std::string strLocation;
			finder.GetAddressByIp("4.4.4.4",strCountry,strLocation);
			cout<<"ip地址信息:"<<strCountry<<","<<strLocation<<endl;
			i++;
		}
	}
	else
	{
		cout<<"database can not open"<<endl;
	}
}