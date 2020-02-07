//
//  main.cpp
//  linearHelper
//
//  Created by Эльдар Дамиров on 07.02.2020.
//  Copyright © 2020 Эльдар Дамиров. All rights reserved.
//

#include "matrixCruncher.cpp"

int main() {
    std::vector<std::vector<int>> temp{{1, 2, 3}, {4, 5, 6}};
    Matrix2D<int> myMatrix(temp);
    
    myMatrix.consoleLatex();

    return 0;
}
