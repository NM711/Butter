#ifndef BUTTER_DATABASE_DEFINITION_TABLE_BUILDER
#define BUTTER_DATABASE_DEFINITION_TABLE_BUILDER

#include "../../common/node.hpp"
#include "../../common/util.hpp"
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

  class TableColumnBuilder : Common::Node::BasicColumnNode {
    private:
      std::ostringstream query;
      Common::Node::ColumnReferenceNode *referenced;
      Common::Node::ColumnDefaultNode *defaulted;
      bool primaryKey;
      bool notNull;
      bool unique;

      void compileNameAndType() {
        this->query << this->name << " " << this->dataType << " ";
      };

      void compilePK() {
        if (this->primaryKey) {
          this->query << "PRIMARY KEY" << " ";
        };
      };

      void compileUnique() {
        if (this->unique) {
          this->query << "UNIQUE" << " ";
        };
      };

      void compileNotNull() {
        if (this->notNull) {
          this->query << "NOT NULL" << " ";
        };
      };

      void compileRef() {
        if (this->referenced != nullptr) {
          this->query << "REFERENCES"
                      << " " << this->referenced->tableQualifier << "(" << this->referenced->columnQualifier << ")"
                      << " ";
        };
      };

      void compileDefault() {
        if (this->defaulted != nullptr) {
          this->query << "DEFAULT" << " ";

          if (this->defaulted->isFunction) {
            if (!std::holds_alternative<std::string>(this->defaulted->literal)) {
              std::cout << "Cannot use a primitive type other than string when default is meant to be an identifier!"
                        << std::endl;
              exit(1);
            };

            this->query << "`" << std::get<std::string>(this->defaulted->literal) << "`";
            return;
          };

          this->query << "'";
          this->query << Common::Util::ConvertLiteralToString(this->defaulted->literal);
          this->query << "'";
        };
      };

    public:
      TableColumnBuilder(std::string columnName, std::string type) {
        this->name = columnName;
        // May make it so the user can just use an ENUM to select the type
        this->dataType = type;
        this->referenced = nullptr;
        this->defaulted = nullptr;
        this->primaryKey = false;
        this->notNull = false;
        this->unique = false;
      };

      ~TableColumnBuilder() {
        delete this->defaulted;
        delete this->referenced;
      };

      TableColumnBuilder *addDefault(Common::Node::Literal literal, bool isFn = false) {
        this->defaulted = new Common::Node::ColumnDefaultNode();
        this->defaulted->literal = literal;
        this->defaulted->isFunction = isFn;
        return this;
      };

      TableColumnBuilder *addReference(std::string tableQualifier, std::string columnQualifier) {
        Common::Node::ColumnReferenceNode *reference;
        this->referenced = new Common::Node::ColumnReferenceNode();
        this->referenced->tableQualifier = tableQualifier;
        this->referenced->columnQualifier = columnQualifier;
        return this;
      };

      TableColumnBuilder *addUnique() {
        this->unique = true;
        return this;
      };

      TableColumnBuilder *addNotNull() {
        this->notNull = true;
        return this;
      };

      TableColumnBuilder *addPrimaryKey() {
        this->primaryKey = true;
        return this;
      };

      std::string compile() {
        this->compileNameAndType();
        this->compilePK();
        this->compileUnique();
        this->compileNotNull();
        this->compileRef();
        this->compileDefault();
        return this->query.str();
      };
  };

  class TableBuilder {
    private:
      std::string name;
      std::vector<TableColumnBuilder *> columns;

    public:
      TableBuilder(std::string tableName) {
        this->name = tableName;
      };

      TableBuilder &addColumn(TableColumnBuilder *builder) {
        this->columns.push_back(builder);
        return *this;
      };

      std::string compile() {
        std::ostringstream query;
        query << "CREATE TABLE" << " `" << this->name << "` " << "(" << std::endl;

        for (int i = 0; i < this->columns.size(); ++i) {
          TableColumnBuilder *column = this->columns.at(i);
          query << "\t" << column->compile();
          Common::Util::AppendFieldsSeperator(query, i, this->columns.size() - 1);
          delete column;
        };

        query << "\n);" << std::endl;

        return query.str();
      };
  };
}; // namespace Butter::Builder::Database

#endif
