#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class MatrixOperator {
public:
    static int** init(int sizeN, int sizeM) {
        int** matrix = new int* [sizeN];
        for (int i = 0; i < sizeN; i++) {
            matrix[i] = new int[sizeM];
        }
        return matrix;
    }
    static int** initWithZeros(int sizeN, int sizeM) {
        int** matrix = new int* [sizeN];
        for (int i = 0; i < sizeN; i++) {
            matrix[i] = new int[sizeM];
            for (int j = 0; j < sizeM; j++)
                matrix[i][j] = 0;
        }
        return matrix;
    }
    static int** initAndCopy(int** fromMatrix, int sizeN, int sizeM) {
        int** toMatrix = new int* [sizeN];
        for (int i = 0; i < sizeN; i++) {
            toMatrix[i] = new int[sizeM];
            for (int j = 0; j < sizeM; j++)
                toMatrix[i][j] = fromMatrix[i][j];
        }
        return toMatrix;
    }
    static int** initAndCopyWithShift(int** fromMatrix, int sizeN, int sizeM, int shiftI = 0, int shiftJ = 0) {
        int** toMatrix = new int* [sizeN];
        for (int i = 0; i < sizeN; i++) {
            toMatrix[i] = new int[sizeM];
            for (int j = 0; j < sizeM; j++) {
                toMatrix[i][j] = fromMatrix[i + shiftI][j + shiftJ];
            }
        }
        return toMatrix;
    }
    static void fillConsole(int** matrix, int sizeN, int sizeM) {
        for (int i = 0; i < sizeN; i++)
            for (int j = 0; j < sizeM; j++)
                cin >> matrix[i][j];
    }
    static void fillRnd(int** matrix, int sizeN, int sizeM) {
        for (int i = 0; i < sizeN; i++)
            for (int j = 0; j < sizeM; j++)
                matrix[i][j] = rand() % 10;
    }
    static void copy(int** toMatrix, int** fromMatrix, int sizeN, int sizeM) {
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeM; j++)
                toMatrix[i][j] = fromMatrix[i][j];
        }
    }
    static void print(int** matrix, int sizeN, int sizeM) {
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeM; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
    static void freeSpace(int** matrix, int sizeN) {
        for (int i = 0; i < sizeN; i++)
            delete [] matrix[i];
        delete [] matrix;
    }
};

class MatrixStrassenMultiplier{
public:
    int** multiply(){
        askUser();
        firstInit();

        cout << "\nМатрица 1\n\n";
        MatrixOperator::print(mainM1, mainM1_N, mainM1_M);
        cout << "\nМатрица 2\n\n";
        MatrixOperator::print(mainM2, main_M2_N, main_M2_M);

        calcSizedMatrices();

        cout << "Приведенные матрицы\n\n";
        cout << "Матрица 1\n\n";
        MatrixOperator::print(sizedM1, square, square);
        cout << "\nМатрица 2\n\n";
        MatrixOperator::print(sizedM2, square, square);

        calcSubmatrices();
        calcIntermediateMatrices();
        calcHelperMatirces();
        calcResultMatrix();

        cout << "\nРезультирующая матрица\n\n";
        MatrixOperator::print(resM2, resM2_N, resM2_M);

        int** ret = MatrixOperator::init(resM2_N,resM2_M);
        MatrixOperator::copy(ret, resM2, resM2_N, resM2_M);

        clean();

        return ret;
    }
    int** multiply(int** matrix1, int sizeN1, int sizeM1, int** matrix2, int sizeN2, int sizeM2){
        mainM1_N = sizeN1;
        mainM1_M = sizeM1;
        main_M2_N = sizeN2;
        main_M2_M = sizeM2;

        mainM1 = MatrixOperator::init(mainM1_N, mainM1_M);
        mainM2 = MatrixOperator::init(main_M2_N, main_M2_M);

        MatrixOperator::copy(mainM1, matrix1, mainM1_N, mainM1_M);
        MatrixOperator::copy(mainM2, matrix2, main_M2_N, main_M2_M);

        cout << "\nМатрица 1\n\n";
        MatrixOperator::print(mainM1, mainM1_N, mainM1_M);
        cout << "\nМатрица 2\n\n";
        MatrixOperator::print(mainM2, main_M2_N, main_M2_M);

        calcSizedMatrices();

        cout << "Приведенные матрицы\n\n";
        cout << "Матрица 1\n\n";
        MatrixOperator::print(sizedM1, square, square);
        cout << "\nМатрица 2\n\n";
        MatrixOperator::print(sizedM2, square, square);

        calcSubmatrices();
        calcIntermediateMatrices();
        calcHelperMatirces();
        calcResultMatrix();

        cout << "\nРезультирующая матрица\n\n";
        MatrixOperator::print(resM2, resM2_N, resM2_M);

        int** ret = MatrixOperator::init(resM2_N,resM2_M);
        MatrixOperator::copy(ret, resM2, resM2_N, resM2_M);

        clean();

        return ret;
    }
private:
    void askUser(){
        cout << "Вас приветствует программа\n"
            << "быстрого перемножения матриц методом Штрассена\n\n";

        //----------Ввод размеров матрицы пользователем----------//
        do {
            cout << "Введите размеры первой матрицы\n";
            cin >> mainM1_N >> mainM1_M;
        } while (mainM1_N <= 0 || mainM1_M <= 0);

        do {
            cout << "Введите размеры второй матрицы\n";
            cin >> main_M2_N >> main_M2_M;
        } while (main_M2_N <= 0 || main_M2_M <= 0);

        //----------Выбор способа заполнения матриц----------//
        do {
            cout << "Выберите способ заполнения матриц\n"
                << "1 - Вручную \n"
                << "2 - Случайным образом\n";

            cin >> fillMethod;
        } while (fillMethod < 1 || fillMethod > 2);
    }

