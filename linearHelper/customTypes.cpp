//
//  customTypes.cpp
//  linearHelper
//
//  Created by Эльдар Дамиров on 10.02.2020.
//  Copyright © 2020 Эльдар Дамиров. All rights reserved.
//

#include <stdio.h>
#include <cmath>
#include <numeric>

// ------------- FRACTION;
template <typename typeOfData>
class Fraction {
    public:
        void simplify();
    private:
        typeOfData numerator{}, denominator{};
};


template <typename typeOfData>
void Fraction<typeOfData>::simplify() {
    typeOfData scale = std::gcd(numerator, denominator);
    
    numerator /= scale;
    denominator /= scale;
}
// ------------- FRACTION;


