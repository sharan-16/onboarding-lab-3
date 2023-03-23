#include <VExercise4.h>
#include <cstdint>
#include <bit>
#include <random>
#include <iostream>

int ex4_sim(uint8_t a, uint8_t b, uint8_t g, uint8_t sel, uint8_t cs){

  uint8_t result;
  if((cs & 0x01) == 0) {result = 0;}
  else {
    if ((sel & 0x00) == 0) {result = a;}
    else if ((sel & 0x01) == 1) {result = b;}
    else if ((sel & 0x02) == 2) {result = g;}
    else {result = a & (b|g);}
  }

  return result;

}
int main() {
  VExercise4 model;
  uint8_t i;

  std::default_random_engine re {std::random_device {}()};
  std::uniform_int_distribution<uint8_t> rand;
  
  model.cs = 1;

  model.alpha = rand (re);
  model.beta = rand (re);
  model.gamma = rand (re);

  model.sel = uint8_t(3);

  for(i=0; i<100; i++){
    model.eval();

    if(model.out != ex4_sim(model.alpha,model.beta, model.gamma, model.sel, model.cs))
    {std::cout<<model.out; return 1;}

    model.alpha = rand (re);
    model.beta = rand (re);
    model.gamma = rand (re);

    model.sel = uint8_t(i%4);
  }

  model.cs = 0;
  model.eval();
  if(model.out == 0)
  return 1;


}
