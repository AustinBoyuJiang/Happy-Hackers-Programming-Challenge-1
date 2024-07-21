/*
 * Author: Austin Jiang
 * Date: 11/21/2023 3:17:02 PM
 * Problem:
 * Source:
 * Description:
*/

/* Configuration */
//#define MULTICASES
//#define LOCAL
//#define READLOCAL
//#define FILESCOMP
//#define SETMEM
#define FASTIO
#define OPTIMIZE
//#define INTTOLL

#ifdef OPTIMIZE
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#endif

#include<bits/stdc++.h>
using namespace std;

#ifdef INTTOLL
#define int long long
#endif

#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define per(i,x,y) for(int i=(x);i>=(y);i--)
#define endl '\n'

/* Pair */
#define fir first
#define sec second

/* Segment Tree */
#define lc (rt << 1)
#define rc (rt << 1 | 1)

/* STL */
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define eb emplace_back
#define ef emplace_front
#define pb push_back
#define pf push_front
#define all(v) v.begin(), v.end()

/* Random */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define random(a,b) rng()%(b-a+1)+a

/* Data type */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using PI = pair<int,int>;
using PPI = pair<PI,int>;
using VI = vector<int>;
using VPI = vector<PI>;
template <class T> using Vec = vector<T>;
template <class T> using PQ = priority_queue<T>;
template <class T> using PQG = priority_queue<T,vector<T>,greater<T>>;

/* Set up */
namespace FastIO{
	inline int read() {int x=0; bool f=0; char ch=0; while(!isdigit(ch)) f=ch=='-',ch=getchar(); while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return f?-x:x;}
	inline ll readLL() {ll x=0; bool f=0; char ch=0; while(!isdigit(ch)) f=ch=='-',ch=getchar(); while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return f?-x:x;}
	inline int read(int &x) {return x=read();}
    template<class T> inline void write(T x) {if(x<0) x=-x,putchar('-'); if(x>9) write(x/10); putchar(x%10+'0');}
	template<class T> inline void write(T x,char ch) {write(x),putchar(ch);}
} using namespace FastIO;

void SETUP(){
	#ifdef FASTIO
	cin.tie(nullptr)->sync_with_stdio(false);
	#endif
	#ifdef READLOCAL
	freopen("in.txt","r",stdin);
	freopen("stdout.txt","w",stdout);
	#endif
	srand(time(0));
}

