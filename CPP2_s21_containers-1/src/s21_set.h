#ifndef S21_SET_H_
#define S21_SET_H_

#include <iostream>

// #include "s21_vector.h"

namespace s21 {

template <class T>
class set {
 private:
  class SetIterator;  // private before public?
  class SetConstIterator;

 public:
  // in-class type overrides
  using value_type = T;
  using key_type = value_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using size_type = size_t;

  // the main public methods
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set &operator=(const set &other);

  // the public methods for iterating over class elements
  iterator begin();
  iterator end();

  // the public methods for accessing the container capacity information
  bool empty();
  size_type size();
  size_type max_size();

  // the public methods for modifying a container
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  // the public methods for viewing the container
  iterator find(const key_type &key);
  bool contains(const key_type &key);

  void pp();

 private:
  class Item {
   public:
    Item *top;
    Item *left;
    Item *right;
    value_type value;
    Item();
    Item(value_type value, Item *head);
  };

  class SetIterator {
   public:
    SetIterator(Item *pointer);
    SetIterator();
    value_type operator*();
    value_type *operator->();
    SetIterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);

   private:
    Item *item;
  };

  class SetConstIterator : public SetIterator {};

  Item *head;

  // template <typename... Args>
  // vector<std::pair<iterator, bool>> emplace(Args &&...args);

  Item *del(Item *pointer, key_type key);
  size_type traversal(Item *pointer) const;
  iterator add(value_type value, Item **pointer_to_head, Item *head);
  Item *least(Item *pointer);
  void copy(Item *head);
  void delete_set(Item *head);
};

template <class T>
set<T>::Item::Item() : value(NULL), top(NULL), left(NULL), right(NULL) {}

template <class T>
set<T>::Item::Item(T value, Item *head)
    : top(head), left(NULL), right(NULL), value(value) {}

template <class T>
set<T>::SetIterator::SetIterator(Item *pointer) : item(pointer) {}

template <class T>
set<T>::SetIterator::SetIterator() : SetIterator(NULL) {}

template <class T>
typename set<T>::value_type set<T>::SetIterator::operator*() {
  if (item == NULL)
    throw std::invalid_argument("Out of scope");
  else
    return item->value;
}

template <class T>
typename set<T>::SetIterator &set<T>::SetIterator::operator++() {
  if (item != NULL) {
    if (item->right != NULL) {
      item = item->right;
      while (item->left != NULL) item = item->left;
    } else {
      while (item->top != NULL && item->value >= item->top->value) {
        item = item->top;
      }
      item = item->top;
    }
  }
  return *this;
}

template <class T>
typename set<T>::value_type *set<T>::SetIterator::operator->() {
  if (item == NULL)
    throw std::out_of_range("Value is NULL");
  else
    return &(item->value);
}

template <class T>
bool set<T>::SetIterator::operator==(const SetIterator &other) {
  return item == other.item;
}

template <class T>
bool set<T>::SetIterator::operator!=(const SetIterator &other) {
  return item != other.item;
}

template <class T>
set<T>::set() : head(NULL) {}

template <class T>
set<T>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto it = items.begin(); it != items.end(); ++it) insert(*it);
}

template <class T>
set<T>::set(const set &s) : set() {
  copy(s.head);
}

template <class T>
set<T>::set(set &&s) : set() {
  swap(s);
  delete_set(s.head);
}

template <class T>
set<T>::~set() {
  delete_set(head);
}

template <class T>
void set<T>::copy(Item *head) {
  if (head != NULL) {
    copy(head->left);
    copy(head->right);
    this->insert(head->value);
  }
}

template <class T>
void set<T>::delete_set(Item *head) {
  if (head != NULL) {
    delete_set(head->left);
    delete_set(head->right);
    delete (head);
  }
}

template <class T>
typename set<T>::set &set<T>::operator=(const set &other) {
  // if (this->head != other.head) {
  this->clear();
  this->copy(other.head);
  // }
  return *this;
}

template <class T>
typename set<T>::iterator set<T>::begin() {
  return SetIterator(least(head));
}

template <class T>
typename set<T>::iterator set<T>::end() {
  return SetIterator();
}

template <class T>
bool set<T>::empty() {
  bool ret = true;
  if (head != NULL && head->left == NULL && head->right == NULL &&
      head->top == NULL)
    ret = false;
  return ret;
}

template <class T>
typename set<T>::size_type set<T>::size() {
  return traversal(this->head);
}

template <class T>
typename set<T>::size_type set<T>::traversal(Item *pointer) const {
  int ret = 0;
  if (pointer != NULL)
    ret = 1 + traversal(pointer->right) + traversal(pointer->left);
  return ret;
}

template <class T>
typename set<T>::size_type set<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(Item);
}
template <class T>
void set<T>::clear() {
  delete_set(head);
  head = NULL;
}
template <class T>
void set<T>::erase(iterator pos) {
  if (pos == NULL || size() == 0)
    throw std::invalid_argument(
        "A being erased element at pos and an iterator are supposed not to be "
        "empty");
  else
    head = del(head, *pos);
}

