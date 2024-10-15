#ifndef BUTTER_DML_OPERATION_BUILDER_HPP
#define BUTTER_DML_OPERATION_BUILDER_HPP

#include <string>
#include <vector>

namespace Butter::Builder::DML {

	struct PreparedQuery {
		std::string query;
		std::vector<std::string> params;
	};
	
	class AbstractDML {
		public:
			
			/*
				Returns raw sql string, not prepared
			*/
			
			virtual std::string compileRaw();

			/*
				Returns a prepared string and its provided params.
			*/
			
			virtual PreparedQuery compile();
	};
	
	class SelectBuilder : AbstractDML {
				public:
					SelectBuilder(std::string qualifier);
					SelectBuilder &column();
					SelectBuilder &columns();
	};

	class DeleteBuilder : AbstractDML {
		
	};

	class UpdateBuilder : AbstractDML {
		
	};

	class InsertBuilder : AbstractDML {
		
	};
};

#endif
