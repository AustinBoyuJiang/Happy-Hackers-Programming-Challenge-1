/*
 * Author: Austin Jiang
 * Date: 10/11/2023 9:48:21 PM
 * Problem: Yonder Ridge
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
#define INTTOLL

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
//namespace FastIO{
//	inline int read() {int x=0; bool f=0; char ch=0; while(!isdigit(ch)) f=ch=='-',ch=getchar(); while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return f?-x:x;}
//	inline ll readLL() {ll x=0; bool f=0; char ch=0; while(!isdigit(ch)) f=ch=='-',ch=getchar(); while(isdigit(ch)) x=x*10+ch-'0',ch=getchar(); return f?-x:x;}
//	inline int read(int &x) {return x=read();}
//    template<class T> inline void write(T x) {if(x<0) x=-x,putchar('-'); if(x>9) write(x/10); putchar(x%10+'0');}
//	template<class T> inline void write(T x,char ch) {write(x),putchar(ch);}
//} using namespace FastIO;

void SETUP(){
	#ifdef FASTIO
	cin.tie(nullptr)->sync_with_stdio(false);
	#endif
	#ifdef READLOCAL
	freopen("in.txt","r",stdin);
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

class BaseReader {
  const static size_t MAX_TOKEN_SIZE = 1e7;

private:
  FILE *stream;

  bool hasLast;
  char lastChar;

public:
  BaseReader(FILE *f) : stream(f), hasLast(false), lastChar(0) {}

  BaseReader(const char *path) : BaseReader(fopen(path, "r")) {}

protected:
  char rawPeekChar() {
    if (!hasLast) {
      lastChar = getc(stream);
      hasLast = true;
    }
    return lastChar;
  }

  char rawReadChar() {
    char ret = rawPeekChar();
    hasLast = false;
    return ret;
  }
  bool eof() { return rawPeekChar() == char_traits<char>::eof(); }

public:
  ll readInt(ll lo = numeric_limits<ll>::min(),
             ll hi = numeric_limits<ll>::max()) {
    try {
      ll ret = convertIntegerToken(readToken());
      if (ret < lo || ret > hi)
        internalRangeError();
      return ret;
    } catch (const out_of_range &e) {
      externalRangeError();
    }
    throw runtime_error("We should never get here");
  }

private:
  ll convertIntegerToken(const string &token) {
    if (token.size() == 0)
      invalidIntegerError();
    if (token == "0")
      return 0;

    size_t i = 0;
    if (token[0] == '-') {
      ++i;
      if (token.size() == 1)
        invalidIntegerError();
    }

    if (token[i] > '9' || token[i] < '1')
      invalidIntegerError();
    ++i;

    for (; i < token.size(); ++i) {
      if (token[i] > '9' || token[i] < '0')
        invalidIntegerError();
    }

    return stoll(token);
  }

public:
  char readChar(char min_char = 0, char max_char = 127) {
    preReadChar();
    char c = rawReadChar();
    if (c > max_char || c < min_char) {
      internalRangeError();
    }
    return c;
  }

  string readToken(char min_char = 0, char max_char = 127) {
    preReadToken();
    string token;
    while (!isspace(rawPeekChar()) && !eof() &&
           token.size() <= MAX_TOKEN_SIZE) {
      token.push_back(readChar(min_char, max_char));
    }
    return token;
  }

  char peekChar() {
    preReadChar();
    return rawPeekChar();
  }

  string readString(int N, char min_char = 0, char max_char = 127) {
    preReadString();
    string ret;
    ret.reserve(N);
    for (int i = 0; i < N; ++i) {
      ret.push_back(readChar(min_char, max_char));
    }
    return ret;
  }

private:
  template <typename Iter> void _fill_arr(Iter it, size_t N, ll lo, ll hi) {
    for (size_t i = 0; i < N; i++) {
      if (i)
        readSpace();
      *it = readInt(lo, hi);
      ++it;
    }
    readNewLine();
  }

public:
  template <size_t length, typename T = ll>
  array<T, length> readIntTuple(ll lo = numeric_limits<ll>::min(),
                                ll hi = numeric_limits<ll>::max()) {
    array<T, length> res;
    _fill_arr(res.begin(), length, lo, hi);
    return res;
  }

  template <typename T = ll>
  pair<T, T> readIntPair(ll lo = numeric_limits<ll>::min(),
                         ll hi = numeric_limits<ll>::max()) {
    T a = readInt(lo, hi);
    readSpace();
    T b = readInt(lo, hi);
    readNewLine();
    return {a, b};
  }

  template <typename T = ll>
  T readSingleInt(ll lo = numeric_limits<ll>::min(),
                  ll hi = numeric_limits<ll>::max()) {
    T x = readInt(lo, hi);
    readNewLine();
    return x;
  }

  template <typename T = ll>
  vector<T> readIntArray(size_t N, ll lo = numeric_limits<ll>::min(),
                         ll hi = numeric_limits<ll>::max()) {
    vector<T> v;
    v.reserve(N);
    _fill_arr(back_inserter(v), N, lo, hi);
    return v;
  }

  template <typename T = ll>
  pair<vector<T>, int>
  readIntArrayOrFlag(size_t N, ll lo = numeric_limits<ll>::min(),
                     ll hi = numeric_limits<ll>::max(), T flag = -1) {
    T first = readInt();
    if (first == flag) {
      readNewLine();
      return {vector<T>(), -1};
    }

    if (lo > first || first > hi) {
      internalRangeError();
      throw runtime_error("We should never get here");
    } else {
      vector<T> v;
      v.reserve(N);
      v.push_back(first);
      if (N > 1) {
        readSpace();
      }
      _fill_arr(back_inserter(v), N - 1, lo, hi);
      return {v, N};
    }
  }

  template <typename T, typename... Ts> void readInts(T &arg, Ts &&...args) {
    arg = readInt();
    readSpace();
    readInts(args...);
  }

  template <typename T> void readInts(T &arg) {
    arg = readInt();
    readNewLine();
  }

  virtual ~BaseReader() {}

protected:
  virtual void preReadToken() {}
  virtual void preReadString() { preReadToken(); }
  virtual void preReadChar() { preReadToken(); }
  virtual void internalRangeError() = 0;
  virtual void externalRangeError() = 0;
  virtual void invalidIntegerError() = 0;
  virtual void wrongWhitespaceError() = 0;

public:
  virtual void readNewLine() = 0;
  virtual void readSpace() = 0;
};

template <typename Parent> class ExactWhitespaceMixin : public Parent {
  void readEOF() {
    if (!Parent::eof())
      Parent::wrongWhitespaceError();
  }

public:
  void readNewLine() override {
    if (Parent::rawReadChar() != '\n')
      Parent::wrongWhitespaceError();
  }

  void readSpace() override {
    if (Parent::rawReadChar() != ' ')
      Parent::wrongWhitespaceError();
  }

  ~ExactWhitespaceMixin() { readEOF(); }

  using Parent::Parent;
};

void assert_permutation(const vector<int> &arr) {
  vector<int> check(arr.size(), 0);
  assert(std::all_of(arr.begin(), arr.end(), [&check](int x) { return ++check[x - 1] == 1; }));
}

class validator_out_of_range {};
class wrong_whitespace {};
class invalid_integer {};

class ValidatingReaderBase : public BaseReader {
protected:
  void externalRangeError() override { throw validator_out_of_range(); }
  void internalRangeError() override { throw validator_out_of_range(); }
  void wrongWhitespaceError() override { throw wrong_whitespace(); }
  void invalidIntegerError() override { throw invalid_integer(); }

public:
  using BaseReader::BaseReader;
};

using ValidatingReader = ExactWhitespaceMixin<ValidatingReaderBase>;

ValidatingReader in_r(stdin);

/* ========================================| Main Program |======================================== */

