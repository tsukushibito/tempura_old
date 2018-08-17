#include <temp/tempura.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  using namespace temp;
  class Test : public SmartPointerType<Test> {
   public:
    Test(Int8 v) : value_(v) {
      TEMP_LOG_TRACE("Test", fmt::format("Test::Test({0})", value_));
    }
    virtual ~Test() { TEMP_LOG_TRACE("Test", "Test::~Test()"); }

   private:
    Int8 value_;
  };

  {
    auto allocator = std::allocator<Test>();
    auto s = Test::allocateShared(allocator, 0);
    auto u = Test::allocateUnique(allocator, 1);
  }

  return 0;
}
