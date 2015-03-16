#include "ofxArgs.h"

ofxArgs::ofxArgs(int argc, char* argv[]){
	this->argc = argc;

	string cVal, nextVal;
	for(int i=0; i < argc; i++){
		cVal = argv[i];
		nextVal = (i < argc-1)?argv[i+1]:"";
		
		int pos = cVal.find('=');
		if(pos != string::npos){
			string key = cVal.substr(0, pos);
			string value = cVal.substr(pos+1);
			this->opts[key] = value;
			this->args.push_back(key);
			this->args.push_back(value);
			this->argc++;
		}
		else{
			this->args.push_back(cVal);
			if(nextVal != "" && cVal.substr(0, 1) == "-" && nextVal.substr(0, 1) != "-" && nextVal.find('=') == string::npos){
				this->opts[cVal] = nextVal;
				this->args.push_back(nextVal);
				i++;
			}
		}
	}
}

int ofxArgs::getCount(){
	return this->argc;
}

bool ofxArgs::contains(string key){
	for(int i = 0; i < this->argc; i++){
		if(this->args[i] == key){
			return true;
		}
	}
	return false;
}

float ofxArgs::getFloat(string key, float def){
	map<string,string>::iterator it;
	it = this->opts.find(key);
	if(it != this->opts.end()){
		return strToFloat(it->second);
	}
	return def;
}

int ofxArgs::getInt(string key, int def){
	map<string,string>::iterator it;
	it = this->opts.find(key);
	if(it != this->opts.end()){
		return strToInt(it->second);
	}
	return def;
}

string ofxArgs::getString(string key, string def){
	map<string,string>::iterator it;
	it = this->opts.find(key);
	if(it != this->opts.end()){
		return it->second;
	}
	return def;
}

bool ofxArgs::getBool(string key, bool def){
	map<string,string>::iterator it;
	it = this->opts.find(key);
	if(it != this->opts.end()){
		string s = it->second;
		return s == "true" || s == "TRUE" || strToInt(s) > 0;
	}
	return def;
}

float ofxArgs::getFloat(int index, float def){
	if(index < this->argc){
		return strToFloat(this->args[index]);
	}
	return def;
}

int ofxArgs::getInt(int index, int def){
	if(index < this->argc){
		return strToInt(this->args[index]);
	}
	return def;
}

string ofxArgs::getString(int index, string def){
	if(index < this->argc){
		return this->args[index];
	}
	return def;
}

bool ofxArgs::getBool(int index, bool def){
	if(index < this->argc){
		string s = this->args[index];
		return s == "true" || s == "TRUE" || strToInt(s) > 0;
	}
	return def;
}

void ofxArgs::printArgs(){
	cout << "--- arguments --------" << endl;
	for(int i=0; i < this->argc; i++)
		cout << i << " => " << this->args[i] << endl;
}

void ofxArgs::printOpts(){
	map<string,string>::iterator it;
	cout << "--- options ----------" << endl;
	for ( it=opts.begin() ; it != opts.end(); it++ )
		cout << (*it).first << " => " << (*it).second << endl;
}

int ofxArgs::strToInt(string value){
	int result;
	sscanf(value.c_str(), "%d", &result);
	return result;
}

float ofxArgs::strToFloat(string value){
	float result;
	sscanf(value.c_str(), "%f", &result);
	return result;
}
