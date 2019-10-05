//to initialize the basic node;
template <typename _Tp>
__detail::__List_node_base<_Tp>::__List_node_base(){
    //set two pointers;
    _M_prev = nullptr;
    _M_next = nullptr;
    //set default data;
    _M_data = _Tp();
}
//to initialize the basic node with given value;
template <typename _Tp>
__detail::__List_node_base<_Tp>::__List_node_base (const _Tp &value){
    //set the two pointers;
    _M_prev = nullptr;
    _M_next = nullptr;
    //set its data;
    _M_data = value;
}
//to initialize the basic List iterator;
template <typename _Tp>
class __detail::__List_iterator
{public:
    //the node it holds;and only element in the __List_iterator
    __List_node_base<_Tp>* _M_node;
    //three different ways of initialize;
    __List_iterator();
    __List_iterator( const __List_iterator<_Tp>& other );
    __List_iterator( __List_node_base<_Tp>* node );
    //reload operators;
    _Tp& operator*();
    _Tp* operator->();
    //reload assignment
    __List_iterator& operator=(const __List_iterator<_Tp>& input);
    //reload ==, true when nodes inside iterators are equal;
    bool operator==(const __List_iterator<_Tp>& input) const;
    //reload !=, true when nodes inside iterators are not equal;
    bool operator!=(const __List_iterator<_Tp>& input) const;
    //reload prefix ++;
    __List_iterator<_Tp>& operator++();
    //reload postfix ++;
    __List_iterator<_Tp> operator++(int);
    //reload prefix --;
    __List_iterator<_Tp>& operator--();
    //reload postfix --;
    __List_iterator<_Tp> operator--(int);
};

template <typename _Tp>
__detail::__List_iterator<_Tp>::__List_iterator(){
    //nothing special, just initialize a nothing node;
    _M_node = nullptr;
};

template <typename _Tp>
__detail::__List_iterator<_Tp>::__List_iterator( const __List_iterator<_Tp>& other ){
    //initialize iterator with the given iterator's node;
    _M_node = other._M_node;
};
template <typename _Tp>
__detail::__List_iterator<_Tp>::__List_iterator( __List_node_base<_Tp>* node ){
    //initialize iterator node with given node;
    _M_node = node;
};
template <typename _Tp>
_Tp& __detail::__List_iterator<_Tp>::operator*(){
    //reload*, return reference of node's data;
    return (this->_M_node->_M_data);
};
template <typename _Tp>
_Tp* __detail::__List_iterator<_Tp>::operator->(){
    //reload ->, return address of node's data;
    return (&this->_M_node->_M_data);
};
template <typename _Tp>
__detail::__List_iterator<_Tp>& __detail::__List_iterator<_Tp>::operator=(const __List_iterator<_Tp>& input){
    //assign the node with rhs of =;
    _M_node = input._M_node;
    //return myself's pointer;
    return *this;
};
template <typename _Tp>
bool __detail::__List_iterator<_Tp>::operator==(const __List_iterator<_Tp>& input) const{
    //reload ==, true when nodes inside iterators are equal;
    return (this->_M_node==input._M_node);
};
template <typename _Tp>
bool __detail::__List_iterator<_Tp>::operator!=(const __List_iterator<_Tp>& input) const{
    //reload !=, true when nodes inside iterators are not equal;

    return (this->_M_node!=input._M_node);
};
template <typename _Tp>
__detail::__List_iterator<_Tp>& __detail::__List_iterator<_Tp>::operator++(){
    //reload prefix++;
    this->_M_node = this->_M_node->_M_next;
    //return the result;
    return *this;
};
template <typename _Tp>
__detail::__List_iterator<_Tp> __detail::__List_iterator<_Tp>::operator++(int){
    //take down previous value;
    __detail::__List_iterator<_Tp> tmp = *this;
    //reload prefix--;
    this->_M_node = this->_M_node->_M_next;
    //return the previous value;
    return tmp;
};
template <typename _Tp>
__detail::__List_iterator<_Tp>& __detail::__List_iterator<_Tp>::operator--(){
    //reload prefix++;
    this->_M_node = this->_M_node->_M_prev;
    //return the result;
    return *this;
};
template <typename _Tp>
__detail::__List_iterator<_Tp> __detail::__List_iterator<_Tp>::operator--(int){
    //take down previous value;
    __detail::__List_iterator<_Tp> tmp = *this;
    //reload prefix--;
    this->_M_node = this->_M_node->_M_prev;
    //return the previous value;
    return tmp;
};

template <typename _Tp>
class __detail::__List_const_iterator
{
public:
    //the node it holds;and only element in the __List_iterator
    const __List_node_base<_Tp>* _M_node;
    //four basic ways of constructor;
    __List_const_iterator();
    __List_const_iterator( const __List_const_iterator<_Tp>& other );
    __List_const_iterator( const __List_node_base<_Tp>* node );
    //convert a normal iterator to a const iterator;
    __List_const_iterator( const __detail::__List_iterator<_Tp>& other );

