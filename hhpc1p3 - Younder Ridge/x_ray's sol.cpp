#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define ppi pair<int, pair<int, int>>
#define pll pair<ll, ll>

typedef long long ll;
typedef long double ld;

using namespace std;

signed main() {
	cin.sync_with_stdio(NULL); cin.tie(NULL);
	// Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki Orz butsurizuki
	int n, q, k; ll m; cin >> n >> m >> q >> k;
	vector<ll> A(n+1), B(n+1), V(n+1);
	for(int i = 1; i <= n; i++) cin >> A[i] >> B[i] >> V[i];
	vector<vector<pll>> leftSurpass(n+1), rightSurpass(n+1);
	vector<ll> buf(n+1);
	for(int i = 1; i <= n; i++) for(int j = i+1; j <= n; j++) {
		if(A[i] == A[j] && B[i] == B[j]) continue;
		if(A[i] >= A[j] && B[i] >= B[j]) buf[j] += V[i];
		else if(A[i] <= A[j] && B[i] <= B[j]) buf[i] += V[j];
		else {
			if(A[i] >= A[j] && B[i] <= B[j]) { //A beats B
				//(m-s)*A[i]+s*B[i] > (m-s)*A[j]+s*B[j]
				//m*(A[i]-A[j]) > s*(B[j]-B[i]+A[i]-A[j])
				//s < m*(A[i]-A[j])/(A[i]-B[i]+B[j]-A[j])
				rightSurpass[i].push_back(mp(m*(A[i]-A[j])/(A[i]-B[i]+B[j]-A[j])+1, V[j])); //ge
				leftSurpass[j].push_back(mp(m*(A[i]-A[j])/(A[i]-B[i]+B[j]-A[j])-((m*(A[i]-A[j]) % (A[i]-B[i]+B[j]-A[j])) ? 0 : 1), V[i])); //le
			} else {
				assert(A[i] <= A[j] && B[i] >= B[j]);
				rightSurpass[j].push_back(mp(m*(A[j]-A[i])/(A[j]-B[j]+B[i]-A[i])+1, V[i])); //ge
				leftSurpass[i].push_back(mp(m*(A[j]-A[i])/(A[j]-B[j]+B[i]-A[i])-((m*(A[j]-A[i]) % (A[j]-B[j]+B[i]-A[i])) ? 0 : 1), V[j])); //le
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		leftSurpass[i].push_back(mp(-1, 0));
		leftSurpass[i].push_back(mp(m+1, 0));
		rightSurpass[i].push_back(mp(-1, 0));
		rightSurpass[i].push_back(mp(m+1, 0));
		sort(leftSurpass[i].begin(), leftSurpass[i].end());
		for(int j = 1; j < leftSurpass[i].size(); j++) leftSurpass[i][j].second += leftSurpass[i][j-1].second;
		sort(rightSurpass[i].begin(), rightSurpass[i].end());
		for(int j = 1; j < rightSurpass[i].size(); j++) rightSurpass[i][j].second += rightSurpass[i][j-1].second;
	}
	for(int i = 1, p, s; i <= q; i++){
		cin >> p >> s;
		ll cnt = buf[p]+(--(leftSurpass[p].end()))->second-(--lower_bound(leftSurpass[p].begin(), leftSurpass[p].end(), mp((ll) s, (ll) -1)))->second+(--lower_bound(rightSurpass[p].begin(), rightSurpass[p].end(), mp((ll) s+k+1, (ll)-1)))->second;
		cout << cnt << "\n"; 
	}
}

