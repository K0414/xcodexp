/* 
 * POJ - 1084
 * square_num = \sum_1^{k}(k^2)
 * edge_num = N*(N+1) + (N+1)*N = 2*N*(N+1)
 * square_id increases by pos and size
 *
 * ios::sync_with_stdio(0) can make cin/cout faster
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <bitset>
using namespace std;

int ans;
map<string, int> memo;

void dfs(int pos, int acc, bitset<55> squares, const vector<bitset<55> > &squareof,
		const vector<bitset<55> > &accum_square_of)
{
	const int N = squareof.size(); // edge count
	if(acc >= ans) return;
	if(squares.none()) {
		if(acc < ans) ans = acc;
		return;
	}
	if(pos == N) return;
	// pruning1: the left edges can not cover all existing squares
	if((accum_square_of[pos] & squares) != squares) return;

	// pruning2: the same square with lower ans already appeared
	const string state = squares.to_string();
	if(memo.count(state) && memo[state] <= acc) return;
	memo[state] = acc;

	for (int i = pos; i < N; i++) {
		bitset<55> res = squares & squareof[i];
		if(res.none()) continue;
		dfs(i+1, acc+1, squares & ~res, squareof, accum_square_of);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	scanf("%d", &T);
	while(T) {
		int N, K;
		scanf("%d%d", &N, &K);
		
		int edge_num = 2 * N * (N + 1);

		// generate squareof[]
		// squareof[i] = squares that contains edge i
		vector<bitset<55> > squareof(edge_num);
		int idx = 0;
		for (int row = 0; row < N; row++) {
			for (int col = 0; col < N; col++) {
				const int maxsize = min(N-row, N-col);

				for (int size = 1; size <= maxsize; size++) {
					int cur = (N + N + 1) * row + col;

					for (int i = 0; i < size-1; i++) { // Go right
						squareof[cur].set(idx);
						cur++;
					}
					squareof[cur].set(idx);
					cur += N+1;
					for (int i = 0; i < size-1; i++) { // Go down
						squareof[cur].set(idx);
						cur += (N+N+1);
					}
					squareof[cur].set(idx);
					cur += N;
					for (int i = 0; i < size-1; i++) { // Go left
						squareof[cur].set(idx);
						cur--;
					}
					squareof[cur].set(idx);
					cur -= N+1;
					for (int i = 0; i < size-1; i++) { // Go up
						squareof[cur].set(idx);
						cur -= (N+N+1);
					}
					squareof[cur].set(idx);
					idx++;
				}
			}
		}

		// calc squares the remaining edges can cover
		vector<bitset<55> > accum_square_of(edge_num);
		for(int i = 0; i < edge_num; i++) {
			for(int j = i; j < edge_num; j++) {
				accum_square_of[i] |= squareof[j];
			}
		}

		// pick out missing edges
		bitset<55> squares;
		for (int i = 0; i < idx; i++) {
			squares.set(i);
		}

		for (int i = 0; i < K; i++) {
			int edge;
			scanf("%d", &edge);
			edge--;
			squares &= ~squareof[edge];
		}

		// solve
		ans = 100;
		memo.clear();
		dfs(0, 0, squares, squareof, accum_square_of);
		cout << ans << endl;

		T--;
	}

    return 0;
}

