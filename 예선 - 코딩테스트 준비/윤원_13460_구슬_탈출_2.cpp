#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

char board[10][10];

int answer = 9999999;

pair<int, int> Red;
pair<int, int> Blue;
pair<int, int> Hole;

bool T_end = false;
bool F_end = false;

// ������
void print_board() {
	cout << "\n��������\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << board[i][j];
		}
		cout << "\n";
	}
}

// ���� ������� ��
pair< pair<int, int>, pair<int, int>> up(int nCount, pair<int, int> Reds, pair<int, int> Blues);

// �Ʒ��� ������� ��
pair< pair<int, int>, pair<int, int>> down(int nCount, pair<int, int> Reds, pair<int, int> Blues);

// �������� ������� ��
pair< pair<int, int>, pair<int, int>> left(int nCount, pair<int, int> Reds, pair<int, int> Blues);

// ���������� ������� ��
pair< pair<int, int>, pair<int, int>> right(int nCount, pair<int, int> Reds, pair<int, int> Blues);

void recursion(int nCount, pair<int, int> Reds, pair<int, int> Blues);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'R') {
				Red.first = i;
				Red.second = j;
			}
			else if (board[i][j] == 'B') {
				Blue.first = i;
				Blue.second = j;
			}
			else if (board[i][j] == 'O') {
				Hole.first = i;
				Hole.second = j;
			}
		}
	}
	
//	print_board();

	pair< pair<int, int>, pair<int, int>> a;

	recursion(0, Red, Blue);
	if (answer == 9999999) cout << -1;
	else cout << answer;
	return 0;
}

void recursion(int nCount, pair<int, int> Reds, pair<int, int> Blues) {

	if (nCount > 10) return;

	pair< pair<int, int>, pair<int, int>> a;

	a = up(nCount+1, Reds, Blues);

	if (a.first.first != -1) {
		recursion(nCount + 1, a.first, a.second);
	}

	a = down(nCount + 1, Reds, Blues);
	
	if (a.first.first != -1) {
		recursion(nCount + 1, a.first, a.second);
	}

	a = left(nCount + 1, Reds, Blues);

	if (a.first.first != -1) {
		recursion(nCount + 1, a.first, a.second);
	}
	
	a = right(nCount + 1, Reds, Blues);
  
	if (a.first.first != -1) {
		recursion(nCount + 1, a.first, a.second);
	}
}

// ���� ������� ��
pair< pair<int, int>, pair<int, int>> up(int nCount, pair<int, int> Reds, pair<int, int> Blues) {

	if (nCount > 10) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		return a;
	}

	int r_y = Reds.first; int r_x = Reds.second;
	int b_y = Blues.first; int b_x = Blues.second;

	// R�� ���� �������� -> '#'�� ���Ë����� ����
	while (board[r_y][r_x] != '#') {
		// �߰��� 'O'�� ������ true��
		if (board[r_y][r_x] == 'O') {
			T_end = true;
			break;
		}
		r_y--;
	}
	r_y++;

	// B�� ���� �������� -> '#'�� ���Ë����� ����
	while (board[b_y][b_x] != '#') {
		// �߰��� 'O'�� ������ false��
		if (board[b_y][b_x] == 'O') {
			F_end = true;
			break;
		}
		b_y--;
	}
	b_y++;

	if (F_end == true) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		F_end = false; T_end = false;
		return a;
	}
	else if (T_end == true) {
		answer = min(nCount, answer);
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		T_end = false;
		return a;
	}

	// ���� ��ĥ ���
	if (r_y == b_y && r_x == b_x) {
		if (abs(r_y - Reds.first) > abs(b_y - Blues.first)) r_y++;
		else b_y++;
	}
	   	
	pair<pair<int, int>, pair<int, int>> a({ r_y, r_x }, { b_y, b_x });
	return a;
}


