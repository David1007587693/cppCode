#include<iostream>
using namespace std;

//快速排序
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
//冒泡排序
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

//基于递归的归并排序（自顶向上）
void MergeSort1(int left, int right, int nums[]){
    if(left >= right) return;
    int mid = (right + left) / 2;
    MergeSort1(left, mid, nums);
    MergeSort1(mid + 1, right, nums);
    Merge(left, mid, right, nums);
}

//基于循环的归并排序（自底向上）
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

//直接插入排序
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


//希尔排序



void printArr(int nums[], int size){
    for(int i = 0; i < size; ++i){
        cout << nums[i] << " ";
    }
    cout << endl;
}

int main(){
    int nums[] = {2,5,7,8,1,3,4,10,9};
    int size = sizeof(nums) / sizeof(nums[0]);
    printArr(nums, size);

    cout << "Sort result:" << endl;
    //quickSort(0, size - 1, nums);
    //bubbleSort(size, nums);
    //MergeSort1(0, size - 1, nums);
    //MergeSort2(size, nums);
    InsertionSort(size, nums);
    printArr(nums, size);
    return 0;
}