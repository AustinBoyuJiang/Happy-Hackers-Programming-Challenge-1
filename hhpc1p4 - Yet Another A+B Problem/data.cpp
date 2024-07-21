/*
 * Author: Austin Jiang
 * Date: 10/10/2023 9:48:17 AM
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
	template<class T> inline T inv(T x){return qpow(x,MOD-2);}
	template<class T> inline bool is_prime(T x){
	if(x==1) return false; for(T i=2;i*i<=x;i++) if(x%i==0) return false;return true;}
	template<class T> inline void disc(Vec<T> &v,int st=0){set<int> num;Vec<T> pos;
	for(T x:v)num.insert(x);for(T x:num)pos.pb(x);for(T &x:v) x=lb(all(pos),x)-pos.begin()+st;}
} using namespace Comfun;

/* ========================================| Main Program |======================================== */

const int T1 = 1e3;
const int T2 = 1e5;
const int N1 = 5e4;
const int N2 = 1e7;
const ull seed = 123456789;
const ull conf[11][5]={{T2,2,0,1,0}, // subcase #0
					{1,N1,0,1,0}, // subcase #1
					{1,N1,0,1,1},
					{T1,1,T1,2,2},
					{T1,N1-T1+1,N1,2,2},
					{T1,1,N1,2,3},
					{1,N2,0,1,0}, // subcase #2
					{1,N2,0,1,1},
					{T2,1,T2,2,2},
					{T2,N2-T2+1,N2,2,2},
					{T2,1,N2,2,3}};

std::mt19937_64 rng(seed);
streambuf* orig_cout_buf = cout.rdbuf();
ofstream file;

void init(int id){
	char cmd[100];
	sprintf(cmd,"data/hhpc1p4.%d.in",id);
	file.open(cmd);
	cout.rdbuf(file.rdbuf());
}

void data(int id,int Case){
	init(id);
	int T=conf[Case][0];
	cout<<T<<endl;
	if(conf[Case][1]==2){
		rep(i,1,T){
			cout<<2<<endl;
		}
		return;
	}
	if(conf[Case][4]==0){
		int n=1;
		while(n*2<=conf[Case][1]){
			n*=2;
		}
		cout<<n<<endl;
		return;
	}
	if(conf[Case][4]==1){
		int n=1,cnt=2;
		while(n*cnt<=conf[Case][1]){
			n*=cnt;
			cnt++;
		}
		cout<<n<<endl;
		return;
	}
	if(conf[Case][4]==2){
		VI n;
		rep(i,1,T) n.pb(conf[Case][1]+i-1);
		random_shuffle(all(n));
		for(int x:n){
			cout<<x<<endl;
		}
		return;
	}
	uniform_int_distribution<int> dist(conf[Case][1],conf[Case][2]);
	rep(i,1,T){
		cout<<dist(rng)<<endl;
	}
}

void answer(int id){
    cout.rdbuf(orig_cout_buf);
    file.close();
	char cmd1[100];
	sprintf(cmd1,"validator.exe < data/hhpc1p4.%d.in",id,id);
    system(cmd1);
	char cmd2[100];
	sprintf(cmd2,"std.exe < data/hhpc1p4.%d.in > data/hhpc1p4.%d.out",id,id);
    system(cmd2);
}

inline void SOLVE(){
	int id=1;
    for(int Case=0;Case<11;Case++){
    	for(int i=1;i<=conf[Case][3];i++){
    		data(id,Case);
    		answer(id);
    		id++;
		}
    }
}

/* =====================================| End of Main Program |===================================== */

signed main(){
	SOLVE();
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

