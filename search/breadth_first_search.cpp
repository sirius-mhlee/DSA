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
#include <queue>

using namespace std;

class breadth_first_search {
public:
    int vertex_count; // 그래프의 정점 수

    vector<bool> visited; // 각 정점의 방문 여부를 저장하는 벡터
    vector<vector<int>> adj; // 그래프의 인접 리스트 (각 정점에 연결된 정점들의 목록)

public:
    // 주어진 정점 수에 따라 visited와 인접 리스트를 초기화
    breadth_first_search(int _vertex_count)
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

    // 시작 정점(start)에서 목표 정점(end)까지의 최단 경로의 깊이를 계산하는 함수
    int process(int start, int end) {
        if (start < 0 || start >= vertex_count || end < 0 || end >= vertex_count) return -1; // 인덱스가 유효하지 않으면 -1 반환
        if (start == end) return 0; // 시작 정점과 목표 정점이 같으면 0 반환

        visited.assign(vertex_count, false); // 방문 여부를 모두 false로 초기화

        queue<pair<int, int>> q; // pair<int, int>: first는 현재 정점, second는 시작 정점부터 현재 정점까지의 깊이(거리)
        q.push(make_pair(start, 0)); // 시작 정점을 큐에 삽입, 깊이는 0부터 시작
        visited[start] = true; // 시작 정점을 방문한 것으로 표시
        while (!q.empty()) { // 큐가 빌 때까지 반복
            // 큐의 front 요소에서 현재 정점과 깊이를 가져옴
            int curr = q.front().first;
            int curr_depth = q.front().second;
            q.pop(); // 처리한 요소 제거

            if (curr == end) return curr_depth; // 만약 목표 정점에 도달했다면 현재까지의 깊이를 반환

            for (int next : adj[curr]) { // 현재 정점과 인접한 모든 정점을 순회
                if (!visited[next]) { // 아직 방문하지 않은 정점이라면
                    q.push(make_pair(next, curr_depth + 1)); // 다음 정점을 큐에 추가하면서 깊이를 1 증가시킴
                    visited[next] = true;  // 해당 정점을 방문 처리
                }
            }
        }
        return -1; // 목표 정점에 도달할 수 없으면 -1 반환
    }
};

// 사용 예시:
// int main() {
//     int N = 5;  // 그래프의 정점 수
//     breadth_first_search bfs(N);
//
//     // 정점 간 무방향 간선 생성
//     bfs.create_edge(0, 1);
//     bfs.create_edge(0, 2);
//     bfs.create_edge(1, 3);
//     bfs.create_edge(2, 3);
//     bfs.create_edge(3, 4);
//
//     // 정점 0에서 4까지의 최단 경로 깊이를 계산
//     int ret_depth = bfs.process(0, 4);
//     cout << "최단 경로의 깊이: " << ret_depth << endl;
//
//     return 0;
// }