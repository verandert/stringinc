#include <stdio.h>

int CompareS(char *S, char *T);
int BinarySearch(char *str[], int low, int high, char *target, int *flag);

int main(){
    char *str[] = {"Cdde", "Dodo", "Edd", "aa", "ddd"};
    int result;
    int index;
    printf("%d\n", index);
    result = BinarySearch(str, 0, 4, "ddd", &index);
    printf("%d %d\n", result, index);
    return 0;
}

int CompareS(char *S, char *T){
    while (*S && *T)
    {
        if(*S != *T) return (*S - *T);
        S++; T++;
    }
    return *S - *T;
}

int BinarySearch(char *str[], int low, int high, char *target, int *flag){
    int mid = 0;
    while (low <= high)
    {   
        mid = (low + high) / 2;
        if(CompareS(target, str[mid])) low = mid + 1;
        else if(CompareS(str[mid], target)) high = mid - 1;
        else return mid;
    }
    printf("%d ", low);
    *flag = low;
    return -1;
}