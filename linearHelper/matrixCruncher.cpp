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
#include <iostream>

#define borderLineDefaultPosition 3

//#define LOG_OPERATIONS




template <typename cellDataType>
class Matrix2D {
    public:
        Matrix2D(size_t sizeXT, size_t sizeYT); // construct blank Matrix2D;
        Matrix2D(std::vector<cellDataType> singleSequence, bool mode = true); // mode = true - init as column, false - as row;
        Matrix2D(std::vector<std::vector<cellDataType>> storageT); // construct matrix from 2D vector;
        Matrix2D(const Matrix2D& matrixToInitFrom); // construct matrix from another matrix;

//        ~Matrix2D();

        // --------------- setters & getters ---------------
        size_t getSizeX() const;
        size_t getSizeY() const;

        void setSizeX(size_t newSizeX);
        void setSizeY(size_t newSizeY);

        cellDataType getCellValue(size_t locationY, size_t locationX);
        std::vector<cellDataType> getRow(size_t rowId);
        std::vector<cellDataType> getColumn(size_t columnId);

        void setCellValue(size_t positionY, size_t positionX, cellDataType newValue);
        void setRow(size_t rowId, std::vector<cellDataType> newRow);
        void setColumn(size_t columnId, std::vector<cellDataType> newColumn);

        void resizeMatrix(size_t sizeYT, size_t sizeXT);

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

        // --------------- output & input ---------------
        void consoleLatex(size_t borderLine = borderLineDefaultPosition);
        std::string latex(size_t borderLine = borderLineDefaultPosition) const;

    #ifdef LOG_OPERATIONS
        void eraseBuffer();
    #endif

    private:
        size_t sizeX{}, sizeY{};
        std::vector<std::vector<cellDataType>> storage{};

    #ifdef LOG_OPERATIONS
        std::string output{};
    #endif


};


// ---------------
// ---------------