// �Ʒ��� ������� ��
pair< pair<int, int>, pair<int, int>> down(int nCount, pair<int, int> Reds, pair<int, int> Blues) {

	if (nCount > 10) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		return a;
	}

	int r_y = Reds.first; int r_x = Reds.second;
	int b_y = Blues.first; int b_x = Blues.second;

	// R�� �Ʒ��� �������� -> '#'�� ���Ë����� ����
	while (board[r_y][r_x] != '#') {
		// �߰��� 'O'�� ������ true��
		if (board[r_y][r_x] == 'O') {
			T_end = true;
			break;
		}
		r_y++;
	}
	r_y--;

	// B�� �Ʒ��� �������� -> '#'�� ���Ë����� ����
	while (board[b_y][b_x] != '#') {
		// �߰��� 'O'�� ������ false��
		if (board[b_y][b_x] == 'O') {
			F_end = true;
			break;
		}
		b_y++;
	}
	b_y--;

	if (F_end == true) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		F_end = false; T_end = false;
		return a;
	}
	else if (T_end == true) {
		answer = min(nCount, answer);
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		T_end = false;
		return a;
	}

	// ���� ��ĥ ���
	if (r_y == b_y && r_x == b_x) {
		if (abs(r_y - Reds.first) > abs(b_y - Blues.first)) r_y--;
		else b_y--;
	}

	pair<pair<int, int>, pair<int, int>> a({ r_y, r_x }, { b_y, b_x });
	return a;
}

// �������� ������� ��
pair< pair<int, int>, pair<int, int>> left(int nCount, pair<int, int> Reds, pair<int, int> Blues) {

	if (nCount > 10) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		return a;
	}

	int r_y = Reds.first; int r_x = Reds.second;
	int b_y = Blues.first; int b_x = Blues.second;

	// R�� �������� �������� -> '#'�� ���Ë����� ����
	while (board[r_y][r_x] != '#') {
		// �߰��� 'O'�� ������ true��
		if (board[r_y][r_x] == 'O') {
			T_end = true;
			break;
		}
		r_x--;
	}
	r_x++;

	// B�� �������� �������� -> '#'�� ���Ë����� ����
	while (board[b_y][b_x] != '#') {
		// �߰��� 'O'�� ������ false��
		if (board[b_y][b_x] == 'O') {
			F_end = true;
			break;
		}
		b_x--;
	}
	b_x++;

	if (F_end == true) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		F_end = false; T_end = false;
		return a;
	}
	else if (T_end == true) {
		answer = min(nCount, answer);
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		T_end = false;
		return a;
	}

	// ���� ��ĥ ���
	if (r_y == b_y && r_x == b_x) {
		if (abs(r_x - Reds.second) < abs(b_x - Blues.second)) b_x++;
		else r_x++;
	}

	pair<pair<int, int>, pair<int, int>> a({ r_y, r_x }, { b_y, b_x });
	return a;
}


// ���������� ������� ��
pair< pair<int, int>, pair<int, int>> right(int nCount, pair<int, int> Reds, pair<int, int> Blues) {

	if (nCount > 10) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		return a;
	}

	int r_y = Reds.first; int r_x = Reds.second;
	int b_y = Blues.first; int b_x = Blues.second;

	// R�� ���������� �������� -> '#'�� ���Ë����� ����
	while (board[r_y][r_x] != '#') {
		// �߰��� 'O'�� ������ true��
		if (board[r_y][r_x] == 'O') {
			T_end = true;
			break;
		}
		r_x++;
	}
	r_x--;

	// B�� ���������� �������� -> '#'�� ���Ë����� ����
	while (board[b_y][b_x] != '#') {
		// �߰��� 'O'�� ������ false��
		if (board[b_y][b_x] == 'O') {
			F_end = true;
			break;
		}
		b_x++;
	}
	b_x--;

	if (F_end == true) {
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		F_end = false; T_end = false;
		return a;
	}
	else if (T_end == true) {
		answer = min(nCount, answer);
		pair<pair<int, int>, pair<int, int>> a({ -1, -1 }, { -1, -1 });
		T_end = false;
		return a;
	}

	// ���� ��ĥ ���
	if (r_y == b_y && r_x == b_x) {
		if (abs(r_x - Reds.second) < abs(b_x - Blues.second)) b_x--;
		else r_x--;
	}

	pair<pair<int, int>, pair<int, int>> a({ r_y, r_x }, { b_y, b_x });
	return a;
}