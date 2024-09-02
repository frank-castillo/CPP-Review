//
// Created by juanf on 2024-02-13.
//
#include <string>
#include <cstring>
#include <iostream>

// Bad practice! Used for ease of code
using namespace std;

enum class ChessPiece {
    Empty = 0,
    Pawn,
    Rook,
    Knight,
    Bishop,
    King,
    Queen
};

int strings_main() {
    // C-style string.
    // String literals are turned into this type of array.
    // Compiler automatically adds the null character.
    char sayHello[] = {'H','e','l','l','o',' ', 'w','o','r','l','d','\0'};
    cout << sayHello << endl;
    cout << "Size of array: " << sizeof(sayHello) << endl;

    // Be mindful where you put the null character!
    // Wherever the compiler finds it, it will stop string processing at that point.
    // However, it won't change the size of the array...
    char sayHel[] = {'H','e','l','\0','l','o',' ', 'w','o','r','l','d'};
    cout << sayHel << endl;
    // Only outputs "Hel" but in memory it still occupies space for the whole phrase.
    cout << "Size of array: " << sizeof(sayHel) << endl;
    // Same size as the first array but the whole phrase is not printed out.

    // If you forget the null character, you will get unexpected behaviour.
    sayHel[3] = 't';
    cout << sayHel << endl;

    // C strings are risky, especially when handling user input.
    // You can run into buffer overflow for not having the adequate space to hold the data.
    char userInput[21];
    cout << "Enter a line no longer than 20 characters:" << endl;
    //cin >> userInput;

    cout << "Length of your input was:" << strlen(userInput) << endl;
    cout << "Your line is: " << userInput << endl;
    // If you input a sentence longer than 20 characters you run into buffer overflow.
    // After the limit is reached, characters after this will be ignored as there has to be space for the null char.
    // This is a vulnerability you should be aware of!

    // Functions that take c-style strings are dangerous as it can be prone to errors involving the null char.
    // Better to use strings than c-style for more secure string operations.
    // String allows for manipulation and resizing of the buffer as needed.

    string firstString ("Hello, I am a string!");
    cout<< firstString << endl;

    string secondString;
    cout << "Enter a text:" << endl;
    std::getline(cin, secondString);

    string thirdString;
    cout << "Enter another text:" << endl;
    std::getline(cin, thirdString);

    const string concetenateString = secondString + " " + thirdString;
    cout << "Concatenation of strings: " << concetenateString << endl;

    string copyString = concetenateString;
    copyString += "And you will obery";
    cout << "Copied string says: " << copyString << endl;

    // As seen by the examples above, strings are more versatile. They can be resized, concatenated, initialized, etc.
    // Strings also provide more functionality and more optimized ways to access its content.

    // test case
    ChessPiece ChessBoard[8][8];

    // This can be turned into a for loop!
    // ChessBoard[1][0] = ChessPiece::Pawn;
    // ChessBoard[1][1] = ChessPiece::Pawn;
    // ChessBoard[1][2] = ChessPiece::Pawn;
    // ChessBoard[1][3] = ChessPiece::Pawn;
    // ChessBoard[1][4] = ChessPiece::Pawn;
    // ChessBoard[1][5] = ChessPiece::Pawn;
    // ChessBoard[1][6] = ChessPiece::Pawn;
    // ChessBoard[1][7] = ChessPiece::Pawn;

    for(int j = 0; j < 8; ++j) {
        ChessBoard[1][j] = ChessPiece::Pawn;
    }

    return 0;
}
