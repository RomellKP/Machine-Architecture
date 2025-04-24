// stock_funcs.c: support functions for the stock_main program.

#include "stock.h"

// PROBLEM 1: Allocate a new stock struct and initialize its fields.
// Integer fields like 'count' and 'lo_index' should be initialied to
// -1.  Pointer fields like 'prices' should be initialized to
// NULL. The stock should be heap-allocated using malloc() and
// returned.  Since this is an allocation function, no use of 'free()'
// should appear.
stock_t *stock_new(){
  // WRITE ME
  //sets all of the fields and allocates space
  stock_t *stock = malloc(sizeof(stock_t));
  stock->data_file = NULL;
  stock->count = -1;
  stock->prices = NULL;
  stock->lo_index = -1;
  stock->hi_index = -1;
  stock->best_buy = -1;
  stock->best_sell = -1;
  return stock;
}

// PROBLEM 1: Free a stock. Check the 'data_file' and 'prices' fields:
// if they are non-NULL, then free them. Then free the pointer to
// 'stock' itself.
void stock_free(stock_t *stock){
  // frees all of the fields of the stock
  if(stock->data_file != NULL){
    free(stock->data_file);
  }
  if(stock->prices != NULL){
    free(stock->prices);
  }
  free(stock);
  return;
}

// PROBLEM 1: Prints data about a stock that is passed in via a
// pointer. Uses the syntax ptr->field to access fields of the struct
// pointed by 'stock'.  Output follows the general convention:
//
// ==STOCK DATA==
// data_file: data/stock-jagged.txt                      
// count: 15
// prices: [103.00, 250.00, 133.00, ...]
// lo_index:  8
// hi_index:  11
// best_buy:  8
// best_sell: 11
// profit:    232.00
//
// Each line prints a field of the stock_t struct. In all cases,
// floating point numbers are printed with 2 decimal digits of
// accuracy.
//
// NULLS FOR FIELDS
// The fields 'data_file' and 'prices' may be NULL in which case they
// will be printed specially as in
// 
// data_file: NULL
// prices: NULL
//
// This requires a manual if/else check for NULL values for these
// pointers.
// 
// PRICES FIELD
// When printing the 'prices' field, if the 'count' field is 0 to 3,
// print the entire array as in
//
// prices: []                        # count == 0
// prices: [70.00]                   # count == 1
// prices: [50.00, 90.00]            # count == 2
// prices: [59.00, 45.00, 103.00]    # count == 3
//
// Otherwise, print the first 3 elements with a ... at the end as in
//
// prices: [10.00, 20.00, 30.00, ...] # count > 3
//
// PROFIT
// There is no 'profit' field in the struct. Instead, calculate the
// profit as the difference between the price at the 'best_sell' index
// and 'best_buy' index.  If these indices are -1 indicating the best
// buy/sell time is not known or not viable, print a proit of 0.0
void stock_print(stock_t *stock){
  // prints the inofrmation about the stock
  double profit;
  if(stock->best_buy == -1 || stock->best_sell == -1){
    profit = 0.00;
  }
  else{
    profit = stock->prices[stock->best_sell] - stock->prices[stock->best_buy];
  }
  printf("==STOCK DATA==\n");
  if(stock->data_file == NULL){
    printf("data_file: NULL\n");
  }
  else{
    printf("data_file: %s\n", stock->data_file);
  }
  printf("count: %d\n", stock->count);
  if(stock->prices == NULL){
    printf("prices: NULL\n");
  }
  else{
    printf("prices: [");
    for(int i = 1; i <= stock->count; i++){
      if(i == 4){
        printf("...");
        break;
      }
      else if(i == stock->count){
        printf("%.2f", stock->prices[i - 1]);
      }
      else{
        printf("%.2f, ", stock->prices[i - 1]);
      }
    }
    printf("]\n");
  }
  printf("lo_index: %d\n", stock->lo_index);
  printf("hi_index: %d\n", stock->hi_index);
  printf("best_buy: %d\n", stock->best_buy);
  printf("best_sell:  %d\n", stock->best_sell);
  printf("profit: %.2f\n", profit);
  return;
}


// PROBLEM 1: Sets the index of 'lo_index' and 'hi_index' fields of
// the stock to be the positions in 'prices' of the lowest and highest
// values present in it. Uses a simple loop over the array 'prices'
// which is 'count' elements long to examine each for high/low. If
// 'count' is zero, makes no changes to 'make helplo_index' and 'hi_index'.
void stock_set_hilo(stock_t *stock){
  // sets the highest and lowest
  double highest = 0;
  double lowest = 10000000;
  //sets highest
  for(int i = 0; i < stock->count; i++){
    if(highest < stock->prices[i]){
      stock->hi_index = i;
      highest = stock->prices[i];
    }
  }
  //sets lowest
  for(int i = 0; i < stock->count; i++){
    if(lowest > stock->prices[i]){
      stock->lo_index = i;
      lowest = stock->prices[i];
    }
  }
  return;
}
  
