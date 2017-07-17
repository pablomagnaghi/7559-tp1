/*
 * OptionsParser.cpp
 *
 *  Created on: 11/05/2013
 *      Author: gonzalo
 */

#include "OptionsParser.h"

OptionsParser::OptionsParser(char* options[], int tam) {
	for (int i = 1; i < tam; i++){
		string key = (string) options[i];
		string val;
		if (isOption(key)){
			this->options[key] = DEFAULT_VAL;
			if ((i+1) < tam){
				val = (string) options[i+1];
				if (!isOption(val)){
					this->options[key] = val;
					i++;
				}
			}
		}
	}
}

/* Get value for options in format -o or --option */
string OptionsParser::getOptionValue(string opt, string longOpt){
	map<string, string>::iterator it;
	if (!isOption(opt)){
		opt = "-" + opt;
	}
	it = (opt.empty())? this->options.end(): this->options.find(opt);
	if (it  != this->options.end()){
			return (*it).second;
	}

	if (!isOption(longOpt)){
		longOpt = "--" + longOpt;
	}
	it = (longOpt.empty())? this->options.end(): this->options.find(longOpt);
	if (it  != this->options.end()){
			return (*it).second;
	}
	return "";
}

void OptionsParser::showOptions(){
	map<string, string>::iterator it;
	if (!options.empty()){
		for(it = options.begin(); it != options.end(); it++) {
			cout << (*it).first << " contains " << (*it).second << endl;
		}
	} else {
		cout << "There's no data to display" << endl;
	}

}

bool OptionsParser::optionExists(string opt, string longOpt){
	return (this->getOptionValue(opt, longOpt) != "");
}


int OptionsParser::optionsCount(){
	return this->options.size();
}

bool OptionsParser::isOption(string v){
	int posguion = v.find('-');
	int posdobleguion = v.find("--");
	return (posguion == 0) || (posdobleguion == 0);
}

OptionsParser::~OptionsParser() {
}
