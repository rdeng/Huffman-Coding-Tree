/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to declare all properties for BitOutputStream.
 * It can write a bit to file using the build in ostream for C++.
 * Assignment number: PA2
 */

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

/**
 * A class to write bit to file
 */
class BitOutputStream {

private:
    char buf;           //one byte buffer of bits
    int nbits;          //how many bits have been written to buf
    std::ostream & out; //reference to the output stream to use

public:

    /**
     * Initialize a BitOutputStream that will use
     * the given ostream for output
     */ 
    BitOutputStream(std::ostream & os) : out(os),buf(0),nbits(0)
    {
        //clear buffer and bit counter
    }

    /** write the least significant bit to buffer */
    void writeBit(int i);

    /** send the buffer to the output, and clear it */
    void flush();
};
#endif //BITOUTPUTSTREAM_HPP
    
