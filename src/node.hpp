#ifndef BUTTER_NODES
#define BUTTER_NODES

#include <string>
#include <variant>

/*
        The builders will aim to create nodes, which can then be used to compile to a relevant string.
*/

namespace Butter::Node {

struct ColumnReferenceNode {
    std::string tableQualifier;
    std::string columnQualifier;
};

typedef std::variant<std::string, double, int> DefaultedLiteral;

struct ColumnDefaultNode {
    DefaultedLiteral literal;
    bool isFunction;    
};


}; // namespace Butter::Node

#endif
