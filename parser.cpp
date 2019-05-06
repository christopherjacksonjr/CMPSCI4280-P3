#include<stdio.h>
#include<iostream>
#include"parser.h"
#include"scanner.h"
#include"token.h"

using namespace std;

int i;
Token token;

Node_t* parser(vector<Token> &tokens)
{
	//Function declarations.
	Node_t* root;
	i = 0;
	
	//Grabbing the first token.
	token = tokens[i];
	
	//Calling first function in grammar.
	root = program(tokens);
	if(token.id == EOF_tk)
	{
		return root;
	}
	else
	{
		error("Error: Expected EOF token.");
		return NULL;
	}
}

Node_t* program(vector<Token> &tokens)
{
	Node_t* program_node = getNode(Program);

	program_node->left_child = vars(tokens);
	program_node->right_child = block(tokens);
		
	return program_node;
}

Node_t* vars(vector<Token> &tokens)
{
	Node_t* vars_node = getNode(Vars);

	if(token.id == INT_tk)
	{
		i++;
		token = tokens[i];

		if(token.id == IDENT_tk)
		{
			vars_node->token = token;
			i++;
			token = tokens[i];

			if(token.id == NUM_tk)
			{
				vars_node->token2 = token;
				i++;
				token = tokens[i];
				vars_node->left_child = vars(tokens);
				return vars_node;
			}
			else
			{
				error("Error: Expected NUMBER token.");
			}
		}
		else
		{
			error("Error: Expected IDENTIFIER token.");
		}
	}
	else //predicts empty
	{
		return NULL;
	}
}

Node_t* block(vector<Token> &tokens)
{
	Node_t* block_node = getNode(Block);

	if(token.id == BEGIN_tk)
	{
		i++;
		token = tokens[i];
		block_node->left_child = vars(tokens);
		block_node->right_child = stats(tokens);

		if(token.id = END_tk)
		{
			i++;
			token = tokens[i];
			return block_node;
		}
		else
		{
			error("Error: Expected END token.");
		}

	}
	else
	{
		error("Error: Expected BEGIN token.");
	}
}

Node_t* expr(vector<Token> &tokens)
{
	Node_t* expr_node = getNode(Expr);

	expr_node->left_child = A(tokens);
	if(token.id == ADDITION_tk)
	{
		expr_node->label = PlusExpr;
		i++;
		token = tokens[i];
		expr_node->right_child = expr(tokens);
		return expr_node;
	}
	else if(token.id == SUBTRACTION_tk)
	{
		expr_node->label = MinusExpr;
		i++;
		token = tokens[i];
		expr_node->right_child = expr(tokens);
		return expr_node;
	}
	else
	{
		return expr_node;
	}
}

Node_t* A(vector<Token> &tokens)
{
	Node_t* A_node = getNode(ALabel);

	A_node->left_child = N(tokens);
	if(token.id == MULTIPLY_tk)
	{
		A_node->label = MultiplicationA;
		i++;
		token = tokens[i];
		A_node->right_child = A(tokens);
		return A_node;
	}
	else
	{
		return A_node;
	}
}

Node_t* N(vector<Token> &tokens)
{
	Node_t* N_node = getNode(NLabel);

	N_node->left_child = M(tokens);
	if(token.id == DIVIDE_tk)
	{
		N_node->label = DivisionN;
		i++;
		token = tokens[i];
		N_node->right_child = N(tokens);
		return N_node;
	}
	else
	{
		return N_node;
	}
}

Node_t* M(vector<Token> &tokens)
{
	Node_t* M_node = getNode(MLabel);

	if(token.id == SUBTRACTION_tk)
	{
		M_node->label = SubtractionM;
		i++;
		token = tokens[i];
		M_node->left_child = M(tokens);
		return M_node;
	}	
	else
	{
		M_node->left_child = R(tokens);
		return M_node;
	}
}

Node_t* R(vector<Token> &tokens)
{
	Node_t* R_node = getNode(RLabel);

	if(token.id == OPEN_BRACKET_tk)
	{
		i++;
		token = tokens[i];
		R_node->left_child = expr(tokens);
		
		if(token.id == CLOSE_BRACKET_tk)
		{
			i++;
			token = tokens[i];
			return R_node;
		}
		else
		{
			cout << token.lineNumber << ": ";
			error("Error: Expected CLOSE BRACKET token.");
		}
	}
	else if(token.id == IDENT_tk)
	{
		R_node->token = token;
		i++;
		token = tokens[i];
		return R_node;
	}
	else if(token.id == NUM_tk)
	{	
		R_node->token = token;
		i++;
		token = tokens[i];
		return R_node;
	}
	else
	{
		cout << token.lineNumber << ": ";
		error("Error: Expected OPEN BRACKET, IDENTIFIER, or NUMBER token");
	}	
}

Node_t* stats(vector<Token> &tokens)
{
	Node_t* stats_node = getNode(Stats);

	stats_node->left_child = stat(tokens);

	if(token.id == COLON_tk)
	{
		i++;
		token = tokens[i];
		stats_node->right_child = mStat(tokens);
		return stats_node;
	}
	else
	{
		error("Error: Expected COLON token.");
	}
}

Node_t* mStat(vector<Token> &tokens)
{
	if(token.id == END_tk)
	{
		return NULL;
	}
	
	Node_t* mStat_node = getNode(MStat);

	mStat_node->left_child = stat(tokens);

        if(token.id == COLON_tk)
        {
                i++;
                token = tokens[i];
                mStat_node->right_child = mStat(tokens);
                return mStat_node;
        }
        else //process empty
        {
		error("Error: Expected COLON token.");		
        }
}

