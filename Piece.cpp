// Piece implementation file

#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>

#include "Piece.h"

using namespace std;

// I. HELPER FUNCTIONS FOR MOVE VALIDITY

// 1. 
bool Piece::areOnSameFile(const string sourceSquare, const string destinationSquare) noexcept
{
    if (sourceSquare[0] == destinationSquare[0])
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// 2. 
bool Piece::areOnSameRank(const string sourceSquare, const string destinationSquare) noexcept
{
    if (sourceSquare[1] == destinationSquare[1])
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// 3. 
bool Piece::areOnSameDiagonal(const string sourceSquare, const string destinationSquare) noexcept
{
    int absFileDifference = abs(sourceSquare[0] - destinationSquare[0]);
    int absRankDifference = abs(sourceSquare[1] - destinationSquare[1]);
    if (absFileDifference == absRankDifference)
    {
        return true; 
    }
    return false; 
}

// 4. 
bool Piece::areOnAdjacentFiles(const string sourceSquare, const string destinationSquare) noexcept
{
    int absFileDifference = abs(sourceSquare[0] - destinationSquare[0]);
    if (absFileDifference == 1)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// 5.
bool Piece::areOnAdjacentRanks(const string sourceSquare, const string destinationSquare) noexcept
{
    int absRankDifference = abs(sourceSquare[1] - destinationSquare[1]);
    if (absRankDifference == 1)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// 6. 
bool Piece::noPieceAlongFile(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    int fileIndex = 0; 
    int rankIndex = 1;
    char higherRank; 
    char lowerRank;

    if (sourceSquare[rankIndex] < destinationSquare[rankIndex])
    {
        higherRank = destinationSquare[rankIndex]; 
        lowerRank = sourceSquare[rankIndex]; 
        
    }
    else if (sourceSquare[rankIndex] > destinationSquare[rankIndex])
    {
        higherRank = sourceSquare[rankIndex]; 
        lowerRank = destinationSquare[rankIndex]; 
    }
    // The ranks are equal so higher/lower rank can both be set to equal either
    // source or destination rank (used source rank here). The for loop will not
    // execute and function will return true (no pieces in the way) by default
    else 
    {
        higherRank = sourceSquare[rankIndex]; 
        lowerRank = sourceSquare[rankIndex]; 
    }

    // Go through each square along the file (file stays constant, rank goes
    // upwards) to check there is no piece
    for (char i = lowerRank + 1; i < higherRank; i++)
    {
        string squareAlongFile = string() + sourceSquare[fileIndex] + i; 
        if (boardMap->find(squareAlongFile) != boardMap->end())
        {
            return false;
        }
    }
    return true; 
}

// 7. 
bool Piece::noPieceAlongRank(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    int fileIndex = 0; 
    int rankIndex = 1;
    char higherFile; 
    char lowerFile;

    if (sourceSquare[fileIndex] < destinationSquare[fileIndex])
    {
        higherFile = destinationSquare[fileIndex]; 
        lowerFile = sourceSquare[fileIndex]; 
        
    }
    else if (sourceSquare[fileIndex] > destinationSquare[fileIndex])
    {
        higherFile = sourceSquare[fileIndex]; 
        lowerFile = destinationSquare[fileIndex]; 
    }
    // The files are equal so higher/lower file can both be set to equal either
    // source or destination file (used source file here). The for loop will not
    // execute and function will return true (no pieces in the way) by default
    else 
    {
        higherFile = sourceSquare[fileIndex]; 
        lowerFile = sourceSquare[fileIndex]; 
    }

    // Go through each square along the rank (rank stays constant, file goes
    // rightwards) to check there is no piece
    for (char i = lowerFile + 1; i < higherFile; i++)
    {
        string squareAlongRank = string() + i + sourceSquare[rankIndex]; 
        if (boardMap->find(squareAlongRank) != boardMap->end())
        {
            return false;
        }
    }
    return true; 
}

// 8. 
bool Piece::noPieceAlongDiagonal(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    int fileIndex = 0; 
    int rankIndex = 1;
    char higherFile; 
    char lowerFile;
    char higherRank; 
    char lowerRank;

    // Set higher and lower file
    if (sourceSquare[fileIndex] < destinationSquare[fileIndex])
    {
        higherFile = destinationSquare[fileIndex]; 
        lowerFile = sourceSquare[fileIndex]; 
        
    }
    else if (sourceSquare[fileIndex] > destinationSquare[fileIndex])
    {
        higherFile = sourceSquare[fileIndex]; 
        lowerFile = destinationSquare[fileIndex]; 
    }
    else 
    {
        higherFile = sourceSquare[fileIndex]; 
        lowerFile = sourceSquare[fileIndex]; 
    }
    // Set higher and lower rank
    if (sourceSquare[rankIndex] < destinationSquare[rankIndex])
    {
        higherRank = destinationSquare[rankIndex]; 
        lowerRank = sourceSquare[rankIndex]; 
        
    }
    else if (sourceSquare[rankIndex] > destinationSquare[rankIndex])
    {
        higherRank = sourceSquare[rankIndex]; 
        lowerRank = destinationSquare[rankIndex]; 
    }
    else 
    {
        higherRank = sourceSquare[rankIndex]; 
        lowerRank = sourceSquare[rankIndex]; 
    }

    // Determine if diagonal trends upwards or downwards. We presume the
    // diagonal is the same (checked in separate helper function) so the
    // absolute values will be the same either way. However if the signs are the
    // same (ie values equal is true), then the diagonal trends upwards (true).
    // If the signs are not the same (ie values equal is false), then the
    // diagonal trends downwards (false)
    int fileDifference = destinationSquare[fileIndex] - sourceSquare[fileIndex];
    int rankDifference = destinationSquare[rankIndex] - sourceSquare[rankIndex];
    bool upwardsDiagonalTrend = (fileDifference == rankDifference);
    string squareAlongDiagonal;


    // Go through each square along diagonal to check if there is a piece
    // between source/ destination
    for (int diff = 1; diff < (higherFile - lowerFile); diff++)
    {
        // Either way go from left to right (from square with lowest file to
        // square with highest file)
        // If the diagonal goes upwards, add the difference to the lower rank
        if (upwardsDiagonalTrend)
        {
            squareAlongDiagonal = string() + (char) (lowerFile + diff) + (char) (lowerRank + diff);
        }
        // If the diagonal goes downwards, subtract the difference from the
        // higher rank
        else
        {
            squareAlongDiagonal = string() + (char) (lowerFile + diff) + (char) (higherRank - diff);
        }
        // Check if there is a piece
        if (boardMap->find(squareAlongDiagonal) != boardMap->end())
        {
            return false;
        }
    }
    return true; 
}

// 9. 
bool Piece::destinationIsOccupied(const map<string, Piece *> *boardMap, const string destinationSquare) noexcept
{   
    if (boardMap->find(destinationSquare) != boardMap->end())
    {
        return true; 
    }
    return false; 
}

// 10. 
bool Piece::areDifferentColour(const map<string, Piece *> *boardMap, const string destinationSquare) noexcept
{
    if (this->colour != boardMap->find(destinationSquare)->second->getPieceColour())
    {
        return true; 
    }
    return false;
}

//==================================================================

// II. CONSTRUCTOR/ DESTRUCTOR

// 1.
Piece::Piece(const string colour, bool isPieceFirstMove) noexcept : colour(colour), isPieceFirstMove(isPieceFirstMove) {}

// 2.
// Virtual
Piece::~Piece() noexcept {}

//==================================================================
        
// III.  GETTER FUNCTIONS / INFO ABOUT PIECE

// 1. 
const string& Piece::getPieceColour() const noexcept
{
    return colour;
}

// 2. 
bool Piece::pieceIsWhite() const noexcept
{
    if (colour == "White")
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// 3.
const string& Piece::getPieceName() const noexcept
{
   return pieceName;
}

// 4.
bool Piece::getPieceIsKing() const noexcept
{
    return pieceIsKing;
}

//==================================================================
        
// IV. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE 

// 1.
// Virtual. To be overriden by specific pieces (no generic move validity
// definition). Set to 0 in header file so definition not needed here


// 2.
// Virtual. To be overriden by specific pieces (no generic duplication
// definition). Set to 0 in header file so definition not needed here

//==================================================================

// V. MOVE IMPLEMENTATION

// 1. 
void Piece::setFirstMoveDone() noexcept
{
    isPieceFirstMove = false; 
}
