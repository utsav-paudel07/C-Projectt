#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define MAX_NAME_LENGTH 50

// Define struct for items
struct Item {
    char name[MAX_NAME_LENGTH];
    int quantity;
    float price;
};

// Function to authenticate user
bool authenticate(const char *username, const char *password) {
    // Hardcoded valid username and password
    const char *validUsername = "user";
    const char *validPassword = "password";

    // Compare provided username and password with valid ones
    return strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    struct Item items[MAX_ITEMS];
    int numItems;
    float total = 0;
    time_t t;
    struct tm *timeinfo;

    // Get current time
    time(&t);
    timeinfo = localtime(&t);

    // Input username and password
    printf("Username: ");
    scanf("%19s", username);
    printf("Password: ");
    scanf("%19s", password);

    // Authenticate user
    if (!authenticate(username, password)) {
        printf("Authentication failed. Exiting...\n");
        return 1; // Exit with error code
    }

    // Set text color to green
    printf("\033[0;32m");

    // Input number of items
    printf("Enter the number of items: ");
    scanf("%d", &numItems);

    // Input items
    for (int i = 0; i < numItems; i++) {
        printf("\nEnter details for item %d:\n", i + 1);
        printf("Name: ");
        scanf("%49s", items[i].name);
        printf("Quantity: ");
        scanf("%d", &items[i].quantity);
        
        // Prompt user until a valid price is entered
        do {
            printf("Price per item (less than or equal to 100000): ");
            scanf("%f", &items[i].price);
            if (items[i].price > 100000)
                printf("Price exceeds limit. Please enter a valid price.\n");
        } while (items[i].price > 100000);
    }

    // Display bill receipt
    printf("\n\n************ Bill Receipt ************\n");
    printf("Item Name\tQuantity\tPrice\tTotal\n");
    for (int i = 0; i < numItems; i++) {
        float itemTotal = items[i].quantity * items[i].price;
        total += itemTotal;
        printf("%s\t\t%d\t\t%.2f\t%.2f\n", items[i].name, items[i].quantity, items[i].price, itemTotal);
    }
    printf("\nTotal Amount: %.2f\n", total);

    // Display date and time
    char time_str[50];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Date & Time: %s\n", time_str);
    
    // Reset text color
    printf("\033[0m");

    return 0;
}

