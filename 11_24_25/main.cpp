// Module 5 Part A Lab Activity
// Student: Ogar Samuel
// Functions: inputDrinkBase() and inputDrinkTemp()

#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <algorithm>
#include "clock.h"
#include "drink.h"

// M05 part a lab fill in inputDrinkBase and inputDrinkTemp

template <class Type>
Type inputType(std::string prompt, std::string err, bool (*valid)(Type, Type, Type), Type low = 0, Type high = 0);

template <class Type>
bool itemGT(Type item, Type low, Type = 0);
template <class Type>
bool itemInRange(Type item, Type low, Type high);
template <class Type>
bool isAorB(Type item, Type a, Type b);

void resetStream();

sizeType inputDrinkSize();
void addFlavorToDrink(drink &thedrink);

// Lab function prototypes
baseType inputDrinkBase();
tempType inputDrinkTemp();

int main()
{
    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<int> twelveHrDist(1, 12);
    std::uniform_int_distribution<int> minSecDist(0, 59);
    std::uniform_int_distribution<int> partDistribution(partType::AM, partType::PM);
    TwelveHrClock randomClock(twelveHrDist(generator), minSecDist(generator), minSecDist(generator), partDistribution(generator) == 0 ? partType::AM : partType::PM);
    std::cout << randomClock << std::endl;
    std::vector<clockType *> vector1;
    // std::vector<clockType *> vector2(10);

    for (int i = 0; i < 10; i++)
    {
        clockType *c = new TwelveHrClock(twelveHrDist(generator), minSecDist(generator), minSecDist(generator), partDistribution(generator) == 0 ? partType::AM : partType::PM);
        vector1.push_back(c);
        // vector2.push_back(c);
    }

    for (int i = 0; i < vector1.size(); i++)
    {
        std::cout << *(vector1[i]) << std::endl;
    }
    for (std::vector<clockType *>::reverse_iterator it = vector1.rbegin(); it != vector1.rend(); ++it)
    {
        std::cout << *(*it) << std::endl;
    }
    sizeType s = inputDrinkSize();
    drink myDrink(COFFEE, ICE, s);
    /*  myDrink.addFlavor(APPLE);
     myDrink.addFlavor(BLUEBERRY);
     myDrink.addFlavor(MANGO);
     myDrink.addFlavor(APPLE);
     myDrink.addFlavor(STRAWBERRY); */
    addFlavorToDrink(myDrink);
    std::cout << myDrink << std::endl;

    TwelveHrClock a = inputType<TwelveHrClock>("Enter the clock data.", "That is not a valid clock", itemGT, TwelveHrClock(10, 0, 0, partType::AM), TwelveHrClock(1, 0, 0, partType::PM));
    std::cout << a << std::endl;
    int num = inputType<int>("Enter a number between 1 and 100: ", "That is not a number between 1 and 100", itemInRange, 1, 100);
    return 0;
}

bool numGTEQX(int num, int x, int)
{
    return num >= x;
}

bool isAorB(int num, int a, int b)
{
    return num == a || num == b;
}

template <class Type>
Type inputType(std::string prompt, std::string err, bool (*valid)(Type, Type, Type), Type low, Type high)
{
    Type item;
    std::cout << prompt;
    std::cin >> item;
    while (!std::cin || !valid(item, low, high))
    {
        if (!std::cin)
        {
            resetStream();
        }

        std::cout << err << std::endl;
        std::cout << prompt;
        std::cin >> item;
    }
    return item;
}

template <class Type>
bool itemGT(Type item, Type low, Type)
{
    return item > low;
}

template <class Type>
bool itemInRange(Type item, Type low, Type high)
{
    return low <= item && high >= item;
}

