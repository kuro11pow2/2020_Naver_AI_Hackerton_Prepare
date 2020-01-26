#include <iostream> 
#include <string>

using namespace std;

string ARR; // 현재 확인 중인 수열
int ARR_LEN; // 만들 수열 길이

int is_good_arr_len(string arr) {

	int now_len = arr.length();
	if (now_len == 1) { // arr의 길이가 1개면 무조건 좋은 수열
		return true;
	}
	if (now_len == 2) { // 2개면 
		if (arr[0] == arr[1]) {
			return false;
		}
		return true;
	}

	int max_check_len = now_len / 2;

	for (int check_len = 1; check_len <= max_check_len; check_len++) { // 길이가 check_len인 경우에

		int max_idx = now_len - check_len*2; // max_idx 미만까지 확인.
		for (int offset = 0; offset <= max_idx; offset++) { // 시작에서 offset 만큼 떨어진 곳에서 부터 존재할 수 있다.

			int same_count = 0; // 현재 offset에서 모든 쌍이 같은지 확인. 전부 같으면 나쁜 수열
			for (int count = 0; count < check_len; count++) { // check_len개의 쌍을 비교해야 한다.

				if (arr[offset + count] == arr[offset + count + check_len]) { // 쌍 중에 같은 것이 개수를 센다.
					same_count++;
				}
			}

			if (same_count == check_len) { // 모든 쌍이 같으면
				return false; // 나쁜 수열이다.
			}
		}
	}
	return true; // 모든 테스트를 통과하면 좋은 수열이다.

}

int find() { 
	if (ARR.length() == ARR_LEN) {// 수열 완성됨. 출력하고 끝.
		cout << ARR;
		return 1;
	}
	for (int i = 1; i <= 3; i++) { // 작은 수부터 뒤에 넣어서
		string tmp_arr = ARR;
		tmp_arr.push_back(i + '0');
		if (is_good_arr_len(tmp_arr)) { // 좋은 수열이 된다면
			ARR = tmp_arr;
			if (find()) // 재귀. 찾았으면
				return 1; // 빠져나가기
		}
		else {
			if (i == 3) { // 1, 2, 3 다 넣는데도 하나도 안 되면 마지막거 빼고 위로 올라가야함.
				ARR.pop_back();
				return 0;
			}
			// 나쁜 수열이된다면 다음 수로 해보기.
		}
	}
}

int main() {
	cin >> ARR_LEN;
	find();
	return 0;
}