#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<StringDict.h>
#include<NumberOperations.h>

class Tokenizer{
	private:
		static Element* DictFind(std::string str, Dict* dictionary);
		static std::vector<size_t> GetPositions(std::string str, std::vector<Element>& dictionary);

	public:
		static std::vector<Element> CharTokenize(std::string str, Dict* dictionary);
		static std::vector<std::vector<Element>> CharLineTokenize(std::string str, Dict* dictionary);
		static std::vector<Element> WordTokenize(std::string str, std::vector<Element>& dictionary, Dict* additionalDict = nullptr);

};

#endif
