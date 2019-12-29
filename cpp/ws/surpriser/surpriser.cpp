#include "surpriser.hpp"

namespace ilrd
{

static int InitRand();

Surpriser Surpriser::m_surprise;
Surpriser SurpriserD1::m_surprise;
Surpriser SurpriserD2::m_surprise;
Surpriser SurpriserD3::m_surprise;

Surpriser::Surpriser()
{
}

Surpriser::~Surpriser()
{
}

Surpriser *Surpriser::GetRandomSurprise()
{
    return &m_surprise;
}

void Surpriser::SurpriseMe() const
{
    switch (InitRand())
    {
        case 0:
        {
            static_cast<SurpriserD1*>(&SurpriserD1::m_surprise)->Surprise();
            return;
        }
        case 1:
        {
            static_cast<SurpriserD2*>(&SurpriserD2::m_surprise)->Surprise();
            return;
        }
        case 2:
        {
            static_cast<SurpriserD3*>(&SurpriserD3::m_surprise)->Surprise();
            return;
        }
        default:
        {
            static_cast<SurpriserD1*>(&SurpriserD1::m_surprise)->Surprise();
            return;
        }
    }
}

void SurpriserD1::Surprise() const
{
    std::cout << "Surprise!" << std::endl;
}

void SurpriserD2::Surprise() const
{
    system("echo -e '\\a'");
}

void SurpriserD3::Surprise() const
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