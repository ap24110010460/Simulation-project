#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int roll;
    char name[50];
    int lateDays;
    float fine;
    struct Node *next;
};

struct Node *head = NULL;

float calculateFine(int days) {
    return days * 5.0;   // ?5 per day
}

void addRecord() {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &newNode->roll);

    printf("Enter Student Name: ");
    scanf("%49s", newNode->name);

    printf("Enter Late Days: ");
    scanf("%d", &newNode->lateDays);

    newNode->fine = calculateFine(newNode->lateDays);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Record Added Successfully!\n");
}

void displayRecords() {
    if (head == NULL) {
        printf("No records available.\n");
        return;
    }

    struct Node *temp = head;
    printf("\nRoll\tName\tLateDays\tFine\n");
    printf("-------------------------------------------\n");

    while (temp != NULL) {
        printf("%d\t%s\t%d\t\t%.2f\n",
               temp->roll, temp->name, temp->lateDays, temp->fine);
        temp = temp->next;
    }
}

void searchRec(struct Node *node, int roll) {
    if (node == NULL) {
        printf("Record NOT FOUND.\n");
        return;
    }

    if (node->roll == roll) {
        printf("\nRecord Found:\n");
        printf("Roll: %d\nName: %s\nLate Days: %d\nFine: %.2f\n",
               node->roll, node->name, node->lateDays, node->fine);
        return;
    }

    searchRec(node->next, roll);
}

void calculateTotalFineRec(struct Node *node, float *sum) {
    if (node == NULL)
        return;

    *sum += node->fine;
    calculateTotalFineRec(node->next, sum);
}

void deleteRecord() {
    if (head == NULL) {
        printf("No records to delete.\n");
        return;
    }

    int roll;
    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    struct Node *temp = head, *prev = NULL;

    while (temp != NULL && temp->roll != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Record NOT FOUND.\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Record Deleted Successfully!\n");
}

int main() {
    int choice, roll;

    while (1) {
        printf("\n===== Library Late Return Fine System =====\n");
        printf("1. Add Late Return Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Record (Recursive)\n");
        printf("4. Calculate Total Fine (Recursive)\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;

            case 2:
                displayRecords();
                break;

            case 3:
                printf("Enter Roll Number to Search: ");
                scanf("%d", &roll);
                searchRec(head, roll);
                break;

            case 4: {
                float total = 0;
                calculateTotalFineRec(head, &total);
                printf("Total Fine of All Students = %.2f\n", total);
                break;
            }

            case 5:
                deleteRecord();
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
