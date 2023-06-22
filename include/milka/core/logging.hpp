#pragma once

#include <string>

namespace milka
{
  struct Result
  {
  public:
    enum Code {
      SUCCESS,
      FAILURE,
    } res;

    // Return code
    int ret;

    // Error
    std::string error_str;

    static Result Success();
    static Result Error(int ret, std::string error_str);

    bool operator==(Code const& code);
    bool operator!=(Code const& code);
  };
}
