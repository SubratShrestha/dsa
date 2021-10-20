#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int UNVISITED = -1;
const int V = 8;
const int E = 13;
vector<int> edges[V];

int id = 0;
int sccCount = 0;
int ids[V];
int low[V];
bool onStack[V];
stack<int> stk;
vector<vector<int>> res;

void dfs(int v) {
        stk.push(v);
        onStack[v] = true;
        ids[v] = low[v] = id++;

        // visit all neighbors and min the low-link value on callback.
        for (int to : edges[v]) {
                if (ids[to] == UNVISITED) dfs(to);

                if (onStack[to]) low[v] = min(low[v], low[to]);

                if (ids[v] == low[v]) {
                        vector<int> scc;
                        while (!stk.empty()) {
                                int node = stk.top();
                                stk.pop();
                                scc.push_back(node);
                                onStack[node] = false;
                                low[node] = ids[v]; 
                                if (node == v) break;
                        }
                        res.push_back(scc);
                        sccCount++;
                }
        }
}

//find strongly connected components.
void countScc() {
        for (int i = 0; i < V; i++) ids[i] = UNVISITED;
        for (int i = 0; i < V; i++) {
                if (ids[i] == UNVISITED) {
                        dfs(i);
                }
        }
}
        
        
int main() {
        for (int i = 0; i < E; i++) {
                int u, v;
                cin >> u >> v;
                edges[u].push_back(v);
        }
        countScc();
        printf("number of strongly connected components = %d\n", sccCount);
       
        for (auto vec : res) {
                for (auto i : vec) {
                        printf("%d ", i);
                }
                printf("\n");
        }
}
