// Tiphaine Ramenason
// Pawn implementation file
#include <iostream>
#include <string>
#include <exception>

#include "Pawn.h"

using namespace std; 

// I. HELPER FUNCTIONS FOR MOVE VALIDITY (additional, specific to this piece)

// 1.
bool Pawn::movingForwards(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    int rankIndex = 1;
    // If piece at source is white, should move up ranks to move forwards 
    if (boardMap->find(sourceSquare)->second->pieceIsWhite())
    {
        if (sourceSquare[rankIndex] < destinationSquare[rankIndex])
        {
            return true; 
        }
        else
        {
            return false; 
        }
    }
    // If piece at source is black, should move down ranks to move forwards
    else
    {
        if (sourceSquare[rankIndex] > destinationSquare[rankIndex])
        {
            return true; 
        }
        else
        {
            return false; 
        }
    }
}     

// 2.
bool Pawn::twoRanksDistance(const string sourceSquare, const string destinationSquare) noexcept
{
    int rankIndex = 1;
    int absRankDifference = abs(destinationSquare[rankIndex] - sourceSquare[rankIndex]);
    if (absRankDifference == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//==================================================================

// II. CONSTRUCTOR/ DESTRUCTOR

// 1.
Pawn::Pawn(const string colour, bool isPieceFirstMove) noexcept : Piece(colour, isPieceFirstMove) 
{
    pieceName = "Pawn"; 
    pieceIsKing = false;
}

// 2.
// Overrides Piece destructor
Pawn::~Pawn() noexcept {}

//==================================================================

// III. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

// 1. 
// Overrides Piece virtual function
bool Pawn::pieceMoveIsValid(const map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // Pawn may move forward to the unoccupied square immediately in front of
    // it on the same file (quote from Spec)
    if (areOnSameFile(sourceSquare, destinationSquare) 
    && areOnAdjacentRanks(sourceSquare, destinationSquare) 
    && movingForwards(boardMap, sourceSquare, destinationSquare) 
    && !destinationIsOccupied(boardMap, destinationSquare))
    {
        return true; 
    }

    // On its first move Pawn may advance two squares along the same file
    // provided both squares are unoccupied (quote from Spec)
    if (this->isPieceFirstMove
    && areOnSameFile(sourceSquare, destinationSquare) 
    && twoRanksDistance(sourceSquare, destinationSquare)
    && movingForwards(boardMap, sourceSquare, destinationSquare)
    && !destinationIsOccupied(boardMap, destinationSquare)
    && noPieceAlongFile(boardMap, sourceSquare, destinationSquare))
    {
        return true;
    }

    // Pawn may move to a square occupied by an opponent’s piece which is
    // diagonally in front of it on an adjacent file, capturing that piece (quote from Spec)
    if (areOnSameDiagonal(sourceSquare, destinationSquare)
    && areOnAdjacentRanks(sourceSquare, destinationSquare)
    && areOnAdjacentFiles(sourceSquare, destinationSquare)
    && movingForwards(boardMap, sourceSquare, destinationSquare)
    && destinationIsOccupied(boardMap, destinationSquare)
    && areDifferentColour(boardMap, destinationSquare))
    {
        return true; 
    }

    // Otherwise the move is not valid based on piece specific rules
    return false;
}

// 2. 
// Overrides Piece virtual function
Pawn* Pawn::duplicatePiece() noexcept
{
    return new Pawn(this->colour, this->isPieceFirstMove);
}



