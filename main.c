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



//init Program
int main(int argc, int *argv[])
{
	
    ulist header = client_hlist();
    ulist l = header->next;
    hlist headerh = history_hlist();

    int loginid;
    int pin,attempts = 0;

    atm cash = read_vaultdb();
    read_custdb(header);
    read_logdb(headerh);

    int nuserid,npin,ntype,conf,nstate, i=0, j=0;
    float namount;
    ulist newdata;
 
    int op;
  
	printf("\t\t -------------------------------------------- \n");    
	printf("\t\t |         C ATM BANK LIMITED               | \n");
	printf("\t\t |           ATM Main Menu                  | \n");
	printf("\t\t |                                          | \n"); 
	printf("\t\t |   WELCOME! PLEASE SELECT YOUR OPTION!    | \n");
	printf("\t\t |                                          | \n");      
	printf("\t\t |    1. Initialize System                  | \n");
	printf("\t\t |                                          | \n");
	printf("\t\t |    2. Display ATM Transactions Log       | \n");
	printf("\t\t |                                          | \n");    
	printf("\t\t |    3. User Transactions Menu             | \n");  
	printf("\t\t |                                          | \n");
	printf("\t\t |    4. Exit                               | \n");
	printf("\t\t --------------------------------------------\n\n");
  
    INPUT
    scanf("%d",&op);
  
    switch (op)
    {
    case 1:
	system("cls");
	printf("\t\t --------------------------------------------\n");
	printf("\t\t |    1. Initialize System                  | \n");  
	printf("\t\t |                                          | \n");
	printf("\t\t |                                          | \n");
	printf("\t\t --------------------------------------------\n\n");
 
  
    
    break;
    case 2:

	system("cls");  
	printf("\t\t --------------------------------------------\n");
	printf("\t\t |    2. Display ATM Transactions Log       | \n");  
	printf("\t\t |                                          | \n");
	printf("\t\t |                                          | \n");
	printf("\t\t --------------------------------------------\n\n");
   

        break;

    case 3:
        write_custdb(header);
        write_vaultdb(cash);
        write_logdb(headerh);
        system("exit");
        break;
    default:
        printf("Choose only the options listed\n");
    }
  
}





//FILING
 
//--------------------------------------------------------------------------------------------------//
//Writes Funds added to ATM Total Funds to file
void write_vaultdb(atm cash)
{
    FILE *f_cash = fopen("vault.txt", "w");
    fprintf(f_cash,"%6.2f",cash.money );
    fclose(f_cash);
}
//--------------------------------------------------------------------------------------------------//
//Reads ATM Total Funds available from file
atm read_vaultdb()
{
    float money;
    float balance;
 
    FILE *f_cash = fopen("vault.txt", "r");
    if (f_cash == NULL)
    {
        FILE *f_cash = fopen("vault.txt", "w");
        fscanf(f_cash,"%f",&balance);
        return banknotes(balance);
    }
    else
        fscanf(f_cash,"%f", &money);
    return banknotes(money);
}
//--------------------------------------------------------------------------------------------------//
//Reads Customers information from file ie. account no, pin, total funds, account type, and status
void read_custdb(ulist header)
{
    int i,pin,type,state,userid;
    float sum;
	
    FILE *f_clientes= fopen("customers.txt", "r"); 
    int res = fscanf(f_clientes, "%d\t\t%d\t\t%f\t\t%d\t\t%d\n", &userid,&pin,&sum,&type,&state);
    for (i = 0; res > 0; i++)
    {
        create_user(header,userid,pin,sum,type,state);
        res = fscanf(f_clientes, "%d\t\t%d\t\t%f\t\t%d\t\t%d\n", &userid,&pin,&sum,&type,&state);
    }
    fclose (f_clientes);
}
//--------------------------------------------------------------------------------------------------//
//Writes customers banking details to file ie. account no, pin, total funds, account type, and status
void write_custdb(ulist header)
{
    ulist l=header->next;
    FILE *f_clientes = fopen("customers.txt", "w");
 
    while (l)
    {
        fprintf (f_clientes, "%d\t\t%d\t\t%6.2f\t\t%d\t\t%d\n", l->userid,l->pin,l->sum,l->type,l->state); 
        l=l->next;
    }
    fclose(f_clientes);
}
//--------------------------------------------------------------------------------------------------//
//Checks and Reads Activity logs to and from File
void read_logdb(hlist headerh)
{
    int nop,nuid,i;
	float ndest;
    hlist l = headerh->next;

    FILE *f_hist = fopen("logs.txt", "r");
    if (f_hist == NULL)
    {
        FILE *f_hist = fopen("logs.txt", "w");
    }
    else
    {
        int res = fscanf(f_hist, "%d %d %f\n", &nop,&nuid,&ndest);
        for (i = 0; res > 0; i++)
        {
            create_log(headerh,nop,nuid,ndest);
            res = fscanf(f_hist, "%d %d %f\n", &nop,&nuid,&ndest);
        }
        fclose (f_hist);
    }
}
//--------------------------------------------------------------------------------------------------//
//Writes Activity logs to File
void write_logdb(hlist headerh)
{
    hlist l=headerh->next;
    FILE *f_hist= fopen("logs.txt", "w");
 
    while (l)
    {
        fprintf (f_hist,"%d %d %6.2f\n",l->operation,l->opuserid,l->opactivity); 
        l=l->next;
    }
    fclose(f_hist);
}