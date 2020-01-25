// #define DEBUG

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int table[101][101] = { 0, };
int answer = 0;

// d�� ����
// 0 : ������	(x��ǥ ����)
// 1 : ��		(y��ǥ ����)
// 2 : ����		(x��ǥ ����)
// 3 : �Ʒ�		(y��ǥ ����)
// 0->1->2->3�� ��� �ð� ����

/*

0����    1����    2����            3����
������ / ���� / ���� ���� / ���� �Ʒ��� ���� ����

0     / 1    /  2    1  /   2    3     2    1


0���� 0
1���� 1 (+1)
2����� 0���� + 1���� reverse �׷��� 0 1 -> 1 0 ���⿡ ��� +1 ���� -> 2 1
< 2���� ���� >
0 1
1 0 + 1 �� -> 2 1

3����� 0���� + 1���� + 2���� reverse �׷��� 0 1 2 1 �ݴ�� 1 2 1 0 ���⿡ ��� +1 ���� -> 2 3 2 1
< 3���� ���� >
0 1 2 1 �ݴ��
1 2 1 0 + 1�� -> 2 3 2 1
*/

void DP(int x, int y, int d, int g) {
	int r_x = x;
	int r_y = y;
	int r_d = d;
	vector<int> direction;
	vector<int> original;

	// �������� 0���� 1�� ����
	table[r_x][r_y]++;
#ifdef DEBUG
	cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
	// index : 0    1    2    3    4 ... -> ���븦 �ǹ�
	// count : 1 -> 1 -> 2 -> 4 -> 8 ... -> �̵� Ƚ���� �ǹ�
	int count = 1;
	for (int i = 0; i < g + 1; i++) {

		if (i == 0) { // 0������ ���
			original.push_back(r_d);
#ifdef DEBUG
			cout << "direction size: " << original.size() << endl;
			cout << "0 is this: " << original[0] << endl;
#endif
			for (int j = 0; j < count; j++) {

				switch (r_d) {
				case 0:	// ������ (x��ǥ ����)
					r_x++;
					break;
				case 1:	// ���� (y��ǥ ����)
					r_y--;
					break;
				case 2: // ���� (x��ǥ ����)
					r_x--;
					break;
				case 3: // �Ʒ��� (y��ǥ ����)
					r_y++;
					break;
				}

				table[r_x][r_y]++;
#ifdef DEBUG
				cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
			}

		}
		else if (i == 1) { // 1������ ���
			r_d++;
			if (r_d > 3) r_d = 0;
			original.push_back(r_d);
#ifdef DEBUG
			cout << "direction size: " << original.size() << endl;
			cout << "1 is this: " << original[1] << endl;
#endif
			for (int j = 0; j < count; j++) {

				switch (r_d) {
				case 0:	// ������ (x��ǥ ����)
					r_x++;
					break;
				case 1:	// ���� (y��ǥ ����)
					r_y--;
					break;
				case 2: // ���� (x��ǥ ����)
					r_x--;
					break;
				case 3: // �Ʒ��� (y��ǥ ����)
					r_y++;
					break;
				}

				table[r_x][r_y]++;
#ifdef DEBUG
				cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
			}

		}
		else {	// 2���� �̻��� ���
			count = pow(2,i-1);
			direction.clear();
			for (int j = 0; j < original.size(); j++) {
				direction.push_back(original[j]);
			}

			reverse(direction.begin(), direction.end());
#ifdef DEBUG
			cout << i << " is this: ";
#endif
			for (int j = 0; j < direction.size(); j++) {
				direction[j]++;
				if (direction[j] > 3) direction[j] = 0;
				original.push_back(direction[j]);
#ifdef DEBUG
				cout << direction[j] << " ";
#endif
			}
#ifdef DEBUG
			cout << "\n";
#endif
			for (int j = 0; j < count; j++) {

				switch (direction[j]) {
				case 0:	// ������ (x��ǥ ����)
					r_x++;
					break;
				case 1:	// ���� (y��ǥ ����)
					r_y--;
					break;
				case 2: // ���� (x��ǥ ����)
					r_x--;
					break;
				case 3: // �Ʒ��� (y��ǥ ����)
					r_y++;
					break;
				}

				table[r_x][r_y]++;
#ifdef DEBUG
				cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
			}

		}


	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	int x, y, d, g;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;	// (x,y), d�������� ����, g���븸ŭ ����
		DP(x, y, d, g);
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			// 4���� �������� ���� ��� �����ִٸ� +1
			if (table[i][j] != 0 && table[i][j + 1] != 0 && table[i + 1][j] != 0 && table[i + 1][j + 1] != 0)
				answer++;
#ifdef DEBUG
			if (table[i][j] != 0) {
				answer++;
			}
#endif
		}
	}

	cout << answer;
	return 0;
}