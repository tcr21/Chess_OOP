// Chess exceptions implementation file

#include <string>
#include <cstring>
#include <exception>
#include "ChessExceptions.h"

using namespace std; 

// I. ANY ERROR CLASS
// 1. 
AnyError::AnyError(const string& message) noexcept : explanation(message) {}
// 2. 
const char* AnyError::what() const noexcept
{
    // Note: need to convert using c_str because what() function expects to
    // return const char* type
    return explanation.c_str(); 
} 

//==================================================================
// II. POSITION (SQUARE) ERROR CLASS
// 1. 
PositionError::PositionError(const string& message, const string& square) noexcept : AnyError(message), square(square) {}
// 2. 
const string& PositionError::getSquare() const noexcept
{
    return square;
}

//==================================================================

// III. INPUT LENGTH ERROR CLASS 
// 1. 
InputLengthError::InputLengthError(const string& message, const string& square) noexcept : PositionError(message, square) {}

//==================================================================

// IV. INPUT CHARACTERS ERROR CLASS
// 1. 
InputCharacterError::InputCharacterError(const string& message, const string& square) noexcept : PositionError(message, square) {}

//==================================================================

// V. HAS NO PIECE AT GIVEN POSITION ERROR CLASS
// 1. 
HasNoPieceError::HasNoPieceError(const string& message, const string& square) noexcept : PositionError(message, square) {}

//==================================================================

// VI. SOURCE AND DESTINATION ARE THE SAME ERROR CLASS
// 1. 
SameSourceDestinationError::SameSourceDestinationError(const string& message, const string& square, const string& secondSquare) noexcept : PositionError(message, square), secondSquare(secondSquare) {}
// 2. 
const string& SameSourceDestinationError::getSecondSquare() const noexcept
{
    return secondSquare;
}

//==================================================================

// VII. NOT PLAYER'S TURN ERROR CLASS
// 1. 
WrongPlayersTurnError::WrongPlayersTurnError(const string& message, const string& colour) noexcept : AnyError(message), colour(colour) {}
// 2. 
const string& WrongPlayersTurnError::getPieceColour() const noexcept
{
    return colour;
}


