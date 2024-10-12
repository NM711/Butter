#ifndef BUTTER_DATABASE_BUILDERS_HPP
#define BUTTER_DATABASE_BUILDERS_HPP

#include "../node.hpp"
#include "./base.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

namespace Butter::Builder::Database {

// May implement IF its needed for quality of life.
// enum ColumnDataType {
//   VARCHAR, // Defaults to 255, if we want a custom varlength you need to set a custom type,
//   TEXT,
//   INTEGER,
//   BIGINT,
//   SERIAL,
//   SMALLINT,
//   BLOB,
//   BINARY,
//   BYTEA,
//   UUID,
// };

class ColumnBuilder {
  private:
    std::string name;
    std::string dataType;
    Node::ColumnReferenceNode *referenced;
    Node::ColumnDefaultNode *defaulted;
    bool primaryKey;
    bool notNull;
    bool unique;

  public:
    ColumnBuilder(std::string columnName, std::string type) {
      this->name = columnName;
      // May make it so the user can just use an ENUM to select the type
      this->dataType = type;
      this->referenced = nullptr;
      this->defaulted = nullptr;
      this->primaryKey = false;
      this->notNull = false;
      this->unique = false;
    };

    ~ColumnBuilder() {
      delete this->defaulted;
      delete this->referenced;
    };
        
    ColumnBuilder *addDefault(Node::DefaultedLiteral literal, bool isFn = false) {
      this->defaulted = new Node::ColumnDefaultNode();
      this->defaulted->literal = literal;
      this->defaulted->isFunction = isFn;
      return this;
    };

    ColumnBuilder *addReference(std::string tableQualifier, std::string columnQualifier) {
      Butter::Node::ColumnReferenceNode *reference;
      this->referenced = new Butter::Node::ColumnReferenceNode();
      this->referenced->tableQualifier = tableQualifier;
      this->referenced->columnQualifier = columnQualifier;
      return this;
    };

    ColumnBuilder *addUnique() {
      this->unique = true;
      return this;
    };

    ColumnBuilder *addNotNull() {
      this->notNull = true;
      return this;
    };

    ColumnBuilder *addPrimaryKey() {
      this->primaryKey = true;
      return this;
    };

    std::string compile() {
      std::ostringstream query;
      query << this->name << " " << this->dataType << " ";

      if (this->primaryKey) {
        query << "PRIMARY KEY"
              << " ";
      };

      if (this->unique) {
        query << "UNIQUE"
              << " ";
      };

      if (this->notNull) {
        query << "NOT NULL"
              << " ";
      };

      if (this->referenced != nullptr) {
        query << "REFERENCES"
              << " " << this->referenced->tableQualifier << "(" << this->referenced->columnQualifier << ")"
              << " ";
      };

      if (this->defaulted != nullptr) {
        query << "DEFAULT"
              << " ";

        if (this->defaulted->isFunction) {
          if (!std::holds_alternative<std::string>(this->defaulted->literal)) {
            std::cout << "Cannot use a primitive type other than string when default is meant to be an identifier!"
                      << std::endl;
            exit(1);
          };
          query << "`" << std::get<std::string>(this->defaulted->literal) << "`";

        } else {
          query << "'";
          if (std::holds_alternative<int>(this->defaulted->literal)) {
            query << std::to_string(std::get<int>(this->defaulted->literal));
          } else if (std::holds_alternative<double>(this->defaulted->literal)) {
            query << std::to_string(std::get<double>(this->defaulted->literal));
          } else {
            query << std::get<std::string>(this->defaulted->literal);
          };

          query << "'";
        };
      };

      return query.str();
    };
};

class TableBuilder {
  private:
    std::string name;
    std::vector<ColumnBuilder*> columns;

  public:
    TableBuilder(std::string tableName) {
      this->name = tableName;
    };

    TableBuilder &addColumn(ColumnBuilder *builder) {
      this->columns.push_back(builder);
      return *this;
    };

    std::string compile() {
      std::ostringstream query;
      query << "CREATE TABLE"
            << " `" << this->name << "` "
            << "(" << std::endl;

      for (int i = 0; i < this->columns.size(); ++i) {
        ColumnBuilder *column = this->columns.at(i);

        query << "\t" << column->compile();
        
        if (i < this->columns.size() - 1) {
          query << "," << std::endl;
        };

        delete column;
      };

      query << std::endl << ");";

      return query.str();
    };
};

}; // namespace Butter::Builder::Database

#endif
