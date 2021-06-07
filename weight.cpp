#include "weight.h"

Weight::Weight()
{

}
Weight::Weight(int weightNumber)
{
    this->weightNumber=weightNumber;
}
int Weight::getWeightNumber()
{
    return this->weightNumber;
}