    void firstInit(){
        //----------Заполнение матриц----------//
        mainM1 = MatrixOperator::init(mainM1_N, mainM1_M);
        mainM2 = MatrixOperator::init(mainM1_N, mainM1_M);

        switch (fillMethod) {
        case 1:
            MatrixOperator::fillConsole(mainM1, mainM1_N, mainM1_M);
            MatrixOperator::fillConsole(mainM2, main_M2_N, main_M2_M);

            break;
        case 2:
            MatrixOperator::fillRnd(mainM1, mainM1_N, mainM1_M);
            MatrixOperator::fillRnd(mainM2, main_M2_N, main_M2_M);

            break;
        }
    }

    void calcSizedMatrices(){
        //----------Приведение матриц к требуемому размеру----------//
        while (square < mainM1_N || square < main_M2_N || square < mainM1_M || square < main_M2_M)
            square *= 2;

        halfSquare = square / 2;

        sizedM1 = MatrixOperator::initWithZeros(square, square);
        sizedM2 = MatrixOperator::initWithZeros(square, square);

        MatrixOperator::copy(sizedM1, mainM1, mainM1_N, mainM1_M);
        MatrixOperator::copy(sizedM2, mainM2, main_M2_N, main_M2_M);
    }

    void calcSubmatrices(){
        //----------Разбиение матриц на подматрицы и их заполнение----------//
        subM1 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare);
        subM2 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare, 0, halfSquare);
        subM3 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare, halfSquare, 0);
        subM4 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare, halfSquare, halfSquare);

        subM5 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare);
        subM6 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare, 0, halfSquare);
        subM7 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare, halfSquare, 0);
        subM8 = MatrixOperator::initAndCopyWithShift(sizedM1, halfSquare, halfSquare, halfSquare, halfSquare);
    }

    void calcIntermediateMatrices(){
        //----------Создание промежуточных матриц----------//
        interM1 = MatrixOperator::init(halfSquare, halfSquare);
        interM2 = MatrixOperator::init(halfSquare, halfSquare);
        interM3 = MatrixOperator::init(halfSquare, halfSquare);
        interM4 = MatrixOperator::init(halfSquare, halfSquare);
        interM5 = MatrixOperator::init(halfSquare, halfSquare);
        interM6 = MatrixOperator::init(halfSquare, halfSquare);
        interM7 = MatrixOperator::init(halfSquare, halfSquare);

        //----------Вычисление значений промежуточных матриц----------//
        for (int i = 0; i < halfSquare; i++) {
            for (int j = 0; j < halfSquare; j++) {
                interM1[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM1[i][j] += (subM1[i][z] + subM4[i][z]) * (subM5[z][j] + subM8[z][j]);

                interM2[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM2[i][j] += (subM3[i][z] + subM4[i][z]) * subM5[z][j];

                interM3[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM3[i][j] += subM1[i][z] * (subM6[z][j] - subM8[z][j]);

                interM4[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM4[i][j] += subM4[i][z] * (subM7[z][j] - subM5[z][j]);

                interM5[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM5[i][j] += (subM1[i][z] + subM2[i][z]) * subM8[z][j];

                interM6[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM6[i][j] += (subM3[i][z] - subM1[i][z]) * (subM5[z][j] + subM6[z][j]);

                interM7[i][j] = 0;
                for (int z = 0; z < halfSquare; z++)
                    interM7[i][j] += (subM2[i][z] - subM4[i][z]) * (subM7[z][j] + subM8[z][j]);
            }
        }
    }

    void calcHelperMatirces(){
        //----------Создание вспомогательных матриц----------//
        helperM1 = MatrixOperator::init(halfSquare, halfSquare);
        helperM2 = MatrixOperator::init(halfSquare, halfSquare);
        helperM3 = MatrixOperator::init(halfSquare, halfSquare);
        helperM4 = MatrixOperator::init(halfSquare, halfSquare);

        //----------Подсчет значений вспомогательных матриц из промежуточных----------//
        for (int i = 0; i < halfSquare; i++)
        {
            for (int j = 0; j < halfSquare; j++)
            {
                helperM1[i][j] = interM1[i][j] + interM4[i][j] - interM5[i][j] + interM7[i][j];
                helperM2[i][j] = interM3[i][j] + interM5[i][j];
                helperM3[i][j] = interM2[i][j] + interM4[i][j];
                helperM4[i][j] = interM1[i][j] - interM2[i][j] + interM3[i][j] + interM6[i][j];
            }
        }
    }

    void calcResultMatrix(){
        //----------Создание результирующей матрицы----------//
        resM1 = MatrixOperator::init(square, square);

        //----------Занесение информации из вспомогательных матриц в результирующую----------//
        for (int i = 0; i < halfSquare; i++)
        {
            for (int j = 0; j < halfSquare; j++)
            {
                resM1[i][j] = helperM1[i][j];
                resM1[i][j + halfSquare] = helperM2[i][j];
                resM1[i + halfSquare][j] = helperM3[i][j];
                resM1[i + halfSquare][j + halfSquare] = helperM4[i][j];
            }
        }

        //----------Выравнивание границ результирующей матрицы----------//
        x = 0; resM2_N = 100; resM2_M = 100;

        for (int i = 0; i < square; i++) {
            x = 0;
            for (int j = 0; j < square; j++) {
                if (resM1[i][j] != 0) {
                    x++;
                    resM2_N = 100;
                }
            }
            if (x == 0 && i < resM2_N)
                resM2_N = i;
        }

        for (int i = 0; i < square; i++) {
            x = 0;
            for (int j = 0; j < square; j++) {
                if (resM1[j][i] != 0) {
                    x++;
                    resM2_M = 100;
                }
            }
            if (x == 0 && i < resM2_M)
                resM2_M = i;
        }

        resM2 = MatrixOperator::initAndCopy(resM1, resM2_N, resM2_M);
    }

    void clean(){
        //----------Очистка динамической памяти----------//
        MatrixOperator::freeSpace(mainM1, mainM1_N);
        MatrixOperator::freeSpace(mainM2, main_M2_N);

        MatrixOperator::freeSpace(sizedM1, square);
        MatrixOperator::freeSpace(sizedM2, square);

        MatrixOperator::freeSpace(resM1, square);
        MatrixOperator::freeSpace(resM2, resM2_N);

        MatrixOperator::freeSpace(subM1, halfSquare);
        MatrixOperator::freeSpace(subM2, halfSquare);
        MatrixOperator::freeSpace(subM3, halfSquare);
        MatrixOperator::freeSpace(subM4, halfSquare);
        MatrixOperator::freeSpace(subM5, halfSquare);
        MatrixOperator::freeSpace(subM6, halfSquare);
        MatrixOperator::freeSpace(subM7, halfSquare);
        MatrixOperator::freeSpace(subM8, halfSquare);

        MatrixOperator::freeSpace(helperM1, halfSquare);
        MatrixOperator::freeSpace(helperM2, halfSquare);
        MatrixOperator::freeSpace(helperM3, halfSquare);
        MatrixOperator::freeSpace(helperM4, halfSquare);

        MatrixOperator::freeSpace(interM1, halfSquare);
        MatrixOperator::freeSpace(interM2, halfSquare);
        MatrixOperator::freeSpace(interM3, halfSquare);
        MatrixOperator::freeSpace(interM4, halfSquare);
        MatrixOperator::freeSpace(interM5, halfSquare);
        MatrixOperator::freeSpace(interM6, halfSquare);
        MatrixOperator::freeSpace(interM7, halfSquare);
    }

    int mainM1_N, mainM1_M;
    int main_M2_N, main_M2_M;
    int fillMethod;
    int square = 2;
    int halfSquare;

    int** mainM1;
    int** mainM2;
    int** sizedM1;
    int** sizedM2;

    int** subM1;
    int** subM2;
    int** subM3;
    int** subM4;
    int** subM5;
    int** subM6;
    int** subM7;
    int** subM8;

    int** interM1;
    int** interM2;
    int** interM3;
    int** interM4;
    int** interM5;
    int** interM6;
    int** interM7;

    int** helperM1;
    int** helperM2;
    int** helperM3;
    int** helperM4;

    int** resM1;

    int x = 0, resM2_N = 100, resM2_M = 100;

    int** resM2;
};

int main() {
    srand(time(NULL));
    system("chcp 1251");

    MatrixStrassenMultiplier m;
    m.multiply();

    system("pause");
}
