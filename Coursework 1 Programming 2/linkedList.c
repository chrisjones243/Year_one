#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


typedef struct node {
    char* name;
    struct node* xor_value;
} Node;

Node* calculate_xor_value(Node* before, Node* after) {
    return (Node*)((intptr_t)before ^ (intptr_t)after);
}

void print_list(Node** head) {
    Node* current = (*head);
    Node* previous = NULL;
    Node* next;
    while (current != NULL) {
        printf("%s ", current->name);
        next = calculate_xor_value(previous, current->xor_value);
        previous = current;
        current = next;
    }
    printf(" NULL \n");

}

void insert_string(Node** head, const char* newObj) {
    int newObj_size = strlen(newObj) + 1;
    if (newObj_size > 64) {
        return;
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->name = malloc(sizeof(char) * strlen(newObj));
    strcpy(new_node->name, newObj);
    new_node->xor_value = calculate_xor_value(NULL, *head);
    if (*head != NULL) {
        (*head)->xor_value = calculate_xor_value(new_node, (*head)->xor_value);
    }
    *head = new_node;
}

int insert_before(Node** head, const char* before, const char* newObj) {
    Node* current = (*head);
    Node* previous = NULL;
    Node* next;
    int newObj_size = strlen(newObj) + 1;
    if (newObj_size <= 64) {
        while (current != NULL) {
            if (strcmp(current->name, before) == 0) {
                Node* new_node = malloc(sizeof(Node));
                if (current == (*head)) {
                    (*head) = new_node;
                }
                new_node->name = malloc(sizeof(char) * strlen(newObj));
                strcpy(new_node->name, newObj);
                new_node->xor_value = calculate_xor_value(previous, current);
                if (previous != NULL) {
                    previous->xor_value = calculate_xor_value(previous->xor_value, current);
                    previous->xor_value = calculate_xor_value(previous->xor_value, new_node);
                }
                current->xor_value = calculate_xor_value(previous, current->xor_value);
                current->xor_value = calculate_xor_value(current->xor_value, new_node);
                return true;
            }
            next = calculate_xor_value(previous, current->xor_value);
            previous = current;
            current = next;
        }
    }

    return false;
}

int insert_after(Node** head, const char* after, const char* newObj) {
    Node* current = (*head);
    Node* previous = NULL;
    Node* next;
    int newObj_size = strlen(newObj) + 1;
    if (newObj_size <= 64) {
        int j = 0;
        while (current != NULL) {
            if (j == 1) {
                Node* new_node = malloc(sizeof(Node));
                new_node->name = malloc(sizeof(char) * strlen(newObj));
                strcpy(new_node->name, newObj);
                new_node->xor_value = calculate_xor_value(previous, current);
                if (previous != NULL) {
                    previous->xor_value = calculate_xor_value(previous->xor_value, current);
                    previous->xor_value = calculate_xor_value(previous->xor_value, new_node);
                }
                current->xor_value = calculate_xor_value(previous, current->xor_value);
                current->xor_value = calculate_xor_value(current->xor_value, new_node);
                return true;
            }
            if (strcmp(current->name, after) == 0) {
                j = 1;
            }
            
            next = calculate_xor_value(previous, current->xor_value);
            previous = current;
            current = next;

        }
    }
    return false;
}

int remove_string(Node** head, char* result) {
    Node* delete_node = (*head);
    Node* new_head = delete_node->xor_value;
    new_head->xor_value = calculate_xor_value((*head), new_head->xor_value);
    if (new_head == NULL) {
        return false;
    }
    new_head->xor_value = calculate_xor_value(new_head->xor_value, NULL);
    strcpy(result, delete_node->name);
    free(delete_node);
    (*head) = new_head;

    return true;
}


int remove_after(Node** head, const char *after, char *result) {
    Node* current = (*head);
    Node* previous = NULL;
    Node* next;
    while (current != NULL) {
        if (strcmp(current->name, after) == 0) {
            Node* delete_node = calculate_xor_value(previous, current->xor_value);
            if (delete_node == NULL) {
                return false;
            }
            next = calculate_xor_value(current, delete_node->xor_value);
            if (next != NULL) {
                next->xor_value = calculate_xor_value(next->xor_value, delete_node);
                next->xor_value = calculate_xor_value(next->xor_value, current);
            }
            current->xor_value = calculate_xor_value(current->xor_value, delete_node);
            current->xor_value = calculate_xor_value(current->xor_value, next);
            strcpy(result, delete_node->name);
            free(delete_node);
            return true;
        }
        next = calculate_xor_value(previous, current->xor_value);
        previous = current;
        current = next;
    }

    return false;
}

int remove_before(Node** head, const char *before, char *result) {
    Node* current = (*head);
    Node* previous = NULL;
    Node* next;
    while (current != NULL) {
        if (strcmp(current->name, before) == 0) {
            Node* delete_node = previous;
            if (delete_node == NULL) {
                return false;
            }
            if (delete_node == (*head)) {
                (*head) = current;
            }
            previous = calculate_xor_value(current, delete_node->xor_value);
            if (next != NULL) {
                previous->xor_value = calculate_xor_value(previous->xor_value, delete_node);
                previous->xor_value = calculate_xor_value(previous->xor_value, current);
            }
            current->xor_value = calculate_xor_value(current->xor_value, delete_node);
            current->xor_value = calculate_xor_value(current->xor_value, previous);
            strcpy(result, delete_node->name);
            free(delete_node);
            return true;
        }
        next = calculate_xor_value(previous, current->xor_value);
        previous = current;
        current = next;
    }

    return false;
}

void free_all(Node** head) {
    Node* current = (*head);
    Node* previous = NULL;
    Node* next;
    while (current != NULL) {
        next = calculate_xor_value(previous, current->xor_value);
        free(current);
        previous = current;
        current = next;
    }
    (*head) = NULL;
}

int main() {
    Node* head = NULL;
    insert_string(&head, "Alpha");
    insert_string(&head, "Bravo");
    insert_string(&head, "Charlie");
    insert_string(&head, "Delta");
    insert_string(&head, "Echo");
    insert_string(&head, "Foxtrot");
    insert_string(&head, "Golf");
    insert_string(&head, "Hotel");

    print_list(&head);
    printf("\n");  

    printf("Inserting Golf before Hotel \n");
    insert_before(&head, "Hotel", "Golf");
    print_list(&head);
    printf("\n");

    printf("Inserting Hotel after Bravo \n");
    insert_after(&head, "Bravo", "Hotel");
    print_list(&head);
    printf("\n");
    
    printf("\n");

    char* result = malloc(sizeof(char) * 64);

    printf("Removing first \n");
    remove_string(&head, result);
    printf("Removed: %s \n", result);
    print_list(&head);
    printf("\n");

    
    printf("Removing after Bravo \n");
    remove_after(&head, "Bravo", result);
    printf("Removed: %s \n", result);
    print_list(&head);
    printf("\n");

    printf("Removing before Delta \n");
    remove_before(&head, "Delta", result);
    printf("Removed: %s \n", result);
    print_list(&head);

    free_all(&head);
    
    return 0;
}