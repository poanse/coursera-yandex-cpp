#include "test_runner.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <unordered_map>
#include <optional>
#include <unordered_set>

using namespace std;

const string HTTP_VERSION = "HTTP/1.1";

enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};

string GetCommentFromCode(HttpCode code) {
	switch (code) {
	case HttpCode::Ok:
		return "OK";
		break;
	case HttpCode::Found:
		return "Found";
		break;
	case HttpCode::NotFound:
		return "Not found";
		break;
	}
	return "Unknown code";
}

class HttpResponse {
public:
  explicit HttpResponse(HttpCode a_code)
		: code(a_code)
		, comment(GetCommentFromCode(code))
	{}

  HttpResponse& AddHeader(string name, string value) {
		headers.insert({move(name), move(value)});
		return *this;
	}

  HttpResponse& SetContent(string a_content) {
		content = move(a_content);
		auto it = headers.find("Content-Length");
		if (it == headers.end()) {
			headers.insert({"Content-Length", to_string(content.size())});
		} else {
			it->second = to_string(content.size());
		}
		return *this;
	}

  HttpResponse& SetCode(HttpCode a_code) {
		code = a_code;
		comment = GetCommentFromCode(code);
		return *this;
	}

  friend ostream& operator << (ostream& output, const HttpResponse& resp);

private:
	unordered_multimap<string, string> headers;
	string content;
	HttpCode code;
	string comment;
};

ostream& operator << (ostream& output, const HttpResponse& resp) {
	output << HTTP_VERSION << ' ' << (size_t)resp.code << resp.comment << '\n';
	for (auto& [key, value] : resp.headers) {
		output << key << ": " << value << '\n';
	}
	if (resp.content.size()) {
		output << '\n' << resp.content << '\n';
	}
	return output;
}

struct HttpRequest {
  string method, path, body;
  map<string, string> get_params;
};

pair<string, string> SplitBy(const string& what, const string& by) {
  size_t pos = what.find(by);
  if (by.size() < what.size() && pos < what.size() - by.size()) {
    return {what.substr(0, pos), what.substr(pos + by.size())};
  } else {
    return {what, {}};
  }
}

template<typename T>
T FromString(const string& s) {
  T x;
  istringstream is(s);
  is >> x;
  return x;
}

pair<size_t, string> ParseIdAndContent(const string& body) {
  auto [id_string, content] = SplitBy(body, " ");
  return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo {
  size_t user_id, consecutive_count;
};

class CommentServer {
private:
  vector<vector<string>> comments_;
  std::optional<LastCommentInfo> last_comment;
  unordered_set<size_t> banned_users;

public:
  HttpResponse ServeRequest(const HttpRequest& req, ostream& os) {
		HttpResponse resp = HttpResponse(HttpCode::NotFound);
    if (req.method == "POST") {
      if (req.path == "/add_user") {
        comments_.emplace_back();
        auto response = to_string(comments_.size() - 1);
				resp = HttpResponse(HttpCode::Ok).SetContent(response);
        //os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << "\n" << "\n"
          //<< response;
      } else if (req.path == "/add_comment") {
        auto [user_id, comment] = ParseIdAndContent(req.body);

        if (!last_comment || last_comment->user_id != user_id) {
          last_comment = LastCommentInfo {user_id, 1};
        } else if (++last_comment->consecutive_count > 3) {
          banned_users.insert(user_id);
        }

        if (banned_users.count(user_id) == 0) {
          comments_[user_id].push_back(string(comment));
					resp = HttpResponse(HttpCode::Ok);
          //os << "HTTP/1.1 200 OK\n\n";
        } else {
					resp = HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
          //os << "HTTP/1.1 302 Found\n\n"
            //"Location: /captcha\n"
            //"\n";
        }
      } else if (req.path == "/checkcaptcha") {
        if (auto [id, response] = ParseIdAndContent(req.body); response == "42") {
          banned_users.erase(id);
          if (last_comment && last_comment->user_id == id) {
            last_comment.reset();
          }
					resp = HttpResponse(HttpCode::Ok);
          //os << "HTTP/1.1 200 OK\n\n";
        } else if (response != "42") {
					resp = HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
				}
      } else {
				resp = HttpResponse(HttpCode::NotFound);
        //os << "HTTP/1.1 404 Not found\n\n";
      }
    } else if (req.method == "GET") {
      if (req.path == "/user_comments") {
        auto user_id = FromString<size_t>(req.get_params.at("user_id"));
        string response;
        for (const string& c : comments_[user_id]) {
          response += c + '\n';
        }

				resp = HttpResponse(HttpCode::Ok).SetContent(response);
        //os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << response;
      } else if (req.path == "/captcha") {
				resp = HttpResponse(HttpCode::Ok).SetContent(
						"What's the answer for The Ultimate Question of "
						"Life, the Universe, and Everything?"
				);
        //os << "HTTP/1.1 200 OK\n" << "Content-Length: 80\n" << "\n"
          //<< "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
      } else {
				resp = HttpResponse(HttpCode::NotFound);
        //os << "HTTP/1.1 404 Not found\n\n";
      }
    }
		os << resp;
		return resp;
  }
};

struct HttpHeader {
  string name, value;
};

ostream& operator<<(ostream& output, const HttpHeader& h) {
  return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) {
  return lhs.name == rhs.name && lhs.value == rhs.value;
}

struct ParsedResponse {
  int code;
  vector<HttpHeader> headers;
  string content;
};

istream& operator >>(istream& input, ParsedResponse& r) {
  string line;
  getline(input, line);

  {
    istringstream code_input(line);
    string dummy;
    code_input >> dummy >> r.code;
  }

  size_t content_length = 0;

  r.headers.clear();
  while (getline(input, line) && !line.empty()) {
    if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
      istringstream length_input(value);
      length_input >> content_length;
    } else {
      r.headers.push_back( {std::move(name), std::move(value)});
    }
  }

  r.content.resize(content_length);
  input.read(r.content.data(), r.content.size());
  return input;
}

void Test(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected) {
  stringstream ss;
  srv.ServeRequest(request, ss);
  ParsedResponse resp;
  ss >> resp;
  ASSERT_EQUAL(resp.code, expected.code);
  ASSERT_EQUAL(resp.headers, expected.headers);
  ASSERT_EQUAL(resp.content, expected.content);
}

template <typename CommentServer>
void TestServer() {
  CommentServer cs;

  const ParsedResponse ok{200};
  const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
  const ParsedResponse not_found{404};

  Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
  Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
  Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
	cerr << "6 tests passed" << endl;
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
  Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
	cerr << "9 tests passed" << endl;
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "0"}}},
    {200, {}, "Hello\nWhat are you selling?\n"}
  );
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\n"}
  );
  Test(
    cs,
    {"GET", "/captcha"},
    {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}}
  );
	cerr << "12 tests passed" << endl;
  Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
	cerr << "13 tests passed" << endl;
  Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
	cerr << "15 tests passed" << endl;
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"}
  );

  Test(cs, {"GET", "/user_commntes"}, not_found);
  Test(cs, {"POST", "/add_uesr"}, not_found);
	cerr << "All tests passed" << endl;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestServer<CommentServer>);
}