template <class T>
typename set<T>::Item *set<T>::del(Item *pointer, key_type key) {
  Item *tmp = NULL;
  // std::cout << " key " << key;
  // std::cout << " pointer->value " << pointer->value;
  // std::cout << " pointer->left " << pointer->left;
  // std::cout << " pointer->right " << pointer->right;

  if (pointer != NULL) {
    if (key < pointer->value)  // go left
      pointer->left = del(pointer->left, key);
    else if (key > pointer->value)  // go right
      pointer->right = del(pointer->right, key);
    else if (pointer->left != NULL and pointer->right != NULL) {  // found
      // std::cout << " IN_pointer->value" << pointer->value;
      // std::cout << " IN_pointer->right->value" << pointer->right->value;
      pointer->value = least(pointer->right)->value;
      // std::cout << " IN2_pointer->value" << pointer->value;
      // std::cout << " IN3_pointer->right->value" << pointer->right->value;
      pointer->right = del(pointer->right, pointer->value);
      // std::cout << " IN4_pointer->right->value" << pointer->right->value;
    } else if (pointer->left != NULL) {  // the lefttmost
      tmp = pointer;
      pointer = pointer->left;
      pointer->top = tmp->top;
    } else if (pointer->right != NULL) {  // // the rightmost
      tmp = pointer;
      pointer = pointer->right;
      pointer->top = tmp->top;
    } else {  // the one
      // std::cout << " DEL_pointer->value" << pointer->value;
      delete_set(pointer);
      pointer = NULL;
    }
    delete (tmp);
  }
  return pointer;
}

template <class T>
void set<T>::swap(set &other) {
  Item *tmp = this->head;
  this->head = other.head;
  other.head = tmp;
}

template <class T>
void set<T>::merge(set &other) {
  set<T> tmp;
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (find(*it) == NULL) {
      tmp.insert(*it);
      insert(*it);
    }
  }
  for (auto it = tmp.begin(); it != tmp.end(); ++it) other.erase(it);
}

template <class T>
typename set<T>::iterator set<T>::find(const key_type &key) {
  iterator ret = NULL;
  for (auto it = this->begin(); ((it != this->end()) && (ret == NULL)); ++it) {
    if (*it == key) ret = it;
  }
  return ret;
}

template <class T>
bool set<T>::contains(const key_type &key) {
  return (find(key) != NULL);
}

template <class T>
void set<T>::pp() {
  std::cout << " this->head->value " << this->head->value << '\n';
  std::cout << " this->head->top " << this->head->top << '\n';
  std::cout << " this->head->left " << this->head->left << '\n';
  std::cout << " this->head->right " << this->head->right << '\n';

  // set<T> *a = this->head->left;
  Item *tmp = this->head;  // ->head->left;
  // std::cout << " tmp->value " << tmp->value << '\n';
  // std::cout << " tmp->->top " << tmp->top << '\n';
  // std::cout << " tmp->->left " << tmp->left << '\n';
  // std::cout << " tmp->->right " << tmp->right << '\n';

  std::cout << "left ";
  while (tmp->left != NULL) {
    tmp = tmp->left;
    std::cout << " tmp->left->value " << tmp->value << '\n';
  }

  std::cout << "right ";
  tmp = this->head;
  while (tmp->right != NULL) {
    tmp = tmp->right;
    std::cout << " tmp->right->value " << tmp->value << '\n';
  }

  // std::cout << "left ";
  // while (tmp->left != NULL) {
  //   tmp = tmp->left;
  //   std::cout << " tmp->left->value " << tmp->value << '\n';
  // }

  // tmp = tmp->left;
  // std::cout << " tmp->value " << tmp->value << '\n';
  // tmp = tmp->left;
  // std::cout << " tmp->value " << tmp->value << '\n';

  // std::cout << " this->head->left->head->value "
  //           << this->head->left->head->value << '\n';
}

template <class T>
std::pair<typename set<T>::SetIterator, bool> set<T>::insert(
    const typename set<T>::value_type &value) {
  iterator result = add(value, &head, NULL);
  return std::pair<set<T>::SetIterator, bool>(result, result != NULL);
}

template <class T>
typename set<T>::iterator set<T>::add(value_type value, Item **pointer_to_head,
                                      Item *head) {
  if (*pointer_to_head == NULL)
    *pointer_to_head = new Item(value, head);
  else {
    if (value < (*pointer_to_head)->value)
      add(value, &(*pointer_to_head)->left, *pointer_to_head);
    else if (value != (*pointer_to_head)->value)
      add(value, &(*pointer_to_head)->right, *pointer_to_head);
  }
  return SetIterator(*pointer_to_head);
}

template <class T>
typename set<T>::Item *set<T>::least(Item *pointer) {  // Item *set<T> ?
  if (pointer != NULL)
    while (pointer->left != NULL) pointer = pointer->left;
  return pointer;
}

// template <class T>
// template <typename... Args>
// vector<std::pair<typename set<T>::SetIterator, bool>> set<T>::emplace(
//     Args &&...args) {
//   std::initializer_list<value_type> items{args...};
//   vector<std::pair<iterator, bool>> result;
//   for (auto it = items.begin(); it != items.end(); ++it) {
//     result.push_back(insert(*it));
//   }
//   return result;
// }

}  // namespace s21

#endif  // #ifndef S21_SET_H_
