#include<iostream>
using namespace std;

//快速排序
void quickSort(int left, int right, int nums[]){
    if(left > right) return;
    int i = left, j = right, base = nums[left], tmp;
    while (i < j)
    {
        while (nums[j] >= base && i < j)
        {
            j--;
        }
        while (nums[i] <= base && i < j)
        {
            i++;
        }
        if(i < j){
            tmp = nums[j];
            nums[j] = nums[i];
            nums[i] = tmp;
        }
    }
    nums[left] = nums[j];
    nums[j] = base;
    quickSort(left, j - 1, nums);
    quickSort(j + 1, right, nums);
}

void printArr(int size, int nums[]){
    for(int i = 0; i < size; ++i){
        cout << nums[i] << " ";
    }
    cout << endl;
}

int main(){
    int nums[] = {6, 3, 1, 8, 5, 9, 2, 7, 4, 0};
    int size = sizeof(nums) / sizeof(nums[0]);
    printArr(size, nums);
    quickSort(0, size - 1, nums);
    printArr(size, nums);
    return 0;
}