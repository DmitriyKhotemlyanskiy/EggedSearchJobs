#include "labOop2.h"


int main()
{
	Complex A,B(3,4);
	cout<<"\nA: ";
	A.Print();
	cout<<"\nB: ";
	B.Print();
	A.SetValues(5,6);
	cout<<"\nAnd now A: ";
	A.Print();
	Complex C=A.Sum(B);
	cout<<"\nC: ";
	C.Print();
	Complex *D;

	............
    return 0;
}

