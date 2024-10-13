#ifndef BUTTER_BUILDER_FACTORY_HPP
#define BUTTER_BUILDER_FACTORY_HPP

#include "./builder/definitions/table.hpp"
#include "./builder/definitions/type.hpp"

namespace Butter::Factory {

	class DataManipulationQueryFactory {
		public:
			// SELECT
			// DELETE
			// UPDATE
			// INSERT	
	};

	class TypeFactory {
		public:
			Builder::Database::EnumTypeBuilder createEnum(std::string name) {
				return Builder::Database::EnumTypeBuilder(name);
			};

			Builder::Database::CompositeTypeBuilder createComposite(std::string name) {
				return Builder::Database::CompositeTypeBuilder(name);
			};
	};
	
	class DatabaseDefinitionFactory {
		public:
			Builder::Database::TableColumnBuilder *createColumn(std::string name, std::string type) {
				return new Builder::Database::TableColumnBuilder(name, type);
			};
			
			Builder::Database::TableBuilder createTable(std::string name) {
				return Builder::Database::TableBuilder(name);
			};

			TypeFactory types() {
				return TypeFactory();
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
