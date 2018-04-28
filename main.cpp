#include <csignal>
#include <iostream>
#include "TNController.hpp"

#define TN_MAIN "MAIN"

using namespace tn;

void sigint_handler(int sig)
{
	log_inf(TN_MAIN, "Cleaning resources");
	delete TNController::getInstance();
	log_inf(TN_MAIN, "Exiting application");
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sigint_handler);
	TNController *controller = TNController::getInstance();
	return 1;
}