void resetStream()
{
    std::cout << "You have entered non-numeric data! Please try again!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

sizeType inputDrinkSize()
{
    std::string sizeStr;
    std::cout << "Please enter the drink size: ";
    std::cin >> sizeStr;
    transform(sizeStr.begin(), sizeStr.end(), sizeStr.begin(), ::toupper);
    while (!drink::strToSize.count(sizeStr))
    {
        std::cout << "That is not a valid size." << std::endl;
        std::cout << "Valid sizes are: ";
        auto it = drink::sizeToStr.begin();
        std::cout << it->second;
        for (++it; it != drink::sizeToStr.end(); ++it)
        {
            std::cout << ", " << it->second;
        }
        std::cout << std::endl;
        std::cout << "Please enter the drink size: ";
        std::cin >> sizeStr;
        transform(sizeStr.begin(), sizeStr.end(), sizeStr.begin(), ::toupper);
    }
    return drink::strToSize[sizeStr];
}

void addFlavorToDrink(drink &thedrink)
{
    std::string flavStr;
    while (flavStr != "-1")
    {
        std::cout << "Please enter a flavor enter -1 to stop: ";
        getline(std::cin >> std::ws, flavStr);
        if (flavStr == "-1")
        {
            return;
        }
        transform(flavStr.begin(), flavStr.end(), flavStr.begin(), ::tolower);
        while (!drink::strToFlav.count(flavStr))
        {
            std::cout << "That is not a valid flavor." << std::endl;
            std::cout << "Valid flavors are: ";
            auto it = drink::flavToStr.begin();
            std::cout << it->second;
            for (++it; it != drink::flavToStr.end(); ++it)
            {
                std::cout << ", " << it->second;
            }
            std::cout << std::endl;
            std::cout << "Please enter the drink flavor or enter -1 to stop: ";
            std::cin >> flavStr;
            if (flavStr == "-1")
            {
                return;
            }
            transform(flavStr.begin(), flavStr.end(), flavStr.begin(), ::tolower);
        }
        thedrink.addFlavor(drink::strToFlav[flavStr]);
    }
}

// =============================================================================
// LAB FUNCTIONS - Ogar Samuel
// =============================================================================

// Function: inputDrinkBase()
// Purpose: Get and validate drink base input from user
baseType inputDrinkBase()
{
    std::string baseStr;
    std::cout << "Please enter the drink base: ";
    std::cin >> baseStr;
    
    // Transform to uppercase for case-insensitive comparison
    transform(baseStr.begin(), baseStr.end(), baseStr.begin(), ::toupper);
    
    // Loop while input is not valid
    while (!drink::strToBase.count(baseStr))
    {
        std::cout << "That is not a valid base." << std::endl;
        std::cout << "Valid bases are: ";
        
        // Use iterator to display all valid options
        auto it = drink::baseToStr.begin();
        std::cout << it->second;
        
        for (++it; it != drink::baseToStr.end(); ++it)
        {
            std::cout << ", " << it->second;
        }
        std::cout << std::endl;
        
        std::cout << "Please enter the drink base: ";
        std::cin >> baseStr;
        transform(baseStr.begin(), baseStr.end(), baseStr.begin(), ::toupper);
    }
    
    // Return the enum value from the map
    return drink::strToBase[baseStr];
}

// Function: inputDrinkTemp()
// Purpose: Get and validate drink temperature input from user
tempType inputDrinkTemp()
{
    std::string tempStr;
    std::cout << "Please enter the drink temperature: ";
    std::cin >> tempStr;
    
    // Transform to uppercase for case-insensitive comparison
    transform(tempStr.begin(), tempStr.end(), tempStr.begin(), ::toupper);
    
    // Loop while input is not valid
    while (!drink::strToTemp.count(tempStr))
    {
        std::cout << "That is not a valid temperature." << std::endl;
        std::cout << "Valid temperatures are: ";
        
        // Use iterator to display all valid options
        auto it = drink::tempToStr.begin();
        std::cout << it->second;
        
        for (++it; it != drink::tempToStr.end(); ++it)
        {
            std::cout << ", " << it->second;
        }
        std::cout << std::endl;
        
        std::cout << "Please enter the drink temperature: ";
        std::cin >> tempStr;
        transform(tempStr.begin(), tempStr.end(), tempStr.begin(), ::toupper);
    }
    
    // Return the enum value from the map
    return drink::strToTemp[tempStr];
}
