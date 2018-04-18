#include <mettle.hpp>
#include "../src/character.h"

using namespace mettle;
using namespace forest;

suite<> first("Tree suite", [](auto &_) {
  tree_t ddata; // default data
  _.setup([&ddata](){
    ddata.positions = {0,0};
    ddata.age = 0;
  });
  _.test("Character creation and initialization", []() {
    tree_t ddata; // ?? Why not possible to pass ddata, size of positions is not 2
    ddata.positions = {0,0};
    ddata.age = 0;
		std::unique_ptr<Tree> tree (new Tree(ddata));
    expect(tree->GetID().length(), greater(0));
    auto recorded = tree->GetInfo();
    expect(recorded.positions.size(), equal_to(2));
    expect(recorded.age, equal_to(ddata.age));
  });
  _.test("Character comparison", [](){
    tree_t ddata; // default data
    ddata.positions = {0,0};
    ddata.age = 0;
    std::unique_ptr<Tree> tree(new Tree(ddata));
    expect(tree==tree, equal_to(true));
    std::unique_ptr<Tree> tree2(new Tree(ddata));
    expect(tree2==tree, equal_to(false));
    std::string id = tree2->GetInfo().uid;
    expect(tree2 ==id, equal_to(true));
  });
  _.test("Time Passed", [ddata]() {
		std::unique_ptr<Tree> tree (new Tree(ddata));
    tree->TimePassed();
    expect(tree->GetInfo().age, equal_to(ddata.age+1));
  });
});

