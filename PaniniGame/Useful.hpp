#ifndef USEFUL_HPP
#define USEFUL_HPP

#include <iostream>
#include <cmath>
#include <sstream>

class Useful
{
public:
    static int Abs(int a)
    {
        return a >= 0 ? a : -a;
    }

    static float Abs(float a)
    {
        return a >= 0 ? a : -a;
    }

    static int Max(int a, int b)
    {
        return a >= b ? a : b;
    }

    static float Max(float a, float b)
    {
        return a >= b ? a : b;
    }

    static double Max(double a, double b)
    {
        return a >= b ? a : b;
    }

    static int Min(int a, int b)
    {
        return a <= b ? a : b;
    }

    static float Min(float a, float b)
    {
        return a <= b ? a : b;
    }

    static double Min(double a, double b)
    {
        return a <= b ? a : b;
    }
};

class Random
{
public:
    static void SetRandomSeed()
    {
        srand(time(0));
    }

    static float Rand()
    {
        return ((float)rand()) / RAND_MAX;
    }

    static int Rand(int a, int b)
    {
        return (int)(Rand() * Useful::Abs(b - a)) + a;
    }

    static float Rand(float a, float b)
    {
        return Rand() * Useful::Abs(b - a) + a;
    }

    static int RandExclude(int a, int b)
    {
        return Rand(a, b + 1);
    }

    static float RandExclude(float a, float b)
    {
        return (((float)(rand() - 1)) / RAND_MAX) * Useful::Abs(b - a) + a;
    }
};

struct Object
{
public:

    virtual std::string ToString() const
    {
        return "Object";
    }
};

template <typename T>
class Array2D : public Object
{
private:
    T* array;
    int width;
    int height;

public:

    int Width() { return width; }
    int Height() { return height; }

    Array2D(int width, int height)
    {
        this->width = width;
        this->height = height;

        array = new T[width * height];
    }

    T Get(int i, int j) const
    {
        return array[i * width + j];
    }

    void Set(int i, int j, T value)
    {
        array[i * width + j] = value;
    }
};

struct Vector2 : public Object
{
public:

    float x, y;

    Vector2()
    {
        this->x = 0.0f; this->y = 0.0f;
    }

    Vector2(float x)
    {
        this->x = x; this->y = 0.0f;
    }

    Vector2(float x, float y)
    {
        this->x = x; this->y = y;
    }

    float SqrMagnitude() const
    {
        return x * x + y * y;
    }

    float Magnitude() const
    {
        return sqrtf(x * x + y * y);
    }

    Vector2 Normalize() const
    {
        float mag = Magnitude();
        return Vector2(this->x / mag, this->y / mag);
    }

    float SqrDistance(const Vector2& v) const
    {
        return (v.x - this->x) * (v.x - this->x) + (v.y - this->y) * (v.y - this->y);
    }

    float Distance(const Vector2& v) const
    {
        return sqrt((v.x - this->x) * (v.x - this->x) + (v.y - this->y) * (v.y - this->y));
    }

    std::string ToString() const override
    {
        std::ostringstream os;
        os << "(" << x << ", " << y << ")" << std::endl;
        return os.str();
    }

    Vector2 operator+(Vector2 v)
    {
        return Vector2(v.x + this->x, v.y + this->y);
    }
    Vector2 operator-(Vector2 v)
    {
        return Vector2(this->x - v.x, this->y - v.y);
    }
    Vector2 operator-()
    {
        return Vector2(-this->x, -this->y);
    }
    Vector2 operator*(float a)
    {
        return Vector2(a * this->x, a * this->y);
    }
    Vector2 operator/(float a)
    {
        return Vector2(this->x / a, this->y / a);
    }
};

#endif