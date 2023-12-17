// FAIRLY UGLY BUT IT WORKED..

#include <bits/stdc++.h>
using namespace std;

#define N1 1
#define N2 2
#define N3 3
#define N4 4
#define N5 5
#define N6 6
#define N7 7
#define N8 8
#define N9 9
#define N10 10

#define W1 11
#define W2 12
#define W3 13
#define W4 14
#define W5 15
#define W6 16
#define W7 17
#define W8 18
#define W9 19
#define W10 20

#define E1 21
#define E2 22
#define E3 23
#define E4 24
#define E5 25
#define E6 26
#define E7 27
#define E8 28
#define E9 29
#define E10 30


#define S1 31
#define S2 32
#define S3 33
#define S4 34
#define S5 35
#define S6 36
#define S7 37
#define S8 38
#define S9 39
#define S10 40


unsigned long dp[150][150][41] = {0};
unsigned long dpv[150][150] = {0};

int val(char c)
{
    return c - '0';
}


void print(vector<string>& v, unsigned long (&dp)[][150][41], int isp) {
   for (int i=0;i< v.size();++i) {
        for (int j=0;j<v[0].size();++j) {
            unsigned long x = INT_MAX;
            for (int step=1;step<41;++step) {
                if (step < 4) continue;
                if (step >10 and step < 14) continue;
                if (step > 20 and step < 24) continue;
                if (step > 30 and step < 34) continue;
                if (isp==1) cout << setw(2) << dp[i][j][step] << " ";
                x = min(x, dp[i][j][step]);
                dpv[i][j] = x;
            }
            if (isp==1) cout << ", ";
            if (isp==2) cout << setw(3) << (x==INT_MAX?0:x) << " ";
        }
        if (isp) cout << endl;
    }
    if (isp) cout << endl;
}


