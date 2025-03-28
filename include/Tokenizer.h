#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<StringDict.h>

class Tokenizer{
	private:
		Node* dictionary = nullptr;
		Element* DictFind(std::string str);

	public:
		std::vector<Element> Tokenize(std::string);
		std::vector<std::vector<Element>> LineTokenize(std::string);
		void SetDict(Node* _dictionary);


};

#endif
