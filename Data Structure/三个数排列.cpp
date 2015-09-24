#include <iostream>
using namespace std;
int main()
{
	char i,j,k;
	for (i='A';i<='C';++i){
		for (j='A';j<='C';++j){
			if (i==j) continue;
			for (k='A';k<='C';++k){
				if (i==k || j==k) continue;
				cout<<i<<j<<k<<endl;
			}
		}
	}
	return 0;
}