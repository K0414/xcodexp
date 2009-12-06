/*****************************************************************************

倒水问题的经典形式是这样的：
"假设有一个池塘，里面有无穷多的水。现有2个空水壶，容积分别为5升和6升。
问题是如何只用这2个水壶从池塘里取得3升的水。"

事实上，要解决上面这题，你只要用两个壶中的其中一个从池塘里灌水，
不断地倒到另一个壶里，当第二个壶满了的时候，把其中的水倒回池塘里，
反复几次，就得到答案了。以5升壶(A)灌6升壶(B)为例：

A　　B
0　　0
5　　0　　A→B
0　　5
5　　5　　A→B
4　　6
4　　0　　A→B
0　　4
5　　4　　A→B
3　　6

*****************************************************************************/

#include <iostream>
using namespace std;

typedef struct _Jug {
	int capacity;
	int current;
}Jug;

int goal;

/*bool pour(Jug &a, Jug &b) {
	int b_left = b.capacity - b.current;
	
	cout << "pour A B" << endl;
	
	if(b_left > a.current) {
		b.current += a.current;
		a.current = 0;
		
		return false;
	} else {
		a.current -= b_left;
		
		return true;
	}
}*/

void run(Jug &a, Jug &b) {
	while(b.current != goal) {
		if(a.current == 0) {
			a.current = a.capacity;
			cout << "fill A" << endl;		
		}
		
		// 上面的pour函数sub->cmp->?{(add,mov),(sub)}，会导致超时，
		// 下面的方法add->mov->cmp->?(sub,mov),在b不满的情况下每次节约一个减法
		
		b.current += a.current;
		a.current = 0;
		cout << "pour A B" << endl;
		if(b.current > b.capacity) {
			a.current = b.current - b.capacity;
			b.current = 0;
			cout << "empty B" << endl;
		}
	}
	cout << "success" << endl;
}

int main() {
	int Ca,Cb;
	Jug A, B;
	
	while(cin>>Ca>>Cb>>goal) {
		A.capacity = Ca;
		A.current = 0;
		B.capacity = Cb;
		B.current = 0;
		
		run(A, B);
	}
	
	return 0;
}