    //reload operators
    const _Tp& operator*();
    const _Tp* operator->();
    //reload assignment
    __List_const_iterator& operator=(const __List_const_iterator<_Tp>& input);
    //reload ==, return true when node's are the same;
    bool operator==(const __List_const_iterator<_Tp>& input);
    //reload !=, return true when node's are not the same;
    bool operator!=(const __List_const_iterator<_Tp>& input);
    //reload prefix++;
    __List_const_iterator<_Tp>& operator++();
    //reload postfix++;
    __List_const_iterator<_Tp> operator++(int);
    //reload prefix--;
    __List_const_iterator<_Tp>& operator--();
    //reload postfix--;
    __List_const_iterator<_Tp> operator--(int);
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp>::__List_const_iterator(){
    //initialize a nothing node;
    _M_node = nullptr;
};

template <typename _Tp>
__detail::__List_const_iterator<_Tp>::__List_const_iterator( const __List_const_iterator<_Tp>& other ){
    //initialize the iterator's node with given iterator's node;
    _M_node = other._M_node;
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp>::__List_const_iterator( const __List_node_base<_Tp>* node ){
    //initialize the iterator'snode with given node;
    _M_node = node;
};

//convert a normal iterator to a const iterator;
template <typename _Tp>
__detail::__List_const_iterator<_Tp>::__List_const_iterator( const __List_iterator<_Tp>& other ){
    //initialize the iterator's node with given iterator's node;
    _M_node = other._M_node;
};

template <typename _Tp>
 const _Tp& __detail::__List_const_iterator<_Tp>::operator*(){
     //reload * and return ref of iterator's data;
     return (this->_M_node->_M_data);
};
template <typename _Tp>
 const _Tp* __detail::__List_const_iterator<_Tp>::operator->(){
    //reload * and return address of iterator's data;
    return (&this->_M_node->_M_data);
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp>& __detail::__List_const_iterator<_Tp>::operator=(const __List_const_iterator<_Tp>& input){
    //reload =, assign the given iterators' node to the lhs;
    _M_node= input._M_node;
    //return lhs;
    return *this;
};
template <typename _Tp>
bool __detail::__List_const_iterator<_Tp>::operator==(const __List_const_iterator<_Tp>& input){
    //reload ==, return true when node's are the same;
    return (this->_M_node==input._M_node);
};
template <typename _Tp>
bool __detail::__List_const_iterator<_Tp>::operator!=(const __List_const_iterator<_Tp>& input){
    //reload !=, return true when node's are not the same;
    return (this->_M_node!=input._M_node);
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp>& __detail::__List_const_iterator<_Tp>::operator++(){
    //reload prefix++;
    this->_M_node = this->_M_node->_M_next;
    //return the result;
    return *this;
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp> __detail::__List_const_iterator<_Tp>::operator++(int){
    //take down the original data;
    __detail::__List_const_iterator<_Tp> tmp = *this;
    //reload postfix++;
    this->_M_node = this->_M_node->_M_next;
    //return the original data;
    return tmp;
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp>& __detail::__List_const_iterator<_Tp>::operator--(){
    //reload the prefix --;
    this->_M_node = this->_M_node->_M_prev;
    //return the result;
    return *this;
};
template <typename _Tp>
__detail::__List_const_iterator<_Tp> __detail::__List_const_iterator<_Tp>::operator--(int){
    //take down the old data;
    __detail::__List_const_iterator<_Tp> tmp = *this;
    //reload the postfix--;
    this->_M_node = this->_M_node->_M_prev;
    //return the old value;
    return tmp;
};


//below are to implement the methods in doubll;
//which is some basic methods of normal doublly linked list;
template <typename _Tp>
doubll<_Tp>::doubll(){
    //connect the head and tail
    _M_head._M_prev = nullptr;
    _M_head._M_next = &_M_tail;
    _M_tail._M_next = nullptr;
    _M_tail._M_prev = &_M_head;
    //zero the size
    _M_size = 0;
};

template <typename _Tp>
doubll<_Tp>::doubll(size_t size, const _Tp& value){
    //connect the head and tail
    _M_head._M_prev = nullptr;
    _M_head._M_next = &_M_tail;
    _M_tail._M_next = nullptr;
    _M_tail._M_prev = &_M_head;
    //adjust the size
    _M_size = 0;
    __detail::__List_iterator<_Tp> pos = end();
    //while size!=0, keep adding before tail;
    while(size!=0){
        //just insert anyway
        this->doubll<_Tp>::insert(pos, value);
        size--;
    }

};

template <typename _Tp>
doubll<_Tp>::~doubll(){
    //start from the head to delete;
    __detail::__List_node_base<_Tp>* iter = _M_head._M_next;
    //temp is the node to delete;
    __detail::__List_node_base<_Tp>* temp = iter;
    //just delete till the tail
    while(iter!=&_M_tail){
        //do not delete tail and head;
        temp = iter;
        iter = iter->_M_next;
        //delete;
        delete temp;
    }
    //adjust the remaining head and tail;
    _M_head._M_next = &_M_tail;
    _M_tail._M_prev = &_M_head;
}


template <typename _Tp>
size_t doubll<_Tp>::size () const{
    //just return the size;
    return _M_size;
};

template <typename _Tp>
__detail::__List_iterator<_Tp> doubll<_Tp>::begin(){
    //return the one after head;
    return __detail::__List_iterator<_Tp>(_M_head._M_next);
};

template <typename _Tp>
__detail::__List_iterator<_Tp> doubll<_Tp>::end(){
    //return tail;
    return __detail::__List_iterator<_Tp>(&_M_tail);
};

template <typename _Tp>
__detail::__List_const_iterator<_Tp> doubll<_Tp>::cbegin() const{
    //return the const version of head;
    return __detail::__List_const_iterator<_Tp>(_M_head._M_next);
};

template <typename _Tp>
__detail::__List_const_iterator<_Tp> doubll<_Tp>::cend() const{
    //return the const version of tail;
    return __detail::__List_const_iterator<_Tp>(&_M_tail);
};

template <typename  _Tp>
__detail::__List_iterator<_Tp> doubll<_Tp>::insert(__detail::__List_iterator<_Tp> pos, const _Tp &value){
    //creat a new node to insert with value;
    __detail::__List_node_base<_Tp>* insert_node = new __detail::__List_node_base<_Tp>(value);
    //settle down where the node insert;
    insert_node->_M_prev = pos._M_node->_M_prev;
    insert_node->_M_next = pos._M_node;
    //repostion the pos node;
    pos._M_node->_M_prev->_M_next = insert_node;
    pos._M_node->_M_prev = insert_node;
    //return the inserted node in iterator format;
    this->_M_size++;
    return __detail::__List_iterator<_Tp>(insert_node);
};

template <typename  _Tp>
__detail::__List_iterator<_Tp> doubll<_Tp>::insert(__detail::__List_const_iterator<_Tp> pos, const _Tp &value){
    //creat a new node to insert with value;
    __detail::__List_node_base<_Tp>* insert_node = new __detail::__List_node_base<_Tp>(value);    //settle down where the node insert;
    //my way to to do the const cast;
    __detail::__List_iterator<_Tp> p =
            __detail::__List_iterator<_Tp>((__detail::__List_node_base<_Tp>*)pos._M_node);
    insert_node->_M_prev = p._M_node->_M_prev;
    insert_node->_M_next = p._M_node;
    //repostion the pos node;
    p._M_node->_M_prev->_M_next = insert_node;
    p._M_node->_M_prev = insert_node;
    //return the inserted node in iterator format;
    this->_M_size++;
    return __detail::__List_iterator<_Tp>(insert_node);
};

template  <typename _Tp>
__detail::__List_iterator<_Tp> doubll<_Tp>::erase (__detail::__List_iterator<_Tp> pos){
    //get the return iter;
    __detail::__List_iterator<_Tp> ret =
            __detail::__List_iterator<_Tp>(pos._M_node->_M_next);
    //first to repostion nodes around pos
    pos._M_node->_M_next->_M_prev = pos._M_node->_M_prev;
    pos._M_node->_M_prev->_M_next = pos._M_node->_M_next;
    //since we need to erase, so delete the pos's node;
    delete pos._M_node;
    //adjust the size;
    this->_M_size--;
    //return the node after deleted node;
    return ret;
};

template  <typename _Tp>
__detail::__List_iterator<_Tp> doubll<_Tp>::erase (__detail::__List_const_iterator<_Tp> pos){
    //get the return iter;
    __detail::__List_iterator<_Tp> ret = __detail::__List_iterator<_Tp>(pos._M_node->_M_next);
    //first to repostion nodes around pos
    pos._M_node->_M_next->_M_prev = pos._M_node->_M_prev;
    pos._M_node->_M_prev->_M_next = pos._M_node->_M_next;
    //since we need to erase, so delete the pos's node;
    delete pos._M_node;
    //adjust the size;
    this->_M_size--;
    //return the node after deleted node;
    return ret;
};

template <typename _Tp>
void doubll<_Tp>::reverse () {
    //use cycle method to reverse the list;
    __detail::__List_node_base <_Tp>* pre = nullptr;
    __detail::__List_node_base <_Tp>* next = nullptr;
    //begin the reverse from the original head;
    __detail::__List_node_base <_Tp>* edge = &_M_head;
    while (edge != nullptr) {
        //the one after me go afront;
        next = edge->_M_next;
        edge->_M_prev = next;
        //set my after to my pre;
        edge->_M_next = pre;
        //the next of next node should be me
        //which is originally prev node of it;
        pre = edge;
        //renew the status, move edge down the list;
        edge = next;
    }
    //switch the so-called previous head and tail
    _M_head._M_prev->_M_next = &_M_tail;
    _M_tail._M_next->_M_prev = &_M_head;
    _M_head._M_next = _M_tail._M_next;
    _M_tail._M_prev = _M_head._M_prev;
    _M_head._M_prev = nullptr;
    _M_tail._M_next = nullptr;

};

