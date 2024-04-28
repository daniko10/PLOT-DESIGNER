#include "vecmat.h"

Vector::Vector()
{
    data[0] = 0.0; data[1] = 0.0; data[2] = 1.0;
}

void Vector::Print(void)
{
    printf("(%2.3lf,%2.3lf,%2.3lf)\n", data[0], data[1], data[2]);
}

void Vector::Set(double d1, double d2)
{
    data[0] = d1; data[1] = d2;
}

double Vector::GetX()
{
    return data[0];
}

double Vector::GetY()
{
    return data[1];
}

Matrix::Matrix()
{
    data[0][0] = 0.0; data[0][1] = 0.0; data[0][2] = 0.0;
    data[1][0] = 0.0; data[1][1] = 0.0; data[1][2] = 0.0;
    data[2][0] = 0.0; data[2][1] = 0.0; data[2][2] = 1.0;
}

void Matrix::Print(void)
{
    printf("\n|%2.3lf,%2.3lf,%2.3lf|\n", data[0][0], data[0][1], data[0][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[1][0], data[1][1], data[1][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[2][0], data[2][1], data[2][2]);
}

Matrix Matrix::operator* (const Matrix gMatrix)
{
    int i, j, k;
    Matrix tmp;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            tmp.data[i][j] = 0.0;
            for (k = 0; k < 3; k++)
                tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * gMatrix.data[k][j]);
        }
    return tmp;
}

Vector operator* (const Matrix gMatrix, const Vector gVector)
{
    unsigned int i, j;
    Vector tmp;

    for (i = 0; i < 3; i++)
    {
        tmp.data[i] = 0.0;
        for (j = 0; j < 3; j++) tmp.data[i] = tmp.data[i] + (gMatrix.data[i][j] * gVector.data[j]);
    }
    return tmp;
}


Matrix GetScaleMatrix(double w, double h, double x0, double x1, double y0, double y1)
{
    Matrix M;

    M.data[0][0] = w / (x1 - x0);
    M.data[1][1] = -h / (y1 - y0); // minus bo y1 jest mniejszy bo zaczynamy "od gory"

    return M;
}

Matrix GetRotationMatrix(double alpha)
{
    Matrix M;

    const double rad = alpha * M_PI / 180.0;

    M.data[0][0] = cos(rad);
    M.data[0][1] = -sin(rad);
    M.data[1][0] = sin(rad);
    M.data[1][1] = cos(rad);

    return M;
}

Matrix GetTranslationMatrix(double dx, double dy)
{
    Matrix M;

    // przesuniecie o dx w kierunku X i dy w kierunku Y
    M.data[0][0] = 1.0;
    M.data[1][1] = 1.0;
    M.data[0][2] = dx;
    M.data[1][2] = dy;

    // [2][2] zawsze 1

    return M;
}