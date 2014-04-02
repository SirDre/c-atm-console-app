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


//ulist Records functions 
ulist client_hlist (void);
hlist history_hlist(void);

//ATM Structures functions 
atm banknotes(float balance);
atm read_vaultdb();

//Users login functions 
int login(ulist header,hlist headerh, int acctno, int acctpin,atm cash);
void userlogin ();

int search_client(ulist header,int key); //returns 1 if it finds, 0 otherwise
void create_log(hlist headerh,int noperation, int nopuserid,float noactions);

//Display functions
void option1(ulist header,hlist headerh,int login,int pin,atm cash);
void option2(ulist header,hlist headerh,int login,int pin,atm cash);
void menu(ulist header,hlist headerh,int login,int pin,atm cash);
void menu2(ulist header,hlist headerh,int login, int pin,atm cash);

//Admin functions 
void create_client(ulist header,hlist headerh,int login,int pin,atm cash);
void create_user(ulist header, int nuserid, int npin, float namount, int ntype, int nstate);
void print_log(ulist header,hlist headerh,int login,int pin,atm cash);
void delete_client(ulist header,hlist headerh,int login, int pin,atm cash);
void print_clients(ulist header,hlist headerh,int login,int pin,atm cash);
int unlock_client(ulist header,hlist headerh,int login, int pin,atm cash);  

//Customer functions 
void query_acct(ulist header,hlist headerh,int login, int pin,atm cash);
void cust_deposit(ulist header, hlist headerh,int login, int pin, atm cash);
void cust_transfer(ulist header,hlist headerh,int login, int pin,atm cash);
void cust_withdraw(ulist header,hlist headerh, int login, int pin, atm cash);
void print_custlog(ulist header,hlist headerh,int login,int pin,atm cash);
int change_client_pin(ulist header,hlist headerh,int login,int pin,atm cash); 

//Read&Write functions
void write_custdb(ulist header);
void read_custdb(ulist header);
void read_logdb(hlist headerh);
void write_logdb(hlist headerh);
void write_vaultdb(atm cash);


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
        
start:    
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
 
     for (i=0; i <= 20;i++) {
 
        nuserid = 1000+i;
        npin = 0000;
        namount = 1000.00;
        ntype = 0;
        nstate = 0;
        
         newdata = (ulist) malloc (sizeof (users));
	    if (newdata != NULL)
	    {
	    	
	       if (search_client(header,nuserid) == 1)
	        {
	            system("cls");
	            printf("\tERROR: Customers accounts already exist\n");
	            printf("\t-------------------------------------------------\n");
	            goto start;
	        }else{
		    //create new admin users  
		    create_user(header,nuserid,npin,namount,ntype,nstate);
		    //add new value to atm balance
		    cash.money+=namount;
			
	         }   
	        
	    }else{
	    	
	        system("cls");
	     	userlogin (); 
	    }
	    
	        create_log(headerh,1,nuserid,namount); 
     }  
     
    for (j=0; j <= 2;j++) {
 
        nuserid = 2000+j;
        npin = 0000;
        namount = 1000.00;
        ntype = 1;
        nstate = 0;
 
	     newdata = (ulist) malloc (sizeof (users));
	    if (newdata != NULL)
	    {
		if (search_client(header,nuserid) == 1)
	        {
	            system("cls");
	            printf("\tERROR: Customers accounts already exist\n");
	            printf("\t-------------------------------------------------\n");
	            goto start;
	        }else{
	       
		    //create new admin users  
		    create_user(header,nuserid,npin,namount,ntype,nstate);
		    //add new value to atm balance
		    cash.money+=namount;
	        }
			  
			   
	    }else{
	    	
	        system("cls");
	     	userlogin (); 	
	    }
	    
	        create_log(headerh,1,nuserid,namount); 
     }  


    write_custdb(header);
    write_vaultdb(cash);
    write_logdb(headerh);  
   
    system("cls"); 
    printf("%s\n" ,__TIME__);
    printf("Initialized System Successfully!\n");
	goto start;
    
    break;
    case 2:

	system("cls");  
	printf("\t\t --------------------------------------------\n");
	printf("\t\t |    2. Display ATM Transactions Log       | \n");  
	printf("\t\t |                                          | \n");
	printf("\t\t |                                          | \n");
	printf("\t\t --------------------------------------------\n\n");
   
	printf("\t\t	Please login	\n");
	
	printf("Enter Admin Account Number:\n");
	INPUT
	scanf("%6d",&loginid); 
	printf("Enter pin:\n");
	INPUT
	scanf("%4d",&pin);
	//if account number is true and login returns 1 show admin menu
	if (login(header,headerh,loginid,pin,cash) == 1)
	{
	printf("Logged in user: %d\n\n",loginid);
	      print_log(header,headerh,loginid,pin,cash);	
	}else {
	    
		system("cls");
		userlogin ();   	
	}

        break;
    case 3:
        system("cls");
        userlogin ();    
        break;
    case 4:
        write_custdb(header);
        write_vaultdb(cash);
        write_logdb(headerh);
        system("exit");
        break;
    default:
        printf("Choose only the options listed\n");
    }
  
}

