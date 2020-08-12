#include "Common.h"
#include <unordered_map>
#include <list>
#include <iostream>
#include <mutex>

using namespace std;
using UBookPtr = unique_ptr<IBook>;

class LruCache : public ICache {
private:
	const Settings _settings;
	shared_ptr<IBooksUnpacker> _unpacker;
	unordered_map<string, list<BookPtr>::iterator> bookmap;
	list<BookPtr> booklist;
	size_t memory = 0;
	mutex m;

	void ClearCache() {
		while (memory > _settings.max_memory) {
			// remove lowest rank and update memory
			auto& book = booklist.front();
			memory -= book->GetContent().length();
			bookmap.erase(book->GetName());
			booklist.pop_front();
		}
	}
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ) : _settings(settings)
	{
    // реализуйте метод
		_unpacker = move(books_unpacker);
		//cerr << "Memory at construction " << memory << endl;
		//cerr << "Booklist size " << booklist.size() << endl;
		//ClearCache();
  }

  BookPtr GetBook(const string& book_name) override {
		lock_guard<mutex> lock(m);
		//cerr << "Current memory: " << memory << "; max: " << _settings.max_memory;
    // реализуйте метод
		// is book in cache?
		if (bookmap.count(book_name)) {
			// book in cache
			auto it = bookmap[book_name];
			booklist.push_back(move(*it));
			booklist.erase(it);
		} else {
			// book not in cache
			booklist.push_back(shared_ptr(_unpacker->UnpackBook(book_name)));
			memory += booklist.back()->GetContent().length();
			// TBD: if book too large -> do not add it to cache
		}
		//cerr << "; New: " << memory << endl;
		bookmap[book_name] = prev(booklist.end(), 1);
		BookPtr output = booklist.back();
		ClearCache();
		return output;
  }
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  // реализуйте функцию
	return make_unique<LruCache>(books_unpacker, settings);
}
