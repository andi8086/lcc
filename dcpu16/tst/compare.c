#include <dcpulib.h>

int main() {
    int i, j;
    
    i = 2; j = 1;
    printf("2 > 1?    %s ", (i > j)?"y":"n");
    printf("1 > 2? %s\n",   (j > i)?"y":"n");

    i = 1; j = 0;
    printf("1 > 0?    %s ", (i > j)?"y":"n");
    printf("0 > 1? %s\n",   (j > i)?"y":"n");

    i = 1; j = -1;
    printf("1 > -1?   %s ", (i > j)?"y":"n");
    printf("-1 > 1? %s\n",  (j > i)?"y":"n");

    i = 0; j = -1;
    printf("0 > -1?   %s ", (i > j)?"y":"n");
    printf("-1 > 0? %s\n",  (j > i)?"y":"n");

    i = -1; j = -2;
    printf("-1 > -2?  %s ", (i > j)?"y":"n");
    printf("-2 > -1? %s\n", (j > i)?"y":"n");

    i = 0; j = 0;
    printf("0 > 0? %s ", (i > j)?"y":"n");
    i = 1; j = 1;
    printf("1 > 1? %s ", (i > j)?"y":"n");
    i = -1; j = -1;
    printf("-1 > -1? %s\n", (i > j)?"y":"n");


    i = 2; j = 1;
    printf("2 >= 1?    %s ", (i >= j)?"y":"n");
    printf("1 >= 2? %s\n",   (j >= i)?"y":"n");

    i = 1; j = 0;
    printf("1 >= 0?    %s ", (i >= j)?"y":"n");
    printf("0 >= 1? %s\n",   (j >= i)?"y":"n");

    i = 1; j = -1;
    printf("1 >= -1?   %s ", (i >= j)?"y":"n");
    printf("-1 >= 1? %s\n",  (j >= i)?"y":"n");

    i = 0; j = -1;
    printf("0 >= -1?   %s ", (i >= j)?"y":"n");
    printf("-1 >= 0? %s\n",  (j >= i)?"y":"n");

    i = -1; j = -2;
    printf("-1 >= -2?  %s ", (i >= j)?"y":"n");
    printf("-2 >= -1? %s\n", (j >= i)?"y":"n");

    i = 0; j = 0;
    printf("0 >= 0? %s ", (i >= j)?"y":"n");
    i = 1; j = 1;
    printf("1 >= 1? %s ", (i >= j)?"y":"n");
    i = -1; j = -1;
    printf("-1 >= -1? %s\n", (i >= j)?"y":"n");


    i = 2; j = 1;
    printf("2 < 1?    %s ", (i < j)?"y":"n");
    printf("1 < 2? %s\n",   (j < i)?"y":"n");

    i = 1; j = 0;
    printf("1 < 0?    %s ", (i < j)?"y":"n");
    printf("0 < 1? %s\n",   (j < i)?"y":"n");

    i = 1; j = -1;
    printf("1 < -1?   %s ", (i < j)?"y":"n");
    printf("-1 < 1? %s\n",  (j < i)?"y":"n");

    i = 0; j = -1;
    printf("0 < -1?   %s ", (i < j)?"y":"n");
    printf("-1 < 0? %s\n",  (j < i)?"y":"n");

    i = -1; j = -2;
    printf("-1 < -2?  %s ", (i < j)?"y":"n");
    printf("-2 < -1? %s\n", (j < i)?"y":"n");

    i = 0; j = 0;
    printf("0 < 0? %s ", (i < j)?"y":"n");
    i = 1; j = 1;
    printf("1 < 1? %s ", (i < j)?"y":"n");
    i = -1; j = -1;
    printf("-1 < -1? %s\n", (i < j)?"y":"n");


    i = 2; j = 1;
    printf("2 <= 1?    %s ", (i <= j)?"y":"n");
    printf("1 <= 2? %s\n",   (j <= i)?"y":"n");

    i = 1; j = 0;
    printf("1 <= 0?    %s ", (i <= j)?"y":"n");
    printf("0 <= 1? %s\n",   (j <= i)?"y":"n");

    i = 1; j = -1;
    printf("1 <= -1?   %s ", (i <= j)?"y":"n");
    printf("-1 <= 1? %s\n",  (j <= i)?"y":"n");

    i = 0; j = -1;
    printf("0 <= -1?   %s ", (i <= j)?"y":"n");
    printf("-1 <= 0? %s\n",  (j <= i)?"y":"n");

    i = -1; j = -2;
    printf("-1 <= -2?  %s ", (i <= j)?"y":"n");
    printf("-2 <= -1? %s\n", (j <= i)?"y":"n");

    i = 0; j = 0;
    printf("0 <= 0? %s ", (i <= j)?"y":"n");
    i = 1; j = 1;
    printf("1 <= 1? %s ", (i <= j)?"y":"n");
    i = -1; j = -1;
    printf("-1 <= -1? %s\n", (i <= j)?"y":"n");
}