//--------------------------------------------------------------------------------------------------//
//LOGIN
void userlogin ()
{
    ulist header = client_hlist();
    ulist l = header->next;
    hlist headerh = history_hlist();

    int loginid, pin, attempts = 0;

    atm cash = read_vaultdb();
    read_custdb(header);
    read_logdb(headerh);

    printf("\t\t --------------------------------------------\n");
    printf("\t\t |       3. User Transactions Menu          | \n");  
    printf("\t\t |                                          | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t --------------------------------------------\n");
    printf("\n\n");
    printf("\t\t	Please login	\n");

    printf("Enter Account Number:\n");
    INPUT
    scanf("%6d",&loginid); 
    printf("Enter pin:\n");
    INPUT
    scanf("%4d",&pin);
    //if account number is true and login returns 1 show admin menu
    if (login(header,headerh,loginid,pin,cash) == 1)
    {
        printf("Logged in user: %d\n\n",loginid);
        menu(header,headerh,loginid,pin,cash);
    }
     //if account number is true and login returns 1 show customer menu
    else if (login(header,headerh,loginid,pin,cash) == 2)
    {
        printf("Logged in user: %d\n\n",loginid);
        menu2(header,headerh,loginid,pin,cash);
    }
     //if account number is false and login returns 3 then give user 3 tries to login
    else if (login(header,headerh,loginid,pin,cash) == 3)
    {
        printf("Invalid account! try again\n");
        //Try 2
        while (attempts<=1)
        {
            printf("Enter pin:\n");
            INPUT
            scanf("%d",&pin);

            if (login(header,headerh,loginid,pin,cash) == 3)
            {
                attempts+= 1;
                printf("Data invalid or blocked account! try again\a\n");
            }
            else if (login(header,headerh,loginid,pin,cash) == 1)
            {
                printf("Logged in user: %d\n\n",loginid);
                menu(header,headerh,loginid,pin,cash);
                break;
            }
            else if (login(header,headerh,loginid,pin,cash) == 2)
            {
                printf("Logged in user: %d\n\n",loginid);
                menu2(header,headerh,loginid,pin,cash);
                break;
            }
            else
                printf("Invalid or blocked account! try again\n");
        }
    }
    else printf("Account Number invalid! Try again!\n");
    //Try 3
    if (attempts==2)
    {
        l = header->next;
        while (l)
        {
            if ((l->userid == loginid) && (l->state == 0))
            { 
                //Change state to 1 = Account locked
                l->state = 1;
                printf("Blocked Card\n");
                //Save to file
                write_custdb(header);
                create_log(headerh,12,loginid,1);
                write_logdb(headerh);
            }
            l=l->next;
        }
    }
} 
// function for login: if return 1 admin login, if 2 client login and 3 wrong password
int login(ulist header,hlist headerh, int acctno, int acctpin,atm cash)
{
    ulist l = header->next;
    //Loops through out the values from the clients structure
    while (l)
    {   //if account number, pin is true and state is unlock and type is admin return value 1
        if ((l->userid == acctno) && (l->pin == acctpin) && (l->state == 0) && (l->type == 1))
        {
            system("cls"); //clear screen              
            return 1;
        }
        //if account number, pin is true and state is unlock and type is customer return value 2
        else if ((l->userid == acctno) && (l->pin == acctpin) && (l->state == 0) && (l->type == 0))
        {
            system("cls"); //clear screen 
            return 2;
        }
        //if account number is true and pin is false and state is unlock return value 3
        else if ((l->userid == acctno) && (l->pin != acctpin) && (l->state == 0))
        {
            system("cls"); //clear screen 
            return 3;
        }
        l=l->next;
    }
    return 0;
}


