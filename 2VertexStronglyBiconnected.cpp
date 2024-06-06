#include <chrono>
#include <functional>
#include <iostream>
#include <vector>
#include <stack>
#include<fstream>
#include <algorithm>
using namespace std;
using namespace chrono;
//نهاد شريتح
struct Node {
    int id;
    vector<int> neighbors;
};

void addEdge(vector<Node>& graph, int from, int to) {
    graph[from].neighbors.push_back(to);
}

// Gabow Algorithm    
vector<vector<int>> Gabow(vector<Node>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> low(n, 0);
    vector<int> dfn(n, 0);
    stack<int> st;
    int time = 0;
    vector<vector<int>> sccs;

function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        dfn[u] = low[u] = ++time;
        st.push(u);
        for (int v : graph[u].neighbors) {
            if (!visited[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (dfn[v] < low[u]) {
                low[u] = dfn[v];
            }
        }
        if (low[u] == dfn[u]) {
            vector<int> scc;
            while (!st.empty() && st.top() != u) {
                scc.push_back(st.top());
                st.pop();
            }
            scc.push_back(st.top());
            st.pop();
            sccs.push_back(scc);
        }
    };

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    return sccs;
}
//ألاء صبح
//  Jens Schmidt Algorithm  
vector<int>Jens_Schmidt(vector<Node>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> dfsNum(n, 0);
    vector<int> low(n, 0);
    vector<int> parent(n, -1);
    int time = 0;
    vector<int> articulationPoints;
//انس ملحم
    function<void(int, int)> dfs = [&](int u, int p) {
        visited[u] = true;
        dfsNum[u] = low[u] = ++time;
        parent[u] = p;
        int childrenCount = 0;
//ألاء كللي
        for (int v : graph[u].neighbors) {
            if (!visited[v]) {
                childrenCount++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
//أية قرقماز
                if (p != -1 && low[v] >= dfsNum[u]) {
                    articulationPoints.push_back(u);
                }
            } else if (v != p) {
                low[u] = min(low[u], dfsNum[v]);
            }
        }
 //اناس احمد       
        if (p == -1 && childrenCount > 1) {
            articulationPoints.push_back(u);
        }
    };
//ريناد الحسين
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }

    return articulationPoints;
}
int main() {
    //جعفر يوسف
    std::ifstream file("Slashdot0811.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
//يارا كور علي
    std::vector<int> column1;
    std::vector<int> column2;
    int data1;
    int data2;
    while (file >> data1 >> data2) {
        column1.push_back(data1);
        column2.push_back(data2);
}
    file.close();
//صبا زرقة    

 int max=0;
 for (size_t i = 0; i < column1.size(); ++i) {
if(column1[i]>max) max=column1[i];
  if(column2[i]>max) max=column2[i];
 }
    vector <Node> graph(max);
    
    for (size_t i = 0; i < column1.size(); ++i) {
    addEdge(graph,column1[i], column2[i]);
    }
    
//أية العلي 
 vector <int> f;
    auto start = high_resolution_clock::now();
    vector<vector<int>> sccs = Gabow(graph);
        for (size_t i = 0; i < column1.size(); ++i) {
    addEdge(graph,column2[i], column1[i]);
    }
    vector<int> articulationPoints = Jens_Schmidt(graph);
    auto end= high_resolution_clock::now();
    auto duration=duration_cast<seconds>(end-start);
//علي ابراهيم
 if(sccs.size()>= graph.size() && articulationPoints.size()==0) 
 cout<<"is 2-vertext strongly biconnected"<<endl;
 cout<<"Take Time:"<<duration.count();
 
    return 0;
}
