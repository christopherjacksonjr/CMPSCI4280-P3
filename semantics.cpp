#include"semantics.h"

string determineNodeLabel(NodeLabel label);
vector<Token> variables;

void semantics(struct Node_t* root)
{
	string label;
	Token token;
	//token = root->token;	

	if(root != NULL)
	{
		label = determineNodeLabel(root->label);
		token = root->token;

		if(label == "vars")
		{
			//Token token;
			//token = root->token;
			cout << "Match: ";
			if(std::find(variables.begin(), variables.end(), token) != variables.end())
			{
				cout << "Error - variable already defined." << endl;
                                exit(1);
			}
			else
			{
				variables.push_back(token);
                                cout << "Added" << endl;
			}
		}
		else if(label == "R")
		{
			if(std::find(variables.begin(), variables.end(), token) != variables.end())
                        {
                                variables.push_back(token);
                                cout << "Verified" << endl;
                        }
                        else
                        {
                                cout << "Error - variable not defined." << endl;
                                exit(1);
                        }
		}
		else if(label == "in")
		{
			if(std::find(variables.begin(), variables.end(), token) != variables.end())
                        {
                                variables.push_back(token);
                                cout << "Verified" << endl;
                        }
                        else
                        {
                                cout << "Error - variable not defined." << endl;
                                exit(1);
                        }
		}
		else
		{
			cout << "No match: ";
		}

		cout << label << " ";
		cout << root->token.instance << " ";
		cout << root->token2.instance << endl;

		semantics(root->left_child);
		semantics(root->right_child);
	}
}

string determineNodeLabel(NodeLabel label)
{
        switch(label)
        {
                case Program:
                        return "program";
                case Block:
                        return "block";
                case Vars:
                        return "vars";
                case Expr:
                        return "expr";
                case PlusExpr:
                        return "+expr";
                case MinusExpr:
                        return "-expr";
                case ALabel:
                        return "A";
                case MultiplicationA:
                        return "*A";
                case NLabel:
                        return "N";
                case DivisionN:
                        return "/N";
                case MLabel:
                        return "M";
                case SubtractionM:
                        return "-M";
                case RLabel:
                        return "R";
                case Stats:
                        return "stats";
                case MStat:
                        return "mStat";
                case Stat:
                        return "stat";
                case In:
                        return "in";
                case Out:
                        return "out";
                case If:
                        return "if";
                case Loop:
                        return "loop";
                case Assign:
                        return "assign";
                case ROLabel:
                        return "RO";
                default:
                        return "not-defined";

        }
}