/*---------------------------------------------------------------------------*/
/*---------------------------------ADMIN MENU--------------------------------*/
void menu(ulist header,hlist headerh,int login,int pin,atm cash)
{
    int op;
 
    printf("\t\t -------------------------------------------- \n");    
    printf("\t\t |          C ATM BANK LIMITED              | \n");
    printf("\t\t |           Admin Main Menu                | \n"); 
    printf("\t\t |                                          | \n");
    printf("\t\t |          1. Create customer accounts     | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t |          2. Delete customer accounts     | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t |          3. Unlock customer accounts     | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t |          4. Show all customers accounts  | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t |          5. Display ATM Transactions Log | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t |          6. Show ATM Vault Balance       | \n");
    printf("\t\t |                                          | \n");
    printf("\t\t |          0. Save&Exit                    | \n");
    printf("\t\t --------------------------------------------\n\n");
 
    INPUT
    scanf("%d",&op);

    switch (op)
    {
    case 1:
        system("cls");
        printf("\t\t --------------------------------------------\n");
        printf("\t\t |                                          | \n");
        printf("\t\t |        Create Customer Account           | \n");
        printf("\t\t |                                          | \n");
        printf("\t\t --------------------------------------------\n");
        create_client(header,headerh,login,pin,cash);
        break;
    case 2:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::          Delete customer           :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        delete_client(header,headerh,login,pin,cash);
        break; 
    case 3:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::           Unlock customer          :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        unlock_client(header,headerh,login,pin,cash);
        break;
    case 4:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::    Show all customers accounts     ::D \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        print_clients(header,headerh,login,pin,cash); 
        break;    
    case 5:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::    Display ATM Transactions Log    :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        print_log(header,headerh,login,pin,cash); 
        break;
    case 6:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::    Show ATM Vault Balance          :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        print_vault(header,headerh,login,pin,cash); 
        break;
    case 0:
        system("cls");
	printf("\t\t --------------------------------------------\n");
	printf("\t\t |          C ATM BANK LIMITED              | \n");  
	printf("\t\t |     Thank you for banking with us        | \n");    
	printf("\t\t |                                          | \n");
	printf("\t\t |          0. Save&Exit                    | \n");
	printf("\t\t --------------------------------------------\n\n");
        write_custdb(header);
        write_vaultdb(cash);
        write_logdb(headerh);
        system("exit");
        break;
    default:
        printf("Choose only the options listed\n");
    }
}
/*---------------------------------------------------------------------------*/
/*----------------------------------CLIENT MENU -----------------------------*/
void menu2(ulist header,hlist headerh,int login, int pin,atm cash)
{
    int op;
    
	printf("\t\t --------------------------------------------------\n");
	printf("\t\t |            C ATM BANK LIMITED                  | \n");  
	printf("\t\t |             Customer Banking                   | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          1. Deposit Funds                      | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          2. Withdraw Funds                     | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          3. Transfer Funds                     | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          4. Check Account Balance              | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          5. Display Account Transaction Log    | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          6. Change My Pin                      | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |          0. Save&Exit                          | \n");
	printf("\t\t --------------------------------------------------\n\n");
 
    INPUT
    scanf("%d",&op);

    switch (op)
    {
    case 1:    	
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::          Deposit Funds             :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
        cust_deposit(header,headerh,login,pin,cash);
        break;
    case 2:
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::         Withdraw Funds             :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
        cust_withdraw(header,headerh,login,pin,cash);
        break;
    case 3:
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::        Transfer Funds              :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
        cust_transfer(header,headerh,login,pin,cash);
        break;
    case 4:        
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::      Check Account Balance         :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
        query_acct(header,headerh,login,pin,cash);
        break;
    case 5:
    	system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::  Display Account Transaction Log   :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");    	
        print_custlog(header,headerh,login,pin,cash); 
        break;
    case 6:
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::         Change My PIN              :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
        change_client_pin(header,headerh,login,pin,cash);
        break;
    case 0:
        system("cls");
	printf("\t\t --------------------------------------------------\n");
	printf("\t\t |            C ATM BANK LIMITED                  | \n");  
	printf("\t\t |             Customer Banking                   | \n");
	printf("\t\t |                                                | \n");
	printf("\t\t |         Thank you for banking with us          | \n");    
	printf("\t\t --------------------------------------------------\n");
        printf("\n\n");
        write_custdb(header);
        write_logdb(headerh);
        write_vaultdb(cash);
        system("exit");
        break;
    default:
        printf("Choose only the options listed\n");
    }
}
 
 
//client option menu  
void option1(ulist header,hlist headerh,int login,int pin,atm cash)
{
    int decision;

    printf("\n\t0 - Back to menu                  1 - Exit\t");
    INPUT
    scanf("%d",&decision);

    if (decision == 0)
    {
        system("cls");
        menu2(header,headerh,login,pin,cash);
    }
    else if (decision == 1)
    {
        system("exit");
        write_custdb(header);
        write_vaultdb(cash);
        write_logdb(headerh);
        system("cls");
    }
}
//admin option menu
void option2(ulist header,hlist headerh,int login,int pin,atm cash)
{
    int decision;

    printf("\n\t0 - Back to menu                     1 - Exit\t");
    INPUT
    scanf("%d",&decision);

    if (decision == 0)
    {
        system("cls");
        menu(header,headerh,login,pin,cash);
    }
    else if (decision == 1)
    {
        system("exit");
        write_custdb(header);
        write_logdb(headerh);
        write_vaultdb(cash);
        system("cls");
    }
}
 
 // A dynamic memory allocation of the client ulist header 
