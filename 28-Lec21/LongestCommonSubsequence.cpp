
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

// using recursion

class Solution_Recursion {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = text1.size(),len2 = text2.size();
        if(len1*len2==0) return 0;
        return longestCommonSubsequence(text1,text2,0,0);
    }
    int longestCommonSubsequence(string text1, string text2,int i ,int j ){
        int len1 = text1.size(),len2= text2.size();
        if(i==len1||j==len2) return 0;
        if(text1[i]==text2[j]) return 1+longestCommonSubsequence(text1,text2,i+1,j+1);
        int result1 = longestCommonSubsequence(text1,text2,i+1,j);
        int result2 = longestCommonSubsequence(text1,text2,i,j+1);
        int result3 = longestCommonSubsequence(text1,text2,i+1,j+1);
        return max(result1,max(result2,result3));
    } 
};
// only keep last 2 rows 

class Solution_Itration_Better {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = text1.size(),len2 = text2.size();
        if(len1*len2==0) return 0;
        vector<int> curr_row(len2+1),last_row(len2+1);
        for(int i = 0; i<=len2;i++)
        {
            last_row[i] = 0;
        }

        for(int i = len1-1; i>=0; i--)
        {
            curr_row[len2] = 0;
            for(int j = len2-1; j>=0;j--)
            {
                if(text1[i]==text2[j]) 
                    curr_row[j] = last_row[j+1]+1;
                else 
                    curr_row[j] = max(curr_row[j+1],max(last_row[j],last_row[j+1])); 
            }
            last_row = curr_row;
        }
        return curr_row[0];
    } 
};

int main()
{

    string s1("hieroglyphology");
    string s2("michaelangelo"); 
    string s3("dinitrophenylhydrazine");
    string s4("acetylphenylhydrazine"); 
    Solution_Recursion solution_r;
    Solution_Itration_Better solution_ib;
    cout<< solution_r.longestCommonSubsequence(s1,s2)<<endl; // 45 seconds!
    // cout<< solution_ib.longestCommonSubsequence(s1,s2)<<endl; //  0.9 seconds!


    // cout<< solution_i.longestCommonSubsequence(s2,s3)<<endl;
    // cout<< solution_i.longestCommonSubsequence(s3,s4)<<endl;

}