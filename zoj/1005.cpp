/*****************************************************************************

��ˮ����ľ�����ʽ�������ģ�
"������һ��������������������ˮ������2����ˮ�����ݻ��ֱ�Ϊ5����6����
���������ֻ����2��ˮ���ӳ�����ȡ��3����ˮ��"

��ʵ�ϣ�Ҫ����������⣬��ֻҪ���������е�����һ���ӳ������ˮ��
���ϵص�����һ��������ڶ��������˵�ʱ�򣬰����е�ˮ���س����
�������Σ��͵õ����ˡ���5����(A)��6����(B)Ϊ����

A����B
0����0
5����0����A��B
0����5
5����5����A��B
4����6
4����0����A��B
0����4
5����4����A��B
3����6

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
		
		// �����pour����sub->cmp->?{(add,mov),(sub)}���ᵼ�³�ʱ��
		// ����ķ���add->mov->cmp->?(sub,mov),��b�����������ÿ�ν�Լһ������
		
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
