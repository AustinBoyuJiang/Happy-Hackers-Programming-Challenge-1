/*
 * Author: Austin Jiang
 * Date: 9/26/2023 2:49:06 PM
 * Problem:
 * Source:
 * Description:
*/

/* Configuration */
//#define MULTICASES
//#define LOCAL
#define READLOCAL
//#define FILESCOMP
//#define SETMEM
//#define FASTIO
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
	freopen("data.in","r",stdin);
//	freopen("stdout.txt","w",stdout);
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
const ll MOD = 1e9+7;
const int dir[8][2] = {{1,0},{0,1},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
const unordered_set<char> vowel = {'a','e','i','o','u'};

/* Common functions and data structures */

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
	template<class T> inline T inv(T x){return qpow(x*1ll,MOD-2);}
	template<class T> inline bool is_prime(T x){
	if(x==1) return false; for(T i=2;i*i<=x;i++) if(x%i==0) return false;return true;}
	template<class T> inline void disc(Vec<T> &v,int st=0){set<int> num;Vec<T> pos;
	for(T x:v)num.insert(x);for(T x:num)pos.pb(x);for(T &x:v) x=lb(all(pos),x)-pos.begin()+st;}
} using namespace Comfun;

/* ========================================| Main Program |======================================== */

using PID = pair<ll,ld>;

const int N = 5e4+10;
const int C = 5e5+10;
const int K = 5;

int n,m,c[N],l[N],r[N],k[N];
ll sum[N];
Vec<pair<PID,int>> lst[C];
Vec<PID>invlst[C];
VI q[N],p[N];
PID ans[N];
	
PID max(PID a,PID b){
	if(a.sec>b.sec) return a;
	return b;
}

struct Decomposition{
	int siz;
	PID flag1[N],flag2[(int)sqrt(N)+10];
	
	int block(int pos){
		return (pos-1)/siz+1;
	}
	
	void init(){
		siz=sqrt(n);
		rep(i,1,n){
			flag1[i]={1,0};
			flag2[block(i)]={1,0};
		}
	}
	
	void upd(int pos,PID val){
		flag1[pos]=max(flag1[pos],val);
		flag2[block(pos)]=max(flag2[block(pos)],val);
	}
	
	PID ask(int l,int r){
		PID res={1,0};
		if(block(l)==block(r)){
			rep(i,l,r) res=max(res,flag1[i]);
			return res;
		}
		rep(i,block(l)+1,block(r)-1){
			res=max(res,flag2[i]);
		}
		rep(i,l,block(l)*siz){
			res=max(res,flag1[i]);
		}
		rep(i,(block(r)-1)*siz+1,r){
			res=max(res,flag1[i]);
		}
		return res;
	}
} sq[K+1];

PID mult(PID a,int b){
	a.fir*=b;
	a.fir%=MOD;
	a.sec+=log2((ld)b);
	return a;
}

PID mult(PID a,PID b){
	a.fir*=b.fir;
	a.fir%=MOD;
	a.sec+=b.sec;
	return a;
}

void get_primes(VI &res,int x){
	for(int i=1;i*i<=x;i++){
		if(x%i) continue;
		res.pb(i);
		if(i!=x/i) res.pb(x/i);
	}
}

inline void SOLVE(int Case){
	read(n);
	sum[0]=1;
	rep(i,1,n){
		read(c[i]);
		get_primes(p[i],c[i]);
		sum[i]=sum[i-1]*c[i]%MOD;
	}
	read(m);
	rep(i,1,m){
		read(l[i]),read(r[i]),read(k[i]);
		ans[i]={1,0};
		q[r[i]].pb(i);
	}
	rep(i,1,C-1){
		lst[i].pb({{1,0},0}); //[value,log2(value),pos]
		invlst[i].pb({1,0});
	}
	rep(i,1,K){
		sq[i].init();
	}
	rep(i,1,n){
		for(int j:p[i]){
			PID val=mult(lst[j][lst[j].size()-1].fir,j);
			lst[j].pb({val,i});
			invlst[j].pb({inv(val.fir),-val.sec});
			rep(pre,1,K){
				if(lst[j].size()<pre+1) break;
				int pos=lst[j][lst[j].size()-pre].sec;
				PID val=mult(lst[j][lst[j].size()-1].fir,invlst[j][lst[j].size()-pre-1]);
				sq[pre].upd(pos,val);
				int p1=lst[j][lst[j].size()-1].sec;
				int p2=lst[j][lst[j].size()-pre-1].sec;
				if(p1<p2) cout<<i<<" "<<p1<<" "<<p2<<endl;
//				cout<<pos<<" "<<val.sec<<endl;
			}
		}
		for(int id:q[i]){
			rep(j,1,k[id]){
				ans[id]=max(ans[id],sq[j].ask(l[id],i));
			}
		}
	}
	rep(i,1,m){
		cout<<ans[i].sec<<endl;
		write(sum[r[i]]*inv(sum[l[i]-1])%MOD*inv(ans[i].fir)%MOD,endl);
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

