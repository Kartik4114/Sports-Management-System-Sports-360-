#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

void title()
{
    printf(RED "  ██████╗ ██████╗    ████████    ██████╗   ██████████╗   ██████╗   ██████╗   ██████╗\n");
    printf(" ██╔════╝ ██╔══██   ██╔═════██   ██╔══██╗  ╚═══██╔═══╝   ╚════██╗ ██╔════╝  ██╔═══██╗\n");
    printf(" ██║      ██║  ██╗ ██╔╝      ██╗ ██║  ██║      ██║            ██║ ██║       ██║   ██║\n");
    printf(" ╚█████╗  ██████╔╝ ██║       ██║ ██████╔╝      ██║       ███████║ ███████╗  ██║   ██║\n");
    printf("  ╚═══██╗ ██╔═══╝  ██║       ██║ ████══╝       ██║       ╚════██║ ██╔═══██╗ ██║   ██║\n");
    printf("      ██║ ██║      ╚██      ██╔╝ ██║██══╗      ██║            ██║ ██║   ██║ ██║   ██║\n");
    printf(" ██████╔╝ ██║       ╚████████╔╝  ██║ ███║      ██║       ██████╔╝ ╚██████╔╝ ╚██████╔╝\n");
    printf(" ╚═════╝  ╚═╝        ╚═══════╝   ╚═╝ ╚══╝      ╚═╝       ╚═════╝   ╚═════╝   ╚═════╝\n" RESET);
}
// ------------------------------------------Admin password protections-----------------------------------------

// structure of Nodes in a binary tree.
typedef struct Node
{
    int user_id;
    char password[10];
    struct Node *left;
    struct Node *right;
} Admin;

// Function to Add Node in a binary tree.
Admin *insertNode(Admin *root, int userId, char pass[])
{
    if (!root)
    { // add a node.
        root = (Admin *)malloc(sizeof(Admin));
        root->left = NULL;
        root->right = NULL;
        root->user_id = userId;
        strcpy(root->password, pass);
        return root;
    }
    if (userId < root->user_id) // move towards left
        root->left = insertNode(root->left, userId, pass);
    else // move towards right
        root->right = insertNode(root->right, userId, pass);
    return root;
}

// Function to Create a binary tree.
void CreateBinaryTree(Admin **root, FILE *fp)
{
    int userId;
    char pass[10];
    fscanf(fp, "%d %s", &userId, pass);
    while (userId != -1)
    {
        *root = insertNode(*root, userId, pass);
        fscanf(fp, "%d %s", &userId, pass);
    }
}

// Function to Verify a user.
bool verify(Admin *root, int userId, char pass[])
{
    if (!root)
        return 0;

    // matches user_id and password.
    if (root->user_id == userId)
    {
        if (strcmp(root->password, pass) == 0)
        {
            return 1;
        }
        return 0;
    }
    if (userId < root->user_id) // move towards left.
        return verify(root->left, userId, pass);
    else // move towards right.
        return verify(root->right, userId, pass);
}

int Verification()
{
    system("clear");
    title();
    FILE *fp;
    fp = fopen("./Admin.txt", "r");
    Admin *root = NULL;
    // call the "createBinaryTree" function.
    CreateBinaryTree(&root, fp);
    fclose(fp);

    int userId;
    char pass[10];
    printf(MAGENTA "\n\t Log In \n\n" RESET);
    printf(YELLOW " Fill details\n" RESET);
    printf(BLUE "\n User ID : " RESET);
    scanf("%d", &userId);
    printf(BLUE "\n Password : " RESET);
    scanf("%s", pass);
    // call the function to "verify".
    int result;
    if (verify(root, userId, pass) == 1)
    {
        printf(YELLOW "\n Valid User\n");
        result = 2;
    }
    else
    {
        printf("\nInvalid User\n" RESET);
        result = 0;
    }
    printf(GREEN "\n\tPress any key to continue " RESET);
    getchar();
    getchar();
    return result;
}
// --------------------------------------------------------------------------------------------

typedef struct Equipment_Inventory
{
    int available, Quantity, issueQuantity;
    char Sport[15];
    char equipment[15];
} Equipment_Inventory;

typedef struct Sport_Equipment_Management
{
    int issueDate, dueDate, returnDate, daysDelayed, fine;
    long int studentID;
    char equipmentID[10];
    char equipment[15];
    char incharge[15];
    char Sport[15];
} Sport_Equipment_Management;

typedef struct Node1
{
    Equipment_Inventory data;
    struct Node1 *next;
} Node1;

typedef struct Node2
{
    Sport_Equipment_Management data;
    struct Node2 *next;
} Node2;

void swap1(Node1 *a, Node1 *b)
{
    Equipment_Inventory equipInvent = a->data;
    a->data = b->data;
    b->data = equipInvent;
}

