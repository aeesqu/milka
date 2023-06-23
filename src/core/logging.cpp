#include <iostream>

#include "milka/core/logging.hpp"

namespace milka
{
  bool Result::operator==(Code const& code)
  {
    return this->res == code;
  }

  bool Result::operator!=(Code const& code)
  {
    return this->res != code;
  }

  Result Result::Success()
  {
    Result r;
    r.res = Result::SUCCESS;
    r.ret = 0;
    r.error_str = "";

    return r;
  }

  Result Result::Error(int ret, std::string error_str)
  {
    Result r;
    r.res = Result::FAILURE;
    r.ret = ret;
    r.error_str = error_str;
    
    // TODO: Create different levels of warning and option
    // for printing only certain levels.
    // TODO: Give an option to write to log files.
    std::cout << "[ERROR] "<< error_str << '\n';

    return r;
  }
}
