#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
		:	user_to_page(MAX_USER_COUNT_ + 1, 0)
		, page_to_cum(MAX_PAGE_COUNT_ + 1, 0)
	{
	}

  void Read(int user_id, int page_count) {
		size_t old_page_count = user_to_page[user_id];
		user_to_page[user_id] = page_count;
		if (old_page_count == 0) {
			user_count++;
			for (size_t i = page_count + 1; i < page_to_cum.size(); i++) {
				page_to_cum[i]++;
			}
		} else {
			for (int i = old_page_count; i < page_count; i++) {
				page_to_cum[i + 1]--;
			}
		}
  }

  double Cheer(int user_id) const {
    if (user_to_page[user_id] == 0) {
      return 0;
    }
    if (user_count == 1) {
      return 1;
    }
		auto n = page_to_cum[user_to_page[user_id]];
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return n * 1.0 / (user_count - 1);
  }

private:
	size_t user_count = 0;
	vector<size_t> user_to_page;
	vector<size_t> page_to_cum;
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;

  //int GetUserCount() const {
  //}
  //void AddUser(int user_id) {
  //}
  //void SwapUsers(int lhs_position, int rhs_position) {
  //}
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