/* Constants */
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
#ifndef int
const int INF = 0x3f3f3f3f;
#else
const ll INF = LLINF;
#endif
const int MOD = 1e9+7;
const int dir[8][2] = {{1,0},{0,1},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
const unordered_set<char> vowel = {'a','e','i','o','u'};

/* Common functions */

namespace Comfun{
	template<class T> inline T lowbit(T x){return x&-x;}
	template<class T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
	template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
	template<class T> inline T chkmax(T &a,T b){return a=max(a,b);}
	template<class T> inline T chkmin(T &a,T b){return a=min(a,b);}
	template<class T> inline T qpow(T a,T b){T ans=1;
	while(b){if(b&1)ans*=a,ans%=MOD;a*=a,a%=MOD;b>>=1;}return ans;}
	inline int mex(VI s){sort(all(s));int j=0;rep(i,0,s[s.size()-1]+1){
	while(j<s.size()&&s[j]<i) j++;if(s[j]!=i) return i;}}
	template<class T> inline T inv(T x){return qpow(x,MOD-2);}
	template<class T> inline bool is_prime(T x){
	if(x==1) return false; for(T i=2;i*i<=x;i++) if(x%i==0) return false;return true;}
	template<class T> inline void disc(Vec<T> &v,int st=0){set<int> num;Vec<T> pos;
	for(T x:v)num.insert(x);for(T x:num)pos.pb(x);for(T &x:v) x=lb(all(pos),x)-pos.begin()+st;}
} using namespace Comfun;

/* ========================================| Main Program |======================================== */

const int N = 3e5+10;
const int C = 1e6+10;
const int Z = 25;

int n,m,a[N];
VI pos[C],p[C];

int get(int x,int l,int r){ // O(log(n))
	int ll,rr,L,R;
	L=0,R=pos[x].size()-1,ll=pos[x].size();
	while(L<=R){
		int mid=L+R>>1;
		if(pos[x][mid]>=l){
			ll=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	L=0,R=pos[x].size()-1,rr=pos[x].size();
	while(L<=R){
		int mid=L+R>>1;
		if(pos[x][mid]>r){
			rr=mid;
			R=mid-1;
		}
		else L=mid+1;
	}
	return rr-ll;
}

struct segtree{
	VPI nd[N<<2];
	int lim;
	
	VPI merge(VPI a,VPI b,int l,int r){ // O(Zlog(n))
		VPI res;
		for(PI x:a){
			res.pb({x.fir,min(get(x.fir,l,r),lim)});
		}
		for(PI x:b){
			res.pb({x.fir,min(get(x.fir,l,r),lim)});
		}
		sort(all(res),[](PI a,PI b){
			return a.sec*log(a.fir)>b.sec*log(b.fir);
		});
		while(res.size()>Z) res.pop_back();
		return res;
	}
	
	void build(int rt,int l,int r){ // O(nZlog(n)^2)
		if(l==r){
			nd[rt].clear();
			rep(i,0,min(Z,(int)p[a[l]].size())-1){
				nd[rt].pb({p[a[l]][i],1});
			}
			return;
		}
		int mid=l+r>>1;
		build(lc,l,mid);
		build(rc,mid+1,r);
		nd[rt]=merge(nd[lc],nd[rc],l,r);
	}
	
	VPI query(int rt,int l,int r,int x,int y){ // O(Zlog(n)^2)
		if(l==x&&r==y) return nd[rt];
		int mid=l+r>>1;
		if(y<=mid) return query(lc,l,mid,x,y);
		else if(x>mid) return query(rc,mid+1,r,x,y);
		return merge(query(lc,l,mid,x,mid),query(rc,mid+1,r,mid+1,y),x,y);
	}
	
} st[10];

inline void SOLVE(int Case){
	cin>>n;
	int MX=0;
	rep(i,1,n){
		cin>>a[i];
		chkmax(MX,a[i]);
	}
	Vec<ll> sum(n+1),invsum(n+1);
	sum[0]=invsum[0]=1;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]*a[i];
		sum[i]%=MOD;
	}
	invsum[n]=qpow(sum[n],MOD-2ll);
	for(int i=n-1;i>0;i--){
		invsum[i]=invsum[i+1]*a[i+1];
		invsum[i]%=MOD;
	}
	rep(i,1,MX){
		for(int j=i;j<=MX;j+=i){
			p[j].pb(i);
		}
	}
	rep(i,1,n){
		for(int x:p[a[i]]){
			pos[x].pb(i);
		}
	}
	rep(i,1,MX){
		reverse(all(p[i]));
	}
	rep(i,0,9){ // O(nkZlog(n)^2)
		st[i].lim=i+1;
		st[i].build(1,1,n);
	}
	cin>>m;
	rep(i,1,m){ // O(qkZlog(n)^2)
		int l,r,k;
		cin>>l>>r>>k;
		PI mx=st[k-1].query(1,1,n,l,r)[0];
		ll ans=sum[r]*invsum[l-1]%MOD;
		ans*=qpow(mx.fir*1ll, MOD-1ll-mx.sec);
		ans%=MOD;
		cout<<ans<<endl;
	}
}

/* =====================================| End of Main Program |===================================== */

signed main(){
	#ifdef SETMEM
    int size(512<<20);  //512MB
    __asm__("movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
	#endif
	#ifndef FILESCOMP
	SETUP();
	int CASE=1;
	#ifdef MULTICASES
	cin>>CASE;
	#endif
	rep(i,1,CASE){
		#ifdef LOCAL
		printf("Case #%d: \n",i);
		#endif
		SOLVE(i);
	}
	#else
	system("fc stdout.txt out.txt");
	#endif
	#ifdef SETMEM
    exit(0);
    #endif
	return 0;
}

/* stuff you should look for
	* read questions at least 3 times!!!
    * think more and then code!!!
    * partial points are GOD.
	* remember to initialize variables
    * don't stuck on one question for two long (like 30-45 min)
    * Debug: (a) read your code once, check overflow and edge case
    * Debug: (b) create your own test case
    * Debug: (c) Adversarial Testing
*/

