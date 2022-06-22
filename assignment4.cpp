#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

void negCycle(){
    int n;
    int m;
    cin>>n>>m;
    vector<Edge> edges;
    for(int i=0;i<m;i++){
        int a,b,cost;
        cin>>a>>b>>cost;
        Edge x;
        x.a = a;
        x.b = b;
        x.c = cost;
        edges.push_back(x);
    }


    vector<int> d(n);
    vector<int> p(n, -1);
    int x;
    for(int i = 0; i < n; i++){
        x = -1;
        for(Edge e : edges){
            if(d[e.a] + e.c < d[e.b]){
                d[e.b] = d[e.a] + e.c;
                p[e.b] = e.a;
                x = e.b;
            }
        }
    }

    if(x == -1){
        cout << "NO";
    } 
    else{
        for (int i = 0; i < n; ++i)
            x = p[x];

        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());

        cout << "YES"<<endl;
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
    }
}

const int N = 100005;
vector<int> vis(N);
vector<int> dis(N);
priority_queue<pair<int,int>> q;
vector<int> adj2[100005];
vector<vector<int>> adj[100005];
void dij(int s){
    for(int i = 1;i<N;i++) 
        dis[i]=INT_MAX;
    dis[s]=0;
    q.push({0,s});
    while(!q.empty()){
        int a = q.top().second;
        q.pop();
        if (vis[a])
            continue;
        vis[a]=1;
        for (auto X: adj[a]){
            int b = X[0];
            int w = X[1];
            if(dis[a]+w < dis[b]){
                dis[b] = dis[a]+w;
                q.push({-dis[b],b});
            }
        }
    }
}
bool v2[100005];
vector<int> v;
void dfs(int s){
    if(v2[s]) 
        return;
    v2[s]=1;
    for(auto i: adj2[s]) 
        dfs(i);
    v.push_back(s);
}
int path[100005], mx[100005], mn[100005];
void Djikstra(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back({b,w});
    }
    dij(1);
    for(int i=1;i<n+1;i++){
        for (auto X: adj[i]){
            int j = X[0];
            int w = X[1];
            if(dis[j]==dis[i]+w) 
                adj2[j].push_back(i);
        }
    }
    for(int i=1;i<n+1;i++){
        if (!v2[i]) 
            dfs(i);
    }
    vector<int> t; 
    int f=0;
    for(int i=0;i<v.size();i++){
        if(v[i]==1) 
            f=1;
        if(f) 
            t.push_back(v[i]);
    }
    for(int i=1;i<n+1;i++)
        mn[i] = INT_MAX;
    path[1]=1, mx[1]=1, mn[1]=1;
    for (auto i : t){
        for (auto j: adj2[i]){
            path[i] += path[j];
            if(mn[i] > mn[j]+1 && mn[j]) 
                mn[i] = mn[j]+1;
            if(mx[i] < mx[j]+1 && mx[j]) 
                mx[i] = mx[j]+1;
        }
    }
    cout<<dis[n]<<" "<<path[n]<<" "<<mn[n]-1<<" "<<mx[n]-1<<endl;
}


int main(){
    
    // question 1
    // negCycle();

    //question 2
    // Djikstra();

    return 0;
}