#ifndef USEFUL_HPP
#define USEFUL_HPP

#include <iostream>
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>

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

    static float SqrMagnitude(const sf::Vector2f v)
    {
        return v.x * v.x + v.y * v.y;
    }

    static float Magnitude(const sf::Vector2f v)
    {
        return sqrtf(v.x * v.x + v.y * v.y);
    }

    static sf::Vector2f Normalize(const sf::Vector2f v)
    {
        float mag = Magnitude(v);
        return sf::Vector2f(v.x / mag, v.y / mag);
    }

    static float SqrDistance(const sf::Vector2f p1, const sf::Vector2f p2)
    {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }

    static float Distance(const sf::Vector2f p1, const sf::Vector2f p2)
    {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    static float Dot(const sf::Vector2f p1, const sf::Vector2f p2)
    {
        return p1.x * p2.x + p1.y * p2.y;
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

    static float RandExclude()
    {
        return ((float)rand()) / (RAND_MAX + 1);
    }

    static int Rand(int a, int b)
    {
        return (int)(RandExclude() * (Useful::Abs(b - a) + 1)) + a;
    }

    static float Rand(float a, float b)
    {
        return Rand() * Useful::Abs(b - a) + a;
    }

    static int RandExclude(int a, int b)
    {
        return Rand(a, b - 1);
    }

    static float RandExclude(float a, float b)
    {
        return RandExclude() * Useful::Abs(b - a) + a;
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

#endif