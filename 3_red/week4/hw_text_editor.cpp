#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
private:
	list<char> text;
	list<char> buffer;
	list<char>::iterator position;
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() 
		: text()
		, buffer()
	{
		position = text.begin();
	}
  void Left() {
		if (position != text.begin()) {
			position--;
		}
	}
  void Right() {
		if (position != text.end()) {
			position++;
		}
	}
  void Insert(char token) {
		text.insert(position, token);
	}
  void Cut(size_t tokens = 1) {
		bool start;
		list<char>::iterator tmp;
		if (position == text.begin()) {
			start = true;
		} else {
			tmp = prev(position);
			start = false;
		}
		buffer = list<char>();
		auto end_pos = position;
		for (auto i = 0; (i < tokens) && (end_pos != text.end()); i++) {
			end_pos++;
		}
		buffer.splice(buffer.begin(), text, position, end_pos);
		if (start) {
			position = text.begin();
		} else {
			position = next(tmp);
		}
	}
  void Copy(size_t tokens = 1) {
		buffer = list<char>(position, next(position, tokens));
	}
  void Paste() {
		text.insert(position, buffer.begin(), buffer.end());
	}
  string GetText() const {
		return {text.begin(), text.end()};
	}
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
	//Editor editor;
  //TypeText(editor, "example");
	//editor.Left();
	//cout << editor.GetText() << endl;
	//editor.Insert('!');
	//cout << editor.GetText() << endl;

  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
