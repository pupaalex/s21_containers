#include <gtest/gtest.h>

#include <utility>

#include "../s21_containers.h"

TEST(TestVector, BasicConstructor) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.data(), nullptr);
  EXPECT_EQ(0, vec.size());
}

TEST(TestVector, SizeConstructor) {
  s21::vector<double> vec(5);
  double* data = vec.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(5, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_DOUBLE_EQ(0, data[i]);
  }
}

TEST(TestVector, InitializerListConstructor) {
  s21::vector<char> vec({'a', 'b', 'c'});
  char* data = vec.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(3, vec.size());

  EXPECT_EQ('a', data[0]);
  EXPECT_EQ('b', data[1]);
  EXPECT_EQ('c', data[2]);
}

TEST(TestVector, CopyConstructor) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector vec(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, ordata);
  EXPECT_EQ(vec.size(), origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], ordata[i]);
  }
}

TEST(TestVector, MoveConstructor) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector vec(std::move(origin));

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(TestVector, CopyAssignment) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector<unsigned> vec(15);

  vec = origin;

  EXPECT_EQ(4, vec.size());
  EXPECT_EQ(4, origin.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(origin[i], vec[i]);
  }
}

TEST(TestVector, MoveAssignment) {
  s21::vector<unsigned> origin({1, 2, 3, 4});
  s21::vector<unsigned> vec(15);

  vec = std::move(origin);

  unsigned* data = vec.data();
  unsigned* ordata = origin.data();

  EXPECT_NE(data, nullptr);
  EXPECT_EQ(ordata, nullptr);

  EXPECT_EQ(4, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, data[i]);
  }
}

TEST(TestVector, InitializerListAssignment) {
  s21::vector<unsigned> vec(10);

  vec = {1, 2, 3, 4};

  EXPECT_EQ(4, vec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i + 1, vec[i]);
  }
}

TEST(TestVector, AtNormal) {
  s21::vector<int> vec({1, 2, 3});
  int* data = vec.data();

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], vec.at(i));
  }
}

TEST(TestVector, AtOutOfRange) {
  EXPECT_ANY_THROW({
    s21::vector<double> vec;
    vec.at(0);
  });

  EXPECT_ANY_THROW({
    s21::vector<int> vec({1, 2, 3});
    vec.at(3);
  });
}

TEST(TestVector, IndexOperator) {
  s21::vector<char> vec({'a', 'b', 'c', 'd'});
  char* data = vec.data();

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(data[i], vec[i]);
  }
}

TEST(TestVector, Front) {
  s21::vector<int> vec({'a', 'b', 'c', 'd'});
  EXPECT_EQ('a', vec.front());

  s21::vector<double> vec2({2e22});
  EXPECT_DOUBLE_EQ(2e22, vec2.front());

  s21::vector<void*> vec3(5);
  EXPECT_EQ(nullptr, vec3.front());
}

TEST(TestVector, Back) {
  s21::vector<int> vec({'a', 'b', 'c', 'd'});
  EXPECT_EQ('d', vec.back());

  s21::vector<double> vec2({2e22});
  EXPECT_DOUBLE_EQ(2e22, vec2.back());

  s21::vector<void*> vec3(5);
  EXPECT_EQ(nullptr, vec3.back());
}

TEST(TestVector, Iterator) {
  s21::vector<unsigned> vec({0, 2, 4, 6, 8, 10});
  unsigned* data = vec.data();
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    EXPECT_EQ(*(data++), *iter);
  }

  data = vec.data();

  for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter) {
    EXPECT_EQ(*(data++), *iter);
  }
}

TEST(TestVector, Reserve) {
  s21::vector<unsigned> vec;
  auto cap = vec.capacity();

  vec.reserve(15);
  cap = 15;
  EXPECT_EQ(cap, vec.capacity());

  vec.reserve(200);
  cap = 200;
  EXPECT_EQ(cap, vec.capacity());

  vec.reserve(100);
  EXPECT_EQ(cap, vec.capacity());

  EXPECT_EQ(0, vec.size());
}

TEST(TestVector, ShrinkToFit) {
  s21::vector<int> vec(25);

  vec.reserve(1000);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());

  vec.reserve(100000);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());

  vec.reserve(22);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(TestVector, Clear) {
  s21::vector<int> vec;
  vec.clear();
  EXPECT_EQ(0, vec.size());

  s21::vector<char> vec2({'a', 'b', 'c'});
  vec2.clear();
  EXPECT_EQ(0, vec2.size());
}