void swap2(Node2 *a, Node2 *b)
{
    Sport_Equipment_Management equipManage = a->data;
    a->data = b->data;
    b->data = equipManage;
}

void Insert_Equipment_Inventory(Node1 **head, Equipment_Inventory record)
{
    Node1 *temp = (Node1 *)malloc(sizeof(Node1));
    temp->data = record;
    temp->next = *head;
    *head = temp;
}

void Insert_Sport_Equipment_Management(Node2 **head, Sport_Equipment_Management record)
{
    Node2 *temp = (Node2 *)malloc(sizeof(Node2));
    temp->data = record;
    temp->next = *head;
    *head = temp;
}

void addSpaces(char word[])
{
    int len1 = strlen(word);
    if (len1 < 8)
    {
        for (int i = len1; i < 8; i++)
        {
            word[i] = ' ';
        }
        word[8] = '\0';
    }
}

void Display_Equipment_Inventory(Node1 *head)
{
    system("clear");
    printf(MAGENTA "\n\t\t\t\t=======Equipment Inventory Record=======\n" RESET);
    int i = 1;
    printf(BLUE "\nSNo\tSport \t\tEquipment Name\t\tQuantity \tAvailable \tIssueQuantity\n");
    printf("---------------------------------------------------------------------------------------------\n" RESET);
    while (head != NULL)
    {
        char sport[15];
        char equip[15];
        strcpy(sport, head->data.Sport);
        strcpy(equip, head->data.equipment);
        addSpaces(sport);
        addSpaces(equip);
        printf(YELLOW " %d\t%s\t%s\t\t%d\t\t%d\t\t%d\n" RESET, i, sport, equip, head->data.Quantity, head->data.available, head->data.issueQuantity);
        head = head->next;
        i++;
    }
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
}

