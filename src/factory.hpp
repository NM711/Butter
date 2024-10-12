#ifndef BUTTER_BUILDER_FACTORY_HPP
#define BUTTER_BUILDER_FACTORY_HPP

#include "./builder/database-definitions.hpp"

namespace Butter::Factory {

	class OperatoinQueryFactory {
		public:
			// SELECT
			// DELETE
			// UPDATE
			// INSERT	
	};
	
	class DatabaseDefinitionFactory {
		public:
			Builder::Database::ColumnBuilder *createColumn(std::string name, std::string type) {
				return new Builder::Database::ColumnBuilder(name, type);
			};
			
			Builder::Database::TableBuilder createTable(std::string name) {
				return Builder::Database::TableBuilder(name);
			};
				
			// ALTER
			// CREATE VIEW
			// CREATE PROC
			// CREATE TYPE
			// CREATE FUNCTION
			// CREATE CONSTRAINT
	};
	
};


#endif
