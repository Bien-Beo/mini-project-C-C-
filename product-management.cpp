#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product_time
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

struct employee
{
    unsigned int employee_id;
    char employee_name[50];
    unsigned short employee_age;
    char employee_gender[10];
    char employee_address[100];
    unsigned short employee_phoneNumber[10] = {0};
    unsigned int employee_contribute = 0;
};

struct product
{
    unsigned int product_id;
    char product_name[100];
    unsigned int product_price;
    struct product_time product_time;
    struct employee producter;
};

void addNewEmployee();

void addNewProduct(product *&productList, int &num_of_product);
void addNewProductList();
void displayProductList();
void editProductByName();
void deleteProductByID();
void searchProductByProducter();
void sortProductsByPrice();
void saveProductList();

int main()
{
    unsigned int num_of_product = 1;
    product *productList = (product*)malloc(num_of_product * sizeof(product));
    unsigned int ordinal;
}

void addNewEmployee(employee *employee)
{
    printf("\nEnter ID of the Employee: "); 
    scanf("%d", &employee->employee_id); getchar();

    printf("\nEnter the name of the Employee: ");
    fgets(employee->employee_name, sizeof(employee->employee_name) + 1, stdin);

    printf("\nEnter the age of the Employee: ");
    scanf("%d", &employee->employee_age);

    printf("\nEnter the gender of the Employee: ");
    fgets(employee->employee_gender, sizeof(employee->employee_gender) + 1, stdin);

    printf("\nEnter the address of the Employee: ");
    fgets(employee->employee_address, sizeof(employee->employee_address) + 1, stdin);

    printf("\nEnter the phone number of the Employee: ");
    for(int i = 1; i < 10; i++)
        scanf("%d", &employee->employee_phoneNumber[i]); getchar();
}

void addNewProduct(product *&productList, int &num_of_product)
{
    product new_product;

    printf("\nEnter ID of the Product: "); 
    scanf("%d", &new_product.product_id); getchar();

    printf("\nEnter the name of the Product: "); 
    fgets(new_product.product_name, sizeof(new_product.product_name) + 1, stdin);

    printf("\nEnter the Product's manuafacturing date: ");
    scanf("%d%d%d", &new_product.product_time.day, &new_product.product_time.month, &new_product.product_time.year); 

    printf("\nEnter the Producter: ");
    employee new_employee; addNewEmployee(&new_employee); new_product.producter = new_employee;

    num_of_product++;
    product *arr_resizable = (product*)malloc(num_of_product * sizeof(product));

    for(int i = 0; i < num_of_product - 1; i++)
        arr_resizable[i] = productList[i];

    arr_resizable[num_of_product - 1] = new_product;
    free(productList);

    productList = arr_resizable;
}