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
	       
		        newdata->userid = nuserid;
		        newdata->pin = npin;
		        newdata->sum = namount;
		        newdata->type = ntype;
		        newdata->state = nstate;
		        newdata->next = header->next;
		        header->next = newdata;
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
	       
		        newdata->userid = nuserid;
		        newdata->pin = npin;
		        newdata->sum = namount;
		        newdata->type = ntype;
		        newdata->state = nstate;
		        newdata->next = header->next;
		        header->next = newdata;
		        
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
        
        break;
    case 2:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::          Delete customer           :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
       
        break; 
    case 3:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::           Unlock customer          :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        
        break;
    case 4:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::    Show all customers accounts     :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
       
        break;    
	case 5:
        system("cls");
        printf("\t\t -----------------------------------------\n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::    Display ATM Transactions Log    :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t -----------------------------------------\n");
        
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
       
        break;
    case 4:        
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::      Check Account Balance         :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
        
        break;
    case 5:
    	system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::  Display Account Transaction Log   :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");    	
    
        break;
    case 6:
        system("cls");
        printf("\t\t ---------------------------------------- \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ::         Change My PIN              :: \n");
        printf("\t\t ::                                    :: \n");
        printf("\t\t ---------------------------------------- \n");
      
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
