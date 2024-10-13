#ifndef BUTTER_DATABASE_DEFINITION_TYPE_BUILDER
#define BUTTER_DATABASE_DEFINITION_TYPE_BUILDER

#include "../../common/node.hpp"
#include "../../common/util.hpp"
#include <sstream>
#include <vector>

namespace Butter::Builder::Database {
  class EnumTypeBuilder {
    private:
      std::string name;
      std::vector<Common::Node::Literal> values;

    public:
      EnumTypeBuilder(std::string typeName) {
        this->name = typeName;
      };

      EnumTypeBuilder &addValue(Common::Node::Literal &literal) {
        this->values.push_back(literal);
        return *this;
      };

      std::string compile() {
        std::ostringstream query;
        query << "CREATE ENUM" << "`" << this->name << "`" << " " << "AS" << " " << "(\n";

        for (int i = 0; i < this->values.size(); ++i) {
          Common::Node::Literal literal = this->values.at(i);
          query << "\t" << "'" << Common::Util::ConvertLiteralToString(literal) << "'";
          Common::Util::AppendFieldsSeperator(query, i, this->values.size() - 1);          
        };

        query << "\n);" << std::endl;
        return query.str();
      };
  };

  class CompositeTypeBuilder {
    private:
      std::string name;
      std::vector<Common::Node::BasicColumnNode> columns;

    public:
      CompositeTypeBuilder(std::string typeName) {
        this->name = typeName;
      };

      CompositeTypeBuilder &addColumn(std::string name, std::string type) {
        this->columns.push_back({name, type});
        return *this;
      };

      std::string compile() {
        std::ostringstream query;

        query << "CREATE TYPE" << " " << "`" << this->name << "`" << " " << "AS" << " " << "(\n";

        for (int i = 0; i < this->columns.size(); ++i) {
          Common::Node::BasicColumnNode column = this->columns.at(i);
          query << "\t" << column.name << " " << column.dataType;
          Common::Util::AppendFieldsSeperator(query, i, this->columns.size() - 1);          
        };

        query << "\n);" << std::endl;
        return query.str();
      };
  };
}; // namespace Butter::Builder::Database

#endif
