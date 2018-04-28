#ifndef _EXCEL_H
#define _EXCEL_H "Excel"

#include <algorithm>
#include <iostream>
#include <vector>
#include <xlsxio_read.h>
#include <xlsxio_write.h>

class Excel
{
  private:
    std::string filename;
    xlsxioreader reader = NULL;
    xlsxiowriter writer = NULL;
    xlsxioreadersheet _selectedSheet = NULL;
    std::string selectedSheet;
    std::vector<std::string> *sheets;
    bool isFileValid()
    {
        if (filename == "")
        {
            log_err(_EXCEL_H, "A vaild file must be selected before doing a operation");
            return false;
        }
        return true;
    }

    bool isSheetSelected()
    {
        _selectedSheet = xlsxioread_sheet_open(reader, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
        if (_selectedSheet == NULL)
        {
            log_war(_EXCEL_H, "A sheet must be selected before operation");
            return false;
        }
        return true;
    }

  public:
    Excel()
    {
    }

    //DONE
    std::vector<std::string> *
    getSheets()
    {
        if (sheets)
            return sheets;
        if (!isFileValid())
            return new std::vector<std::string>();
        sheets = new std::vector<std::string>();
        xlsxioreadersheetlist sheetlist;
        if ((sheetlist = xlsxioread_sheetlist_open(reader)) == NULL)
        {
            log_err(_EXCEL_H, "No sheets are found in the selected file");
            return new std::vector<std::string>();
        }
        const XLSXIOCHAR *sheetname;
        while ((sheetname = xlsxioread_sheetlist_next(sheetlist)) != NULL)
        {
            log_inf(_EXCEL_H, "sheet: %s", sheetname);
            sheets->push_back(sheetname);
            //XML_Char_printf(X(" - %s\n"), sheetname);
        }
        log_inf(_EXCEL_H, "Closing sheetlist");
        xlsxioread_sheetlist_close(sheetlist);
	return sheets;
    }

    //TODO
    void selectSheet(std::string sheetName)
    {
        if (!isFileValid())
            return;
        if (std::find(getSheets()->begin(), getSheets()->end(), sheetName) == getSheets()->end())
        {
            log_err(_EXCEL_H, "Cannot open the selected sheet");
            return;
        }
        selectedSheet = sheetName;

        //read values from first sheet
        XLSXIOCHAR *value;
        printf("Contents of first sheet:\n");
        xlsxioreadersheet _selectedSheet = xlsxioread_sheet_open(reader, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
        while (xlsxioread_sheet_next_row(_selectedSheet))
        {
            while ((value = xlsxioread_sheet_next_cell(_selectedSheet)) != NULL)
            {
                log_inf(_EXCEL_H, "%s", value);
                free(value);
            }
        }
        xlsxioread_sheet_close(_selectedSheet);
    }

    //DONE
    void openFile(std::string filename)
    {
        if ((reader = xlsxioread_open(filename.c_str())) == NULL)
        {
            log_err(_EXCEL_H, "Error opening .xlsx file");
            this->filename = "";
            return;
        }
        this->filename = filename;
    }

    std::vector<std::string> *getColumns()
    {
        std::vector<std::string> *columns = new std::vector<std::string>();
        //read values from first sheet
        XLSXIOCHAR *value = NULL;
        _selectedSheet = xlsxioread_sheet_open(reader, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
        if (xlsxioread_sheet_next_row(_selectedSheet))
        {
            while ((value = xlsxioread_sheet_next_cell(_selectedSheet)) != NULL)
            {
                log_inf(_EXCEL_H, "Column: %s", value);
                columns->push_back(value);
            }
        }
        xlsxioread_sheet_close(_selectedSheet);
        return columns;
    }

    //TODO
    std::string getCell(int row, int column)
    {
        if (!isFileValid())
            return std::string("");
	return std::string(""); //send correct value here
    }

    //TODO
    void setCell(int row, int column, std::string val)
    {
        if (!isFileValid())
            return;
    }

    ~Excel()
    {
        log_inf(_EXCEL_H, "Cleaning up");
        //clean up
        if (reader != NULL)
            xlsxioread_close(reader);
        if (writer != NULL)
            xlsxiowrite_close(writer);
    }
};

#endif
