#include <mettle.hpp>
#include "../src/libs/lumberjack/lumberjack.h"

using namespace mettle;
using namespace forest;

suite<> first("Lumberjack suite", [] (auto &mettle){
	mettle.test("Lumberjack creation",[](){
		lumberjack_t data;
		data.positions = {0,0};
		data.ressources = 0;
		std::unique_ptr<Lumberjack> lumberjack(new Lumberjack(data));
		expect(lumberjack->GetInfo().ressources, equal_to(data.ressources));
	});
}); //end suite
