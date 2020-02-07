//
//  matrixCruncher.hpp
//  linearHelper
//
//  Created by Эльдар Дамиров on 07.02.2020.
//  Copyright © 2020 Эльдар Дамиров. All rights reserved.
//

#ifndef matrixCruncher_hpp
#define matrixCruncher_hpp

#include <stdio.h>
#include <vector>


template <typename cellDataType>
class Matrix2D {
    public:
        Matrix2D(size_t sizeXT, size_t sizeYT); // construct blank Matrix2D;
        Matrix2D(std::vector<cellDataType> singleSequence, bool mode = true); // mode = true - init as column, false - as row;
        Matrix2D(std::vector<std::vector<cellDataType>> storageT); // construct matrix from 2D vector;

        ~Matrix2D();

        // --------------- setters & getters ---------------
        size_t getDimensionX();
        size_t getDimensionY();

        void setDimensionX();
        void setDimensionY();

        cellDataType getCellValue(size_t locationY, size_t locationX);
        std::vector<cellDataType> getRow(size_t rowId);
        std::vector<cellDataType> getColumn(size_t columnId);

        void setCellValue(cellDataType newValue);
        void setRow(size_t rowId, std::vector<cellDataType> newRow);
        void setColumn(size_t columnId, std::vector<cellDataType> newColumn);

        // --------------- basic transformations ---------------
        void selfTranspose();
        void selfInverse();
        void selfRowEchelonForm();
        void selfEnchancedRowEchelonForm();

        std::vector<std::vector<cellDataType>> getTransposed();
        std::vector<std::vector<cellDataType>> getInversed();
        std::vector<std::vector<cellDataType>> getRowEchelonForm();
        std::vector<std::vector<cellDataType>> getEnchancedRowEchelonForm();

        // --------------- binary operations ---------------
        Matrix2D& operator+ (const Matrix2D& matrixToOperateWith);
        Matrix2D& operator* (const Matrix2D& matrixToOperateWith);
        Matrix2D& operator- (const Matrix2D& matrixToOperateWith);
        Matrix2D& operator/ (const Matrix2D& matrixToOperateWith);

        Matrix2D& product (const Matrix2D& matrixToOperateWith);

    private:
        size_t sizeX{}, sizeY{};
        std::vector<std::vector<cellDataType>> storage{};
};


#endif /* matrixCruncher_hpp */
