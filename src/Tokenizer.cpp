#include "StringDict.h"
#include <Tokenizer.h>
#include <sstream>

Element* Tokenizer::DictFind(std::string str, Dict* dictionary){
	return SD::Find(dictionary, str);
}

std::vector<Element> Tokenizer::Tokenize(std::string data, Dict* dictionary){
	std::vector<Element> tokens;

	std::stringstream stream(data);

	std::string iterated = "";
	char ch;

	while(stream.get(ch)){
		std::string str(1, ch);
		if(str == "\n"){
			if(iterated!=""){
				tokens.push_back({iterated, "local"});
				iterated.clear();
			}
			tokens.push_back({str, "nl"});
			continue;
		}
		Element* dictElement = DictFind(str, dictionary);
		if(dictElement!=nullptr){
			if(iterated!=""){
				tokens.push_back({iterated, "local"});
				iterated.clear();
			}
			tokens.push_back(*dictElement);
		}
		else if(str == " "){
			if(iterated != ""){
				tokens.push_back({iterated, "local"});
				iterated.clear();
			}
		}
		else{
			iterated+=ch;
		}
	}
	if(iterated!=""){
		tokens.push_back({iterated, "local"});
	}
	tokens.push_back({"\n", "nl"});

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
