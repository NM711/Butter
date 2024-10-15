#ifndef BUTTER_DML_CLAUSE_BUILDER_HPP
#define BUTTER_DML_CLAUSE_BUILDER_HPP




namespace Butter::DML::Clauses {

	enum JoinType {
		INNER,
		LEFT,
		RIGHT,
		FULL,
		FULL_OUTER,
		SELF
	};
	

	class JoinBuilder {
		JoinType type;
		JoinBuilder(JoinType type);

		JoinType &on();
		std::string compile();
	};
	
	
	class ClauseBuilder {
		public:
	};
};

#endif
