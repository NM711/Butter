#ifndef BUTTER_BUILDER_FACTORY_HPP
#define BUTTER_BUILDER_FACTORY_HPP

#include "./builder/ddl/table.hpp"
#include "./builder/ddl/type.hpp"

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
			Builder::DDL::EnumTypeBuilder createEnum(std::string name) {
				return Builder::DDL::EnumTypeBuilder(name);
			};

			Builder::DDL::CompositeTypeBuilder createComposite(std::string name) {
				return Builder::DDL::CompositeTypeBuilder(name);
			};
	};
	
	class DatabaseDefinitionFactory {
		public:
			Builder::DDL::TableColumnBuilder *createColumn(std::string name, std::string type) {
				return new Builder::DDL::TableColumnBuilder(name, type);
			};
			
			Builder::DDL::TableBuilder createTable(std::string name) {
				return Builder::DDL::TableBuilder(name);
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
