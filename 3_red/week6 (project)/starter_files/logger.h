#pragma once
#include <chrono>
#include <iostream>
#include <map>
#include <string>

using namespace std;
using namespace chrono;

class Logger {
	public:
		map<string, steady_clock::duration> clocks;
		steady_clock::time_point current;
		steady_clock::duration total;
		Logger() : total(0) {}
		void Start() {
			current = steady_clock::now();
		}
		void Tick(const string& str){
			auto duration = steady_clock::now() - current;
			clocks[str] += duration;
			total += duration;
			current = steady_clock::now();
		}
		~Logger(){
			cerr << "Total: " << duration_cast<milliseconds>(total).count() 
				<< " ms" << endl;
			for (auto [key, value] : clocks) {
				cerr << key << ": " << duration_cast<milliseconds>(value).count()
					<< " ms" << endl;
			}
		}
};
