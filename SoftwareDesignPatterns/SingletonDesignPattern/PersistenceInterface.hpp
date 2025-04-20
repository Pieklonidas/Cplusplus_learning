#pragma once

class PersistenceInterface
{
public:
    virtual ~PersistenceInterface() = default;

    bool read()
    {
        return do_read();
    }

private:
    virtual bool do_read() const = 0;
    virtual bool do_write() = 0;
};

PersistenceInterface* get_persistence_interface();
void set_persistance_interface(PersistenceInterface* persistence);

extern PersistenceInterface* instance;