ulist client_hlist (void)
{
    ulist header;
    header = (ulist) malloc (sizeof (users));
    if (header != NULL)
    {
        header->next = NULL;
    }
    return header;
}
// A dynamic memory allocation of the log list header 
hlist history_hlist(void)
{
    hlist headerh;
    headerh = (hlist) malloc (sizeof(logs));
    if (headerh != NULL)
    {
        headerh->next = NULL;
    }
    return headerh;
}
// A dynamic memory allocation of the bank balance list header 
atm banknotes(float balance)
{
    atm cash;
    cash.money = balance;

    return cash;
}
void create_log(hlist headerh,int noperation, int nopuserid,float noactions)
{
    hlist newdata;
    newdata = (hlist) malloc (sizeof(logs));
    if (newdata!=NULL)
    {
        newdata->operation=noperation;
        newdata->opuserid=nopuserid;
        newdata->opactivity=noactions;
        newdata->next=headerh->next;
        headerh->next=newdata;
    }
}
//checks account no = 0 false and 1 true 
int search_client(ulist header,int key)  
{
    ulist l = header->next;  
    while (l)
    {
        if (l->userid == key) 
            return 1;
        l=l->next;
    }
    return 0;
}


//ADMIN FUNCTIONS

//--------------------------------------------------------------------------------------------------//
// function to print all logs
void print_log(ulist header,hlist headerh,int login,int pin,atm cash)
{
    hlist h = headerh->next;
    
    printf("\n");
    printf("%s\n\n" ,__TIME__);
    printf("USERS\t\t\tID\t\tOPERATION\t\tACTION\n\n");
    while (h)
    {
        //Each log data is assign a unique number as a reference to determine each log operation
        if (h->operation == 1) printf("ADMIN\t\t\t%d\t\tUSERADD\t\t\t%6.2f\t\t\n",h->opuserid,h->opactivity);
        else if (h->operation == 2) printf("ADMIN\t\t%d\t\tUSERDELETED\t\t%6.0f\t\t\n",h->opuserid,h->opactivity); 
        else if (h->operation == 3) printf("ADMIN\t\t%d\t\tSHOWLIST\t\t%6.0f\t\t\n",h->opuserid,h->opactivity); 
        else if (h->operation == 4) printf("ADMIN\t\t%d\t\tUSERCHECK\t\t%6.0f\t\t\n",h->opuserid,h->opactivity);
        else if (h->operation == 5) printf("ADMIN\t\t%d\t\tUSERUNLOCK\t\t%6.0f\t\t\n",h->opuserid,h->opactivity); 
        else if (h->operation == 6) printf("ADMIN\t\t%d\t\tVAULT\t\t$%6.2f\t\t\n",h->opuserid,h->opactivity);
	else if (h->operation == 7) printf("CUSTOMER\t\t%d\t\tQUERY\t\t\n",h->opuserid);
        else if (h->operation == 8) printf("CUSTOMER\t\t%d\t\tDEPOSIT\t\t\t%6.2f\t\t\n",h->opuserid,h->opactivity);
        else if (h->operation == 9) printf("CUSTOMER\t\t%d\t\tWITHDRAW\t\t\t%6.2f\t\t\n",h->opuserid,h->opactivity);
        else if (h->operation == 10) printf("CUSTOMER\t\t%d\t\tTRANSFER\t\t%6.2f\t\t\n",h->opuserid,h->opactivity);
        else if (h->operation == 11) printf("CUSTOMER\t\t%d\t\tCHANGEPIN\t\t\t%6.0f\n",h->opuserid,h->opactivity);
        else if (h->operation == 12) printf("CUSTOMER\t\t%d\t\tLOCKED\t\t\n",h->opuserid);
        h=h->next;
    }
  option2(header,headerh,login,pin,cash);
}
//--------------------------------------------------------------------------------------------------//
// function to create new users
void create_client(ulist header,hlist headerh,int login,int pin,atm cash)
{
   int nuserid,npin,ntype,conf,nstate;
   float namount;
   ulist newdata;
    
start:
    do
    {
        printf("Enter Account No: \n");
        INPUT scanf("%d",&nuserid);
        if (search_client(header,nuserid) == 1)
        {
            printf("\tAccount exist already. Please enter another Account No\n"); 
            goto start;
        }
        printf("Enter pin (4 digits): \n");
        INPUT scanf("%4d",&npin);
        
	printf("Enter Balance: \n");
        INPUT scanf("%f",&namount);
        
        printf("Enter the type of user: \n");
        printf("0  -  Customer\t1  -  Admin\t");
        INPUT scanf("%d",&ntype);
        
        printf("Enter the initial state of the user: \n");
        printf("0 Active\t1 Blocked\t\t");
        INPUT scanf("%d",&nstate);
        
        printf("1 Save&Exit\t\t0 Edit\n");
        INPUT scanf("%d",&conf);
    
    }while (conf==0);
    //create users 
    create_user(header,nuserid,npin,namount,ntype,nstate);
    //add new value to atm balance
    cash.money+=namount;
 
    printf("%s\n" ,__TIME__);
    printf("CREATED SUCCESSFULLY!!\n");
    create_log(headerh,1,login,nuserid);
    option2(header,headerh,login,pin,cash);
}
void create_user(ulist header, int nuserid, int npin, float namount, int ntype, int nstate)
{
    ulist newdata;

    newdata = (ulist) malloc (sizeof (users));
    if (newdata != NULL)
    {
        newdata->userid = nuserid;
        newdata->pin = npin;
        newdata->sum = namount;
        newdata->type = ntype;
        newdata->state = nstate;
        newdata->next = header->next;
        header->next = newdata;
    }
}
//--------------------------------------------------------------------------------------------------//
// function to delete new users
void delete_client(ulist header,hlist headerh,int login, int pin,atm cash)
{
    ulist dlist;
    ulist users;
    int key;

    printf("Enter the ID of the client you want to delete\n");
    INPUT scanf("%d",&key);

    users = header;
    //loop 
    while (users->next != NULL)
    {
    	//switch and pass list values
        dlist = users;
        users = users->next;
        if ((users->userid) == key)
        {
            //Pass values	
            dlist->next = users->next;
            free(users);
            
            printf("%s\n" ,__TIME__);
            printf("Account no. %d deleted successfully\n",key);
            create_log(headerh,2,login,key); 
            option2(header,headerh,login,pin,cash);  
            return;
        }
    }
    printf("User does not exist\n");
    option2(header,headerh,login,pin,cash);
} 
//--------------------------------------------------------------------------------------------------//
// function to unlock users
int unlock_client(ulist header,hlist headerh,int login, int pin,atm cash) 
{
    ulist l = header->next; 
    ulist j = header->next;
    int key;

     
    printf("Block Accounts\t");
   //Loops through out the values of nodes and is a vector
    while (j)
    {
        if (j->state == 1) printf("\t%d\n\n",j->userid);
        j=j->next;
    }
    
    printf("Enter the Account no. you want to unlock\n");
    INPUT
    scanf("%d",&key);
    //Loops through out the values from the clients structure
    while (l)
    {
        if ((l->userid == key) && (l->state == 1))
        {
            l->state = 0;
            printf("Client %d successfully unlocked\n",key);
            create_log(headerh,5,login,key);
            option2(header,headerh,login,pin,cash);
            return 1;
        }
        l=l->next;
    }
    printf("Invalid data\n");
    option2(header,headerh,login,pin,cash);
    return 0;
}
//--------------------------------------------------------------------------------------------------//
// function to unlock users
void print_clients(ulist header,hlist headerh,int login,int pin,atm cash)
{
    ulist l = header->next;
   
    int i,j;
    int MAXSIZE = 0;
    int array[MAXSIZE];
    
     //Bubble sort 
       for (i = 0; i < MAXSIZE-1; ++i)  
          for (j = 0; j < MAXSIZE-i+1;++j)
            {                
                if (array[j] > array[j+1]){
                    int temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
  
        printf("\t\tAccount Number");
        printf("\t\tBalance\n\n");
       //loops through out list
        while (l)  
        {
            if (l->userid)
            {
                printf("\t\t%d \t\t\t$%6.2f\n",l->userid, l->sum);
                j++;
            }
            l=l->next;
            if ((l == NULL) && (j<MAXSIZE))
                l = header->next;
        }

    create_log(headerh,3,login,0);    
    option2(header,headerh,login,pin,cash);
}
//--------------------------------------------------------------------------------------------------//
// function to print ATM balance users
void print_vault(ulist header,hlist headerh,int login,int pin,atm cash)
{
    ulist l = header->next;
    float value = cash.money;
 
    printf("\n\t\tBalance\t\t");
    printf("\t\t$%6.2f\n",value);
    printf("\t\t-----------------------------------------\n\n");
    
    create_log(headerh,6,login,0);    
    option2(header,headerh,login,pin,cash);
}



//CUSTOMERS FUNCTIONS


//--------------------------------------------------------------------------------------------------//
//function view each account login account no. log data
void print_custlog(ulist header,hlist headerh,int login,int pin,atm cash)
{
    hlist h = headerh->next;
    
    printf("\n");
    printf("%s\n\n" ,__TIME__);
    printf("USER\t\t\tID\t\tOPERATION\t\tACTION\n\n");
     //Loops through out the values from the clients structure
    while (h)
    {
          
        if (h->opuserid == login)  {
        
	        if (h->operation == 7) printf("CUSTOMER\t\t%d\t\tQUERY\t\t\n\n",h->opuserid);
	        else if (h->operation == 8) printf("CUSTOMER\t\t%d\t\tDEPOSIT\t\t\t$%6.2f\t\t\n",h->opuserid,h->opactivity);
	        else if (h->operation == 9) printf("CUSTOMER\t\t%d\t\tWITHDRAW\t\t$%6.2f\t\t\n",h->opuserid,h->opactivity);
	        else if (h->operation == 10) printf("CUSTOMER\t\t%d\t\tTRANSFER\t\t$%6.2f\t\t\n",h->opuserid,h->opactivity);
	        else if (h->operation == 11) printf("CUSTOMER\t\t%d\t\tCHANGEPIN\t\t\t%6.0f\n",h->opuserid,h->opactivity);
	        else if (h->operation == 12) printf("CUSTOMER\t\t%d\t\tLOCKED\t\t\n",h->opuserid);
	        
    	}
        h=h->next;
    }
    option1(header,headerh,login,pin,cash);
 
     
}
//--------------------------------------------------------------------------------------------------//
// function to check each login account data
void query_acct(ulist header,hlist headerh,int login, int pin,atm cash)
{
    ulist l = header->next; 
    
    int decision;
      //Loops through out the values from the clients structure
    while (l)
    {
        if (l->userid == login)
        {
        	
        printf("\t\t%s\n" ,__TIME__);
        printf("\t\t                                     \n");
        printf("\t\t       Account No: %6d               \n", l->userid);
        printf("\t\t       Pin: %4d\n                    \n",l->pin);
        printf("\t\t       Balance: $%6.2f               \n",l->sum);
        printf("\t\t                                     \n"); 
        printf("\t\t -------------------------------------- \n");
        
        create_log(headerh,7,login,pin);
        option1(header,headerh,login,pin,cash);

        }
        l=l->next;
    }
 
}
//--------------------------------------------------------------------------------------------------//
//function to change each login account pin data
int change_client_pin(ulist header,hlist headerh,int login,int pin,atm cash) // return 1 if changed, 0 otherwise
{
    ulist l = header->next;
  
    int newpin;
    int oldpin;
    int decision;
    int i=0;
 
    printf("Enter the current PIN\n");
    INPUT
    scanf("%d",&newpin);
 
    //checks if PIN is true
    if (pin==newpin)
    {    //Loops through out the values from the clients structure
        while (l)
        { //checks if user is true
            if (l->userid == login)
            { 
                printf("Enter the new PIN ( 4 digits )\n");
                INPUT
                scanf("%d",&oldpin); 
              /*  for(i=0;i<=3;i++){
                	oldpin = getch();
                	printf ("*");
                 	l->pin = oldpin;
                }*/
    
    		l->pin = oldpin;
    			
                printf("%s\n\n" ,__TIME__);
                printf("PIN successfully changed\n");
                create_log(headerh,11,login,newpin);
                write_custdb(header);
                
		option1(header,headerh,login,oldpin,cash);
            }
            l=l->next;
        }
    }
    else
    {
        printf("Invalid PIN\n");
        option1(header,headerh,login,pin,cash);
    }
}
//--------------------------------------------------------------------------------------------------//
//function to deposit/add new value to each login account balance
void cust_deposit(ulist header, hlist headerh,int login, int pin, atm cash)
{
 //gets structures ulist values and assign a variable l
    ulist d = header->next;
    
    float total, value = 0;
    float fee = 0;
   
    
    printf("How much do you like to deposit?\n");
    INPUT 
    scanf("%f",&value);
    
  //Loops through out the values from the clients structure     
    while (d)
    {   //checks if user is true
        if (d->userid == login)
        {
            total = value;
            //add new value to atm balance
	    cash.money+=value;
            //substract fee from login account
            d->sum-=fee;
           	//add new value to login account balance
            d->sum+=total;
       
	    printf("A fee of $%6.2f was deducted\n\n",fee);
            printf("Your balance is now $%6.2f\n",d->sum);        

        }
        //Add all values to variable l and save it to the structure ulist
       d=d->next;
    }
    //Save to file
    create_log(headerh,8,login,total);
    write_vaultdb(cash);
    write_logdb(headerh);
    option1(header,headerh,login,pin,cash);
}
//--------------------------------------------------------------------------------------------------///
//function to pay school fee value from a login account balance
void cust_transfer(ulist header,hlist headerh,int login, int pin,atm cash)
{
    ulist l = header->next;
    ulist j = header->next;

    int uid = 0;
    float value;
    float fee = 0.09;   
//declare a goto starter = if account number is yours start here    
start:
    printf("Enter the Account No to transfer funds\n");
    INPUT
    scanf("%d",&uid);

    //checks if user is not transfering to his/her own account
    if ((search_client(header,uid)==1) && (login != uid))  
    {   
         //Loops through out the values from the clients structure
        while (l)
        {   //checks if user is true
            if (l->userid == login)
            {
                printf("Indicate the amount you wish to transfer\n");
                INPUT
                scanf("%f",&value);
                if (value<=(l->sum))
                {
                   //substract fee value from login account 
                    l->sum-=fee;
                   //add fee value to atm balance		
		    cash.money+=fee;
		   //substract transfer value from login account 
                    l->sum-=value;
                     //Loops tru the values from the clients structure
                    while (j)
                    { //checks if user is true
                        if (j->userid == uid)
                        { 
                            j->sum+=value;
                            
                            printf("%s\n\n" ,__TIME__);
                            printf("A fee of $%6.2f was deducted\n\n",fee);
                            printf("Transferred $%6.2f \nFrom the Account no. %d to Account no. %d\n\n",value,l->userid,j->userid);       
			    printf("Your Current Balance is $%6.2f\n",l->sum);                     
                            create_log(headerh,10,login,uid);
                        }
                        //Add all values to variable l and save it to the structure ulist
                        j=j->next;
                    }
               
		}else{
                    printf("There is not enough funds available in your account\n");
                    printf("You only have $%6.2f in your account\n",l->sum);
                }
                  
            }
            //Add all values to variable l and save it to the structure ulist
            l=l->next;
        }
    }
    else if (login == uid)
    {
        printf("Sorry, not allowed. Try another account no. This is yours\n\n");
        goto start;
    
	}else
        printf("Account no %d do not exist in our records \n",uid);
    LINE
    
    //Save to file
    write_vaultdb(cash);
    write_logdb(headerh);   
    option1(header,headerh,login,pin,cash); 
}
//--------------------------------------------------------------------------------------------------//
//function to withdraw value from a login account balance
void cust_withdraw(ulist header,hlist headerh, int login, int pin, atm cash)
{
    ulist l = header->next; 
    
    float value = 0;
    float money = 0;
    float fee = 0.02;
    float max = 30000;
    float min = 10;
    //Withdraw Restrictions
    do
    {
        printf("Indicate the amount you wish to withdraw\n");
        INPUT 
        scanf("%f",&value);
        if (value>max) printf("The maximum withdrawal is $%6.2f\n\n",max);
        else if (value<min) printf("The minimum withdrawal is $%6.2f\n\n",min); 
        
    }while (value>max);
    //Set values
    float total = value;
    
    //Loops through out the values from the clients structure
    while (l)
    {
        if (l->userid == login)
        {
        	//Check ATM Vault
		if(cash.money>=value){
		
		    if (l->sum>=value)
		    {

	                money++;  
	                l->sum-=fee;
			//add fee value to atm balance		
			cash.money+=fee;	 
			//substract new value from atm balance
			cash.money-=value;    
			//substract new value from login balance             
			l->sum-=total;
		           
		        printf("%s\n\n" ,__TIME__);
		        printf("A fee of $%6.2f was deducted\n\n",fee);
		        printf("You now have $%6.2f in your account\n",l->sum);
		        create_log(headerh,9,login,total);
		        option1(header,headerh,login,pin,cash);
		       
	             }else{
		       printf("Insufficient Funds within A/c!\n");
		       printf("You only have $%6.2f in your account\n\n",l->sum);
		       option1(header,headerh,login,pin,cash);	
		     }
		
		}else{
		printf("Insufficient Funds within ATM at this time!\n");
		printf("Only $%6.2f available for withdrawal\n\n",cash.money);
		option1(header,headerh,login,pin,cash);	
            }
        }
        l=l->next;
    }
    
write_logdb(headerh);
write_vaultdb(cash);
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
	
    FILE *f_clients= fopen("customers.txt", "r"); 
    int res = fscanf(f_clients, "%d\t\t%d\t\t%f\t\t%d\t\t%d\n", &userid,&pin,&sum,&type,&state);
    for (i = 0; res > 0; i++)
    {
        create_user(header,userid,pin,sum,type,state);
        res = fscanf(f_clients, "%d\t\t%d\t\t%f\t\t%d\t\t%d\n", &userid,&pin,&sum,&type,&state);
    }
    fclose (f_clients);
}
//--------------------------------------------------------------------------------------------------//
//Writes customers banking details to file ie. account no, pin, total funds, account type, and status
void write_custdb(ulist header)
{
    ulist l=header->next;
    FILE *f_clients = fopen("customers.txt", "w");
 
    while (l)
    {
        fprintf (f_clients, "%d\t\t%d\t\t%6.2f\t\t%d\t\t%d\n", l->userid,l->pin,l->sum,l->type,l->state); 
        l=l->next;
    }
    fclose(f_clients);
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
