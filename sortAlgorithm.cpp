#include<iostream>
using namespace std;

//1.交换排序_快速排序
void quickSort(int left, int right, int nums[]){
    if(left >= right) return;
    int i = left, j = right, base = nums[left], tmp;
    while (i < j)
    {   
        while (nums[j] >= base && i < j)
            j--;
        while (nums[i] <= base && i < j)
            i++;
        if(i < j){
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }        
    }
    nums[left] = nums[j];
    nums[j] = base;
    quickSort(left, j - 1, nums);
    quickSort(j + 1, right, nums);
}
//2.交换排序_冒泡排序
void bubbleSort(int size, int nums[]){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - 1 - i; j++){
            if(nums[j] > nums[j + 1]){
                int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}

//3.归并
void Merge(int left, int mid, int right, int nums[]){
    int i = left, j = mid + 1, k = 0;
    int *tmp = new int[right - left + 1];
    while (i <= mid && j <= right)
    {
        if(nums[i] <= nums[j]){
            tmp[k++] = nums[i++];
        }else{
            tmp[k++] = nums[j++];
        }
    }
    while (i <= mid)
    {
        tmp[k++] = nums[i++];
    }
    while (j <= right)
    {
        tmp[k++] = nums[j++];
    }
    for(int i = left, k = 0; i <= right; i++, k++){
        nums[i] = tmp[k];
    }
    delete []tmp;
}

//3.基于递归的归并排序（自顶向上）
void MergeSort1(int left, int right, int nums[]){
    if(left >= right) return;
    int mid = (right + left) / 2;
    MergeSort1(left, mid, nums);
    MergeSort1(mid + 1, right, nums);
    Merge(left, mid, right, nums);
}

//3.基于循环的归并排序（自底向上）
void MergeSort2(int size, int nums[]){
    for(int i = 1; i < size; i *= 2){
        for(int low = 0; low + i < size; low += 2 * i){
            int mid = low + i - 1;
            int high = low + 2 * size - 1;
            if(high > size - 1)
                high = size - 1;
            Merge(low, mid, high, nums);
        }
    }
}

//4.插入排序_直接插入排序
void InsertionSort(int size, int nums[]){
    for(int i = 1; i < size; ++i){
        int val = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > val)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = val;
    }
}

//5.插入排序_希尔排序
void ShellSort(int size, int nums[]){
    int d, tmp, j;
    d = size / 2;
    while (d > 0)
    {
        for(int i = d; i < size; ++i){
            tmp = nums[i];
            j = i - d;
            while (j >= 0 && tmp <nums[j])
            {
                nums[j + d] = nums[j];
                j = j - d;
            }
            nums[j + d] = tmp;
        }
        d = d / 2;  //缩小增量
    }
}

//6.选择排序
void SelectSort(int n, int size, int nums[]){
    for(int i = 0; i < size; ++i){
        int index = i;
        for(int j = i + 1; j < size; j++)
            if(nums[j] < nums[index])
                index = j;
        int tmp = nums[index];
        nums[index] = nums[i];
        nums[i] = tmp;
    }
    cout << endl;
}

//7.堆排序
//构造大顶堆
void maxHeap(int n, int size, int nums[]){
    int left, right, maxV;
    left = 2 * n;
    right = 2 * n + 1;
    if(left <= size && nums[left - 1] > nums[n - 1])
        maxV = left;
    else
        maxV = n;
    if(right <= size && nums[right - 1] > nums[maxV - 1])
        maxV = right;
    if(maxV != n){
        swap(nums[n - 1], nums[maxV - 1]);
        maxHeap(maxV, size, nums);

    }
}

//构造大顶堆
void buildMaxHeap(int size, int nums[]){
    for(int i = size / 2; i > 0; i--)
        maxHeap(i, size, nums);
}

void HeapSort(int size, int nums[]){
    buildMaxHeap(size, nums);
    for(int i = size; i > 1; i--){
        swap(nums[0], nums[i - 1]);
        size--;
        maxHeap(1, size, nums);
    }
}

//数组显示
void printArr(int nums[], int size){
    for(int i = 0; i < size; ++i){
        cout << nums[i] << " ";
    }
    cout << endl;
}

int main(){
    int nums[] = {2,5,7,8,1,6,3,4,10,9};
    int size = sizeof(nums) / sizeof(nums[0]);
    printArr(nums, size);

    cout << "Sort result:" << endl;
    //quickSort(0, size - 1, nums);
    //bubbleSort(size, nums);
    //MergeSort1(0, size - 1, nums);
    //MergeSort2(size, nums);
    //InsertionSort(size, nums);
    //ShellSort(size, nums);
    //SelectSort(size, nums);
    HeapSort(size, nums);
    printArr(nums, size);
    return 0;
}