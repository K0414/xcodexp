#include <iostream>
#include <stack>

#define IN	0
#define OUT	1

using namespace std;

stack<char> g_stack;
char		g_queue[1000];
char		g_str[128],*ptr;
int 		cur;

void dfs(char *str, char *dest)
{
	if((ptr - g_str) == strlen(dest)) {
		*ptr = 0;
		
		if(!strcmp(g_str, dest)) {
			for(int i=0; i != cur; i++) {
				cout << g_queue[i] << ' ';
			}
			cout << endl;
		}
	} else {
		if(*str) {
			g_stack.push(*str++);
			g_queue[cur++] = 'i';
			dfs(str, dest);
			g_stack.pop();
			cur--;
			str--;
		}
		
		if(!g_stack.empty()) {
			*ptr++ = g_stack.top();
			g_stack.pop();
			g_queue[cur++] = 'o';
			dfs(str, dest);
			g_stack.push(*(--ptr));
			cur--;
		}
	}
}

int main()
{
	char str[128],dest[128];
	
	while(cin>>str && cin>>dest) {
		ptr = g_str;
		cur = 0;
		
		cout << "[" << endl;
		if(strlen(str) == strlen(dest))
			dfs(str, dest);
		cout << "]" << endl;
	}
	
	return 0;
}
