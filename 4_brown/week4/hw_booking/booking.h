#pragma once
#include <iostream>

namespace RAII {
	
	template <class Provider>
	class Booking {
	private:
		Provider * p;
	public:
		Booking(Provider * p_, int) 
			: p(p_)
		{
		}
		Booking(const Booking&) = delete;
		Booking(Booking&& b) {
			p = b.p;
			b.p = nullptr;
		}

		Booking& operator=(const Booking&) = delete;
		Booking& operator=(Booking&&) = delete;

		~Booking() {
			//std::cerr << "booking destructor" << std::endl;
			if (p) {
				p->CancelOrComplete(*this);
			}
		}
	};
}
