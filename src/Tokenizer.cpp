#include "StringDict.h"
#include <Tokenizer.h>
#include <sstream>

Element* Tokenizer::DictFind(std::string str, Dict* dictionary){
	return SD::Find(dictionary, str);
}
std::vector<size_t> Tokenizer::GetPositions(std::string str, std::vector<Element>& dictionary){
	std::vector<size_t> positions;
	positions.push_back(0);

	//Get dictionary positions
	for(int i=0; i<dictionary.size()-1; i++){
		size_t pos = str.find(dictionary[i].key);
		size_t wordSize = dictionary[i].key.size();
		while(pos!=std::string::npos){
			if(pos==0){
				positions.push_back(pos+wordSize);
			}
			else{
				positions.resize(positions.size()+2);
				positions[positions.size()-2] = pos;
				positions[positions.size()-1] = pos+wordSize;
			}
			pos = str.find(dictionary[i].key, pos+1);
		}
	}

	//find spaces
	size_t pos = str.find(" ");
	while(pos!=std::string::npos){
		positions.resize(positions.size()+2);
		positions[positions.size()-2] = pos;
		positions[positions.size()-1] = pos+1;
		pos = str.find(" ", pos+1);
	}
	//find newLines
	pos = str.find("\n");
	while(pos!=std::string::npos){
		positions.resize(positions.size()+2);
		positions[positions.size()-2] = pos;
		positions[positions.size()-1] = pos+1;
		pos = str.find("\n", pos+1);
	}

	NO::QuickSort(positions);

	return positions;
}

std::vector<Element> Tokenizer::CharTokenize(std::string data, Dict* dictionary){
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
std::vector<std::vector<Element>> Tokenizer::CharLineTokenize(std::string data, Dict* dictionary){
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

std::vector<Element> Tokenizer::WordTokenize(std::string str, std::vector<Element>& dictionary, Dict* additionalDict){
	std::vector<Element> returner;
	std::vector<size_t> positions = GetPositions(str, dictionary);
	
	for(int i=1; i<positions.size(); i++){
		if(positions[i-1] == positions[i]){
			continue;
		}

		std::string token = str.substr(positions[i-1], positions[i]-positions[i-1]);
		if(token!=" "){
			
			Element pushedElement;
			if(additionalDict!=nullptr){
				Element* foundElement = SD::Find(additionalDict, token);
				pushedElement = (foundElement!=nullptr)?*foundElement:Element({"",""});
			}
			else{
				pushedElement = SD::Find(dictionary, token);
			}
			if(pushedElement.key == ""){
				pushedElement = {token, "local"};
			}
			returner.push_back(pushedElement);
		}
	}
	return returner;
}
