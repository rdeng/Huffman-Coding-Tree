/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file implements the functions to support building the
 * HCTree, encode, decode and delete the tree.
 * Assignment number: PA2
 */

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;
    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs)
    {
        //intialize a priority queue to build the haffman tree
        std::priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> list;
 
        //for loop to build haffman tree using HCNode
        int size = freqs.size();
        for(int i = 0; i < size ; i++)
        {
            //if frequency is not 0, should create a corresponding HCNode 
            //and store it to leaves 
            if(freqs[i] != 0)
            {
                leaves[i] = new HCNode(freqs[i],i,0,0,0);
                list.push(leaves[i]);
            }
        }
 
        //if there is only one character in the list
        if(list.size() == 1)
        {
           HCNode *c0 = list.top();
           list.pop();
           //insert a null node
           HCNode *c1 = new HCNode(0,0,0,0,0);
           int count = c0->count;
           //make them a parent node
           HCNode *par = new HCNode(count,c0->symbol,c0,c1,0); 
           c0->p = par;
           c1->p = par;
           list.push(par);
        }

        //while there's more than 1 tree in the forest
        while(list.size() >= 2)
        {
            //remove the two lowest count trees
            HCNode* topOne = list.top();
            list.pop();
            HCNode* secOne = list.top();
            list.pop();
            
            //combine two trees into a new tree
            int bothCount = topOne->count + secOne->count;
            HCNode* combinePar = new HCNode(bothCount,topOne->symbol,topOne,
                                            secOne,0);
            topOne->p = combinePar;
            secOne->p = combinePar;

            //insert the new tree in to forest
            list.push(combinePar);
        }

        //if nothing in the tree, make the root null and return
        if(list.empty())
        {
            root = 0;
            return;
        }
        //else make the root to be top element in the list
        else
        {
            root = list.top();
        }
    }

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void HCTree::encode(byte symbol, BitOutputStream& out) const
    {
        //find the node for the symbol in parameter and create a vector to
        //store all the position information for it 
        HCNode* start = leaves[symbol];         
        vector<int> encodedMes;

        //whiel loop go all the way up to find the path
        while(start->p != 0)
        {
            HCNode* par = start->p;
            
            //if left child, add 0 to the vector
            if(par->c0 == start)
            {
                encodedMes.push_back(0);
            }
            //if right child, add 1 to the vector
            else
            {
                encodedMes.push_back(1);
            }
            start = par;
        }
        
        //write all the chars in the vector to output file
        int i = encodedMes.size() - 1;
        while(i >= 0)
        {
            out.writeBit(encodedMes[i]);
            i--;
        }
    }
    /** 
     * Write to the given ofstream;
     * the sequence of bits (as ASCII) coding the given symbol.
     * PRECONDITION: build() has been called, to create the coding
     * tree, and initialize root pointer and leaves vector.
     * THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     * BE USED IN THE FINAL SUBMISSION.
     */
    void HCTree::encode(byte symbol, ofstream& out) const
    {
        //find the node for the symbol in parameter and create a vector to
        //store all the position information for it
        HCNode* start = leaves[symbol]; 
        vector<unsigned char> encodedMes;

        //while loop go all the way up to find the path
        while(start->p != 0)
        {
            HCNode* par = start->p;

            //if left child, add '0' to the vector
            if(par->c0 == start)
            {
                encodedMes.push_back('0');
            }
            //if right child, add '1' to the vector
            else
            {
                encodedMes.push_back('1');
            }
            start = par;
        }

        //write all the chars in the vector to output file
        int i = encodedMes.size() - 1;
        while(i >= 0)
        {
            out << encodedMes[i];
            i--;
        } 
    }
   
    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int HCTree::decode(BitInputStream& in) const
    {
        HCNode* decodedMes = root;

        //empty file case, return -1
        if(decodedMes == 0)
        {
            return -1;
        }

        //while loop go all the way down to find the symbol 
        while(decodedMes->c0 != 0)
        {
            //read an int from the file after compression
            int code = in.readBit();

            //if the int is 0, go to the left child 
            if(code == 0)
            {
                decodedMes = decodedMes->c0;
            }
            //if the int is 1, go to the right child
            else if(code == 1)
            {
                decodedMes = decodedMes->c1;
            }
            //all other cases, break
            else
            {
                break;
            }
        }

        //return the symbol after decoding as a form of int
        return (int)decodedMes->symbol;
    }

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int HCTree::decode(ifstream& in) const
    {
        HCNode* decodedMes = root;

        //while loop go all the way down to find the symbol
        while(decodedMes->c0 != 0)
        {
            //read a char from the file after compression
            char code = in.get();
 
            //if the char is '0', go to the left child 
            if(code =='0')
            {
                decodedMes = decodedMes->c0;
            }
            //if the char is '1', go to the right child
            else if(code == '1')
            {
                decodedMes = decodedMes->c1;
            }
            //all other cases, break
            else
            {
                break;
            }
        }

        //return the symbol after decoding as a form of int
        return (int)decodedMes->symbol;
    }

    /**
     * recursively delete all the node in the HCTree 
     * and set all pointer to null
     */
    void HCTree::deleteAll(HCNode* n)
    {
        if(n == 0)
          return;
     
        //delete the node in post-order travalse   
        deleteAll(n->c0);
        deleteAll(n->c1);
        delete n;
        n = 0;
    }
