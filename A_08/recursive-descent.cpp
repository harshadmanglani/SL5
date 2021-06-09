#include <iostream>
using namespace std;

// E -> iE'
// E'-> +iE'| null

void E();
void EDash();
void match(char);
char l;
int main()
{
    // E is a start symbol.
    E();
 
    // if lookahead = $, it represents the end of the string
    // Here l is lookahead.
    if (l == '$')
        printf("Parsing Successful");
    return 0;
}
 
// Definition of E, as per the given production
void E()
{
    l = getchar();
    if (l == 'i') {
        match('i');
        EDash();
    }
    else
    {
        cout<<"Error";
        exit(0);
    }
}
 
// Definition of EDash as per the given production
void EDash()  
{
    if (l == '+') {
        match('+');
        match('i');
        EDash();
    }
    else
        return;
}
 
// Match function
void match(char t)
{
    if (l == t) {
        l = getchar();
    }
    else
    {
        printf("Error\n");
        exit(0);
    }
}