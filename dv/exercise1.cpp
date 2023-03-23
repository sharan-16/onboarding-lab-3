#include <VExercise1.h>
#include <cstdint>
#include <catch2/catch_test_macros.hpp>

int main() {
  VExercise1 model;
  model.a =0;
  model.b =0;
  model.op =0;

  for (int i =0; i<256; i++){
    model.a = i;
    for (int j =1; j<256; j++){
      model.b = j;

      model.op =0;
      model.eval();
      assert(model.out == uint8_t(model.a ^ model.b));

      model.op =1;
      model.eval();
      //assert(model.out == uint8_t(model.a << model.b));

      model.op =2;
      model.eval();
      assert(model.out == uint8_t(model.a % model.b));

      model.op =3;
      model.eval();
      assert(model.out == uint8_t(~(model.a & model.b)));
    }
  }
}
