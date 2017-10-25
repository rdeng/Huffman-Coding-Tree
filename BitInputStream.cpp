/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to read bit from a file using the build in
 * istream for C++.
 * Assignment number: PA2
 */

#include "BitInputStream.hpp"

    /**
     * Fill the buffer from the input
     */ 
    void BitInputStream::fill()
    {
        buf = in.get();
        nbits = 0;
    }

    /**
     * Read the next bit from the bit buffer
     * Fill the buffer from the input stream first if needed
     * Return 1 if the bit read is 1;
     * Return 0 if the bit read is 0.
     */ 
    int BitInputStream::readBit()
    {
        //if all bits in the buffer are read, fill the buffer first
        if(nbits == 8)
        {
            fill();
        }

        //get the bit at the appriopriate location in the bit buffer,
        //and return the appropriate int
        int readB = (buf >> (7 - nbits)) & (0x01);
        
        //increment the index
        nbits++;

        //return the bit
        return readB;
    }
