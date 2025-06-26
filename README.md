# COMPILER-DESIGN-BASICS

COMPANY: CODTECH IT SOLUTIONS

NAME: ABHIJEET KUMAR

INTERN ID:

DOMAIN: C LANGUAGE

DURATION: 4 WEEKS

MENTOR: NEELA SANTOSH

DESCRIPTION: This C program for lexical analysis was written and tested in a modern code editor such as Visual Studio Code, a widely-used and powerful Integrated Development Environment (IDE) that supports multiple programming languages, including C and C++. The code can be typed into a new file with the .c extension, such as lexer.c, using Visual Studio Code’s syntax highlighting and auto-completion features for better readability and efficiency. After writing the code, the GCC (GNU Compiler Collection) compiler can be used through an integrated terminal or command-line interface to compile and run the program. The purpose of this code is to simulate the behavior of a lexical analyzer — a fundamental component in the front end of a compiler that reads source code and breaks it down into meaningful tokens such as keywords, identifiers, operators, delimiters, numbers, string literals, and character literals. The code starts by defining arrays for C language keywords, operators, and delimiters, and includes several helper functions like isKeyword, isOperator, and isDelimiter to check the classification of tokens. It also features a crucial function named getNextChar, which reads characters from a file while skipping whitespaces and ignoring both single-line and multi-line comments. The main function first creates a sample C source code file (input.c) containing various language elements like loops, conditionals, variables, and comments to serve as input for lexical analysis. The analyzeLexemes function then reads this file character by character, processes the input through multiple logical conditions, and prints out each detected lexeme along with its token type in a formatted table. It is capable of recognizing multi-character operators (such as ==, ++, >=, &&), numeric constants (both integers and floating-point numbers), and properly enclosed string and character literals. The implementation includes a buffer to temporarily hold each lexeme while it is being constructed, and uses ungetc() to put back characters when necessary, ensuring the correct sequence of reading. If a character or sequence does not match any known type, it is marked as "Unknown." This code provides a clear and functional example of how lexical analysis works at a basic level in compiler design, demonstrating token recognition, pattern matching, and handling of comments and literals. It’s an educational tool for understanding how a compiler interprets raw source code and converts it into a sequence of tokens that can be further processed by parsers and code generators. By using Visual Studio Code, the development experience becomes smoother, with helpful extensions, debugging capabilities, and terminal integration to test the code efficiently. Thus, this project serves as both a practical exercise in C programming and an introduction to compiler construction concepts.

OUTPUT:

