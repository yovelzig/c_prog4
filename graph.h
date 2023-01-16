
typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
    pnode source;
    struct edge_ *nextB;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    int distance;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;
// void shortsPath_cmd(pnode head);
void delete_node_cmd(pnode *head);
void deleteGraph_cmd(pnode *head);
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void free_edges(pnode edge_fr);
pnode new_node(int num, struct GRAPH_NODE_ *next);
pnode findNode(int name, pnode *head);
pnode findNodePrev(int name, pnode *head);
void add_Edge(int weight, pnode src_node, pnode dst_node);
pedge newEdge(int weight, pnode endpoint);
void free_node(pnode delete_node);
void free_edgeFrom(pnode *head, pnode des_point);
void shortsPath_cmd(pnode head);