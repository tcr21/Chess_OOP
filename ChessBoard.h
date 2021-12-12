// PLEASE NOTE THIS FILE CONTAINS BOTH EXCEPTIONS AND CHESSBOARD HEADER 
// LAB TS TEST DID NOT PASS WHEN I HAD A SEPARATE .H FILE FOR EXCEPTIONS (EVEN THOUGH MY PROGRAM COMPILED ON THE LAB COMPUTERS)

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <exception>

#include "Piece.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

//============================================================================================================

// CHESSBOARD HEADER FILE

class ChessBoard
{
    private:
        // I. DATA MEMBERS

        // Constants
        const int MAX_INPUT_LENGTH = 2; 
        const int MIN_POSITION_FILE_DEC = 65; // A character in decimal
        const int MAX_POSITION_FILE_DEC = 72; // H character in decimal
        const int MIN_POSITION_RANK_DEC = 49; // 1 character in decimal
        const int MAX_POSITION_RANK_DEC = 56; // 8 character in decimal
        const std::string WHITE = "White"; 
        const std::string BLACK = "Black";
        const bool isPieceFirstMoveTrue = true; 
        const char whitePawnInitialRank = '2'; 
        const char blackPawnInitialRank = '7'; 
        const bool realMove = true; 
        const bool simulatedMove = false; 

        // Pointer to board map
        std::map<std::string, Piece *> *boardMap;

        // Game conditions
        bool isWhitesTurn; 
        bool gameIsInCheck;
        bool gameIsOver;

        //==================================================================

        // II. HELPER FUNCTIONS FOR RESET BOARD 

        // 1. Deletes the previous board
        void deleteBoard(std::map<std::string, Piece *> *boardMap) noexcept;

        // 2. Sets up a new board
        void setUpBoard() noexcept; 

        //==================================================================

        // III. SUB-HELPER FUNCTIONS FOR SET UP BOARD

        // 1. Initialises game conditions: who's turn (white), in check (no), game over (no)
        void setUpGameConditions() noexcept; 

        // 2. Inserts white pieces onto board at start of game
        void setUpWhitePieces() noexcept;

        // 3. Inserts black pieces onto board at start of game
        void setUpBlackPieces() noexcept; 

        // 4. Inserts white pawns on rank 2 at start of game
        void setUpWhitePawns() noexcept; 

        // 5. Inserts black pawns on rank 7 at start of game
        void setUpBlackPawns() noexcept; 


        //==================================================================
        
        // IV. HELPER FUNCTIONS FOR SUBMIT MOVE (A): ERROR CHECKING (use of exceptions)

        // 1. Checks lengths of input source and destination are valid
        void inputLengthIsValid(const std::string& square); 

        // 2. Checks characters of input source and destination are valid
        void inputCharactersAreValid(const std::string& square); 

        // 3. Checks there is a piece at the source
        void sourceHasPiece(const std::string& sourceSquare);

        // 4. Checks source and destination are not equal
        void sourceDestinationAreDifferent(const std::string& sourceSquare, const std::string& destinationSquare);

        // 5. Checks it is the right player's turn
        void rightPlayersTurn(const std::string& colour, const bool isWhitesTurn);

        //==================================================================

        // V. HELPER FUNCTIONS FOR SUBMIT MOVE (B): GAME IN CHECK RULES & IMPLEMENTATION

        // 1. Finds the current player's king
        std::string findMyKing(const std::map<std::string, Piece *> *boardMap) noexcept; 

        // 2. Finds the opponent's king
        std::string findOpponentsKing(const std::map<std::string, Piece *> *boardMap) noexcept; 
        
        // 3. Determines if current player's king is safe
        bool myKingIsSafe(const std::map<std::string, Piece *> *boardMap) noexcept;

        // 4. Determines if opponent's king is safe
        bool opponentsKingIsSafe(const std::map<std::string, Piece *> *boardMap) noexcept;
    
