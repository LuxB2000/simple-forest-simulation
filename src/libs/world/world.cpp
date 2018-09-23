#include "world.h"
// constuctor
forest::World::World(int N) : m_mapSz(N){
	this->m_map = map_forest::map_t(N);
}
// Run the World
forest::population_info_t forest::World::StartWorld(int max_epoch) const{
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
		forest::tree_t* t_data = (forest::tree_t*)(data); //todo: check
		// smart pointer.
		Tree::TreeT new_t(new Tree(*t_data), forest::Tree::TreeDel);
		// connect the new object with the global time.
		this->m_global_time.connect(boost::bind(&Tree::TimePassed, new_t.get()));
		// let the new object create other objects.
		new_t->add_sig.connect(boost::bind(&World::AddCharacter, this, _1, _2));
		// let the new object ask for information about the map
		new_t->ask_neigh_sig.connect(boost::bind(&World::GetNeighborhood, this, _1));
		// let the new object ask for information population on particular position
		new_t->ask_info_pop_sig.connect(boost::bind(&World::GetLocalPopulationInfo, this, _1));
		// record the character on the map.
		this->m_map.SetCharacter(t_data->positions, new_t->GetID());
		// insert the new element to the global population
		this->m_population.trees.insert(std::make_pair(new_t->GetID(),std::move(new_t)));
	}
	else if (c_type == CharacterE::lumberjack)
	{
		lumberjack_t* ldata = (lumberjack_t*) data;
		LumberjackT new_l(new Lumberjack(*ldata), Lumberjack::LumberjackDel);
		// connect the signals
		// connect the new object with the global time.
		this->m_global_time.connect(boost::bind(&Lumberjack::TimePassed, new_l.get()));
		// let the lumberjack move along the map
		new_l->moving_sig.connect(boost::bind(&World::MoveCharacter, this, _1, _2, _3));
		// let the lumberjack remove trees.
		new_l->cutting_sig.connect(boost::bind(&World::RemoveCharacter, this, _1));
		// let the new object ask for information about the map
		new_l->ask_neigh_sig.connect(boost::bind(&World::GetNeighborhood, this, _1));
		// let the new object ask for information population on particular position
		new_l->ask_info_pop_sig.connect(boost::bind(&World::GetLocalPopulationInfo, this, _1));
		// record the character on the map.
		this->m_map.SetCharacter(ldata->positions, new_l->GetID());
		// insert the new element to the global population
		this->m_population.lumberjacks.insert(std::make_pair(new_l->GetID(),std::move(new_l)));
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
forest::population_info_t forest::World::GetPopulationInfo() const{
	population_info_t pop_info;
	// TODO: generate a iterator for the map and ask for each position the localpopulationinfo
	pop_info.trees.resize(0); // todo: create local function to initiate the population_info_t
	pop_info.lumberjacks.resize(0);
	for(auto tree_it= this->m_population.trees.begin(); tree_it!=this->m_population.trees.end(); tree_it++)
	{
		pop_info.trees.push_back(tree_it->second->GetInfo());
	}
	for(auto luja_it= this->m_population.lumberjacks.begin(); luja_it!=this->m_population.lumberjacks.end(); luja_it++)
	{
		pop_info.lumberjacks.push_back(luja_it->second->GetInfo());
	}
	return pop_info;
}

forest::population_info_t forest::World::GetLocalPopulationInfo(positions_t pos) const
{
	population_info_t local_pop;
	local_pop.trees.resize(0);
	// find the information on the map
	auto ids = this->m_map.GetCharacters(pos);
	for(auto id : ids){
		// @TODO: more general solution to find any character on the ID
		auto it = this->m_population.trees.find(id);
		//std::cout << "Id: " << id << std::endl;
		if(it!=m_population.trees.end())
		{
			local_pop.trees.push_back(it->second->GetInfo());
		}else{
			// have a look in the lumberjacks
			auto itl = this->m_population.lumberjacks.find(id);
			if(itl!=m_population.lumberjacks.end()){
				local_pop.lumberjacks.push_back(itl->second->GetInfo());
			}
		}
	}
	return local_pop;
}

forest::population_info_t forest::World::GetNeighborhoodPopulationInfo(positions_t pos, float area)
{
	population_info_t neigh_pop;
	neigh_pop.trees.resize(0);

	if(area<1.0){
		std::cerr << "World::GetNeighborhood, area =0 : NOT YET IMPLEMENTED" << std::endl;
		exit(-1);
	}
	if(area<1.5){
		// get the local neighborhood
		auto neigh = this->m_map.GetNeighborhood(pos);
		for(auto n_i : neigh){
			auto pop = this->GetLocalPopulationInfo(n_i);
			neigh_pop.trees.insert(neigh_pop.trees.end(), pop.trees.begin(), pop.trees.end());
		}
	}else{
		std::cerr << "World::GetNeighborhood, area =1.5 : NOT YET IMPLEMENTED" << std::endl;
		exit(-1);
	}
	return neigh_pop;
}

forest::list_positions_t forest::World::GetNeighborhood(positions_t pos){
	return this->m_map.GetNeighborhood(pos);
}

void
forest::World::MoveCharacter(std::string uid, forest::positions_t from, forest::positions_t to )
{
	// WARNING: only Lumberjack can move for now
	auto it = this->m_population.lumberjacks.find(uid);
	if( it!= this->m_population.lumberjacks.end())
	{
		// find the object and change its information
		it->second->SetPositions(to);
		// move the object on the map
		this->m_map.SetCharacter(to, it->second->GetID());
		this->m_map.RemoveCharacter(from, it->second->GetID());
	}
}
