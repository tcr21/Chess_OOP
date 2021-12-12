// Rook header file 
#ifndef ROOK_H
#define ROOK_H

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "Piece.h"

class Rook : public Piece
{
    public:
        // I. CONSTRUCTOR/ DESTRUCTOR

        // 1. Constructor
        Rook(const std::string colour, bool isPieceFirstMove) noexcept; 

        // 2. Destructor 
        // Overrides Piece virtual destructor
        ~Rook() noexcept; 

        //==================================================================
        
        // II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

        // 1. Determines move validity based on piece specific rules
        // Overrides Piece virtual function
        bool pieceMoveIsValid(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept override;

        // 2. Duplicates the piece include the same features
        // Overrides Piece virtual function
        Rook* duplicatePiece() noexcept override;
}; 

#endif

