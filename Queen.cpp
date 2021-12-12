// Queen implementation file 
#include <iostream>
#include <string>
#include <exception>

#include "Queen.h"

using namespace std; 

// I. CONSTRUCTOR/ DESTRUCTOR

// 1. 
Queen::Queen(const string colour, bool isPieceFirstMove) noexcept : Piece(colour, isPieceFirstMove)
{
    pieceName = "Queen"; 
    pieceIsKing = false;
}

// 2.
// Overrides Piece virtual destructor
Queen::~Queen() noexcept {}

//==================================================================
        
// II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

// 1.
// Overrides Piece virtual function
bool Queen::pieceMoveIsValid(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // Queen... can move any number of squares along rank, file, or diagonal (quoted from Spec)
    if ( !(areOnSameFile(sourceSquare, destinationSquare))
    && !(areOnSameRank(sourceSquare, destinationSquare))
    && !(areOnSameDiagonal(sourceSquare, destinationSquare)) )
    {
        return false; 
    }

    // It may not leap over other pieces (quoted from Spec)
    if ( (areOnSameFile(sourceSquare, destinationSquare) && !noPieceAlongFile(boardMap, sourceSquare, destinationSquare))
    || (areOnSameRank(sourceSquare, destinationSquare) && !noPieceAlongRank(boardMap, sourceSquare, destinationSquare))
    || (areOnSameDiagonal(sourceSquare, destinationSquare) && !noPieceAlongDiagonal(boardMap, sourceSquare, destinationSquare)) )
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
Queen* Queen::duplicatePiece() noexcept
{
    return new Queen(this->colour, this->isPieceFirstMove);
}
