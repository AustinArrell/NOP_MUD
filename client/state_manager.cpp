
#include "state_manager.hpp"
#include "map"

state* current_state;
std::map<std::string, state*> state_map;


//**********************************************************************
void add_state(std::string name,state& s)
{
    state_map[name] = &s;
}


//**********************************************************************
void handle_events(const sf::Event& e)
{
    current_state->handle_events(e);
}


//**********************************************************************
void change_state(std::string s)
{
    // TODO: Ensure s is a valid state
    if(current_state)
        current_state->cleanup();
    current_state = state_map[s];
    current_state->startup();
}


//**********************************************************************
void update_state()
{
    current_state->update();
}


//**********************************************************************
void render_state()
{
    current_state->draw();
}

