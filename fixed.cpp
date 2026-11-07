#include <cstdint>

struct foo {
  std::uint32_t a;
  std::uint32_t b;
};

static_assert(sizeof(foo) == sizeof(std::uint64_t));

std::uint32_t bar(std::uint64_t &i, const foo &f) noexcept {
  if (f.a == 2) {
    (std::uint32_t&)i = 4; // now f.b is not overwriten: 0x04
  }
  if (f.a == 2) { // still false
    return f.a;
  }
  return f.b; // f.b was not overwriten; return 3
}

int main() {
  foo f{2, 3};
  return bar((std::uint64_t&)f, f);
}
