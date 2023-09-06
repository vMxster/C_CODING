/**
Fibonacci's eggs problem

A large basket contains eggs. The number of eggs enjoys the
following properties: if you count the eggs two to two, or three to
three, or four to four, or five to five, or six to
six, then at the end of the count there is one left. On the other hand, if you
count the eggs seven to seven, then at the end of the count there remains
none.

Write a program that calculates and prints the minimum integer value
n>0 that enjoys the previous properties.

**/
#include <stdio.h>

int main( void )
{
    /*
     * From the specification of the problem, we examine only the multiples of 7 to find the
     * smallest of them that enjoys the remaining properties
     */
    int n = 0, found = 0;
    do {
        n += 7;
        found = ((n%2 == 1) &&
                   (n%3 == 1) &&
                   (n%4 == 1) &&
                   (n%5 == 1) &&
                   (n%6 == 1));
    } while (!found);
    printf("%d\n", n);
    return 0;
}
