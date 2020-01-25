// #define DEBUG

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int table[101][101] = { 0, };
int answer = 0;

// d의 값이
// 0 : 오른쪽	(x좌표 증가)
// 1 : 위		(y좌표 감소)
// 2 : 왼쪽		(x좌표 감소)
// 3 : 아래		(y좌표 증가)
// 0->1->2->3일 경우 시계 방향

/*

0세대    1세대    2세대            3세대
오른쪽 / 위쪽 / 왼쪽 위쪽 / 왼쪽 아래쪽 왼쪽 위쪽

0     / 1    /  2    1  /   2    3     2    1


0세대 0
1세대 1 (+1)
2세대는 0세대 + 1세대 reverse 그래서 0 1 -> 1 0 여기에 모두 +1 적용 -> 2 1
< 2세대 과정 >
0 1
1 0 + 1 씩 -> 2 1

3세대는 0세대 + 1세대 + 2세대 reverse 그래서 0 1 2 1 반대로 1 2 1 0 여기에 모두 +1 적용 -> 2 3 2 1
< 3세대 과정 >
0 1 2 1 반대로
1 2 1 0 + 1씩 -> 2 3 2 1
*/

void DP(int x, int y, int d, int g) {
	int r_x = x;
	int r_y = y;
	int r_d = d;
	vector<int> direction;
	vector<int> original;

	// 시작점을 0에서 1로 변경
	table[r_x][r_y]++;
#ifdef DEBUG
	cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
	// index : 0    1    2    3    4 ... -> 세대를 의미
	// count : 1 -> 1 -> 2 -> 4 -> 8 ... -> 이동 횟수를 의미
	int count = 1;
	for (int i = 0; i < g + 1; i++) {

		if (i == 0) { // 0세대일 경우
			original.push_back(r_d);
#ifdef DEBUG
			cout << "direction size: " << original.size() << endl;
			cout << "0 is this: " << original[0] << endl;
#endif
			for (int j = 0; j < count; j++) {

				switch (r_d) {
				case 0:	// 오른쪽 (x좌표 증가)
					r_x++;
					break;
				case 1:	// 위쪽 (y좌표 감소)
					r_y--;
					break;
				case 2: // 왼쪽 (x좌표 감소)
					r_x--;
					break;
				case 3: // 아래쪽 (y좌표 증가)
					r_y++;
					break;
				}

				table[r_x][r_y]++;
#ifdef DEBUG
				cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
			}

		}
		else if (i == 1) { // 1세대일 경우
			r_d++;
			if (r_d > 3) r_d = 0;
			original.push_back(r_d);
#ifdef DEBUG
			cout << "direction size: " << original.size() << endl;
			cout << "1 is this: " << original[1] << endl;
#endif
			for (int j = 0; j < count; j++) {

				switch (r_d) {
				case 0:	// 오른쪽 (x좌표 증가)
					r_x++;
					break;
				case 1:	// 위쪽 (y좌표 감소)
					r_y--;
					break;
				case 2: // 왼쪽 (x좌표 감소)
					r_x--;
					break;
				case 3: // 아래쪽 (y좌표 증가)
					r_y++;
					break;
				}

				table[r_x][r_y]++;
#ifdef DEBUG
				cout << "table[" << r_x << "][" << r_y << "] = " << table[r_x][r_y] << endl;
#endif
			}

		}
		else {	// 2세대 이상일 경우
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
				case 0:	// 오른쪽 (x좌표 증가)
					r_x++;
					break;
				case 1:	// 위쪽 (y좌표 감소)
					r_y--;
					break;
				case 2: // 왼쪽 (x좌표 감소)
					r_x--;
					break;
				case 3: // 아래쪽 (y좌표 증가)
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
		cin >> x >> y >> d >> g;	// (x,y), d방향으로 시작, g세대만큼 형성
		DP(x, y, d, g);
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			// 4방향 꼭지점에 점이 모두 찍혀있다면 +1
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