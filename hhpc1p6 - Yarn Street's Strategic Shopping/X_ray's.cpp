#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("avx2,fma")
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define ppi pair<int, pair<int, int>>
#define pll pair<ll, ll>

typedef long long ll;
typedef long double ld;

using namespace std;

const int blockSize = 548, mod = 1e9+7, K=10;


inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}


struct query {
	int idx, l, r, k, o;
	query(int idx, int l, int r, int k,int o) : idx(idx), l(l), r(r), k(k),o(o) { }
	
	inline pair<int, int> toPair() const {
		return make_pair(l / blockSize, ((l / blockSize) & 1) ? -r : +r);
	}
	
	bool operator < (const query& a) {
		return o < a.o;
	}
};



ll modPow(ll b, ll p) {
	return (p ? (! (p&1) ? modPow(b*b % mod, p>>1) : ((modPow(b*b % mod, p>>1)*b) % mod)): 1);
}

signed main() {
//	freopen("hhpc1p5.1.in","r",stdin);
//	freopen("std.out","w",stdout);
	cin.sync_with_stdio(NULL); cin.tie(NULL);
	// Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki
	int N, M, ocLim = 0;
	cin >> N;
	vector<vector<int>> F(N+1);
	vector<ll> PPDA(N+1, 1);
	for(int i = 1, c; i <= N; i++) {
		cin >> c; ocLim = max(ocLim, c);
		PPDA[i] = (PPDA[i-1]*c) % mod;
		F[i].pb(c);
		for(int j = 2; j*j <= c; j++) {
			if(c % j) continue;
			F[i].pb(j);
			if(j*j == c) continue;
			F[i].pb(c/j);
		}
	}
	vector<query> block;
	cin >> M;
	int kkk=log2(N*2-1);
	vector<pii> ans(M+1), intvl(M+1);
	for(int i = 1, l, r, k, o; i <= M; i++) {
		cin >> l >> r >> k; intvl[i] = mp(l, r); ans[i] = mp(1, 1);
		o = hilbertOrder(l,r,kkk,0);
		block.pb(query(i, l, r, k, o));
	}
	sort(block.begin(), block.end());
	vector<int> freq(ocLim+1, 0);
	vector<priority_queue<int>> leaders(K+2);
	for(int j = block[0].l; j <= block[0].r; j++) {
		for(auto& k: F[j]) freq[k]++;
	}
	for(int j = 1; j <= ocLim; j++) {
		if(! freq[j]) continue;
		leaders[min(freq[j], K+1)].push(j);
	}
	int L = block[0].l, R = block[0].r;
	{//process first
		ld curMax = -1e9;
		for(int j = 1; j <= K+1; j++) {
			if(leaders[j].empty()) continue;
			if(((ld) min(j, block[0].k))*log(leaders[j].top()) > curMax) {
				curMax = ((ld) min(j, block[0].k))*log(leaders[j].top());
				ans[block[0].idx] = mp(leaders[j].top(), min(j, block[0].k)); 
			}
		}
	}
	int j=1;
	auto gainNum = [&](int ptr) {
		for(auto& jj: F[ptr]) {
			if(freq[jj] < K+1){
				leaders[freq[jj]+1].push(jj);
			}
			freq[jj]++;
		}
	};
	auto loseNum = [&](int ptr) {
		for(auto& jj: F[ptr]) {
			if(freq[jj] > 1 && freq[jj] <= K+1) leaders[freq[jj]-1].push(jj);
			freq[jj]--;
		}
	};
	for(j = 1; j < block.size(); j++) {
		//move right pointer first
		while(R < block[j].r) {
			R++; gainNum(R);
		}
		while(L > block[j].l) {
			L--; gainNum(L);
		}
		while(R > block[j].r) {
			loseNum(R); R--;
		}
		while(L < block[j].l) {
			loseNum(L); L++; 
		}
		ld curMax = -1e9;
		for(int k = 1; k <= K+1; k++) {
			while(! leaders[k].empty() && min(freq[leaders[k].top()], K+1) != k) leaders[k].pop();
			if(leaders[k].empty()) continue;
			if(((ld) min(k, block[j].k))*log(leaders[k].top()) > curMax) {
				curMax = ((ld) min(k, block[j].k))*log(leaders[k].top());
				ans[block[j].idx] = mp(leaders[k].top(), min(k, block[j].k)); 
			}
		}
	}
	for(int i = 1; i <= M; i++) cout << (PPDA[intvl[i].second]*modPow(PPDA[intvl[i].first-1], mod-2) % mod)*modPow(ans[i].first, mod-1-ans[i].second) % mod << "\n";
}
