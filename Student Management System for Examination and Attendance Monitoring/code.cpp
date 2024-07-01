#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

typedef struct Data_Gen_tag
{
	char Name[30];
	char Dep_Code[4];
	//int year;
	int sem;
	char Roll_No[11];
	int Sub[6];
	int attendance[7];
	int application;
	int fee_status;
}Data_Gen;

typedef Data_Gen Item_Type;

typedef struct Tree_Node_tag
{
	Item_Type data;
    struct Tree_Node_tag* left;
    struct Tree_Node_tag* right;
    int height;
    int traverse1;
    int traverse2;
}Tree_Node;

// Calculate height
int height(Tree_Node* node) 
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

int max(int a, int b) 
{
    int retval;
    if (a > b)
    {
        retval = a;
    }
    else
    {
        retval = b;
    }
    return retval;
}

int compare_data(Item_Type data1, Item_Type data2)
{
    int retval;
    if (data1.sem < data2.sem)
    {
        retval = -1;
    }
    else if (data1.sem > data2.sem)
    {
        retval = 1;
    }
    else
    {
        if (strcmp(data1.Dep_Code, data2.Dep_Code) < 0)
        {
            retval = -1;
        }
        else if (strcmp(data1.Dep_Code, data2.Dep_Code) > 0)
        {
            retval = 1;
        }
        else
        {
            if (strcmp(data1.Roll_No, data2.Roll_No) < 0)
            {
                retval = -1;
            }
            else if (strcmp(data1.Roll_No, data2.Roll_No) > 0)
            {
                retval = 1;
            }
            else
            {
                retval = 0;
            }
        }
    }

    return retval;
}
void copy_data(Item_Type* data1, Item_Type* data2)
{
    data1->application = data2->application;
    strcpy_s(data1->Dep_Code, 4, data2->Dep_Code);
    strcpy_s(data1->Name, 30, data2->Name);
    strcpy_s(data1->Roll_No, 11, data2->Roll_No);
    data1->fee_status = data2->fee_status;
    data1->sem = data2->sem;
    int i;
    for (i = 0; i < 7; i++)
    {
        data1->attendance[i] = data2->attendance[i];
    }
    for (i = 0; i < 6; i++)
    {
        data1->Sub[i] = data2->Sub[i];
    }
}

// Create a node
Tree_Node* newNode(Item_Type data) 
{
    Tree_Node* node;
    node = (Tree_Node*)malloc(sizeof(Tree_Node));

    node->data = data;

    node->left = NULL;
    node->right = NULL;

    node->height = 1;
    node->traverse1 = 0;
    node->traverse2 = 0;
    return node;
}

// Right rotate
Tree_Node* rightRotate(Tree_Node* node) 
{
    Tree_Node* ptr = node->left;
    Tree_Node* temp = ptr->right;

    ptr->right = node;
    node->left = temp;

    node->height = max(height(node->left), height(node->right)) + 1;
    ptr->height = max(height(ptr->left), height(ptr->right)) + 1;

    return ptr;
}

// Left rotate
Tree_Node* leftRotate(Tree_Node* node) 
{
    Tree_Node* ptr = node->right;
    Tree_Node* temp = ptr->left;

    ptr->left = node;
    node->right = temp;

    node->height = max(height(node->left), height(node->right)) + 1;
    ptr->height = max(height(ptr->left), height(ptr->right)) + 1;

    return ptr;
}

