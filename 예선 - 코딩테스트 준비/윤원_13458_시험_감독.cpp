#include <iostream>
using namespace std;

// 응시생들을 모두 감독하기 위해 필요한 감독관의 최소 수를 계산하는 함수
void calculate(int N, int *A, int B, int C, long long &result);

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;	// 시험장의 개수
	int A[1000001];	// 각 시험장에 있는 응시자의 수를 저장하는 배열
	int B;	// B는 총감독관이 한 방에서 감시할 수 있는 응시자의 수
	int C;	// C는 부감독관이 한 방에서 감시할 수 있는 응시자의 수
	long long result = 0; // 최종 결과를 나타내는 값, 즉 필요한 감독관의 최소 수

	cin >> N;	// 시험장의 개수 입력을 받는다.

	// 각 시험장에 있는 응시자의 수를 입력받기 위해, 동적 할당
	// index를 1부터 시작하는 것이 좀 더 편하므로 크기를 N+1로 할당
	// A = new int[N+1]; 

	// index는 1부터 시작, A[0]은 사용하지 않는다.
	for (int i = 1; i <= N; i++)
	{
		cin >> A[i];
	}
	
	// 총감독관이 감시할 수 있는 응시자 수와 부감독관이 감시할 수 있는 응시자 수를 입력받는다.
	cin >> B >> C;

	// 여기에 응시생들을 모두 감독하기 위해 필요한 감독관의 최소 수를 계산하는 과정이 들어갑니다.
	calculate(N, A, B, C, result);

	// 최종 결과 출력
	cout << result;
	return 0;
}

// 여기에 응시생들을 모두 감독하기 위해 필요한 감독관의 최소 수를 계산하는 과정이 들어갑니다.
void calculate(int N, int *A, int B, int C, long long &result)
{
	// 우선 모든 시험장에 총감독관은 오직 1명만 있어야 하므로, 
	// 필요한 총감독관의 수는 시험장의 수와 같다.
	result = result + N;

	// 총감독관이 한 방에서 감시할 수 있는 응시자의 수가 B명이므로,
	// A배열에 있는 학생 수에서 B를 뺸다
	// 그렇게 하면 남은 학생은 부감독관이 감시해야 한다.
	for (int i = 1; i <= N; i++)
	{
		A[i] = A[i] - B;
	}

	// 남은 학생은 부감독관이 감시해야 한다.
	// 각 배열을 탐색하면서 필요한 부감독관의 수를 계산하고
	// 그때마다 result를 1 증가시킨다.
	for (int i = 1; i <= N; i++)
	{
		if (A[i] <= 0) // 부감독관이 필요 없는 경우
			continue;
		
		// 1명의 부감독관이 감시할 수 있는 응시자의 수를 뺀다.
		// A[i]/C 한 값은 올림으로 처리되어야 한다.
		result = result + (A[i] / C);

		if (A[i] % C != 0) // 만약 A[i]를 C로 나눈 나머지가 0이 아니라면 +1을 함으로써 올림처리
			result++;
	}
}
