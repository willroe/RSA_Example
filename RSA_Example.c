#include <stdio.h>
#include <stdlib.h>
//#define NDEBUG
#include <assert.h> //for bug checking
#include <time.h>   //for clock()
#include <gmp.h>    //for large numbers
#include <unistd.h>

int gcd(int inE, int inZ);

int xgcd(int inE, int inZ);
 
int * keygen (int * ptr, int inP, int inQ, int inE); 

int modExp (int message, int inE, int inN); 	 

void question2_2();

int question2_3and4(int num);

void defaultFunction ();

void program_pause();


int main()  
{
    int option;

    question2_2();

    return 0;

} 



//*****************************************************************//
//              BEGINNING OF QUESTION 2.2
//****************************************************************//

void question2_2()
{
    int inP = 0, inQ = 0, inE = 0,
        inZ = 0, inN = 0, inD = 0,
        m = 0, encrypt_m = 0, decrypt_m = 0,
        option;
    
    int array[4];


    printf("Task List that will happen to encrypt and decrypt message: \n");
    printf("Task 1 - gcd method \n");
    printf("Task 2 - xgcd method \n");
    printf("Task 3 - RSA key generation method \n");
    printf("Task 4 - RSA Encryption \n");
    printf("Task 5 - RSA Decryption \n\n");
    



    printf("*** Enter non-zero intgers *** \n");
    printf("If all zeros are entered then default values will be used. \n");
    printf("default values are inP = 17, inQ = 11, inE = 7, and m = 88 \n");
    printf("These are the values of the example for the text book CSN on page 278. \n\n");
    
    printf("Enter values for Message, inP, inQ, and inE: ");
    fflush(stdout);
    scanf("%d %d %d %d", &m, &inP, &inQ, &inE);
    
    if( inP == 0 && inQ == 0 && inE == 0 && m == 0 )
    {
    inP = 17;
    inQ = 11;
    inE = 7;
    m = 88;
    }

    printf("\n");

    keygen( array, inP, inQ, inE);

   
    printf("In 2_2 function array address is: %p \n", array);

    printf("Message (m) is: %d \n", m);
    
    // Array has values for e, n, and d. array = {e, n, d}
    printf("The Public key pair are {%d, %d} \n", *array, *(array+1) );
    printf("The Private key pair are {%d, %d} \n", *(array+2), *(array+1) );

    encrypt_m = modExp (m, *array, *(array + 1));
    
    printf( "ecrypt_m is: %d \n", encrypt_m );
    printf("The Private key pair are {%d, %d} \n", *(array + 2), *(array + 1));
    decrypt_m = modExp (encrypt_m, *(array + 2), *(array + 1) ) ;
    
    printf( "decrypt_m is: %d \n", decrypt_m );

    printf("\n");

}




int gcd(int inE, int inZ)
{
   int a, b, q, r, answer, tmp;

   a = inE;
   b = inZ;

   if (a < b) 
   {
       tmp = a;
       a   = b;
       b   = tmp;
   }

       assert(printf("| Dividend | Divisor  | Quotient | Remainder|\n"));
       assert(printf("_____________________________________________\n"));
   
   while(1)
   {
   
       q = a/b;
       r = a % b;
       assert(printf("| %5d    | %5d    | %5d    | %5d    |\n", a, b, q, r ));
       answer = b;
       
       if(r == 0) 
       {
           break;
       }
   
       
       a = b;
       b = r;

   }
      
   assert(printf("\n\t The gcd for %d and %d is: %d\n", inE, inZ, answer));
   
  
   
   return (answer);



}

