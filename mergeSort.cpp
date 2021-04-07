#include<iostream>
using namespace std;

void Merge(int left, int mid, int right, int nums[]){
    int i = left, j = mid + 1, k = 0;
    int *tmp = new int[right - left + 1];
    while (i <= mid && j <= right)
    {
        if(nums[i] <= nums[j])
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    while (i <= mid)
    {
        tmp[k++] = nums[i++];
    }
    while (j <= right)
    {
        tmp[k++] = nums[j++];
    }
    for(int i = left, k = 0; i <= right; i++, k++)
        nums[i] = tmp[k];
    delete []tmp;
}

void mergeSort(int left, int right, int nums[]){
    if(left >= right) return;
    int mid = (right + left) / 2;
    mergeSort(left, mid, nums);
    mergeSort(mid + 1, right, nums);
    Merge(left, mid, right, nums);
}

int main(){
    int nums[] = {6, 3, 1, 8, 9, 2, 7, 4, 0};
    int size = sizeof(nums) / sizeof(nums[0]);
    for(int i = 0; i < size; ++i)
        cout << nums[i] << " " ;
    cout << endl << "After sort:" << endl;
    mergeSort(0, size - 1, nums);
    for(int i = 0; i < size; ++i)
        cout << nums[i] << " " ;
    cout << endl;

    return 0;
}