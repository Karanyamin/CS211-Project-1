#include <stdio.h>
#include <stdlib.h>

int keycode(int key);

struct node {
    int value;
    struct node* next;
};

struct node** table;

struct node* create(int val){
    struct node* temp = malloc(sizeof(struct node));
    (*temp).value = val;
    (*temp).next = NULL;
    return temp;
}

int keycode(int key){
    int code = key % 1000;
    if (code < 0){
        code += 1000;
    }
    return code;
}

void printTable(){
    for (int i = 0; i < 1000; i++){
        struct node* ptr = table[i];
        if (ptr != NULL){
            printf("The values at %d are ", i);

            while (ptr != NULL){
                printf("%d ", (*ptr).value);
                ptr = (*ptr).next;
            }
            printf("\n");
        }
    }
}

struct node* add(struct node* head, struct node* temp){
    if (head == NULL){
        printf("inserted\n");
        return temp;
    }
    struct node* ptr = head;

    while ((*ptr).value != (*temp).value){
        if ((*ptr).next == NULL){
            (*ptr).next = temp;
            printf("inserted\n");
            printTable();
            return head;
        }
        ptr = (*ptr).next;
    }
    printf("duplicate\n");
    free(temp);
    temp = NULL;
    return head;
}

void search(struct node** table, int val){
    int key = keycode(val);
    struct node* head = table[key];
    struct node* ptr = head;
    if(ptr == NULL){
        printf("absent\n");
        return;
    }

    while (ptr != NULL){
        if ((*ptr).value == val){
            printf("present\n");
            return;
        }
        ptr = (*ptr).next;
    }
    printf("absent\n");
}

void insert(struct node** table, int val){
    struct node* temp = create(val);
    int key = keycode((*temp).value);
    struct node* ptr = table[key];
    if (ptr == NULL){
        table[key] = temp;
        printf("inserted\n");
        return;
    } else {
        struct node* prev = NULL;
        while (ptr != NULL){
            if (ptr->value == val){
                printf("duplicate\n");
                return;
            }
            prev = ptr;
            ptr = ptr->next;
        }
        prev->next = temp;
        printf("inserted\n");
        return;
    }

}

int main(int argc, char** argv){
    table = malloc(1000 * sizeof(struct node*));

    for (int i = 0; i < 1000; i++){
        table[i] = NULL;
    }
    FILE* f = fopen(argv[1], "r");
    if (f == NULL){
        printf("errofdfdr");
        exit(0);
    }
    char c = '\0';
    int temp = 0;
    while (fscanf(f, "%c\t%d\n", &c, &temp) != EOF){
        if (c == 'i'){
            insert(table, temp);
        } else if (c == 's'){
            search(table, temp);
        }
    }

    for (int i = 0; i < 1000; i++){
        struct node* temp = table[i];
        while (temp != NULL){
            struct node* temp2 = temp;
            temp = temp->next;
            free(temp2);
        }
    }
    free(table);
    fclose(f);

    return 0;
}
