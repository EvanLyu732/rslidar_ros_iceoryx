#include "iceoryx_posh/popo/subscriber.hpp"
#include "iceoryx_posh/runtime/posh_runtime.hpp"

#include <unistd.h>

#include <iostream>

#include "CustomPointCloud.h"

int main() {
  constexpr char APP_NAME[] = "points_raw_sub";
  iox::runtime::PoshRuntime::initRuntime(APP_NAME);
  iox::popo::Subscriber<CustomPointCloud> s({"Radar", "FrontLeft", "Object"});
  ;

  while (true) {
    auto result = s.take();
    if (!result.has_error()) {
      std::cout << APP_NAME << " got value " << result.value()->width
                << std::endl;

    } else {
      std::cerr << "Err" << std::endl;
    }
    sleep(0.1);
  }
  return 0;
}