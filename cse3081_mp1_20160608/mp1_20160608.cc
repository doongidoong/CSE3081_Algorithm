#include <vector> //중요
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;
int algorithm1(int n, int m, int **arr);
int algorithm2(int n, int m, int **arr);
int algorithm3(int n, int m, int **arr);

int main(int argc, char *argv[]) {
    std::ifstream ifs;
    // cout << ""<< argv[1] << endl;
    ifs.open(argv[1]);
    std::ofstream ofs;
    string s = argv[1];
    s= "result_"+ s;
    ofs.open(s.c_str());
    int num;
    int n, m;
    string index = argv[2];
    ifs >> n;
    ifs >> m;

    ofs<< argv[1] << endl;
    ofs<< argv[2] << endl;
    ofs<< n << endl;
    ofs<< m << endl;
    int **arr;
    arr = (int**)malloc(sizeof(int*) * n);

    for(int i=0;i<n;i++){
        arr[i] = (int*)malloc(sizeof(int) * m);
        for(int j=0;j<m;j++){
            ifs >> num;
            arr[i][j] = num;
        }
    }

    clock_t start, end;
    start = clock();
    int maxArrSum;   
    if(index.compare("1")==0) maxArrSum = algorithm1(n,m,arr);
    if(index.compare("2")==0) maxArrSum = algorithm2(n,m,arr);
    if(index.compare("3")==0) maxArrSum = algorithm3(n,m,arr);
    end = clock();
    ofs<<maxArrSum<< endl;;
    ofs<<(double)(end-start)<< endl;;

    return 0;
}


int algorithm1(int n, int m, int **arr){
    int arrSum;
    int maxArrSum=0;
    for(int up=0;up<n;up++){
        for(int left=0;left<m;left++){
            for(int down=up;down<n;down++){
                for(int right=left;right<m;right++){
                    arrSum=0;
                    for(int v=up;v<=down;v++){
                        for(int h=left;h<=right;h++){
                            arrSum+=arr[v][h];       
                        }    
                    }
                    if(arrSum > maxArrSum){
                        maxArrSum = arrSum;
                    }

                }   
            }
            
        }
    }
    return maxArrSum;   
}


int algorithm2(int n, int m, int **arr){
    int arrSum;
    int maxArrSum=0;
    int colSum[m]={0,}; 
    for(int up=0;up<n;up++){
        for(int left=0;left<m;left++){
            for(int down=up;down<n;down++){
                arrSum=0;
                for(int right=left;right<m;right++){
                    colSum[right]+= arr[down][right];
                    arrSum += colSum[right];
                    if(arrSum > maxArrSum){
                        maxArrSum = arrSum;
                    }
                }

            }
            fill_n(colSum, m, 0);
        }
    }
    return maxArrSum;   
}

int algorithm3(int n, int m, int **arr){
    int arrSum;
    int maxArrSum=0;
    int rowSum[n]={0,}; 
    for(int left=0;left <m; left++ ){
        fill_n(rowSum, n, 0);
        for(int right=left; right <m; right++ ){
            for(int down=0; down <n; down++ ){
                rowSum[down] += arr[down][right]; 
            }
            arrSum=0;
            for(int down=0; down <n; down++ ){
                arrSum+= rowSum[down];     
                if(arrSum > maxArrSum){
                    maxArrSum = arrSum;
                }
                if(arrSum < 0 ) arrSum=0;
            }

        }
    }
    return maxArrSum;   
}