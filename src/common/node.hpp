#ifndef BUTTER_COMMON_NODES_HPP
#define BUTTER_COMMON_NODES_HPP

#include <string>
#include <variant>

/*
        The builders will aim to create nodes, which can then be used to compile to a relevant string.
*/

namespace Butter::Common::Node {

  struct ColumnReferenceNode {
      std::string tableQualifier;
      std::string columnQualifier;
  };

  typedef std::variant<std::string, double, int> Literal;

  struct ColumnDefaultNode {
      Literal literal;
      bool isFunction;
  };

  struct BasicColumnNode {
      std::string name;
      std::string dataType;
  };

}; // namespace Butter::Common::Node

#endif
