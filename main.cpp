#include <cstdint>

struct foo {
  std::uint32_t a;
  std::uint32_t b;
};

static_assert(sizeof(foo) == sizeof(std::uint64_t));

std::uint32_t bar(std::uint64_t &i, const foo &f) noexcept {
  if (f.a == 2) {
    i = 4; // treats i as i64 value, so 4 is 0x0004 which overwrites foo.b
  }
  if (f.a == 2) { // false
    return f.a;
  }
  return f.b; // f.b was overwriten; returns 0
}

int main() {
  foo f{2, 3};
  return bar((std::uint64_t&)f, f);
}
