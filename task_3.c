//COMPILER DESIGN BASICS
//TASK - 3

#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  
#include <ctype.h>   


char *keywords[] = {
    "int", "char", "float", "double", "if", "else", "while", "for", "return", "void",
    "switch", "case", "break", "continue", "struct", "enum", "typedef", "const", "static"
};
int num_keywords = sizeof(keywords) / sizeof(char *); // Calculate number of keywords

// List of common C operators
char *operators[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "++", "--", "&", "|", "^", "~", "<<", ">>"
};
int num_operators = sizeof(operators) / sizeof(char *); // Calculate number of operators

// List of common C delimiters
char delimiters[] = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.', ':'
};
int num_delimiters = sizeof(delimiters) / sizeof(char); // Calculate number of delimiters



int isKeyword(char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

int isOperator(char *str) {
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(operators[i], str) == 0) {
            return 1; // It's an operator
        }
    }
    return 0; // Not an operator
}


int isDelimiter(char ch) {
    for (int i = 0; i < num_delimiters; i++) {
        if (delimiters[i] == ch) {
            return 1; // It's a delimiter
        }
    }
    return 0; // Not a delimiter
}


int getNextChar(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) { // Skip whitespace
            continue;
        }
        if (ch == '/') { // Possible comment or division operator
            int next_ch = fgetc(fp);
            if (next_ch == '/') { // Single-line comment //
                while ((ch = fgetc(fp)) != EOF && ch != '\n'); // Skip till newline
                if (ch == '\n') return getNextChar(fp); // Recurse to get next non-comment char
                else return EOF; // End of file in comment
            } else if (next_ch == '*') { // Multi-line comment /* */
                int prev_ch = 0;
                while ((ch = fgetc(fp)) != EOF && !(prev_ch == '*' && ch == '/')) {
                    prev_ch = ch;
                }
                if (ch == '/') return getNextChar(fp); // Recurse to get next non-comment char
                else return EOF; // End of file in comment
            } else {
                // Not a comment, it's a division operator or something else starting with /
                ungetc(next_ch, fp); // Put the next_ch back
                return '/'; // Return the division operator
            }
        }
        return ch; // Return the non-whitespace, non-comment character
    }
    return EOF; // End of file
}


void analyzeLexemes(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    printf("--- Lexical Analysis Output ---\n");
    printf("Token\t\tType\n");
    printf("-------------------------------\n");

    int ch;
    char buffer[100]; // Buffer to store lexemes
    int buffer_idx = 0;

    // Loop through the file character by character
    while ((ch = getNextChar(fp)) != EOF) {
        buffer_idx = 0; // Reset buffer for new token

        // 1. Handle Operators (check for two-character operators first)
        if (isOperator((char[]){ch, '\0'}) || (ch == '&' || ch == '|' || ch == '<' || ch == '>')) {
            int next_ch = fgetc(fp);
            buffer[buffer_idx++] = ch;
            buffer[buffer_idx] = '\0'; // Null-terminate for single char operator check

            if (next_ch != EOF) {
                char temp_op[3]; // For two-character operators (e.g., ++, ==, &&)
                temp_op[0] = ch;
                temp_op[1] = next_ch;
                temp_op[2] = '\0';

                if (isOperator(temp_op)) {
                    printf("%s\t\tOperator\n", temp_op);
                } else {
                    // It was a single-character operator, put next_ch back
                    ungetc(next_ch, fp);
                    printf("%c\t\tOperator\n", ch);
                }
            } else {
                // End of file after a single char that could be an operator
                printf("%c\t\tOperator\n", ch);
            }
            continue; // Move to the next character in the file
        }

        // 2. Handle Delimiters
        if (isDelimiter(ch)) {
            printf("%c\t\tDelimiter\n", ch);
            continue; // Move to the next character in the file
        }

        // 3. Handle Identifiers and Keywords
        if (isalpha(ch) || ch == '_') {
            buffer[buffer_idx++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[buffer_idx++] = ch;
            }
            buffer[buffer_idx] = '\0'; // Null-terminate the string

            ungetc(ch, fp); // Put the last read non-identifier char back

            if (isKeyword(buffer)) {
                printf("%s\t\tKeyword\n", buffer);
            } else {
                printf("%s\t\tIdentifier\n", buffer);
            }
            continue; // Move to the next character in the file
        }

        // 4. Handle Numbers (Integers and Floats)
        if (isdigit(ch)) {
            buffer[buffer_idx++] = ch;
            int has_decimal = 0;
            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || (ch == '.' && !has_decimal))) {
                if (ch == '.') has_decimal = 1;
                buffer[buffer_idx++] = ch;
            }
            buffer[buffer_idx] = '\0'; // Null-terminate

            ungetc(ch, fp); // Put the last read non-numeric char back
            printf("%s\t\tNumber\n", buffer);
            continue; // Move to the next character in the file
        }

        // 5. Handle String Literals (simple implementation for "...")
        if (ch == '"') {
            buffer[buffer_idx++] = ch; // Store the opening quote
            while ((ch = fgetc(fp)) != EOF && ch != '"') {
                buffer[buffer_idx++] = ch;
            }
            if (ch == '"') { // Include the closing quote
                buffer[buffer_idx++] = ch;
            }
            buffer[buffer_idx] = '\0';
            printf("%s\t\tString Literal\n", buffer);
            continue;
        }

        // 6. Handle Character Literals (simple implementation for ' ')
        if (ch == '\'') {
            buffer[buffer_idx++] = ch; // Store the opening quote
            // Read next char (the character itself)
            if ((ch = fgetc(fp)) != EOF) {
                buffer[buffer_idx++] = ch;
            }
            // Read closing quote
            if ((ch = fgetc(fp)) != EOF && ch == '\'') {
                buffer[buffer_idx++] = ch;
            }
            buffer[buffer_idx] = '\0';
            printf("%s\t\tChar Literal\n", buffer);
            continue;
        }

        // 7. Handle Unknown Characters
        printf("%c\t\tUnknown\n", ch);
    }

    fclose(fp); // Close the file
}

int main() {
    // Create a sample C input file for testing
    FILE *output_fp = fopen("input.c", "w");
    if (output_fp == NULL) {
        perror("Error creating input.c file");
        return EXIT_FAILURE;
    }
    fprintf(output_fp, "// This is a sample C program for lexical analysis\n");
    fprintf(output_fp, "/* Multi-line comment\n");
    fprintf(output_fp, "   with more lines */\n");
    fprintf(output_fp, "int main() {\n");
    fprintf(output_fp, "    int x = 10;\n");
    fprintf(output_fp, "    float pi = 3.14;\n");
    fprintf(output_fp, "    char initial = 'A';\n");
    fprintf(output_fp, "    // Another comment\n");
    fprintf(output_fp, "    if (x > 5 && pi < 4.0) {\n");
    fprintf(output_fp, "        x++; // Increment x\n");
    fprintf(output_fp, "        printf(\"Hello, World!\\n\");\n");
    fprintf(output_fp, "    } else {\n");
    fprintf(output_fp, "        return 0;\n");
    fprintf(output_fp, "    }\n");
    fprintf(output_fp, "    /* End of program */\n");
    fprintf(output_fp, "    return x;\n");
    fprintf(output_fp, "}\n");
    fclose(output_fp);
    printf("Created 'input.c' for demonstration.\n\n");

    analyzeLexemes("input.c"); // Perform lexical analysis on the created file

    return 0;
}