void iter(vector<string>& v) {
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[0].size(); ++j)
        {
            // i,j+1
            if (j + 1 < v[0].size())
            {
                dp[i][j + 1][E1] =  min(dp[i][j + 1][E1] , 
                    val(v[i][j+1]) + 
                    min(
                        {
                            dp[i][j][N4], dp[i][j][N5], dp[i][j][N6],dp[i][j][N7],dp[i][j][N8],dp[i][j][N9],dp[i][j][N10],
                            dp[i][j][S4], dp[i][j][S5], dp[i][j][S6],dp[i][j][S7],dp[i][j][S8],dp[i][j][S9],dp[i][j][S10],
                        }));
                dp[i][j + 1][E2] =  min(dp[i][j + 1][E2] ,val(v[i][j+1]) + dp[i][j][E1]);
                dp[i][j + 1][E3] =  min(dp[i][j + 1][E3] ,val(v[i][j+1]) + dp[i][j][E2]);
                dp[i][j + 1][E4] =  min(dp[i][j + 1][E4] ,val(v[i][j+1]) + dp[i][j][E3]);                
                dp[i][j + 1][E5] =  min(dp[i][j + 1][E5] ,val(v[i][j+1]) + dp[i][j][E4]);                
                dp[i][j + 1][E6] =  min(dp[i][j + 1][E6] ,val(v[i][j+1]) + dp[i][j][E5]);                
                dp[i][j + 1][E7] =  min(dp[i][j + 1][E7] ,val(v[i][j+1]) + dp[i][j][E6]);                
                dp[i][j + 1][E8] =  min(dp[i][j + 1][E8] ,val(v[i][j+1]) + dp[i][j][E7]);                
                dp[i][j + 1][E9] =  min(dp[i][j + 1][E9] ,val(v[i][j+1]) + dp[i][j][E8]);                
                dp[i][j + 1][E10] =  min(dp[i][j + 1][E10] ,val(v[i][j+1]) + dp[i][j][E9]);                                
            }

            // i,j-1
            if (j>0) {
                dp[i][j - 1][W1] =   min(dp[i][j - 1][W1], 
                    val(v[i][j-1]) +  
                    min(
                        {
                            dp[i][j][N4], dp[i][j][N5], dp[i][j][N6],dp[i][j][N7],dp[i][j][N8],dp[i][j][N9],dp[i][j][N10],
                            dp[i][j][S4], dp[i][j][S5], dp[i][j][S6],dp[i][j][S7],dp[i][j][S8],dp[i][j][S9],dp[i][j][S10],
                        }));

                dp[i][j-1][W2] =  min(dp[i][j-1][W2] ,val(v[i][j-1]) + dp[i][j][W1]);
                dp[i][j-1][W3] =  min(dp[i][j-1][W3] ,val(v[i][j-1]) + dp[i][j][W2]);
                dp[i][j-1][W4] =  min(dp[i][j-1][W4] ,val(v[i][j-1]) + dp[i][j][W3]);                
                dp[i][j-1][W5] =  min(dp[i][j-1][W5] ,val(v[i][j-1]) + dp[i][j][W4]);                
                dp[i][j-1][W6] =  min(dp[i][j-1][W6] ,val(v[i][j-1]) + dp[i][j][W5]);                
                dp[i][j-1][W7] =  min(dp[i][j-1][W7] ,val(v[i][j-1]) + dp[i][j][W6]);                
                dp[i][j-1][W8] =  min(dp[i][j-1][W8] ,val(v[i][j-1]) + dp[i][j][W7]);                
                dp[i][j-1][W9] =  min(dp[i][j-1][W9] ,val(v[i][j-1]) + dp[i][j][W8]);                
                dp[i][j-1][W10] =  min(dp[i][j-1][W10] ,val(v[i][j-1]) + dp[i][j][W9]);                

            }


            // i-1,j
            if (i >0) {
                dp[i-1][j ][N1] =   min(dp[i-1][j ][N1], 
                    val(v[i-1][j]) +  
                    min(
                        {
                        dp[i][j][E4], dp[i][j][E5], dp[i][j][E6],dp[i][j][E7],dp[i][j][E8],dp[i][j][E9],dp[i][j][E10],
                        dp[i][j][W4], dp[i][j][W5], dp[i][j][W6],dp[i][j][W7],dp[i][j][W8],dp[i][j][W9],dp[i][j][W10],
                        }));

                dp[i-1][j][N2] =  min(dp[i-1][j][N2] ,val(v[i-1][j]) + dp[i][j][N1]);
                dp[i-1][j][N3] =  min(dp[i-1][j][N3] ,val(v[i-1][j]) + dp[i][j][N2]);
                dp[i-1][j][N4] =  min(dp[i-1][j][N4] ,val(v[i-1][j]) + dp[i][j][N3]);                
                dp[i-1][j][N5] =  min(dp[i-1][j][N5] ,val(v[i-1][j]) + dp[i][j][N4]);                
                dp[i-1][j][N6] =  min(dp[i-1][j][N6] ,val(v[i-1][j]) + dp[i][j][N5]);                
                dp[i-1][j][N7] =  min(dp[i-1][j][N7] ,val(v[i-1][j]) + dp[i][j][N6]);                
                dp[i-1][j][N8] =  min(dp[i-1][j][N8] ,val(v[i-1][j]) + dp[i][j][N7]);                
                dp[i-1][j][N9] =  min(dp[i-1][j][N9] ,val(v[i-1][j]) + dp[i][j][N8]);                
                dp[i-1][j][N10] =  min(dp[i-1][j][N10] ,val(v[i-1][j]) + dp[i][j][N9]);                                



            }

            // i+1,j
            if (i+1 < v.size()) {
                dp[i+1][j ][S1] =   min(dp[i+1][j ][S1], val(v[i+1][j]) +  
                    min(
                        {
                        dp[i][j][E4], dp[i][j][E5], dp[i][j][E6],dp[i][j][E7],dp[i][j][E8],dp[i][j][E9],dp[i][j][E10],
                        dp[i][j][W4], dp[i][j][W5], dp[i][j][W6],dp[i][j][W7],dp[i][j][W8],dp[i][j][W9],dp[i][j][W10],
                        }));


                dp[i+1][j][S2] =  min(dp[i+1][j][S2] ,val(v[i+1][j]) + dp[i][j][S1]);
                dp[i+1][j][S3] =  min(dp[i+1][j][S3] ,val(v[i+1][j]) + dp[i][j][S2]);
                dp[i+1][j][S4] =  min(dp[i+1][j][S4] ,val(v[i+1][j]) + dp[i][j][S3]);                
                dp[i+1][j][S5] =  min(dp[i+1][j][S5] ,val(v[i+1][j]) + dp[i][j][S4]);                
                dp[i+1][j][S6] =  min(dp[i+1][j][S6] ,val(v[i+1][j]) + dp[i][j][S5]);                
                dp[i+1][j][S7] =  min(dp[i+1][j][S7] ,val(v[i+1][j]) + dp[i][j][S6]);                
                dp[i+1][j][S8] =  min(dp[i+1][j][S8] ,val(v[i+1][j]) + dp[i][j][S7]);                
                dp[i+1][j][S9] =  min(dp[i+1][j][S9] ,val(v[i+1][j]) + dp[i][j][S8]);                
                dp[i+1][j][S10] =  min(dp[i+1][j][S10] ,val(v[i+1][j]) + dp[i][j][S9]);                                


            }
        }
    }

}


int main(int argc, char **argv)
{
    string fname{"input.txt"};
    if (argc > 1)
        fname = argv[1];
    ifstream ifs{fname};
    string tmp;
    vector<string> v;
    while (ifs >> tmp)
    {
        v.push_back(tmp);
    }


    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[0].size(); ++j)
        {
            for(int step=0;step< 41;++step) {
                dp[i][j][step] = INT_MAX;
            }
        }
    }    

    for(int step=0;step<41;++step) dp[0][0][step]=0;

    for(int i=0;i<100;++i) {
        iter(v);
        print(v,dp, 0);    
        cout << "Answer: " << dpv[v.size()-1][v[0].size() -1] << endl;
    }

}
