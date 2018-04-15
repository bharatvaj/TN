#include "TN.hpp"

TN *TN::instance = nullptr;

void TN::browse(int type)
{
	Fl_Native_File_Chooser fnfc;
	fnfc.title("Pick a file");
	fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fnfc.directory("/"); // default directory to use
						 // Show native chooser

	switch (type)
	{
	case 0:
		fnfc.filter("Image Files \t*.{tiff,png,jpeg}");
		break;
	case 1:
		fnfc.filter("Excel Files \t*.{xlsx, xls}");
		break;
	}
	switch (fnfc.show())
	{
	case -1:
		fl_choice(fnfc.errmsg(), "OK", nullptr, nullptr, nullptr);
		break; // ERROR
	case 1:
		break; // CANCEL
	default:
		std::string s(fnfc.filename());
		if (type == 0)
		{
			imagePath = s;
			edit1->value(s.c_str());
		}
		else
		{
			sheetPath = s;
			edit2->value(s.c_str());
		}
		break; // FILE CHOSEN
	}
}

void TN::onCreate()
{
	super::onCreate();

	edit1 = new Fl_Input(60, 20, 250, 30, "Image");
	editBtn1 = new Fl_Button(320, 20, 60, 30, "Browse");
	editBtn1->callback(&TN::buttonCallback, new int(1));

	edit2 = new Fl_Input(60, 80, 250, 30, "XLSX");
	editBtn2 = new Fl_Button(320, 80, 60, 30, "Browse");
	editBtn2->callback(&TN::buttonCallback, new int(2));

	Fl_Button *btn = new Fl_Button(320, 140, 60, 30, "Convert");
	btn->callback(&TN::buttonCallback, new int(0));

	getWindow()->add(edit1);
	getWindow()->add(editBtn1);
	getWindow()->add(edit2);
	getWindow()->add(editBtn2);
	getWindow()->add(btn);
}

void TN::onDestroy()
{
}

void TN::convert()
{
	Sheet *sheet = new Sheet();
	log_inf(TN_MAIN, "Converting Image");
}

void TN::buttonCallback(Fl_Widget *o, void *type)
{
	TN *tn = TN::getInstance();
	switch (*(int *)type)
	{
	case 0:
		tn->convert();
		break;
	case 1:
		tn->browse(0);
		break;
	case 2:
		tn->browse(1);
		break;
	}
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
