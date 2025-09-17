// Simple integer calculator with support for the following operations:
// - Addition
// - Subtraction
// - Multiplication
// - Division
// - Binary left shift
// - Binary right shift
// - Binary AND
// - Binary OR
// - Binary XOR
//
// Compile with:
// gcc -o calc -ggdb3 -O0 calc.c
//
// Options used when compiling:
//    -o calc  - Name the executable "calc"
//    -ggdb3   - Build in extra data to help debugging with GDB (with level 3 of information included)
//    -O0      - Do minimal optimizations of the code; good for debugging
//
// Run with command line arguments as follows:
//      ./calc '<n1> <operation> <n2>'
// For example:
//      ./calc '3 + 3'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define supported operators
#define OPERATOR_UNKNOWN -1
#define OPERATOR_ADD 0
#define OPERATOR_SUBTRACT 1
#define OPERATOR_MULTIPLY 2
#define OPERATOR_DIVIDE 3
#define OPERATOR_SLL 4 // Shift Left Logical
#define OPERATOR_SRL 5 // Shift Right Logical
#define OPERATOR_AND 6
#define OPERATOR_OR 7
#define OPERATOR_XOR 8

// This struct represents one mathematical operation between two integers.
struct operation
{
	int n1, n2;
	short operator;
};


// Decode an input from the command line into an "operation" struct.
// The input string assumed to be in the following form:
// "5 + 10"
struct operation decode_input(char *input)
{
	struct operation result;

	// Get first number
	char *n1 = strtok(input, " ");
	if (n1 == NULL)
	{
		printf("Invalid input found.\n");
		result.operator = OPERATOR_UNKNOWN;
		return result;
	}
	result.n1 = atoi(n1);

	// Get operator
	char *operator = strtok(NULL, " ");
	if (operator == NULL)
	{
		printf("Invalid input found.\n");
		result.operator = OPERATOR_UNKNOWN;
		return result;
	}

	// Decode operator
	if (strcmp(operator, "+") == 0)
	{
		result.operator = OPERATOR_ADD;
	}
	else if (strcmp(operator, "-") == 0)
	{
		result.operator = OPERATOR_SUBTRACT;
	}
	else if (strcmp(operator, "*") == 0 || strcmp(operator, "x") == 0)
	{
		result.operator = OPERATOR_MULTIPLY;
	}
	else if (strcmp(operator, "/") == 0)
	{
		result.operator = OPERATOR_DIVIDE;
	}
	else if (strcmp(operator, "<<") == 0)
	{
		result.operator = OPERATOR_SLL;
	}
	else if (strcmp(operator, ">>") == 0)
	{
		result.operator = OPERATOR_SRL;
	}
	else if (strcmp(operator, "&") == 0)
	{
		result.operator = OPERATOR_AND;
	}
	else if (strcmp(operator, "|") == 0)
	{
		result.operator = OPERATOR_OR;
	}
	else if (strcmp(operator, "^") == 0)
	{
		result.operator = OPERATOR_XOR;
	}
	else
	{
		result.operator = OPERATOR_UNKNOWN;
	}

	// Get second number
	char *n2 = strtok(NULL, " ");
	if (n2 == NULL)
	{
		printf("Invalid input found.\n");
		result.operator = OPERATOR_UNKNOWN;
		return result;
	}
	result.n2 = atoi(n2);

	return result;
}


// Returns the result from the passed operation.
int perform_operation(struct operation op)
{
	int result;

	switch (op.operator)
	{
		case OPERATOR_ADD:
			result = op.n1 + op.n2;
			break;

		case OPERATOR_SUBTRACT:
			result = op.n1 - op.n2;
			break;

		case OPERATOR_MULTIPLY:
			result = op.n1 * op.n2;
			break;

		case OPERATOR_DIVIDE:
			result = op.n1 / op.n2;
			break;

		case OPERATOR_SLL:
			result = op.n1 << op.n2;
			break;

		case OPERATOR_SRL:
			result = op.n1 >> op.n2;
			break;

		case OPERATOR_AND:
			result = op.n1 & op.n2;
			break;

		case OPERATOR_OR:
			result = op.n1 | op.n2;
			break;

		case OPERATOR_XOR:
			result = op.n1 ^ op.n2;
			break;

		default:
			printf("Invalid operator found. Defaulting solution to 0.\n");
	}

	return result;
}


int main(int argc, char *argv[])
{
	int result;
	struct operation op;

	// Stop early if the wrong number of command line arguments are provided.
	if (argc != 2)
	{
		printf("Usage: %s '<n1> <operation> <n2>'\n", argv[0]);
		return 1;
	}

	op = decode_input(argv[1]);

	// Stop early if an invalid operator was given.
	if (op.operator == OPERATOR_UNKNOWN)
	{
		printf("Unknown operator.\n");
		return 2;
	}

	result = perform_operation(op);
	printf("Result: %d\n", result);

	return 0;
}