// Get the balance factor
int Balance(Tree_Node* node) 
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Insert node
Tree_Node* insertNode(Tree_Node* node, Item_Type data) 
{
    // Find the correct position to insertNode the node and insertNode it
    if (node == NULL)
    {
        return (newNode(data));
    }

    if (compare_data(data, node->data) < 0) //make and insert compare function
    {
        node->left = insertNode(node->left, data);
    }
    else if (compare_data(data, node->data) > 0) //make and insert compare function
    {
        node->right = insertNode(node->right, data);
    }
    else
    {
        return node;
    }

    // Update the balance factor of each node and balance the tree

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = Balance(node);

    if (balance > 1 && compare_data(data, node->left->data) < 0) //make and insert compare function
    {
        return rightRotate(node);
    }

    if (balance < -1 && compare_data(data, node->right->data) > 0) //make and insert compare function
    {
        return leftRotate(node);
    }

    if (balance > 1 && compare_data(data, node->left->data) > 0)  //make and insert compare function
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && compare_data(data, node->right->data) < 0) //make and insert compare function
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Tree_Node* minValueNode(Tree_Node* node) 
{
    Tree_Node* current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Delete a nodes
Tree_Node* deleteNode(Tree_Node* root, Item_Type* data) 
{
    // Find the node and delete it
    if (root == NULL)
    {
        return root;
    }

    if (compare_data(*data, root->data) < 0) //make and insert compare function
    {
        root->left = deleteNode(root->left, data);
    }

    else if (compare_data(*data, root->data) > 0) //make and insert compare function
    {
        root->right = deleteNode(root->right, data);
    }

    else 
    {
        if ((root->left == NULL) || (root->right == NULL)) 
        {
            Tree_Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) 
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else 
        {
            Tree_Node* temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, &temp->data);
        }
    }

    if (root == NULL)
    {
        return root;
    }

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = Balance(root);

    if (balance > 1 && Balance(root->left) >= 0)
    {
        return rightRotate(root);
    }

    if (balance > 1 && Balance(root->left) < 0) 
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && Balance(root->right) <= 0)
    {
        return leftRotate(root);
    }

    if (balance < -1 && Balance(root->right) > 0) 
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void print_data(Item_Type data)
{
    printf("Sem: %d \t", data.sem);
    printf("Dep: %s \t", data.Dep_Code);
    printf("Roll No: %s \t", data.Roll_No);
    printf("Name: %s \t", data.Name);
    if (data.fee_status == 0)
    {
        printf("Fee Status: Pending \t");
    }
    else
    {
        printf("Fee status: Paid \t");
    }
    if (data.application == 0)
    {
        printf("Application Status: Pending \t");
    }
    else
    {
        printf("Application status: Done \t");
    }

    printf("MCC: %d\t", data.Sub[5]);
    printf("Attendance: %d\t", data.attendance[6]);
    
    printf("\n");
}

// Print the tree
void printInOrder(Tree_Node* root) 
{
    if (root != NULL) 
    {
        printInOrder(root->left);
        print_data(root->data); //data printer function
        printInOrder(root->right);
    }
}

Tree_Node* make_tree(Tree_Node* root)
{
    int flag = 1;
    int c;
    Item_Type data;
    int input = 0;

    FILE* fp;
    int x;
    errno_t error_code;
    error_code = fopen_s(&fp, "C:/Users/vishal raj/source/repos/Project with Avl/Input.txt", "r");
    if (error_code != 0)
    {
        printf_s("The file Input.txt was not opened\n");
    }
    else
    {
        while (flag == 1)
        {
            fscanf(fp, "%d", &flag);

            if (flag == 1)
            {

                fscanf(fp, "%d", &input);
                if (input == 1)
                {

                    fscanf(fp, "%s", &data.Dep_Code, sizeof(data.Dep_Code));

                    fscanf(fp, "%d", &data.sem);

                    for (x = 0; x < 5; x++)
                    {
                        fscanf(fp, "%d", &data.Sub[x]);
                    }
                }

                fscanf(fp, "%s", &data.Name, sizeof(data.Name));
                fscanf(fp, "%s", &data.Roll_No, sizeof(data.Roll_No));
                for (x = 0; x < 5; x++)
                {
                    fscanf(fp, "%d", &data.attendance[x]);
                }
                fscanf(fp, "%d", &data.application);
                fscanf(fp, "%d", &data.fee_status);
                root = insertNode(root, data);
            }
        }
    }
    fclose(fp);
    return root;
}

// finding mcc
int find_max(int arr[], int n)
{
    int i;
    int max = arr[0];
    int retval = 0;
    for (i = 1; i < n; i++)
    {
        if (arr[i] >= max)
        {
            max = arr[i];
            retval = i;
        }
    }

    return retval;
}

int totalNodes(Tree_Node* root)
{
    if (root == NULL)
        return 0;

    int l = totalNodes(root->left);
    int r = totalNodes(root->right);

    return 1 + l + r;
}

