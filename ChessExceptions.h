// Tiphaine Ramenason
// Chess exceptions header file 

#ifndef CHESSEXCEPTIONS_H
#define CHESSEXCEPTIONS_H

#include <string>
#include <cstring>
#include <exception>

// I. ANY ERROR CLASS: explanation
class AnyError : public std::exception
{
    protected:
        std::string explanation;
    
    public:
        // 1. Constructor
        AnyError(const std::string& message) noexcept; 
        // 2. Overrides standard exception virtual what() function
        const char* what() const noexcept override; 
}; 

//==================================================================

// II. POSITION (SQUARE) ERROR CLASS: inherits from any error class. Adds square
// data member & get square function
class PositionError : public AnyError
{
    protected:
        std::string square; 
    public:
        // 1. Constructor
        PositionError(const std::string& message, const std::string& square) noexcept; 
        // 2. Gets square
        const std::string & getSquare() const noexcept; 
}; 

//==================================================================

// III. INPUT LENGTH ERROR CLASS: inherits from position error class. Does not
// add anything, but has a different meaning so is defined as separate error
// class
class InputLengthError : public PositionError 
{
    public:
        // 1. Constructor
        InputLengthError(const std::string& message, const std::string& square) noexcept;
}; 

//==================================================================

// IV. INPUT CHARACTERS ERROR CLASS: inherits from position error class. Does
// not add anything, but has a different meaning so is defined as separate error
// class
class InputCharacterError : public PositionError 
{
    public:
        // 1. Constructor
        InputCharacterError(const std::string& message, const std::string& square) noexcept;
}; 

//==================================================================

// V. HAS NO PIECE AT GIVEN POSITION ERROR CLASS: inherits from position error
// class. Does not add anything, but has a different meaning so is defined as
// separate error class
class HasNoPieceError : public PositionError 
{
    public:
        // 1. Constructor
        HasNoPieceError(const std::string& message, const std::string& square) noexcept;
}; 

//==================================================================

// VI. SOURCE AND DESTINATION ARE THE SAME ERROR CLASS: inherits from position
// error class. Adds second square data member & get second square function,
// since error stems from source and destination squares being the same
class SameSourceDestinationError : public PositionError
{
    private:
        std::string secondSquare; 
    public:
        // 1. Constructor
        SameSourceDestinationError(const std::string& message, const std::string& square, const std::string& secondSquare) noexcept; 
        // 2. Gets second square
        const std::string& getSecondSquare() const noexcept; 
}; 

//==================================================================

// VII. NOT PLAYER'S TURN ERROR CLASS: inherits from any error class. Adds
// colour data member & get colour function
class WrongPlayersTurnError : public AnyError
{
    private:
        const std::string colour;
    public: 
        // 1. Constructor
        WrongPlayersTurnError(const std::string& message, const std::string& colour) noexcept; 
        // 2. Gets colour
        const std::string& getPieceColour() const noexcept; 
}; 

#endif