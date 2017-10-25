/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to write bit to a file using the build in
 * ostream for C++.
 * Assignment number: PA2
 */

#include "BitOutputStream.hpp"

    /**
     * Write the least significant bit of the argument to the bit buffer,
     * and increment the bit buffer index. But flush the buffer first,
     * if it is full
     */ 
    void BitOutputStream::writeBit(int i)
    {
        //If the buffer is full, flush it
        if(nbits == 8)
        {
            flush();
        }

        //write the least significant bit of i into the buffer at the current
        //index
        int lsb = i & 1;
        buf = buf & ~(1<<(7-nbits));
        buf = buf | (lsb << (7-nbits));

        //increment the index
        nbits++;
    }


    /** send the buffer to the output, and clear it */
    void BitOutputStream::flush()
    {
        out.put(buf);
        out.flush();
        buf = nbits = 0;
    }
