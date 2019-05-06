#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<fstream>
#include"token.h"
#include"scanner.h"
#include"parser.h"
#include"semantics.h"

string determineTokenID(enum tokenID);

int main(int argc, char* argv[])
{
	//Setting variables.
	FILE *fp;
	int c;
	string buffer;
	Node_t* root;

	vector<Token> tokens;

	//Error if the user invokes with more than 2 command line arguments.
	if(argc > 2)
	{
		perror("Error: too many arguments.\n");	
	}
	
	//Set up keyboard processing so that below the input is not relevant.
	if(argc < 2)
	{	
		//Setting fp for stdin keyboard entry.
		fp = stdin;
		
		do {
		c = getc(fp);
		buffer.append(1, c);
		} while (c != EOF);
		
		//Calling scanner function then parse function.
		tokens = scanner(buffer);

		/*int x;
                for (int x = 0; x < tokens.size(); ++x)
                {
                 	cout << "{" << determineTokenID(tokens[x].id) << ",";
                        cout << " " << tokens[x].instance << ",";
                        cout << " " << tokens[x].lineNumber << "}" << endl;
                }*/

		root = parser(tokens);
		semantics(root);
		//printPreorder(root, 0);	

		fclose(fp);
	}

	//Process command line arguments and make sure file is readable, error otherwise.
	if(argc == 2)
	{
		//Setting variables.
		char* filename = argv[1];

		//Opening file & error checking.
		fp = fopen(filename, "r");

		if(fp == NULL)
		{
			printf("Program error file %s not found.\n", filename);
			return 1;
		}
		else
		{
			do {
			c = getc(fp);
			buffer.append(1, c);
			} while (c != EOF);

			//Calling scanner function then parse function.
			tokens = scanner(buffer);

			/*int x;
			for (int x = 0; x < tokens.size(); ++x)
        		{
				cout << "{" << determineTokenID(tokens[x].id) << ",";
                		cout << " " << tokens[x].instance << ",";
                		cout << " " << tokens[x].lineNumber << "}" << endl;
        		}*/	

			root = parser(tokens);
			semantics(root);
			//printPreorder(root, 0);

			fclose(fp);
		}
	}

	return 0;
}

string determineTokenID(tokenID enumID)
{
	switch(enumID)
	{
		case 0:
			return "IDENT_tk";
			break;
		case 1:
			return "NUM_tk";
			break;
		case 2:
                        return "KW_tk";
                        break;
		case 3:
                        return "CMNT_tk";
                        break;
		case 4:
                        return "EOF_tk";
                        break;
		case 5:
                        return "BEGIN_tk";
                        break;
		case 6:
                        return "END_tk";
                        break;
		case 7:
                        return "LOOP_tk";
                        break;
		case 8:
                        return "VOID_tk";
                        break;
		case 9:
                        return "INT_tk";
                        break;
		case 10:
                        return "RETURN_tk";
                        break;
		case 11:
                        return "READ_tk";
                        break;
		case 12:
                        return "OUTPUT_tk";
                        break;
		case 13:
                        return "PROGRAM_tk";
                        break;
		case 14:
                        return "IFF_tk";
                        break;
		case 15:
                        return "THEN_tk";
                        break;
		case 16:
                        return "LET_tk";
                        break;
		case 17:
                        return "EQUAL_tk";
                        break;
		case 18:
                        return "LESS_tk";
                        break;
		case 19:
                        return "GREATER_tk";
                        break;
		case 20:
                        return "COLON_tk";
                        break;
		case 21:
                        return "ADDITION_tk";
                        break;
		case 22:
                        return "SUBTRACTION_tk";
                        break;
		case 23:
                        return "MULTIPLY_tk";
                        break;
		case 24:
                        return "DIVIDE_tk";
                        break;
		case 25:
                        return "PERCENT_tk";
                        break;
		case 26:
                        return "PERIOD_tk";
                        break;
		case 27:
                        return "OPEN_PAREN_tk";
                        break;
		case 28:
                        return "CLOSE_PAREN_tk";
                        break;
		case 29:
                        return "COMMA_PAREN_tk";
                        break;
		case 30:
                        return "OPEN_CURLY_tk";
                        break;
		case 31:
                        return "CLOSE_CURLY_tk";
                        break;
		case 32:
                        return "SEMI_COLON_tk";
                        break;
		case 33:
                        return "OPEN_BRACKET_tk";
                        break;
		case 34:
                        return "CLOSE_BRACKET_tk";
                        break;
	}
}
