#include "utilities.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool debug1 = true;
bool debug2 = false;
bool debug3 = false;
bool debug4 = false;

int main(int argc, char* argv[])
{
 
   new_object(Int, a, 1);
   resize(a, 100);
   /*forall(100){
       a[x] = x;
       P("%d\n", a[x]);
   }*/
   clear(a);
   clear(a);
   clear(a);
   if(a == NULL) {
       P("Wee\n");
   }
   else P("Oh no\n");
   new_object(Int*, b, 1);
   int* c = calloc(123, sizeof(int));
   *c = 13;
   clear(c);
   clear(b);
   clear(b);
   if(c == NULL)P("Wee\n");
   // ("%d\n", *d);
   // ("%d\n", *d);
   // ("%p\n", c);
   //clear_real((void* )&b)
   //clear(c);
   //clear(c);
   //clear(d);
   //clear(d);
   //clear(c);
   void* dd = NULL;
   Int e = dd;

   return 0;
}
