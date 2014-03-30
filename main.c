#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#define LINE printf("\n");
#define INPUT printf("-->\t");

// Grouping the structure for the atm vault balance
typedef struct bank *vault;
typedef struct bank
{
    float money;
}atm;

// Grouping the structure for users 
typedef struct user *ulist;
typedef struct user
{
    int userid,pin;
	int type,state;  // for type = 0 customer, 1 admin. for state = 0 active, 1 locked
    float sum;
   ulist *next;
}users;

// Grouping the structure for logs
typedef struct log *hlist;
typedef struct log
{
    int operation,opuserid;
	float opactivity;
    hlist *next;
}logs;