template <typename cellDataType>
Matrix2D<cellDataType>::Matrix2D(size_t sizeXT, size_t sizeYT) {
    sizeX = sizeXT;
    sizeY = sizeYT;

    storage.resize(sizeYT);
    for (auto& currentLine : storage) {
        currentLine.reserve(sizeXT);
    }
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

template <typename cellDataType>
void Matrix2D<cellDataType>::resizeMatrix(size_t sizeYT, size_t sizeXT) {
    storage.clear();
    storage.resize(sizeYT);
    for (auto& currentLine : storage) {
        currentLine.resize(sizeXT);
    }

    sizeX = sizeXT;
    sizeY = sizeYT;
}

// ---------------
// ---------------

template <typename cellDataType>
size_t Matrix2D<cellDataType>::getSizeX() const {
    return sizeX;
}

template <typename cellDataType>
size_t Matrix2D<cellDataType>::getSizeY() const {
    return sizeY;
}

template <typename cellDataType>
void Matrix2D<cellDataType>::setSizeX (size_t newSizeX) {
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
void Matrix2D<cellDataType>::setCellValue(size_t positionY, size_t positionX, cellDataType newValue) {
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

template <typename cellDataType>
std::vector<std::vector<cellDataType>> Matrix2D<cellDataType>::getTransposed() {
    if (storage.empty()) {
        return std::vector<std::vector<cellDataType>>(0);
        }

    std::vector<std::vector<cellDataType>> result(storage[0].size(), std::vector<cellDataType>(storage.size()));
    for (size_t i{}; i < storage.size(); ++i) {
        for (size_t j{}; j < storage[0].size(); ++j) {
            result[j][i] = storage[i][j];
        }
    }

    std::swap(sizeX, sizeY);

    return result;
}

template <typename cellDataType>
std::vector<std::vector<cellDataType>> Matrix2D<cellDataType>::getInversed() {
    // TODO
}

template <typename cellDataType>
std::vector<std::vector<cellDataType>> Matrix2D<cellDataType>::getRowEchelonForm() {
    // TODO
}

template <typename cellDataType>
std::vector<std::vector<cellDataType>> Matrix2D<cellDataType>::getEnchancedRowEchelonForm() {
    // TODO
}

// ---------------
// ---------------

template <typename cellDataType>
void Matrix2D<cellDataType>::selfTranspose() {
    storage = getTransposed();
}

template <typename cellDataType>
void Matrix2D<cellDataType>::selfInverse() {
    storage = getInversed();
}

template <typename cellDataType>
void Matrix2D<cellDataType>::selfRowEchelonForm() {
    storage = getRowEchelonForm();
}

template <typename cellDataType>
void Matrix2D<cellDataType>::selfEnchancedRowEchelonForm() {
    storage = getEnchancedRowEchelonForm();
}

// ---------------
// ---------------



// ---------------
// ---------------

template <typename cellDataType>
Matrix2D<cellDataType>& Matrix2D<cellDataType>::operator+ (const Matrix2D& matrixToOperateWith) {
    std::vector<std::vector<cellDataType>> result(std::max(sizeY, matrixToOperateWith.getSizeY()), std::vector<cellDataType>(std::max(sizeX, matrixToOperateWith.getSizeX())));

    for (size_t i{}; i < std::min(sizeY, matrixToOperateWith.getSizeY()); ++i) {
        for (size_t j{}; j < std::min(sizeX, matrixToOperateWith.getSizeX()); ++j) {
            result[i][j] = storage[i][j] + matrixToOperateWith.storage[i][j];
        }
    }

    Matrix2D<cellDataType>* tempMatrix = new Matrix2D<cellDataType>(result);
    tempMatrix->setSizeX(std::max(sizeX, matrixToOperateWith.getSizeX()));
    tempMatrix->setSizeY(std::max(sizeY, matrixToOperateWith.getSizeY()));

    return *tempMatrix;
}

template <typename cellDataType>
Matrix2D<cellDataType>& Matrix2D<cellDataType>::operator* (const Matrix2D& matrixToOperateWith) {
    std::vector<std::vector<cellDataType>> result(std::max(sizeY, matrixToOperateWith.getSizeY()), std::vector<cellDataType>(std::max(sizeX, matrixToOperateWith.getSizeX())));

    for (size_t i{}; i < std::min(sizeY, matrixToOperateWith.getSizeY()); ++i) {
        for (size_t j{}; j < std::min(sizeX, matrixToOperateWith.getSizeX()); ++j) {
            result[i][j] = storage[i][j] * matrixToOperateWith.storage[i][j];
        }
    }

    Matrix2D<cellDataType>* tempMatrix = new Matrix2D<cellDataType>(result);
    tempMatrix->setSizeX(std::max(sizeX, matrixToOperateWith.getSizeX()));
    tempMatrix->setSizeY(std::max(sizeY, matrixToOperateWith.getSizeY()));

    return *tempMatrix;
}

template <typename cellDataType>
Matrix2D<cellDataType>& Matrix2D<cellDataType>::operator- (const Matrix2D& matrixToOperateWith) {
    std::vector<std::vector<cellDataType>> result(std::max(sizeY, matrixToOperateWith.getSizeY()), std::vector<cellDataType>(std::max(sizeX, matrixToOperateWith.getSizeX())));

    for (size_t i{}; i < std::min(sizeY, matrixToOperateWith.getSizeY()); ++i) {
        for (size_t j{}; j < std::min(sizeX, matrixToOperateWith.getSizeX()); ++j) {
            result[i][j] = storage[i][j] - matrixToOperateWith.storage[i][j];
        }
    }

    Matrix2D<cellDataType>* tempMatrix = new Matrix2D<cellDataType>(result);
    tempMatrix->setSizeX(std::max(sizeX, matrixToOperateWith.getSizeX()));
    tempMatrix->setSizeY(std::max(sizeY, matrixToOperateWith.getSizeY()));

    return *tempMatrix;
}

template <typename cellDataType>
Matrix2D<cellDataType>& Matrix2D<cellDataType>::operator/ (const Matrix2D& matrixToOperateWith) {
    std::vector<std::vector<cellDataType>> result(std::max(sizeY, matrixToOperateWith.getSizeY()), std::vector<cellDataType>(std::max(sizeX, matrixToOperateWith.getSizeX())));

    for (size_t i{}; i < std::min(sizeY, matrixToOperateWith.getSizeY()); ++i) {
        for (size_t j{}; j < std::min(sizeX, matrixToOperateWith.getSizeX()); ++j) {
            result[i][j] = storage[i][j] / matrixToOperateWith.storage[i][j];
        }
    }

    Matrix2D<cellDataType>* tempMatrix = new Matrix2D<cellDataType>(result);
    tempMatrix->setSizeX(std::max(sizeX, matrixToOperateWith.getSizeX()));
    tempMatrix->setSizeY(std::max(sizeY, matrixToOperateWith.getSizeY()));

    return *tempMatrix;
}

// ---------------
// ---------------

template <typename cellDataType>
void Matrix2D<cellDataType>::consoleLatex(size_t borderLine) {
    std::cout << "\\begin{pmatrix}" << '\n';
    for (size_t i{}; i < storage.size(); ++i) {
        for (size_t j{}; j < storage[0].size(); ++j) {
            std::cout << storage[i][j];

            if (j < storage[0].size() - 1) {
                if ((j + 1) == borderLine) {
                    std::cout << "&\\aug&";
                } else {
                    std::cout << "&";
                }
            }
        }
        std::cout << "\\\\ \n";
    }
    std::cout << "\\end{pmatrix}" << '\n';

#ifdef LOG_OPERATIONS
    std::cout << output;
#endif
}

template <typename cellDataType>
std::string Matrix2D<cellDataType>::latex(size_t borderLine) const {
    std::string result{};

    result += "\\begin{pmatrix}\n";
    for (size_t i{}; i < storage.size(); ++i) {
        for (size_t j{}; j < storage[0].size(); ++j) {
            result += std::to_string(storage[i][j]);

            if (j < storage[0].size() - 1) {
                if ((j + 1) == borderLine) {
                    result += "&\\aug&";
                } else {
                    result += "&";
                }
            }
        }
        result += "\\\\ \n";
    }
    result += "\\end{pmatrix}\n";

#ifdef LOG_OPERATIONS
    result += output;
#endif

    return result;
}

#ifdef LOG_OPERATIONS
    template <typename cellDataType>
    void Matrix2D<cellDataType>::eraseBuffer() {
        output = "";
    }
#endif

template <typename cellDataType>
std::ostream& operator<< (std::ostream& outputPipe, const Matrix2D<cellDataType> toOutput) {
    outputPipe << toOutput.latex();

    return outputPipe;
}

template <typename cellDataType>
std::istream& operator>> (std::istream& inputPipe, Matrix2D<cellDataType>& toInput) {

    size_t sizeXT{}, sizeYT{};
    inputPipe >> sizeXT >> sizeYT;

    toInput.resizeMatrix(sizeYT, sizeXT);
    cellDataType currentInput{};

    for (size_t i{}; i < sizeYT; ++i) {
        for (size_t j{}; j < sizeXT; ++j) {
            std::cin >> currentInput;
            toInput.setCellValue(i, j, currentInput);
        }
    }

    return inputPipe;
}

// ---------------
// ---------------

