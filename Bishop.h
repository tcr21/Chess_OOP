// Tiphaine Ramenason
// Bishop header file 
#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "Piece.h"

class Bishop : public Piece
{
    public:
        // I. CONSTRUCTOR/ DESTRUCTOR

        // 1. Constructor
        Bishop(const std::string colour, bool isPieceFirstMove) noexcept; 

        // 2. Destructor 
        // Overrides Piece virtual destructor
        ~Bishop() noexcept; 

        //==================================================================
        
        // II. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

        // 1. Determines move validity based on piece specific rules
        // Overrides Piece virtual function
        bool pieceMoveIsValid(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept override;

        // 2. Duplicates the piece include the same features
        // Overrides Piece virtual function
        Bishop* duplicatePiece() noexcept override;
};

#endif