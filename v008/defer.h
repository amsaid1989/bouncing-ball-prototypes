#ifndef DEFER_H
#define DEFER_H

template <typename T>
struct MAKE_DEFER {
  MAKE_DEFER(T func) : m_func(func){};
  ~MAKE_DEFER() { m_func(); };
  T m_func;
};

template <typename T>
MAKE_DEFER<T> make_defer_func(T func) {
  return MAKE_DEFER<T>(func);
}

#define STRING_JOIN2(x, y) x##y
#define DO_STRING_JOIN2(x, y) STRING_JOIN2(x, y)
#define defer_copy(code)                                                       \
  auto DO_STRING_JOIN2(defer_copy_, __COUNTER__) =                             \
      make_defer_func([=]() { code; })
#define defer_ref(code)                                                        \
  auto DO_STRING_JOIN2(defer_ref_, __COUNTER__) =                              \
      make_defer_func([&]() { code; })

#endif // !DEFER_H
