#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#define size 10000

int globalprecision=3 ;
bool nobraces = false ;
bool bracefound =false ;
int cols ;

void input(void);
int initialcheck(char *str,int) ;  /// Checks for the validity of the expression
int bracecheck(char * , int) ;  /// Checks for the presence of braces and returns the position of them based on the parameters
bool checkifoperator(char *,int); /// Called by initialcheck() and returns true if exp contains invalid operators
char* cutifandinsert(char *str ,int ipos , int fpos , double value) ; /// Inserts the final value of the exp within braces and removes the span
                                          /// from the brace start to end and substitutes in the final expression

char* floattostring(double value,int precision) ; /// converts a float to a string of specified precision and returns the strin garray
void logicbegin(char * ) ;  /// takes out only the expression within the innermost braces and calls the main logic function
void mailsend(void) ;
char* mainlogic(char * str) ;  /// this returns the expression value !
long int fact(int i) ; ///returns factorial of i
char * plus_minus_solve(char *) ;  /// multiplies + and - or -- and -+ ambiguities
double binaryoperation(char *str,int returnvalue ,int index) ; /// This takes the task of binary operations like add , sub, mul , permutation
double trig(char *str , int ipos ,int fpos,char*fun) ;
void fileoutput(char * str) ;
void finalanswer(char *str) ;
char* removespaces(char *str) ;



double trig(char *str, int ipos , int fpos ,char*fun)
{
    char myarr[1000] ={'\0'} ;
    int k = 0,i =0 ;
    if(strcmp(fun,"sin")==0)
    {
        for(i=ipos+3 ,k=0 ; i<=fpos ; i++,k++)
        {
            myarr[k] = str[i] ;
        }
        double value = sin(atof(myarr)* M_PI/180.0) ;
        return value ;
    }

    if(strcmp(fun,"tan")==0)
    {
        for(i=ipos+3 ,k=0 ; i<=fpos ; i++,k++)
        {
            myarr[k] = str[i] ;
        }
        double arg = atof(myarr) ;
        if(arg==90)
        {
            initialcheck("error",4) ;
        }
        double value = tan(arg* M_PI/180.0) ;
        return value ;
    }

    if(strcmp(fun,"sec")==0)
    {
        for(i=ipos+3 ,k=0 ; i<=fpos ; i++,k++)
        {
            myarr[k] = str[i] ;
        }
        double arg = atof(myarr) ;
        if(arg==90)
        {
            initialcheck("error",4) ;
        }
        double value = 1.0/(double)cos(arg* M_PI/180.0) ;
        return value ;
    }

    if(strcmp(fun,"cot")==0)
    {
        for(i=ipos+3 ,k=0 ; i<=fpos ; i++,k++)
        {
            myarr[k] = str[i] ;
        }
        double arg = atof(myarr) ;
        arg==0 ?initialcheck("error",4):1 ;
        double value = 1.0/(double)tan(arg* M_PI/180.0) ;
        return value ;
    }

    if(strcmp(fun,"cos")==0)
    {
        for(i=ipos+3 ,k=0 ; i<=fpos ; i++,k++)
        {
            myarr[k] = str[i] ;
        }
        double arg = atof(myarr) ;
        double value = cos(arg* M_PI/180.0) ;
        return value ;
    }


    if(strcmp(fun,"cosec")==0)
    {
        for(i=ipos+5 ,k=0 ; i<=fpos ; i++,k++)
        {
            myarr[k] = str[i] ;
        }
        double arg = atof(myarr) ;
        arg==0? initialcheck("error",4) :1 ;
        double value = 1.0/(double)sin(arg* M_PI/180.0) ;
        return value ;
    }


}

long int fact(int i)
{
    int k =i ; long int factorial = 1 ;
    for(k=i ; k>=1 ; k--)
    {
        factorial*=k;
    }
    return factorial  ;
}

int main(void)
{
    system("clear") ;fflush(stdout) ;
    setbuf(stdout,NULL) ;
    input() ;
    return 0 ;
}

void fileoutput(char string[])
{
    int i ;printf("\n") ;
    system("sleep 0.1") ;
    char outputstring[400] ;
    int k ;
    for(i=0 ,k=0;string[i] ;i++)
    {
        printf("%c",string[i]);
        outputstring[k]=string[i] ;
        k++ ;
        if(checkifoperator(string,i+1) || checkifoperator(string,i))
            {
                printf(" ") ;
                outputstring[k]=' ' ;
                k++ ;
            }

    }
    for(i= k ;k<i+10 ;k++)
    {
        outputstring[k]=0 ;
    }

    FILE *f ;
    f=fopen("mail.txt","a");
    fprintf(f,"\n%s",outputstring);
    fclose(f);
}

