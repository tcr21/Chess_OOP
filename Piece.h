// Tiphaine Ramenason
// Piece header file: abstract class acting as interface between different
// pieces and chessboard 
#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>
#include <exception>

class Piece
{
    protected:
        // I. DATA MEMBERS

        // Initialised by chessboard set up
        const std::string colour; 
        bool isPieceFirstMove; 
        // Initialised in piece specific constructors (different for each piece and never changes)
        std::string pieceName;
        bool pieceIsKing;

        //==================================================================

        // II. HELPER FUNCTIONS FOR MOVE VALIDITY

        // 1. Determines if source and destination are on the same file
        bool areOnSameFile(const std::string sourceSquare, const std::string destinationSquare) noexcept; 

        // 2. Determines if source and destination are on same rank
        bool areOnSameRank(const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 3. Determines if source and destination are on same diagonal
        bool areOnSameDiagonal(const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 4. Determines if source and destination are on adjacent files
        bool areOnAdjacentFiles(const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 5. Determines if source and destination are on adjacent ranks
        bool areOnAdjacentRanks(const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 6. Determines if path does not have any pieces along file (nothing in
        //    the way vertically)
        bool noPieceAlongFile(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 7. Determines if path does not have any pieces along rank (nothing in
        //    the way horizontally)
        bool noPieceAlongRank(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept; 

        // 8. Determines if path does not have any pieces along diagonal
        bool noPieceAlongDiagonal(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept; 

        // 9. Determines if there is a piece at the destination square
        bool destinationIsOccupied(const std::map<std::string, Piece *> *boardMap, const std::string destinationSquare) noexcept; 

        // 10. Determines if source and destination pieces are of different colours
        bool areDifferentColour(const std::map<std::string, Piece *> *boardMap, const std::string destinationSquare) noexcept;

        //==================================================================
    public:
        // III. CONSTRUCTOR/ DESTRUCTOR

        // 1. Constructor
        Piece(const std::string colour, bool isPieceFirstMove) noexcept;

        // 2. Destructor
        virtual ~Piece() noexcept = 0; 

        //==================================================================
        
        // IV. GETTER FUNCTIONS / INFO ABOUT PIECE

        // 1. Gets piece colour
        const std::string& getPieceColour() const noexcept;

        // 2. Returns whether piece is white
        bool pieceIsWhite() const noexcept; 

        // 3. Gets piece name
        const std::string& getPieceName() const noexcept; 

        // 4. Gets whether piece is king
        bool getPieceIsKing() const noexcept; 

        //==================================================================
        
        // V. MOVE VALIDITY FOR THAT PIECE & COPYING THAT PIECE

        // 1. Determines move validity based on piece specific rules
        virtual bool pieceMoveIsValid(const std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept = 0; 
    
        // 2. Duplicates the piece including the same features and returns the duplicate
        virtual Piece* duplicatePiece() noexcept = 0;

        //==================================================================

        // VI. MOVE IMPLEMENTATION

        // 1. Sets first move as having been made (called when move is
        //    implemented in chessboard, in case piece is Pawn which requires
        //    checking if first move has been made)
        void setFirstMoveDone() noexcept; 
}; 

#endif
