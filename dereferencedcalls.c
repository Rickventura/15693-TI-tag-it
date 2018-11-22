/*
 Author: @Rickventura 
 date  : Nov-21-2018 
 
*/

/*
 C language pointers to functions can turn out very useful in many instances. 
 Besides the basic (example1), this example file, addresses the more complex issue of arrays of pointers to functions. 
 Type definitions keep the declarations of this type of pointers neat and clear of errors.

 example 1: Simple pointers to functions view.
 example 2: Locally declared array of pointers to functions and usage.
 example 3: Array of functions sent as parameters. Accessing elements of the array by means of a pointer to pointer to functions
 example 4: Array of functions sent as parameters. Accessing elemetnts of the array by an array index,
*/

#include <stdio.h>


//void (*deref_func)(char *caller) ; // deref_function is defined as a pointer to function

typedef void (*PTR_TO_FUNC)(char *); // type PTR_TO_FUNC is a pointer to a function of char * argument returning void
typedef void(*(*PTR2PTR_2_FUNC))(char *); // type pointer to a pointer to a function of char * argument  returning void
typedef void (*ARR_FUNC[])(char *);  // type defined as a pointer to an array of pointers to functions


//functions declarations

void funct1(char *caller);
void funct2(char *caller);
void funct3(char *caller);
void funct4(char *caller);
void endOfArr(char *caller);// endOfArr is a dummy function used to signal the end of an array of functions


PTR_TO_FUNC setof_functions[] = {funct1,funct2,funct3}; 

ARR_FUNC functions_arr  = {funct1,funct2,funct3,funct4,funct1,funct2,funct3}; // same as set_of functions using type FUNC_ARR 

ARR_FUNC functions_arr2 = {funct1,funct2,funct3,funct4,funct1,funct2,funct3,endOfArr}; // endOfArr is a dummy function used to signal end of the array

void example1();
void example2();
void example3(PTR_TO_FUNC *arr); // as declared here arr is a pointer to a pointer of functions of char * argument
void example4(ARR_FUNC arr); // as declared here arr is a pointer to a pointer of functions of char * argument
void example5(PTR2PTR_2_FUNC);

void main()
{
 char *caller = "main";
 

 example1(); 

 example2();
 
 example3(functions_arr2);

 example4(functions_arr);
 
 example5(setof_functions);  
}


// function definitions

void example1()
{
 char *caller = "example1";
 void (*deref_func)(char *caller) ;  
 printf("\n---------------------------------------\n"); 
 printf("\nvery basic use of derefereced functions\n"); 
 printf("\n---------------------------------------\n"); 

 deref_func = funct1; 
 (*deref_func)(caller);

 deref_func = funct2; 
 (*deref_func)(caller);

 deref_func = funct3; 
 (*deref_func)(caller);

/* hint: the compiler recognize dref_func[i] as a function thus ther is no need for parenthesis
   for the sake of clarity it's better to add the paretheses.
*/

 deref_func = funct4; 
 deref_func(caller);
//(*deref_func)(caller);



}
void example2()
{

 PTR_TO_FUNC Functions[] = {funct1,funct2,funct3,funct4,funct1,funct2,funct3,funct4,funct1};
 char caller[] = "example2";
 int i;
 long unsigned maxi;
 printf("\n-----------------------------------\n"); 
 printf("\nLocally declared array of functions\n"); 
 printf("\n-----------------------------------\n"); 

 maxi = sizeof(Functions)/sizeof((*Functions));//here we can calculate the size for the arr is declared inside the function
 printf ("------array size = %lu\n", maxi);
 for (i==0;i<maxi;i++) Functions[i](caller);

}


void example3(PTR_TO_FUNC *arr)
/*
 this example receives a pointer to an array of pointers to functions
 */
{

 PTR2PTR_2_FUNC pf; // valid declaratioon of a pointer to a pointer of a function
 //PTR_TO_FUNC *pf; // also a valid declaratioon of a pointer to a pointer of a function
 char *caller = "example3: pointer to pointer to functions";
 long unsigned max = 0;

  printf("\n-----------------------------------------------------------------------------------\n");                                    
  printf("\narray of functions passed as parameter and use of pointers to pointers to functions\n"); 
  printf("\n-----------------------------------------------------------------------------------\n");                                    

  pf = arr;
  /*
    the special function endofArr at the end of the arry signals the end of the array 
  */
  
  while (*pf != endOfArr){
	(**pf++)(caller); // a pointer to a pointer of a functionr is used instead of (*arr[i])
         max++;
  } 
  printf ("------array size = %lu\n", max);
}

void example4(ARR_FUNC arr)
{
 char *caller = "example4: pointer to pointer to functions";
 int i ; 
 long unsigned maxi;
  printf("\n----------------------------------------------------------------------------------------\n");                                    
  printf("\narray of functions passed as parameter, use of indexed arrays of pointers to functions\n");
  printf("\n----------------------------------------------------------------------------------------\n");                                    
                                    
  maxi = sizeof(functions_arr)/sizeof(*functions_arr);
  printf ("------array size = %lu\n", maxi);

  for (i = 0; i < maxi ; i++)
	  arr[i](caller);
	  //(*arr[i])(caller);// hint the compiler recognize arr[i] as a function thus ther is no need for parenthesis
          
}

void example5(PTR2PTR_2_FUNC arr)
{
 char *caller = "example5: pointer to pointer to functions";
 int i ; 
 long unsigned maxi;
  printf("\n----------------------------------------------------------------------------------------\n");                                    
  printf("\nanother way of passing an array of functions as poniter to pointers to functions\n");
  printf("\n----------------------------------------------------------------------------------------\n");                                    

  maxi = sizeof(setof_functions)/sizeof(*setof_functions);
  printf ("------array size = %lu\n", maxi);

  for (i = 0; i < maxi ; i++)
	  (**arr++)(caller);
          
}

void endOfArr(char *caller)
{
 // dummy function to signal end of arr
}

void funct1(char *caller)
{
    printf("this is funct1 called by %s\n",caller);
}   

void funct2(char *caller)
{
    printf("this is funct2 called by %s\n",caller);
}   

void funct3(char *caller)
{
    printf("this is funct3 called by %s\n",caller);
}   

void funct4(char *caller)
{
    printf("this is funct4 called by %s\n",caller);
}   