char* removespaces(char *str)
{
    int i=0 ,j=0 ; char exp[size]={'\0'} ;
    strcpy(exp,str);
    for(i=0 ; exp[i] ; i++)
    {
        if(exp[i]==32)
        {
            for( j=i;exp[j];j++)
            {
                exp[j]= exp[j+1];
            }
        }
    }
    str = exp ;
    return str ;
}


void finalanswer(char *str)
{
    char a[size];
    sprintf(a,"echo %c%s%c | t%ci%cet -F %cay -w 200",'"',str,'"',111,108,103);
    system(a) ;
    printf("\n\n\nDo you want to send the result to your email ? (yes || no) : ") ;
    char ch[20]  ;
    gets(ch) ;
    if(strcmp(ch,"yes")==0 || strcmp(ch,"y")==0)
        mailsend() ;
    printf("\n\n\nPress <Enter> to continue") ;
    system("rm mail.txt") ;
    getchar() ;
    main() ;
}


char * plus_minus_solve(char *str)
{
    int i =0 ;
    char exp[size] ;
    strcpy(exp,str) ;
    int n = strlen(str) ;

    for(i=n-1 ;i>0 ; i--)
    {
        if(exp[i]=='-')
        {
            if(exp[i-1]=='+')
            {

                exp[i-1]='-' ;
                for(i ; exp[i] ; i++)
                {
                    exp[i] = exp[i+1] ;
                }
            }
        else if (exp[i+1] == '-')
                 {
                     exp[i] = '+' ;
                    for(i=i+1 ; exp[i] ; i++)
                    {
                        exp[i] = str[i+1] ;
                    }
                 }
        }

    }
    str= exp ;
    return str ;
}



void logicbegin(char *str)  /// This will separate the innermost expression within braces calls the mainlogic with the innermost string as argument
{
    str = removespaces(str) ;
    int ipos = bracecheck(str,1) ;
    int fpos = bracecheck(str,2 );
    int count=0 , i = 0;
    bool operatorexists=false;
    char temp[size]  ;
    if(bracecheck(str,0)==-1)
    {
        bracefound = true ;
        for(i=ipos+1 ;i<fpos ; i++,count++)
        {
            temp[count] = str[i] ;
        }

        for( i=0 ;i<20 ;i++)
            temp[count+i]='\0' ;
    }
    if(bracecheck(str,0)==-2)
    {
        printf("\n\aInvalid Usage of braces ! ") ;
        main() ;
    }
    else if(bracecheck(str,0)==-3)
    {
        bracefound = false ;
        strcpy(temp,str) ;
    }

    ///Now temp contains the innermost brace exp

    char a[size]={'\0'} ;
    int k =0 ;strcpy(a,str) ;
    strncpy(temp,mainlogic(temp),10000) ;
    char abackup[size] ;
    strcpy(abackup,a) ;

    int mycounterfornow ;
    operatorexists = false ;
    for(mycounterfornow= 1 ; temp[mycounterfornow] ; mycounterfornow++)
    {
        if(checkifoperator(temp,mycounterfornow))
        {
            operatorexists = true ;
            break ;
        }
    }

    if((ipos !=0 || fpos!=0) && operatorexists==false)
    {
        for(i=ipos ; temp[i-ipos] ; i++)
        {
            a[i] = temp[i-ipos] ;
        }
        for(i,k=fpos+1 ;abackup[k] ; k++ , i++)
        {
            a[i] = abackup[k] ;
        }
        for(k=0 ; k<10 ; k++)
        {
            a[i] = '\0' ;
        }
    }

    else if((ipos!=0 || fpos!=0) && operatorexists==true)
    {
        int tc =0  ; // This is the temp counter variable to traverse from 0 to n-1 through temp

        for(i=ipos+1 ,tc=0 ; temp[tc] ; i++,tc++)
            {
                a[i] = temp[tc] ;
            }
            for(k=fpos ;abackup[k] ; k++ , i++)
            {
                a[i] = abackup[k] ;
            }
            for(k=0 ; k<20 ; k++)
            {
                a[i] = '\0' ;
            }
    }

    else strcpy(a,temp) ;

    fileoutput(abackup) ;
    strcpy(abackup,a) ;
    str = abackup ;

    for(i=1 ; str[i] ;i++)
    {
        if(checkifoperator(str,i) || strstr(str,"sin") || strstr(str,"cos") || strstr(str,"tan")|| strstr(str,"cot")|| strstr(str,"sec") || strstr(str,"cosec"))
        {
            operatorexists = true ;
            break ;
        }
    }
    if(operatorexists)
    {
        logicbegin(str) ;
    }
    else
    {
       fileoutput(str) ;
       finalanswer(abackup) ;
    }
}



