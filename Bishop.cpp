// Bishop implementation file 
#include <iostream>
#include <string>
#include <exception>

#include "Bishop.h"

using namespace std; 

// I. CONSTRUCTOR/ DESTRUCTOR

// 1.
Bishop::Bishop(const string colour, bool isPieceFirstMove) noexcept : Piece(colour, isPieceFirstMove)
{
    pieceName = "Bishop"; 
    pieceIsKing = false;
}

// 2.
// Overrides Piece virtual destructor
Bishop::~Bishop() noexcept {}

//==================================================================
        
// II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

// 1. 
// Overrides Piece virtual function
bool Bishop::pieceMoveIsValid(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // The bishop can move any number of squares diagonally (quoted from Spec)
    if (!areOnSameDiagonal(sourceSquare, destinationSquare))
    {
        return false; 
    }

    // But may not leap over other pieces (quoted from Spec)
    if (!noPieceAlongDiagonal(boardMap, sourceSquare, destinationSquare))
    {
        return false; 
    }

    // Cannot move to a destination where there is a piece of the same colour
    if ( (destinationIsOccupied(boardMap, destinationSquare)) && !(areDifferentColour(boardMap, destinationSquare)) )
    {
        return false; 
    }

    return true; 
}

// 2.
// Overrides Piece virtual function
Bishop* Bishop::duplicatePiece() noexcept
{
    return new Bishop(this->colour, this->isPieceFirstMove);
}