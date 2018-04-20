#include <mettle.hpp>
#include "../src/libs/world.h"
#include "../src/libs/tree.h"

using namespace mettle;
using namespace forest;

suite<> first("World suite", [](auto &_) {
  _.test("World creation initialization", []() {
		std::unique_ptr<World> world (new World());
    expect(world->GetMapSize(), equal_to(10));
    expect(world->GetNumberOfCharacters(), equal_to(0));
		std::unique_ptr<World> world2 (new World(20));
    expect(world2->GetMapSize(), equal_to(20));
  });
  _.test("World get population info", [](){
    std::unique_ptr<World> world (new World());
    auto pop_info = world->GetPopulationInfo();
    expect(pop_info.trees.size(), equal_to(0));
  });
  _.test("World tree recording validation", []() {
    tree_t ddata;
    ddata.positions = {0,0};
    ddata.age = 0;
		std::unique_ptr<World> world (new World());
    auto N = world->GetNumberOfCharacters();
    auto Nt = world->GetNumberOfTrees();
    // inside the character
    boost::signals2::signal<void(CharacterE, tree_t*)> creation;
    // link with the world function
    creation.connect(boost::bind(&World::AddCharacter, world.get(), _1, _2)); // TODO: GetInstance() dans World qui est un singleton
    // triget signal
    creation(CharacterE::tree, &ddata);
    // check
    expect(world->GetNumberOfCharacters(), equal_to(N+1));
    expect(world->GetNumberOfTrees(), equal_to(Nt+1));
    // check recording and population information
    auto pop_info = world->GetPopulationInfo();
    expect(pop_info.trees.size(),equal_to(Nt+1));
  });
  _.test("World get local population information", [](){
    tree_t ddata;
    ddata.positions = {0,0};
    ddata.age = 0;
		std::unique_ptr<World> world (new World());
    world->AddCharacter(CharacterE::tree, &ddata);
    expect(world->GetLocalPopulationInfo(ddata.positions).trees.size(), equal_to(1));
    // add a second at the same place
    world->AddCharacter(CharacterE::tree, &ddata);
    expect(world->GetLocalPopulationInfo(ddata.positions).trees.size(), equal_to(2));
  });
  _.test("World Running", [](){
    std::unique_ptr<World> world (new World());
    population_info_t pop = world->StartWorld();
    // expect the program ends
    expect(pop.trees.size(),greater_equal(0));
  });
  _.test("World, time is clicking", [](){
    auto max_epoch = 10;
    std::unique_ptr<World> world (new World());
    tree_t a_tree;
    a_tree.positions = {0,0}; // position on the landskape
    a_tree.age = 0;
    world->AddCharacter(CharacterE::tree, &a_tree);

    population_info_t pop = world->StartWorld(max_epoch); // run the simulation of the world with a 
    population_info_t pop_info = world->GetPopulationInfo();
    // we expect at least one tree to be `max_epoch' years old
    auto found = false;
    for(auto t_info : pop_info.trees){
      if( t_info.age==max_epoch ){
        found = true;
        break;
      }
    }
    expect(found, equal_to(true)); 
	});
  _.test("World removing a tree",[](){
    tree_t ddata;
    ddata.positions = {0,0};
    ddata.age = 0;
		std::unique_ptr<World> world (new World());
    world->AddCharacter(CharacterE::tree, &ddata);
    auto N = world->GetNumberOfCharacters();
    auto Nt = world->GetNumberOfTrees();
    
    population_info_t pop_info = world->GetPopulationInfo();
    world->RemoveCharacter(pop_info.trees[0].uid);
    expect(world->GetNumberOfCharacters(), equal_to(N-1));
    expect(world->GetNumberOfTrees(), equal_to(Nt-1));
  });
  _.test("World get local information of a neighborhood", [](){
    tree_t ddata;
    ddata.positions = {1,1};
    ddata.age = 0;
    positions_t tgt = {0,0};
		std::unique_ptr<World> world (new World());
    world->AddCharacter(CharacterE::tree, &ddata);
    expect(world->GetNeighborhoodPopulationInfo(tgt).trees.size(), equal_to(1));
    ddata.positions = {1,0};
    world->AddCharacter(CharacterE::tree, &ddata);
    expect(world->GetNeighborhoodPopulationInfo(tgt).trees.size(), equal_to(2));
  });

});
