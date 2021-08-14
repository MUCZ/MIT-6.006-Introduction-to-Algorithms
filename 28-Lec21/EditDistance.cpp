#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
// using recursion
class Solution_Recursion { 
public:
    int minDistance(string word1, string word2) {
        return minDistance(word1,word2,0,0);
    }
    int minDistance(string word1, string word2,int i,int j){
        if(i==word1.size()||j==word2.size()) return word1.size()+word2.size()-i-j;
        if(word1[i]==word2[j]) return minDistance(word1,word2,i+1,j+1);
        int insert_cost = 1+minDistance(word1,word2,i,j+1);
        int delete_cost = 1+minDistance(word1,word2,i+1,j);
        int replace_cost = 1+minDistance(word1,word2,i+1,j+1);
        return min(insert_cost,min(delete_cost,replace_cost));
    }
};

// bottom-up 2-d array
class Solution_Iteration { 
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(),len2 = word2.size();
        if(len1*len2==0) return len1+len2;
        
        // initialisation
        int dp[len1+1][len2+1]; // todo ： replace 2-d array with last 2 rows or columns
        for(int i = 0;i<=len1;i++)
        {
            dp[i][len2] = len1-i;
        }
        for(int j = 0; j<=len2;j++)
        {
            dp[len1][j] = len2-j;
        }
        // bottom->up & right->left
        for(int i = len1-1; i>=0; i--)
        {
            for(int j = len2-1; j>=0; j--)
            {
                if(word1[i]==word2[j])
                    dp[i][j] = dp[i+1][j+1];
                else
                    dp[i][j] = 1 + min(dp[i][j+1],min(dp[i+1][j+1],dp[i+1][j]));
            }
        }
        return dp[0][0];
    }
};
// only keep last 2 rows 
class Solution_Itration_Better { 
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size(),len2 = word2.size();
        if(len1*len2==0) return len1+len2;
        // initialisation

        // only need to keep last 2 rows (or last 2 columns)
        vector<int> current_row(len2+1),last_row(len2+1);

        for(int j = 0; j<=len2;j++)
        {
            last_row[j] = len2-j;
        }

        // bottom->up & right->left
        int i = len1-1;
        int j = len2-1;

        for( i = len1-1; i>=0; i--)
        {
            current_row[len2] = len1-i; 
            for(j = len2-1; j>=0; j--)
            {
                if(word1[i]==word2[j])
                    current_row[j] = last_row[j+1];
                else
                    current_row[j] = 1+min(current_row[j+1],min(last_row[j],last_row[j+1]));
            }
            last_row = current_row;
        }
        return current_row[0];
    }
};



int main()
{

    string s1("hieroglyphology");
    string s2("michaelangelo"); 
    string s3("dinitrophenylhydrazine");
    string s4("acetylphenylhydrazine"); 
    Solution_Recursion solution_r;
    Solution_Iteration solution_i;
    Solution_Itration_Better solution_ib;
    // cout<< solution_r.minDistance(s1,s2)<<endl; // 46 seconds!
    // cout<< solution_i.minDistance(s1,s2)<<endl; //  0.873 seconds!
    cout<< solution_ib.minDistance(s1,s2)<<endl; //  0.873 seconds!


    // cout<< solution_i.minDistance(s2,s3)<<endl;
    // cout<< solution_i.minDistance(s3,s4)<<endl;

}