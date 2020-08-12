#include <iostream>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode* root = nullptr;
	ListNode* previous_node = nullptr;
	while (true) {
		ListNode* current_node;
		if (l1 == nullptr && l2 == nullptr) {
			return root;
		} else if (l1 != nullptr && l2 != nullptr) {
			if ((*l1).val <= (*l2).val) {
				current_node = l1;
				l1 = (*l1).next;
			} else {
				current_node = l2;
				l2 = (*l2).next;
			}
		} else if (l2 == nullptr) {
			current_node = l1;
			l1 = (*l1).next;
		} else if (l1 == nullptr) {
			current_node = l2;
			l2 = (*l2).next;
		}
		if (previous_node != nullptr) {
			(*previous_node).next = current_node;
			previous_node = (*previous_node).next;
		} else {
			previous_node = current_node;
			root = current_node;
		}
	}
	return root;
}


int main() {
	ListNode l1, l2, l3, l4;
	l4 = ListNode(4);
	l3 = ListNode(3);
	l1 = ListNode(1, &l3);
	l2 = ListNode(2, &l4);
	/*
	l1.next = &l2;
	int stop = 0;
	ListNode* current_node = &l1;
	*/
	ListNode* current_node = mergeTwoLists(&l1, &l2);
	while (current_node != nullptr) {
		cout << (*current_node).val << endl;
		current_node = (*current_node).next;


	}
}

