#include <string>
#include <vector>
using namespace std;

#define M1(X) M2(X) 
#define M2(X) A ## X
#define UNIQ_ID M1(__LINE__)

// Реализуйте этот макрос так, чтобы функция main компилировалась

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
