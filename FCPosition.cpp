//// FCPosition.cpp : implement the position related functions, it is the core file for this challenge,
#include <algorithm>
#include "FCPosition.h"
#include "Resource.h"
#include <optional>
#include <cwctype>
#include <iostream>
#include <cassert>

FCPosition::FCPosition() {
    coordinate = Coordinate(0,0);
    facing = GetFacingCoordinateByText(ID_FACING_EAST);
}

FCPosition::FCPosition(int x, int y, const std::wstring& facingText) {
    coordinate = Coordinate(x, y);
    facing = GetFacingCoordinateByText(facingText);
}


/// <summary>
/// Resolve facing direction from text to coordinate style
/// the reason for this is trying to make it eaiser for robot movement.
/// </summary>
/// <param name="facingText"></param>
/// <returns></returns>
Coordinate FCPosition::GetFacingCoordinateByText(const std::wstring& facingText) {

    if (caseInsensitiveCompare(facingText, ID_FACING_EAST)) {
        return Coordinate(1, 0);
    }
    else if (caseInsensitiveCompare(facingText, ID_FACING_NORTH)) {
        return Coordinate(0, 1);
    }
    else if (caseInsensitiveCompare(facingText, ID_FACING_WEST)) {
        return Coordinate(-1, 0);
    }
    else if (caseInsensitiveCompare(facingText, ID_FACING_SOUTH)) {
        return Coordinate(0, -1);
    }
    return {};
}

/// <summary>
/// Resolve facing direction from text to coordinate style
/// the reason for this is trying to make it eaiser for robot movement.
/// </summary>
/// <param name="facingText"></param>
/// <returns></returns>
const std::wstring FCPosition::GetFacingCoordinateText() {

    if (facing == Coordinate(1, 0)) {
        return ID_FACING_EAST;
    }
    else if (facing == Coordinate(0, 1)) {
        return ID_FACING_NORTH;
    }
    else if (facing == Coordinate(-1, 0)) {
        return ID_FACING_WEST;
    }
    else if (facing == Coordinate(0, -1)) {
        return ID_FACING_SOUTH;
    }
    return L"Wrong facing situation";
}

bool FCPosition::caseInsensitiveCompare(const std::wstring& a, const std::wstring& b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
        [](wchar_t a, wchar_t b) {
            return std::towupper(a) == std::towupper(b);
        });
}

/// <summary>
/// check for boundry, coordinate start from zero.
/// </summary>
/// <param name="coordinate"></param>
/// <returns></returns>
bool FCPosition::checkCoordinateBoundry(Coordinate coordinate) {
    if(coordinate.x >= GRID_SIZE 
        || coordinate.y >= GRID_SIZE
        ||coordinate.x<0
        ||coordinate.y<0){
        return false;
    }
    else {
        return true;
    }
}

/// <summary>
/// Face robot to left
/// </summary>
void FCPosition::faceLeft() {
    if (facing.x == 0 && facing.y != 0) {
        facing.x = 0 - facing.y;
        facing.y = 0;
    }
    else if (facing.y == 0 && facing.x != 0) {
        facing.y = facing.x;
        facing.x = 0;
    }
    else {
        //assert, should not have this situation
        //asserts("invalid position");
        assert(false); // This will trigger an assertion failure since x is not 5
        std::cout << "Robot direction is not supported." << std::endl;
    }
}


/// <summary>
/// Robot face make a uturn
/// For uturn, just switch the facing coordination
/// Uturn action is not required, but needed by turning right.
/// </summary>
void FCPosition::faceUturn() {
    facing.x = 0 - facing.x;
    facing.y = 0 - facing.y;;
}

/// <summary>
/// Robot face right
/// Facing right is equal turn left and then make a uturn
/// </summary>
void FCPosition::faceRight() {
    faceLeft();
    faceUturn();
}


/// <summary>
/// Robot move a single step.
/// just towards the facing direction, then add the coordinate value.
/// </summary>
bool FCPosition::move() {
    
    //new position  simply added with the facing coordinate.
    Coordinate newPosition 
        = Coordinate(coordinate.x + facing.x, coordinate.y + facing.y);

    //check boundry before move
    if (checkCoordinateBoundry(newPosition)) {
        coordinate = newPosition;
        return true;
    }
    else {
        //Out of boundry, give a tips
        return false;
    }
}


/// <summary>
/// Get text description for position as required.
/// </summary>
/// <returns></returns>
const std::wstring FCPosition::getReport() {
    return L"Output:" 
        + std::to_wstring(coordinate.x) 
        + L"," + std::to_wstring(coordinate.y) 
        + L"," + GetFacingCoordinateText();
}

