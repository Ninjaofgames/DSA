#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Simple linked node
struct NodeStruct{
    char data[50];
    struct NodeStruct *next;
};
typedef struct NodeStruct* node;

//Simple linked list
struct listStruct{
    node head;
};
typedef struct listStruct* list;

//Double linked node
struct NodeDCStruct{
    char data[50];
    struct NodeDCStruct *next;
    struct NodeDCStruct *prev;
};
typedef struct NodeDCStruct node_DC;

//Double linked list
struct listStruct_DC{
    node_DC* head_DC;
};
typedef struct listStruct_DC* list_DC;

//create a node
node createNodef(char x[]){
    node nodeV = malloc(sizeof(node));
    strcpy(nodeV->data, x);
    nodeV->next = NULL;
    return nodeV;
}

//Create a DC node
node_DC* createNodeDCf(char x[]){
    node_DC* nodeDCV = malloc(sizeof(node_DC));
    strcpy(nodeDCV->data, x);
    nodeDCV->next = NULL;
    nodeDCV->prev = NULL;
    return nodeDCV;
}

//Test if the simple linked list is void
bool voidf(list listV){
    if(listV == NULL){
        return true;
    }else{
        return false;
    }
}

//Test if the doule linked list is void
bool voidDCf(list_DC L){
    if(L == NULL){
        return true;
    }else{
        return false;
    }
}

//Calculate the length of a simple linked list
int lengthListF(list L){
    int n;
    if(voidf(L) == true){
        return 0;
    }else{
        n = 1;
        node p = L->head;
        node *next;
        n++;
    }
    return n;
}

//Calculate the length of a double linked list
int lengthList_DCf(list_DC L){
    if(voidDCf(L)){
        return 0;
    }
    int n = 0;
    node_DC* p = L->head_DC;

    while(p != NULL){
        n++;
        p = p->next;
    }
    return n;
}

//another version of the previous function
int lengthListR(node C){
    if(C == NULL){
        return 0;
    }else{
        return 1+lengthListR(C->next);
    }
}

//K-th pointer function
node k_thptr(list L, int rank){
    node p = L->head;
    if(rank <= lengthListF(L) + 1){
        for(int i = 1; i <= rank; i++){
            p = p->next;
        }
        return p;
    }else{
        printf("Error");
        return NULL;
    }
}

//K-th pointer function for doubler linked list
node_DC* k_thptrDC(list_DC L, int rank){
    if(rank <= 0 || rank > lengthList_DCf(L)) return NULL;

    node_DC* p = L->head_DC;
    for(int i = 1; i < rank; i++){
        if(p == NULL) return NULL;
        p = p->next;
    }
    return p;
}

//Add a node in the beginning
list addB(char x[], list L){
    node nodeV = malloc(sizeof(struct NodeStruct));
    node p = createNodef(x);
    p->next = L->head;
    L->head = p;
    return L;
}

//Add a nodeDC in the beginning
list_DC addBDC(char x[], list_DC L){
    node_DC* p = createNodeDCf(x);
    p->next = L->head_DC;
    p->prev = NULL;
    L->head_DC = p;
    return L;
}

//Add a node in the end
list addEnd(char x[], list L){
    node p = createNodef(x);
    if(voidf(L)){
        L->head = p;
    }else{
        node q = L->head;
        while(q->next != NULL){
            q = q->next;
        }
        q->next = p;
    }
    return L;
}

//Add a node DC in the end
list_DC addEnd_DC(char x[], list_DC L){
    node_DC* p = createNodeDCf(x);
    node_DC* q = L->head_DC;
    if(voidDCf(L)){
        return addBDC(x, L);
    }else{
        while(q->next != NULL){
            q = q->next;
        }
        q->next = p;
        p->prev = q;
    }
}

