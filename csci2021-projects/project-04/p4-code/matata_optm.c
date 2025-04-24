// optimized versions of matrix A^T*A operation
#include "matvec.h"
#include <string.h>

int matata_VER1(matrix_t mat, matrix_t ans) {
  long rows = mat.rows;
  long cols = mat.cols;
  int *mdata = mat.data;
  int *adata = ans.data;
  long setter = rows * cols * 4;


  memset(adata, 0, setter); //setting answer matrix to 0

  int tikcalc;
  int mkjcalc;
  int datacalc;
  int k;
  for(int i=0; i<rows; i++){                
    for(int j=0; j<cols; j++){  
      tikcalc = i * cols + j;
      int tik = mdata[tikcalc]; //regular doesn't change with k                       
      for(k = 0; k<rows - 3; k+=3){ //unrolling
        mkjcalc = i * cols + k;
        datacalc = j * cols + k;
        int mkj = mdata[mkjcalc]; //traspose
        adata[datacalc] += tik * mkj;
        mkj = mdata[mkjcalc + 1]; //traspose + 1
        adata[datacalc + 1] += tik * mkj;
        mkj = mdata[mkjcalc + 2]; //traspose + 2
        adata[datacalc + 2] += tik * mkj;
      }
      for(; k < rows; k++){
        mkjcalc = i * cols + k;
        datacalc = j * cols + k;
        int mkj = mdata[mkjcalc]; //traspose
        adata[datacalc] += tik * mkj;
      }
    }
  }               
            
  return 0;
}

// ADDITIONAL VERSIONS HERE

int matata_OPTM(matrix_t mat, matrix_t ans) {
  if(mat.rows != mat.cols ||                    // must be a square matrix for A^T*A
     mat.rows != ans.rows ||
     mat.cols != ans.cols)
  {
    printf("matata_OPTM: dimension mismatch\n");
    return 1;
  }

  // Call to some version of optimized code
  return matata_VER1(mat, ans);
  // return matata_VER2(mat, ans);
}
