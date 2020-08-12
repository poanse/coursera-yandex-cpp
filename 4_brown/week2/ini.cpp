#include "ini.h"

namespace Ini {

	Section& Document::AddSection(string name) {
		return sections[name];
	}

	const Section& Document::GetSection(const string& name) const {
		return sections.at(name);
	}

	size_t Document::SectionCount() const {
		return sections.size();
	}


	Document Load(istream& input) {
		Document doc;
		string line;
		Section *current_section;
		while (getline(input, line)) {
			// 3 possible situations:
				// 1) "[smth]" - start of new section
				// 2) "key=value" - update current section
				// 3) "" - do nothin
			if ("" == line) {
				continue;
			} else if ('[' == line[0]) {
				string section_name = line.substr(1, line.size()-2);
				current_section = &(doc.AddSection(move(section_name)));
			} else if (string::npos != line.find('=')){
				if (!current_section) {
					throw "No active section";
				}
				size_t border = line.find('=');
				string key = line.substr(0, border);
				string value = line.substr(border + 1);
				(*current_section)[move(key)] = move(value);
			} else {
				throw "Incorrect file format";
			}
		}
		return doc;
	}
}
