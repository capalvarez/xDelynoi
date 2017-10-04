#ifndef XDELYNOI_GREATER_H
#define XDELYNOI_GREATER_H

struct greater{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

#endif