//
//  main.cpp
//  linearHelper
//
//  Created by Эльдар Дамиров on 07.02.2020.
//  Copyright © 2020 Эльдар Дамиров. All rights reserved.
//

#include "matrixCruncher.cpp"

int main() {
    auto t1 = Matrix2D<int>({{-1, -5, 7, 1, 0, 0, 0, 0}, {0, 7, -15, 0, 1, 0, 0, 0}, {-7, 5, -13,
        0, 0, 1, 0, 0}, {-4, -9, -13, 0, 0, 0, 1, 0}, {-14, -11, -14, 0, 0, 0, 0, 1}});

    int operationId{}, rowId1{}, rowId2{}, scale{};
    while (1) {
        std::cin >> operationId;
        if (operationId == 0) {
            std::cin >> rowId1 >> scale;
            t1.scaleRow(rowId1, scale);
        }
        if (operationId == 1) {
            std::cin >> rowId1 >> rowId2 >> scale;
            t1.addOtherRow(rowId1, rowId2, scale);
        }


        std::cout << t1;
    }
//    std::vector<std::vector<int>> temp{{1, 2, 3, 0}, {0, 4, 5, 6}};
//    Matrix2D<int> myMatrix(temp);
//    myMatrix.selfTranspose();
//    myMatrix.consoleLatex();
//    myMatrix = myMatrix + Matrix2D<int>({{1,1,1,1}, {1,1,1,1}});
//    myMatrix.consoleLatex();

    return 0;
}
