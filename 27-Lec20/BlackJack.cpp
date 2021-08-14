#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

// to simulate a game
class Simulatation {
public:

    int oneturn(vector<int> deck,int i,int p) // i # of cards used, p :# of hits of player
    {
        cout<<"new turn "<<endl;
        int n = deck.size();

        if(n-i<4) return 0;
        for(int j = i; j<n; j++) cout<<" "<<deck[j];
        cout<<endl;

        int player = deck[i]+deck[i+2];
        cout<<" player: "<<player<<endl;
        for(int j = 0;j<p;j++)
        {
            player+=deck[i+4+j];
            cout<<" player hits: "<<deck[i+4+j]<<" now player :"<<player<<endl;           
        }
        int dealer = deck[i+1]+deck[i+3];
        int d = 0; // d : how many card dealer hits
        cout<<" dealer: "<<dealer<<endl;
        for(d = 0;d<n-i-4-p;d++)
        {
            if(dealer>=17) break;
            dealer += deck[i+4+p+d];
            cout<<" dealer hits:"<<deck[i+4+p+d] <<" now dealer :"<<dealer<<endl;           
        }
        cout<<" player: "<<player<<" dealer: "<<dealer<<endl; 
        if(player>21 || (player<dealer &&dealer<=21)) cout<<"Player lose !"<<endl;
        if(dealer>21 || (player>dealer &&player<=21)) cout<<"Dealer lose !"<<endl;
        cout<<"end"<<endl<<endl;
        return 4+p+d;// # of card used in this turn
    }

};

// to simulata a game
class Solution {
public:
    int MaxBenefit(vector<int> deck)
    {
        Simulatation s;
        int n = deck.size();
        int i = 0; // # of card used
        // play every turn until no cards 
        while(n-i>=4)
        {
            auto ans = BJ(deck,i);  
            i += s.oneturn(deck,i,ans.second); 
        }
        return BJ(deck,0).first; // return the max benefit 
    }

private:
// MAIN ALGORITHM!
    pair<int,int> BJ(vector<int>deck ,int i)
    {
        vector<pair<int,int>> options;
        int n = deck.size();
        if(n-i<4) return {0,0};

        for(int p = 0; p <= n-i-4; p++) //p : how many cards player hits 
        {
            int player = deck[i]+deck[i+2];
            for(int j = 0;j<p;j++)
                player+=deck[i+4+j];
            if(player>21)
            {
                options.push_back(make_pair(-1+BJ(deck,i+p+4).first,p));
                break;
            }

            int dealer = deck[i+1]+deck[i+3];
            int d = 0; // d : how many card dealer hits
            for(d = 0;d<n-i-4-p;d++)
            {
                if(dealer>=17) break;
                dealer += deck[i+4+p+d];
            }
            if(dealer>21) dealer = 0;

            options.push_back(make_pair(cmp(player,dealer)+BJ(deck,i+4+p+d).first,p));
        }

        return *max_element(options.begin(),options.end());
    }

    int cmp(int player,int dealer)
    {
        if(player==dealer) return 0;
        else if(player>dealer) return 1;
        else return -1;
    };
};





int main()
{

    // vector<int> deck{1,1,11,16,6,6};  // hit to win
 
    // vector<int> deck{1,1,11,16 ,6,6,11,11, 10,1,2,3 ,4,5,10}; // hit to win

    // vector<int> deck{1,11,3,10, 11,10,6,3,4,3, 10,4,11,14}; // predict how dealer draw

    vector<int> deck{1,11,3,10, 11,10,6,3,4,4, 10,4,11,14}; // predict how dealer draw

    // vector<int> deck{1,3,13,10,3};// predict how dealer draw

    // vector<int> deck{1,11,3,10, 1,10,1,1, 11,3,10,4}; // hit to avoid futur lose

    // vector<int> deck{1,1,17,16, 1,5,18,16}; // hit to avoid futur lose

    // vector<int> deck{1,10,1,11, 1,10,1,11}; // hit to avoid futur lose

    // vector<int> deck{1,10,1,10, 1,1,17,16, 3,1,18,1};
    // greedy :  win the first match but lose the second 
    //               1+1+1+1+17>10+10      -> 16+1+1<3+18              -> final benefit = +1-1 = 0
    // smarter: lose the first match but win the second and the third 
    //                 1+1<10+10           -> 1+17>1+16 -> 3+18>1+1    -> final benefit = -1+1+1 = 2;

    Solution s;
    int ans = s.MaxBenefit(deck);
    cout<< ans<< " is the Max Benefit"<<endl;

}   