TEST(TestVector, Insert) {
  s21::vector<char> vec({'a'});

  auto pos = vec.insert(vec.begin(), 'b');
  EXPECT_EQ('b', *pos);

  pos = vec.begin();
  pos = vec.insert(++pos, 'c');
  EXPECT_EQ('c', *pos);

  EXPECT_EQ(3, vec.size());
  EXPECT_EQ('b', vec[0]);
  EXPECT_EQ('c', vec[1]);
  EXPECT_EQ('a', vec[2]);

  vec.insert(vec.begin(), 'd');
  pos = vec.begin();
  ++pos;
  ++pos;
  vec.insert(pos, 'e');

  EXPECT_EQ(5, vec.size());
  EXPECT_EQ('d', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('e', vec[2]);
  EXPECT_EQ('c', vec[3]);
  EXPECT_EQ('a', vec[4]);
}

TEST(TestVector, InsertEnd) {
  s21::vector<char> vec({'a'});

  auto pos = vec.insert(vec.end(), 'b');
  EXPECT_EQ('b', *pos);

  pos = vec.insert(vec.end(), 'c');
  EXPECT_EQ('c', *pos);

  EXPECT_EQ(3, vec.size());
  EXPECT_EQ('a', vec[0]);
  EXPECT_EQ('b', vec[1]);
  EXPECT_EQ('c', vec[2]);
}

TEST(TestVector, InsertEmpty) {
  s21::vector<int> vec;

  auto pos = vec.insert(vec.begin(), 11);
  EXPECT_EQ(11, *pos);

  EXPECT_EQ(1, vec.size());
  EXPECT_EQ(11, vec[0]);

  s21::vector<double> vec2;

  auto pos2 = vec2.insert(vec2.end(), 2.33);
  EXPECT_DOUBLE_EQ(2.33, *pos2);

  EXPECT_EQ(1, vec2.size());
  EXPECT_DOUBLE_EQ(2.33, vec2[0]);
}

TEST(TestVector, Erase) {
  s21::vector<int> vec({1, 2, 3, 4, 5});

  auto pos = vec.begin();
  ++pos;
  ++pos;

  vec.erase(pos);

  EXPECT_EQ(4, vec.size());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(4, vec[2]);
  EXPECT_EQ(5, vec[3]);

  pos = vec.end();
  --pos;

  vec.erase(pos);

  EXPECT_EQ(3, vec.size());
  EXPECT_EQ(1, vec[0]);
  EXPECT_EQ(2, vec[1]);
  EXPECT_EQ(4, vec[2]);

  vec.erase(vec.begin());

  EXPECT_EQ(2, vec.size());
  EXPECT_EQ(2, vec[0]);
  EXPECT_EQ(4, vec[1]);
}

TEST(TestVector, PushBack) {
  s21::vector<int> vec;

  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
  }

  EXPECT_EQ(100, vec.size());

  vec.shrink_to_fit();

  for (int i = 100; i < 1000; ++i) {
    vec.push_back(i);
  }

  EXPECT_EQ(1000, vec.size());

  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(i, vec[i]);
  }
}

TEST(TestVector, PopBack) {
  s21::vector<int> vec;

  for (int i = 0; i < 2000; ++i) {
    vec.push_back(i);
  }

  for (int i = 0; i < 500; ++i) {
    vec.pop_back();
  }

  EXPECT_EQ(1500, vec.size());

  for (int i = 0; i < 1500; ++i) {
    EXPECT_EQ(i, vec.at(i));
  }

  for (int i = 0; i < 1500; ++i) {
    vec.pop_back();
  }

  EXPECT_EQ(0, vec.size());
}

TEST(TestVector, Swap) {
  s21::vector<int> vec({1, 2, 3, 4});
  s21::vector copied_vec(vec);
  auto size = vec.size();
  auto capacity = vec.capacity();
  auto data = vec.data();

  s21::vector<int> other_vec({5, 6, 7, 8, 9, 10});
  s21::vector copied_other_vec(other_vec);
  auto other_size = other_vec.size();
  auto other_capacity = other_vec.capacity();
  auto other_data = other_vec.data();

  vec.swap(other_vec);

  EXPECT_EQ(vec.size(), other_size);
  EXPECT_EQ(other_vec.size(), size);

  EXPECT_EQ(copied_other_vec.size(), vec.size());
  EXPECT_EQ(copied_vec.size(), other_vec.size());

  EXPECT_EQ(vec.capacity(), other_capacity);
  EXPECT_EQ(other_vec.capacity(), capacity);

  EXPECT_EQ(vec.data(), other_data);
  EXPECT_EQ(other_vec.data(), data);

  for (size_t i = 0; i < copied_vec.size(); ++i) {
    EXPECT_EQ(copied_vec[i], other_vec[i]);
  }

  for (size_t i = 0; i < copied_other_vec.size(); ++i) {
    EXPECT_EQ(copied_other_vec[i], vec[i]);
  }
}

TEST(TestVector, SelfSwap) {
  s21::vector<int> vec({1, 2, 3, 4});
  s21::vector copied_vec(vec);

  vec.swap(vec);

  EXPECT_EQ(copied_vec.size(), vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(copied_vec[i], vec[i]);
  }
}
