//
//  main.cpp
//  linearHelper
//
//  Created by Эльдар Дамиров on 07.02.2020.
//  Copyright © 2020 Эльдар Дамиров. All rights reserved.
//

#include "matrixCruncher.cpp"
#include <numeric>

int main() {
    auto t1 = Matrix2D<int>({{1,-2,-1,-2},{1,2,1,6},{-3,-5,-2,-15}});

    std::cout << t1;
    std::cout << "\\longrightarrow \n";
    int operationId{}, rowId1{}, rowId2{}, scale{};
    for (size_t i{}; i < 3; ++i) {
        for (size_t j{}; j < 3; ++j) {
            if (j != i) {
                if (t1.getCellValue(j, i) != 0) {
                    int scale = std::lcm(t1.getCellValue(j, i), t1.getCellValue(i, i)) / t1.getCellValue(j, i);
                    t1.scaleRow(j, scale);
                    std::cout << t1;
                    std::cout << "\\longrightarrow \n";
                    t1.addOtherRow(j, i, -std::lcm(t1.getCellValue(j, i), t1.getCellValue(i, i)) / t1.getCellValue(i, i));
                    std::cout << t1;
                    std::cout << "\\longrightarrow \n";
                }
            }
        }

    }
//    while (1) {
//        std::cin >> operationId;
//        if (operationId == 0) {
//            std::cin >> rowId1 >> scale;
//            t1.scaleRow(rowId1, scale);
//        }
//        if (operationId == 1) {
//            std::cin >> rowId1 >> rowId2 >> scale;
//            t1.addOtherRow(rowId1, rowId2, scale);
//        }
//        if (operationId == 2) {
//            std::cin >> rowId1 >> rowId2;
//            t1.swapRows(rowId1, rowId2);
//        }
//
//        std::cout << t1;
//    }
//    std::vector<std::vector<int>> temp{{1, 2, 3, 0}, {0, 4, 5, 6}};
//    Matrix2D<int> myMatrix(temp);
//    myMatrix.selfTranspose();
//    myMatrix.consoleLatex();
//    myMatrix = myMatrix + Matrix2D<int>({{1,1,1,1}, {1,1,1,1}});
//    myMatrix.consoleLatex();

    return 0;
}
