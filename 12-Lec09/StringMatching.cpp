#include <string>
#include <iostream>
#include <vector>

using namespace std;

class RollingHash
{
private:
    int val;
public:
    RollingHash(int v = 0):val(v){};
    int r();
    void append(char c);
    void skip(char c);
};

int RollingHash::r()
{
    return val%256; // A random prime
}

void RollingHash::append(char c)
{
    val+=c;
}

void RollingHash::skip(char c)
{
    val-=c;
}

class Solution {
public:
    int strStr(string s, string p) { // find p in s 
// KMP Algo
        auto n = s.size(), m = p.size();
        if(m==0) return 0;
        p.insert(p.begin(),' ');
        s.insert(s.begin(),' ');
        vector<int> next(m+1);
        // build next
        next[1] = 1;
        for(int i = 2,j = 1 ;i <=m ; i++)
        {
            while((j>1) and (p[j]!=p[i])) j = next[j-1];
            if(p[j]==p[i]) j++;
            next[i] = j;
        }
        // rolling check
        for(int i = 1,j = 1; i<=n ; i++)
        {
            while(j>1 and s[i]!=p[j]) j = next[j-1];
            if(s[i] == p[j]) j++;
            if(j==m+1) return i-m;
        }
        return -1;

// Same KMP Algo but using diffrent subscript

        // int lens = s.size();
        // int lenp = p.size();
        // s.insert(s.begin(),' ');
        // p.insert(p.begin(),' ');
        // vector<int> next(lenp+1);
        // for(int j = 2, i = 0; j<=lenp;j++)
        // {
        //     if(i && p[i+1]!=p[j]) i = next[i];
        //     if(p[i+1]==p[j]) i++;
        //     next[j] = i;
        // }
        // for(int j = 1,i = 0;j<=lens;j++)
        // {
        //     if(i && s[j]!=p[i+1]) i = next[i];
        //     if(s[j]==p[i+1]) i++;
        //     if(i == lenp) return j-lenp;
        // }
        // return -1;

// Rolling Hash Algo
        // int check;
        // RollingHash hp;
        // RollingHash hs;
        // for(int i = 1;i <= m;i++)
        // {
        //     hp.append(p[i]);
        // }
        // for(int i = 1;i<= m;i++)
        // {
        //     hs.append(s[i]);
        // }
        // int h_v = hp.r();
        // if(h_v==hs.r()) // check string equal
        // {
        //     check = 1;
        //     for(int j = 1; j <= m ; j++)
        //     {
        //         if(p[j]!=s[j])
        //         {
        //             check = 0;
        //             break;
        //         }
        //     }
        //     if(check)
        //         return 0;
        // }
        // for(int i = m+1;i<=n;i++)
        // {
        //     hs.skip(s[i-m]);
        //     hs.append(s[i]);
        //     if(h_v==hs.r()) // check string equal
        //     {
        //         check = 1;
        //         for(int j = m; j >= 1; j--)
        //         {
        //             if(s[i-m+j]!=p[j])
        //             {
        //                 check = 0;
        //                 break;
        //             }
        //         }
        //         if(check)
        //             return i-m;
        //     }
        // }
        // return -1;
    }
};






int main()
{
    Solution func;
    cout<< func.strStr("hello","llo") <<endl;
    cout<< func.strStr("hello","el") <<endl;
    cout<< func.strStr("nihao","ihx") <<endl;
    cout<< func.strStr("aaaaa","bba") <<endl;

}