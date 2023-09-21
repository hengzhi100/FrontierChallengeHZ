#pragma once
#include <string>

const wchar_t* const ID_FACING_EAST = L"east";
const wchar_t* const ID_FACING_WEST = L"west";
const wchar_t* const ID_FACING_SOUTH = L"south";
const wchar_t* const ID_FACING_NORTH = L"north";

class Coordinate {
public:
    int x;
    int y;
    Coordinate() : x(0), y(0) {} // Default constructor

    Coordinate(int _x, int _y) {
        x = _x;
        y = _y;
    }

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

class FCPosition
{
public:
    Coordinate coordinate;
    Coordinate facing;
    // Default constructor
    FCPosition();
    //Handy constructor for user input place
    FCPosition(int x, int y, const std::wstring& facingText);
    Coordinate GetFacingCoordinateByText(const std::wstring& facingText);
    bool checkCoordinateBoundry(Coordinate coordinate);
    const std::wstring GetFacingCoordinateText();
    const std::wstring getReport();
    void faceLeft();
    void faceUturn();
    void faceRight();
    bool move();

private:
    bool caseInsensitiveCompare(const std::wstring& a, const std::wstring& b);
};