int xgcd(int inE, int inZ)
{
    int a, a_Oldest = 1, 
        a_Older = 0, 
        b, b_Oldest = 0, 
        b_Older = 1;

    int d_Older, 
        d, 
        q, 
        r, 
        gcd = 0, 
        multi_inv = 0, 
        tmp;

    d_Older = inE;
    d       = inZ;
   
   if (d_Older < d) 
   {
       tmp      = d_Older;
       d_Older  = d;
       d        = tmp;
   }
   
   tmp = d_Older;
   //assert( printf(" \n tmp is: %d \n", tmp ) );
   

       assert( printf("|    a     |    b     |    d    |    q    |\n") );
       assert( printf("___________________________________________\n") );


    while (1)
    {

        q = d_Older / d;
        r = d_Older % d;
        a = a_Oldest - a_Older * q;
        b = b_Oldest - b_Older * q;

        if(r == 0 && d == 1)
        {
        
            if (multi_inv <= 0)
            {
                multi_inv = multi_inv + tmp;  
            }
        
            assert( printf("The gcd is: %d and the mutiplicative inverse is: %d. \n",
                       gcd, multi_inv) );
           
            return (multi_inv);
               
        }
        if(r <= 0 && d != 1) 
        {
          assert( printf("Error, There is no mutiplicative inverse for %d and %d. \n", 
                      inE, inZ ) );
          return (-1);
        }

        if (a_Oldest == 1 && b_Oldest == 0)
        {
            assert( printf("| %5d    | %5d    | %5d    |          |\n", 
                        a_Oldest, b_Oldest, d_Older ) );
            assert( printf("| %5d    | %5d    | %5d    | %5d    |\n"  , 
                        a_Older,  b_Older, d, q ) );

        }

        assert( printf("| %5d    | %5d    | %5d    | %5d    |\n", 
                    a, b, r, (d/r) ) );


        gcd = r;
        multi_inv = b;

        a_Oldest = a_Older;
        a_Older  = a      ;
        b_Oldest = b_Older;
        b_Older  = b      ;
        d_Older  = d      ;
        d        = r      ;


    }
    


}


int * keygen (int * ptr, int inP, int inQ, int inE) 
{
    
   int p = inP, q = inQ, e = inE, n, z, d, r = 0;
   
   printf("--------------------------------------------------------------- \n");

   printf("First we have to find the values of n. \n"
       "To find n we need to multiply P and Q, so \n"
       "the formulat is: n = p * q \n"
       "With our number the formula is: n = %d * %d \n" , inP, inQ);
   
   n = p * q;
   
   printf("\n So n = %d as in %d = %d * %d \n\n" , n, n, inP, inQ);
   
   program_pause();  

   z = (p-1)*(q-1);

   printf("Next we need to calculate phi(n) which is(p - 1)(q - 1) \n"
          "So we have %d = (%d - 1)(%d - 1) \n", z, p, q);

   program_pause();
   
   
   if (e <= 1 || gcd(e,z) != 1 || e > z)
   {
       e = 1;
       int count;      // Does not matter what number we start with.
       srand(count + time(NULL));   // Initialization of srand with 
                                    // count and time as seed.
       
       while ( e <= 1 )
       {
                  
           assert(printf("\n Inside of keygen inside while ( e <= 1 || e > z) \n"));
           assert(printf("     e is: %d \n", e));

           r = rand()%z;    // Returns random number less than z
           
           if( gcd(r,z) == 1 ) e = r;
           assert(printf("     \n Now e is: %d and r is: %d \n\n", e, r));

           count++;
       
       }
   }
   assert(printf("e is: %d \n", e));
  

   d = xgcd(e,z);

   ptr[0] = e;
   ptr[1] = n;
   ptr[2] = d;

   
   
   printf("ptr address is : %p \n arr address is: %p \n", ptr, ptr);

   assert(printf("n is: %d, z is: %d, e is: %d, d is: %d, r is: %d \n", 
               n, z, e, d, r ));
 
   return ptr;

}


//
// Calculate c = a^b mod n
//
int modExp (int message, int inE, int inN) 	 
{

	int x = 1;
	int w = message; 
	int y = inE;
	
	while (y > 0) {
		int t = y%2; 
		y = y/2;
		if (t == 1) { 
			long xLong = x * w; 
			x = (int) (xLong % inN);
		}
		
		long wLong = w * w;
		w = (int) (wLong % inN);
        
	}
    assert( printf("In modExp - message is: %d \n", message ));
    assert( printf("In modExp - inE is: %d \n", inE ));
    assert( printf("In modExp - inN is: %d \n", inN ));
    assert( printf("In modExp - x is: %d \n", x ));
    assert( printf("In modExp - w is: %d \n", w ));
    assert( printf("In modExp - y is: %d \n", y ));
	
    return x;
}



//*****************************************************************//
//                   END OF QUESTION 2.2
//****************************************************************//

void program_pause()
{
    
    char n = '\0';

    while(1)
    {
        
        

        printf("\n ENTER in n to continue... \n");
        
        fflush(stdout);

        scanf(" %c", &n);

        if (n == 'n')
            break;
       

    };

    printf("-------------------------------------- \n");
}







