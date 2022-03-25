#include "../include/algo.h"

int doComputation(int a, float b){
   return a;
}

int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
}