char* mainlogic(char *str)
{
    str =plus_minus_solve(str) ;
    bracefound=false ;
    char exp[10000]={'\0'};
    int i=0  ;
    if(str[0]=='(')
    {   bracefound = true ;
        for(i=1 ; i<strlen(str)-1 ; i++)
        {
            exp[i-1] = str[i];
        }
    }

    else
    {
        strcpy(exp,str) ;
    }
    str =removespaces(exp) ;
    strcpy(exp,str) ;

    ///e as constant
    for(i=0 ; exp[i] ; i++)
    {
        if(exp[i]=='e' && exp[i+1]!='c')
        {
            str = cutifandinsert(exp,i,i,2.7182818284590452353602874713527) ;
            strcpy(exp,str) ;
        }
    }

///  PERMUTATION

    for(i=0 ; exp[i] ; i++)
    {
        exp[0]=='p' || exp[strlen(exp)-1]=='p' ? initialcheck("error",2):1 ;
        if(exp[i]=='p')
        {
            int ipos = ipos_fpos_find(exp,1,i) ;
            int fpos = ipos_fpos_find(exp,2,i) ;

            double value1 = binaryoperation(exp,1,i);
            double value2 = binaryoperation(exp,2,i) ;

            if((value1<value2) || value1!= (int)value1  || (value2!= (int)value2))
            {
                initialcheck("error",2) ;
            }
            long int value = (fact(value1)/(fact(value1-value2))) ;

            str = cutifandinsert(exp,ipos,fpos,(double)value) ;
            strcpy(exp,str) ;
            return str ;
        }

    }


    ///  Combination

    for(i=0 ; exp[i] ; i++)
    {
        if(strstr(exp,"cos")==0 && strstr(exp,"cot")==0 && strstr(exp,"cosec")==0)
        {
            exp[0]=='c' || exp[strlen(exp)-1]=='c' ? initialcheck("error",3):1 ;
        }

        if(exp[i]=='c')
        {
            if(isalpha(exp[i-1]) || isalpha(exp[i+1])) break;

            int ipos = ipos_fpos_find(exp,1,i) ;
            int fpos = ipos_fpos_find(exp,2,i) ;

            double value1 = binaryoperation(exp,1,i);
            double value2 = binaryoperation(exp,2,i) ;

            if((value1<value2) || value1!= (int)value1  || (value2!= (int)value2))
            {
                initialcheck("error",3) ;
            }

            long int value = (fact(value1)/((fact(value1-value2))*fact(value2))) ;

            str = cutifandinsert(exp,ipos,fpos,(double)value) ;
            strcpy(exp,str) ;

            return str ;
        }
    }


/// factorial thing
    for(i=0 ; exp[i] ; i++)
    {
        if(i>strlen(exp) && strlen(exp)==1) break ;
        str = removespaces(exp) ;;
        strcpy(exp,str) ;
        int count ;
        int ipos = 0 ;  ///Initial position for the number to find factorial.
        int fpos = 0 ;
        int isittrue=0 ;
        if(exp[i]=='!')
        {
            fpos = i ;
            count = i -1;

            for(i=count;i>=0 ; i--)
            {
                if(checkifoperator(exp,i))
                {
                    isittrue = 1 ;  /// It specifies if it found an operator before the number ! begins
                    ipos=i+1 ;
                    break ;
                }
            }

            if(isittrue ==0) ipos = 0 ; /// This means that number factorial is written at the begginning of exp
            int k =0 ;

            char mynumber[1000]={'\0'};
            for(i=ipos,k=0 ; i<=count ; k++,i++)
            {
                mynumber[k] = exp[i] ;
            }
            int numi ;
            float num = atof(mynumber) ;
            if(num != (int)num)
                initialcheck("fact",1) ;
            else
                numi = (int)num ;
            unsigned long long fact =1 ;
            for(i=numi ; i>=1 ; i--)
            {
                fact*=i ;
            }
            double value = (double)fact ;

            str = cutifandinsert(exp,ipos,fpos,value) ;
            strcpy(exp,str) ;
            i = ipos ;

            return str ;
        }

    }


for(i=0  ; exp[i] ; i++)
{
    if(exp[i] == '^')
    {
        int ipos = ipos_fpos_find(exp,1,i) ;
        int fpos = ipos_fpos_find(exp,2,i) ;
        double value1 = binaryoperation(exp,1,i);
        double value2 = binaryoperation(exp,2,i) ;

        long double value =(long double) pow(value1,value2) ;

        str = cutifandinsert(exp,ipos,fpos,(long double)value) ;
        strcpy(exp,str) ;

        return str ;
    }
}

///SIN
for(i=0 ; i<strlen(exp)-1 ; i++)
{
    if(i>strlen(exp) && strlen(exp)==1) break ;
    if(exp[i]=='s' && exp[i+1]=='i')
    {
        int ipos= i ;
        int fpos =ipos_fpos_find(str,2,i) ;
        double value = trig(str,ipos,fpos,"sin") ;
        str = cutifandinsert(exp,ipos,fpos,value) ;
        strcpy(exp,str) ;

        return str ;
    }
}
///tan
for(i=0 ; i<strlen(exp)-1 ; i++)
{
    if(i>strlen(exp) && strlen(exp)==1) break ;
    if(exp[i]=='t' && exp[i+1]=='a')
    {
        int ipos= i ;
        int fpos =ipos_fpos_find(str,2,i) ;
        double value = trig(str,ipos,fpos,"tan") ;
        str = cutifandinsert(exp,ipos,fpos,value) ;
        strcpy(exp,str) ;
        return str  ;
    }
}

i =0 ;
/// Cosec
for(i=0 ; i<(strlen(exp)-3) ;i++)
{
    if(i>strlen(exp) || strlen(exp)==1) break ;
    if(exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='s' && exp[i+3]=='e')
    {
        int ipos= i ;
        int fpos =ipos_fpos_find(str,2,i) ;
        double value = trig(str,ipos,fpos,"cosec") ;
        str = cutifandinsert(exp,ipos,fpos,value) ;
        strcpy(exp,str) ;
        return str  ;
    }
}

///SEC

for(i=0 ; i<strlen(exp)-1 ; i++)
{
    if(i>strlen(exp) && strlen(exp)==1) break ;
    if(exp[i]=='s' && exp[i+1]=='e')
    {
        int ipos= i ;
        int fpos =ipos_fpos_find(str,2,i) ;
        double value = trig(str,ipos,fpos,"sec") ;
        str = cutifandinsert(exp,ipos,fpos,value) ;
        strcpy(exp,str) ;
        if(!bracefound) fileoutput(exp) ;
    }
}


/// Cot
for(i=0 ; i<strlen(exp)-2 ; i++)
{
    if(i>strlen(exp) && strlen(exp)==1) break ;
    if(exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='t')
    {
        int ipos= i ;
        int fpos =ipos_fpos_find(str,2,i) ;
        double value = trig(str,ipos,fpos,"cot") ;
        str = cutifandinsert(exp,ipos,fpos,value) ;
        strcpy(exp,str) ;
        return str  ;
    }
}

///Cos
for(i=0 ; i<strlen(exp)-2 ; i++)
{
    if(i>strlen(exp) && strlen(exp)==1) break ;
    if(exp[i]=='c' && exp[i+1]=='o' && exp[i+2]=='s')
    {
        int ipos= i ;
        int fpos =ipos_fpos_find(str,2,i) ;
        double value = trig(str,ipos,fpos,"cos") ;
        str = cutifandinsert(exp,ipos,fpos,value) ;
        strcpy(exp,str) ;
        return str  ;
    }
}

      /// Product and Quotient
    for(i=0 ;exp[i] ; i++)
    {
        if(i>strlen(exp) && strlen(exp)==1) break ;

        if(exp[i]=='*')
        {
            str = removespaces(exp) ;
            strcpy(exp,str) ;
            int ipos = ipos_fpos_find(exp,1,i) ;
            int fpos = ipos_fpos_find(exp,2,i) ;

            double value1 = binaryoperation(exp,1,i);
            double value2 = binaryoperation(exp,2,i);
            str = cutifandinsert(exp,ipos,fpos ,(value1*value2) ) ;
            strcpy(exp,str) ;
            return str  ;
        }
        else if(exp[i]=='/')
        {
            str = removespaces(exp) ;
            strcpy(exp,str) ;
            int ipos = ipos_fpos_find(exp,1,i) ;
            int fpos = ipos_fpos_find(exp,2,i) ;
            double value1 = binaryoperation(exp,1,i);
            double value2 = binaryoperation(exp,2,i);
            str = cutifandinsert(exp,ipos,fpos ,(value1/value2) ) ;
            strcpy(exp,str) ;
            return str  ;
        }

    }

        ///Addition and Subtraction
    for(i=1 ; exp[i];i++ )
    {
        if(i>strlen(exp) && strlen(exp)==1) break ;
        str = removespaces(exp) ;
        strcpy(exp,str) ;
        if(exp[i]=='+' || exp[i]=='-')
        {
            int ipos = ipos_fpos_find(exp,1,i);
            int fpos = ipos_fpos_find(exp,2,i) ;

            double value1 = binaryoperation(exp,1,i);
            double value2 = binaryoperation(exp,2,i);
            if(((value1+value2)>0) && ipos>0) exp[ipos-1] = '+' ;
            str = cutifandinsert(exp,ipos,fpos ,(value1+value2) ) ;
            strcpy(exp,str) ;

            return str ;
        }
    }

    return str ;
}


