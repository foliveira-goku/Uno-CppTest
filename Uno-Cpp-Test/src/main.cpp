#include "Table.h"
#include "InputReader.h"

const int GetActionInputsOptions(std::string& ActionsDisplay)
{
	ActionsDisplay = "[1] Discard a card  [2] Buy a card  [3] Say Uno! \n";

	return 3;
}

int main()
{
	std::srand(std::time(0));
}