void Display_Sport_Equipment_Management(Node2 *head)
{
    system("clear");
    printf(MAGENTA "\n\t\t\t\t\t\t\t=======Sport Equipment Management Record=======\n" RESET);
    int i = 1;
    printf(BLUE "\nSNo\tIncharge\tStudent ID\tSport\t\tEquipment Name\tEquipment ID\tIssue date\tDue date\tReturn date\tDays delayed\tFine\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);
    while (head != NULL)
    {
        // Calculate Date.
        int Iday = head->data.issueDate / pow(10, 6);
        int Imonth = (head->data.issueDate / 10000) % 100;
        int Iyear = head->data.issueDate % 10000;
        int Dday = head->data.dueDate / pow(10, 6);
        int Dmonth = (head->data.dueDate / 10000) % 100;
        int Dyear = head->data.dueDate % 10000;
        int Rday = head->data.returnDate / pow(10, 6);
        int Rmonth = (head->data.returnDate / 10000) % 100;
        int Ryear = head->data.returnDate % 10000;

        char sport[15];
        char equip[15];
        char Incharge[15];
        strcpy(Incharge, head->data.incharge);
        strcpy(sport, head->data.Sport);
        strcpy(equip, head->data.equipment);
        addSpaces(Incharge);
        addSpaces(sport);
        addSpaces(equip);
        printf(YELLOW " %d\t%s\t%ld\t%s\t%s\t%s\t\t%.2d-%.2d-%.4d\t%.2d-%.2d-%.4d\t%.2d-%.2d-%.4d\t\t%d \t%d\n" RESET,
               i, Incharge, head->data.studentID, sport, equip, head->data.equipmentID, Iday, Imonth, Iyear,
               Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, head->data.daysDelayed, head->data.fine);
        head = head->next;
        i++;
    }
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
}

int countNode_Inventory(Node1 *head)
{
    int cnt = 0;
    while (head != NULL)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}

int countNode_Management(Node2 *head)
{
    int cnt = 0;
    while (head != NULL)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}

void bubbleSort(Node2 *head2)
{
    int len = countNode_Management(head2);
    for (int i = 0; i < len - 1; i++)
    {
        Node2 *curr = head2;
        for (int j = 0; j < len - 1; j++)
        {
            if ((curr->data.dueDate) % 10000 < (curr->next->data.dueDate) % 10000) // compared year wise.
            {
                swap2(curr, curr->next); // swap the node's value in LL.
            }
            else if ((curr->data.dueDate) % 10000 <= (curr->next->data.dueDate) % 10000 &&
                     ((curr->data.dueDate) / 10000) % 100 < ((curr->next->data.dueDate) / 10000) % 100) // compared month wise.
            {
                swap2(curr, curr->next); // swap the node's value in LL.
            }
            else if ((curr->data.dueDate) % 10000 <= (curr->next->data.dueDate) % 10000 &&
                     ((curr->data.dueDate) / 10000) % 100 <= ((curr->next->data.dueDate) / 10000) % 100 &&
                     (curr->data.dueDate) / 1000000 < (curr->next->data.dueDate) / 1000000) // compared day wise.
            {
                swap2(curr, curr->next); // swap the node's value in LL.
            }
            curr = curr->next;
        }
    }
}

void Student_History(Node2 *head)
{
    bubbleSort(head);
    system("clear");
    printf(MAGENTA "\n\t\t\t\t\t\t=======Student Check-in and Check-out of Sports Equipment=======\n" RESET);
    getchar();
    long int studId;
    int flag = 0;
    printf(CYAN "\n Enter your studentId : " RESET);
    scanf("%ld", &studId);

    // printf("\n Issued equipment");
    printf(GREEN "\n Check-out" RESET);
    int i = 1;
    Node2 *curr = head;
    while (curr != NULL)
    {
        if (curr->data.studentID == studId && curr->data.returnDate == 0)
        {
            if (flag == 0)
            {
                printf(BLUE "\nSNo\tIncharge\tStudent ID\tSport\t\tEquipment Name\tEquipment ID\tIssue date\tDue date\tReturn date\tDays delayed\tFine\n");
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);
            }
            // Calculate Date.
            int Iday = curr->data.issueDate / pow(10, 6);
            int Imonth = (curr->data.issueDate / 10000) % 100;
            int Iyear = curr->data.issueDate % 10000;
            int Dday = curr->data.dueDate / pow(10, 6);
            int Dmonth = (curr->data.dueDate / 10000) % 100;
            int Dyear = curr->data.dueDate % 10000;
            int Rday = curr->data.returnDate / pow(10, 6);
            int Rmonth = (curr->data.returnDate / 10000) % 100;
            int Ryear = curr->data.returnDate % 10000;

            char sport[15];
            char equip[15];
            char Incharge[15];
            strcpy(Incharge, curr->data.incharge);
            strcpy(sport, curr->data.Sport);
            strcpy(equip, curr->data.equipment);
            addSpaces(Incharge);
            addSpaces(sport);
            addSpaces(equip);
            printf(YELLOW " %d\t%s\t%ld\t%s\t%s\t%s\t\t%.2d-%.2d-%.4d\t%.2d-%.2d-%.4d\t%.2d-%.2d-%.4d\t\t%d\t%d\n" RESET,
                   i, Incharge, curr->data.studentID, sport, equip, curr->data.equipmentID, Iday, Imonth, Iyear,
                   Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, curr->data.daysDelayed, curr->data.fine);
            i++;
            flag++;
        }
        curr = curr->next;
    }
    if (flag == 0)
    {
        printf(YELLOW "\n\n No Equipment to Return\n" RESET);
    }

    // printf("\n Returned equipment");
    printf(GREEN "\n Check-in" RESET);
    flag = 0;
    i = 1;
    curr = head;
    while (curr != NULL)
    {
        if (curr->data.studentID == studId && curr->data.returnDate != 0)
        {
            if (flag == 0)
            {
                printf(BLUE "\nSNo\tIncharge\tStudent ID\tSport\t\tEquipment Name\tEquipment ID\tIssue date\tDue date\tReturn date\tDays delayed\tFine\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n" RESET);
            }
            // Calculate Date.
            int Iday = curr->data.issueDate / pow(10, 6);
            int Imonth = (curr->data.issueDate / 10000) % 100;
            int Iyear = curr->data.issueDate % 10000;
            int Dday = curr->data.dueDate / pow(10, 6);
            int Dmonth = (curr->data.dueDate / 10000) % 100;
            int Dyear = curr->data.dueDate % 10000;
            int Rday = curr->data.returnDate / pow(10, 6);
            int Rmonth = (curr->data.returnDate / 10000) % 100;
            int Ryear = curr->data.returnDate % 10000;

            char sport[15];
            char equip[15];
            char Incharge[15];
            strcpy(Incharge, curr->data.incharge);
            strcpy(sport, curr->data.Sport);
            strcpy(equip, curr->data.equipment);
            addSpaces(Incharge);
            addSpaces(sport);
            addSpaces(equip);
            printf(YELLOW " %d\t%s\t%ld\t%s\t%s\t%s\t\t%.2d-%.2d-%.4d\t%.2d-%.2d-%.4d\t%.2d-%.2d-%.4d\t\t%d\t%d\n" RESET, i,
                   Incharge, curr->data.studentID, sport, equip, curr->data.equipmentID, Iday, Imonth, Iyear,
                   Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, curr->data.daysDelayed, curr->data.fine);
            i++;
            flag++;
        }
        curr = curr->next;
    }
    if (flag == 0)
    {
        printf(YELLOW "\n\n No records found" RESET);
    }
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
    getchar();
}

int isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int getMonthDays(int month, int year)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    else
        return days[month - 1];
}

