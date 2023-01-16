#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <limits.h>

/********************/
// free edges from node
void free_edgeFrom(pnode *head, pnode des_point)
{
    pnode p = *head;
    while (p != NULL)
    {
        pedge e = p->edges;
        if (e != NULL && e->endpoint == des_point)
        {
            pedge curr_e = e;
            p->edges = e->next;
            free(curr_e);
        }
        else
        {
            while (e != NULL && e->next != NULL)
            {
                if (e->next->endpoint == des_point)
                {
                    pedge curr_e = e->next;
                    e->next = e->next->next;
                    free(curr_e);
                }
                else
                {
                    e = e->next;
                }
            }
        }
        p = p->next;
    }
}
/*************************/
// free a node from edges
void free_node(pnode delete_node)
{
    pedge curr_edge = delete_node->edges;
    while (curr_edge != NULL)
    {
        pedge temp = curr_edge;
        curr_edge = curr_edge->next;
        free(temp);
    }
    free(delete_node);
}
/*****************/
// a new edge
pedge newEdge(int weight, pnode endpoint)
{
    pedge p = (pedge)malloc(sizeof(edge));
    if (p == NULL)
    {
        printf("error in allocate memory");
        exit(-1);
    }

    p->endpoint = endpoint;
    p->weight = weight;
    p->next = NULL;
    return p;
}
/*****************/
// add a new edge
void add_Edge(int weight, pnode src_node, pnode dst_node)
{
    pedge curr = newEdge(weight, dst_node);
    pedge find_edge = src_node->edges;
    if (find_edge == NULL)
    {
        src_node->edges = curr;
        return;
    }
    while (find_edge->next != NULL)
    {
        find_edge = find_edge->next;
    }
    find_edge->next = curr;
}
/***************************/
// find node
pnode findNodePrev(int name, pnode *head)
{
    pnode p = *head;
    if (p != NULL && p->node_num == name)
    {
        return NULL;
    }
    else
    {
        while (p->next != NULL)
        {
            if (p->next->node_num == name)
                return p;
            p = p->next;
        }
    }
    return NULL;
}
/************/
/***************************/
// find node
pnode findNode(int name, pnode *head)
{
    pnode p = *head;
    while (p != NULL)
    {
        if (p->node_num == name)
            return p;
        p = p->next;
    }
    return NULL;
}
/************/
// make a new node
pnode new_node(int num, struct GRAPH_NODE_ *next)
{
    pnode p1 = (pnode)malloc(sizeof(node));
    if (p1 == NULL)
    {
        printf("error in allocate memory");
        exit(-1);
    }

    p1->node_num = num;
    p1->next = next;
    p1->edges = NULL;
    return p1;
}
/*********************/
/*********************/
// free node edges
void free_edges(pnode edge_fr)
{
    pedge e = edge_fr->edges;
    pedge e1 = edge_fr->edges;
    while (e != NULL)
    {
        pedge tmp = e;
        e = e->next;
        free(tmp);
        if (e1 != NULL)
        {
            pedge tmp1 = e1;
            e1 = e1->nextB;
            free(tmp1);
        }
    }
    edge_fr->edges = NULL;
}
/*****************/
// insert a node
void insert_node_cmd(pnode *head)
{
    int src_node = 0;
    scanf("%d", &src_node);
    // find node number n
    pnode start_node = findNode(src_node, head);
    // check if n already exist, free his edges
    if (start_node == NULL)
    {
        start_node = new_node(src_node, NULL);
        pnode p = *head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = start_node;
    }
    else
    {
        free_edges(start_node);
        start_node->edges = NULL;
    }
    int dest;
    int weight; // i is destinaion, j is weight
    while (1)
    {
        if (scanf("%d", &dest) != 1)
        {
            break;
        }
        if (scanf("%d", &weight) != 1)
        {
            break;
        }
        // create a edge from n to i with i as weight
        pnode dest_node = findNode(dest, head);
        add_Edge(weight, start_node, dest_node);
    }
}
/******************************/

