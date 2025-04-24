// hashmap_funcs.c: utility functions for operating on hash maps. Most
// functions are used in hash_main.c which provides an application to
// work with the functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"


long hashcode(char key[]){
  union {
    char str[8];
    long num;
  } strnum;
  strnum.num = 0;

  for(int i=0; i<8; i++){
    if(key[i] == '\0'){
      break;
    }
    strnum.str[i] = key[i];
  }
  return strnum.num;
  //already done for me
}

void hashmap_init(hashmap_t *hm, int table_size){
  hm->table_size = table_size;
  hm->item_count = 0;
  hm->table = malloc(sizeof(hashnode_t*) * table_size);
  for(int i = 0; i < table_size; i++){
    hm->table[i] = NULL;
  }
  //initializes inte_count, table_size, andsets items in table to null
}
// Initialize the hash map 'hm' to have given size and item_count
// 0. Ensures that the 'table' field is initialized to an array of
// size 'table_size' and filled with NULLs. 

int hashmap_put(hashmap_t *hm, char key[], char val[]){
  hashnode_t  *hashy = malloc(sizeof(hashnode_t)); // either a prblm w/ free or not every function in main thats needs to frees
  hashnode_t *ptr;
  strcpy(hashy->val, val);
  strcpy(hashy->key, key);
  int position = hashcode(key) % hm->table_size;
  ptr = hm->table[position];
  //if there isnt anythinhg in the position it adds the hashnode
  if(ptr == NULL){
    hm->table[position] = hashy;
    hashy -> next = NULL;
    hm -> item_count++;
    return 1;
  }
  //compares to all of the nodes and if it matches on it replaces the val with the new val
  int compare = 1;
  while(ptr != NULL){
    compare = strcmp(hashy->key, ptr->key);
    if(compare == 0){
      strcpy(ptr->val, hashy->val);
      return 0;
    }
    ptr = ptr->next;
  }
  //gets ptr to the end of the list
  hashy->next = NULL;
  while(ptr->next != NULL){
    ptr = ptr->next;
  }
  //adds if there is no comprable hashnode and adds to item count
  if(compare == 1){
    ptr->next = hashy;
    hm->item_count++;
  }

  return 1;
}
// Adds given key/val to the hash map. 'hashcode(key) modulo
// table_size' is used to calculate the position to insert the
// key/val.  Searches the entire list at the insertion location for
// the given key. If key is not present, a new node is added. If key
// is already present, the current value is altered in place to the
// given value "val" (no duplicate keys are every introduced).  If new
// nodes are added, increments field "item_count".  Makes use of
// standard string.h functions like strcmp() to compare strings and
// strcpy() to copy strings. Lists in the hash map are arbitrarily
// ordered (not sorted); new items are always appended to the end of
// the list.  Returns 1 if a new node is added (new key) and 0 if an
// existing key has its value modified.

char *hashmap_get(hashmap_t *hm, char key[]){
  long index = hashcode(key) % hm->table_size;
  hashnode_t *ptr;
  ptr = hm->table[index];
  int compare = 1;
  //goes through and compares the keys of each node in the table
  while(ptr != NULL){
    compare = strcmp(key, ptr->key);
    if(compare == 0){
      break;
    }
    ptr = ptr->next;
  }
  //returns null if there is not a same node in the table
  if(compare == 1){
    return NULL;
  }
  else{
    return ptr->val;
  }
}
// Looks up value associated with given key in the hashmap. Uses
// hashcode() and field "table_size" to determine which index in table
// to search.  Iterates through the list at that index using strcmp()
// to check for matching key. If found, returns a pointer to the
// associated value.  Otherwise returns NULL to indicate no associated
// key is present.

void hashmap_free_table(hashmap_t *hm){
  struct hashnode *ptr;
  struct hashnode *tmp;
  //goes through and frees each node individually with the pointers
  for(int i = 0; i < hm->table_size; i++){
    ptr = hm->table[i];
    while(ptr != NULL){
      tmp = ptr;
      ptr = ptr->next;
      free(tmp);
    }
  }
  //frees the table and resets the fields
  free(hm->table);
  hm->table_size = 0;
  hm->item_count = 0;
  hm->table = NULL;
}
// De-allocates the hashmap's "table" field. Iterates through the
// "table" array and its lists de-allocating all nodes present
// there. Subsequently de-allocates the "table" field and sets all
// fields to 0 / NULL. Does NOT attempt to free 'hm' as it may be
// stack allocated.

void hashmap_show_structure(hashmap_t *hm){
  double load_factor = hm->item_count;
  load_factor /= hm->table_size;
  //prints each of the fields
  printf("item_count: %d\n", hm->item_count);
  printf("teable_size: %d\n", hm->table_size);
  printf("load_factor: %.4f", load_factor);
  struct hashnode *ptr;
  //goes through the hashmap, gets the values and keys, and prints them out
  for(int i = 0; i < hm->table_size; i++){
    printf("%d : ", i);
    ptr = hm->table[i];
    while(ptr != NULL){
      printf("{(%ld) %s : %s}", hashcode(ptr->key), ptr->key, ptr->val);
      ptr = ptr->next;
    }
    printf("\n");
  }
}
// Displays detailed structure of the hash map. Shows stats for the
// hash map as below including the load factor (item count divided
// by table_size) to 4 digits of accuracy.  Then shows each table
// array index ("bucket") on its own line with the linked list of
// key/value pairs on the same line. The hash code for keys is appears
// prior to each key.  EXAMPLE:
// 
// item_count: 6
// table_size: 5
// load_factor: 1.2000
//   0 : {(65) A : 1} 
//   1 : 
//   2 : {(122) z : 3} {(26212) df : 6} 
//   3 : {(98) b : 2} {(25443) cc : 5} 
//   4 : {(74) J : 4} 
//
// NOTES:
// - Uses format specifier "%3d : " to print the table indices
// - Shows the following information for each key/val pair
//   {(25443) cc : 5}
//     |      |    |
//     |      |    +-> value
//     |      +-> key
//     +-> hashcode("cc"), print using format "%ld" for 64-bit longs

