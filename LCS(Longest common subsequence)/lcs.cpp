#include<iostream>
#include<algorithm>
using namespace std;

int lcs(string a, string b){

    int lenA = a.length();
    int lenB = b.length();
    int c[lenA + 1][lenB + 1];
    int tempi, tempj;

    for(int i = 0; i < lenA + 1; i++){
        c[i][0] = 0;
    }

    for(int i = 0; i < lenB + 1; i++){
        c[0][i] = 0;
    }

    for(int i = 0; i < lenA; i++){
        for(int j = 0; j < lenB; j++){
            tempi = i + 1;
            tempj = j + 1;

            if(a[i] == b[j]){
                c[tempi][tempj] = c[tempi - 1][tempj - 1] + 1;
            }else{
                c[tempi][tempj] = max(c[tempi - 1][tempj], c[tempi][tempj - 1]);
            }
        }
    }

    return c[lenA][lenB];

}

int main(){
    string a, b;
    cin>>a>>b;
    cout<<lcs(a, b)<<endl;
}
