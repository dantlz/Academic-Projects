#ifndef SEARCHUI_H
#define SEARCHUI_H
#include <string>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QListWidget>
#include <QWidget>
#include <QGroupBox>
#include "searcheng.h"
#include "webpage.h"
#include "mytextedit.h"


class SearchUI : public QWidget{
	Q_OBJECT
public:
	SearchUI();
	~SearchUI();
	void set_searchEngine(SearchEng& search_eng);
public slots:
	void quitButton_clicked();
	void returnKey_hit();
	void searchButton_clicked();
	void mainList_sortType_clicked();
	void mainList_item_clicked(int itemRow);
	void closeButton_clicked();
	void inList_sortType_clicked();
	void inList_item_clicked(int itemRow);
	void outList_sortType_clicked();
	void outList_item_clicked(int itemRow);
private:
	void populate_mainList();
	void populate_nameDisplay(WebPage* wp);
	void populate_contentDisplay(WebPage* wp);
	void populate_inList(WebPage* wp);
	void populate_outList(WebPage* wp);
	void search_single(std::string input);
	void search_and(std::vector<std::string> input_words);
	void search_or(std::vector<std::string> input_words);
	void sort_name(std::vector<WebPage*>& v);
	void sort_inLink(std::vector<WebPage*>& v);
	void sort_outLink(std::vector<WebPage*>& v);
	std::string lowerCase(std::string s);

	QGridLayout* main_layout;
		QPushButton* quitButton;
		MyTextEdit* searchInput;
		QPushButton* searchButton;
		QRadioButton* radio_single;
		QRadioButton* radio_and;
		QRadioButton* radio_or;
		QGroupBox* searchType_group;
		QHBoxLayout* searchType_layout;
		QRadioButton* mainList_nameSort_button;
		QRadioButton* mainList_inLink_button;
		QRadioButton* mainList_outLink_button;
		QGroupBox* mainListSort_group;
		QHBoxLayout* mainListSort_layout;
		QButtonGroup* mainList_sortType;
		QListWidget* mainList;
	QWidget* details_window;
	QGridLayout* details_layout;
		QLabel* currentFile_name;
		QLabel* nameDisplay;
		QPushButton* closeButton;
		QTextEdit* webContent;
		QButtonGroup* inList_sortType;
		QGroupBox* inListSort_group;
		QHBoxLayout* inListSort_layout;
		QRadioButton* inList_nameSort_button;
		QRadioButton* inList_inLink_button;
		QRadioButton* inList_outLink_button;
		QListWidget* inList;
		QButtonGroup* outList_sortType;
		QGroupBox* outListSort_group;
		QHBoxLayout* outListSort_layout;
		QRadioButton* outList_nameSort_button;
		QRadioButton* outList_inLink_button;
		QRadioButton* outList_outLink_button;
		QListWidget* outList;

	SearchEng sn;
	MySetWebPage search_result;
	std::vector<WebPage*> mainList_data;
	std::vector<WebPage*> inList_data;
	std::vector<WebPage*> outList_data;
};
#endif