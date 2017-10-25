/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to make the uncompress functionality work using 
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
 * The main method in uncompress.cpp. It will read the file after compression
 * and then uncompress it.
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
    BitInputStream finalI(inputF);

    //make a vector to store all the frequencies of symbols
    vector<int> freq(256,0);

    //reader the counter of unique symbols
    int counter = 0;
    inputF.read((char*)&counter,sizeof(int));
    
    //for loop to get back all the frequencies from the header of the 
    //compressed file
    int index = 0;
    for( int i = 0; i < counter; i++)
    {
        inputF.read((char*)&index,sizeof(int));      
        inputF.read((char*)&freq[index],sizeof(int));
    }
 
    //build the tree using frequencies
    HCTree buildT;
    buildT.build(freq);

    //count the total number of symbols using for the for loop later
    int totalSymbol = 0;
    for(int i = 0; i < freq.size(); i++)
    {
        totalSymbol = totalSymbol + freq[i];
    }

    //for loop to decode all the characters back until the file ends
    for(int i = 0; i < totalSymbol; i++)
    {
       int decodedMes = buildT.decode(finalI);
       if(inputF.eof() || decodedMes == -1)
           break;
       outputF.write((char*)&decodedMes,1);
    }

    //flush the stream
    outputF.flush();

    //close both input and output files
    inputF.close();
    outputF.close();

    //ends the main method
    return 0;    
}