int updateDate(int date)
{
    int day = date / pow(10, 6);
    int month = (date / 10000) % 100;
    int year = date % 10000;
    int monthDays = getMonthDays(month, year);
    day += 15;
    if (day > monthDays)
    {
        day -= monthDays;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
    return day * pow(10, 6) + month * 10000 + year;
}

int calculateDays(int due_date, int return_date)
{
    int startDay = due_date / pow(10, 6);
    int startMonth = (due_date / 10000) % 100;
    int startYear = due_date % 10000;

    int endDay = return_date / pow(10, 6);
    int endMonth = (return_date / 10000) % 100;
    int endYear = return_date % 10000;

    int days = 0;
    while (startYear < endYear || startMonth < endMonth || startDay < endDay)
    {
        days++;
        startDay++;
        if (startDay > getMonthDays(startMonth, startYear))
        {
            startDay = 1;
            startMonth++;
        }
        if (startMonth > 12)
        {
            startMonth = 1;
            startYear++;
        }
    }
    return days;
}

int nearest_Availibility_Date(Node2 *head2)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // system date.
    int sys_date = tm.tm_mday;
    int sys_month = tm.tm_mon + 1;
    int sys_year = tm.tm_year + 1900;
    // min date.
    int min_day = 1;
    int min_month = 1;
    int min_year = 100000;
    Node2 *curr = head2;
    while (curr != NULL)
    {
        if ((((curr->data.dueDate) % 10000 > sys_year) ||
             ((curr->data.dueDate) % 10000 == sys_year && ((curr->data.dueDate) % 1000000) / 10000 > sys_month) ||
             ((curr->data.dueDate) % 10000 == sys_year && ((curr->data.dueDate) % 1000000) / 10000 == sys_month && (curr->data.dueDate) / 1000000 >= sys_date)) &&
            (((curr->data.dueDate) % 10000 < min_year) ||
             ((curr->data.dueDate) % 10000 == min_year && ((curr->data.dueDate) % 1000000) / 10000 < min_month) ||
             ((curr->data.dueDate) % 10000 == min_year && ((curr->data.dueDate) % 1000000) / 10000 == min_month && (curr->data.dueDate) / 1000000 < min_day))) // compared year wise.
        {
            min_day = (curr->data.dueDate) / 1000000;
            min_month = ((curr->data.dueDate) % 1000000) / 10000;
            min_year = (curr->data.dueDate) % 10000;
        }
        curr = curr->next;
    }
    if (min_year != 100000 && min_month != 1 && min_day != 1)
        return min_day * 1000000 + min_month * 10000 + min_year;
    else
        return 0;
}

bool check_Quantity(Node1 *head1, char sport[], char equip[])
{
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sport) == 0 && strcmp(head1->data.equipment, equip) == 0)
        {
            if (head1->data.available != 0)
            {
                head1->data.available--;
                head1->data.issueQuantity++;
                return 1;
            }
            else
                return 0;
        }
        head1 = head1->next;
    }
    return 0;
}

void equipment_issue(Node1 *head1, Node2 **head2, char sport[], char equip[])
{
    if (check_Quantity(head1, sport, equip) == 0)
    {
        int nearestAvailableDate = nearest_Availibility_Date(*head2);
        if (nearestAvailableDate != 0)
        {
            printf(YELLOW " Desired equipment is not available now!" RESET);
            printf(CYAN "\n Equipment will be available by : %.2d-%.2d-%.4d\n" RESET, nearestAvailableDate / 1000000,
                   (nearestAvailableDate % 1000000) / 10000, nearestAvailableDate % 10000);
        }
        else
        {
            printf(CYAN "\n Desired equipment is not available for Issue\n" RESET);
        }
    }
    else
    {
        Sport_Equipment_Management equipManage;
        strcpy(equipManage.Sport, sport);
        strcpy(equipManage.equipment, equip);

        printf(MAGENTA "\n Fill details(i.e use only lowercase character)\n" RESET);
        printf(YELLOW "\n Incharge : " RESET);
        scanf("%[^\n]", equipManage.incharge);
        printf(YELLOW "\n Student ID : " RESET);
        scanf("%ld", &equipManage.studentID);
        printf(YELLOW "\n Equipment ID : " RESET);
        scanf("%s", equipManage.equipmentID);
        equipManage.daysDelayed = 0;
        equipManage.fine = 0;

        // date
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        equipManage.issueDate = (tm.tm_mday) * 1000000 + (tm.tm_mon + 1) * 10000 + tm.tm_year + 1900;
        equipManage.returnDate = 0;
        equipManage.dueDate = updateDate(equipManage.issueDate);

        // insert record.
        Insert_Sport_Equipment_Management(head2, equipManage);

        // display
        printf(CYAN "\n Your due date is 15 days from now : %.2d-%.2d-%.4d\n" RESET, equipManage.dueDate / 1000000,
               (equipManage.dueDate % 1000000) / 10000, equipManage.dueDate % 10000);
        printf(GREEN "\n Issued Successfully\n" RESET);
    }
}