// PROBLEM 2: Sets the 'best_buy' and 'best_sell' fields of 'stock'.
// This corresponds to the pair which produces the best profit. On
// determining the best buy/sell indices which produce a positive
// profit, sets these fields in 'stock' and returns 0. If there is no
// buy/sell point which would result in a positive profit, sets the
// 'best_buy' and 'best_sell' indices to -1 and returns -1. Always
// calculates the earliest buy/sell pair of indices that would get the
// best profit: if 5,8 and 5,9 and 7,10 all give the same, maximal
// profit, the best buy/sell indices are set to 5,7.
// 
// ALGORITHM NOTES
// One intuitive algorithm to compute this is to try every possible
// buy index (outer loop) and every possible sell index after it
// (inner loop) looking for the maximum profit produced in it. This is
// a O(N^2) algorithm with N=count.  Using this algorithm is a good
// start. Some MAKEUP CREDIT will be awarded for implementing a more
// efficient, O(N) algorithm here. See the specification for more details.
int stock_set_best(stock_t *stock){
  // calculates the best stock
  stock->best_buy = -1;
  stock->best_sell = -1;
  double best_profit = 0.0;
  double curr_profit = 0.0;
  //calculates the best profit
  for(int i = 0; i < stock->count; i++){
    for(int j = i+1; j < stock->count; j++){
      curr_profit = stock->prices[j] - stock->prices[i];
      if(curr_profit > best_profit){
        stock->best_buy = i;
        stock->best_sell = j;
        best_profit = curr_profit;
      }
    }
  }
  //sets best buy and sell to -1 if the best profit is <= 0
  if(best_profit <= 0.0){
    stock->best_buy = -1;
    stock->best_sell = -1;
    return -1;
  }
  else{
    return 0;
  }
}

// PROBLEM 2: Opens file named 'filename' and counts how many times
// the '\n' newline character appears in it which corresponds to how
// many lines of text are in it.  Makes use of either fscanf() with
// the %c format to read single characters or alternative I/O
// functions like fgetc(). Closes the file before returning a count of
// how many lines are it it.  If for any reason the file cannot be
// opened, prints a message like
//
// Could not open file 'not-there.txt'
//
// and returns -1 to indicate failure.
int count_lines(char *filename){
  // counts the lines of the given file
  int newline_counter = 0;
  FILE *stock_file;
  char c;
  stock_file = fopen(filename, "r");
  //if unable to open prints an error
  if(stock_file == NULL){
    printf("Could not open file \'%s\'\n", filename);
    return -1;
  }
  //iterates through the file and counts the lines
  for(c = getc(stock_file); c != EOF; c = getc(stock_file)){
    if(c == '\n'){
      newline_counter++;
    }
  }
  fclose(stock_file);
  return newline_counter;
}
// PROBLEM 2: Loads a stock from file 'filename' into 'stock' filling
// its 'prices' and 'count' fields in. Makes use of the count_lines()
// function to determine how many lines are in the file which will
// dictate 'count' and the length of 'prices'. Allocates space in the
// heap for the stock's 'prices' array, opens the 'filename' and
// iterates through reading prices into the array. The data format for
// prices files is
//
// time_03 133.00
// time_04 143.00
// time_05 168.00
// time_06 91.00t
// 
// where each line has a time as as single string and a price which is
// floating point number. The times can be ignored which can be
// accomplished with a fscanf() call with format "%*s" to read a
// string but ignore/discard it.
// 
// Assigns the 'datafile' field to be a duplicated string of
// 'filename' for which 'strdup()' is extremely useful. This string
// must be free()'d later likely in 'stock_free()'
// 
// On successfully loading the stock, returns 0.
//
// If 'filename' cannot be opened, prints the message 
// 
// Unable to open stock file 'some-stock.txt', bailing out
//
// with 'filename' substituted in for the name of the stock and
// returns -1.
int stock_load(stock_t *stock, char *filename){
  //opens file and and fills in fields
  stock->count = count_lines(filename);
  FILE *stock_file;
  stock_file = fopen(filename, "r");
  //if unable to open prints an error
  if(stock->count == -1){
    if(stock_file == NULL){
      printf("Unable to open stock file \'%s\', bailing out\n", filename);
      return -1;
   }
  }
  //sets fields
  double *price_array = malloc(stock->count * sizeof(double));
  for(int i = 0; i < stock->count; i++){
    fscanf(stock_file, "%*s %lf", &price_array[i]);

  }
  stock->data_file = strdup(filename);
  stock->prices = price_array;
  fclose(stock_file);
  return 0;
}

