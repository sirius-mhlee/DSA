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

#include <vector>

using namespace std;

class depth_first_search {
public:
    int vertex_count; // 그래프의 정점 수

    vector<bool> visited; // 방문한 정점을 추적하는 벡터
    vector<vector<int>> adj; // 그래프의 인접 리스트 표현

public:
    // 주어진 정점 수로 그래프를 초기화하는 생성자
    depth_first_search(int _vertex_count)
        : vertex_count(_vertex_count), visited(_vertex_count, false), adj(_vertex_count) {
    }

public:
    // 두 정점 사이에 무방향 간선을 생성하는 함수
    void create_edge(int from, int to) {
        if (from >= 0 && from < vertex_count &&
            to >= 0 && to < vertex_count) { // 인덱스가 유효한지 확인
            adj[from].push_back(to);
            adj[to].push_back(from);
        }
    }

    // DFS 과정을 시작하고 연결된 컴포넌트 수를 세는 함수
    int process() {
        int result = 0; // 연결된 컴포넌트 수를 초기화
        for (int i = 0; i < vertex_count; i++) {
            if (!visited[i]) { // 정점이 방문되지 않았다면 새로운 DFS 시작
                inner_process(i);
                result++; // 연결된 컴포넌트 수 증가
            }
        }
        return result; // 총 연결된 컴포넌트 수 반환
    }

private:
    // 주어진 정점에서 DFS를 수행하는 재귀 함수
    void inner_process(int curr) {
        visited[curr] = true; // 현재 정점을 방문으로 표시
        for (int next : adj[curr]) { // 모든 인접 정점을 순회
            if (!visited[next]) { // 인접 정점이 방문되지 않았다면 재귀 호출
                inner_process(next);
            }
        }
    }
};

// 사용 예시:
// int main() {
//     int N = 5; // 정점 수
//     depth_first_search dfs(N);
//
//     dfs.create_edge(0, 1);
//     dfs.create_edge(1, 2);
//     dfs.create_edge(3, 4);
//
//     int ret_count = dfs.process();
//     cout << "연결된 컴포넌트 수: " << ret_count << endl;
//
//     return 0;
// }