/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to make the compress functionality work using 
 * HCNode and HCTree
 * Assignment number: PA2
 */

#include "HCNode.hpp"
#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/**
 * The main method in compress.cpp. It will read a file, then compress
 * it and store it to another file
 */
int main(int argc, char* argv[])
{
    //check if the argument number is exactly 3 to make sure the program works
    if(argc != 3)
    {
        std::cout<<"Invalid arguments input!"<<std::endl;
        return -1;
    }

    //open the input file and output file
    ifstream inputF(argv[1],ios::binary);
    ofstream outputF(argv[2],ios::binary);
    BitOutputStream finalOut(outputF);

   
    //initialize a symbol the store the character get and a vector to store
    //all the frequencies
    byte symbol;
    vector<int> freq(256,0);

    //for loop to get all the frequencies from the file reading until
    //the file ends and counts total number of symbols
    int totalSymbol = 0;
    while(1)
    {
        symbol = inputF.get();
        if(inputF.eof())
            break;
        freq[symbol]++;
        totalSymbol++;
    }

    //build the tree using frequencies    
    HCTree buildT;
    buildT.build(freq);
 
    //close input file and open again the clear all the reading procedure
    inputF.close();
       
    //write the header used for uncompression
    //first write the counter of unique symbols 
    int counter = 0;
    for(int j = 0; j < freq.size(); j ++) 
    {
        if(freq[j] != 0)
        {
            counter++;
        }
    }    
    outputF.write((char*)&counter,sizeof(int));

    //then write all non-zero count symbols and its frequency
    for(int j = 0; j < freq.size(); j ++) 
    {
        if(freq[j] != 0)
        {
            outputF.write((char*)&j,sizeof(int));
            outputF.write((char*)&freq[j],sizeof(int));
        }
    }

    inputF.open(argv[1],ios::binary);

    //encode characters one by one using for loop going through all symbols
    for(int i = 0; i < totalSymbol; i++)
    {
        byte toEncode = inputF.get();
        if(inputF.eof())
        {
            break;
        }
        //if there exist a char, encode it
        if(freq[toEncode] != 0)
        {
            buildT.encode(toEncode,finalOut);
        }
    }

    //flush the stream
    finalOut.flush(); 

    //close both input and output files 
    inputF.close();
    outputF.close();
    
    //ends the main method
    return 0;    
}