void hashmap_write_items(hashmap_t *hm, FILE *out){
  struct hashnode *ptr;
  //goes through the hashmap and writes each of the values onto a file
  for(int i = 0; i < hm->table_size; i++){
    ptr = hm->table[i];
    while(ptr != NULL){
      fprintf(out, "%12s : %s\n", ptr->key, ptr->val);
      ptr = ptr->next;
    }
  }
  return;

}
// Outputs all elements of the hash table according to the order they
// appear in "table". The format is
// 
//       Peach : 3.75
//      Banana : 0.89
//  Clementine : 2.95
// DragonFruit : 10.65
//       Apple : 2.25
// 
// with each key/val on a separate line. The format specifier
//   "%12s : %s\n"
// 
// is used to achieve the correct spacing. Output is done to the file
// stream 'out' which is standard out for printing to the screen or an
// open file stream for writing to a file as in hashmap_save().

void hashmap_save(hashmap_t *hm, char *filename){
  //opens a file, writes the size and count, and then call hashmap_write_items
  FILE *wFile;
  wFile = fopen(filename, "w");
  fprintf(wFile, "%d %d", hm->table_size, hm->item_count);
  hashmap_write_items(hm, wFile);
  return;

}
// Writes the given hash map to the given 'filename' so that it can be
// loaded later.  Opens the file and writes its 'table_size' and
// 'item_count' to the file. Then uses the hashmap_write_items()
// function to output all items in the hash map into the file.
// EXAMPLE FILE:
// 
// 5 6
//            A : 2
//            Z : 2
//            B : 3
//            R : 6
//           TI : 89
//            T : 7
// 
// First two numbers are the 'table_size' and 'item_count' field and
// remaining text are key/val pairs.

int hashmap_load(hashmap_t *hm, char *filename){
  FILE *filer;
  filer = fopen(filename, "r");
  //if cannot open file prints an error
  if(filer == NULL){
    printf("ERROR: could not open the file %s", filename);
    return 0;
  }
  //iterates through table
  else{
    //struct hashmap_t *newhash;
    struct hashnode *ptr;
    for(int i = 0; i < hm->table_size; i++){
      ptr = hm->table[i];
      while(ptr != NULL){
        ptr = ptr->next;
      }
    }
  }
  return 1;
}
// Loads a hash map file created with hashmap_save(). If the file
// cannot be opened, prints the message
// 
// ERROR: could not open file 'somefile.hm'
//
// and returns 0 without changing anything. Otherwise clears out the
// current hash map 'hm', initializes a new one based on the size
// present in the file, and adds all elements to the hash map. Returns
// 1 on successful loading. This function does no error checking of
// the contents of the file so if they are corrupted, it may cause an
// application to crash or loop infinitely.

int next_prime(int num){
  int is_prime = 0;
  int the_prime = num;
  //figures out if the number is a prime
  for(int i = 2; i < num / 2; i++){
    if(num % i == 0){
      is_prime = 1;
    }
  }
  //returns the number if it is a prime
  if(is_prime == 1){
    return num;
  }
  //finds the next prime up from that number
  while(is_prime == 0){
    the_prime++;
    for(int i = 2; i < the_prime / 2; i++){
      if(the_prime % i == 0){
        break;
      }
      if(i == num / 2 - 1 && num % i != 0){
        is_prime = 1;
      }
    }    
  }
  return the_prime;

}
// If 'num' is a prime number, returns 'num'. Otherwise, returns the
// first prime that is larger than 'num'. Uses a simple algorithm to
// calculate primeness: check if any number between 2 and (num/2)
// divide num. If none do, it is prime. If not, tries next odd number
// above num. Loops this approach until a prime number is located and
// returns this. Used to ensure that hash table_size stays prime which
// theoretically distributes elements better among the array indices
// of the table.

void hashmap_expand(hashmap_t *hm){
  hashmap_t new_map;
  hashnode_t *ptr;
  //sets the new map with a larger size
  hashmap_init(&new_map, next_prime(2 * hm->table_size + 1));
  //sets all indexies to NULL
  for(int i = 0; i < new_map.table_size; i++){
    new_map.table[i] = NULL;
  }
  //puts all of the values from the first table into the new table
  for(int i = 0; i < hm->table_size; i++){
    ptr = hm->table[i];
    while(ptr != NULL){
      hashmap_put(&new_map, ptr->key, ptr->val);
      ptr = ptr->next;
    }
  }
  //clears the old table
  hashmap_free_table(hm);
  //makes new table = old table
  *hm = new_map;
  return;
}
// Allocates a new, larger area of memory for the "table" field and
// re-adds all items currently in the hash table to it. The size of
// the new table is next_prime(2*table_size+1) which keeps the size
// prime.  After allocating the new table, all entries are initialized
// to NULL then the old table is iterated through and all items are
// added to the new table according to their hash code. The memory for
// the old table is de-allocated and the new table assigned to the
// hashmap fields "table" and "table_size".  This function increases
// "table_size" while keeping "item_count" the same thereby reducing
// the load of the hash table. Ensures that all memory associated with
// the old table is free()'d (linked nodes and array). Cleverly makes
// use of existing functions like hashmap_init(), hashmap_put(),
// and hashmap_free_table() to avoid re-writing algorithms
// implemented in those functions.for(int i = 0; i < ; i++){