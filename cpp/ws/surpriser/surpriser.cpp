#include "surpriser.hpp"

namespace ilrd
{

static int InitRand();

SurpriserD1 SurpriserD1::s_surprise;
SurpriserD2 SurpriserD2::s_surprise;
SurpriserD3 SurpriserD3::s_surprise;

Surpriser::Surpriser()
{
}

Surpriser::~Surpriser()
{
}

Surpriser *Surpriser::GetRandomSurprise()
{
    switch (InitRand())
    {
        case 0:
        {
            return &SurpriserD1::s_surprise;
        }
        case 1:
        {
            return &SurpriserD2::s_surprise;
        }
        case 2:
        {
            return &SurpriserD3::s_surprise;
        }
        default:
        {
            return &SurpriserD1::s_surprise;
        }
    }
}

void Surpriser::SurpriseMe() const
{

}

void SurpriserD1::SurpriseMe() const
{
    std::cout << "Surprise!" << std::endl;
}

void SurpriserD2::SurpriseMe() const
{
    system("echo '\\a'");
}

void SurpriserD3::SurpriseMe() const
{
  std::ofstream ofs;
  ofs.open ("nothing_here.txt", std::ofstream::out | std::ofstream::app);
  ofs.close();
}

static int InitRand()
{
    srand(time(NULL));
    return(rand() % NSURPRISES + 0);
}

}