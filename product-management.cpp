#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT 100
#define NAME_LENGTH 100

struct product_time
{
    int day;
    int month;
    int year;
};

struct product
{
    int product_id;
    char product_name[NAME_LENGTH];
    double product_price;
    struct product_time product_time;
    struct employee *employee;
};

struct employee
{
    int employee_id;
    char employee_name[NAME_LENGTH];
    int employee_age;
    char employee_gender[10];
    char employee_address[NAME_LENGTH];
    char employee_phoneNumber[10];
    int num_products_made;
};

struct node
{
    employee data;
    struct node *pNext;
};

typedef struct singlyLinkedList
{
    node *pHead;
    node *pTail;
} singeList;

void initEmployeeInformation(employee *employee);
node *creatNewNode(employee employee);
void linkInitialization(singeList &employeeList);
bool isEmpty(singeList &employeeList);
void addNewEmployee(singeList &employeeList, employee employee);
void addNewEmployeeList(singeList &employeeList, employee employee);
void addNewEmployeeListToFile(singeList &employeeList, employee employee);
void displayEmployeeList(singeList &employeeList);
bool checkEmployeePhoneNumber(const employee employee);
bool checkEmployeeAge(employee &employee);
bool isDuplicateID(const singeList &employeeList, int id);
void deleteNodeData(singeList &employeeList, employee employee);
void readEmployeeListFromFile(singeList &employeeList);
void saveEmployeeList(const singeList &employeeList);

void addNewProduct(product *&productList, int &num_of_product, singeList &employeeList);
void addNewProductList(product *&productList, int &num_of_product, singeList &employeeList);
void displayProductList(const product *productList, int num_of_product, singeList &employeeList);
void editProductByName(product *productList, int num_of_product);
void deleteProductByID(product *&productList, int &num_of_product);
void findMostContributingID(product *productList, int num_of_product);
void sortProductsByPrice(product *productList, int num_of_product);
void addProductToFile(const char* filename, product *productList, int &num_of_product);
void readProductListFromFile(product *&productList, int &num_of_product);
void saveProductList(const product *productList, int num_of_product);
bool checkTime(const product &product);
int checkPrice(const product &product);

void printMenu();
void printStatusMenu();
char *pop_str_last(char *str);

