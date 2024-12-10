#include <string>
#include <string_view>

class Muffin 
{
    public:
        virtual ~Muffin() = default;

        std::string_view getDescription() const;
        void setDescription(std::string_view description);

        int getSize() const;
        void setSize(int size);

        bool hasChocolateChips() const;
        void setHasChocolateChips(bool hasChips);
    private:
        std::string mDescription;
        int mSize = 0;
        bool mHasChocolateChips = false;
};

std::string_view Muffin::getDescription() const { return mDescription; }

void Muffin::setDescription(std::string_view description)
{
    mDescription = description;
}

int Muffin::getSize() const { return mSize; }
void Muffin::setSize(int size) { mSize = size; }

bool Muffin::hasChocolateChips() const { return mHasChocolateChips; }

void Muffin::setHasChocolateChips(bool hasChips)
{
    mHasChocolateChips = hasChips;
}