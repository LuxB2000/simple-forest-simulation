#include <mettle.hpp>
#include "../src/libs/lumberjack/lumberjack.h"
#include "../src/libs/world/world.h"

using namespace mettle;
using namespace forest;

suite<> first("Lumberjack suite", [] (auto &mettle){
	mettle.test("lumberjack_t default data creation", [](){
		lumberjack_t data;
		expect(data.ressources, equal_to(0));
	});
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
	mettle.test("TimePassed", [](){
		// scenario: a lumberjack is located in a position without tree.
		// All the 8 neighberhood positions contains a tree with age 4.
		// after TimePassed is called we expect that the lumberjack has moved
		// and we expect no more tree with age>=3 in that position (others can appears due to seeding).
		// we also expect that the ressources of the lumberjack is greater.
		int age = 4;
		tree_t tree1, tree2, tree3, tree4, tree5, tree6, tree7, tree8;
		tree1.age = age; tree1.positions = {0,0};
		tree2.age = age; tree2.positions = {1,0};
		tree3.age = age; tree3.positions = {2,0};
		tree4.age = age; tree4.positions = {1,0};
		tree5.age = age; tree5.positions = {1,2};
		tree6.age = age; tree6.positions = {2,0};
		tree7.age = age; tree7.positions = {2,1};
		tree8.age = age; tree8.positions = {2,2};
		lumberjack_t lumberjack;
		int ressources = 0;
		lumberjack.ressources = ressources;
		lumberjack.positions = {1,1};

		std::unique_ptr<World> world (new World());
		world->AddCharacter(CharacterE::tree, &tree1);
		world->AddCharacter(CharacterE::tree, &tree2);
		world->AddCharacter(CharacterE::tree, &tree3);
		world->AddCharacter(CharacterE::tree, &tree4);
		world->AddCharacter(CharacterE::tree, &tree5);
		world->AddCharacter(CharacterE::tree, &tree6);
		world->AddCharacter(CharacterE::tree, &tree7);
		world->AddCharacter(CharacterE::tree, &tree8);
		world->AddCharacter(CharacterE::lumberjack, &lumberjack);

		auto pop_info = world->StartWorld(1); // run the world with one epoch

		// we expect the lumberjack has moved
		expect(pop_info.lumberjacks[0].positions==lumberjack.positions, equal_to(false));
		// we expect all the trees to aged to zeros.
		auto exp_no_tree = world->GetLocalPopulationInfo(pop_info.lumberjacks[0].positions);
		for(auto tree : exp_no_tree.trees)
		{
			expect(tree.age, equal_to(0));
		}
		expect(pop_info.lumberjacks[0].ressources, greater(ressources));

	});
}); //end suite
