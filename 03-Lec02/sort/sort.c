//quick sort recursive 递归方法
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

void insertion_sort(int arr[], int len){ //插入排序
    // printf("Begin insertion_sort！\n");
    for (int i = 1; i < len; i++)
    {
        // printA(arr,len);
        int num = arr[i];

        /*while 版本*/
        int j = i-1;
        while(j>=0 && arr[j]>num)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = num;
        
    }       
    // printf("Insertion_sort done！\n"); 
}

void Paritition(int arr[], int low, int high) //快速排序 - 主体 / 递归+挖坑法
{
    if (low>=high)
    {
        return;
    }
    int left = low, right = high;
    int pivot = arr[left];
    while (left!=right)
    {
        while(left<right && arr[right]>=pivot) //等于pivot的情况放在两个中任意一个都可以 \
                                                但不要两个都取等号
        {                                   
            right--;
        }
        if(left<right)
        {
            arr[left]=arr[right];
            left++; //因为原本left的位置已经放了一个注定>=pivot的值
        }
        while (left<right && arr[left]<pivot)
        {
            left++;
        }
        if(left<right)
        {
            arr[right]=arr[left];
            right--;
        }
    }
    arr[left]=pivot;
    Paritition(arr,low,left-1);
    Paritition(arr,left+1,high);
}

void Paritition_O1(int arr[], int low, int high) //快速排序 + 小序列优化 / 递归+挖坑法
{
    if (low>=high)
    {
        return;
    }
    if(high-low<=10)  //小序列优化 : 当需要排序的元素个数很少时，插入排序比快速排序效率更高
    {
        insertion_sort(arr+low,high-low+1);
        return;
    }
    else
    {
        int left = low, right = high;
        int pivot = arr[left];
        while (left!=right)
        {
            while(left<right && arr[right]>=pivot) 
            {                                   
                right--;
            }
            if(left<right)
            {
                arr[left]=arr[right];
                left++;
            }
            while (left<right && arr[left]<pivot)
            {
                left++;
            }
            if(left<right)
            {
                arr[right]=arr[left];
                right--;
            }
        }
        arr[left]=pivot;
        Paritition_O1(arr,low,left-1);
        Paritition_O1(arr,left+1,high);
    }   
}

void quick_sort(int arr[],int len) //快速排序 接口
{
    Paritition(arr,0,len-1);
}   

void quick_sort_O1(int arr[],int len) //快速排序 接口
{
    Paritition_O1(arr,0,len-1);
}   

void arrcpy(int dest[],int res[],int start,int end) // 归并排序 工具函数
{
    for(int i = start; i<=end; i++)
    {
        dest[i] = res[i];
    }
}

void merge_sort_recursive(int arr[],int tmp[],int start,int end)  // 归并排序 递归 
{
    if(start>=end)
        return;
    int len = end-start;
    int mid = (len/2) + start;
    int start1 = start, end1 = mid;
    int start2 = mid+1, end2 = end;

    merge_sort_recursive(arr,tmp,start1,end1);
    merge_sort_recursive(arr,tmp,start2,end2);
    
    int p = start;
    while(start1 <= end1 && start2 <= end2)
        tmp[p++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while(start1 <= end1)
        tmp[p++] = arr[start1++];
    while(start2 <= end2)
        tmp[p++] = arr[start2++];

    arrcpy(arr,tmp,start,end);
}

void merge_sort(int arr[],int len) // 归并排序 递归 接口
{
    int* tmp = (int*)calloc(len,sizeof(int));
    merge_sort_recursive(arr,tmp,0,len-1);
    free(tmp);
}

void merge_sort_i(int Arr[],int len) // 归并排序 迭代
{
    #define MIN(x,y) x<y?x:y
    int *arr = Arr;
    int *tmp = (int*)calloc(len,sizeof(int)); 
    int seg, start;
    int *temp_swap;
    for(seg = 1; seg < len; seg += seg)
    {
        for(start = 0; start < len;start += seg*2)
        {
            int start1 = start;
            int end1 = MIN(start+seg,len); 
            int start2 = end1;
            int end2 = MIN(end1+seg,len);
            int p = start;
            while(start1<end1 && start2<end2)
                tmp[p++] = arr[start1]<arr[start2]? arr[start1++]:arr[start2++];
            while(start1<end1)
                tmp[p++] = arr[start1++];
            while(start2<end2)
                tmp[p++] = arr[start2++];
        }
        temp_swap = arr;
        arr = tmp;
        tmp = temp_swap;
    }
    if (arr != Arr)
    {
        for(int i = 0; i < len; i++)
            Arr[i]=arr[i];
        tmp = arr;
    }
    #undef MIN
    free(tmp);
}


typedef void (*sort_fun_p)(int* ,int);
#define checkround 10
#define len 1000000
#define range_of_array len*2

/*检查排序算法正确性，同时输出排序计算时间*/
void check(sort_fun_p sort_fun_p)
{
    char error = 0;
    long Time = 0;
    int batchcount = 1;
    for(int i = 0;i<checkround;i++){
        // printf("%d/%d ",batchcount++,checkround);
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
            printA(arr_copy,len);
            printA(arr,len);
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
    sort_fun_p q_sort = & quick_sort;
    sort_fun_p i_sort = & insertion_sort;
    sort_fun_p q_sort_O1 = & quick_sort_O1;
    sort_fun_p m_sort = & merge_sort;
    sort_fun_p m_sort_i = & merge_sort_i;

    printf("  Batch:  %d \
              Length of array : %d\n",checkround,len);

    printf("m_r: ");
    check(m_sort);  

    printf("m_i: ");
    check(m_sort_i);  

    printf("q: ");
    check(q_sort);  

    printf("qO1: ");
    check(q_sort_O1);  

    // printf("i: ");
    // check(i_sort);  

    return 0;
}

