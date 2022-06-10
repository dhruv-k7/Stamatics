#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <string>

using namespace std;

vector<int> parent;
vector<int> sz;
vector<int> Rank;

int find(int p)
{
    int root = p;
    while (root != parent[root])
        root = parent[root];

    while (p != root)
    {
        int temp = parent[p];
        parent[p] = root;
        p = temp;
    }
    return root;
}
void unifyByRank(int p, int q)
{
    int root1 = find(p);
    int root2 = find(q);

    if (root1 == root2)
        return;
    if (Rank[root1] < Rank[root2])
    {
        sz[root2] += sz[root1];
        parent[root1] = root2;
        Rank[root2]++;
    }
    else
    {
        sz[root1] += sz[root2];
        parent[root2] = root1;
        Rank[root1]++;
    }
}
void unifyBySize(int p, int q)
{
    int root1 = find(p);
    int root2 = find(q);

    if (root1 == root2)
        return;

    if (sz[root1] < sz[root2])
    {
        sz[root2] += sz[root1];
        parent[root1] = root2;
    }
    else
    {
        sz[root1] += sz[root2];
        parent[root2] = root1;
    }
}
struct unionFind
{
    int n, m;
    unionFind()
    {
        cin >> n >> m;
        parent = vector<int>(n);
        sz = vector<int>(n, 1);
        Rank = vector<int>(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
        cin.ignore();
        for (int i = 0; i < m; i++)
        {
            string s;
            getline(cin, s);
            if (s[0] == 'u')
            {
                int a = s[6] - '1';
                int b = s[8] - '1';
                //uncomment one of the following respectively for performing union by rank(default) or union by size:
                unifyByRank(a, b);
                // unifyBySize(a,b);
            }
            else
            {
                int a = s[4] - '1';
                int b = s[6] - '1';

                if (find(a) == find(b))
                {
                    cout << "YES" << endl;
                }
                else
                {
                    cout << "NO" << endl;
                }
            }
        }
    }
};

void cuttingGraph()
{

    int n, m, k;
    cin >> n >> m >> k;
    parent = vector<int> (n);
    sz = vector<int> (n,0);
    vector<vector<int>> adj(n,vector<int> (n));
    for (int i = 0; i < n; i++)
        parent[i] = i;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a][b] = 1;
        adj[b][a] = 1;
        unifyBySize(a,b);
    }
    cin.ignore();
    for(int i=0;i<k;i++){
        string s;
        getline(cin,s);
        int u = s[4] - '1';
        int v = s[6] - '1';
        if(s[0] == 'a'){
            if(find(u) == find(v))
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
        else{
            if(find(u) != find(v))
                continue;
            adj[u][v] = 0;
            adj[v][u] = 0;
            parent[u] = u;
            parent[v] = v;
            for(int i=0;i<n;i++){
                if(adj[u][i] == 1){
                    unifyBySize(u,i);
                }
                if(adj[v][i] == 1){
                    unifyBySize(v,i);
                }
            }
        }
    }
}

struct Edge
{
    int u, v, weight;
    bool operator<(Edge const &other)
    {
        return weight < other.weight;
    }
};

void spanningTree()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);

    int cost = 0;
    vector<int> tree_id(n);
    for (int i = 0; i < n; i++)
        tree_id[i] = i;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i].u = a - 1;
        edges[i].v = b - 1;
        edges[i].weight = c;
    }

    sort(edges.begin(), edges.end());

    for (Edge e : edges)
    {
        if (tree_id[e.u] != tree_id[e.v])
        {
            cost += e.weight;
            int old_id = tree_id[e.u], new_id = tree_id[e.v];
            for (int i = 0; i < n; i++)
            {
                if (tree_id[i] == old_id)
                    tree_id[i] = new_id;
            }
        }
    }
    cout << cost << endl;
}

vector<int> arr;
int lsb(int x){
    return x & -x;
}

long long int prefixSum(int i){
    long long int sum = 0;
    while(i > 0){
        sum += arr[i];
        i -= lsb(i);
    }
    return sum;
}
long long int sum(int a,int b){
    return prefixSum(b)-prefixSum(a-1);
}
void add(int k,int x){
    while(k<arr.size()){
        arr[k] += x;
        k += lsb(k);
    }
}
void set(int k,int u){
    long long int value = sum(k,k);
    int x = u- value;
    while(k<arr.size()){
        arr[k] += x;
        k += lsb(k);
    }
}

void DynamicRangeSumQueries(){
    int n,q;
    cin>>n>>q;
    arr = vector<int>(n+1);
    for(int i=1;i<n+1;i++)
        cin>>arr[i];
    for(int i=1;i<n+1;i++){
        int j = i+ lsb(i);
        if(j<n+1){
            arr[j] += arr[i];
        }
    }
    for(int i=0;i<q;i++){
        int x;
        cin>>x;
        if(x == 1){
            int k,u;
            cin>>k>>u;
            set(k,u);
        }   
        else{
            int a,b;
            cin>>a>>b;
            cout<<sum(a,b)<<endl;
        }
    }
}

void RangeUpdateQueries(){
    int n,q;
    cin>>n>>q;
    arr = vector<int>(n+1);
    for(int i=1;i<n+1;i++)
        cin>>arr[i];
    for(int i=0;i<q;i++){
        int x;
        cin>>x;
        if(x == 1){
            int a,b,u;
            cin>>a>>b>>u;
            add(a,u);
            add(b+1,-u);
        }
        else{
            int k;
            cin>>k;
            cout<<sum(1,k)<<endl;
        }
    }
    
}
    
int main()
{
    //Uncomment only one of the following for respective question and provide the respective input.
    //Using more than one functions at once may lead to wrong answers.

    //Q1
    // unionFind();

    //Sample input:
    // 4 4
    // union 1 2
    // union 1 3
    // get 1 4
    // get 2 3


    //Q2
    // cuttingGraph();

    //Sample input:
    // 3 3 7
    // 1 2
    // 2 3
    // 3 1
    // ask 3 3
    // cut 1 2
    // ask 1 2
    // cut 1 3
    // ask 2 1
    // cut 2 3
    // ask 3 1


    //Q3
    // spanningTree();

    //Sample input:
    // 4 4
    // 1 2 1
    // 2 3 2
    // 3 4 5
    // 4 1 4


    //Q4
    // DynamicRangeSumQueries();

    //Sample input:
    // 8 4
    // 3 2 4 5 1 1 5 3
    // 2 1 4
    // 2 5 6
    // 1 3 1
    // 2 1 4


    //Q5
    // RangeUpdateQueries();

    //Sample input:
    // 8 3
    // 3 2 4 5 1 1 5 3
    // 2 4
    // 1 2 5 1
    // 2 4

    return 0;
}