# Stamatics
Assignmet 1
Input to be provided: number of nodes(n), number of edges(m), all 'm' edges
Sample inputs:
Sample input 1
6 5
0 1
1 2
2 3
3 1
4 5
Sample input 2
4 4
0 1
1 2
2 3
3 1

Note: Edges entered as input must be from '0' to 'n-1', and do not enter same edge in reverse (provide only of 'u v' or 'v u').

Also, to find distance of a node from node '0', uncomment the respective lines (indicated in the code) and provide a node in the input.

Since the graph is undirected, back_edges and bridges are saved twice as (u,v) and (v,u) to avoid problems while using them later.

Also, two visited vectors are used (vis and vist), firstly in dfs() function and secondly in components() function.
