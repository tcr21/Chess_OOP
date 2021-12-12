// Chessboard implementation file

#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <exception>

#include "ChessBoard.h"

using namespace std; 

// I. HELPER FUNCTIONS FOR RESET BOARD

// 1. 
void ChessBoard::deleteBoard(map<string, Piece *>* boardMap) noexcept
{
    for (map<string, Piece *>::iterator itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Deletes space of memory that each Piece pointer on the map points to,
        // allocated to the pieces
        delete itr->second;
    } 
    // Delete space in memory that the map pointer points to, allocated to the
    // map itself
    delete boardMap; 
}

// 2. 
void ChessBoard::setUpBoard() noexcept
{
    setUpGameConditions(); 
    setUpWhitePieces();
    setUpBlackPieces();
    setUpWhitePawns(); 
    setUpBlackPawns(); 
    cout << "A new chess game is started! \n"; 
}

//==================================================================

// II. SUB-HELPER FUNCTIONS FOR SET UP BOARD

// 1. 
void ChessBoard::setUpGameConditions() noexcept
{
    isWhitesTurn = true; 
    gameIsOver = false; 
}

// 2. 
void ChessBoard::setUpWhitePieces() noexcept
{
    boardMap->insert(pair<string, Piece *>("A1", new Rook(WHITE, isPieceFirstMoveTrue)));
    boardMap->insert(pair<string, Piece *> ("B1", new Knight(WHITE, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("C1", new Bishop(WHITE, isPieceFirstMoveTrue)));
    boardMap->insert(pair<string, Piece *> ("D1", new Queen(WHITE, isPieceFirstMoveTrue)));
    boardMap->insert(pair<string, Piece *> ("E1", new King(WHITE, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("F1", new Bishop(WHITE, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("G1", new Knight(WHITE, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *>("H1", new Rook(WHITE, isPieceFirstMoveTrue)));
}

// 3.
void ChessBoard::setUpBlackPieces() noexcept
{
    boardMap->insert(pair<string, Piece *>("A8", new Rook(BLACK, isPieceFirstMoveTrue)));
    boardMap->insert(pair<string, Piece *> ("B8", new Knight(BLACK, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("C8", new Bishop(BLACK, isPieceFirstMoveTrue)));
    boardMap->insert(pair<string, Piece *> ("D8", new Queen(BLACK, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("E8", new King(BLACK, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("F8", new Bishop(BLACK, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *> ("G8", new Knight(BLACK, isPieceFirstMoveTrue))); 
    boardMap->insert(pair<string, Piece *>("H8", new Rook(BLACK, isPieceFirstMoveTrue)));
}

// 4. 
void ChessBoard::setUpWhitePawns() noexcept
{
    string pawnPosition; 
    for (char pawnFile = 'A'; pawnFile <= 'H'; pawnFile++)
    {
        pawnPosition = string() + pawnFile + whitePawnInitialRank; 
        boardMap->insert(pair<string, Piece *>(pawnPosition, new Pawn(WHITE, isPieceFirstMoveTrue)));
    }
}

// 5. 
void ChessBoard::setUpBlackPawns() noexcept
{
    string pawnPosition; 
    for (char pawnFile = 'A'; pawnFile <= 'H'; pawnFile++)
    {
        pawnPosition = string() + pawnFile + blackPawnInitialRank; 
        boardMap->insert(pair<string, Piece *>(pawnPosition, new Pawn(BLACK, isPieceFirstMoveTrue)));
    }
}

//==================================================================

// III. HELPER FUNCTIONS FOR SUBMIT MOVE (A): ERROR CHECKING

// 1. 
void ChessBoard::inputLengthIsValid(const string& square)
{
    int length = square.length();
    if (length != MAX_INPUT_LENGTH)
    {
        throw InputLengthError(" has an invalid input length! ", square); 
    }
}

// 2. 
void ChessBoard::inputCharactersAreValid(const string& square)
{
    char squareFile = square[0];
    char squareRank = square[1];
    // Check file
    if (squareFile < MIN_POSITION_FILE_DEC || squareFile > MAX_POSITION_FILE_DEC)
    {
        throw InputCharacterError(" position's file has an invalid character! ", square);
        return;
    }
    // Check rank
    if (squareRank < MIN_POSITION_RANK_DEC || squareRank > MAX_POSITION_RANK_DEC)
    {
        throw InputCharacterError(" position's rank has an invalid character! ", square);
        return; 
    }
}

// 3. 
void ChessBoard::sourceHasPiece(const string& sourceSquare)
{
    if (boardMap->find(sourceSquare) == boardMap->end())
    {
        throw HasNoPieceError("There is no piece at position ", sourceSquare);
        return; 
    } 
}

// 4. 
void ChessBoard::sourceDestinationAreDifferent(const string& sourceSquare, const string& destinationSquare)
{
    if (sourceSquare == destinationSquare)
    {
        throw SameSourceDestinationError(" are the same! ", sourceSquare, destinationSquare); 
    }
}

// 5. 
void ChessBoard::rightPlayersTurn(const string& colour, const bool isWhitesTurn)
{
    if ((colour == WHITE && isWhitesTurn == false) || (colour == BLACK && isWhitesTurn == true))
    {
        throw WrongPlayersTurnError("turn to move! ", colour); 
    }
}

//==================================================================

// IV. HELPER FUNCTIONS FOR SUBMIT MOVE (B): GAME IN CHECK RULES & IMPLEMENTATION

// 1. 
string ChessBoard::findMyKing(const map<string, Piece *> *boardMap) noexcept
{
    // Declare iterator to loop through map
    map<string, Piece *>::const_iterator itr; 
    // Go through the map (ie. where there are pieces)
    for (itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Set square to equal key (first of pair in map), and piece to equal
        // value (second of pair in map)
        string pieceSquare = itr->first;
        Piece* piece = itr->second; 
        // If piece is mine (ie whether the piece is white or not matches
        // whether it is currently white's turn or not) AND if the piece is a
        // king, then return the key that maps to that king
        if ( (piece->pieceIsWhite() == isWhitesTurn) && (piece->getPieceIsKing() == true))
        {
            return pieceSquare;
        }
    }
    cout << "Could not find my king \n"; 
    return NULL; 
}

// 2. 
string ChessBoard::findOpponentsKing(const map<string, Piece *> *boardMap) noexcept
{
    // Declare iterator to loop through map
    map<string, Piece *>::const_iterator itr; 
    // Go through the map (ie. where there are pieces)
    for (itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Set square to equal key (first of pair in map), and piece to equal
        // value (second of pair in map)
        string pieceSquare = itr->first;
        Piece* piece = itr->second; 
        // If piece is opponent's (ie whether the piece is white or not DOES NOT
        // match whether it is currently white's turn or not) AND if the piece
        // is a king, then return the key that maps to that king
        if ( (piece->pieceIsWhite() != isWhitesTurn) && (piece->getPieceIsKing() == true))
        {
            return pieceSquare; 
        }
    }
    cout << "Could not find opponent's king \n"; 
    return NULL; 
}

// 3. 
bool ChessBoard::myKingIsSafe(const map<string, Piece *> *boardMap) noexcept
{
    // Find square where my king is
    string myKingSquare = findMyKing(boardMap); 
    
    // Declare iterator to loop through map
    map<string, Piece *>::const_iterator itr; 
    // Go through the map (ie. where there are pieces)
    for (itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Set pieceSquare to equal key (first of pair in map), and piece to
        // equal value (second of pair in map)
        string pieceSquare = itr->first;
        Piece* piece = itr->second; 
        // If piece is my opponent's (ie whether the piece is white or not DOES NOT match
        // whether it is currently white's turn or not) AND there exists a valid
        // move for it to make from its current position to take my king, then
        // my king is not safe
        if ( (piece->pieceIsWhite() != isWhitesTurn) && (piece->pieceMoveIsValid(boardMap, pieceSquare, myKingSquare)) )
        {
            return false; 
        }
    }
    return true; 
}

// 4. 
bool ChessBoard::opponentsKingIsSafe(const map<string, Piece *> *boardMap) noexcept
{
    // Find square where opponent's king is
    string opponentsKingSquare = findOpponentsKing(boardMap); 
    
    // Declare iterator to loop through map
    map<string, Piece *>::const_iterator itr; 
    // Go through the map (ie. where there are pieces)
    for (itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Set square to equal key (first of pair in map), and piece to equal
        // value (second of pair in map)
        string pieceSquare = itr->first;
        Piece* piece = itr->second; 
        // If piece is mine (ie whether the piece is white or not matches
        // whether it is currently white's turn or not) AND there exists a valid
        // move for it to make from its current position to take opponent's king, then
        // opponent's king is not safe
        if ( (piece->pieceIsWhite() == isWhitesTurn) && (piece->pieceMoveIsValid(boardMap, pieceSquare, opponentsKingSquare)) ) 
        {
            return false; 
        }
    }
    return true; 
}

// 5. 
map<string, Piece *>* ChessBoard::duplicateBoard(map<string, Piece *> *boardMap) noexcept
{
    // Create a new board map
    map<string, Piece *>* boardMapCopy = new map<string, Piece *>; 

    // Declare iterator to loop through current board map 
    map<string, Piece *>::const_iterator itr;
    // Insert a duplicate of each piece into the new board copy, at the piece's
    // current position
    for (itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Set pieceSquare to equal key (first of pair in map), and piece to
        // equal value (second of pair in map)
        string pieceSquare = itr->first;
        Piece* piece = itr->second; 
        // Insert piece copies into new map copy
        boardMapCopy->insert(pair<string, Piece *> (pieceSquare, piece->duplicatePiece()));
    }
    return boardMapCopy;
}

// 6.
void ChessBoard::implementMove(map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare, const bool move) noexcept
{
    // Declare sourcePiece variable
    Piece* sourcePiece = boardMap->find(sourceSquare)->second;
    // Declare string variable that will say if a piece is being captured
    string captureMessage = ""; 
    // If there is a piece at the destination
    if (boardMap->find(destinationSquare) != boardMap->end())
    {
        // Get that piece (it is being taken)
        Piece* destinationPiece = boardMap->find(destinationSquare)->second; 
        // Add to the capture message
        captureMessage = " taking " + destinationPiece->getPieceColour() + "'s " + destinationPiece->getPieceName(); 
        // Delete the taken piece from the board
        delete destinationPiece; 
        // Replace it at its position with the source piece (the latter is being moved)
        boardMap->find(destinationSquare)->second = sourcePiece;
    }
    // If the destination is empty, just insert a new pair in the map with the
    // destination square and source piece (which is being moved)
    else
    {
        boardMap->insert(pair<string, Piece *> (destinationSquare, sourcePiece));
    }
    // Remove the source pair from the map (note the source piece has been moved
    // to the destination square already). Note: erase() function removes the
    // pair with the given key from the map
    boardMap->erase(sourceSquare); 
    // Set the piece's first move as being done
    sourcePiece->setFirstMoveDone(); 

    // Only print out the capture message if this was a real move as opposed to
    // a simulated one (in the latter case, implementMove would be being applied
    // to a board copy).
    if (move == realMove)
    {
        cout << sourcePiece->getPieceColour() << "'s " << sourcePiece->getPieceName() << " moves from " << sourceSquare << " to " << destinationSquare << captureMessage << endl; 
    }
}

// 7. 
bool ChessBoard::myKingWouldBeSafe(map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // Copy the board
    map<string, Piece *> *boardMapCopy = duplicateBoard(boardMap);
    // Implement the move currently under consideration on the copy of the board
    implementMove(boardMapCopy, sourceSquare, destinationSquare, simulatedMove); 
    // Check if my king is safe in the simulated game (on the board copied, with
    // the move having been made on it)
    if (myKingIsSafe(boardMapCopy))
    {
        deleteBoard(boardMapCopy);
        return true; 
    } 
    deleteBoard(boardMapCopy);
    return false;
}

// 7. 
bool ChessBoard::opponentsKingWouldBeSafe(map<string, Piece *> *boardMap, const string sourceSquare, const string destinationSquare) noexcept
{
    // Copy the board
    map<string, Piece *> *boardMapCopy = duplicateBoard(boardMap);
    // Implement the move currently under consideration on the copy of the board
    implementMove(boardMapCopy, sourceSquare, destinationSquare, simulatedMove); 
    // Check if my king is safe in the simulated game (on the board copied, with
    // the move having been made on it)
    if (opponentsKingIsSafe(boardMapCopy))
    {
        deleteBoard(boardMapCopy);
        return true; 
    } 
    deleteBoard(boardMapCopy);
    return false;
}

// 9. 
bool ChessBoard::validMovesLeftForOpponent(map<string, Piece *> *boardMap) noexcept
{
    // Declare iterator to loop through board map
    map<string, Piece *>::const_iterator itr;
    // Loop through all pieces on map
    for (itr = boardMap->begin(); itr != boardMap->end(); itr++)
    {
        // Set pieceSquare to equal key (first of pair in map), and piece to
        // equal value (second of pair in map)
        string pieceSquare = itr->first;
        Piece* piece = itr->second; 
        // If the piece is my opponent's (ie whether the piece is white and
        // whether it is currently white's turn DO NOT match)
        if (piece->pieceIsWhite() != isWhitesTurn)
        {
            // Loop through all squares on the map as potential destinations
            for (char file = MIN_POSITION_FILE_DEC; file <= MAX_POSITION_FILE_DEC; file++)
            {
                for (char rank = MIN_POSITION_RANK_DEC; rank <= MAX_POSITION_RANK_DEC; rank++)
                {
                    
                    string potentialDestinationSquare = string() + file + rank; 
                    // If the piece could go to that destination respecting
                    // piece specific rules 
                    if (piece->pieceMoveIsValid(boardMap, pieceSquare, potentialDestinationSquare))
                    {
                        // Move is potentially valid
                        bool moveIsValid = true;
                        // If their king would not be safe if they did the move
                        if (!opponentsKingWouldBeSafe(boardMap, pieceSquare, potentialDestinationSquare))
                        {
                            // The move is not valid. Keep looping
                            moveIsValid = false;
                        }
                        if (moveIsValid)
                        {
                            return true; 
                        }
                    }
                }
            }
        }
    }
    return false; 
}

//==================================================================

// V. PUBLIC FUNCTIONS

// 1.
void ChessBoard::submitMove(const string sourceSquare, const string destinationSquare)
{
    // a. Check if the game is over
    if (gameIsOver == true)
    {
        cout << "Game is over. Please reset the board to play again. \n"; 
        return; 
    }
    
    // b. Check for input & move submission errors
    try
    {
        inputLengthIsValid(sourceSquare); 
        inputLengthIsValid(destinationSquare); 
        inputCharactersAreValid(sourceSquare);
        inputCharactersAreValid(destinationSquare);
        sourceHasPiece(sourceSquare);
        sourceDestinationAreDifferent(sourceSquare, destinationSquare);
        // Find() function below returns iterator which points to map pair that
        // has sourceSquare as key. Second is the corresponding value ie. the
        // piece, through which we access colour
        rightPlayersTurn(boardMap->find(sourceSquare)->second->getPieceColour(), isWhitesTurn); 
    }
    catch (const InputLengthError& e)
    {
        cout << e.getSquare() << e.what() << endl; 
        return; 
    }
    catch (const InputCharacterError& e)
    {
        cout << e.getSquare() << e.what() << endl; 
        return; 
    }
    catch (const HasNoPieceError& e)
    {
        cout << e.what() << e.getSquare() << "! \n"; 
        return; 
    }
    catch (const SameSourceDestinationError& e)
    {
        cout << "Source " << e.getSquare() << " and destination " << e.getSecondSquare() << e.what() << endl; 
        return; 
    }
    catch (const WrongPlayersTurnError& e)
    {
        cout << "It is not " << e.getPieceColour() << "'s " << e.what() << endl; 
        return; 
    }
    catch (const exception& e)
    {
        cout << e.what() << endl; 
        return;
    }

    // c. Set sourcePiece variable and cannot move message
    Piece* sourcePiece = boardMap->find(sourceSquare)->second;
    string cannotMoveMessage = sourcePiece->getPieceColour() + "'s " + sourcePiece->getPieceName() + " cannot move to " + destinationSquare + "! \n";

    // d. Check move is valid for that piece (respects piece-specific rules)
    if (!(sourcePiece->pieceMoveIsValid(boardMap, sourceSquare, destinationSquare)))
    {
        cout << cannotMoveMessage;
        return; 
    }

    // e. If my (current player's) king is safe, and my move would not leave my
    // king safe, then I cannot make the move as I am not allowed to endanger my
    // own king
    if ( myKingIsSafe(boardMap) 
    && !myKingWouldBeSafe(boardMap, sourceSquare, destinationSquare) )
    {
        cout << cannotMoveMessage; 
        return; 
    }

    // f. Implement the move now that its validity has been checked
    implementMove(boardMap, sourceSquare, destinationSquare, realMove); 

    // g. Game is potentially not in check
    gameIsInCheck = false; 

    // h. Get opponent's colour
    string opponentsColour = "";
    if (isWhitesTurn)
    {
        opponentsColour = BLACK;
    }
    else
    {
        opponentsColour = WHITE;
    }

    // i. Check for check, checkmate, stalemate

    // If opponent is in check, set game is in check game condition to true
    if (!opponentsKingIsSafe(boardMap))
    {
        gameIsInCheck = true;
    }

    // If valid moves left for opponent, then the oponnent is in check
    if (validMovesLeftForOpponent(boardMap))
    {
        if (gameIsInCheck)
        {
            cout << opponentsColour << " is in check \n";
        }
    }
    // If no valid moves left for opponent
    else
    {
        // and the opponent is in check, then they are in checkmate
        if (gameIsInCheck)
        {
            cout << opponentsColour << " is in checkmate \n";
        }
        // and the opponent is not in check, then they are in stalemate
        else 
        {
            cout << opponentsColour << " is a stalemate \n"; 
        }
        gameIsOver = true; 
    }
    
    // j. Swap player's turn
    isWhitesTurn = !isWhitesTurn; 
    return; 
}

// 2. 
void ChessBoard::resetBoard() noexcept
{
    deleteBoard(boardMap);
    boardMap = new map<string, Piece *>;
    isWhitesTurn = true;
    gameIsInCheck = false;
    gameIsOver = false; 
    setUpBoard(); 
}

// 3. 
ChessBoard::ChessBoard() noexcept
{
    boardMap = new map<string, Piece *>; 
    isWhitesTurn = true;
    gameIsInCheck = false;
    gameIsOver = false; 
    setUpBoard();
}

// 4. 
ChessBoard::~ChessBoard(){};
