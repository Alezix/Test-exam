#include <stdio.h>
#include <math.h>

// Set total dimension
const int N= 50;

// Generates next Fibonacchi number, starting at zero
unsigned long getNextFibonacci( void )
{
  static unsigned long prv= 0;
  static unsigned long cur= 0;
  static char  initialized= 0;

  unsigned long next= 0;

  // Initialize two first elements of Fibonacchi numbers
  if( !initialized ) {
    if( cur ) {
      initialized= 1;
      next=        1;
    }
    cur= 1;
  }
  else {
    next= prv + cur;
    prv=  cur;
    cur=  next;
  }

  return next;
}

// Check the number is prime
// (2, 3, 4, 5, 6, 7, 8, 9, 10 numbers are already checked,
// so we start with 11).
int checkPrime( unsigned long n )
{
  unsigned long max= (unsigned long) ( sqrt( n ) + 1);

  for( unsigned long i= 11; i< max; i++ ) {
    // Check odd numbers only
    if( i & 0x1 )
      if( !(n % i) ) return 0;
  }

  return 1;
}

//===========================================================================
int main( void )
{
  int n= 1;

  while( 1 ) {
    unsigned long num= getNextFibonacci();

    // Printing next number
    printf("Next (%2i): %lu", n-1, num );

    // Special cases (all numbers in the range 1-3 are prime)
    if( num < 4 ) {
      printf( num ? " BuzzFizz\r\n" : "\r\n");
    }
    else {
      enum {
        divider_ZERO=  0x0,
        divider_THREE= 0x1,
        divider_FIVE=  0x2,
        divider_BOTH=  0x3
      };

      int divider= divider_ZERO;

      // Check only odd numbers
      if( num & 0x1 ) {
        // Check "3" as divider
        if( !(num % 3) ) {
          divider|= divider_THREE;
          printf(" Buzz" );
        }

        // Check "5" as divider
        if( !(num % 5) ) {
          divider|= divider_FIVE;
          printf(" Fizz" );
        }

        // Check "15" as divider
        if( (divider & divider_BOTH) == divider_BOTH ) {
          printf(" FizzBuzz" );
        }

        // Check prime number
        if( !divider ) {
          if( (num % 7) && checkPrime( num ) )
            printf(" BuzzFizz" );
        }
      }
      // Go to the next number
      printf("\r\n");
    }

    if( ++n > N+1 ) break;
  }

  return 0;
}