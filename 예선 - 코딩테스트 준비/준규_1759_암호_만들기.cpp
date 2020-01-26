#define DEBUG_PRINT if (false)

#include <iostream>

using namespace std;

char psw_char[15]; // 암호로 사용될 수 있는 문자들
char selected[15]; // 암호로 선택된 글자들
int sel_num; // 선택된 글자 수
int aeiou; // 선택된 모음수
int not_aeiou; // 자음수
int L_psw_len;
int C_char_num;

int choose_char(int min) { // 암호를 선택한다. min은 선택 가능한 psw_char에서의 최하 idx를 뜻한다.
	int max = C_char_num - (L_psw_len - sel_num - 1); // 전체 문자 중에서 남은 뽑을 수 있는 문자 수만큼은 남겨놔야함. 뒤쪽 친구들도 뽑아야 하니까

	if (sel_num >= L_psw_len) { // 탐색 완료
		if (aeiou >= 1 && not_aeiou >= 2) { // 출력 조건
			for (int i = 0; i < sel_num; i++) {
				cout << selected[i];
			}
			cout << '\n';
		}
		return 2;
	}
	
	if (max > C_char_num) { // 탐색 불가능 루트
		return 1;
	}
	for (int i = min; i < max; i++) {
		int result;
		selected[sel_num++] = psw_char[i];
		if (psw_char[i] == 'a' || psw_char[i] == 'e' || psw_char[i] == 'i' || psw_char[i] == 'o' || psw_char[i] == 'u')
			aeiou++;
		else
			not_aeiou++;
		DEBUG_PRINT cout << "i: " << i << ", psw_char[i]: " << psw_char[i] << endl;
		result = choose_char(i + 1); // 선택한 문자의 다음 문자부터 다시 선택
		if (result >= 0) { // 스택에서 하나 빼는 것과 같음.
			int rmv = selected[sel_num - 1];
			selected[--sel_num] = '\0';
			if (rmv == 'a' || rmv == 'e' || rmv == 'i' || rmv == 'o' || rmv == 'u')
				aeiou--;
			else
				not_aeiou--;
		}
	}
	return 0; // ?
}

int main(void) {

	cin >> L_psw_len >> C_char_num;
	
	for (int i = 0; i < C_char_num; i++) { // 암호 문자 입력 받기 
		cin >> psw_char[i];
	}

	for (int i = 0; i < C_char_num - 1; i++) { // 정렬 먼저 하기
		for (int j = i+1; j < C_char_num; j++) {
			if (psw_char[i] > psw_char[j]) { // 오름차순으로 정렬
				char tmp = psw_char[i];
				psw_char[i] = psw_char[j];
				psw_char[j] = tmp;
			}
		}
	}
	DEBUG_PRINT for (int i = 0; i < C_char_num; i++) { // 암호 문자 입력 받기 
		cout << psw_char[i];
		if (i == C_char_num - 1)
			cout << '\n';
	}
	
	choose_char(0);

	return 0;
}