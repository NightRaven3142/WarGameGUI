//
//  main2.cpp
//  War Card Game
//
//  Created by Varun Chaganty on 10/12/2018.
//  Copyright © 2018 Varun Chaganty. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <cstdlib>

//using namespace std;

int turns = 0;
const size_t deckSize = 52;

int randomNumGen(int i )
{
    return std::rand()%i;
}

std::vector<int> generateDeck(size_t dSize)
{
    std::vector<int> deck;
    
    for (int x = 0; x < dSize / 13; x++)
    {
        for (int i = 2; i <= 14; i++)
        {
            deck.push_back(i);
        }
    }
    return deck;
}


int main(int argc, const char * argv[])
{
    std::srand(unsigned(std::time(0)));
    std::vector<int> deck = generateDeck(deckSize);
    
    std::random_shuffle(deck.begin(), deck.end(), randomNumGen);
    
    
    for(int x = 0; x < deck.size(); x++)
    {
        std::cout << deck[x] << ", ";
    }
    
    std::cout << std::endl;
    
    
    std::vector<int> mOne;
    std::vector<int> mTwo;
     
     
    for (int i = 0; i < 26; i++)
    {
        mOne.push_back(deck[i]);
    }
    
    for (int i = 26; i < deck.size(); i++)
    {
        mTwo.push_back(deck[i]);
    }
    
   // std::cout << mOne.size() << std::endl;
    // std::cout << mTwo.size() << std::endl;
    
    while (true)
    {
        //std::cout << "Turns " << turns << " mOne: " << mOne[0] << " mTwo " << mTwo[0] << " Size " << mOne.size() << " Size " << mTwo.size() << std::endl;
        
        if(mOne.size() == 0)
        {
            std::cout << "Player two is the winner with " << turns << " Turns" << std::endl;
            break;
        }
        else if (mTwo.size() == 0)
        {
            std::cout << "Player one is the winner with " << turns << " Turns" << std::endl;
            break;
        }
        
        int One = mOne[0];
        int Two = mTwo[0];
        
        if(One > Two)
        {
            mOne.push_back(Two);
            mOne.push_back(One);
            
            mOne.erase(mOne.begin());
            mTwo.erase(mTwo.begin());
        }
        else if(Two > One)
        {
            mTwo.push_back(One);
            mTwo.push_back(Two);
            
            mTwo.erase(mTwo.begin());
            mOne.erase(mOne.begin());
        }
        else if (One == Two)
        {
                if(mOne.size() > 3 && mTwo.size() > 3 && mOne[4] != mTwo[4])
                {
                    std::vector<int> pOne;
                    std::vector<int> pTwo;
                    
                    for(int i = 0; i < 3; i++)
                    {
                        pOne.push_back(mOne[i]);
                        mOne.erase(mOne.begin());
                    }
                    
                    for(int i = 0; i < 3; i++)
                    {
                        pTwo.push_back(mTwo[i]);
                        mTwo.erase(mTwo.begin());
                    }
                    
                  //  std::cout << mOne[4] << std::endl;
                   // std::cout << mTwo[4] << std::endl;
                    
                    
                    if(mOne[4] > mTwo[4])
                    {
                        for(int x = 0; x < pOne.size(); x++) { mOne.push_back(pOne[x]); }
                        for(int x = 0; x < pOne.size(); x++) { mOne.push_back(pTwo[x]); }
                    }
                    else if (mTwo[4] > mOne[4])
                    {
                        for(int x = 0; x < pTwo.size(); x++) { mTwo.push_back(pOne[x]); }
                        for(int x = 0; x < pTwo.size(); x++) { mTwo.push_back(pTwo[x]); }
                    }
                    /*
                    std::cout << "One" << mOne.size() << std::endl;
                    std::cout << "Two" << mTwo.size() << std::endl;
                    std::cout << "Total" << mOne.size() + mTwo.size() << std::endl;
                    std::cout << std::endl;
                */
                     }
            else
            {
                rotate(mOne.begin(), mOne.end()-1, mOne.end());
                rotate(mTwo.begin(), mTwo.end()-1, mTwo.end());
            }
            
        }
        turns++;
        
    }
}