int max2(int a, int b)
{
    return (a > b ? a : b);
}
int max3(int a, int b, int c)
{
    if (a > b && a > c)
    {
        return a;
    }
    else if (b > c && b > a)
    {
        return b;
    }
    else
    {
        return c;
    }
}

int ret_with_attd(Tree_Node* root, int* mcc, int max)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        root->data.Sub[5] = *mcc;
        //printf("%d", root->data.Sub[5]);
        return max2(root->data.attendance[*mcc], max);
    }
    else
    {
        root->data.Sub[5] = *mcc;
        int l = ret_with_attd(root->left, mcc, max);
        int r = ret_with_attd(root->right, mcc, max);
        return max3(l, r, root->data.attendance[*mcc]);
    }
}

void ret_with_attd_per(Tree_Node* root, int* data)
{
    if (root == NULL)
    {
        return;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        root->data.attendance[5] = *data;
        int mcc = root->data.Sub[5];
        float x = root->data.attendance[mcc] * 100;
        root->data.attendance[6] = x / *data;
    }
    else
    {
        root->data.attendance[5] = *data;
        int mcc = root->data.Sub[5];
        int x = root->data.attendance[mcc] * 100;
        root->data.attendance[6] = x / *data;
        ret_with_attd_per(root->left, data);
        ret_with_attd_per(root->right, data);
    }
}

Tree_Node* search(Tree_Node* root,  char* dep, int sem)
{
    //Tree_Node* ret;
    // Base Cases: root is null or key is present at root
    if (root == NULL || (root->data.sem == sem && strcmp(dep, root->data.Dep_Code) == 0))
        return root;

    // Key is greater than root's key
    if (root->data.sem < sem)
    {
        return search(root->right, dep, sem);
    }
    else if(root->data.sem > sem)
    {// Key is smaller than root's key
        return search(root->left, dep, sem);
    }
    else
    {
        if (strcmp(dep, root->data.Dep_Code) > 0)
        {
            return search(root->right, dep, sem);
        }
        else
        {// Key is smaller than root's key
            return search(root->left, dep, sem);
        }
    }
}

Tree_Node* action(Tree_Node* root)
{
    Tree_Node* newtree = NULL;
    Tree_Node* temp = NULL;
    Tree_Node* node;

    Item_Type data;
    data.sem = 0;
    int SEM;
    char DEP[4];

    int count1 = 0;
    int count2 = 0;

    while (root != NULL)
    {
        SEM = root->data.sem;
        strcpy_s(DEP, 4, root->data.Dep_Code);

        count1 = totalNodes(root);
        count2 = 0;
        while (count1 != count2)
        {
            count1 = totalNodes(root);
            node = search(root, DEP, SEM);
            if (node != NULL)
            {
                //printf("%s", node->data.Name);
                copy_data(&data, &node->data);
                //printf("%s", data.Name);
                root = deleteNode(root, &data);
                node = NULL;
                temp = insertNode(temp, data);
            }
            count2 = totalNodes(root);
        }
        int mcc;

        mcc = find_max(temp->data.Sub, 5);
        int max = temp->data.attendance[mcc];
        //process to insert mcc and store attendance of each node
        max = ret_with_attd(temp, &mcc, max);
        ret_with_attd_per(temp, &max);

        while (temp != NULL)
        {
            copy_data(&data, &temp->data);
            //printf("%d %d %d", data.Sub[5], data.attendance[5], data.attendance[6]);
            temp = deleteNode(temp, &data);
            newtree = insertNode(newtree, data);
        }
    }
    return newtree;
}

Tree_Node* not_applied(Tree_Node* root, Tree_Node* newRoot)
{
    if (root == NULL)
    {
        return newRoot;
    }
    newRoot = not_applied(root->left, newRoot);
    if (root->data.application != 1)
    {
        newRoot = insertNode(newRoot, root->data);
    }
    newRoot = not_applied(root->right, newRoot);
    return newRoot;
}

Tree_Node* eligible(Tree_Node* root, Tree_Node* newRoot)
{
    if (root == NULL) 
    {
        return newRoot;
    }
    newRoot = eligible(root->left, newRoot);
    if (root->data.application == 1 && root->data.attendance[6] > 74)
    {
        newRoot  = insertNode(newRoot, root->data);
    }
    newRoot = eligible(root->right, newRoot);
    return newRoot;
}

