#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<StringDict.h>
#include<NumberOperations.h>

class Tokenizer{
	private:
		static Element* DictFind(std::string str, Dict* dictionary);

	public:
		static std::vector<Element> Tokenize(std::string str, Dict* dictionary);
		static std::vector<std::vector<Element>> LineTokenize(std::string str, Dict* dictionary);

};

#endif
