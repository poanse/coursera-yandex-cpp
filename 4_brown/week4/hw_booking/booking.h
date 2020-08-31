#include <iostream>

namespace RAII {
	
	template <class Provider>
	class Booking {
	private:
		Provider * p;
	public:
		Booking(Provider * p_, int i = 0) 
			: p(p_)
		{
		}

		Booking(const Booking&) = delete;
		Booking(Booking&& b) {
			p = b.p;
			b.p = nullptr;
		}

		Booking& operator=(const Booking&) = delete;
		Booking& operator=(Booking&& b) {
			if (p) {
				p->CancelOrComplete(*this);
			}
			p = b.p;
			b.p = nullptr;
			return *this;
		}

		~Booking() {
			//std::cerr << "booking destructor" << std::endl;
			if (p) {
				p->CancelOrComplete(*this);
			}
		}
	};
}
