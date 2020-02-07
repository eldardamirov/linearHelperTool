//
//  matrixCruncher.cpp
//  linearHelper
//
//  Created by Эльдар Дамиров on 07.02.2020.
//  Copyright © 2020 Эльдар Дамиров. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>



template <typename cellDataType>
class Matrix2D {
    public:
        Matrix2D(size_t sizeXT, size_t sizeYT); // construct blank Matrix2D;
        Matrix2D(std::vector<cellDataType> singleSequence, bool mode = true); // mode = true - init as column, false - as row;
        Matrix2D(std::vector<std::vector<cellDataType>> storageT); // construct matrix from 2D vector;
        Matrix2D(const Matrix2D& matrixToInitFrom);

        ~Matrix2D();

        // --------------- setters & getters ---------------
        size_t getSizeX();
        size_t getSizeY();

        void setSizeX(size_t newSizeX);
        void setSizeY(size_t newSizeY);

        cellDataType getCellValue(size_t locationY, size_t locationX);
        std::vector<cellDataType> getRow(size_t rowId);
        std::vector<cellDataType> getColumn(size_t columnId);

        void setCellValue(size_t positionY, size_t positionX, cellDataType newValue);
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

        // --------------- output ---------------
        void consoleLatex();
        std::string latex();

    private:
        size_t sizeX{}, sizeY{};
        std::vector<std::vector<cellDataType>> storage{};
};


// ---------------
// ---------------

template <typename cellDataType>
Matrix2D<cellDataType>::Matrix2D(size_t sizeXT, size_t sizeYT) {
    sizeX = sizeXT;
    sizeY = sizeYT;
}

template <typename cellDataType>
Matrix2D<cellDataType>::Matrix2D(std::vector<cellDataType> singleSequence, bool mode) { // mode = true - init as column, false - as row;
    if (mode == true) {
        sizeX = 1;
        sizeY = singleSequence.size();

        storage.resize(singleSequence.size());
        for (size_t i{}; i < singleSequence.size(); ++i) {
            storage[i].push_back(singleSequence[i]);
        }
    } else {
        sizeX = singleSequence.size();
        sizeY = 1;

        storage.push_back(std::vector<cellDataType>());
        for (size_t i{}; i < singleSequence.size(); ++i) {
            storage[0].push_back(singleSequence[i]);
        }

    }
}

template <typename cellDataType>
Matrix2D<cellDataType>::Matrix2D(std::vector<std::vector<cellDataType>> storageT) { // construct matrix from 2D vector;
    storage = storageT;

    if (!storageT.empty()) {
        sizeX = storageT[0].size();
    }

    sizeY = storage.size();
}

template <typename cellDataType>
Matrix2D<cellDataType>::Matrix2D(const Matrix2D& matrixToInitFrom) {
    storage = matrixToInitFrom.storage;

    sizeX = matrixToInitFrom.sizeX;
    sizeY = matrixToInitFrom.sizeY;
}


// ---------------
// ---------------

template <typename cellDataType>
size_t Matrix2D<cellDataType>::getSizeX() {
    return sizeX;
}

template <typename cellDataType>
size_t Matrix2D<cellDataType>::getSizeY() {
    return sizeY;
}

template <typename cellDataType>
void Matrix2D<cellDataType>::setSizeX(size_t newSizeX) {
    sizeX = newSizeX;
}

template <typename cellDataType>
void Matrix2D<cellDataType>::setSizeY(size_t newSizeY) {
    sizeY = newSizeY;
}

template <typename cellDataType>
cellDataType Matrix2D<cellDataType>::getCellValue(size_t locationY, size_t locationX) {
    return storage[locationY][locationX];
}

template <typename cellDataType>
std::vector<cellDataType> Matrix2D<cellDataType>::getRow(size_t rowId) {
    return storage[rowId];
}

template <typename cellDataType>
std::vector<cellDataType> Matrix2D<cellDataType>::getColumn(size_t columnId) {
    std::vector<cellDataType> resultColumn;
    resultColumn.reserve(sizeY);
    for (const auto& current : storage) {
        resultColumn.push_back(current[columnId]);
    }

    return resultColumn;
}

template <typename cellDataType>
void  Matrix2D<cellDataType>::setCellValue(size_t positionY, size_t positionX, cellDataType newValue) {
    storage[positionY][positionX] = newValue;
}

template <typename cellDataType>
void Matrix2D<cellDataType>::setRow(size_t rowId, std::vector<cellDataType> newRow) {
    storage[rowId] = newRow;
}

template <typename cellDataType>
void Matrix2D<cellDataType>::setColumn(size_t columnId, std::vector<cellDataType> newColumn) {
    for (size_t i{}; i < sizeY; ++i) {
        storage[i][columnId] = newColumn[i];
    }
}

// ---------------
// ---------------














