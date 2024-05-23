#include <stdio.h>
#include <string.h>

typedef struct{
    int quantity;
    float price;
} Item;

float Total_Payment(Item paratha, Item vegetable, Item mineral_water) {
    float total_paid = (paratha.quantity * paratha.price) +
                       (vegetable.quantity * vegetable.price) +
                       (mineral_water.quantity * mineral_water.price);
                       
    return total_paid;
}

float Individual_Payment(float total_paid, int person) {
    return total_paid / person;
}

int main() {
    Item paratha, vegetable, mineral_water;
    
    int person;

    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.price);

    printf("Quantity Of Vegetables: ");
    scanf("%d", &vegetable.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetable.price);

    printf("Quantity Of Mineral Water: ");
    scanf("%d", &mineral_water.quantity);
    printf("Unit Price: ");
    scanf("%f", &mineral_water.price);

    printf("Number of People: ");
    scanf("%d", &person);

    float total_paid = Total_Payment(paratha, vegetable, mineral_water);

    float paid = Individual_Payment(total_paid, person);

    printf("\nIndividual people will pay: %.2f tk\n", paid);

    return 0;
}
