#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// Constants
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10
#define MAX_DEPARTMENTS 10
#define MAX_ROOMS 100

// Patient structure
typedef struct Patient {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
    char diagnosis[MAX_NAME_LENGTH];
    struct Patient* next;
} Patient;

// Appointment structure
typedef struct Appointment {
    char patientId[MAX_ID_LENGTH];
    int department;
    int priority; // 1 (high) to 5 (low)
    struct Appointment* next;
} Appointment;

// Room structure
typedef struct Room {
    int number;
    bool occupied;
    char patientId[MAX_ID_LENGTH];
} Room;

// Graph node for hospital layout (for BFS/DFS)
typedef struct HospitalNode {
    int id;
    char name[MAX_NAME_LENGTH]; // e.g., "Emergency", "Radiology"
    struct HospitalNode* next;
} HospitalNode;

// Graph structure for hospital departments
typedef struct HospitalGraph {
    int numDepartments;
    HospitalNode** adjacencyList;
} HospitalGraph;

// Stack structure for DFS
typedef struct Stack {
    int top;
    unsigned capacity;
    int* array;
} Stack;

// Queue structure for BFS
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

// Global variables
Patient* patientList = NULL;
Appointment* appointmentQueue = NULL;
Room rooms[MAX_ROOMS];
char departments[MAX_DEPARTMENTS][MAX_NAME_LENGTH] = {
    "Emergency", "Cardiology", "Radiology", "Pediatrics", 
    "Orthopedics", "Neurology", "Oncology", "General", 
    "ICU", "Pharmacy"
};

// Function prototypes
void initHospitalGraph(HospitalGraph* graph, int numDepartments);
void addDepartmentEdge(HospitalGraph* graph, int src, int dest);
void printHospitalGraph(HospitalGraph* graph);
void BFS(HospitalGraph* graph, int startDepartment);
void DFS(HospitalGraph* graph, int startDepartment);
Stack* createStack(unsigned capacity);
bool isStackFull(Stack* stack);
bool isStackEmpty(Stack* stack);
void push(Stack* stack, int item);
int pop(Stack* stack);
Queue* createQueue(unsigned capacity);
bool isQueueFull(Queue* queue);
bool isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);
void addPatient();
void displayPatients();
Patient* searchPatient(char id[]);
void deletePatient(char id[]);
void addAppointment();
void processAppointments();
void displayAppointments();
void initializeRooms();
void assignRoom(char patientId[]);
void vacateRoom(int roomNumber);
void displayRoomStatus();
void hospitalManagementMenu();
void departmentNavigationMenu(HospitalGraph* graph);

