#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<climits>

using namespace std;

int n,m;
vector<vector<int>> adj;
vector<int> vis;

//Part 1
vector<int> topological(){
    vector<int> deg(n,0);
    for(int i=0;i<n;i++){
        for(auto j: adj[i]){
            deg[j]++;
        }
    }

    queue<int> q;

    for(int i=0;i<n;i++){
        if(deg[i] == 0){
            q.push(i);
        }
    }
    int ind = 0;
    vector<int> sorted(n,0);
    
    while(!q.empty()){
        int x = q.front();
        q.pop();
        sorted[ind] = x;
        ind++;
        for(auto j: adj[x]){
            deg[j]--;
            if(deg[j] == 0){
                q.push(j);
            }
        }
    }
    
    if(ind != n){
        return vector<int> (0);
    }
    return sorted;
}

vector<int> check;
vector<int> lengths;

//Part 2
int countPaths(int s, int d, int length){
    if (s == d){
        lengths.push_back(length);
        return 1;
    }
    if (check[s] != -1){   
        length++;
        lengths.push_back(length);
        return check[s];
    }
 
    int c = 0;
    for (int& k : adj[s]) {
        long x = countPaths(k, d, length+1);
        if (x != -1) {
            c = c + x;
        }
    }
    
   check[s] = c;
   if(c == 0){
       return -1;
   }
   else{
       return c;
   }
}
int Paths(int u, int v){
    
    check = vector<int> (10000000,-1);
    int c = countPaths(u, v, 0);
 
    if (c == -1)
        return 0;
 
    return c;
}

int id = 0;
int scc = 0;
int sccid = 1;
stack<int> s;
vector<int> ids;
vector<int> low;
vector<int> onstack;

//Part 3
void dfs(int node){
    s.push(node);
    onstack[node] = 1;
    ids[node] = id;
    low[node] = id;
    id++;
    for(auto x: adj[node]){
        if(ids[x] == 0){
            dfs(x);
        }
        if(onstack[x] == 1){
            if(low[x]<low[node])
                low[node] = low[x];
        }
    }
    if(ids[node] == low[node]){
        while(!s.empty()){
            int a = s.top();
            s.pop();
            onstack[a] = 0;
            low[a] = sccid;
            if(node == a){
                break;
            }
        }
        scc++;
        sccid++;
    }

}
vector<int> sccs(){
    for(int i=0;i<n;i++){
        if(ids[i] == 0){
            dfs(i);
        }
    }
    return low;
}


int tval[1000000];
vector<int> adj2[1000000], adj3[1000000];
vector<int> v;
bool vis2[1000000];

//Part 4
void dfs2(int s){
    if(vis2[s]) 
        return;
    vis2[s]=1;
    for(auto i: adj2[s]) 
        dfs2(i);
    v.push_back(s);
}
int k=0;
int comp[1000000];
void dfs3(int s){
    if(vis2[s]) 
        return;
    vis2[s]=1;
    comp[s]=k;
    for(auto i: adj3[s]){
        dfs3(i);
    }
}
void sat2(){
    int n,m;
    cin>>n>>m;
    //2sat
    for(int i=0;i<n;i++){
        char x,y;
        int a,b;
        cin>>x>>a>>y>>b;
        if(x=='-')
            a=2*m-a+1;
        if(y=='-') 
            b=2*m-b+1;
        adj2[2*m-a+1].push_back(b);
        adj2[2*m-b+1].push_back(a);
        adj3[a].push_back(2*m-b+1);
        adj3[b].push_back(2*m-a+1);
    }
    for(int i = 1;i<2*m+1;i++){
        if(!vis2[i]) 
            dfs2(i);
    }
    for(int i=0;i<1000000;i++){
        vis2[i]=0;
    }
    for (auto i=v.rbegin();i!=v.rend();i++){
        int x = *i;
        if(!vis2[x]){
            k++;
            dfs3(x);
        }
    }
    for(int i = 1;i<m+1;i++){
        if (comp[i]==comp[2*m-i+1]){
            cout<<"IMPOSSIBLE";
            return;
        }
        if(comp[i]>comp[2*m-i+1])
            tval[i] = 1;
        else
            tval[i] = 0;
    }
    for(int i = 1;i<m+1;i++){
        if(tval[i] == 1){
            cout<<'+';
        }
        else{
            cout<<'-';
        }
    }
}



int main(){
    
    //Uncomment the following line for 4th question of the assignment
    // sat2();


    //Uncomment the below part for first 3 questions of the assignment

    cin>>n>>m;
    ids = vector<int> (n,0);
    low = vector<int> (n,0);
    onstack = vector<int> (n,0);
    adj = vector<vector<int>> (n);
    vis = vector<int> (n,0);
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
    }

    //Calculating and printing topologically sorted vector:

    // vector<int> topo = topological();
    // cout<<"Topological sorted :"<<endl;
    // for(auto i: topo){
    //     cout<<i<<" ";
    // }
    // cout<<endl;

    //Calculating and printing number of paths, shortest path length, longest path length

    // int u,v;
    // cin>>u>>v;
    // cout<<"Number of paths = "<<Paths(u,v)<<endl;
    // sort(lengths.begin(), lengths.end());
    // int slength = lengths[0];
    // int llength = lengths[lengths.size()-1];
    // cout<<"Length of shortest path = "<<slength<<endl;
    // cout<<"Length of longest path = "<<llength<<endl;

    //Calculating sccs and printing all the sccs(unique id) that each node belongs to:

    // vector<int> Scc = sccs();
    // cout<<"Number of sccs = "<<scc<<endl;
    // cout<<"Id of each node :"<<endl;
    // for(auto i: Scc){
    //     cout<<i<<" ";
    // }


    return 0;
}