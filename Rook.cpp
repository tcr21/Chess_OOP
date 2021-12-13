// Tiphaine Ramenason
// Rook implementation file 
#include <iostream>
#include <string>
#include <exception>

#include "Rook.h"

using namespace std; 

// I. CONSTRUCTOR/ DESTRUCTOR

// 1.
Rook::Rook(const string colour, bool isPieceFirstMove) noexcept : Piece(colour, isPieceFirstMove) 
{
    pieceName = "Rook"; 
    pieceIsKing = false;
}

// 2.
// Overrides Piece virtual destructor
Rook::~Rook() noexcept {}

//==================================================================
        
// II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

// 1. 
// Overrides Piece virtual function
bool Rook::pieceMoveIsValid(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // Rook can move any number of squares along same rank or file
    if ( !(areOnSameFile(sourceSquare, destinationSquare))
    && !(areOnSameRank(sourceSquare, destinationSquare)) )
    {
        return false; 
    }

    // It may not leap over other pieces
    if ( (areOnSameFile(sourceSquare, destinationSquare) && !noPieceAlongFile(boardMap, sourceSquare, destinationSquare))
    || (areOnSameRank(sourceSquare, destinationSquare) && !noPieceAlongRank(boardMap, sourceSquare, destinationSquare)) )
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
Rook* Rook::duplicatePiece() noexcept
{
    return new Rook(this->colour, this->isPieceFirstMove);
}
