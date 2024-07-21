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

const int MX = 1e6;

const int seed = 123456789;
const int conf[7][4]={
					{0,0,1,1},
					{MX,(int)1e5,0,2},
					{MX,10000,0,2},
					{MX,1000,0,2},
					{MX,100,0,2},
					{MX,10,0,2},
					{MX,1,0,2},
					};

std::mt19937_64 rng(seed);
uniform_int_distribution<int> dist(0,INT_MAX);
streambuf* orig_cout_buf = cout.rdbuf();
ofstream file;

int random(int lb,int ub){
	return dist(rng)%(ub-lb+1)+lb;
}

VI random_array(int n,int sum){
	VI num(n);
	rep(i,0,n-2){
		num[i]=sum/n;
	}
	num[n-1]=sum-sum/n*(n-1);
	rep(i,1,n-1){
		int j=random(0,i-1);
		int tmp=num[i]+num[j];
		num[i]=random(1,tmp-1);
		num[j]=tmp-num[i];
	}
	return num;
}

void init(int id){
	char cmd[100];
	sprintf(cmd,"data/hhpc1p1.%d.in",id);
	file.open(cmd);
	cout.rdbuf(file.rdbuf());
}

void solve(int n,int tt=0){
	int tp;
	if(n>=100&&tt!=1){
		if(n<=10000)
			tp=random(1,5);
		else{
			tp=5;
		}
	}
	else{
		tp=random(1,4);
	}
	if(tp==1){
		rep(i,1,n){
			cout<<(char)('a'+random(0,25));
		}
	}
	else if(tp==2){
		char lst=' ';
		rep(i,1,n){
			char res='a'+random(0,25);
			while(res==lst) res='a'+random(0,25);
			cout<<res;
		}
	}
	else if(tp==3){
		char a='a'+random(0,25);
		rep(i,1,n){
			if(random(1,10)==1){
				cout<<(char)('a'+random(0,25));
			}
			else cout<<a;
		}
	}
	else if(tp==4){
		char a='a'+random(0,25);
		rep(i,1,n){
			cout<<a;
		}
	}
	else{
		VI split=random_array(n/20,n);
		for(int x:split){
			solve(x,1);
		}
	}
}

void data(int id,int Case,int subcase){
	init(id);
	int tp=conf[Case][2];
	if(tp==1){
		cout<<4<<endl;
		cout<<3<<endl;
		cout<<"abc"<<endl;
		cout<<6<<endl;
		cout<<"utgggg"<<endl;
		cout<<5<<endl;
		cout<<"eeeee"<<endl;
		cout<<11<<endl;
		cout<<"oowooowoooo"<<endl;
	}
	else{
		int T=conf[Case][1];
		int SUM=conf[Case][0];
		cout<<T<<endl;
		VI N=random_array(T,SUM);
		rep(i,0,T-1){
			cout<<N[i]<<endl;
			solve(N[i]);
			cout<<endl;
		}
	}
}

void answer(int id){
    cout.rdbuf(orig_cout_buf);
    file.close();
	char cmd1[100];
	sprintf(cmd1,"validator.exe < data/hhpc1p1.%d.in",id,id);
    system(cmd1);
	char cmd2[100];
	sprintf(cmd2,"std.exe < data/hhpc1p1.%d.in > data/hhpc1p1.%d.out",id,id);
    system(cmd2);
}

inline void SOLVE(){
	int id=1;
    for(int Case=0;Case<7;Case++){
    	for(int i=0;i<conf[Case][3];i++){
			cout<<"=============== test case #"<<id<<" ==============="<<endl;
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

