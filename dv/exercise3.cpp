#include <VExercise3.h>
#include <cstdint>
#include <bit>
#include <random>

uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  switch(a) {
    case 0:
      return ((a & 0x3) << 6) | ((b & 0x7) << 3) | (c & 0x7);
    case 1:
      return ((a & 0x3) << 6) | ((c & 0x7) << 3) | (b  & 0x7);
    case 2:
      return b;
    default:
      return c;
  }
};

struct Mystery2 {
  uint8_t count {0};
  uint16_t out;

  uint16_t reset(uint8_t a, uint8_t b) {
    out = (b << 8) | a;
    count = 0;
    return out;
  }

  uint16_t step(uint8_t a, uint8_t b) {
    switch(count++) {
      case 0:
        return out = ((a & 0xFF) << 8) | (out & 0x00FF);
      case 1:
        return out = (out & 0xFF00) | b;
      case 2:
        return out = ((out & 0x00FF) << 8) | ((out & 0xFF00) >> 8);
      case 3:
        return out = (out << 12) | ((out & 0xF0) << 4) | ((out >> 4) & 0xF0) | (out >> 12);
      default:
        return out = (0x0000 | (std::popcount(out) & 1));
    }
    count %= 5;
  }
};

  struct Excercise3_sim {
  Mystery2 state;

  uint16_t reset(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in {mystery1(a & 0x3, b & 0xFF, c & 0xFF)};
    uint8_t b_in {mystery1(a >> 2, b >> 8, c >> 8)};
    return state.reset(a_in, b_in);
  }

  uint16_t step(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in {mystery1(a & 0x3, b & 0xFF, c & 0xFF)};
    uint8_t b_in {mystery1(a >> 2, b >> 8, c >> 8)};
    return state.step(a_in, b_in);
  }
};

void step(VExercise3& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
};

int main() {
  VExercise3 model;
  Excercise3_sim sim;
  bool test_pass;

  std::default_random_engine re {std::random_device {}()};
  std::uniform_int_distribution<uint8_t> rand4 {0, 15};
  std::uniform_int_distribution<uint16_t> rand16;

  model.a = 0x23;
  model.b = 0xFFFF;
  model.c = 0x0000;

  model.reset = 1;
  step(model);
  if(model.out != sim.reset(model.a, model.b, model.c)) test_pass = false;
  //assert(model.out == 0xFF00);
  //assert(sim.reset(model.a, model.b, model.c) == 0xFF00);
  model.reset = 0;

  for(size_t cycles {0}; cycles < 100; ++cycles) {
    model.a = rand4(re);
    model.b = rand16(re);
    model.c = rand16(re);
    step(model);
    //model.eval();
    if(model.out != sim.step(model.a, model.b, model.c)) test_pass = false;
  }
}