void build_graph_cmd(pnode *head)
{
    int num_of_vert = 0;
    int i = 1;
    pnode h = new_node(0, NULL);
    *head = h;
    scanf("%d", &num_of_vert);
    while (i < num_of_vert)
    {
        pnode curr = new_node(i, NULL);
        h->next = curr;
        h = curr;
        i++;
    }
    char ch;
    while (i > 1)
    {
        scanf("%c", &ch);
        insert_node_cmd(head);
        i--;
    }
}
/******************************/
// delete graph
void deleteGraph_cmd(pnode *head)
{
    pnode p = *head;
    while (p != NULL)
    {
        pnode tmp = p;
        p = p->next;
        free_node(tmp);
    }
}
/*******************/
// delete node
void delete_node_cmd(pnode *head)
{
    int node_toDel;
    scanf("%d", &node_toDel);
    pnode p = findNodePrev(node_toDel, head);
    if (p == NULL)
    {
        pnode b = *head;
        free_edgeFrom(head, b);
        free_node(b);
        *head = (*head)->next;
    }
    else
    {
        pnode k = p->next;
        free_edgeFrom(head, k);
        p->next = p->next->next;
        free_node(k);
    }
}
/*****************/
// print graph
void printGraph_cmd(pnode head)
{
    printf("*graph*\n");
    pnode p = head;
    while (p != NULL)
    {
        printf("edges of %d:", p->node_num);
        pedge e = p->edges;
        while (e != NULL)
        {
            printf("->(endpoint:%d weight:%d)", e->endpoint->node_num, e->weight);
            e = e->next;
        }
        printf("\n");
        p = p->next;
    }
    printf("-----------------------------------------------\n");
}
/*****************/
void shortsPath_cmd(pnode head)
{
    int src;
    int dest;
    scanf(" %d", &src);
    scanf(" %d", &dest);
    // Initialize distances and edges for nodes
    pnode p = head;
    pedge eList = NULL;
    pedge prev = NULL;
    while (p != NULL)
    {
        if (p->node_num == src)
        {
            p->distance = 0;
        }
        else
        {
            p->distance = INT_MAX;
        }
        if (p->edges != NULL)
        {
            pedge e = p->edges;
            while (e != NULL)
            {
                if (eList == NULL)
                {
                    eList = e;
                }
                else
                {
                    prev->nextB = e;
                }
                prev = e;
                e->source = p;
                e = e->next;
            }
        }
        p = p->next;
    }
    // printf("finished initiation 45 \n");

    // // Relax edges repeatedly
    p = head;
    while (p != NULL)
    {
        pedge e = eList;
        while (e != NULL)
        {
            pnode u = e->source;
            pnode v = e->endpoint;
            int uDist = u->distance;
            int vDist = v->distance;
            int weight = e->weight;
            if ((uDist != INT_MAX) && (uDist + weight < vDist))
                v->distance = uDist + weight;
            e = e->nextB;
        }
        p = p->next;
    }
    pnode pTheOne = head;
    // printGraph_cmd(head);
    while (pTheOne->node_num != dest)
    {
        pTheOne = pTheOne->next;
    }

    if (pTheOne->distance == INT_MAX)
    {
        printf("Dijsktra shortest path %d\n", -1);
    }
    else
    {
        printf("Dijsktra shortest path %d\n", pTheOne->distance);
    }
}
/******************/
/*****************/
int shortsPathForTsp(pnode head, int src, int dest)
{
    pnode p = head;
    pedge eList = NULL;
    pedge prev = NULL;
    while (p != NULL)
    {
        if (p->node_num == src)
        {
            p->distance = 0;
        }
        else
        {
            p->distance = INT_MAX;
        }
        if (p->edges != NULL)
        {
            pedge e = p->edges;
            while (e != NULL)
            {
                if (eList == NULL)
                {
                    eList = e;
                }
                else
                {
                    prev->nextB = e;
                }
                prev = e;
                e->source = p;
                e = e->next;
            }
        }
        p = p->next;
    }
    p = head;
    while (p != NULL)
    {
        pedge e = eList;
        while (e != NULL)
        {
            pnode u = e->source;
            pnode v = e->endpoint;
            int uDist = u->distance;
            int vDist = v->distance;
            int weight = e->weight;
            if ((uDist != INT_MAX) && (uDist + weight < vDist))
                v->distance = uDist + weight;
            e = e->nextB;
        }
        p = p->next;
    }
    pnode pTheOne = head;
    // printGraph_cmd(head);
    while (pTheOne->node_num != dest)
    {
        pTheOne = pTheOne->next;
    }

    if (pTheOne->distance == INT_MAX)
    {
        return INT_MAX;
    }
    else
    {
        return pTheOne->distance;
    }
}
/*******************/
/*****************/
void belman_ford(pnode head, int sourceP)
{
    // initialization of added arrtibutes
    pnode p = head;
    pedge eList = NULL;
    pedge prev = NULL;
    while (p != NULL)
    {
        if (p->node_num == sourceP)
        {
            p->distance = 0;
        }
        else
        {
            p->distance = INT_MAX;
        }
        if (p->edges != NULL)
        {
            pedge e = p->edges;
            while (e != NULL)
            {
                if (eList == NULL)
                    eList = e;
                else
                {
                    prev->nextB = e;
                }
                prev = e;
                e->source = p;
                e = e->next;
            }
        }
        p = p->next;
    }
    // Relax edges repeatedly
    p = head;
    while (p != NULL)
    {
        pedge e = eList;
        while (e != NULL)
        {
            pnode u = e->source;
            pnode v = e->endpoint;
            int uDist = u->distance;
            int vDist = v->distance;
            int weight = e->weight;
            if ((uDist != INT_MAX) && (uDist + weight < vDist))
                v->distance = uDist + weight;
            e = e->nextB;
        }
        p = p->next;
    }
}
int permute(pnode *arr, int start, int end, int *distances, pnode *arrOriginal)
{
    int i;
    if (start == end)
    {
        // print the permutation
        for (i = 0; i <= end; i++)
        {
            // printf("%d ", arr[i]->node_num);
        }
        // printf(" | ");
        // sums the permutation
        int sum = 0;
        for (i = 0; i < end; i++)
        {
            int k = 0, j = 0;
            while (arr[i]->node_num != arrOriginal[j]->node_num)
            {
                j++;
            }
            while (arr[i + 1]->node_num != arrOriginal[k]->node_num)
            {
                k++;
            }
            // printf("(%d,%d)", arrOriginal[j]->node_num, arrOriginal[k]->node_num);
            if (*(distances + j * (end + 1) + k) != INT_MAX)
            {
                // printf(" %d -> ", *(distances + j * (end + 1) + k));
                sum += *(distances + j * (end + 1) + k);
            }
            else
            {
                // printf(" INFINITY | ");
                sum = *(distances + j * (end + 1) + k);
                break;
            }
        }
        // printf("| sum  = %d\n", sum);
        return sum;
    }
    int sum = INT_MAX;
    for (i = start; i <= end; i++)
    {
        // swap the current element with the start element
        pnode temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;

        // recursively permute the remaining elements
        int num = permute(arr, start + 1, end, distances, arrOriginal);
        if (num < sum)
            sum = num;
        // swap the elements back
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
    }
    return sum;
}

