
#include<iostream>
#include<algorithm>
using namespace std;

int* insertionSort(int a[], int n){

    for(int i = 1; i < n; i++){
        int j = i;
        while(j > 0 && a[j] < a[j - 1]){
            swap(a[j], a[j - 1]);
            j--;
        }
    }

    for(int i = 0; i < n; i++) cout<<a[i]<<" ";
    cout<<endl;

}

int main(){
 int inputArray[100];
 int n;
 cin>>n;

 for(int i = 0; i < n; i++){
    cin>>inputArray[i];
 }
 insertionSort(inputArray, n);
}
