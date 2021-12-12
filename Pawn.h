// Pawn header file 
#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include <map>
#include <string>
#include <exception>

#include "Piece.h"

class Pawn : public Piece
{
    private:
        // I. HELPER FUNCTIONS FOR MOVE VALIDITY (additional, specific to this piece)

        // 1. Determines if would be moving forward (towards opponent)
        bool movingForwards(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 2. Determines if destination would be 2 ranks away
        bool twoRanksDistance(const std::string sourceSquare, const std::string destinationSquare) noexcept;

        //==================================================================
    public:
        // II. CONSTRUCTOR/ DESTRUCTOR

        // 1. Constructor
        Pawn(const std::string colour, bool isPieceFirstMove) noexcept; 

        // 2. Destructor 
        // Overrides Piece virtual destructor
        ~Pawn() noexcept; 

        //==================================================================
        
        // III. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

        // 1. Determines move validity based on piece specific rules
        // Overrides Piece virtual function
        bool pieceMoveIsValid(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept override;

        // 2. Duplicates the piece include the same features
        // Overrides Piece virtual function
        Pawn* duplicatePiece() noexcept override;
}; 

#endif
