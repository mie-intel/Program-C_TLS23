#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fi first
#define se second

const int maxn = 2e5 + 1;
ll seg[4 * maxn], arr[maxn];

void build(int l, int r, int v){
	if(l == r) seg[v] = arr[l];
	else{
		int m = (l + r)/2;
		build(l, m, 2 * v);
		build(m + 1, r, 2 * v + 1);
		seg[v] = max(seg[2 * v], seg[2 * v + 1]);
	}
}

ll query(int l, int r, int v, int lq, int rq){
	if(lq <= l && r <= rq) return seg[v];
	if(l > rq || r < lq) return LLONG_MIN;
	int m = (l + r)/2;
	return max(query(l, m, 2 * v, lq, rq), query(m + 1, r, 2 * v + 1, lq, rq));
}

void update(int l, int r, int v, ll pos, ll val){
	if(l == r){
		seg[v] = val;
	}
	else{
		int m = (l + r)/2;
		if(pos <= m) update(l, m, 2 * v, pos, val);
		else update(m + 1, r, 2 * v + 1, pos, val);
		seg[v] = max(seg[2 * v], seg[2 * v + 1]);
	}
}

void print(int l, int r, int v){
	if(l == r) cout << seg[v] << " ";
	else{
		int m = (l + r)/2;
		print(l, m, 2 * v);
		print(m + 1, r, 2 * v + 1);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	// cin.tie(0);

	int n;
	cout << "Masukkan ukuran array (maks 200000): ";
	cin >> n;

	cout << "Masukkan array: ";
	for(int a = 1; a <= n; ++a){
		cin >> arr[a];
	}

	build(1, n, 1);

	while(true){
		cout << '\n';
		cout << "Masukkan tipe query!\n";
		cout << "1 untuk query\n";
		cout << "2 untuk update\n";
		cout << "3 untuk keluar\n";
		cout << "~> ";
		int type;
		cin >> type;
		if(type == 1){
			int l, r;
			cout << "Masukkan range (l, r): ";
			cin >> l >> r;
			cout << "Nilai maks dari range " << l << " sampai " << r << " adalah " << query(1, n, 1, l, r) << '\n';
		}
		else if(type == 2){
			int pos; ll val;
			cout << "Masukkan posisi dan value (pos, val): ";
			cin >> pos >> val;
			update(1, n, 1, pos, val);
			cout << "Update posisi array di posisi " << pos << " dengan nilai " << val << '\n';
		}
		else{
			break;
		}
	}

	cout << '\n';
	cout << "Array sekarang\n";
	print(1, n, 1);

	return 0;
}