#include <bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define y second
const int N = 1e5 + 3;

bool used[N];
vector<pair<int, int>> g[N];

/*
 *алгоритм Прима
 * Изначально остов — одна произвольная вершина.
 * Пока минимальный остов не найден, выбирается ребро минимального веса,
 * исходящее из какой-нибудь вершины текущего остова в вершину,
 * которую мы ещё не добавили. Добавляем это ребро в остов и начинаем
 * заново, пока остов не будет найден.
 */

// O(nm)
int mst() {
    used[0] = true;
    int wt = 0;
    for (int i = 1; i < N; ++i) {
        int min_ed = 1e12, min_v = -1, min_u = -1;
        for (int u = 0; u < N; ++u) {
            if (!used[u]) continue;
            for (auto &p : g[u]) {
                if (used[p.x]) continue;
                if (min_ed > p.y) {
                    min_ed = p.y;
                    min_v = p.x;
                    min_u = u;
                }
            }
        }
        wt += min_ed;
        used[min_v] = true;
        // {min_u, min_v} in mst
    }
    return wt;
}

// O(m log(n))
int mst() {
    used[0] = true;
    int wt = 0;
    set<pair<int, pair<int, int>>> st;  //{вес, {откуда, куда}}
    for (auto &p : g[0]) {              // изначальная инициализация
        st.insert({p.y, {0, p.x}});
    }
    for (int i = 1; i < N; ++i) {
        int min_ed = st.begin()->x;   // вес минимального ребра
        int min_v = st.begin()->y.x;  // откуда
        int min_u = st.begin()->y.y;  // куда

        wt += min_ed;        // увеличиваем ответ
        used[min_u] = true;  // {min_u, min_v} in mst

        for (auto &p : g[min_u]) {  // обновляем st
            if (used[p.x]) {
                // !если это ребро между вершинами множества
                st.erase({p.y, {p.x, min_u}});
            } else {
                //! если ребро в вершину не из множества
                st.insert({p.y, {min_u, p.x}});
            }
        }
    }
    return wt;
}

/*
 * Алгоритм Краскала
 * отсортировать все ребра и пытаться добавлять их в изначально пустой
 *  остов в порядке возрастания их весов.
 */

