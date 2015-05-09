#include "smiles.h"
#include "fragment.h"
#include <iostream>
#include <strstream>
#include <mysql/plugin.h>
#include <string>
#include <string.h>

Fragmentor* pf_fragmentor;

void set_status(const char* status) {
    std::strcpy(current_status, status);
}

bool str_eql(const char* str1, const char* str2) {
	return strncmp(str1, str2, sizeof(str2) - 1) == 0;
}

int mysql_smiles_fragmentor_parse(MYSQL_FTPARSER_PARAM *param) {
	param->flags = MYSQL_FTFLAGS_NEED_COPY; // Since we just using 1 buffer to add indexes, so mysql need to copy the text.
    set_status("Tokenizing the smiles");
	if(param->mode == MYSQL_FTPARSER_SIMPLE_MODE) {
		std::string s = std::string(param->doc, param->length);
		std::cerr << "Tokenizing [" << s << "]" << std::endl;
		Fset* pf_set = pf_fragmentor->fragment(s.c_str());
		if(pf_set) {
			SetItr itr;
			for(itr=pf_set->begin(); itr!=pf_set->end();++itr) {
				std::vector<int> v = (std::vector<int>) *itr;
				ostrstream out;

				std::vector<int>::iterator i;
				for(i=v.begin(); i!=v.end(); ++i) {
					out << *i;
				}
				std::string s = out.str();
//				std::cerr << "Get token " << s << std::endl;
				int weight = s[0]? 1 : 0;
				MYSQL_FTPARSER_BOOLEAN_INFO bool_info = {
					FT_TOKEN_WORD, // Token type
					0, // Yes No - Use no by default
					weight, // Weight Adjust - No adjust by default
					0, // Weight Adjust Sign - No sign
					0, // Trunk
		//          pos, // Position
					' ', // Prev
					0 // Quote
				};
				param->mysql_add_word(param, strdup((char *)s.c_str()), s.length(), &bool_info);
			}
		}
	}
	
	return 0;
}

int mysql_smiles_fragmentor_init(MYSQL_FTPARSER_PARAM *param __attribute__((unused))) {
    set_status("Initializing smiles fragmentor...");
	pf_fragmentor = new Fragmentor();
	return 0;
}

int mysql_smiles_fragmentor_deinit(MYSQL_FTPARSER_PARAM *param __attribute__((unused))) {
    set_status("Deinitializing smiles fragmentor...");
	delete pf_fragmentor;
	pf_fragmentor = NULL;
	return 0;
}
