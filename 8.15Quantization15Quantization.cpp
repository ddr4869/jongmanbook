#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include <string>
using namespace std;
const int INF = 987654321;
int n, s;
// A:수열, pSum:A[]의 부분합 저장, pSqSum:A[]제곱의 부분합 저장
int A[101], pSum[101], pSqSum[101];
int cache[101][11];

//A를 정렬하고 각 부분합을 계산
void precalc() {
	sort(A, A + n);
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	for (int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
	}
}

//A[lo]..A[hi]구간을 하나의 숫자로 표현할 때 최소오차값 계산
int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
	int m = int(0.5 + (double)sum / (hi - lo + 1));
	int ret = sqSum - 2 * m*sum + m * m*(hi - lo + 1);
	return ret;
}

int quantize(int from, int parts) {
	if (from == n)return 0;
	if (parts == 0)return INF;
	int &ret = cache[from][parts];
	if (ret != -1)return ret;
	ret = INF;
	for (int partSize = 1; from + partSize <= n; partSize++)
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	return ret;
}

int main() {
	memset(cache, -1, sizeof(cache));
	cin >> n >> s;
	for (int i = 0; i < n; i++)
		cin >> A[i];
	precalc();
	cout << quantize(0, s) << endl;
	return 0;
}
