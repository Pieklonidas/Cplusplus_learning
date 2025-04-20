#include "Database.hpp"

PersistenceInterface* instance = nullptr;

PersistenceInterface* get_persistence_interface()
{
    static bool init = [](){
        if(!instance)
        {
            std::cout << "creating new database" << std::endl;
            static Database db;
            instance = &db;
        }
        return true;
    }();

    return instance;
}

void set_persistance_interface(PersistenceInterface* persistence)
{
    instance = persistence;
}