void user_issue(Node1 *head1, Node2 **head2)
{
    system("clear");
    printf(MAGENTA "=======Issue Sports Equipment=======\n" RESET);
    int choice, equip_No;
    char sport[15];
    char equip[15];

    // Display Sports
    Node1 *curr = head1;
    printf(BLUE "\nSNo\tSport\n");
    printf("------------------\n" RESET);
    int i = 1;
    printf(YELLOW " %d\t%s\n" RESET, i, curr->data.Sport);
    curr = curr->next;
    i++;
    while (curr != NULL)
    {
        int flag = 0;
        Node1 *check = head1;
        while (check != curr)
        {
            if (strcmp(curr->data.Sport, check->data.Sport) == 0)
            {
                flag++;
                break;
            }
            check = check->next;
        }
        if (flag == 0)
        {
            printf(YELLOW " %d\t%s\n" RESET, i, curr->data.Sport);
            i++;
        }
        curr = curr->next;
    }
    printf(CYAN "Choose your desired sport : " RESET);
    scanf("%d", &choice);
    getchar();

    // Store Sports Name.
    curr = head1;
    i = 0;
    while (curr != NULL)
    {
        int flag = 0;
        Node1 *check = head1;
        while (check != curr)
        {
            if (strcmp(curr->data.Sport, check->data.Sport) == 0)
            {
                flag++;
                break;
            }
            check = check->next;
        }
        if (flag == 0)
        {
            i++;
            if (i == choice)
            {
                break;
            }
        }
        curr = curr->next;
    }
    if (curr != NULL)
    {
        strcpy(sport, curr->data.Sport);
    }
    else
    {
        printf(RED "\n Invalid Input!!\n" RESET);
        printf(GREEN "\n \t Press any key to exit" RESET);
        getchar();
        return;
    }

    // Display Equipments.
    curr = head1;
    printf(BLUE "\n\nSNo\tEquipment\n");
    printf("------------------\n" RESET);
    i = 1;
    while (curr != NULL)
    {
        if (strcmp(sport, curr->data.Sport) == 0)
        {
            printf(YELLOW " %d\t%s\n" RESET, i, curr->data.equipment);
            i++;
        }
        curr = curr->next;
    }
    printf(BLUE "\nChoose the equipment : " RESET);
    scanf("%d", &choice);
    getchar();

    // Store Equipment Name.
    curr = head1;
    i = 0;
    while (curr != NULL)
    {
        if (strcmp(sport, curr->data.Sport) == 0)
        {
            i++;
            if (i == choice)
            {
                break;
            }
        }
        curr = curr->next;
    }
    if (curr != NULL)
    {
        strcpy(equip, curr->data.equipment);
    }
    else
    {
        printf(RED "\n Invalid Input!!\n" RESET);
        printf(GREEN "\n \t Press any key to exit" RESET);
        getchar();
        return;
    }
    equipment_issue(head1, head2, sport, equip);

    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
    getchar();
}

void user_display_Quantity(Node1 *head1, char sport[], char equip[])
{
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sport) == 0 && strcmp(head1->data.equipment, equip) == 0)
        {
            if (head1->data.available != 0)
            {
                printf(GREEN "\n Equipment is available\n");
                return;
            }
            break;
        }
        head1 = head1->next;
    }
    printf("\n Equipment is not available\n" RESET);
}

