//
//  main.cpp
//  proj6
//
//  Created by Monica Bellare on 11/25/18.
//  Copyright © 2018 Monica Bellare. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

/*
int main()
{
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;
    
    *ptr = 30;          // set arr[0] to 30
    *ptr + 1 = 20;      // set arr[1] to 20
    ptr += 2;
    ptr[0] = 10;        // set arr[2] to 10
    
    while (ptr >= arr)
    {
        ptr--;
        cout << *ptr << endl;    // print values
    }
}

int main()
{
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;
    
    *ptr = 30;          // set arr[0] to 30
    *(ptr + 1) = 20;      // set arr[1] to 20
    ptr += 2;
    ptr[0] = 10;        // set arr[2] to 10
    
    ptr -=2 ; // reset to initial address
    while (ptr <= &arr[2])
    {
        cout << *ptr << endl;    // print values
        ptr++; // needs to come after print line so that first value is printed
    }
}
 */


/*
 int i = 1;
 while (ptr <= &arr[2])
 {
 cout << *ptr << endl;    // print values
 ptr = &arr[i]; // switched
 i++;
 }
 */

/* 1B
void findMax(int arr[], int n, int* pToMax)
{
    if (n <= 0)
        return;      // no items, no maximum!
    
    pToMax = arr;
    
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *pToMax)
            pToMax = &arr[i]; // DID NOT GUARENTEE i POSITION IN ARR
    }
}

int main()
{
    int nums[4] = { 5, 3, 15, 6 };
    int* ptr;
    ptr = &nums[0];

    findMax(nums, 4, ptr); // function isn't doing anything for some reason
    cout << "The maximum is at address " << ptr << endl;
    cout << "It's at position " << ptr - nums << endl;
    cout << "Its value is " << *ptr << endl;
}
 */

/* 1C
void computeCube(int n, int* ncubed)
{
    *ncubed = n * n * n;
}

int main()
{
    int* ptr;
    int i = 0;
    ptr = &i;
    computeCube(5, ptr);
    cout << "Five cubed is " << *ptr << endl;
}
*/

/* 1D
 // return true if two C strings are equal
 bool strequal(const char str1[], const char str2[])
 {
 if(strlen(str1) != strlen(str2))
 return false;
 int i = 0;
 while (str1[i] != 0  &&  str2[i] != 0)
 {
 if (str1[i] != str2[i])  // compare corresponding characters
 return false;
 i++;
 }
 return true;   // both ended at same time?
 }
 
 int main()
 {
 char a[15] = "Zhou";
 char b[15] = "Zhouo";
 
 if (strequal(a,b))
 cout << "They're the same person!\n";
 }
*/

// 3A
/*
double mean(const double* scores, int numScores)
{
    int count = 0;
    const double* ptr = scores;
    double tot = 0;
    while (count < numScores)
    {
        tot += *(ptr + count);
        count++;
    }
    return tot/numScores;
}

int main()
{
    double nums[3] = { 1, 2, 3 };
    double* ptr = nums;
    cout << mean(ptr, 3) << endl;
}
*/

/*
const char* findTheChar(const char* strPtr, char chr) //strPtr must be initialized to str
{
    while(*ptr!= 0) {
        if (*ptr == chr) {
            return (strPtr + (ptr-strPtr));
        }
        ptr++;
    }
    return nullptr;
}
*/

/*
const char* findTheChar(const char str[], char chr)
{
    for (int k = 0; str[k] != 0; k++)
        if (str[k] == chr)
            return &str[k];
    
    return nullptr;
}

int main()
{
    const char str[] = {'m', 'o', 'n', 'i', 'c', 'a'};
    const char* ptr = str;

    cout << findTheChar(ptr, 'o') << endl;
}
*/

/*
void findMax(int arr[], int n, int*& pToMax)
{
    if (n <= 0)
        return;      // no items, no maximum!
    
    pToMax = arr;
    
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *pToMax)
            pToMax = arr + i;
    }
}

int main()
{
    int nums[4] = { 5, 3, 15, 6 };
    int* ptr;
    
    findMax(nums, 4, ptr);
    cout << "The maximum is at address " << ptr << endl;
    cout << "It's at position " << ptr - nums << endl;
    cout << "Its value is " << *ptr << endl;
}
 */

// 4
/*
int* maxwell(int* a, int* b)
{
    if (*a > *b)
        return a;
    else
        return b;
}

void swap1(int* a, int* b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int array[6] = { 5, 3, 4, 17, 22, 19 };
    
    int* ptr = maxwell(array, &array[2]); // inputs: 1st and 3rd elements of array --> ptr = index 0
    *ptr = -1; // index 0 = -1
    ptr += 2; // ptr = 2
    ptr[1] = 9; // index 3 = 9
    *(array+1) = 79; // indedx 1 = 79
    
    cout << &array[5] - ptr << endl; // should output 3 (5-2) // array now : {-1 ,79, 4, 9, 22, 19}
    
    swap1(&array[0], &array[1]); // array now : {-1, 79, 4, 9, 22, 19}
    swap2(array, &array[2]); // array now : {4, 79, -1, 9, 22, 19}
    
    for (int i = 0; i < 6; i++)
        cout << array[i] << endl;
}
*/

/*
void removeS(char cstr[]) {
    char* ptr = cstr;
    while(*ptr != 0) {
        if(*ptr == 's' || *ptr == 'S') {
            while(*ptr !=0) {
                *ptr = *(ptr+1);
                ptr++;
            }
            ptr = cstr;
        }
        ptr++;
    }
}

const char* findTheChar(const char str[], char chr) //strPtr must be initialized to str
{
    const char* strPtr = str;
    for (int k = 0; *(strPtr + k) != 0; k++)
        if (*(str + k) == chr)
            return (strPtr + k);
    return nullptr;
}

int main()
{
    const char str[] = {'m', 'o', 'n', 'i', 'c', 'a'};
    const char* ptr = str;
    
    cout << findTheChar(ptr, 'o') << endl;
}
 */
void removeS(char cstr[]) {
    char* ptr = cstr; // first element
    while(*ptr != 0) {
        if(*ptr == 's' || *ptr == 'S') {
            while(*ptr !=0) {
                *ptr = *(ptr+1);
                ptr++;
            }
            ptr = cstr;
        }
        if(*ptr != 's' && *ptr != 'S') // in case first two elems are s
            ptr++;
    }
}

int main()
{
    char msg[50] = "She'll be a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll be a male prince.
}


