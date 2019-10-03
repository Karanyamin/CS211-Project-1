#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node* left;
    struct node* right;
};

struct node* head = NULL;

struct node* create(int n){
    struct node* temp = malloc(sizeof(struct node));
    (*temp).val = n;
    (*temp).left = NULL;
    (*temp).right = NULL;
    return temp;
}

void insert(int num){
    if (head == NULL){
        head = create(num);
        printf("inserted 1\n");
    } else {
        struct node* ptr = head;
        int height = 1;
        while (ptr != NULL){
            if ((*ptr).val == num){
                printf("duplicate\n");
                return;
            } else if ((*ptr).val > num){//Go left
                if ((*ptr).left == NULL){ //Add the new node there
                    (*ptr).left = create(num);
                    printf("inserted %d\n", (height + 1));
                    return;
                } else {
                    ptr = (*ptr).left;
                    height++;
                }
            } else {
                if ((*ptr).right == NULL){
                    (*ptr).right = create(num);
                    printf("inserted %d\n", (height + 1));
                    return;
                } else {
                    ptr = (*ptr).right;
                    height++;
                }
            }
        }
    }
}

void search(int num){
    if (head == NULL){
        printf("absent\n");
    } else {
        struct node* ptr = head;
        int height = 1;
        while(ptr != NULL){
            if ((*ptr).val == num){
                printf("present %d\n", height);
                return;
            } else if ((*ptr).val > num){
                ptr = (*ptr).left;
                height++;
            } else {
                ptr = (*ptr).right;
                height++;
            }
        }
        printf("absent\n");
    }
}



void freetree(struct node* ptr){
    if (ptr == NULL) return;

    freetree((*ptr).left);
    freetree((*ptr).right);

    free(ptr);
    ptr = NULL;
}


int main(int argc, char** argv){
    FILE* f = fopen(argv[1], "r");
    if (f == NULL){
        printf("error");
        exit(0);
    }

    char c;
    int val;

    while (fscanf(f, "%c\t%d\n", &c, &val) != EOF){
        if (c == 'i'){
            insert(val);
        } else {
            search(val);
        }
    }

    freetree(head);

    free(f);
    return 0;
}
