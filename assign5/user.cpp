#include "user.h"
// #include <algorithm>

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
std::ostream& operator<<(std::ostream& out, User& user) {
  std::string names = "";

  if(user._size > 0) {
    for(int i = 0; i < user._size; i++) {
      names += ", " + user._friends[i];
    }
    names = names.substr(2);
  }

  out << "User(name=" << user.get_name()
      << ", friends=[" << names << "])";
  return out;
}

User::User(const User& other) : _name(other._name), _size(other._size),
                              _capacity(other._capacity) {
  _friends = new std::string[_capacity];
  std::copy(other._friends, other._friends + other._size, _friends);
}

User::~User() {
  delete[] _friends;
}

User& User::operator=(const User& other) {
  if(this == &other) {
    return *this;
  }

  _size = other._size;
  _capacity = other._capacity;
  _name = other._name;

  delete[] _friends;
  _friends = new std::string[_capacity];

  std::copy(other._friends, other._friends + other._size, _friends);

  return *this;
}

User& User::operator+=(User& other) {
  add_friend(other._name);
  other.add_friend(_name);

  return *this;
}

bool User::operator<(const User& other) const {
  return _name < other._name;
}