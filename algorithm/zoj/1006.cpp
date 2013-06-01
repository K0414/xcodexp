/**************************************************************************
	ciphercode[i] = (plaincode[ki mod n] - i) mod 28
		==>
	plaincode[ki mod n] = (ciphercode[i] + i) mod 28
		==>
	plaincode[0..n-1]全部得出即完成解密
**************************************************************************/

#include <iostream>
using namespace std;

int plaincode[70],ciphercode[70];
char msg[71];

int main() {
	int k,n;
	char c;
	
	while(cin>>k) {
		if(!k)
			return 0;
			
		cin >> msg;
		
		n = strlen(msg);
		
		for(int i=0; i<n; i++) {
			if(msg[i] == '_')
				ciphercode[i] = 0;
			else if(msg[i] == '.')
				ciphercode[i] = 27;
			else
				ciphercode[i] = msg[i] - 'a' + 1;		
		}
		
		for(int i=0; i<n; i++)
			plaincode[(k*i) % n] = (ciphercode[i] + i) % 28;
			
		for(int i=0; i<n; i++) {
			if(plaincode[i] == 0)
				cout << '_';
			else if(plaincode[i] == 27)
				cout << '.';
			else {
				c = 'a' + plaincode[i] - 1;
				cout << c;
			}
		}
		cout << endl;
	}
	return 0;
}
