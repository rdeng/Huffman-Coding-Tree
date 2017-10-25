/**
 * Name: Rui Deng
 *       Dadong Jing
 * Data: Jan 28, 2016
 * Overview: this file is to implement basic functionality of HCNode
 * Assignment number: PA2
 */

#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other)
{
    //when there's a difference between the counts, then lower count has
    //higher priority
    if(count != other.count)
        return count > other.count;
    //when the counts are the same, break the tie
    else
        return symbol < other.symbol;
}


