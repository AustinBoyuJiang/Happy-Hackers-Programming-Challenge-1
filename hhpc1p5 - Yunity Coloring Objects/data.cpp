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

const int N1 = 1e4;
const int Q1 = 2e3;
const int N3 = 1e5;
const int seed = 123456789;
const int conf[9][5]={{0,2,N1,Q1,0},//subtask1
					{1,2,N1,Q1,0},
					{2,2,N1,Q1,0},
					{0,2,N3,N3,1},//subtask2
					{1,2,N3,N3,1},
					{2,2,N3,N3,1},
					{0,2,N3,N3,0},//subtask3
					{1,2,N3,N3,0},
					{2,2,N3,N3,0}};
int n,m;

std::mt19937_64 rng(seed);
uniform_int_distribution<int> dist(0,INT_MAX);
streambuf* orig_cout_buf = cout.rdbuf();
ofstream file;

int random(int lb,int ub){
	return dist(rng)%(ub-lb+1)+lb;
}

void init(int id){
	char cmd[100];
	sprintf(cmd,"data/hhpc1p5.%d.in",id);
	file.open(cmd);
	cout.rdbuf(file.rdbuf());
}

PI gen_pair(){
	int s,t;
	s=random(1,n);
	do{
		t=random(1,n);
	} while(s==t);
	return make_pair(s,t);
}

void data(int Case){
	int subcase=conf[Case][0];
	int rep=conf[Case][4];
	if(subcase==0){
		n=random(1,conf[Case][2]);
		m=random(1,conf[Case][3]);
	}
	else{
		n=conf[Case][2];
		m=conf[Case][3];
	}
	cout<<n<<" "<<m<<endl;
	map<PI,bool> flag;
	if(subcase==2){
		int d=min(n,(int)sqrt(m*2));
		int st=random(1,n-d+1);
		VPI query;
		rep(i,st,st+d-1){
			rep(j,i+1,st+d-1){
				flag[{i,j}]=1;
				flag[{j,i}]=1;
				if(random(0,1)) query.pb({i,j});
				else query.pb({j,i});
			}
		}
		if(rep==0){
			random_shuffle(all(query));
			while(query.size()<m){
				query.pb(query[random(0,query.size()-1)]);
				if(random(0,1)){
					swap(query[query.size()-1].fir,query[query.size()-1].sec);
				}
			}
		}
		else{
			while(query.size()<m){
				PI pr;
				do{
					pr=gen_pair();
				} while(flag[pr]);
				flag[pr]=1;
				flag[{pr.sec,pr.fir}]=1;
				query.pb(pr);
			}
			random_shuffle(all(query));
		}
		for(PI q:query){
			cout<<q.fir<<" "<<q.sec<<endl;
		}
	}
	else{
		VPI query;
		int a=random(0,m),b=m-a;
		if(rep) a=m,b=0;
		if(a<b) swap(a,b);
		rep(i,1,a){
			PI pr;
			do{
				pr=gen_pair();
			} while(flag[pr]);
			flag[pr]=1;
			flag[{pr.sec,pr.fir}]=1;
			query.pb(pr);
		}
		random_shuffle(all(query));
		rep(i,0,b-1){
			query.pb({query[i].sec,query[i].fir});
		}
		random_shuffle(all(query));
		for(PI q:query){
			cout<<q.fir<<" "<<q.sec<<endl;
		}
	}
}

void answer(int id){
    cout.rdbuf(orig_cout_buf);
    file.close();
//	char cmd1[100];
//	sprintf(cmd1,"validator.exe < data/hhpc1p5.%d.in",id,id);
//    system(cmd1);
	char cmd2[100];
	sprintf(cmd2,"std.exe < data/hhpc1p5.%d.in > data/hhpc1p5.%d.out",id,id);
    system(cmd2);
}

inline void SOLVE(){
	int id=1;
    for(int Case=0;Case<9;Case++){
    	for(int i=0;i<conf[Case][1];i++){
    		init(id);
    		data(Case);
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