int main() {
    // Initialize hospital graph
    HospitalGraph graph;
    initHospitalGraph(&graph, MAX_DEPARTMENTS);
    
    // Add connections between departments
    addDepartmentEdge(&graph, 0, 1);  // Emergency -> Cardiology
    addDepartmentEdge(&graph, 0, 2);  // Emergency -> Radiology
    addDepartmentEdge(&graph, 1, 3);  // Cardiology -> Pediatrics
    addDepartmentEdge(&graph, 2, 4);  // Radiology -> Orthopedics
    addDepartmentEdge(&graph, 3, 5);  // Pediatrics -> Neurology
    addDepartmentEdge(&graph, 4, 6);  // Orthopedics -> Oncology
    addDepartmentEdge(&graph, 5, 7);  // Neurology -> General
    addDepartmentEdge(&graph, 6, 8);  // Oncology -> ICU
    addDepartmentEdge(&graph, 7, 9);  // General -> Pharmacy
    addDepartmentEdge(&graph, 8, 9);  // ICU -> Pharmacy
    
    initializeRooms();
    
    int choice;
    do {
        printf("\n=== Hospital Management System ===\n");
        printf("1. Patient Management\n");
        printf("2. Appointment Scheduling\n");
        printf("3. Room Management\n");
        printf("4. Department Navigation\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                hospitalManagementMenu();
                break;
            case 2:
                appointmentManagementMenu();
                break;
            case 3:
                roomManagementMenu();
                break;
            case 4:
                departmentNavigationMenu(&graph);
                break;
            case 5:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
    
    return 0;
}

// Initialize hospital graph
void initHospitalGraph(HospitalGraph* graph, int numDepartments) {
    graph->numDepartments = numDepartments;
    graph->adjacencyList = (HospitalNode*)malloc(numDepartments * sizeof(HospitalNode));
    for (int i = 0; i < numDepartments; i++) {
        graph->adjacencyList[i] = NULL;
    }
}

// Add edge between departments
void addDepartmentEdge(HospitalGraph* graph, int src, int dest) {
    // Add edge from src to dest
    HospitalNode* newNode = (HospitalNode*)malloc(sizeof(HospitalNode));
    newNode->id = dest;
    strcpy(newNode->name, departments[dest]);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
    
    // Add edge from dest to src (undirected graph)
    newNode = (HospitalNode*)malloc(sizeof(HospitalNode));
    newNode->id = src;
    strcpy(newNode->name, departments[src]);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Print hospital graph
void printHospitalGraph(HospitalGraph* graph) {
    for (int v = 0; v < graph->numDepartments; v++) {
        HospitalNode* temp = graph->adjacencyList[v];
        printf("\nDepartment %d (%s) connects to: ", v, departments[v]);
        while (temp) {
            printf("%d (%s) ", temp->id, temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

// BFS algorithm for department navigation
void BFS(HospitalGraph* graph, int startDepartment) {
    bool* visited = (bool*)malloc(graph->numDepartments * sizeof(bool));
    for (int i = 0; i < graph->numDepartments; i++) {
        visited[i] = false;
    }
    
    Queue* queue = createQueue(graph->numDepartments);
    visited[startDepartment] = true;
    enqueue(queue, startDepartment);
    
    printf("BFS Department Navigation starting from %s:\n", departments[startDepartment]);
    
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("-> %s ", departments[current]);
        
        HospitalNode* temp = graph->adjacencyList[current];
        while (temp != NULL) {
            int adjDepartment = temp->id;
            if (!visited[adjDepartment]) {
                visited[adjDepartment] = true;
                enqueue(queue, adjDepartment);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    
    free(visited);
    free(queue->array);
    free(queue);
}

// DFS algorithm for department navigation
void DFS(HospitalGraph* graph, int startDepartment) {
    bool* visited = (bool*)malloc(graph->numDepartments * sizeof(bool));
    for (int i = 0; i < graph->numDepartments; i++) {
        visited[i] = false;
    }
    
    Stack* stack = createStack(graph->numDepartments);
    push(stack, startDepartment);
    
    printf("DFS Department Navigation starting from %s:\n", departments[startDepartment]);
    
    while (!isStackEmpty(stack)) {
        int current = pop(stack);
        
        if (!visited[current]) {
            printf("-> %s ", departments[current]);
            visited[current] = true;
        }
        
        HospitalNode* temp = graph->adjacencyList[current];
        while (temp != NULL) {
            int adjDepartment = temp->id;
            if (!visited[adjDepartment]) {
                push(stack, adjDepartment);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    
    free(visited);
    free(stack->array);
    free(stack);
}

// Stack operations for DFS
Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

bool isStackFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    if (isStackFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) return INT_MIN;
    return stack->array[stack->top--];
}

// Queue operations for BFS
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isQueueFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Patient management functions
void addPatient() {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    
    printf("\nEnter patient ID: ");
    scanf("%s", newPatient->id);
    
    printf("Enter patient name: ");
    scanf(" %[^\n]s", newPatient->name);
    
    printf("Enter patient age: ");
    scanf("%d", &newPatient->age);
    
    printf("Enter patient gender (M/F): ");
    scanf(" %c", &newPatient->gender);
    
    printf("Enter diagnosis: ");
    scanf(" %[^\n]s", newPatient->diagnosis);
    
    newPatient->next = patientList;
    patientList = newPatient;
    
    printf("Patient added successfully!\n");
}

void displayPatients() {
    if (patientList == NULL) {
        printf("\nNo patients in the system.\n");
        return;
    }
    
    Patient* current = patientList;
    printf("\n=== Patient List ===\n");
    printf("%-10s %-20s %-5s %-5s %-20s\n", "ID", "Name", "Age", "Gender", "Diagnosis");
    
    while (current != NULL) {
        printf("%-10s %-20s %-5d %-5c %-20s\n", 
               current->id, current->name, current->age, current->gender, current->diagnosis);
        current = current->next;
    }
}

Patient* searchPatient(char id[]) {
    Patient* current = patientList;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deletePatient(char id[]) {
    Patient *current = patientList, *prev = NULL;
    
    while (current != NULL && strcmp(current->id, id) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Patient not found.\n");
        return;
    }
    
    if (prev == NULL) {
        patientList = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    printf("Patient deleted successfully.\n");
}

// Appointment management functions
void addAppointment() {
    char patientId[MAX_ID_LENGTH];
    printf("\nEnter patient ID: ");
    scanf("%s", patientId);
    
    if (searchPatient(patientId) == NULL) {
        printf("Patient not found. Please add patient first.\n");
        return;
    }
    
    Appointment* newAppointment = (Appointment*)malloc(sizeof(Appointment));
    strcpy(newAppointment->patientId, patientId);
    
    printf("\nAvailable Departments:\n");
    for (int i = 0; i < MAX_DEPARTMENTS; i++) {
        printf("%d. %s\n", i, departments[i]);
    }
    printf("Select department: ");
    scanf("%d", &newAppointment->department);
    
    printf("Enter priority (1-high to 5-low): ");
    scanf("%d", &newAppointment->priority);
    
    // Insert based on priority (priority queue)
    if (appointmentQueue == NULL || newAppointment->priority < appointmentQueue->priority) {
        newAppointment->next = appointmentQueue;
        appointmentQueue = newAppointment;
    } else {
        Appointment* current = appointmentQueue;
        while (current->next != NULL && current->next->priority <= newAppointment->priority) {
            current = current->next;
        }
        newAppointment->next = current->next;
        current->next = newAppointment;
    }
    
    printf("Appointment added successfully!\n");
}

void processAppointments() {
    if (appointmentQueue == NULL) {
        printf("\nNo appointments to process.\n");
        return;
    }
    
    printf("\nProcessing appointment for patient ID: %s\n", appointmentQueue->patientId);
    Patient* patient = searchPatient(appointmentQueue->patientId);
    if (patient) {
        printf("Patient: %s, Department: %s\n", patient->name, departments[appointmentQueue->department]);
        assignRoom(appointmentQueue->patientId);
    }
    
    Appointment* temp = appointmentQueue;
    appointmentQueue = appointmentQueue->next;
    free(temp);
}

void displayAppointments() {
    if (appointmentQueue == NULL) {
        printf("\nNo appointments scheduled.\n");
        return;
    }
    
    Appointment* current = appointmentQueue;
    printf("\n=== Appointment Queue ===\n");
    printf("%-10s %-20s %-10s\n", "Patient ID", "Department", "Priority");
    
    while (current != NULL) {
        printf("%-10s %-20s %-10d\n", 
               current->patientId, departments[current->department], current->priority);
        current = current->next;
    }
}

// Room management functions
void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].number = i + 1;
        rooms[i].occupied = false;
        strcpy(rooms[i].patientId, "");
    }
}

void assignRoom(char patientId[]) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (!rooms[i].occupied) {
            rooms[i].occupied = true;
            strcpy(rooms[i].patientId, patientId);
            printf("Assigned room %d to patient %s\n", rooms[i].number, patientId);
            return;
        }
    }
    printf("No rooms available!\n");
}

void vacateRoom(int roomNumber) {
    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number.\n");
        return;
    }
    
    if (!rooms[roomNumber-1].occupied) {
        printf("Room %d is already vacant.\n", roomNumber);
        return;
    }
    
    printf("Room %d vacated by patient %s\n", roomNumber, rooms[roomNumber-1].patientId);
    rooms[roomNumber-1].occupied = false;
    strcpy(rooms[roomNumber-1].patientId, "");
}

void displayRoomStatus() {
    printf("\n=== Room Status ===\n");
    printf("%-10s %-15s %-10s\n", "Room No.", "Occupied", "Patient ID");
    
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("%-10d %-15s %-10s\n", 
               rooms[i].number, 
               rooms[i].occupied ? "Yes" : "No", 
               rooms[i].occupied ? rooms[i].patientId : "N/A");
    }
}

// Menu functions
void hospitalManagementMenu() {
    int choice;
    char id[MAX_ID_LENGTH];
    
    do {
        printf("\n=== Patient Management ===\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                printf("Enter patient ID to search: ");
                scanf("%s", id);
                Patient* patient = searchPatient(id);
                if (patient) {
                    printf("\nPatient Found:\n");
                    printf("ID: %s\nName: %s\nAge: %d\nGender: %c\nDiagnosis: %s\n",
                           patient->id, patient->name, patient->age, 
                           patient->gender, patient->diagnosis);
                } else {
                    printf("Patient not found.\n");
                }
                break;
            case 4:
                printf("Enter patient ID to delete: ");
                scanf("%s", id);
                deletePatient(id);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);
}

void appointmentManagementMenu() {
    int choice;
    
    do {
        printf("\n=== Appointment Management ===\n");
        printf("1. Add Appointment\n");
        printf("2. Process Next Appointment\n");
        printf("3. Display Appointment Queue\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addAppointment();
                break;
            case 2:
                processAppointments();
                break;
            case 3:
                displayAppointments();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}

void roomManagementMenu() {
    int choice, roomNumber;
    char patientId[MAX_ID_LENGTH];
    
    do {
        printf("\n=== Room Management ===\n");
        printf("1. Assign Room to Patient\n");
        printf("2. Vacate Room\n");
        printf("3. Display Room Status\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter patient ID to assign room: ");
                scanf("%s", patientId);
                assignRoom(patientId);
                break;
            case 2:
                printf("Enter room number to vacate: ");
                scanf("%d", &roomNumber);
                vacateRoom(roomNumber);
                break;
            case 3:
                displayRoomStatus();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}

void departmentNavigationMenu(HospitalGraph* graph) {
    int choice, startDept;
    
    do {
        printf("\n=== Department Navigation ===\n");
        printf("1. View Hospital Layout\n");
        printf("2. Navigate using BFS\n");
        printf("3. Navigate using DFS\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printHospitalGraph(graph);
                break;
            case 2:
                printf("\nAvailable Departments:\n");
                for (int i = 0; i < MAX_DEPARTMENTS; i++) {
                    printf("%d. %s\n", i, departments[i]);
                }
                printf("Enter starting department number: ");
                scanf("%d", &startDept);
                if (startDept >= 0 && startDept < MAX_DEPARTMENTS) {
                    BFS(graph, startDept);
                } else {
                    printf("Invalid department number.\n");
                }
                break;
            case 3:
                printf("\nAvailable Departments:\n");
                for (int i = 0; i < MAX_DEPARTMENTS; i++) {
                    printf("%d. %s\n", i, departments[i]);
                }
                printf("Enter starting department number: ");
                scanf("%d", &startDept);
                if (startDept >= 0 && startDept < MAX_DEPARTMENTS) {
                    DFS(graph, startDept);
                } else {
                    printf("Invalid department number.\n");
                }
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}
