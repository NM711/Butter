#ifndef BUTTER_COMMON_UTIL_HPP
#define BUTTER_COMMON_UTIL_HPP

#include "./node.hpp"
#include <sstream>
#include <string>

namespace Butter::Common {
  class Util {
    public:
      static std::string ConvertLiteralToString(Node::Literal &literal) {
        std::string literalStr;
        if (std::holds_alternative<int>(literal)) {
          literalStr = std::to_string(std::get<int>(literal));
        } else if (std::holds_alternative<double>(literal)) {
          literalStr = std::to_string(std::get<double>(literal));
        } else {
          literalStr = std::get<std::string>(literal);
        };

        return literalStr;
      };

      static void AppendFieldsSeperator(std::ostringstream &stream, int index, int length) {
        if (index < length) {
          stream << ",\n";
        };
      };
  };

}; // namespace Butter::Common

#endif
