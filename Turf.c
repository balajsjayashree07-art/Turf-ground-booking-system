#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Turf
{
    int id, price;
    char name[30], sport[20];
};

struct Turf t[5] =
{
    {101,800,"Green Arena","Football"},
    {102,1000,"Victory Turf","Cricket"},
    {103,900,"Champion Turf","Football"},
    {104,1200,"Sports Zone","Box Cricket"},
    {105,1500,"Elite Turf","Multi Sports"}
};

struct Booking
{
    int id, turfId, hours, amount;
    char name[30], mobile[15], date[20], slot[20];
} *b = NULL;

FILE *fp;

void login()
{
    char u[20], p[20];
    do
    {
        printf("\nUsername: ");
        scanf("%19s", u);
        printf("Password: ");
        scanf("%19s", p);
    } while(strcmp(u, "admin") != 0 || strcmp(p, "1234") != 0);
}

void viewTurfs()
{
    int i;
    printf("\n------ Available Turfs ------\n");
    for(i=0; i<5; i++)
    {
        printf("%d | %s | %s | Rs.%d/hr\n",
        t[i].id, t[i].name, t[i].sport, t[i].price);
    }
}

void book()
{
    int i, id;

    if(b != NULL)
        free(b);

    b = (struct Booking*)malloc(sizeof(struct Booking));

    printf("\nBooking ID: ");
    scanf("%d", &b->id);

    printf("Customer Name: ");
    scanf("%29s", b->name);

    printf("Mobile Number: ");
    scanf("%14s", b->mobile);

    printf("Turf ID: ");
    scanf("%d", &id);

    for(i=0; i<5; i++)
    {
        if(t[i].id == id)
        {
            b->turfId = id;

            printf("Date: ");
            scanf("%19s", b->date);

            printf("Slot: ");
            scanf("%19s", b->slot);

            printf("Hours: ");
            scanf("%d", &b->hours);

            b->amount = t[i].price * b->hours;

            fp = fopen("booking.dat", "wb");

            if(fp != NULL)
            {
                fwrite(b, sizeof(struct Booking), 1, fp);
                fclose(fp);
            }

            printf("\nBooking Successful!\n");
            printf("Total Amount = Rs.%d\n", b->amount);
            return;
        }
    }

    printf("\nInvalid Turf ID!\n");
    free(b);
    b = NULL;
}

void load()
{
    fp = fopen("booking.dat", "rb");

    if(fp == NULL)
        return;

    b = (struct Booking*)malloc(sizeof(struct Booking));

    if(fread(b, sizeof(struct Booking), 1, fp) != 1)
    {
        free(b);
        b = NULL;
    }

    fclose(fp);
}

void view()
{
    if(b == NULL)
    {
        printf("\nNo Booking Found!\n");
        return;
    }

    printf("\n------ Booking Details ------\n");
    printf("Booking ID : %d\n", b->id);
    printf("Customer   : %s\n", b->name);
    printf("Mobile     : %s\n", b->mobile);
    printf("Turf ID    : %d\n", b->turfId);
    printf("Date       : %s\n", b->date);
    printf("Slot       : %s\n", b->slot);
    printf("Hours      : %d\n", b->hours);
    printf("Amount     : Rs.%d\n", b->amount);
}

void bill()
{
    if(b == NULL)
        printf("\nNo Booking Available!\n");
    else
        printf("\nTotal Bill = Rs.%d\n", b->amount);
}

void admin()
{
    printf("\n------ Admin Panel ------\n");
    viewTurfs();
}

int main()
{
    int ch;

    load();
    login();

    do
    {
        printf("\n\n===== TURF BOOKING SYSTEM =====");
        printf("\n1. View Turfs");
        printf("\n2. Book Turf");
        printf("\n3. View Booking");
        printf("\n4. Bill");
        printf("\n5. Admin");
        printf("\n6. Exit");
        printf("\nEnter Choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                viewTurfs();
                break;

            case 2:
                book();
                break;

            case 3:
                view();
                break;

            case 4:
                bill();
                break;

            case 5:
                admin();
                break;

            case 6:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(ch != 6);

    if(b != NULL)
        free(b);

    return 0;
}
