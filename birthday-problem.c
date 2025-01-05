#include <stdio.h>
#include <math.h>

/*

UUID Collision Chance
------------------------------------

The likelihood that there is at least one collision for UUIDs can be understood
with what's typically called the birthday problem story.
Counterintuitively, it only takes 23 people to have a roughly equal chance of there being
a 50% chance of at least two people having the same birthday in the room.
If we increase the number of options from 365 to whatever the number of alternatives for UUIDs are
then we can use similar mathematics to work out the likelihood of UUID and hash function collisions
which have real world consequences for software systems.

The chance of at least one collision for birthdays can be calculated by calculating the chance that
there are no collisions and then convert that to the chance of one of more collisions by converting
it to one minus that amount.

P(no collisions) = 0/365 * 1/365 * 2/365 * ... one term per person
P(one of more collisions) = 1 - P(no collisions)



Reality can be split into parallel dimensions :) where there is a collision
and where there is no collision (C or NC).

             Reality
                |
          ┌─────┴─────┐
          │           │
          C           NC
       ┌──┴──┐     ┌──┴──┐
       │     │     │     │
       C     NC    C     NC
    ┌──┴──┐ ┌─┴─┐ ┌─┴─┐ ┌─┴─┐
    │     │ │   │ │   │ │   │
    C    NC C  NC C  NC C  NC


The first bifurcation has a 0/100 chance of a collision C and a 100/100 chance of no collision (NC).
Then there's a 1/100 chance of a collision and a 99/100 chance of no collision.
Then it's C = 2/100 and NC = 98/100 and so on.

For universal unique identifiers we're interested in the chance that there is at least one collision throughout all time.
This can be conveniently calculated by finding the chance of having absolutely no collisions which is the route taken
on the right hand side of the graph choosing all NC options.

To calculate it multiply 100/100 * 99/100 * 98/100 and so on with one term per insertion.


“You know nothing of future time,” pronounced Deep Thought, “and yet in my teeming circuitry I can navigate infinite delta streams of future probability and see that there must one day come a computer whose merest operational parameters I am not worthy to calculate, but which it will be my eventual fate to design.” - Douglas Adams

*/

	       
	     
int birthday_problem_start(double N)
{
  // double N = 20;
  double i = 0;
  double p = 1;

  // The probability that N random numbers are different is the following.  
  for(i=0;i<N;i+=1){
    p = p * (365-i)/365;
  }
  // So the probability that there is at least one collision is 1-p
  printf("Probability that there is at least one collision is: %f\n",1-p);
  return 0;
}

double birthday_problem(double num_alternatives, double num_random_items)
{
  double i = 0;
  double p = 1;

  // The probability that N random items.  
  for(i=0;i<num_random_items;i+=1){
    p = p * (num_alternatives-i)/num_alternatives;
  }
  // So the probability that there is at least one collision is 1-p
  return 1-p;
}

double birthday_problem_approximation(double na, double nri) // num_alternatives, double num_random_items)
{
  double i = 0;
  double p = 1;

  // Approximations
  // e^x ~= 1 + x
  // e^(-a/365)  ~= 1 - a/365  so when a = 1, 1-a/365 = 365/365 - 1/365 = 364/365
  // so 364/365 * 363/365 * ... = exp(-1/365)*exp(-2/365) = exp((-1-2)/365) = exp(-3/365)

  /*  
  double sa = 0; // sum of a
  for(i=0;i<nri;i+=1){
    sa = sa + i;
  }
  */
  
  double sa = nri*nri/2 - nri/2; // n*n/2 - n/2

  p = exp(-sa / na);
  return 1-p;
}




int main()
{
  double p,i;

  /*
  p = 0;
  p = birthday_problem_start(20);


  */
  /*
  p = birthday_problem(365, 23);
  printf("%f %f\n", 23., p); // people, chance of at least one collision.
  */

  /*
  double na, nri; // num_alternatives, num_random_items;

  na = pow(2,64);
  nri = pow(2,32);
  
  printf("%f %f\n", na, nri);
  p = birthday_problem(na, nri);
  printf("%f %f\n", i, p); // items, chance of at least one collision.
  */
  /*
  p = birthday_problem_approximation(365, 23);
  printf("%f %f\n", 23., p); // people, chance of at least one collision.
  */


  for(i=0;i<50;i+=1){
    double bp = birthday_problem(365, i);
    double bpa = birthday_problem_approximation(365, i);
    printf("%f %f %f %f\n", i, bp, bpa, bp-bpa);
  }

  
  double na = pow(2,64);
  double nri = pow(2,32);  
  double bpa = birthday_problem_approximation(na, nri);
  printf("%f %f %f\n", na, nri, bpa);


  na = pow(2,128);
  nri = pow(2,63);
  bpa = birthday_problem_approximation(na, nri);
  printf("%f %f %f\n", na, nri, bpa);

  // if the number of random items is 2^(possibilities/2) or higher the probability of collisions quickly goes to 1

  // The number of items must remain below the square root of the number of possibilities or alternatives

  // For a 128 bit UUID there are 2^128 alternatives.  The number of items must remain under (2^128)^(1/2) = 2^64 items
  // for there to be an acceptable chance of collisions.  It's a ceiling on the number of items really.



  return 0;
}
