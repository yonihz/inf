#ifndef _ILRD_RD743_SURPRISER_HPP_
#define _ILRD_RD743_SURPRISER_HPP_

#include <iostream>
#include <fstream>
#include <cstdlib>      /* srand, rand */
#include <ctime>        /* time */

#define NSURPRISES 3

namespace ilrd
{

class Surpriser
{
public:
    Surpriser();
    virtual ~Surpriser();
    
    static Surpriser *GetRandomSurprise();
    
    virtual void SurpriseMe() const;
};

class SurpriserD1: public Surpriser
{
public:
    SurpriserD1() {};
    
    ~SurpriserD1() {};

    void SurpriseMe() const;

    static SurpriserD1 s_surprise;
};

class SurpriserD2: public Surpriser
{
public:
    SurpriserD2() {};
    
    ~SurpriserD2() {};

    void SurpriseMe() const;

    static SurpriserD2 s_surprise;
};

class SurpriserD3: public Surpriser
{
public:
    SurpriserD3() {};
    
    ~SurpriserD3() {};

    void SurpriseMe() const;

    static SurpriserD3 s_surprise;
};

}
#endif // _ILRD_RD743_SURPRISER_HPP_

