/*
 * OptionsParser.h
 *
 *  Created on: 11/05/2013
 *      Author: gonzalo
 */

#ifndef OPTIONSPARSER_H_
#define OPTIONSPARSER_H_

#define DEFAULT_VAL "&%&%&"

#include <iostream>
#include<sstream>
#include <string>
#include <map>

using namespace std;
class OptionsParser {
public:
	OptionsParser(char* options[], int tam);
	string getOptionValue(string opt, string longOpt = "");
	bool optionExists(string opt, string longOpt = "");
	void showOptions();
	int optionsCount();
	virtual ~OptionsParser();

private:
	map<string, string> options;
	int counter;
	bool isOption(string v);
};

#endif /* OPTIONSPARSER_H_ */
