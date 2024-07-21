#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define sz(v) (int)v.size()
#define sq(a) ((a)*(a))

#define per(i,a,b) for (int i = (b)-1; i >= a; i--)
#define rep(i,a,b) for (int i=a; i<b; i++)

#define FOR(i,a,b) for (int i=a; i<b; i++)
#define F0R(i,a) for (int i=0; i<a; i++)
#define ROF(i,a,b) for (int i = (b)-1; i >= a; i--)
#define R0F(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << endl, 0;
#define dbg(x) cerr << ">>> " << #x << " = " << x << endl;
#define _ << " _ " <<

#define ll long long

template<class T> bool ckmin(T&a, T&b) { bool B = a > b; a = min(a,b); return B; }
template<class T> bool ckmax(T&a, T&b) { bool B = a < b; a = max(a,b); return B; }

typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ld,ld> pld;
typedef complex<ld> cd;

typedef vector<int> vi;
typedef vector<ld> vld;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;

const ld PI = acos(-1.0);
const ld EPS = 1e-7;
const int MOD = 1e9+7;
 
ll POW(ll b, ll e) {
	ll r = 1;
	while(e) {
		if(e % 2 == 1) {
			r *= b;
			r %= MOD;
		}
		e /= 2;
		b *= b;
		b %= MOD;
	}
	return r;
}

struct Tree {
	typedef ll T;
	static constexpr T unit = 1;
	T f(T a, T b) { return (a * b) % MOD; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = max(s[pos], dif);
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res = max(res, s[pos-1]);
		return res;
	}
};

const int MX = 1000100;

int32_t main() { FAST
	freopen("hhpc1p5.12.in","r",stdin);
  vvi factors(MX);
  vector<FT> seg;
  vector<vi> sb;

  ROF(i, 1, MX){
    for (int j = i; j < MX; j += i){
      factors[j].pb(i);
    }
  }

  vi rec(MX);

  int n;
  cin >> n;

  vi c(n);
  F0R(i, n) c[i] = 942480;
  F0R(i, n) cin >> c[i];

  Tree prod(n);

  F0R(i, n) prod.update(i, c[i]);

  int q;
  cin >> q;

  vi l(q), r(q), k(q);
  vll out(q);
  vvi rev(n);

  F0R(i, 10){
    seg.eb(n);
    sb.eb(n);
  }

  F0R(i, q){
    cin >> l[i] >> r[i] >> k[i];
    l[i]--; r[i]--;
    rev[r[i]].pb(i);
  }
	int aa=0,bb=0;
  vvi last(MX);
  F0R(i, n){
    for(auto v: factors[c[i]]){
      last[v].pb(i);

      int uu = sz(last[v]);
      int amt = min(10, uu);
      FOR(j, 0, amt){
        int left = last[v][uu - 1 - j];
        if (v > sb[j][n-1-left]){
            seg[j].update(n - 1 - left, v);
            sb[j][n-1-left] = v;
        }
        else bb++;
        aa++;
      }
    }

    for(auto ind : rev[i]){
      int tot = 1;
      int e = 1;

      F0R(j, k[ind]){
        int best = seg[j].query(n - l[ind]);

        if (best <= 0) continue;

        if ((j + 1) * log(best) > e * log(tot)){
          tot = best;
          e = j + 1;
        }
      }
      
      out[ind] = prod.query(l[ind], r[ind] + 1);
      out[ind] *= POW(tot, MOD - 1 - e);
      out[ind] %= MOD;
    }
  }
	cout<<bb*1.0/aa<<endl;
//  F0R(i, q){
//    cout << out[i] << '\n';
//  }
}

