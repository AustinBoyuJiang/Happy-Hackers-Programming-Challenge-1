#pragma GCC optimize(2)
#pragma GCC optimize(3)
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

namespace FastIO{
	inline int read() {int x=0; bool f=0; char ch=0; while(!isdigit(ch)) f=ch=='-',ch=getchar(); while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return f?-x:x;}
	inline ll readLL() {ll x=0; bool f=0; char ch=0; while(!isdigit(ch)) f=ch=='-',ch=getchar(); while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return f?-x:x;}
	inline int read(int &x) {return x=read();}
    template<class T> inline void write(T x) {if(x<0) x=-x,putchar('-'); if(x>9) write(x/10); putchar(x%10+'0');}
	template<class T> inline void write(T x,char ch) {write(x),putchar(ch);}
} using namespace FastIO;

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

const int MOD = 1e9+7;
 
inline ll POW(ll b, int e) { //快速幂 
	ll r = 1;
	while(e) {
		if(e&1) {
			r *= b;
			r %= MOD;
		}
		e>>=1;
		b *= b;
		b %= MOD;
	}
	return r;
}

const int lim = 548;
struct DSQRT {  //单点更新+区求间最大值 O(log(n))
	vector<ll> s1,s2;
	DSQRT(int n) : s1(n),s2(n/lim+1) {}
	inline void update(int pos, ll val) {
		s1[pos]=max(s1[pos],val);
		s2[pos/lim]=max(s2[pos/lim],val);
	}
	inline ll query(int l,int r) {
		ll res=0;
		if(l/lim==r/lim){
			for(int i=l;i<=r;i++){
				res=max(res,s1[i]);
			}
			return res;
		}
		for(int i=l/lim+1;i<r/lim;i++){
			res=max(res,s2[i]);
		}
		for(int i=l;i<=(l/lim+1)*lim-1;i++){
			res=max(res,s1[i]);
		}
		for(int i=r/lim*lim;i<=r;i++){
			res=max(res,s1[i]);
		}
		return res;
	}
};

const int MX = 1000010;

int32_t main() {
  vvi factors(MX);
  vector<DSQRT> seg;

  FOR(i, 1, MX){ // O(nIn(n))
    for (int j = i; j < MX; j += i){
      factors[j].pb(i);
    }
  }

  vi rec(MX);

  int n;
  n=read(); 

  vi c(n); // vector<int>
  F0R(i, n) c[i]=read();
  
  vll sum(n),invsum(n);
  sum[0]=c[0];
  for(int i=1;i<n;i++){
    sum[i]=sum[i-1]*c[i];
    sum[i]%=MOD;
  }
  invsum[n-1]=POW(sum[n-1],MOD-2);
  for(int i=n-2;i>=0;i--){
  	invsum[i]=invsum[i+1]*c[i+1];
  	invsum[i]%=MOD;
  }
  
  int q;
  q=read();

  vi l(q), r(q), k(q);
  vll out(q); // vector<ll>
  vvi rev(n); // vector<vector<int>>

  F0R(i, 10){
    seg.eb(n);
  }

  F0R(i, q){
  	l[i]=read();
  	r[i]=read();
  	k[i]=read();
    l[i]--; r[i]--;
    rev[r[i]].pb(i);
  }
  
  // O(nkcbrt(c)+qksqrt(n))
  
  /*
  O(nkcbrt(c)+qksqrt(n))
  vs.
  O(nklog(n)cbrt(c)+qklog(n))

  k = 10
  c = 1e6
  n = 6e4
  q = 6e4
  */

  vvi last(MX);
  F0R(i, n){ // O(n)
    for(int v: factors[c[i]]){ // O(cbrt(c))
      last[v].pb(i);

      int uu = sz(last[v]);
      int amt = min(10, uu);
      F0R(j, amt){  // O(k)
        int left = last[v][uu - 1 - j];
        seg[j].update(left, v);
      }
    }

    for(int ind : rev[i]){ // O(q)
      int tot = 1;
      int e = 1;

      F0R(j, k[ind]){ // O(k)
        int best = seg[j].query(l[ind],i); // O(sqrt(n))
        if (best <= 0) continue;

        if ((j + 1) * log(best) > e * log(tot)){
          tot = best;
          e = j + 1;
        }
      }
      if(!l[ind]) out[ind]=sum[r[ind]];
      else out[ind] = sum[r[ind]]*invsum[l[ind]-1]%MOD;
      out[ind] *= POW(tot, MOD - 1 - e);
      out[ind] %= MOD;
    }
  }

  F0R(i, q){
    write(out[i],'\n');
  }
}

