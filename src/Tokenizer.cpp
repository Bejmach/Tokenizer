#include "StringDict.h"
#include <Tokenizer.h>
#include <algorithm>
#include <ostream>
#include <sstream>

Element* Tokenizer::DictFind(std::string str, Dict* dictionary){
	return SD::Find(dictionary, str);
}

std::vector<Element> Tokenizer::Tokenize(std::string data, Dict* dictionary){
	std::vector<Element> tokens;

	std::stringstream stream(data);

	std::string iterated = "";
	char forwardBuffer = 0;
	char ch;
	char curChar;

	while(stream.get(ch)){
		curChar = forwardBuffer;
		forwardBuffer = ch;
		if(curChar == 0){
			continue;
		}
		std::string charStr(1, curChar);
		if(SD::Find(dictionary, iterated+charStr+forwardBuffer) != nullptr){
			if(stream.get(ch)){
				tokens.push_back(*SD::Find(dictionary, iterated+charStr+forwardBuffer));
				iterated.clear();
				curChar = forwardBuffer;
				forwardBuffer = ch;
			}
			else{
				tokens.push_back(*SD::Find(dictionary, iterated+forwardBuffer));
				return tokens;
			}
		}
		else if(SD::Find(dictionary, iterated+charStr)!=nullptr){
			tokens.push_back(*SD::Find(dictionary, iterated+charStr));
			iterated.clear();
		}
		else if(SD::Find(dictionary, charStr+forwardBuffer)!=nullptr){
			if(iterated!=""){
				tokens.push_back({iterated, "local"});
				iterated.clear();
			}
			if(stream.get(ch)){
				tokens.push_back(*SD::Find(dictionary, charStr+forwardBuffer));
				curChar = forwardBuffer;
				forwardBuffer = ch;

			}
			else{
				tokens.push_back(*SD::Find(dictionary, charStr+forwardBuffer));
				return tokens;
			}
		}
		else if(SD::Find(dictionary, charStr)!=nullptr){
			if(iterated!=""){
				tokens.push_back({iterated, "local"});
				iterated.clear();
			}
			tokens.push_back(*SD::Find(dictionary, charStr));		
		}
		else if(charStr == " " || charStr == "\n" || charStr == "\t"){
			if(iterated!=""){
				tokens.push_back({iterated, "local"});
				iterated.clear();
			}
		}
		else{
			iterated+=curChar;
		}
	}

	return tokens;
}
std::vector<std::vector<Element>> Tokenizer::LineTokenize(std::string data, Dict* dictionary){
	std::vector<std::vector<Element>> tokens;

	std::stringstream stream(data);

	std::string iterated = "";
	char ch;

	tokens.push_back({});
	int line = 0;

	while(stream.get(ch)){
		std::string str(1, ch);
		if(str == "\n"){
			if(iterated!=""){
				tokens[line].push_back({iterated, "local"});
				iterated.clear();
			}
			tokens[line].push_back({str, "nl"});
			tokens.push_back({});
			line+=1;
			continue;
		}
		Element* dictElement = DictFind(str, dictionary);
		if(dictElement!=nullptr){
			if(iterated!=""){
				tokens[line].push_back({iterated, "local"});
				iterated.clear();
			}
			tokens[line].push_back(*dictElement);
		}
		else if(str == " "){
			if(iterated!=""){
				tokens[line].push_back({iterated, "local"});
				iterated.clear();
			}
		}
		else{
			iterated+=ch;
		}
	}
	if(iterated!=""){
		tokens[line].push_back({iterated, "local"});
	}
	tokens[line].push_back({"\n", "nl"});

	return tokens;
}