void User_Check_Availability(Node1 *head1, Node2 *head2)
{
    system("clear");
    printf(MAGENTA "=======Check Availibality of Sport Equipment=======\n" RESET);
    int choice, equip_No;
    char sport[15];
    char equip[15];

    // Display Sports
    Node1 *curr = head1;
    printf(BLUE "\nSNo\tSport\n");
    printf("------------------\n" RESET);
    int i = 1;
    printf(YELLOW " %d\t%s\n" RESET, i, curr->data.Sport);
    curr = curr->next;
    i++;
    while (curr != NULL)
    {
        int flag = 0;
        Node1 *check = head1;
        while (check != curr)
        {
            if (strcmp(curr->data.Sport, check->data.Sport) == 0)
            {
                flag++;
                break;
            }
            check = check->next;
        }
        if (flag == 0)
        {
            printf(YELLOW " %d\t%s\n" RESET, i, curr->data.Sport);
            i++;
        }
        curr = curr->next;
    }
    printf(CYAN "Choose your desired sport : " RESET);
    scanf("%d", &choice);
    getchar();

    // Store Sports Name.
    curr = head1;
    i = 0;
    while (curr != NULL)
    {
        int flag = 0;
        Node1 *check = head1;
        while (check != curr)
        {
            if (strcmp(curr->data.Sport, check->data.Sport) == 0)
            {
                flag++;
                break;
            }
            check = check->next;
        }
        if (flag == 0)
        {
            i++;
            if (i == choice)
            {
                break;
            }
        }
        curr = curr->next;
    }
    if (curr != NULL)
    {
        strcpy(sport, curr->data.Sport);
    }
    else
    {
        printf(RED "\n Invalid Input!!\n" RESET);
        printf(GREEN "\n \t Press any key to exit" RESET);
        getchar();
        return;
    }

    // Display Equipments.
    curr = head1;
    printf(MAGENTA "\n\nSNo\tEquipment\n");
    printf("------------------\n" RESET);
    i = 1;
    while (curr != NULL)
    {
        if (strcmp(sport, curr->data.Sport) == 0)
        {
            printf(YELLOW " %d\t%s\n" RESET, i, curr->data.equipment);
            i++;
        }
        curr = curr->next;
    }
    printf(CYAN "\nChoose the equipment : " RESET);
    scanf("%d", &choice);
    getchar();

    // Store Equipment Name.
    curr = head1;
    i = 0;
    while (curr != NULL)
    {
        if (strcmp(sport, curr->data.Sport) == 0)
        {
            i++;
            if (i == choice)
            {
                break;
            }
        }
        curr = curr->next;
    }
    if (curr != NULL)
    {
        strcpy(equip, curr->data.equipment);
    }
    else
    {
        printf(RED "\n Invalid Input!!\n" RESET);
        printf(GREEN "\n \t Press any key to exit" RESET);
        getchar();
        return;
    }
    // call the "user_display_Quantity" function.
    user_display_Quantity(head1, sport, equip);

    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
}

void user_return(Node1 *head1, Node2 *head2)
{
    system("clear");
    printf(MAGENTA "\t\t=======Return Sports Equipment=======\n" RESET);
    long int studId;
    char equipId[10];
    printf(BLUE "\n Fill Details(i.e use only lowercase character)\n" RESET);
    printf(YELLOW "\n StudentID : " RESET);
    scanf("%ld", &studId);
    printf(YELLOW "\n EquipmentID : " RESET);
    scanf("%s", equipId);
    getchar();
    while (head2 != NULL)
    {
        if (head2->data.studentID == studId && strcmp(head2->data.equipmentID, equipId) == 0)
        {
            // update available equipments & issueQuantity.
            while (head1)
            {
                if (strcmp(head1->data.Sport, head2->data.Sport) == 0 && strcmp(head1->data.equipment, head2->data.equipment) == 0)
                {
                    head1->data.available++;
                    head1->data.issueQuantity--;
                    break;
                }
                head1 = head1->next;
            }
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            head2->data.returnDate = (tm.tm_mday) * 1000000 + (tm.tm_mon + 1) * 10000 + tm.tm_year + 1900;

            // call program to find number of days delay in return.
            head2->data.daysDelayed = calculateDays(head2->data.dueDate, head2->data.returnDate);
            head2->data.fine = (head2->data.daysDelayed) * 10;
            // printf fine.
            printf(BLUE "\n Days delayed = %d" RESET, head2->data.daysDelayed);
            printf(BLUE "\nFine = %d Rs\n" RESET, head2->data.fine);
            printf(CYAN "\n Returned successfully\n" RESET);
            printf(GREEN "\n \t Press any key to exit" RESET);
            getchar();
            return;
        }
        head2 = head2->next;
    }
    printf(RED "\n You havn't issue any sports equipment\n" RESET);
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
}

void DISPLAY_Equipment_Inventory_By_Sport(Node1 *head1)
{
    system("clear");
    printf(MAGENTA "\n\t\t=======Equipment Inventory Records=======\n\n" RESET);
    int flag = 0;
    int i = 1;

    char sports[15];
    printf(YELLOW "Enter the sports name : " RESET);
    scanf("%[^\n]", sports);
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sports) == 0)
        {
            if (flag == 0)
            {
                printf(BLUE "\nSNo\tSport \t\tEquipment Name\t\tQuantity \tAvailable \tIssueQuantity\n");
                printf("---------------------------------------------------------------------------------------------\n" RESET);
            }
            char sport[15];
            char equip[15];
            strcpy(sport, head1->data.Sport);
            strcpy(equip, head1->data.equipment);
            addSpaces(sport);
            addSpaces(equip);
            printf(YELLOW " %d\t%s\t%s\t\t%d\t\t%d\t\t%d\n" RESET, i, sport, equip, head1->data.Quantity,
                   head1->data.available, head1->data.issueQuantity);
            flag++;
            i++;
        }
        head1 = head1->next;
    }
    if (flag == 0)
    {
        printf(YELLOW "\nNo results found?\n\n" RESET);
    }
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
    getchar();
}