double binaryoperation(char *exp,int returnvalue , int index)
{
            int decimalindex = 0 ;
            int ipos = ipos_fpos_find(exp,1,index) ;
            int fpos = ipos_fpos_find(exp,2,index) ;
            double value1 ;
            double value2 ;
            char myvalue1[100] ;
            int k =0 ;
            int j =0 ;
            int pointindex1=0 ;
            int pointindex2=0 ;
            char myvalue2[100] ;

            if(exp[index]=='+' || exp[index]=='-')
            {
                if(ipos>0) ipos = ipos-1 ;

                for(j=ipos ,k=0; j<index ; k++,j++)
                {
                    myvalue1[k] = exp[j] ;
                }

                for(j=index ,k=0 ; j<=fpos ; j++ ,k++)
                {
                    if(((checkifoperator(exp,j) || exp[j]=='\0')) && j!=index)
                    {
                        fpos = j ;
                        break ;
                    }

                    myvalue2[k] = exp[j] ;
                }
                myvalue2[k]='\0' ;
            }

            else
            {

                for(j=ipos ,k = 0 ; j<index ; k++,j++)
                {
                    myvalue1[k]=exp[j] ;
                }
                myvalue1[k] = '\0' ;

                for(j=index+1 ,k=0 ; j<=fpos ; j++,k++)
                {
                    if(checkifoperator(exp,j) || exp[j]=='\0')
                    {
                        fpos = j ;
                        break ;
                    }
                    else
                    {
                        myvalue2[k] = exp[j] ;
                    }
                }
                myvalue2[k] = '\0';
            }


            value1 = atof(myvalue1) ;
            value2 = atof(myvalue2) ;

            if(returnvalue == 1) return value1 ;
            else if (returnvalue == 2) return value2 ;
}




