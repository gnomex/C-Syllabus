#include <stdio.h>
#include <stdbool.h>

int posix_reader(char *str)  {
  int number;

  printf("Digit the %s: ", str);
  fflush(stdout); //wait for the prompt to be written on the screen
  scanf("%d",&number);

  return number;
}

bool verify_leap_years(int year) {
  bool leap = false;

  if ( year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0)) ) {
    leap = true;
  }

  return leap;
  // if (leap == true) {
  //   printf("%i: Yeap, it is a leap year!", year);
  // } else {
  //   printf("%i: This year is not a leap!", year);
  // }
}

int verify_valid_date(int day, int month, int year)  {
  bool leap = verify_leap_years(year);

  int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (month > 12){ printf("The month %i is invalid\n", month); return -1; }

  int month_at_index = days_in_month[month - 1];

  if ( (leap == true) && (month == 2) && (day <= month_at_index + 1))  {
    printf("%i: Yeap, it is a leap year!\n", year);
  }

  if ( !(leap == true) && day <= month_at_index)  {
    printf("%i: This year is not a leap, but the date is valid.\n", year);
    return 0;
  } else  {
    printf("The day %i is invalid\n", day);
  }

  printf("Please, enter a valid date!");
  return 0;
}


int main()
{
  int day;
  int month;
  int year;

  day = posix_reader("day");
  month = posix_reader("month");
  year = posix_reader("year");

  verify_valid_date(day, month, year);

  return 0;
}