const int N = 5010;
const int Q = 5e5+10;

int x,k,n,q,a[N],b[N],c[N],base[N],ans[Q];
VPI query[N],u[N],d[N];

inline void SOLVE(int Case){
	in_r.readInts(n,x,q,k);
	assert(n>=1&&n<=5e3);
	assert(1<=k&&k<=x&&x<=1e9);
	assert(q>=1&&q<=5e5);
	rep(i,1,n){
		in_r.readInts(a[i],b[i],c[i]);
		assert(a[i]>=-1e9&&a[i]<=1e9);
		assert(b[i]>=-1e9&&b[i]<=1e9);
		assert(c[i]>=1&&c[i]<=1e9);
	}
	rep(i,1,q){
		int id,s;
		in_r.readInts(id,s);
		assert(id>=1&&id<=n);
		assert(s>=0&&s<=x-k);
		query[id].pb({s,i});
	}
	rep(i,1,n){
		rep(j,1,n){
			if(i==j) continue;
			if(b[i]-a[i]==b[j]-a[j]){
				if(a[j]>a[i]){
					base[i]+=c[j];
				}
				continue;
			}
			int dpos=(a[j]-a[i])*x/(b[i]-a[i]-b[j]+a[j]);
			int upos=((a[j]-a[i])*x+b[i]-a[i]-b[j]+a[j]-1)/(b[i]-a[i]-b[j]+a[j]);
			if(b[i]-a[i]<b[j]-a[j]) u[i].pb({dpos,c[j]});
			if(b[i]-a[i]>b[j]-a[j]) d[i].pb({upos,c[j]});
		}
		sort(all(query[i]));
		sort(all(u[i]));
		sort(all(d[i]));
	}
	rep(i,1,n){
		int j1=0,j2=0,res=base[i];
		for(PI dd:d[i]) res+=dd.sec;
		for(PI ask:query[i]){
			while(j1<u[i].size()&&u[i][j1].fir<ask.fir+k){
				res+=u[i][j1].sec;
				j1++;
			}
			while(j2<d[i].size()&&d[i][j2].fir<=ask.fir){
				res-=d[i][j2].sec;
				j2++;
			}
			ans[ask.sec]=res;
		}
	}
	rep(i,1,q){
		cout<<ans[i]<<endl;
	}
	in_r.~ExactWhitespaceMixin();
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