void Modify_Equipment_Inventory_Quantity(Node1 *head1)
{
    // Modify sports equipment quantity
    system("clear");
    printf(MAGENTA "=======Modify Sport Equipment Quantity=======\n" RESET);
    int choice, equip_No;
    char sport[15];
    char equip[15];

    // Display Sports
    Node1 *curr = head1;
    printf(BLUE "\nSNo\tSport\n");
    printf("------------------\n" RESET);
    int i = 1;
    printf(YELLOW " %d\t%s\n" RESET, i, curr->data.Sport);
    curr = curr->next;
    i++;
    while (curr != NULL)
    {
        int flag = 0;
        Node1 *check = head1;
        while (check != curr)
        {
            if (strcmp(curr->data.Sport, check->data.Sport) == 0)
            {
                flag++;
                break;
            }
            check = check->next;
        }
        if (flag == 0)
        {
            printf(YELLOW " %d\t%s\n" RESET, i, curr->data.Sport);
            i++;
        }
        curr = curr->next;
    }
    printf(CYAN "Enter your desired sport : " RESET);
    scanf("%d", &choice);
    getchar();

    // Store Sports Name.
    curr = head1;
    i = 0;
    while (curr != NULL)
    {
        int flag = 0;
        Node1 *check = head1;
        while (check != curr)
        {
            if (strcmp(curr->data.Sport, check->data.Sport) == 0)
            {
                flag++;
                break;
            }
            check = check->next;
        }
        if (flag == 0)
        {
            i++;
            if (i == choice)
            {
                break;
            }
        }
        curr = curr->next;
    }
    if (curr != NULL)
    {
        strcpy(sport, curr->data.Sport);
    }
    else
    {
        printf(RED "\n Invalid Input!!\n" RESET);
        printf(GREEN "\n \t Press any key to exit" RESET);
        getchar();
        return;
    }

    // Display Equipments.
    curr = head1;
    printf(MAGENTA "\n\nSNo\tEquipment\n");
    printf("------------------\n" RESET);
    i = 1;
    while (curr != NULL)
    {
        if (strcmp(sport, curr->data.Sport) == 0)
        {
            printf(YELLOW " %d\t%s\n" RESET, i, curr->data.equipment);
            i++;
        }
        curr = curr->next;
    }
    printf(CYAN "\nChoose the equipment : " RESET);
    scanf("%d", &choice);
    getchar();

    // Store Equipment Name.
    curr = head1;
    i = 0;
    while (curr != NULL)
    {
        if (strcmp(sport, curr->data.Sport) == 0)
        {
            i++;
            if (i == choice)
            {
                break;
            }
        }
        curr = curr->next;
    }
    if (curr != NULL)
    {
        strcpy(equip, curr->data.equipment);
    }
    else
    {
        printf(RED "\n Invalid Input!!\n" RESET);
        printf(GREEN "\n \t Press any key to exit" RESET);
        getchar();
        return;
    }

    curr = head1;
    int quantity;
    while (curr != NULL)
    {
        if (strcmp(curr->data.Sport, sport) == 0 && strcmp(curr->data.equipment, equip) == 0)
        {
            printf(BLUE "\n Initial Quantity : %d" RESET, curr->data.Quantity);
            printf(YELLOW "\n Enter quantity: " RESET);
            scanf("%d", &quantity);
            getchar();
            if (quantity >= curr->data.Quantity)
            {
                curr->data.available = curr->data.Quantity - curr->data.issueQuantity;
            }
            else
            {
                if (curr->data.issueQuantity >= quantity)
                {
                    curr->data.issueQuantity = quantity;
                    curr->data.available = 0;
                }
                else
                {
                    curr->data.available = quantity - curr->data.issueQuantity;
                }
            }
            curr->data.Quantity = quantity;
            printf(BLUE "\n Record modified successfully\n" RESET);
            break;
        }
        curr = curr->next;
    }
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
}

void Add_record_equipment_inventory(Node1 **head1)
{
    Equipment_Inventory equipInvent;
    printf(MAGENTA "\n Fill details(i.e use only lowercase character)\n" RESET);
    printf(YELLOW "\n Sport : " RESET);
    scanf("%[^\n]", equipInvent.Sport);
    getchar();
    printf(YELLOW "\n Equipment name : " RESET);
    scanf("%[^\n]", equipInvent.equipment);
    getchar();
    printf(YELLOW "\n Quantity : " RESET);
    scanf("%d", &equipInvent.Quantity);
    equipInvent.available = equipInvent.Quantity;
    equipInvent.issueQuantity = 0;
    Insert_Equipment_Inventory(head1, equipInvent);
    printf(CYAN "\n Record added successfully\n" RESET);
    printf(GREEN "\n \t Press any key to exit" RESET);
    getchar();
    getchar();
}

