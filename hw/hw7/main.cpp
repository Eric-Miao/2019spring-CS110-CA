// #include "doubll.hpp"
// #include <iostream>

// void test_int()
// {
//     doubll<int> myll_int(2,3);

//     myll_int.insert(myll_int.end(), 1);
//     myll_int.insert(myll_int.end(), 2);
//     myll_int.reverse();
//     myll_int.insert(myll_int.end(), 3);
//     myll_int.insert(myll_int.end(), 4);


//     __detail::__List_iterator<int> it = myll_int.begin();
//     std::cout << "Head-to-Tail: head" << "->";
//     for (; it != myll_int.end(); ++it) {
//     	std::cout << *it << "->";
//     }
//     std::cout << "tail" << std::endl;
// }

// int main()
// {
//     std::cout << "============> Test int" << std::endl;
//     test_int();
//     std::cout << "<==========================" << std::endl << std::endl;
// }

#include "doubll.hpp"
#include <iostream>

template <typename T>
void print_doubll(doubll<T>& ll, bool from_tail = false)
{
    if (!from_tail) {
        // from head to tail
        typename doubll<T>::iterator it = ll.begin();
        std::cout << "Head-to-Tail: head" << "->";
        for (; it != ll.end(); it++) {
            std::cout << *it << "->";
        }
        std::cout << "tail" << std::endl;
    } else {
        // from tail to head
        typename doubll<T>::iterator it = ll.end();
        it--;
        std::cout << "Tail-to-Head: tail" << "->";
        for (; it != --ll.begin(); it--) {
            std::cout << *it << "->";
        }
        std::cout << "head" << std::endl;
    }
}


void test_int()
{
    doubll<int> ll;

    // Testcase: 0 (memory-leaking test)
    std::cout << *(ll.end()) << std::endl;

    // Testcase: 1 1
    std::cout << (ll.cbegin() == ll.cend()) << std::endl;
    std::cout << (ll.begin() == ll.end()) << std::endl;
    //
    //    // Testcase: head-2->5->tail
    ll.insert(ll.begin(), 2);
    typename doubll<int>::iterator it = ll.insert(ll.end(), 5);
    print_doubll<int>(ll);

    // Testcase: head->2->3->tail
    it = ll.erase(it);
    ll.insert(it, 3);
    print_doubll<int>(ll);

    // Testcase: head->3->2->tail
    ll.reverse();
    print_doubll<int>(ll);

    // Testcase: head->3->1->2->tail
    --it;
    ll.insert(it, 1);
    print_doubll<int>(ll);

    // Testcase: head->3->1->5->2->4->tail
    typename doubll<int>::const_iterator it2 = ll.cend();
    ll.insert(it2--, 4);
    print_doubll<int>(ll);
    it2 = ll.insert(it2, 5);
    print_doubll<int>(ll);

    // Testcase: head->3->1->2->5->4->tail
    it2 = ll.erase(it2);
    ll.insert(++it2, 5);
    print_doubll<int>(ll);

    // Testcase: 4
    ll.reverse();
    std::cout << *(it2++) << std::endl;

    // Testcase: head->4->5->1->3->tail
    it2 = ll.erase(++it2);
    print_doubll<int>(ll);

}

void test_string()
{

    doubll<std::string> ll(2, "a");

    // Testcase: 1
    std::cout << (ll.cbegin() == ll.begin()) << std::endl;

    // Testcase: head->hello->123->a->a->tail
    ll.insert(ll.end(), "123");
    ll.insert(ll.end(), "hello");
    ll.reverse();
    print_doubll<std::string>(ll);

    // Testcase: Tail-to-Head: tail->a->a->123->hello->head
    print_doubll<std::string>(ll, true);

    // Testcase: 11
    ll.insert(ll.begin()++, "meliaphilic");
    std::cout << (ll.begin())->size() << std::endl;

    // Testcase: head->boom->hohoho->meliaphilic->hello->123->a->whatever->a->tail
    typename doubll<std::string>::const_iterator it(ll.begin());
    ll.insert(it, "hohoho");
    ll.insert(--ll.cend(), "whatever");
    ll.insert(ll.cbegin(), "boom");
    print_doubll<std::string>(ll);
}

int main()
{
    std::cout << "============> Test int" << std::endl;
    test_int();
    std::cout << "<==========================" << std::endl << std::endl;
    std::cout << "============> Test string" << std::endl;
    test_string();
    std::cout << "<==========================" << std::endl << std::endl;
}