Node_t* stat(vector<Token> &tokens)
{
	Node_t* stat_node = getNode(Stat);

	switch(token.id)
	{
		case READ_tk:
			i++;
			token = tokens[i];
			return in(tokens);
		case OUTPUT_tk:
			i++;
                        token = tokens[i];
                        return out(tokens);
		case BEGIN_tk:
			//i++;
                        //token = tokens[i];
                        return block(tokens);
		case IFF_tk:
			i++;
                        token = tokens[i];
                        return if_tk(tokens);
		case LOOP_tk:
			i++;
                        token = tokens[i];
                        return loop(tokens);
		case IDENT_tk:
			i++;
                        token = tokens[i];
                        return assign(tokens);
		default:
			error("Error: Expected READ, OUTPUT, BLOCK, IFF, LOOP, or IDENTIFIER token.");
			break;
	}
}

Node_t* in(vector<Token> &tokens)
{
	Node_t* in_node = getNode(In);

		if(token.id == OPEN_BRACKET_tk)
		{
			i++;
			token = tokens[i];

			if(token.id == IDENT_tk)
			{
				i++;
				token = tokens[i];

				if(token.id == CLOSE_BRACKET_tk)
				{
					i++;
					token = tokens[i];
					return in_node;
				}
				else
				{
					cout << token.lineNumber << ": ";
					error("Error: Expected CLOSE BRACKET token.");
				}
			}
			else
			{
				error("Error: Expected IDENTIFIER token.");
			}
		}
		else
		{
			cout << token.lineNumber << ": ";
			error("Error: Expected OPEN BRACKET token.");
		}
}

Node_t* out(vector<Token> &tokens)
{
	Node_t* out_node = getNode(Out);

	if(token.id == OPEN_BRACKET_tk)
	{
		i++;
		token = tokens[i];
		out_node->left_child = expr(tokens);	

		if(token.id == CLOSE_BRACKET_tk)
		{
			i++;
			token = tokens[i];
			return out_node;
		}
		else
		{
			cout << token.lineNumber << ": ";
			error("Error: Expected CLOSE BRACKET token.");
		}
	}
	else
	{
		cout << token.lineNumber << ": ";
		error("Error: Expected OPEN BRACKET token.");
	}	
}

Node_t* if_tk(vector<Token> &tokens)
{
	Node_t* iff_node = getNode(If);

	if(token.id == OPEN_BRACKET_tk)
	{
		i++;
		token = tokens[i];
		iff_node->left_child = expr(tokens);
		iff_node->ro_child = RO(tokens);
		iff_node->right_child = expr(tokens);
		
		if(token.id == CLOSE_BRACKET_tk)
		{
			i++;
			token = tokens[i];
			iff_node->stat_child = stat(tokens);
			return iff_node;
		}
		else
		{
			cout << token.lineNumber << ": ";
			error("Error: Expected CLOSE BRACKET token.");
		}
	}
	else
	{
		cout << token.lineNumber << ": ";
		error("Error: Expected OPEN BRACKET token.");
	}
}

Node_t* loop(vector<Token> &tokens)
{
	Node_t* loop_node = getNode(Loop);

	if(token.id == OPEN_BRACKET_tk)
	{
		//expr(tokens);
		i++;
		token = tokens[i];
		loop_node->left_child = expr(tokens);
		loop_node->ro_child = RO(tokens);
		loop_node->right_child = expr(tokens);

		if(token.id == CLOSE_BRACKET_tk)
		{
			i++;
			token = tokens[i];
			loop_node->stat_child = stat(tokens);
			return loop_node;
		}
		else
		{
			cout << token.lineNumber;
			error("Error: Expected CLOSE BRACKET token.");
		}
	}
	else
	{
		cout << token.lineNumber;
		error("Error: Expected OPEN BRACKET token.");
	}
}

Node_t* assign(vector<Token> &tokens)
{
	Node_t* assign_node = getNode(Assign);

	if(token.id == EQUAL_tk)
	{
		i++;
		token = tokens[i];
		assign_node->left_child = expr(tokens);
		return assign_node;
	}
	else 
	{
		error("Error: Expected EQUAL token.");
	}
}

Node_t* RO(vector<Token> &tokens)
{
	Node_t* RO_node = getNode(ROLabel);

	if(token.id == LESS_tk)
	{
		i++;
		token = tokens[i];
		return RO_node;
	}
	else if(token.id == EQUAL_tk)
	{
		i++;
		token = tokens[i];

		if(token.id == LESS_tk)
		{
			i++;
			token = tokens[i];
			return RO_node;
		}
		else if(token.id == GREATER_tk)
		{
			i++;
			token = tokens[i];
			return RO_node;
		}
		else if(token.id == EQUAL_tk)
		{
			i++;
			token = tokens[i];
			return RO_node;
		}

		return RO_node;
	}
	else if(token.id == GREATER_tk)
	{
		i++;
		token = tokens[i];
		return RO_node;
	}
	else
	{
		error("Error: Expected LESS THAN, EQUAL, or GREATER THAN token.");
	}
}

void error(string message)
{
	cout << message << endl;
	exit(1);
}

Node_t* getNode(NodeLabel label)
{
	Node_t* temp = new Node_t;

	temp->label = label;
	temp->token.instance = "";
	temp->token2.instance = "";
	temp->left_child = NULL;
	temp->right_child = NULL;
	temp->ro_child = NULL;
	temp->stat_child = NULL;

	return temp;
}