void Import_Database(Node1 **head1, Node2 **head2)
{
    FILE *fp;
    fp = fopen("Equipment_Inventory.txt", "r");
    Equipment_Inventory equipInvent;
    int n;
    fscanf(fp, "%d", &n);
    while (n--)
    {
        fscanf(fp, "%d %d %d %[^\n] %[^\n]", &equipInvent.available, &equipInvent.Quantity, &equipInvent.issueQuantity,
               equipInvent.Sport, equipInvent.equipment);
        Insert_Equipment_Inventory(head1, equipInvent);
    }
    fclose(fp);

    fp = fopen("Sport_Equipment_Management.txt", "r");
    Sport_Equipment_Management equipManage;
    fscanf(fp, "%d", &n);
    while (n--)
    {
        fscanf(fp, "%s %d %d %d %d %d %ld %[^\n] %[^\n] %[^\n]", equipManage.equipmentID, &equipManage.issueDate,
               &equipManage.dueDate, &equipManage.returnDate, &equipManage.daysDelayed, &equipManage.fine,
               &equipManage.studentID, equipManage.equipment, equipManage.incharge, equipManage.Sport);
        Insert_Sport_Equipment_Management(head2, equipManage);
    }
    fclose(fp);
}

void Update_Database(Node1 *head1, Node2 *head2)
{
    FILE *fp;
    fp = fopen("Equipment_Inventory.txt", "w");
    int len = countNode_Inventory(head1);
    fprintf(fp, "%d\n", len);
    while (head1 != NULL)
    {
        fprintf(fp, "%d %d %d\n%s\n%s\n", head1->data.available, head1->data.Quantity,
                head1->data.issueQuantity, head1->data.Sport, head1->data.equipment);
        head1 = head1->next;
    }
    fclose(fp);

    fp = fopen("Sport_Equipment_Management.txt", "w");
    len = countNode_Management(head2);
    fprintf(fp, "%d\n", len);
    while (head2 != NULL)
    {
        fprintf(fp, "%s %d %d %d %d %d %ld\n%s\n%s\n%s\n", head2->data.equipmentID, head2->data.issueDate, head2->data.dueDate,
                head2->data.returnDate, head2->data.daysDelayed, head2->data.fine, head2->data.studentID, head2->data.equipment,
                head2->data.incharge, head2->data.Sport);
        head2 = head2->next;
    }
    fclose(fp);
}

void login(int *who)
{
    do
    {
        system("clear");
        title();
        printf(MAGENTA "\n\tSelect Account\n" RESET);
        printf(YELLOW "\n 1. User\n\n 2. Admin \n\n 3. Exit\n" RESET);
        printf(BLUE "\nEnter your choice : " RESET);
        scanf("%d", who);
        if (*who == 2)
        {
            *who = Verification();
        }
    } while (*who != 1 && *who != 2 && *who != 3);
}

int main()
{
    Node1 *head1 = NULL;
    Node2 *head2 = NULL;
    Import_Database(&head1, &head2);
    int who;
    login(&who);
    do
    {
        switch (who)
        {
        case 1:
            system("clear");
            int user_choose;
            printf(MAGENTA "\n\t\tWelcome!!\n\n You have logged into the student account\n" RESET);
            printf(YELLOW "\n 1. Issue \n 2. Return \n 3. Check-in and check-out log \n 4. Check Availability \n 5. Quit \n\n" RESET);
            printf(BLUE " Choose your work : " RESET);
            scanf("%d", &user_choose);
            switch (user_choose)
            {
            case 1:
                user_issue(head1, &head2);
                break;
            case 2:
                user_return(head1, head2);
                break;
            case 3:
                Student_History(head2);
                break;
            case 4:
                User_Check_Availability(head1, head2);
                break;
            case 5:
                login(&who);
                break;
            default:
                break;
            }
            break;
        case 2:
            system("clear");
            int admin_choose;
            printf(MAGENTA "\n\t\tWelcome!!\n\n You have logged into the admin account\n" RESET);
            printf(YELLOW "\n 1. Display equipments inventory record \n 2. Display equipments inventory records by sports name \n 3. Display sport equipment management records \n 4. Modify sports equipment quantity \n 5. Add a new record in equipment inventory \n 6. Quit \n\n" RESET);
            printf(BLUE " Choose your work : " RESET);
            scanf("%d", &admin_choose);
            getchar();
            switch (admin_choose)
            {
            case 1:
                Display_Equipment_Inventory(head1);
                break;
            case 2:
                DISPLAY_Equipment_Inventory_By_Sport(head1);
                break;
            case 3:
                bubbleSort(head2);
                Display_Sport_Equipment_Management(head2);
                break;
            case 4:
                Modify_Equipment_Inventory_Quantity(head1);
                break;
            case 5:
                Add_record_equipment_inventory(&head1);
                break;
            case 6:
                login(&who);
                break;
            default:
                break;
            }
            break;
        case 3:
            Update_Database(head1, head2);
            return 0;
        }
    } while (true);
    return 0;
}