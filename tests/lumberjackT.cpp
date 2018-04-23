#include <mettle.hpp>
#include "../src/libs/lumberjack/lumberjack.h"

using namespace mettle;
using namespace forest;

suite<> first("Lumberjack suite", [] (auto &mettle){
	mettle.test("Lumberjack creation",[](){
		std::unique_ptr<Lumberjack> lumberjack(new Lumberjack());
	});
}); //end suite
