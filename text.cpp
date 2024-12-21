#ifndef TEXT
#define TEXT

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include "list.cpp"

using namespace std;

// Base class for all text types
class Text
{
protected:
    string text;
    int delay;

public:
    // Constructor to initialize text and delay
    Text(const string &text, int delay = 100) : text(text), delay(delay) {}

    // Virtual print method (to be overridden by derived classes)
    virtual void print() = 0;

    // Static method for reset
    static string reset() { return "\033[0m"; }

    // Static methods for ANSI color codes
    static string red() { return "\033[31m"; }
    static string green() { return "\033[32m"; }
    static string blue() { return "\033[34m"; }
    static string yellow() { return "\033[33m"; }
    static string magenta() { return "\033[35m"; }
    static string cyan() { return "\033[36m"; }
    static string white() { return "\033[37m"; }
    static string bold() { return "\033[1m"; }
    static string normal() { return "\033[0m"; }
};

// Derived class for single-color text
class SingleColorText : public Text
{
private:
    string color; // Single color for the text
    bool bold;

public:
    // Constructor for single-color text
    SingleColorText(const string &text, const string &color, bool bold = 0, int delay = 40)
        : Text(text, delay), color(color), bold(bold) {}

    void setText(const string text)
    {
        this->text = text;
    }
    void setBold(const bool bold)
    {
        this->bold = bold;
    }
    void setDelay(const int delay)
    {
        this->delay = delay;
    }
    void setColor(const string &color)
    {
        this->color = color;
    }
    // Method to display the animated text in single color
    void print() override
    {
        for (size_t i = 0; i < text.length(); ++i)
        {
            if (bold)
                cout << Text::bold();
            else
                cout << Text ::normal();
            cout << color << text[i] << Text::reset(); // Call reset from Text
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
    }
};

// Derived class for multi-color text
class MultiColorText : public Text
{
private:
    List<string> colors; // List to store multiple colors

public:
    // Constructor for multi-color text
    MultiColorText(const string &text, const List<string> &colors, int delay = 100)
        : Text(text, delay), colors(colors)
    {
    }
    void setText(const string text)
    {
        this->text = text;
    }

    void setColor(const List<string> &colors)
    {
        this->colors = colors;
    }

    // Method to display the animated text with multiple colors
    void print() override
    {
        int colorCount = colors.length();
        for (int i = 0; i < text.length(); ++i)
        {
            string color = colors[i % colorCount];
            cout << color << text[i] << Text::reset(); // Call reset from Text
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
    }
};

class SpiralText : public Text
{
public:
    SpiralText(const string &text, int delay = 100) : Text(text, delay) {}

    void print() override
    {
        int n = text.length();
        for (int i = 0; i < n; ++i)
        {
            // Move the cursor to a new position to create the spiral effect
            cout << string(i, ' ') << text[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(delay));
            cout << endl;
        }
    }
};

class RandomColorText : public Text
{
public:
    RandomColorText(const string &text, int delay = 100) : Text(text, delay)
    {
        srand(time(0)); // Seed the random number generator
    }

    string randomColor()
    {
        int color = rand() % 5; // Random number between 0 and 4
        switch (color)
        {
        case 0:
            return Text::red();
        case 1:
            return Text::green();
        case 2:
            return Text::blue();
        case 3:
            return Text::yellow();
        case 4:
            return Text::cyan();
        default:
            return Text::reset();
        }
    }

    void print() override
    {
        for (size_t i = 0; i < text.length(); ++i)
        {
            cout << randomColor() << text[i] << Text::reset();
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
        cout << endl;
    }
};

class BlinkingText : public Text
{
    int times;

public:
    BlinkingText(const string &text, int delay = 100, int times = 10) : Text(text, delay), times(times) {}

    void print() override
    {
        for (int i = 0; i < times; i++)
        {
            // Print the text
            cout << text << flush;
            this_thread::sleep_for(chrono::milliseconds(delay));

            // Clear the text
            cout << "\r" << string(text.length(), ' ') << "\r" << flush;

            this_thread::sleep_for(chrono::milliseconds(delay));
        }
    }
};

#endif