int ipos_fpos_find(char *str ,int returnvalue , int index)    /// This finds the ipos and fpos of numbers like 5+4 ipos of 5 and fpos of 4
{
    ///  THE INDEX should be a index of a binary operator
    /// Put returnvalue = 1 to return the ipos or put returnvalue = 2 to return fpos
    int count = 0 ,i=0 ,ipos =0 , fpos = 0 ;
    if(returnvalue==1)
    {
        for(i=index-1 ;i>=0 ; i--)
        {
            if(i==0)
            {
                ipos = 0 ;
                break ;
            }
            if(checkifoperator(str,i) && str[i]!='.')
               {
                    ipos =i+1 ;
                    break;
               }
        }
        return ipos ;
    }
    if(returnvalue==2)
    {
        for(i=index+1  ;str[i]; i++)
        {
            if(checkifoperator(str,i) && str[i]!='.')
            {
                fpos = i-1 ;
                break ;
            }
            else if(i==strlen(str)-1)
                fpos = i ;
        }
        return fpos ;
    }
}



void input(void)
{
    /// THIS FUNCTION JUST TAKES THE INPUT STRING OF THE EXPRESSION FROM THE USER
    system("clear") ;
    system("tput setaf 12");
    system("figlet -f future \"            Welcome to THE CALCULATOR  SIMULATOR !!!\" -w 200\n\n");
    system("tput setaf 11") ;
    printf("1.Execute the Program");
    printf("\n2.Rules");
    printf("\n3.Example expressions ") ;
    printf("\n4.Credits ") ;
    printf("\n5.Program Code ") ;
    printf("\n6.Set the precision for the result : ") ;
    printf("\n7.Exit\n\n\n");
    printf("ENTER CHOICE : ") ;

    char str[size] ;int i ;
    fgets(str,size,stdin);
    str[strlen(str)-1]='\0';

    for(i = 0 ; i<strlen(str) ; i++)
    {
        if(str[i]>'A' && str[i]<'Z') str[i]=str[i]+32 ;
    }

    if(!strcmp(str,"7") || !strcmp(str,"exit"))
    {
        char thz[] = "\n\nThank you for using the program";
        for(i=0 ; thz[i] ; i++)
        {
            putchar(thz[i]) ;
            usleep(55000) ;
        }
        exit(0) ;
    }

    else if(strcmp(str,"1")==0)
    {
        printf("Enter your EXPRESSION : ") ;
        system("tput setaf 10");
        fgets(str,size,stdin) ;
        str[strlen(str)-1]='\0';
        for(i = 0 ; i<strlen(str) ; i++)
        {
            if(str[i]>'A' && str[i]<'Z') str[i]=str[i]+32 ;
        }

        initialcheck(str,0) ;
        logicbegin(str) ;
    }

    else if(strcmp(str,"2")==0)
    {
        system("tput setaf 14") ;
        printf("\n\n\nRULE ZERO : JUST BECAUSE I HAVE WRITTEN SOME RULES , DOESNT MEAN YOU HAVE TO FOLLOW THEM \n\n");
        printf("\n1. User has to Enter an Expression which is mathematically valid ! Writing poems and Gibberish isn't allowed \n! You should know that this is a Math program.\n\n");
        printf("2. There should be a finite value for the expression entered . Even a supercomputer cannot handle Infinity \u221E . How can a PC with a CPU inside the monitor at SIT handle it ? %c \n\n",236,1) ;
        printf("3. Maximum Precision is 10 digits. Otherwise the results look untidy and confusing.\n\n") ;
        printf("4. If the program is giving the wrong answers , then please give your calculator for repairing.\n\n") ;
        printf("5. And dont give huge numbers for factorials . Max is 10 for a factorial.\n\n") ;
        printf("6. Program is limitless for the number of terms involved in the expression . So throw something which even the MATH TEACHER can't handle.LOL\n\n") ;
        printf("7. That's all (or is it ? )\n\n",1) ;
        printf("Press <Enter> key to continue : " ) ;getchar() ;
        input() ;
    }

    else if(strcmp(str,"6")==0)
    {
        system("tput setaf 10") ;
        int pre ;
        printf("\n\nEnter the required precision. Max is 10 : ") ;
        scanf("%d",&pre) ;
        if(pre%10==0) pre=10 ;
        else ( pre=(pre%10) ) ;
        printf("\n\nPrecision set as : %d",pre) ;
        globalprecision = pre ;
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress <Enter> key to continue") ;
        getchar() ;
        getchar() ;
        main() ;
    }
    else if (strcmp(str,"3")==0)
    {
        system("clear") ;
        system("tput setaf 7") ;
        char mystr[10000]="\n\
10*4*4*4-4*4*4+5*4-43-100\n\
\n\
2*3-sin(85) * 25 /5p3 + 7c2 - 275 * 5! -5!\n\
\n\
2*3-cot(85) / 23 + 7c2 - 275*tan(40) - 512 - 2000\n\
\n\
6! - 7! *1/22 * 3 * 4 * 5 - 8 + 55 - sin(30)\n\
\n\
640.000 - 64.000 + 20.000 - 43 - 100\n\
\n\
3 + 5 + 10 *2 + 4 + 5p5 + 5c5 + 6 /2\n\
\n\
5 - 10 + 50 * 3 * 3 - 24 -100 - 1000 + 5p5 - 5! + 25\n\
\n\
-5 + - 5.000 + 426.000 - 100 - 1000\n\
\n\
-10.000 + 426.000 - 100 - 1000\n\
\n\
5/5+24*3p3/5p5-25+66+42+67\n\
\n\
0+2309*239+32*(3+23*2.23+234.23)\n\
\n\
sin83-sin20+ 382 /32.234/32.230 - 8*3 - (32.234-23.23*(10.0*20)+0.238)\n\
\n\
4*4-(5p5 + 3250 - 1000 ) - (500 + 500 - 200 - 5p5 + 5!) + 100 + 200  - 100 * 0.43 - 324.343 - 10.4233\n\
\n\
4*4-(5p5 + 3250 - 1000 ) - (500 + 500 - 200 - 5p5 + 5!)\n\
\n\
sin234 - cos(23490)^9.234 + 9p2 *6p2 * 100 - 8! - 10234.24232 * tan(43.2234)\n\
\n\
(3^4)+(4*(4^2)-(4*3+(3+2)^2))\n\
\n\
(3^4)*(4+(4*2)-(4*8)^3)*7+78\n\
\n\
5+ 5 - 10 - 200 + 5p2 + 6c3 + (555*5-4.34/2) + (4.554-23*43/34.32423)+88\n\
\n\
tan(45) + 50000 - (0 * 1000 + (4 - 5p5 )* 100 - 2000) * 4.3424 - 2342.234234 *0.00034 + cot(32) + sin(90) - cot34 * 3p2 + 7c2\n\
\n\
10+(3.234+329+(32.234-0.234*(32.234)))\n\
\n\
10000\n\
\n\
sin99\n\
\n\
SIN(99)\n\
"  ;

        printf("%s",mystr) ;
        printf("\n\n\nPress <Enter> key to continue : ") ;
        getchar() ;
        main() ;
    }

    else if(strcmp(str,"4")==0)
    {
        char credits[] = "\n\n\
1.  Author    : Natesh Bhat\n\n\
2.  Motivator : Bhargavi mam\n\n\
SPECIAL THANKS TO BHARGAVI MAM WHO MADE THIS PROJECT POSSIBLE AND PROVIDED US A PLATFORM AND GAVE US A REASON TO LEARN SO MANY CONCEPTS OUTSIDE THE SYLLABUS \n\n\
3.  Editor    : Codeblocks IDE v10.05\n\n\
4.  Debugger  : GNU GCC debugger\n\n\
5.  Compiler  : GNU GCC compiler\n\n\
6.  Concepts used : Strings , Pointers , arrays , functions , variables (ofcourse!) , file I/O and Some tweaks of my own\n\n\n\
Thanks for using the program if u haven't directly skipped to the credits section :) (If so , thanks for watching the credits ! \u263A )" ;
        int i;

        system("tput setaf 11") ;
        system("figlet \"          Credits\" -f mono9 -w 200");
        system("tput setaf 10") ;

        for(i=0 ; credits[i] ; i++)
        {
            putchar(credits[i]) ;
            usleep(60000) ;  // NOT WORKING !!!
        }
        printf("\n\n\n\nPress <Enter> key to continue : " ) ;getchar() ;
        input() ;
    }

    else if(!strcmp(str,"5"))
    {
        system("tput setaf 14") ;
        FILE *cf ;
        cf=fopen("main.c","r") ;
        for( ; !feof(cf) ;)
        {

            printf("%c",fgetc(cf)) ;
            usleep(500) ;
        }
        printf("\n\n\nPress <Enter> key to continue : ") ;getchar() ;
        input() ;
    }
    else main() ;

}


