Projects for Machine Architecture:

Project 1: 

  Description: Two seprate implementations: a hashmap and stock class. Implemented following hashmap functions for operating on hashmaps: _init,
  _put, _get, _free_table, _show_structure, _write_items, _save, _load, next_prime, and _expand. Implemented the following functions to use and 
  display stock data found in the data folder: stock_print, stock_new, stock_free, stock_set_hilo, stock_set_best, count_lines, stock_load, and
  stock_plot.

  Run and Compile: For hashmap problem compile and run hashmap_main.c and for stock problem compile and run stock_main.c. From there, follow 
  directions in terminal and type out commands. 

  My Contributions: hashmap_funcs.c, stock_funcs.c

Project 3:

  Description:Implemented a thermo display controller that reads temperature sensor data and updates a digital display. Optimized for embedded
  systems as it uses minimal CPU and memory footprint. This is achieved through integer operations no dynamic memory allocation. Implemented the
  following funtions: thermo_update, set_temp_from_ports, and set_display_from_temp.

  Run and Compile: Run and compile thermo_main.c. From there, follow directions in terminal and type out commands.

  My Contributions: thermo_update.c

Project 4:

  Description:Two seprate implementations: search algorithms and matrices and vectors. The first implements multiple search algorithms including
  arrays, linked lists, and binary search trees. Implemented the following functions: linear_array_search, linked_list_search, bineary_array_search, 
  binary_tree_search, make_evens_array, make_evens_list, make_evens_tree, tree_merge, list_free, bst_free, and node_remove_all. The second provides 
  utilities for working with matrices and vectors. It includes memory allocating, performing basic operations on them, amd reading/writing them from/to
  files. implemented the following funtions: vector_init, matrix_init, vector_free_data, matrix_free_data, vector_read_from_file, matrix_read_from_file,
  vector_write, matrix_write, vector_fill_sequential, and matrix_fill_sequential.

  Run and Compile: For search algorithms problem compile and run search_benchmark.c and for matrices and vectors problem compile and run matata_print.c and matata_benchmark.c. 
  From there, follow directions in terminal and type out commands.

  My Contributions: matvec_util.c and search_funcs.c

Project 5:

  Description:Implemented an explicit list memory allocator. Provides a malloc/free memory manager and uses an explicit free list to manage available 
  memory blocks. Allocator supports splitting and merging of memory blocks for efficient heap utilization. Implemented the following functions: el_init,
  el_cleanup, el_get_footer, el_get_header, el_block_above, el_block_below, el_print_blocklist, el_print_block, el_print_stats, el_init_blobklist, 
  el_add_block_font, el_remove_back, el_find_first_avail, el_split_block, el_malloc, el_merge_block_with_above, el_free, and el_append_pages_to_heap.

+--------------------+  
| el_blockhead_t     |  (contains size, state, prev, next)
+--------------------+
| User Data Area     |
|  ...               |
+--------------------+
| el_blockfoot_t     |  (contains size)
+--------------------+  

  Run and Compile: Run and compile test_el_malloc.c

  My Contributions: el_malloc.c
