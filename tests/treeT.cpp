#include <mettle.hpp>
#include "../src/libs/tree/tree.h"
#include "../src/libs/map.h"

using namespace mettle;
using namespace forest;

suite<> first("Tree suite", [](auto &_) {
  _.test("Test positions_t comparison", [](){
    positions_t p1 = {0,0};
    positions_t p1bis = {0,0};
    positions_t p2 = {1,0};
    positions_t p3 = {0,1};
    expect(p1.is_equal(p1), equal_to(true));
    expect(p1==p1, equal_to(true));
    expect(p1==p1bis, equal_to(true));
    expect(p1.is_equal(p2), equal_to(false));
    expect(p1==p2, equal_to(false));
    expect(p1.is_equal(p3), equal_to(false));
    expect(p1==p3, equal_to(false));
  });
  _.test("positions_t sum", [](){
    positions_t p1 = {1,1};
    positions_t p2 = {2,3};
    positions_t expected = {3,4}, sum = p1+p2;
    expect(sum==expected, equal_to(true));
  });
  _.test("is any position in positions_t smaller than",[](){
    positions_t pos = {0,1};
    positions_t pos1 = {-1,1};
    positions_t pos2 = {0,-1};
    expect(pos<0, equal_to(false));
    expect(pos1<0, equal_to(true));
    expect(pos2<0, equal_to(true));
  });
 _.test("is any position in positions_t bigger than",[](){
    positions_t pos={1,1};
    positions_t pos2={0,2};
    positions_t pos3={2,0};
    expect(pos>1, equal_to(false));
    expect(pos2>1, equal_to(true));
    expect(pos3>1, equal_to(true));
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
   // expect(tree2 ==id, equal_to(true));
  });
  _.test("Change the position of a character", [](){
    tree_t data;
    data.positions={0,0};
    data.age = 0;
    std::unique_ptr<Tree> tree(new Tree(data));
    positions_t new_pos = {1,1};
    tree->SetPositions(new_pos);
    expect(tree->GetInfo().positions == new_pos, equal_to(true));

  });
  _.test("Seeding", [](){
    tree_t ddata; // default data
    ddata.positions = {0,0};
    ddata.age = 0;

    tree_t newT;
    newT.positions = {1,1};
    newT.age = 0;

		std::unique_ptr<Tree> tree (new Tree(ddata));
    class CatchAnswer{
    public:
      tree_t mdata;
      void gotMessage(CharacterE c, tree_t *data){
        this->mdata = *data;//= tree_t();
        //this->mdata.positions={};
        //this->mdata.positions = data->positions;
      }
    };
    CatchAnswer catcher;
    tree->add_sig.connect(boost::bind(&CatchAnswer::gotMessage, catcher, _1, _2));
    tree->Seeding(newT.positions);
    expect(catcher.mdata.positions == newT.positions, equal_to(true));
  });
  _.test("Time Passed", []() {
    tree_t ddata; // default data
    ddata.positions = {0,0};
    ddata.age = 0;
		std::unique_ptr<Tree> tree (new Tree(ddata));
    map_forest::map_t map(10);
    class MsgCatcher{
      public:
      void ICanCatch(CharacterE c_type, character_t* p){}
      list_positions_t ICanToo(positions_t pos){
        list_positions_t opos;
        opos.resize(0);
        return opos;
      }
    };
    MsgCatcher catcher;
		tree->add_sig.connect(boost::bind(&MsgCatcher::ICanCatch, catcher, _1, _2));
		tree->ask_neigh_sig.connect(boost::bind(&MsgCatcher::ICanToo, catcher, _1));

    tree->TimePassed();
    expect(tree->GetInfo().age, equal_to(ddata.age+1));
  });
});

