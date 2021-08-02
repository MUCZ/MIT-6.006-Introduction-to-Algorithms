#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>


long GetSysTime() // 用于计算算法运行时间
{
	struct timeb time;
	ftime(&time);
	return time.time * 1000 + time.millitm;;
}

void printA(int arr[],int len) // 显示数组用于调试
{
    printf("A:{");
    for (int i = 0; i < len; i++)
    {
        printf(" %d",arr[i]);
    }
    printf("}\n");
}


void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify_r(int *heap,int i,int len ) 
{
    int l = (i+1)*2-1;
    int r = (i+1)*2;
    int largest = i;
    if(l<len && heap[l] > heap[i])
        largest = l;
    else
        largest = i;
    if(r<len && heap[r] > heap[largest])
        largest = r;
    if(largest!=i)
    {
        swap(&heap[i],&heap[largest]);
        max_heapify_r(heap,largest,len);
    }
}   

void max_heapify_i(int* heap, int i, int len)
{
    int largest,left,right;
    while (1)
    {
        left = (i+1)*2-1;
        right = (i+1)*2;
        if(left<len && heap[left]>heap[i])
            largest = left;
        else
            largest = i;
        if(right<len && heap[right]>heap[largest])
            largest = right;
        swap(&heap[i],&heap[largest]);
        if(largest > len/2-1 || largest == i)
            return;
        i = largest;
    }       
}

void build_max_heap(int *heap ,int len) 
{ 
    for(int i = len/2 ; i >= 1; i--)
        max_heapify_r(heap,i-1,len); 
}

void heap_sort_r(int *heap,int len)  //堆排序 迭代
{
    for(int i = len/2 ; i >= 1; i--) //build_max_heap(heap,len);
        max_heapify_r(heap,i-1,len); 
    while(len>0)
    {
        swap(&heap[0],&heap[--len]);
        max_heapify_r(heap,0,len);
    }
}

void heap_sort_i(int *heap,int len)  //堆排序 递归
{
    // build_max_heap(heap,len);
    for(int i = len/2 ; i >= 1; i--)
        max_heapify_i(heap,i-1,len); 
    while(len>0)
    {
        swap(&heap[0],&heap[--len]);
        max_heapify_i(heap,0,len);
    }
}

void heap_append(int* heap,int num,int* len)
{
    (*len)+=1;
    int *temp= realloc(heap,(*len)*sizeof(int));
    heap[(*len)-1] = num;
    int p = *len;
    while(p>1)
    {
        p = (p)/2;
        max_heapify_i(heap,p-1,(*len));
    }
} 

int heap_pop(int *heap,int* len)
{
    int val = heap[0];
    swap(&heap[0],&heap[(*len)-1]);
    (*len)--;
    max_heapify_i(heap,0,*len);
    return val;
}

typedef void (*sort_fun_p)(int* ,int); // 指向排序算法的函数指针 注意参数列表 如果排序函数不对应 需要设计接口函数
/*检查排序算法正确性，同时输出排序计算时间*/
void check(sort_fun_p sort_fun_p)
{
    #define checkround 20    // 测试轮数，多次测试取平均值，减少随机因素影响
    #define len 200000     // 单论测试中的待排序数组长度，数组数据随机生成 
    #define range_of_array len*2  // 待排序数组的数据的随机生成的范围 
    char error = 0;
    long Time = 0;
    int batchcount = 1;
    for(int i = 0;i<checkround;i++){
        printf(".");
        fflush(stdout);
        int *arr = (int*)calloc(len,sizeof(int));
        int *arr_copy = (int*)calloc(len,sizeof(int));
        long sum_after=0,sum_before=0;
        //initialization 
        for (int j = 0; j < len; j++)
        {
            arr[j]=rand()%range_of_array;
            arr_copy[j]=arr[j]; //to show when error happens
            sum_before+=arr[j]; //checksum
        }

        //sort 
        long start = GetSysTime();
        sort_fun_p(arr,len);
        long end = GetSysTime();

        //order check
        for (int i = 0; i < len-1; i++)
        {
            if(arr[i] > arr[i+1])
            {
                error = 1;
                break;
            }
        }

        //sumcheck 
        if (error!=1)
        {
            for (int j = 0; j < len; j++)
            {
                sum_after+=arr[j];
            }
            if(sum_after!=sum_before)
                error = 2;
        }

        //error handle
        if(error != 0)
        {
            char err_des[100];
            if(error==2)
                strcpy(err_des,"sum error!");
            else    
                strcpy(err_des,"order error!");
            printf("Found non-sorted list! error :%s \n",err_des);
            if (len<=10)
            {
                printA(arr_copy,len);
                printA(arr,len);
            }
            exit(1);
        }
        Time+=end-start;
        free(arr);
        free(arr_copy);
    }
    printf("\n平均每次排序耗费时间%f毫秒\n",(float)Time/checkround);
    return;
}

int main(){
    printf("  Batch:  %d \
              Length of array : %d\n",checkround,len);
              
    // 堆排序测试
    printf("h_r: "); 
    check(&heap_sort_r);  
    printf("h_i: "); 
    check(&heap_sort_i);  

    // 堆测试
    int l = 5;
    int *A = (int*)calloc(l,sizeof(int));
    for(int i = 1 ; i<=l ;i++)
        A[i-1]=i;
    printA(A,l);
    build_max_heap(A,l);
    printA(A,l);
    heap_append(A,l+1,&l);
    printA(A,l);
    int a = heap_pop(A,&l);
    printA(A,l);
    printf("a : %d",a);

    return 0;
}
