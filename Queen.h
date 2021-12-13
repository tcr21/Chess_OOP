// Tiphaine Ramenason
// Queen header file
#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "Piece.h"

class Queen : public Piece
{
    public:
        // I. CONSTRUCTOR/ DESTRUCTOR

        // 1. Constructor
        Queen(const std::string colour, bool isPieceFirstMove) noexcept; 

        // 2. Destructor 
        // Overrides Piece virtual destructor
        ~Queen() noexcept; 

        //==================================================================
        
        // II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

        // 1. Determines move validity based on piece specific rules
        // Overrides Piece virtual function
        bool pieceMoveIsValid(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept override;

        // 2. Duplicates the piece include the same features
        // Overrides Piece virtual function
        Queen* duplicatePiece() noexcept override;
}; 

#endif