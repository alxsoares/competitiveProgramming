#include <cstdio>

using namespace std;

const int NN = 100;
int t[NN * 4], v[NN * 4], h[NN * 4], a[NN], n;

void build (int i = 1, int l = 0, int r = n - 1)
{
	if (l == r)
		t[i] = a[l];
	else
	{
		int m = (l + r) / 2;
		build (i + i, l, m);
		build (i + i + 1, m + 1, r);
	}
}

void update (int l, int r, int d, int i = 1, int tl = 0, int tr = n - 1)
{
	if (l == tl && r == tr)
		h[i] = 1, v[i] = d;
	else 
	{
		if (h[i])
		{
			h[i] = 0;
			h[i+i] = h[i+i+1] = 1;
			v[i+i] = v[i+i+1] = v[i];
		}
		int m = (tl + tr) / 2;
		if (r <= m)
			update (l, r, d, i + i, tl, m);
		else if (l > m)
			update (l, r, d, i + i + 1, m + 1, tr);
		else
		{
			update (l, m, d, i + i, tl, m);
			update (m + 1, r, d, i + i + 1, m + 1, tr);
		}
		t[i] = h[i+i] * v[i+i] * (m - l + 1) + 
			   !h[i+i] * t[i+i] + !h[i+i+1] * t[i+i+1] +
			   h[i+i+1] * v[i+i+1] * (r - m);
	}
}

int getsum (int l, int r, int i = 1, int tl = 0, int tr = n - 1)
{
	if (h[i])
		return v[i] * (r - l + 1);
	if (tl == l && tr == r)
		return t[i];
	int m = (tl + tr) / 2;
	if (r <= m)
		return getsum(l, r, i + i, tl, m);
	if (l > m)
		return getsum(l, r, i + i + 1, m + 1, tr);
	return getsum(l, m, i + i, tl, m) + getsum(m + 1, r, i + i + 1, m + 1, tr);
}

int main ()
{
	scanf ("%d", &n);
	for(;;)
	{
		int A, B, C;
		scanf("%d", &C);
		if (C)
		{
			puts("update");
			scanf("%d%d%d", &A, &B, &C);
			update(A,B,C);
		}
		else
		{
			puts("sum");
			scanf ("%d%d", &A, &B);
			printf("%d\n", getsum(A, B));
		}
	}
	return 0;
}
