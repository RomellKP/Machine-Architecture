// main function for a linked list manager, student version

#include <stdio.h>
#include <string.h>
#include "hashmap.h"

int main(int argc, char *argv[]){
  int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
  if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
    echo=1;
  }

    printf("Hashmap Main\n");
    printf("Commands:\n");
    printf("  hashcode <key>   : prints out the numeric hash code for the given key (does not change the hash map)\n");
    printf("  put <key> <val>  : inserts the given key/val into the hash map, overwrites existing values if present\n");
    printf("  get <key>        : prints the value associated with the given key or NOT FOUND\n");
    printf("  print            : shows contents of the hashmap ordered by how they appear in the table\n");
    printf("  structure        : prints detailed structure of the hash map\n");
    printf("  clear            : reinitializes hash map to be empty with default size\n");
    printf("  save <file>      : writes the contents of the hash map the given file\n");
    printf("  load <file>      : clears the current hash map and loads the one in the given file\n");
    printf("  next_prime <int> : if <int> is prime, prints it, otherwise finds the next prime and prints it\n");
    printf("  expand           : expands memory size of hashmap to reduce its load factor\n");
    printf("  quit             : exit the program\n");

  //declares the table, success, and command
  char cmd[128];
  hashmap_t thehash;
  int success;
  hashmap_init(&thehash, HASHMAP_DEFAULT_TABLE_SIZE);
  //command line for user inputs that echos back the user inputs
  while(1){
    printf("HM> ");                 // print prompt
    success = fscanf(stdin,"%s",cmd); // read a command
    if(success==EOF){                 // check for end of input
      printf("\n");                   // found end of input
      break;                          // break from loop
      //goes to a new line if the user has stopped inputting
    }
    if(strcmp("put", cmd) == 0){
      //calls the put function and puts the function in
      char val[100];
      char key[100];
      fscanf(stdin,"%s %s",key, val);
      if(echo){
        printf("put %s %s\n", key, val);
      }
      int res = hashmap_put(&thehash, key, val);
      //prints about overriting if put function overwrit one of the vals
      if(res == 0){
        printf("Overivting previous key/val\n");
      }
    }
    if(strcmp("get", cmd) == 0){
      //calls get function and tells user if founc
      char key[100];
      fscanf(stdin,"%s",key);
      if(echo){
        printf("get %s\n", key);
      }
      char *getter;
      getter = hashmap_get(&thehash, key);
      if(getter == NULL){
        printf("NOT FOUND\n");
      }
      else{
        printf("FOUND: %s\n", getter);
      }
    }
    if(strcmp("save", cmd) == 0){
      //calls save function
      char filename[100];
      fscanf(stdin,"%s", filename);
      hashmap_save(&thehash, filename);
      if(echo){
        printf("save %s\n", filename);
      }
    }
    if(strcmp("load", cmd) == 0){
      //calls load function
      char filename[100];
      fscanf(stdin,"%s",filename);
      hashmap_load(&thehash, filename);
      if(echo){
        printf("load %s\n", filename);
      }
    }
    if(strcmp("hashcode", cmd) == 0){
      //calls the hashcode function and prints the hashcode
      char key[100];
      fscanf(stdin,"%s",key);
      if(echo){
        printf("hashcode %s\n", key);
      }
      long code = hashcode(key);
      printf("%ld\n", code);
    }
    if(strcmp("next_prime", cmd) == 0){
      //calls next prime function and prints the next prime
      int prime;
      fscanf(stdin,"%d", &prime);
      if(echo){
        printf("next_prime %d\n", prime);
      }
      prime = next_prime(prime);
      printf("%d\n", prime);

    }
    if(strcmp("print", cmd) == 0){
      if(echo){
        printf("print\n");
      }
      hashnode_t *ptr;
      for(int i = 0; i < thehash.table_size; i++){
        ptr = thehash.table[i];
        while(ptr != NULL){
          printf("%12s : %s\n", ptr->key, ptr->val);
          ptr = ptr->next;
        }
      }
    }
    if(strcmp("clear", cmd) == 0){
      //calls free table function
      if(echo){
        printf("clear\n");
      }
      hashmap_free_table(&thehash);
    }
    if(strcmp("structure", cmd) == 0){
      //calls the hashmap_show_structure function
      if(echo){
        printf("structure\n");
      }
      hashmap_show_structure(&thehash);
      printf("structure\n");
    }
    if(strcmp("expand", cmd) == 0){
      //calls expand function to resize the table
      if(echo){
        printf("expand\n");
      }
      hashmap_expand(&thehash);
    }
    if( strcmp("quit", cmd)==0 ){     // check for exit command
    //breaks out of infinite command loop
      if(echo){
        printf("quit\n");
      }
      break;                          // break from loop
    }
  }
  hashmap_free_table(&thehash);
  //frees the hashtable
  return 0;
}