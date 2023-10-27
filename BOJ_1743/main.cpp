#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

int n, m, k;
vvi bd;
vvb visit;

const auto dr = vi{ -1,1,0,0 };
const auto dc = vi{ 0,0,-1,1 };

int dfs(int i, int j) {
	auto st = stack<pii>{};
	st.push({ i, j });
	visit[i][j] = true;

	auto ret = 0;
	while (!st.empty()) {
		auto [r, c] = st.top();
		st.pop();

		++ret;

		for (auto d = 0; d < 4; ++d) {
			const auto nr = r + dr[d];
			const auto nc = c + dc[d];

			if (nr < 0 || n <= nr ||
				nc < 0 || m <= nc) {
				continue;
			}

			if (visit[nr][nc]) {
				continue;
			}

			if (0 == bd[nr][nc]) {
				continue;
			}

			st.push({ nr, nc });
			visit[nr][nc] = true;
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m >> k;

	bd = vvi(n, vi(m, 0));
	while (0 < (k--)) {
		int r, c;
		cin >> r >> c;

		bd[r - 1][c - 1] = 1;
	}

	visit = vvb(n, vb(m, false));
	auto ans = int{ 0 };
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (visit[i][j]) {
				continue;
			}

			if (0 == bd[i][j]) {
				continue;
			}

			ans = max(ans, dfs(i, j));
		}
	}

	cout << ans;

	return 0;
}