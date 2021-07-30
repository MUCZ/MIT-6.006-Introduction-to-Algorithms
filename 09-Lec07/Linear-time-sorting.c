#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* 计数排序的例程 */
/* 基数排序过于繁琐没有写 */

void print_arr(int *arr, int n) {
        int i;
        printf("%d", arr[0]);
        for (i = 1; i < n; i++)
                printf(" %d", arr[i]);
        printf("\n");
}

void counting_sort(int* arr, int len,int range)
{
    int* tmpp = (int*)calloc(range,sizeof(int)); // positive nums
    int* tmpn = (int*)calloc(range,sizeof(int)); // negative nums
    for(int i = 0, num = 0; i < len; i++)        // read arr
    {
        num = arr[i];
        num>=0? tmpp[num]++:tmpn[-num]++ ;
    }

    // 写回 arr
    int count = 0;          
    for(int i = range-1; i >= 0 && count < len; i--)
    {
        int k = tmpn[i];
        if( k == 0)
            continue;
        for(int j = 0; j < k ; j++)
        {
            arr[count++] = -i;
        }
    }
    for(int i = 0; i < range && count < len; i++)
    {
        int k = tmpp[i];
        if( k == 0)
            continue;
        for(int j = 0; j < k ; j++)
        {
            arr[count++] = i;
        }
    }
    free(tmpp);
    free(tmpn);

}

int main(int argc, char **argv) {
        int n = 10;
        int i;
        int range = 10;
        int *arr = (int *) malloc(sizeof(int) * n);
        int *sorted_arr = (int *) malloc(sizeof(int) * n);
        srand(time(0));
        for (i = 0; i < n; i++)
                arr[i] = rand() % range - range/2;

        printf("ini_array: ");
        print_arr(arr, n);

        counting_sort(arr,n,range);

        printf("sorted_array: ");
        print_arr(arr, n);

        free(arr);
        free(sorted_arr);
        printf("%d",RAND_MAX);
        return 0;
}
