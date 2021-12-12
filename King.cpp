// King implementation file 

#include <iostream>
#include <string>
#include <exception>

#include "King.h"

using namespace std; 

// I. CONSTRUCTOR/ DESTRUCTOR

// 1. 
King::King(const string colour, bool isPieceFirstMove) noexcept : Piece(colour, isPieceFirstMove)
{
    pieceName = "King"; 
    pieceIsKing = true;
}

// 2. 
// Overrides Piece virtual destructor
King::~King() noexcept {}

//==================================================================
        
// II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

// 1.
// Overrides Piece virtual function
bool King::pieceMoveIsValid(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // A king moves one square in any direction (quote from Spec): if
    // destination/ source are neither on adjacent files nor on adjacent ranks,
    // then move is not valid
    if ( ! (areOnAdjacentRanks(sourceSquare, destinationSquare)
    && areOnAdjacentFiles(sourceSquare, destinationSquare)) )
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
King* King::duplicatePiece() noexcept
{
    return new King(this->colour, this->isPieceFirstMove);
}



