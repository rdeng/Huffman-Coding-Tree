/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to declare all properties for BitInputStream.
 * It can read a bit from file using the build in istream for C++.
 * Assignment number: PA2
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

/**
 * A class to read bit from file
 */
class BitInputStream {

private:
    char buf;           //one byte buffer of bits
    int nbits;          //how many bits have been read from buf
    std::istream & in;  //the input stream to use

public:

    /**
     * Initialize a BitInputStream that will use the given istream for input.
     */ 
    BitInputStream(std::istream & is) : in(is)
    {
        buf = 0;
        nbits = 8;
    }

    /** fill the buffer from the input*/
    void fill();

    /** read the next bit from the bit buffer */
    int readBit();

    
};
#endif // BITINPUTSTREAM_HPP
    
