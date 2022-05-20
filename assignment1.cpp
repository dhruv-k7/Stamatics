#include<iostream>
#include<queue>
#include<vector>
#include<math.h>
using namespace std;

int n,m;
int timer;
int timer2;
vector<vector<int>> adj;    
vector<vector<int>> adjn;    
vector<int> vis;
vector<int> vist;
vector<int> tin;
vector<int> tout;
vector<int> low;
vector<vector<int>> back_edges;
vector<vector<int>> bridges;
vector<vector<int>> comps;
queue<int> dfsarray;

// Function to find dfsarray, back edges and bridges
void dfs(int node, int parent){
    vis[node] = 1;
    tin[node] = timer;
    low[node] = timer++;
    dfsarray.push(node);

    vector<int> :: iterator it;
    for(it = adj[node].begin(); it != adj[node].end(); it++){
        if(*it == parent)
            continue;
        if(vis[*it]){
            back_edges[node][*it] = 1;
            back_edges[*it][node] = 1;
            low[node] = min(low[node], tin[*it]);
        }
        else{
            dfs(*it, node);
            low[node] = min(low[node], low[*it]);
            if(low[*it]>tin[node]){
                bridges[*it][node] = 1;
                bridges[node][*it] = 1;
            }
        }
    }
    tout[node] = timer2++;
}

// Function to return the type of edge (u,v)
char typeofedge(int u,int v){
   if(back_edges[u][v] == 1){
       return 'b';
   }
   else return 'a';
}

// Function to return distance of node s from 0
int distance(int s){
    int dist=0;
    queue<int> tempdfs = dfsarray;
    while(!tempdfs.empty()){
        if(s == tempdfs.front()){
            return dist;
        }
        dist++;
        tempdfs.pop();
    }
    return -1;
}

// Function to find all the connected components
void components(int node, int id){
    if(!vist[node]){
        vist[node] = 1;
        comps[id].push_back(node);
        for(auto i : adj[node]){
            if(!vist[i]){
                components(i,id);
                vist[i] = 1;
            }
        }
    }
    return;
}

// Function to delete all the bridges
void deleteBridges(){
    for(int i=0;i<n;i++){
        vector<int> :: iterator it;
        for(it = adj[i].begin(); it != adj[i].end(); it++){
            if(bridges[i][*it] == 1){
                adj[i].erase(it);
                bridges[i][*it] = 0;
                break;
            }
        }
    }
}


int main(){
    cin>>n>>m;
    timer = 0;
    timer2 = 0;
    adj = vector<vector<int>>(n);
    vis = vector<int>(n,0);
    vist = vector<int>(n,0);
    tin = vector<int>(n,0);
    tout = vector<int>(n,0);
    low = vector<int>(n,0);
    comps = vector<vector<int>>(n);                              // For storing connected components
    back_edges = vector<vector<int>>(n,vector<int>(n));          // For storing all the back edges
    bridges = vector<vector<int>>(n,vector<int>(n));             // For storing all the bridges

    // Storing the adjacency list in a 2D vector adj
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    adjn = adj;                                                  // Copy of adj for ease in deleting bridges
    
    // Printing the given adjacency list
    cout<<"Adjacency list:"<<endl;
     for(int i=0;i<n;i++){
        vector<int> :: iterator it;
        cout<<i<<"->";
        for(auto it = adjn[i].begin(); it != adjn[i].end(); it++){
            cout<<*it<<" ";
        }
        cout<<endl;
    }

    // Specifying type of edge (Tree edge or Back edge) for sample input 0,1
    char toe = typeofedge(0,1);
    if(toe == 'b')
        cout<<"0,1 is a Back edge"<<endl;
    else
        cout<<"0,1 is a Tree edge"<<endl;

    // Printing dfs with starting node 0
    dfs(0, -1);   
    cout<<"DFS:"<<endl;
    queue<int> copydfs = dfsarray;
    while(!copydfs.empty()){
        cout<<copydfs.front()<<" ";
        copydfs.pop();
    }
    cout<<endl;

    // Checking for presence of cycle
    int count = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(back_edges[i][j] == 1){
                count = 1;
                break;
            } 
        }
        if(count == 1)
            break;
    }
    if(count == 1){
        cout<<"Cycle is present"<<endl;
    }
    else{
        cout<<"No cycles are present"<<endl;
    }

    // Printing all the components of the given graph
    int k = 0;
    cout<<"Components:"<<endl;
    for(int i=0;i<n;i++){
        if(!vist[i]){
            k++;
            components(i,k);
            cout<<k<<"= ";
            for(auto j: comps[k]){
                cout<<j<<" ";
            }
         cout<<endl;
        }
    }
    
    // Uncomment the following part to fetch distance of a node from node 0 
    // int s;
    // cin>>s;

    // if(back_edges[0][s] == 1){
    //     cout<<"1"<<endl;
    // }
    // else{
    //     cout<<distance(s)<<endl;
    // }

    // Printing all the bridges present in the graph
    cout<<"Bridges:"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(bridges[i][j] == 1){
                cout<<i<<" "<<j<<endl;
            }
        }
    }

    //Deleting all the above bridges
    while(true){
        int c = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(bridges[i][j] == 1){
                    c++;
                    deleteBridges();
                    bridges[i][j] = 0;
                }
            }
        }
        if(c<=0)
            break;
    }

    // Printing adjacency list after deleting all the bridges
    cout<<"Adjacency list after deleting bridges:"<<endl;
    for(int i=0;i<n;i++){
        vector<int> :: iterator it;
        cout<<i<<"->";
        for(auto it = adj[i].begin(); it != adj[i].end(); it++){
            cout<<*it<<" ";
        }
        cout<<endl;
    }

    return 0;
}