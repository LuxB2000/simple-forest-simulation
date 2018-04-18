#include "world.h"
// constuctor
forest::World::World(int N) : m_mapSz(N){
	this->m_map = map_t(N);
}
// Run the World
forest::World::population_info_t forest::World::StartWorld(int max_epoch) const{
	for(auto epoch=0; epoch<max_epoch; epoch++){
		std::cout << "** epoch " << epoch << " **" << std::endl;
		this->m_global_time(); // time is clicking

	}
	return this->GetPopulationInfo();
}
// Add a Character
void forest::World::AddCharacter(CharacterE c_type, const character_t* data ){
	// create a specific delete function
	if ( c_type == CharacterE::tree )
	{
		// convert the data
		forest::tree_t* t_data= (forest::tree_t*)(data); //todo: check
		// smart pointer.
		Tree::TreeT new_t(new Tree(*t_data), forest::Tree::TreeDel);
		// connect the new object with the global time.
		this->m_global_time.connect(boost::bind(&Tree::TimePassed, new_t.get()));
		// let the new object create other objects.
		new_t->add_sig.connect(boost::bind(&World::AddCharacter, this, _1, _2));
		// record the character on the map.
		this->m_map.SetCharacter(t_data->positions, new_t->GetID());
		// insert the new element to the global population
		this->m_population.trees.insert(std::make_pair(new_t->GetID(),std::move(new_t)));
	}
	else if (c_type == CharacterE::man)
	{
		std::cerr  << "NOT YET IMPLEMENTED" << std::endl;
	}
	else
	{
		std::cerr << "ERROR TYPE UNKNOWN!" << std::endl;
	}
	//if( strcmp(typeid(*data).name(), "tree_t")==0 ){
	//}
}
// removing a character based on the UID
void forest::World::RemoveCharacter(std::string uid)
{
	auto it = this->m_population.trees.find(uid);
	if( it!= this->m_population.trees.end())
	{
		this->m_map.RemoveCharacter(it->second->GetInfo().positions, uid);
		this->m_global_time.disconnect(boost::bind(&Tree::TimePassed, it->second.get()));
		this->m_population.trees.erase(it);
	}

}
forest::World::population_info_t forest::World::GetPopulationInfo() const{
	population_info_t pop_info;
	pop_info.trees.resize(0); // todo: create local function to initiate the population_info_t
	for(auto tree_it= this->m_population.trees.begin(); tree_it!=this->m_population.trees.end(); tree_it++)
	{
		pop_info.trees.push_back(tree_it->second->GetInfo());
	}

	return pop_info;
}

forest::World::population_info_t forest::World::GetLocalPopulationInfo(positions_t pos) const
{
	population_info_t local_pop;
	local_pop.trees.resize(0);
	// find the information on the map
	auto ids = this->m_map.GetCharacters(pos);
	for(auto id : ids){
		auto it = this->m_population.trees.find(id);
		std::cout << "Id: " << id << std::endl;
		if(it!=m_population.trees.end())
		{
			local_pop.trees.push_back(it->second->GetInfo());
		}
	}
	return local_pop;
}
