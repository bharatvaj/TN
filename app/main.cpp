#include <iostream>
#include "TN.hpp"

#define TN_MAIN "MAIN"

void sigint_handler(int sig)
{
	log_inf(TN_MAIN, "Cleaning resources");
	delete TN::getInstance();
	log_inf(TN_MAIN, "Exiting application");
	exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{
	signal(SIGINT, sigint_handler);
	ActivityInvoker<TN> ai;
	return ai.startActivity();
}