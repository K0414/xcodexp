#include <iostream>

using namespace std;

typedef enum { NO_ACT, FILL_A, EMPTY_A, POUR_A, FILL_B, EMPTY_B, POUR_B} Action;

class Container {
public:
	Container(int a, int b, int dest) : capacity_a(a), capacity_b(b), dest(dest),
										current_a(0), current_b(0),
										previous_a(0), previous_b(0), last_action(NO_ACT) {};
	bool process(Action act);
	void undo();
	inline int get_current_a() { return current_a; };
	inline int get_current_b() { return current_b; };
	inline bool is_ok() { return ((current_a == dest) || (current_b == dest)); };

private:
	int capacity_a, capacity_b, dest;
	int current_a, current_b;
	int previous_a, previous_b;
	Action last_action;
};

Action	action_queue[512];
int		cur;

void Container::undo() {
	current_a = previous_a;
	current_b = previous_b;
	
	cur--;
}

bool Container::process(Action act) {
	previous_a = current_a;
	previous_b = current_b;
	
	if(last_action == FILL_A) {
		if(act == FILL_A || act == EMPTY_A
						 || act == FILL_B
						 || act == EMPTY_B
						 || act == POUR_B)
			return false;
	} else if(last_action == EMPTY_A) {
		if(act == EMPTY_A|| act == EMPTY_B
						 || act == FILL_A
						 || act == POUR_A)
			return false;
	} else if(last_action == POUR_A) {
		if(act == POUR_A || act == EMPTY_A)
			return false;
	} else if(last_action == FILL_B) {
		if(act == FILL_B || act == FILL_A
						 || act == POUR_A
						 || act == EMPTY_A
						 || act == EMPTY_B)
			return false;
	} else if(last_action == EMPTY_B) {
		if(act == EMPTY_B|| act == EMPTY_A
						 || act == FILL_B
						 || act == POUR_B)
			return false;
	} else if(last_action == POUR_B) {
		if(act == POUR_B || act == EMPTY_B)
			return false;
	}
	
	switch(act) {
		case FILL_A :
			if(current_a == capacity_a)
				return false;
			current_a = capacity_a;
			break;
		case EMPTY_A :
			current_a = 0;
			break;
		case POUR_A :
			if(current_b == capacity_b)
				return false;
			current_b += current_a;
			if(current_b > capacity_b) {
				current_a = current_b - capacity_b;
				current_b = capacity_b;
			}
			break;
		case FILL_B :
			if(current_b == capacity_b)
				return false;
			current_b = capacity_b;
			break;
		case EMPTY_B :
			current_b = 0;
			break;
		case POUR_B :
			if(current_a == capacity_a)
				return false;
			current_a += current_b;
			if(current_a > capacity_a) {
				current_b = current_a - capacity_a;
				current_a = capacity_a;
			}
			break;
		default:
			break;
	}
	
	action_queue[cur++] = act;
	last_action = act;
	
	return true;
}

void print_action(Action act) {
	switch(act) {
		case FILL_A:
			cout << "fill A" << endl;
			break;
		case EMPTY_A:
			cout << "empty A" << endl;
			break;
		case POUR_A:
			cout << "pour A B" << endl;
			break;
		case FILL_B:
			cout << "fill B" << endl;
			break;
		case EMPTY_B:
			cout << "empty A" << endl;
			break;
		case POUR_B:
			cout << "pour B A" << endl;
			break;
		default:
			cout << "Invalid value!" << endl;
			break;
	}
}

void dfs(Container &container) {
	if(container.is_ok()) {
		for(int i=0; action_queue[i]; i++) {
			print_action(action_queue[i]);
		}
		cout << "success" << endl;
	} else {
		for(int a = 1; a != 7; a++) {
			if(!container.process((Action)a)) 
				continue;	
			dfs(container);
			container.undo();
		}
	}
}

int main() {
	int a, b, dest;
	
	while(cin>>a>>b>>dest) {
		Container container(a, b, dest);
		dfs(container);
	}
	
	cout << "should not be here." << endl;
	
	return 0;
}