        // 5. Duplicates the board
        std::map<std::string, Piece *>* duplicateBoard(std::map<std::string, Piece *> *boardMap) noexcept; 
        
        // 6. Implements the current player's move
        void implementMove(std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare, bool move) noexcept; 

        // 7. Determines if the move were to be implemented, would the current
        //    player's king be safe
        bool myKingWouldBeSafe(std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 8. Determines if the move were to be implemented, would the
        //    opponent's king be safe
        bool opponentsKingWouldBeSafe(std::map<std::string, Piece *> *boardMap, const std::string sourceSquare, const std::string destinationSquare) noexcept;

        // 9. Determines if there are valid moves left for opponent, that would
        //    make their king safe
        bool validMovesLeftForOpponent(std::map<std::string, Piece *> *boardMap) noexcept;
        
        //==================================================================

    public: 
        // VI. PUBLIC FUNCTIONS
        
        // 1. Takes in move input, checks if it is valid, and implements it
        void submitMove(const std::string sourceSquare, const std::string destinationSquare);

        // 2. Deletes the old board and sets up a new one
        void resetBoard() noexcept; 

        // 3. Constructor
        ChessBoard() noexcept; 

        // 4. Destructor
        ~ChessBoard(); 

}; 

//============================================================================================================

// EXCEPTIONS HEADER FILE

// I. ANY ERROR CLASS: explanation
class AnyError : public std::exception
{
    protected:
        std::string explanation;
    
    public:
        // 1. Constructor
        AnyError(const std::string& message) noexcept; 
        // 2. Overrides standard exception virtual what() function
        const char* what() const noexcept override; 
}; 

//==================================================================

// II. POSITION (SQUARE) ERROR CLASS: inherits from any error class. Adds square
// data member & get square function
class PositionError : public AnyError
{
    protected:
        std::string square; 
    public:
        // 1. Constructor
        PositionError(const std::string& message, const std::string& square) noexcept; 
        // 2. Gets square
        const std::string & getSquare() const noexcept; 
}; 

//==================================================================

// III. INPUT LENGTH ERROR CLASS: inherits from position error class. Does not
// add anything, but has a different meaning so is defined as separate error
// class
class InputLengthError : public PositionError 
{
    public:
        // 1. Constructor
        InputLengthError(const std::string& message, const std::string& square) noexcept;
}; 

//==================================================================

// IV. INPUT CHARACTERS ERROR CLASS: inherits from position error class. Does
// not add anything, but has a different meaning so is defined as separate error
// class
class InputCharacterError : public PositionError 
{
    public:
        // 1. Constructor
        InputCharacterError(const std::string& message, const std::string& square) noexcept;
}; 

//==================================================================

// V. HAS NO PIECE AT GIVEN POSITION ERROR CLASS: inherits from position error
// class. Does not add anything, but has a different meaning so is defined as
// separate error class
class HasNoPieceError : public PositionError 
{
    public:
        // 1. Constructor
        HasNoPieceError(const std::string& message, const std::string& square) noexcept;
}; 

//==================================================================

// VI. SOURCE AND DESTINATION ARE THE SAME ERROR CLASS: inherits from position
// error class. Adds second square data member & get second square function,
// since error stems from source and destination squares being the same
class SameSourceDestinationError : public PositionError
{
    private:
        std::string secondSquare; 
    public:
        // 1. Constructor
        SameSourceDestinationError(const std::string& message, const std::string& square, const std::string& secondSquare) noexcept; 
        // 2. Gets second square
        const std::string& getSecondSquare() const noexcept; 
}; 

//==================================================================

// VII. NOT PLAYER'S TURN ERROR CLASS: inherits from any error class. Adds
// colour data member & get colour function
class WrongPlayersTurnError : public AnyError
{
    private:
        const std::string colour;
    public: 
        // 1. Constructor
        WrongPlayersTurnError(const std::string& message, const std::string& colour) noexcept; 
        // 2. Gets colour
        const std::string& getPieceColour() const noexcept; 
}; 


#endif