int main()
{
    int num_of_product = 0;
    product *productList = (product*)malloc(sizeof(product));

    int num_of_employee = 0;
    singeList employeeList; linkInitialization(employeeList);

    while(1)
    {
        printMenu();
        int choose;
        printf("\nPlease enter your choice: "); scanf("%d", &choose);

        switch(choose)
        {
        case 1:
            {
                readEmployeeListFromFile(employeeList);

                employee employee_case_1;
                addNewEmployee(employeeList, employee_case_1);
                
                char choose_case_1;
                int check_choose_case_1;
                do
                {
                    printStatusMenu();
                    printf("Please enter your choice: "); scanf("%c", &choose_case_1);
                    check_choose_case_1 = (int)choose_case_1;
                    if(check_choose_case_1 != 121 && check_choose_case_1 != 89 && check_choose_case_1 != 110 && check_choose_case_1 != 78)
                        printf("\nError: Invalid selection !");
                } while (check_choose_case_1 != 121 && check_choose_case_1 != 89 && check_choose_case_1 != 110 && check_choose_case_1 != 78);

                if(check_choose_case_1 == 121 || check_choose_case_1 == 89)
                    saveEmployeeList(employeeList);
                else if(check_choose_case_1 == 110 || check_choose_case_1 == 78)
                {
                    deleteNodeData(employeeList, employee_case_1);
                    saveEmployeeList(employeeList);
                }
                break;
            }

        case 2:
            {
                readEmployeeListFromFile(employeeList);

                node *pTmp_index_last = employeeList.pTail;
                employee employee_case_2;
                addNewEmployeeList(employeeList, employee_case_2);

                char choose_case_2;
                int check_choose_case_2;
                do
                {
                    printStatusMenu();
                    printf("Please enter your choice: "); scanf("%c", &choose_case_2);
                    check_choose_case_2 = (int)choose_case_2;
                    if(check_choose_case_2 != 121 && check_choose_case_2 != 89 && check_choose_case_2 != 110 && check_choose_case_2 != 78)
                        printf("\nError: Invalid selection !");
                } while (check_choose_case_2 != 121 && check_choose_case_2 != 89 && check_choose_case_2 != 110 && check_choose_case_2 != 78);

                if(check_choose_case_2 == 121 || check_choose_case_2 == 89)
                    saveEmployeeList(employeeList);
                else if(check_choose_case_2 == 110 || check_choose_case_2 == 78)
                {
                    while(pTmp_index_last != NULL)
                    {
                        deleteNodeData(employeeList, pTmp_index_last->data);
                        pTmp_index_last = pTmp_index_last->pNext;
                    }
                }
                break;
            }

        case 3:
            displayEmployeeList(employeeList);
            break;

        case 4:
            editProductByName(productList, num_of_product);
            break;

        case 5:
            deleteProductByID(productList, num_of_product);
            break;

        case 6:
            //findMostContributingID(productList, num_of_product);
            break;

        case 7:
            sortProductsByPrice(productList, num_of_product);
            break;

        case 8:
            saveProductList(productList, num_of_product);
            break;

        case 9:
                readProductListFromFile(productList, num_of_product);
                displayProductList(productList, num_of_product, employeeList);
            break;

        case 10:
            //addProductToFile("product_list.txt", productList, num_of_product);
            break;

        case 0:
            free(productList);
            return 0;

        default:
            free(productList);
            return 0;
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------------

void initEmployeeInformation(employee *employee)
{
    printf("\nEnter ID of the Employee: "); 
    scanf("%d", &employee->employee_id); getchar();

    printf("\nEnter the name of the Employee: ");
    fgets(employee->employee_name, sizeof(employee->employee_name) + 1, stdin); pop_str_last(employee->employee_name);

    do
    {
        printf("\nEnter the age of the Employee: ");
        scanf("%d", &employee->employee_age); getchar();
        if(checkEmployeeAge(*employee))
            printf("\nError: Age is not within working age !");
    } while (checkEmployeeAge(*employee));

    printf("\nEnter the gender of the Employee: ");
    fgets(employee->employee_gender, sizeof(employee->employee_gender) + 1, stdin); pop_str_last(employee->employee_gender);

    printf("\nEnter the address of the Employee: ");
    fgets(employee->employee_address, sizeof(employee->employee_address) + 1, stdin); pop_str_last(employee->employee_address);

    do
    {
        printf("\nRequirement: Only enter 9 numbers after the first 0 !");
        printf("\nEnter the phone number of the Employee: ");
        scanf("%10s", &employee->employee_phoneNumber);
        if(!checkEmployeePhoneNumber(*employee))
            printf("\nError: Wrong phone number format !"); 
    } while (!checkEmployeePhoneNumber(*employee));

    printf("\nNumber of products made: 0\n");
    employee->num_products_made = 0;
    getchar();

    printf("\nStatus: Created employee information successfully !");
}

node *creatNewNode(employee employee)
{
	node *pNode;
    do
    {
        pNode = (node*)malloc(sizeof(node));
        if(pNode == NULL)
            printf("\nError: Allocating memory !");
    }while(pNode == NULL);
    
    initEmployeeInformation(&employee);
    pNode->data = employee;
    pNode->pNext = NULL;
    return pNode;
}

void linkInitialization(singeList &employeeList)
{
    employeeList.pHead = employeeList.pTail = NULL;
}

bool isEmpty(singeList &employeeList)
{
    return employeeList.pHead == NULL;
}

void addNewEmployee(singeList &employeeList, employee newEmployee)
{
	node *new_node;
    do
    {
        new_node = creatNewNode(newEmployee);
        if (new_node->data.employee_id != 0 && isDuplicateID(employeeList, new_node->data.employee_id))
            printf("\nError: Duplicate employee ID!");
    } while (new_node->data.employee_id != 0 && isDuplicateID(employeeList, new_node->data.employee_id));

    if(isEmpty(employeeList))
        employeeList.pHead = employeeList.pTail = new_node;
    else
    {
        employeeList.pTail->pNext = new_node;
        employeeList.pTail = new_node;
    }
    printf("\nStatus: Successfully added new employee !");
}

void addNewEmployeeList(singeList &employeeList, employee employee)
{
    int quantity; 
    do
    {
        printf("\nEnter the number of employees: "); scanf("%d", &quantity); getchar();
        if(quantity <= 0)
            printf("\nError: Number of employees cannot be negative !");
    } while (quantity <= 0);
    
    while(quantity--)
        addNewEmployee(employeeList, employee);
    printf("\nStatus: Added employee list successfully !");
}

void addNewEmployeeListToFile(singeList &employeeList, employee employee)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = employee;
    newNode->pNext = NULL;

    if (employeeList.pHead == NULL)
        employeeList.pHead = newNode;
    else
    {
        node *currentNode = employeeList.pHead;
        while (currentNode->pNext != NULL)
            currentNode = currentNode->pNext;
        currentNode->pNext = newNode;
    }
}

void displayEmployeeList(singeList &employeeList)
{
    node *pTmp = employeeList.pHead;
    if(pTmp == NULL)
    {
        printf("\nThe Employee list is empty !");
        return;
    }
    while(pTmp != NULL)
    {
        printf("%d, %s, %d, %s, %s, %s, %d\n",
            pTmp->data.employee_id, 
            pTmp->data.employee_name, 
            pTmp->data.employee_age, 
            pTmp->data.employee_gender, 
            pTmp->data.employee_address, 
            pTmp->data.employee_phoneNumber,
            pTmp->data.num_products_made);
        pTmp = pTmp->pNext;
    }
}

bool checkEmployeePhoneNumber(const employee employee)
{
    if (strlen(employee.employee_phoneNumber) != 10) {
        return false;
    }

    if (employee.employee_phoneNumber[0] != '0') {
        return false;
    }

    for (int i = 1; i < 10; i++)
        if (employee.employee_phoneNumber[i] < '0' || employee.employee_phoneNumber[i] > '9')
            return false;

    return true;
}

bool checkEmployeeAge(employee &employee)
{
    if(employee.employee_age > 65 || employee.employee_age < 18)
        return true;
    return false;
}

bool isDuplicateID(const singeList &employeeList, int id)
{
    const node *current_node = employeeList.pHead;
    while(current_node != NULL)
    {
        if(current_node->data.employee_id == id)
            return true;
        current_node = current_node->pNext;
    }
    return false;
}

void deleteNodeData(singeList &employeeList, employee employee) 
{
    node *current = employeeList.pHead;
    node *previous = NULL;

    while (current != NULL) 
    {
        if (current->data.employee_id == employee.employee_id)  
            break;
        previous = current;
        current = current->pNext;
    }

    if (current == NULL) 
    {
        printf("\nStatus: No employee data to be deleted found !");
        return;
    }

    if (previous == NULL) 
        employeeList.pHead = current->pNext;
    else 
        previous->pNext = current->pNext;

    free(current);
}

void readEmployeeListFromFile(singeList &employeeList)
{
    FILE *inputFile;
    do
    {
        inputFile = fopen("employee_list.txt", "r");
        if (inputFile == NULL) 
            printf("\nError: Could not open file !");
    } while (inputFile == NULL);

    employee employee_replacement;
    while (fscanf(inputFile, "%d, %[^,], %d, %[^,], %[^,], %[^,], %d\n",
                &employee_replacement.employee_id,
                employee_replacement.employee_name,
                &employee_replacement.employee_age,
                employee_replacement.employee_gender,
                employee_replacement.employee_address,
                employee_replacement.employee_phoneNumber,
                &employee_replacement.num_products_made) == 7)
                {
                    printf("\nStatus: Loading employee data !\n\n");
                    addNewEmployeeListToFile(employeeList, employee_replacement);
                    displayEmployeeList(employeeList);
                    printf("\nStatus: Upload data successfully !\n");
                }

    fclose(inputFile);
}

void saveEmployeeList(const singeList &employeeList)
{
    FILE *output_file;
    do
    {
        output_file = fopen("employee_list.txt", "w");
        if (output_file == NULL) 
            printf("\nError: Could not open file !");
    } while (output_file == NULL);

    if(output_file != NULL)
    {
        const node *current_node = employeeList.pHead;
        while (current_node != NULL)
        {
            fprintf(output_file, "%d, %s, %d, %s, %s, %s, %d\n",
                current_node->data.employee_id,
                current_node->data.employee_name,
                current_node->data.employee_age,
                current_node->data.employee_gender,
                current_node->data.employee_address,
                current_node->data.employee_phoneNumber,
                current_node->data.num_products_made);
            printf("\n\nStatus: Saved employee successfully !\n");

            current_node = current_node->pNext;
        }

        printf("\nStatus: Product list saved successfully !");
        fclose(output_file);
    }
    else
    {
        fprintf(stderr, "\nError: Failed to open the output file !");
    }
}

// ------------------------------------------------------------------------------------------------------------------------

void addNewProduct(product *&productList, int &num_of_product, singeList &employeeList)
{
    num_of_product++;
    product *arr_resizable = (product*)malloc(num_of_product * sizeof(product));

    for(int i = 0; i < num_of_product - 1; i++)
        *(arr_resizable + i) = productList[i];

    free(productList);
    productList = arr_resizable;

    product new_product;

    printf("\nEnter ID of the Product: "); 
    scanf("%d", &new_product.product_id); getchar();

    printf("\nEnter the name of the Product: "); 
    fgets(new_product.product_name, sizeof(new_product.product_name) + 1, stdin); pop_str_last(new_product.product_name);

    do
    {
        printf("\nEnter the product's price: ");
        scanf("%lf", &new_product.product_price); getchar();
        if(!checkPrice(new_product))
            printf("\nError: The product's price is a non-negative number !");
    } while (!checkPrice(new_product));

    do
    {
        printf("\nEnter the Product's manuafacturing date: ");
        scanf("%d%d%d", &new_product.product_time.day, &new_product.product_time.month, &new_product.product_time.year);
        if(!checkTime(new_product))
            printf("\nError: Incorrect time format !");
    } while (!checkTime(new_product));

    int employee_in_charge;
    printf("\nEnter the ID of the employee in charge: ");
    scanf("%d", &employee_in_charge); getchar();

    bool mark = false;
    node *current = employeeList.pHead;
    while (current != NULL)
    {
        if(current->data.employee_id == employee_in_charge)
        {
            current->data.num_products_made++;
            new_product.employee = &(current->data);
            mark = true;
            break;
        }
        current = current->pNext;
    }
    if(mark)
        printf("\nStatus: The employee's ID has been successfully added !");
    else
        printf("\nError: Employee ID not found !");

    arr_resizable[num_of_product - 1] = new_product;
}

void addNewProductList(product *&productList, int &num_of_product, singeList &employeeList)
{
    int quantity; scanf("%d", &quantity);
    int newSize = num_of_product + quantity;
    for(int i = num_of_product; i < newSize; i++)
        addNewProduct(productList, num_of_product, employeeList);
}

void displayProductList(const product *productList, int num_of_product, singeList &employeeList)
{
    if(num_of_product == 0)
        printf("Error: Product list information does not exist !\n");
    else
    {
        for(int i = 0; i < num_of_product; i++)
        {
            node *current = employeeList.pHead;
            int employee_in_charge;
            while (current != NULL)
            {
                if(&(current->data) == (*(productList + i)).employee)
                {
                    employee_in_charge = current->data.employee_id;
                    break;
                }
                current = current->pNext;
            }

            printf("%d, %s, %.2lf, %d/%d/%d, %d\n",
                (*(productList + i)).product_id, 
                (*(productList + i)).product_name, 
                (*(productList + i)).product_price, 
                (*(productList + i)).product_time.day, (*(productList + i)).product_time.month, (*(productList + i)).product_time.year),
                employee_in_charge;
        }
    }
}

void editProductByName(product *productList, int num_of_product)
{
    bool marker = false;
    int index_alternative_product;
    char alternative_product_name[MAX_PRODUCT];

    printf("\nEnter the name of the alternative Product: "); getchar();
    fgets(alternative_product_name, sizeof(alternative_product_name) + 1, stdin);

    for(int index_product = 0; index_product < num_of_product; index_product++)
    {
        int result = strcmp(alternative_product_name, (productList[index_product].product_name));
        if(result != 0)
        {
            printf("\nError: The requested product name was not found !");
            break;
        }
        else
        {
            marker = true;
            index_alternative_product = index_product;
        }
    }

    if(marker)
    {
        product alternative_product;

        printf("\nEnter ID of the Product: "); 
        scanf("%d", &alternative_product.product_id); getchar();

        printf("\nEnter the name of the Product: "); 
        fgets(alternative_product.product_name, sizeof(alternative_product.product_name) + 1, stdin);

        do
        {
            printf("\nEnter the Product's manuafacturing date: ");
            scanf("%d%d%d", &alternative_product.product_time.day, &alternative_product.product_time.month, &alternative_product.product_time.year);
            if(!checkTime(alternative_product))
                printf("\nError: Incorrect time format !");
        } while (!checkTime(alternative_product));

        do
        {
            printf("\nEnter the product's price: ");
            scanf("%lf", &alternative_product.product_price); getchar();
            if(!checkPrice(alternative_product))
                printf("\nError: The product's price is a non-negative number !");
        }   while (!checkPrice(alternative_product)); 

        *(productList + index_alternative_product) = alternative_product;
    }
}

void deleteProductByID(product *&productList, int &num_of_product)
{
    int ID_location_of_product_deleted;
    printf("\nEnter the ID of the product to delete: ");
    scanf("%d", &ID_location_of_product_deleted); getchar();

    if(ID_location_of_product_deleted != productList->product_id)
    {
        printf("\nError: Cannot find product ID to delete !");
    }
    else
    {
        for(int index_product = ID_location_of_product_deleted - 1; index_product < num_of_product; index_product++)
        *(productList + index_product) = *(productList + (index_product + 1));

        num_of_product--;
    }
}

/*void findMostContributingID(product *productList, int num_of_product)
{
    int num_of_emoloyee_id = num_of_product;
    int arr_employee_id[num_of_emoloyee_id];

    for(int index_product = 0; index_product < num_of_product; index_product++)
        arr_employee_id[index_product] = productList[index_product].producter.employee_id;

    //countFrequency(arr_emloyee_id, num_of_emoloyee_id);
    int arr_frequency[MAX_PRODUCT];
    int unique_elements[MAX_PRODUCT] = {0};
    int unique_count = 0;

    for (int i = 0; i < num_of_emoloyee_id; i++) 
    {
        bool is_new_element = true;

        for (int j = 0; j < unique_count; j++) 
        {
            if (arr_employee_id[i] == unique_elements[j]) 
            {
                is_new_element = false;
                break;
            }
        }

        if (is_new_element) 
        {
            unique_elements[unique_count] = arr_employee_id[i];
            unique_count++;
        }
    }

    for (int i = 0; i < unique_count; i++) 
    {
        int count_frequency = 0;

        for (int j = 0; j < num_of_emoloyee_id; j++) 
            if (arr_employee_id[j] == unique_elements[i]) 
                count_frequency++;
                
        arr_frequency[i] = count_frequency;   
    }

    int largest_frequency = arr_frequency[0];
    int contribute_value = 0;
    for(int i = 1; i < unique_count; i++)
    {
        if(largest_frequency < arr_frequency[i])
        {
            largest_frequency = arr_frequency[i];
            contribute_value = i;
        }
    }

    printf("ID of the employee who contributed the most based on the number of products produced: %d", unique_elements[contribute_value]);
    printf("The contribution amount of ID %d = %d", unique_elements[contribute_value], largest_frequency);
}*/

void sortProductsByPrice(product *productList, int num_of_product)
{
    for(int i = 0; i < num_of_product - 1; i++)
    {
        for(int j = i + 1; j < num_of_product; j++)
        {
            if((productList + i)->product_price > (productList + j)->product_price)
            {
                product temp_product = *(productList + i);
                *(productList + i) = *(productList + j);
                *(productList + j) = temp_product;
            }
        }
    }
}

/*void addProductToFile(const char *filename, product *&productList, int &num_of_product)
{
    FILE *inputFile = fopen(filename, "a");
    if (inputFile == NULL) 
    {
        printf("\nError: Could not open file !");
        return;
    }

    addNewProduct(productList, num_of_product);

    fprintf(inputFile, "%d, %s, %d, %d, %d, %d\n", 
        productList->product_id, 
        productList->product_name,
        productList->product_price, 
        productList->product_time.day, 
        productList->product_time.month, 
        productList->product_time.year);

    fclose(inputFile);
}*/

void readProductListFromFile(product *&productList, int &num_of_product)
{
    int num_products_system = 0;
    product system_product_list[MAX_PRODUCT];
    FILE *inputFile = fopen("product_list.txt", "r");

    if (inputFile == NULL) 
    {
        printf("\nError: Could not open file !");
        exit(1);
    } 

    while (num_products_system < MAX_PRODUCT &&
           fscanf(inputFile, "%d, %[^,], %lf, %d/%d/%d\n", 
                  &system_product_list[num_products_system].product_id, 
                  system_product_list[num_products_system].product_name,
                  &system_product_list[num_products_system].product_price, 
                  &system_product_list[num_products_system].product_time.day, 
                  &system_product_list[num_products_system].product_time.month, 
                  &system_product_list[num_products_system].product_time.year) == 6) 
    {
        num_products_system++;
    }

    num_of_product = num_products_system;
    productList = (product*)malloc(num_products_system * sizeof(product));
    if (productList == NULL) 
    {
        printf("\nError: Memory allocation failed!");
        exit(1);
    }

    for(int i = 0; i < num_products_system; i++)
    {
        productList[i] = system_product_list[i];
    }

    fclose(inputFile);
}

void saveProductList(const product *productList, int num_of_product)
{
    FILE *output_file = fopen("product_list.txt", "w");

    if(output_file != NULL)
    {
        for(int i = 0; i < num_of_product; i++)
        {
            fprintf(output_file, "%d, %s, %.3lf, %d/%d/%d\n",
            (productList + i)->product_id, 
            (productList + i)->product_name, 
            (productList + i)->product_price, 
            (productList + i)->product_time.day, (productList + i)->product_time.month, (productList + i)->product_time.year);
        }
        printf("\nStatus: Product list saved successfully !");
        fclose(output_file);
    }
    else
        fprintf(stderr, "\nError: Failed to open the output file !");
}

bool checkTime(const product &product)
{
    if(product.product_time.day <= 0 || product.product_time.month <= 0 || product.product_time.year <= 0) 
        return false;
    if(product.product_time.month == 4 || product.product_time.month == 6 || product.product_time.month == 9 || product.product_time.month == 11)
        if(product.product_time.day >= 30) 
            return false;
    else if(product.product_time.month == 2)
    {
        if(product.product_time.year % 4 != 0 && product.product_time.day > 28) 
            return false;
        else if(product.product_time.year % 4 == 0 && product.product_time.day > 29) 
            return false;
    }
    else if(product.product_time.month > 12 || product.product_time.day > 31) 
        return false;
    else if(product.product_time.year < 1000 || product.product_time.year > 9999)
        return false;
    return true;
}

int checkPrice(const product &product)
{
    return product.product_price >= 0;
}

// ------------------------------------------------------------------------------------------------------------------------

void printMenu()
{
    printf("\n======================================================================\n");
    printf("===================*** FACTORY MANAGEMENT PROGRAM ***===================\n");
    printf("======================================================================\n\n");

    printf("+----------+---------------------------------------------------------+\n");
    printf(":   S No.  : FUNCTION                                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   1st    : Create a new employee                                   :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   2nd    : Create a new employee list                              :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   3rd    : Displays a list of employees                            :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   4th    : Update product information by product name              :\n"); 
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   5th    : Delete the product by ID                                :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   6th    : Find the ID of the employee with the most contributions :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   7th    : Sort products by price                                  :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   8th    : Save product list to the system                         :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   9th    : Displays the list of available products on the system   :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":   10st   : Create new products on the system (Quick feature)       :\n");
    printf("+----------+---------------------------------------------------------+\n");
    printf(":    0     : Exit the program                                        :\n");
    printf("+----------+---------------------------------------------------------+\n");

    printf("\n======================================================================");
}

void printStatusMenu()
{
    printf("\n\nWarning: Do you want to save the data you just entered into the system ?\n");
    printf("Warning: If you do not save all entered data, you will be lost !\n");
    printf("+---------------------------------+----------------------------------+\n");
    printf(":          [y] Save               :          [n] Don't save          :\n");
    printf("+---------------------------------+----------------------------------+\n");
}

char *pop_str_last(char *str) {
    const int len = strlen(str);
    if (len == 0)
        return '\0';
    else 
    {
        str[len - 1] = '\0';
        return str;
    }
}
