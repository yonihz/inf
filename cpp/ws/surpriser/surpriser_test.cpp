#include "surpriser.hpp"

using namespace ilrd;

int main()
{
    Surpriser *todaySurprise = Surpriser::GetRandomSurprise();

    todaySurprise->SurpriseMe();
}