#include "./src/factory.hpp"
#include <iostream>

class Schema {
	private:
			Butter::Factory::DatabaseDefinitionFactory dbDefFactory;
	public:

	void createAdministratorTable() {
		auto table = this->dbDefFactory.createTable("Administrator");
		table.addColumn(this->dbDefFactory.createColumn("id", "SERIAL")->addPrimaryKey());
		table.addColumn(this->dbDefFactory.createColumn("username", "VARCHAR(255)")->addUnique()->addNotNull());
		table.addColumn(this->dbDefFactory.createColumn("password_hash", "TEXT")->addUnique()->addNotNull());
		table.addColumn(this->dbDefFactory.createColumn("created_at", "TIMESTAMP")->addDefault("DATETIME(\"NOW\")", true)->addNotNull());
		auto query = table.compile();
		std::cout << query << std::endl;
	};
};


int main () {
	Schema schema;

	schema.createAdministratorTable();
	return 0;
}