//Add a node at the rank k
list addRank(char x[], list L, int k){
    node nodeV = malloc(sizeof(struct NodeStruct));
    if(k == 1){
        addB(x, L);
    }else if(k == lengthListF(L) + 1){
        addEnd(x, L);
    }else if(k > 1 && k < lengthListF(L) + 1){
        node p = createNodef(x);
        node q = L->head;
        for(int i = 1; i < k - 1; i++){
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
    return L;
}

//Add a node DC at the rank k
list_DC addRank_DC(char x[], list_DC L, int k){
    if(k > lengthList_DCf(L) + 1){
        return NULL;
    }else if(k == lengthList_DCf(L) + 1){
        return addEnd_DC(x, L);
    }else{
        node_DC* p = k_thptrDC(L, k - 1);
        node_DC* q = createNodeDCf(x);
        q->next = p->next;
        q->prev = p;
        p->next = q;
        return L;
    }
}

//Delete a node in the beginning
list deleteB(list L){
    if(voidf(L)){
        return L;
    }

    node p = L->head;
    L->head = p->next;
    free(p);
    return L;
}

//Delete a node DC in the beginning
list_DC deleteBDC(list_DC L){
    if(L == NULL){
        return NULL;
    }else{
        node_DC* p = L->head_DC;
        p->prev = NULL;
        p = p->next;
        free(p);
        return L;
    }
}

//Delete a node in the end
list deleteEnd(list L){
    if(voidf(L)){
        return L;
    }else if(lengthListF(L) == 1){
        deleteB(L);
    }

    node p = L->head;
    node prev = NULL;
    while (p->next != NULL){
        prev = p;
        p = p->next;
    }

    prev->next = NULL;
    free(p);
    return L;
}

//Delete a node DC in the end
list_DC deleteEndDC(list_DC L){
    if(lengthList_DCf(L) == 1){
        return deleteBDC(L);
    }else{
        node_DC* p = L->head_DC;
        node_DC* prevar;
        for(int i = 0; i < lengthList_DCf(L) + 1; i++){
            prevar = p;
            p = p->next;
        }
        p->prev->next = NULL;
        free(p);
        return L;
    }
}

//Delete a node in a rank
list deleteRank(list L, int k){
    if(k == 1){
        return deleteB(L);
    }else if(k == lengthListF(L)){
        return deleteEnd(L);
    }else if(k > 1 && k < lengthListF(L)){
        node p = k_thptr(L, k - 1);
        node q = k_thptr(L, k);
        p->next = q->next;
        free(q);
    }
    return L;
}

//Delete a node DC in a rank
list_DC deleteRankDC(list_DC L, int k){
    if(k == 1){
        return deleteBDC(L);
    }else{
        node_DC* p = L->head_DC;
        node_DC* prevar;
        for(int i = 0; i < k; i++){
            prevar = p;
            p = p->next;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        return L;
    }
}

//---------STACKS SECTION---------
struct StackStruct{
    node top;
};
typedef struct StackStruct stack;

//Test if the stack is empty
bool VoidS(stack* s){
    if(s == NULL){
        return true;
    }else{
        return false;
    }
}

//Calculate the length of a stack
int lengthS(stack* s){
    if(VoidS(s)){
        return 0;
    }else{
        int n = 1;
        node q = s->top;
        while(q->next != NULL){
            n++;
            q = q->next;
        }
        return n;
    }
}

//Test if the stack reached its maximum
bool maxStockS(stack* s, int k){
    if(k >= lengthS(s)){
        return true;
    }else{
        return false;
    }
}

//Extract the top of a stack
node topf(stack* s){
    if(VoidS(s)){
        return NULL;
    }
    node q = s->top;
    return q;
}

//Push a node
stack* push(char x[], stack* s){
    node q = createNodef(x);
    q->next = s->top;
    s->top = q;
    return s;
}

//Pull a node
stack* pull(stack* s){
    if(VoidS(s)){
        return NULL;
    }else{
        node q = s->top;
        s->top = s->top->next;
        free(q);
        return s;
    }
}

//Pull a node - Static
stack* pullStatic(stack *s){

}

//---------QUEUES SECTION---------
struct queueStruct{
    int front;
    int rear;
    int maxQueue;
    char *tab;
};
typedef struct queueStruct queue;

//Create a queue
queue* createQueue(int size){
    queue* q = malloc(sizeof(q) + sizeof(char) * size);
    if(!q) return NULL;
    q->front = -1; //-1 means that the front is empty
    q->rear = -1; // -1 means that the rear is empty
    q->maxQueue = size;
    return q;
}

//Test if the queue is empty
bool voidQ(queue* q){
    if(q->front == -1 && q->rear == -1){
        return true;
    }else{
        return false;
    }
}

//Test if the queue is full
bool fullQ(queue* q){
    if(q->rear == q->maxQueue - 1 && q->front == 0){
        return true;
    }else{
        return false;
    }
}

//Push a tab to an array
queue* pushQ(queue* q, char x){
    if (fullQ(q)) {
        return q;
    }

    if (voidQ(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear++;
    }

    q->tab[q->rear] = x;
    return q;
}

//Pull a tab from an array
queue* pullQ(queue* q){
    if(voidQ(q)){
        return NULL;
    }

    if(q->front == q->rear){
        q->front = -1;
        q->rear = -1;
    }else{
        q->front = (q->front + 1) % q->maxQueue;
    }

    return q;
}

//Seek the front element of a queue
char frontf(queue* q){
    if(voidQ(q)) return '\0';
    return q->tab[q->front];
}

//---------TREES SECTION---------
//The node of a tree
struct nodeABR{
    char x[50];
    struct nodeABR *left;
    struct nodeABR *right;
};
typedef struct nodeABR nodeT;

//A tree struct
struct tree{
    nodeT* root;
};
typedef struct tree tree;

nodeT preTree(tree T){
    nodeT q = T->root;
    if(T == NULL){
        return NULL;
    }else{
        return q;
        preTree(q->left);
        preTree(q->right);
    }
}

int main(){
    struct NodeStruct helloN;
    strcpy(helloN.data, "Hello World");
    printf("%s", helloN.next);
    return 0;
}
