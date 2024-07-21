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

const int N = 5e5;
const int N2 = 5e3;
const int Q = 5e5;
const int A = 1e6;
int a[N+10];
const int seed = 123456789;
const int conf[11][4]={{6,10,0,2},//subcase 1
					{6,10,1,2},
					{6,10,2,2},
					{N2,A,0,1},
					{N2,A,2,2},
					{N2,A,3,1},
					{N2,A,5,1},
					{N,A,4,5}, //subcase 2
					{N,A,0,1},
					{N,A,2,2},
					{N,A,3,1}};

std::mt19937_64 rng(seed);
uniform_int_distribution<int> dist(0,INT_MAX);
streambuf* orig_cout_buf = cout.rdbuf();
ofstream file;

int random(int lb,int ub){
	return dist(rng)%(ub-lb+1)+lb;
}

void init(int id){
	char cmd[100];
	sprintf(cmd,"data/hhpc1p2.%d.in",id);
	file.open(cmd);
	cout.rdbuf(file.rdbuf());
}

void data(int id,int Case,int subcase){
	init(id);
	int tp=conf[Case][2];
	if(tp==4){
		int n=conf[Case][0];
		int q=1;
		cout<<n<<" "<<q<<endl;
		int l=random(1,n);
		int r=random(1,n);
		if(r<=l) swap(l,r);
		rep(i,1,n){
			a[i]=random(-conf[Case][1],conf[Case][1]);
		}
		if(subcase==1){
			rep(i,l,r){
				while(a[i]==0) a[i]=random(-conf[Case][1],conf[Case][1]);
			}
			int x=random(l,r);
			int y=random(l,r);
			while(x==y) y=random(l,r);
			a[x]=-a[y];
		}
		else if(subcase==2){
			int k=random(-conf[Case][1],conf[Case][1]);
			while(k==0) k=random(-conf[Case][1],conf[Case][1]);
			rep(i,l,r){
				a[i]=k;
			}
		}
		else if(subcase==3){
			a[random(l,r)]=0;
		}
		else if(subcase==4){
			map<int,bool> flag;
			flag[0]=1;
			rep(i,l,r){
				while(flag[a[i]]) a[i]=random(-conf[Case][1],conf[Case][1]);
				flag[-a[i]]=1;
			}
		}
		rep(i,1,n-1){
			cout<<a[i]<<" ";
		}
		cout<<a[n]<<endl;
		cout<<l<<" "<<r<<endl;
		return;
	}
	int n=conf[Case][0];
	int q;
	if(n<=20) q=n*(n+1)/2;
	else q=conf[Case][0];
	cout<<n<<" "<<q<<endl;
	if(tp==0){
		rep(i,1,n){
			a[i]=random(-conf[Case][1],conf[Case][1]);
		}
	}
	else if(tp==1){
		if(subcase==0){
			a[1]=-1;
			a[2]=2;
			a[3]=2;
			a[4]=2;
			a[5]=1;
			a[6]=0;
		}
		else{
			a[1]=0;
			a[2]=-4;
			a[3]=-4;
			a[4]=6;
			a[5]=6;
			a[6]=4;
		}
	}
	else if(tp==2){
		int mid=random(2,n-1);
		int aa=random(1,mid-1);
		aa=random(1,aa);
		int bb=random(mid+1,n);
		bb=random(bb,n);
		int k=random(-conf[Case][1],conf[Case][1]);
		rep(i,1,aa) a[i]=k;
		rep(i,bb,n) a[i]=-k;
		rep(i,aa+1,bb-1) a[i]=random(-conf[Case][1],conf[Case][1]);
		a[mid]=0;
	}
	else if(tp==5){
		int k=random(-conf[Case][1],conf[Case][1]);
		rep(i,1,n){
			a[i]=k;
		}
		rep(i,1,n/5){
			a[random(1,n)]=random(-conf[Case][1],conf[Case][1]);
		}
	}
	else{
		VI mid;
		mid.pb(random(1,n-1));
		mid.pb(random(1,n-1));
		mid.pb(random(1,n-1));
		sort(all(mid));
		int k=random(-conf[Case][1],conf[Case][1]);
		rep(i,1,mid[0]) a[i]=k;
		k=random(-conf[Case][1],conf[Case][1]);
		rep(i,mid[0]+1,mid[1]) a[i]=k;
		k=random(-conf[Case][1],conf[Case][1]);
		rep(i,mid[1]+1,mid[2]) a[i]=k;
		k=random(-conf[Case][1],conf[Case][1]);
		rep(i,mid[2]+1,n) a[i]=k;
	}
	rep(i,1,n-1){
		cout<<a[i]<<" ";
	} cout<<a[n]<<endl;
	VPI query;
	if(n<=1000){
		rep(l,1,n) rep(r,l,n){
			query.pb({l,r});
		}
		random_shuffle(all(query));
	}
	else{
		rep(i,1,q){
			int l=random(1,n);
			int r=random(1,n);
			if(r<l) swap(l,r);
			query.pb({l,r});
		}
	}
	for(PI que:query){
		cout<<que.fir<<" "<<que.sec<<endl;
	}
}

void answer(int id){
    cout.rdbuf(orig_cout_buf);
    file.close();
	char cmd1[100];
	sprintf(cmd1,"validator.exe < data/hhpc1p2.%d.in",id,id);
    system(cmd1);
	char cmd2[100];
	sprintf(cmd2,"std.exe < data/hhpc1p2.%d.in > data/hhpc1p2.%d.out",id,id);
    system(cmd2);
}

inline void SOLVE(){
	int id=1;
    for(int Case=0;Case<11;Case++){
    	for(int i=0;i<conf[Case][3];i++){
    		data(id,Case,i);
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