char* cutifandinsert(char *str ,int ipos , int fpos , double value)
{
    /// If ipos and fpos are equal , the function removes only that charecter;
    int i = 0,j=0 ,k=0 ; char *p ;
    char mystr[1000]={'\0'} ;
    strcpy(mystr,str) ;

    char* myvalue = floattostring(value,globalprecision) ;

    for(i=ipos , k =0 ; myvalue[k] ; k++,i++)
    {
        mystr[i] = myvalue[k] ;
    }
    for(i=ipos , k=fpos+1 ;i<strlen(str)+100;i++,k++)
    {
        mystr[i+strlen(myvalue)]=str[k] ;
    }
    str = mystr ;
    return str;
}



char* floattostring(double value,int precision)
{
    int i ;
    char a[1000]={'\0'};
    char format[20] ;
    sprintf(format,"%%.%df",precision,value) ;
    sprintf(a,format,value) ;

  //  long int b = (long int)((float)(value*pow(10,precision))) ;
  //  sprintf(a,"%.%sf",b/pow(10,precision)); int n =strlen(a) ;
    for(i=0 ; i<strlen(a);i++)
    {
        if(a[i]=='.')
            {
                int dot=i ;
                break ;
            }
    }
    a[i+precision+1]='\0' ;
    char *str = a ;
    return str;
}




