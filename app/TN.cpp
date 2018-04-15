#include "TN.hpp"

TN *TN::instance = nullptr;

void TN::onCreate()
{
	super::onCreate();
	log_inf(TN_MAIN, "Adding Button");
	getWindow()->begin();
	Fl_Button(10, 20, 45, 30, "Convert");
	getWindow()->end();
}

void TN::onDestroy()
{
}

void TN::convert()
{
	log_inf(TN_MAIN, "Converting Image");
}

void TN::but_cb(Fl_Widget *o, void *)
{
	log_inf(UI_MAIN, "Button Pressed");
	getInstance()->convert();
}
TN::TN()
{
}

TN *TN::getInstance()
{
	if (TN::instance == nullptr)
	{
		log_inf(TN_MAIN, "Initialzing TN");
		TN::instance = new TN();
	}
	return TN::instance;
}

TN::~TN()
{
	//TODO cleanup memory before exit
}
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
	TN *tn = TN::getInstance();
	return tn->run();
}