// PROBLEM 2: Plots a graphical representation of stock
// information. First calculates and prints plot which is in the
// following format:
//
// ==PLOT DATA==
// start/stop:  0 15
// max_height:  14
// price range: 309.00
// plot step:   22.07
//            +--B=S----------+
//     300.93 |    H   *      |
//     278.86 | *  H   *      |
//     256.79 | *  H   *      |
//     234.71 | *  H   *      |
//     212.64 |**  H   *      |
//     190.57 |**  H * *      |
//     168.50 |**  H** *  *  *|
//     146.43 |**  H** *  ****|
//     124.36 |**  H****  ****|
//     102.29 |**  H****  ****|
//      80.21 |** *H***** ****|
//      58.14 |** *H***** ****|
//      36.07 |** *H***** ****|
//      14.00 |****H*****L****|
//            +^----^----^----+
//             0    5    10   
// 
// Here brief notes on the format with more detail in the project
// specification.
// - Parameters start, stop, and max_height are printed first along with
//   calculated information like the price_range (uses hi_index and
//   lo_index)
// - The main body of the plot is exactly max_height characters high. The
//   lowest line is the price at lo_index; the highest is hi_index minus
//   plot_step
// - The vertical axis prices can be printed with the format specifier
//   %10.2f to give the correct leading whitespace with 2 digits of
//   accuracy
// - If the hi and lo prices appear in the range, their bar is printed
//   with an H or an L while all other stocks are printed with a *
// - The top axis may include a B and an S at the positions of the
//   best_buy and best_sell index with a = between these to show the
//   period of ownership.
// - The bottom axis shows tic marks as ^ and below them index labels at
//   values divisible by 5. For the numeric index labels, it is easiest
//   to print spaces to a value divisible by 5 then use the format
//   specifier %-5d to print integers: this aligns left and prints
//   whitespace padding on the right to width 5. In a loop, one can
//   advance by +5 each time a label is printed.
void stock_plot(stock_t *stock, int max_height, int start, int stop){
  // prints the stocks data
  printf("==PLOT DATA==\n");
  printf("start/stop: %d %d\n", start, stop);
  printf("max_height: %d\n", max_height);
  double price_range = stock->prices[stock->hi_index] - stock->prices[stock->lo_index];
  printf("price range: %.2f\n", price_range);
  double plot_step = price_range / max_height;
  printf("plot step: %.2f\n", plot_step);
  double stepper;
  int check_bs = 0;
  for(int i = 0; i < max_height + 3; i++){
    //prints the first line
    if(i == 0){
      printf("           ");
      for(int j = start; j < stop + 2; j++){
        if((stock->best_buy - start) * (stock->best_buy - stop) > 0 && j < stock->best_sell + 1 && (stock->best_sell - start) * (stock->best_sell - stop) <= 0){
          check_bs = 1;
        }
        if(j == start || j == stop + 1){
          printf("+");
          if(j == stop + 1){
            printf("\n");
          }
        }
        else if(j == stock->best_buy + 1){
          printf("B");
          check_bs = 1;
        }
        else if(j == stock->best_sell + 1){
          printf("S");
          check_bs = 0;
        }
        else if(check_bs == 1){
          printf("=");
        }
        else{
          printf("-");
        }
      }
    }
    //prints second to last line
    else if(i == (max_height + 1)){
      printf("           ");
      for(int j = start; j < stop + 2; j++){
        if(j == start || j == stop + 1){
          printf("+");
          if(j == stop + 1){
            printf("\n");
          }
        }
        else if(j % 5 == 1){
          printf("^");
        }
        else{
          printf("-");
        }
      }

    }
    //prints last line
    else if(i == (max_height + 2)){
      printf("           ");
      for(int j = start; j < stop + 2; j++){
        if(j % 5 == 1 && j != stop + 1){
          printf("%d", j - 1);
        }
        else{
          printf(" ");
        }
      }
    }
    //prints all of the middle lines
    else{
      stepper = price_range + stock->prices[stock->lo_index] - (plot_step * (double) (i));
      printf("%10.2f ", stepper);
      for(int j = start; j < stop + 2; j++){
        if(j == start || j == stop + 1){
          printf("|");
          if(j == stop + 1){
            printf("\n");
          }
        }
        else if(j == stock->hi_index + 1 && stock->prices[stock->hi_index] >= stepper){
          printf("H");
        }
        else if(j == stock->lo_index + 1 && stock->prices[stock->lo_index] >= stepper){
          printf("L");         
        }

        else if(stock->prices[j-1] >= stepper){
          printf("*");
        }
        else{
          printf(" ");
        }
      }
    }

  }

  return;
}
  