Tree_Node* less_attendance(Tree_Node* root, Tree_Node* newRoot)
{
    if (root == NULL)
    {
        return newRoot;
    }
    newRoot = less_attendance(root->left, newRoot);
    if (root->data.attendance[6] < 75)
    {
        newRoot = insertNode(newRoot, root->data);
    }
    newRoot = less_attendance(root->right, newRoot);
    return newRoot;
}

Tree_Node* pending(Tree_Node* root, Tree_Node* newRoot)
{
    if (root == NULL)
    {
        return newRoot;
    }
    newRoot = pending(root->left, newRoot);
    if (root->data.fee_status == 0 && root->data.attendance[6] > 74)
    {
        newRoot = insertNode(newRoot, root->data);
    }
    newRoot = pending(root->right, newRoot);
    return newRoot;
}

int count[5] = { 0,0,0,0,0 };

Tree_Node* defaulter(Tree_Node* root, Tree_Node* newRoot)
{
    if (root == NULL)
    {
        return newRoot;
    }

    newRoot = defaulter(root->left, newRoot);

    if (root->data.attendance[6] < 75 || root->data.fee_status != 1)
    {
        if (strcmp("CSE", root->data.Dep_Code) == 0)
        {
            count[0]++;
        }
        else if (strcmp("ECE", root->data.Dep_Code) == 0)
        {
            count[1]++;
        }
        else if (strcmp("EEE", root->data.Dep_Code) == 0)
        {
            count[2]++;
        }
        else if (strcmp("MEC", root->data.Dep_Code) == 0)
        {
            count[3]++;
        }
        else if (strcmp("CIV", root->data.Dep_Code) == 0)
        {
            count[4]++;
        }
        newRoot = insertNode(newRoot, root->data);
    }
    newRoot = defaulter(root->right, newRoot);
    return newRoot;
}

void delete_tree(Tree_Node* root)
{
    while (root != NULL)
    {
        root = deleteNode(root, &root->data);
    }
}

void print_defaulter()
{
    int max = 0;
    int j = 0;
    for (int i = 0; i < 5; i++)
    {
        if (count[i] > max)
        {
            max = count[i];
            j = i;
        }
    }

    if (j == 0)
    {
        printf("Max Defaulter is: CSE\n");
    }
    else if (j == 1)
    {
        printf("Max Defaulter is: ECE\n");
    }
    else if (j == 2)
    {
        printf("Max Defaulter is: EEE\n");
    }
    else if (j == 3)
    {
        printf("Max Defaulter is: MEC\n");
    }
    else if (j == 4)
    {
        printf("Max Defaulter is: CIV\n");
    }
}

Tree_Node* rangeSort(Tree_Node* root, Tree_Node* newRoot, char* Roll1, char* Roll2)
{
    if (root == NULL)
    {
        return newRoot;
    }
    newRoot = rangeSort(root->left, newRoot, Roll1, Roll2);
    if (strcmp(root->data.Roll_No, Roll1) < 0 && strcmp(root->data.Roll_No, Roll2) > 0)
    {
        newRoot = insertNode(newRoot, root->data);
    }
    newRoot = rangeSort(root->right, newRoot, Roll1, Roll2);
    return newRoot;
}

int main() 
{
    Tree_Node* root = NULL;
    Tree_Node* Root = NULL;
    Tree_Node* Not_Applied = NULL;
    Tree_Node* Eligible = NULL;
    Tree_Node* Less_Attendance = NULL;
    Tree_Node* Pending = NULL;
    Tree_Node* Defaulter = NULL;

    root = make_tree(root);
    Root = action(root);

    //Not_Applied = not_applied(Root, Not_Applied);
    //Eligible = eligible(Root, Eligible);
    //Less_Attendance = less_attendance(Root, Less_Attendance);
    //Pending = pending(Root, Pending);
    //Defaulter = defaulter(Root, Defaulter);
    //print_defaulter();

    printInOrder(Root);

    //delete_tree(tree);
    delete_tree(Root);
    delete_tree(root);

    return 0;
}