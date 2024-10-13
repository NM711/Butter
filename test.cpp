#include "./src/factory.hpp"
#include <iostream>

class Schema {
	private:
			Butter::Factory::DatabaseDefinitionFactory dbDefFactory;
	public:
	// Create 3 methods.
	// compileRaw() -> will compile to a raw non parameterized sql statement.
	// compile() -> will compile to a parameterized sql statement, with the provided arguments in the same struct.
	// exec() -> will interact with the sql driver, and ultimately prepare the stataement under the hood.
	void createAdministratorTable() {
		std::string query = this->dbDefFactory.createTable("Administrator")
			.addColumn(this->dbDefFactory.createColumn("id", "SERIAL")->addPrimaryKey())
			.addColumn(this->dbDefFactory.createColumn("username", "VARCHAR(255)")->addUnique()->addNotNull())
			.addColumn(this->dbDefFactory.createColumn("password_hash", "TEXT")->addUnique()->addNotNull())
			.addColumn(this->dbDefFactory.createColumn("created_at", "TIMESTAMP")->addDefault("DATETIME(\"NOW\")", true)->addNotNull())
			.compile();

		std::cout << query << std::endl;
	};

	void createCredentialsType() {
		std::string query = this->dbDefFactory.types().createComposite("Credentials")
			.addColumn("username", "VARCHAR(255)")
			.addColumn("email", "VARCHAR(255)")
			.addColumn("secret", "TEXT")
			.addColumn("birthday", "TIMESTAMP")
			.compile();

		std::cout << query << std::endl;
	};
};


int main () {
	Schema schema;

	schema.createAdministratorTable();
	schema.createCredentialsType();
	return 0;
}
