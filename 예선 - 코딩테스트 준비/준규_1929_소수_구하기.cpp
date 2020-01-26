#pragma warning(disable:4996)

#include <iostream>

int M, N, S, P[79000]; // 출력할 소수 범위 (최소, 최대), 소수 배열 크기, 소수 배열

int main(void) {
	scanf("%d%d", &M, &N);
	for (int T = 2; T <= N; T++) {  // 2이상 최대 이하의 모든 수 T에 대하여
		for (int I = 0; T == 2 || I < S; I++) { // 지금까지 알아낸 모든 소수로 나누어 본다. 나눌 수 P[I]
			if (T == 2 || P[I] * P[I] > T) { // P[I]^2 > T 가 성립하면 
				P[S++] = T; // 발견하지 못한 소수이므로 배열에 넣고 배열 크기 키우고
				if (T >= M && T <= N) // 출력 범위 내에 있으면 출력하고
					printf("%d\n",T);
				break; // 다음 수를 판정한다
			}
			if (T % P[I] == 0) // 나누어 떨어지면 소수가아니므로
				break; // 다음 수를 판정한다.
		}
	}
	return 0;
}