#include "labOop1.h"

int main()
{
	Point P1,P2;
	double x,y;
	cout<<"Enter two coordinates of your point:";
	cin>>x>>y;
	P1.SetXY(x,y);
	cout<<"\nThe first point:";
	P1.Print();
	cout<<"\n\nEnter two coordinates of your another point:";
	cin>>x>>y;
	P2.SetXY(x,y);
	cout<<"\nThe second point:";
	P2.Print();
	double D=P1.Distance(P2);
	cout<<"\n\nThe distance between two points is: "<<D<<endl;
	return 0;
}
