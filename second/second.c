#include <stdio.h>
#include <stdlib.h>

void insert(int val);
void print();
int exists(int val);
void delete(int val);
void count();

struct node {
    int data;
    struct node* next;
};

struct node * head = NULL;

int main(int argc, char* argv[]){
    FILE* ptr = fopen(argv[1], "r");
    if (ptr == NULL){
        printf("error");
        exit(0);
    }

    char type;
    int val;

    while (fscanf(ptr, "%c\t%d\n", &type, &val) != EOF){
        if (type == 'i'){
            insert(val);
        } else {
            delete(val);
        }
    }
    count();
    print();
    fclose(ptr);
    return 0;
//    printf("The char type is %c and the corresponding value is %d", type, val);
}

void count(){
	int count = 0;
	struct node * temp = head;
	while (temp != NULL){
		count++;
		temp = (*temp).next;
    }
    printf("%d\n",count);
}

void insert(int val){
    if (exists(val) == 1){
        return;
    }

    if (head == NULL){

        struct node * temp = malloc(sizeof(struct node));
        (*temp).data = val;
        (*temp).next = head;
        head = temp;

    } else {
        struct node * pretemp = NULL;
        struct node * temp = head;
        while (temp != NULL){
            if (val < (*temp).data){
                struct node * new = malloc(sizeof(struct node));
                (*new).data = val;
                (*new).next = temp;
                if (temp == head){
                    head = new;
                } else {
                    (*pretemp).next = new;
                }
                return;
            } else {
                pretemp = temp;
                temp = (*temp).next;
            }
        }
        struct node * new = malloc(sizeof(struct node));
        (*new).data = val;
        (*new).next = NULL;
        (*pretemp).next = new;
    }
}

void print(){
    struct node * temp = head;
    while (temp != NULL){
        printf("%d\t", (*temp).data);
        temp = (*temp).next;
    }
    printf("\n");
}

void delete(int val){
    if (head == NULL) return;
    struct node * pretemp = NULL;
    struct node * temp = head;

    while (temp != NULL){
        if ((*temp).data == val){
            if (temp == head){ //First element pretemp is NULL
                head = (*temp).next;
            } else {
                (*pretemp).next = (*temp).next;
            }
            return;
        }
	pretemp = temp;
        temp = (*temp).next;
    }

}

int exists(int val){
    struct node * temp = head;
    while (temp != NULL){
        if ((*temp).data == val) return 1;
        temp = (*temp).next;
    }
    return 0;
}
