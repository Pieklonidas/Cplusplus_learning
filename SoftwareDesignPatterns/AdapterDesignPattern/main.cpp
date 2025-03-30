#include "Word.hpp"
#include "Pages.hpp"
#include <memory>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<Document>> documents;
    
    documents.emplace_back(std::make_unique<Word>());
    documents.emplace_back(std::make_unique<Pages>());

    for(const auto& doc : documents)
    {
        doc->exportToJSON();
        doc->serialize();
    }

    return 0;
}