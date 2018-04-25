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
	mettle.test("Moving", [](){
		lumberjack_t data;
		data.positions = {0,0};
		data.ressources = 0;
		std::unique_ptr<Lumberjack> lumberjack(new Lumberjack(data));
		class CatchAnswer {
			public:
			positions_t exp_from, exp_to;
			std::string exp_uid;
			CatchAnswer(std::string uid_to_catch, positions_t from, positions_t to)
			{
				this->exp_uid = uid_to_catch;
				this->exp_from = from;
				this->exp_to = to;
			}
			void GotMessage(const std::string uid, positions_t from, positions_t to){
				expect(uid==this->exp_uid, equal_to(true));
				expect(exp_from==from, equal_to(true));
				expect(exp_to==to, equal_to(true));
			}
		};
		positions_t new_pos = {1,1};
		CatchAnswer catcher(lumberjack->GetID(), data.positions, new_pos);

		lumberjack->moving_sig.connect(boost::bind(&CatchAnswer::GotMessage, catcher, _1, _2, _3));
		lumberjack->Moving(new_pos);
	});
	mettle.test("Cutting", [](){
		lumberjack_t data;
		data.positions = {1,1};
		data.ressources = 0;

		class Catcher{
			public:
			std::string exp_uid;
			Catcher(std::string uid) : exp_uid(uid) {} 
			void GotMessage(std::string catched_uid)
			{
				expect(catched_uid==this->exp_uid, equal_to(true));
			}
		};

		std::string tree_id = "someID";
		std::unique_ptr<Lumberjack> lumberjack(new Lumberjack(data));
		Catcher catcher(tree_id);

		lumberjack->cutting_sig.connect(boost::bind(&Catcher::GotMessage, catcher, _1));
		lumberjack->Cutting(tree_id);

	});
}); //end suite
