#include "PersistenceInterface.hpp"
#include <cstdlib>
#include <cassert>

int main()
{
   PersistenceInterface* persistence1 = get_persistence_interface();

   PersistenceInterface* persistence2 = get_persistence_interface();

   persistence1->read();

   assert(persistence1 == persistence2);

   return EXIT_SUCCESS;
}