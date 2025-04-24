// Complete this main to benchmark the search algorithms outlined in
// the project specification
#include "search.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
  //sets min, max, reps, and initializes len, la, ll, bl, and bt
  int min = atoi(argv[1]);
  int max = atoi(argv[2]);
  int reps = atoi(argv[3]);
  int la = 0;
  int ll = 0;
  int ba = 0;
  int bt = 0;
  int len = 1;

  //loop for determining proper length
  for(int i = 0; i < min; i++){
    len *= 2;
  }

  if(argc == 4){
    la = 1;
    ll = 1;
    ba = 1;
    bt = 1;
  }
  else{
    for(int i = 4; i < argc; i++){
      if(strcmp(argv[i], "la") == 0){
       la = 1;
      }
      if(strcmp(argv[i], "ll") == 0){
        ll = 1;
      }
      if(strcmp(argv[i], "ba") == 0){
        ba = 1;
      }
      if(strcmp(argv[i], "bt") == 0){
        bt = 1;
      }
    }
  }
//prints header
  printf("  LENGTH SEARCHES");
  if(la == 1){ 
    printf("      array");
  }
  if(ll == 1){
    printf("       list");
  }
  if(ba == 1){
    printf("     binary");
  }
  if(bt == 1){
    printf("       tree");
  }
  printf("\n");

//makes timer, searches and clock
  int searches;
  clock_t begin;
  clock_t end;
  double la_timer;
  double ll_timer;
  double ba_timer;
  double bt_timer;

//loop for searching, timing and printing
  for(int i = min; i <= max; i++){
    la_timer = 0;
    ll_timer = 0;
    ba_timer = 0;
    bt_timer = 0;
//timing loop
    if(la == 1){
      int *larray;
      larray = make_evens_array(len);
      begin = clock();
      for(int k = 0; k < reps; k++){
        for(int j = 0; j < (2 * len) - 1; j++){
           linear_array_search(larray, len, j);
         }
      }
      end = clock();
      la_timer = ((double) (end - begin)) / CLOCKS_PER_SEC;
      free(larray);
    }
    if(ll == 1){
      list_t *llist;
      llist = make_evens_list(len);
      begin = clock();
      for(int k = 0; k < reps; k++){
        for(int j = 0; j < (2 * len) - 1; j++){
          linkedlist_search(llist, len, j);
        }
      }
      end = clock();
      ll_timer = ((double) (end - begin)) / CLOCKS_PER_SEC;
      list_free(llist);
    }
    if(ba == 1){
      int *barray;
      barray = make_evens_array(len);
      begin = clock();
      for(int k = 0; k < reps; k++){
        for(int j = 0; j < (2 * len) - 1; j++){
          binary_array_search(barray, len, j);
        }
      }
      end = clock();
      ba_timer = ((double) (end - begin)) / CLOCKS_PER_SEC;
      free(barray);
    }
    if(bt == 1){
      bst_t *btree;
      btree = make_evens_tree(len);
      begin = clock();
      for(int k = 0; k < reps; k++){
        for(int j = 0; j < (2 * len) - 1; j++){
          binary_tree_search(btree, len, j);
        }
      }
      end = clock();
      bt_timer = ((double) (end - begin)) / CLOCKS_PER_SEC;
      bst_free(btree);
    }
//prints the len, and # of searches
    len *= 2;
    searches = len * reps * 2;
    printf("%8d ", len);
    printf("%8d ", searches);
    if(la == 1){
      printf("%10.4e ",la_timer);
    }
    if(ll == 1){
      printf("%10.4e ",ll_timer);
    }
    if(ba == 1){
      printf("%10.4e ",ba_timer);
    }
    if(bt){
      printf("%10.4e ",bt_timer);
    }
    printf("\n");
  }

  return 0;
}
