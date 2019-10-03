#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node* left;
    struct node* right;
};

struct node* head = NULL;
int success = 0;


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

struct node* inOrderSuccessor(struct node* ptr){
    if ((*ptr).left == NULL) return ptr;

    return inOrderSuccessor((*ptr).left);
}

struct node* deleteInOrder(struct node* ptr, int num){
    if ((*ptr).left == NULL){
        if ((*ptr).right == NULL){
            free(ptr);
            ptr = NULL;
            return ptr;
        } else {
            struct node* temp = ptr;
            ptr = (*ptr).right;
            free(temp);
            return ptr;
        }
    }

    (*ptr).left = deleteInOrder((*ptr).left, num);
    return ptr;
}

struct node* deleteR(struct node* ptr, int num){
    if (ptr == NULL) return NULL;

    if ((*ptr).val == num){
        //NO children
        if ((*ptr).left == NULL && (*ptr).right == NULL){ //Remember to clear memory
            free(ptr);
            ptr = NULL;
            success = 1;
        } else if ((*ptr).left != NULL && (*ptr).right != NULL){
            //Has both children
            struct node* ios = inOrderSuccessor((*ptr).right);
            (*ptr).val = (*ios).val;
            (*ptr).right = deleteInOrder((*ptr).right, (*ios).val);
            success = 1;
        } else {
            if ((*ptr).left != NULL){
                struct node* temp = ptr;
                ptr = (*ptr).left;
                free(temp);
            } else {
                struct node* temp = ptr;
                ptr = (*ptr).right;
                free(temp);
            }
            success = 1;
        }
    } else if ((num < (*ptr).val)){
        (*ptr).left = deleteR((*ptr).left, num);
    } else {
        (*ptr).right = deleteR((*ptr).right, num);
    }

    return ptr;
}

void delete(int num){
    if (head == NULL){
        printf("fail\n");
    } else {
        head = deleteR(head, num);
        if (success == 1){
            printf("success\n");
            success = 0;
        } else {
            printf("fail\n");
        }
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
        } else if (c == 's'){
            search(val);
        } else {
            delete(val);
        }
    }

    freetree(head);

    fclose(f);
    return 0;
}