void TSP_cmd(pnode head)
{
    int i;
    int result = scanf(" %d", &i);
    if (result != 1)
    {
        printf("Invalid input\n");
        exit(-1);
    }
    // printf("21. got digit from input: %d\n", i);
    pnode *arr = (pnode *)malloc((sizeof(pnode) * i));
    pnode *arrOriginal = (pnode *)malloc((sizeof(pnode) * i));
    int countdown = i - 1;
    int length = i;
    while (countdown > -1)
    {
        result = scanf(" %d", &i);
        if (result != 1)
        {
            printf("Invalid input\n");
            exit(-1);
        }
        // printf("22. got digit from input: %d\n", i);

        pnode pTheOne = head;
        while (pTheOne->node_num != i)
        {
            pTheOne = pTheOne->next;
        }
        arr[countdown] = (pnode)(pTheOne);
        arrOriginal[countdown] = (pnode)(pTheOne);
        countdown--;
    }
    int *distances = (int *)malloc(length * length * sizeof(int));
    for (int j = 0; j < length; j++)
    {
        belman_ford(head, arr[j]->node_num);
        for (int k = 0; k < length; k++)
        {
            *(distances + j * length + k) = arr[k]->distance;
        }
    }
    int min = permute(arr, 0, length - 1, distances, arrOriginal);
    if (min == INT_MAX) printf("TSP shortest path: %d \n", -1);
    else printf("TSP shortest path: %d \n", min);
    free(distances);
    free(arrOriginal);
    free(arr);
}

int main()
{
    char c = 'z';
    int flag = 1;
    pnode *head = (pnode *)malloc(sizeof(node));
    while (1)
    {
        scanf("%c", &c);
        // printf("%c\n", c);
        if (getchar() == EOF)
        {
            break;
        }
        else if (c == 'A')
        {
            if (flag == 1)
            {
                build_graph_cmd(head);
                flag = 0;
            }
            else
            {
                deleteGraph_cmd(head);
                build_graph_cmd(head);
            }
            // break;
        }
        else if (c == 'n')
        {
            insert_node_cmd(head);
            // break;
        }
        else if (c == 'B')
        {
            insert_node_cmd(head);
            // break;
        }
        else if (c == 'D')
        {
            delete_node_cmd(head);
            // break;
        }
        else if (c == 'P')
        {
            printGraph_cmd(*head);
            // break;
        }
        else if (c == 'S')
        {
            shortsPath_cmd(*head);
        }
        else if (c == 'T')
        {
            TSP_cmd(*head);
        }
    }
    deleteGraph_cmd(head);
    free(head);
    return 0;
}