#include <iostream>
#include <cassert>
#include <cmath>
#include <complex>
#include <chrono>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false); // C++의 표준 입출력과 C의 표준 입출력을 동기화하지 않음으로써 입출력 성능을 향상시킴
    cin.tie(nullptr); // cin과 cout의 묶음을 풀어줌으로써 입출력 성능을 향상시킴
    cout.tie(nullptr); // cout과 cin의 묶음을 풀어줌으로써 입출력 성능을 향상시킴

    cout.setf(ios::fixed); // 고정 소수점 형식으로 출력 설정
    cout.precision(10); // 소수점 이하 10자리까지 출력 설정

    cout.unsetf(ios::fixed); // 고정 소수점 형식 해제

    return 0;
}