bool checkifoperator(char *str,int i) /// returns true if the expression contains invalid operators
{
    if(str[i] < 48  || (str[i]>57 && str[i]<65)|| (str[i]>90 && str[i]<97) || str[i]>122)
    {
        if(str[i]=='.')
        {
            return false ;
        }
        else
        return true ;
    }
    else return false ;
}



void mailsend()
{
    char mystring[2500] ;
        FILE* myfile ;
        myfile = fopen("mailer.py","w") ;
        sprintf(mystring,"\n\
import smtplib\n\
import getpass\n\
with open(\"mail.txt\",\"r\") as f :\n\
    message=f.read();\n\
message=\"\"\"Subject:\"Caculator\"\n\n\"\"\"+message\n\
try:\n\
    sobj=smtplib.SMTP(\"smtp.gmail.com\",25)\n\
    sobj.starttls()\n\
    sobj.login(\"nateshmbhat1@gmail.com\",getpass.getpass(\"Enter Natesh's gmail password : \")) \n\
    sobj.sendmail(\"nateshmbhat1@gmail.com\",raw_input(\"Enter recepient mail address : \"),message)\n\
    print(\"Mail sent successfully ! \")\n\
except:\n\
    print(\"Internet connection Error ! Check network connection !\")\n\
    ") ;
        fprintf(myfile,mystring) ;
        fclose(myfile) ;
        system("python mailer.py") ;
        system("rm mailer.py") ;
        system("rm mail.txt") ;
}


