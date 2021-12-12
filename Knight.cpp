// Knight implementation file  
#include <iostream>
#include <string>
#include <exception>

#include "Knight.h"

using namespace std; 
    
// I. CONSTRUCTOR/ DESTRUCTOR

// 1.
Knight::Knight(const string colour, bool isPieceFirstMove) noexcept : Piece(colour, isPieceFirstMove) 
{
    pieceName = "Knight"; 
    pieceIsKing = false;
}

// 2.
// Overrides Piece virtual destructor
Knight::~Knight() noexcept {}

//==================================================================

// II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

// 1.
// Overrides Piece virtual function
bool Knight::pieceMoveIsValid(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // Knight moves to any of the closest squares that are not on the same rank,
    // file, or diagonal (quote from Spec)
    if ( areOnSameFile(sourceSquare, destinationSquare) 
    || areOnSameRank(sourceSquare, destinationSquare) 
    || areOnSameDiagonal(sourceSquare, destinationSquare) )
    {
        return false; 
    }

    // Thus the move forms an ’L’-shape: two squares vertically and one square
    // horizontally, or two squares horizontally and one square vertically
    // (quoted from Spec)
    char fileIndex = 0;
    char rankIndex = 1; 
    int absFileDifference = abs(sourceSquare[fileIndex] - destinationSquare[fileIndex]);
    int absRankDifference = abs(sourceSquare[rankIndex] - destinationSquare[rankIndex]);
    if ((absFileDifference * absRankDifference) != 2)
    {
        return false; 
    }

    // The knight is the only piece that can leap over other pieces (quote from Spec)

    // Cannot move to a destination where there is a piece of the same colour
    if ( (destinationIsOccupied(boardMap, destinationSquare)) && !(areDifferentColour(boardMap, destinationSquare)) )
    {
        return false; 
    }

    return true;
}

// 2.
// Overrides Piece virtual function
Knight* Knight::duplicatePiece() noexcept
{
    return new Knight(this->colour, this->isPieceFirstMove);
}




