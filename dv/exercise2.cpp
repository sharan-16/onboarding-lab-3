#include <VExercise2.h>
#include <cstdint>
#include <bit>
#include <random>

void step(VExercise2& model){
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}
int main() {
  VExercise2 model;
  uint16_t init;

  struct exercise2_sim
  {
    uint16_t out;
    uint16_t mask {0x050A};

    void step() {
    uint16_t bits = out & mask;
    out = (out << 1) | (std::popcount(bits) & 1);
    }
  };
  
  std::default_random_engine re {std::random_device {}()};
  std::uniform_int_distribution<uint16_t> rand16;

  exercise2_sim lfsr;
  init = rand16(re);
  lfsr.out = uint16_t(~init);

  model.init = init;
  model.reset = 1;
  step(model);
  assert(model.out == uint16_t(~init));
  model.reset = 0;

  for(int i = 0; i < 100; i++){
    
    assert(model.out = lfsr.out);
    //assert(lfsr.out = uint16_t(~init));
    step(model);
    lfsr.step();
  }

}
