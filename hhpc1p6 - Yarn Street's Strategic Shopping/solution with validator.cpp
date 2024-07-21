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
    template<class T> inline void write(T x) {if(x<0) x=-x,putchar('-'); if(x>9) write(x/10); putchar(x%10+'0');}
	template<class T> inline void write(T x,char ch) {write(x),putchar(ch);}
} using namespace FastIO;

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
  in_r.readInts(n);
  assert(n>=1&&n<=3e5);

  vector<ll> c; // vector<int>
  c=in_r.readIntArray(n);
  F0R(i, n){
  	assert(c[i]>=1&&c[i]<=1e6);
  }
  
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
  in_r.readInts(q);
  assert(q>=1&&q<=5e4);

  vi l(q), r(q), k(q);
  vll out(q); // vector<ll>
  vvi rev(n); // vector<vector<int>>

  F0R(i, 10){
    seg.eb(n);
  }

  F0R(i, q){
  	in_r.readInts(l[i],r[i],k[i]);
  	assert(l[i]>=1);
  	assert(r[i]<=n);
  	assert(l[i]<=r[i]);
  	assert(k[i]>=1&&k[i]<=10);
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
  
	in_r.~ExactWhitespaceMixin();
}