int initialcheck(char *str,int k)  /// Returns 1 if the string contains operators at the beginning or end and
                             /// if number is divided by zero
{
    char a[size] ;
    strcpy(a,str) ;
    /// K specifies the error codes which corresponds to different errors that the user made.
    str = plus_minus_solve(str) ;
    int i ;
    for(i=strlen(a)-1 ; a[i]==' ' || a[i]==0 ; i--)
    {
        a[i]=0 ;
    }

    if(k==1) /// Error code 1 for factorial error
    {
        printf("\n\aINVALID EXPRESSION ! Factorial of numbers can only be found for integers not decimal numbers.\n\nPress <Enter> key to restart the program :");
        getchar() ;main() ;
    }

    if(k==2)  ///Error code 2 for permutation expression error
    {
        printf("\n\aINVALID EXPRESSION because of wrong usage of permutation expression.\n\nPress <Enter> key to restart the program :");
        getchar() ;main() ;
    }
    if(k==3)  /// Error code 3 for combination expression error
    {
        printf("\n\aINVALID EXPRESSION because of wrong usage of combination expression.\n\nPress <Enter> key to restart the program :");
        getchar() ;main() ;
    }
    if(k==4)  /// Trignometric expression error
    {
        printf("\n\aINVALID Trignometric Expression ! Nothing can handle infinity \u221E . \n\nPress <Enter> key to restart the program :",236) ;
        getchar() ; main() ;
    }

    if(checkifoperator(a,0) && a[0]!='-' && a[0]!='(')
    {
        printf("\n\aEnter a valid expression. Expression should not start with an operator ! \n\nPress <Enter> key to restart the program : ");
        getchar() ; main() ;
    }

    if(checkifoperator(a,strlen(a)-1) && a[strlen(a)-1]!=')' && a[strlen(a)-1]!='!')
    {
        printf("\n\aEnter a valid expression. Expression should not end with an operator ! It doesn't make sense.\n\nPress <Enter> key to restart the program : ");
        getchar() ; main() ;
    }

    for(i=1 ; i<strlen(a); i++)
        {
            if(a[i]=='0' && a[i-1]=='/')
            {
                printf("\n\aEnter a valid expression ! How can i divide something by 0 I say !\n\n\n\n\nPress <Enter> key to restart the program : ") ;
                getchar() ; main() ;
            }
        }
    strcpy(str,a) ;
    return 0 ;
}


int bracecheck(char str[size],int pos)
{
 /**   Returns
    if pos = 0
    -1 = braces found
    -2 = invalid braceusage
    -3 = braces not found
    if pos 1 return ipos
    if pos 2 return fpos*/

    int myref =1 ;
    int i=0  ;
    int ipos = 0 ;
    int fpos = 0 ;

    for(i=0 ; str[i] ; i++)
    {
        if(str[i]=='(')
            ipos = i ;
    }
    for(i=ipos+1 ; str[i] ; i++)
    {
        if(str[i]==')')
        {
            fpos=i ;
            break;
        }
    }

    if(ipos>0 && fpos==0 && pos==0)
    {
        return -2 ; ///Wrong brace usage
    }

    else if(fpos!=0 && pos==0) return -1 ; ///Found braces
    else if(fpos==0 && ipos ==0 && pos==0) return -3 ; /// Dindt find braces


    else if(pos==1)
    {
        return ipos ;
    }
    else if (pos==2)
        return fpos ;

}
