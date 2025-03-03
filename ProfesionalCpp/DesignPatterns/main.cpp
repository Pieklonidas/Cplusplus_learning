#include <iostream>
#include "Logger.hpp"
#include "LeastBusyFactory.hpp"
#include "Player.hpp"
#include "PlayerProxy.hpp"
#include "Paragraph.hpp"
#include "BoldParagraph.hpp"
#include "ItalicParagraph.hpp"
#include "ObservableSubject.hpp"
#include <memory>

void singletonExample()
{
    Logger::instance().setLogLevel(Logger::LogLevel::Debug);

    Logger::instance().log("test message", Logger::LogLevel::Debug);
    std::vector<std::string> items = {"item1", "item2"};
    Logger::instance().log(items, Logger::LogLevel::Error);
    Logger::instance().setLogLevel(Logger::LogLevel::Error);
    Logger::instance().log("A debug message", Logger::LogLevel::Debug);
}

void factoryExample()
{
    ToyotaFactory myFactory;
    auto myCar = myFactory.requestCar();
    std::cout << myCar->info() << std::endl;

    std::vector<std::unique_ptr<CarFactory>> factories;

    factories.push_back(std::make_unique<FordFactory>());
    factories.push_back(std::make_unique<FordFactory>());
    factories.push_back(std::make_unique<FordFactory>());
    factories.push_back(std::make_unique<ToyotaFactory>());

    factories[0]->requestCar();
    factories[0]->requestCar();
    factories[1]->requestCar();
    factories[3]->requestCar();

    LeastBusyFactory LeastBusyFactory(std::move(factories));
    for(size_t i = 0; i < 10; ++i)
    {
        auto theCar = LeastBusyFactory.requestCar();
        std::cout << theCar->info() << std::endl;
    }
}

bool informWinner(const IPlayer& player)
{
    auto result = player.sendInstantMessage("You have won! Play again?");
    if(result == "yes")
    {
        std::cout << player.getName() << " wants to play again." << std::endl;
        return true;
    }
    else if(result == "offline")
    {
        std::cout << player.getName() << " is offline." << std::endl;
    }
    else
    {
        std::cout << player.getName() << " does not want to play again." << std::endl;
    }
    return false;
}

void proxyExample()
{
    auto p1 = std::make_unique<Player>();
    informWinner(*p1);
    Player::wannaPlayAgain = false;
    informWinner(*p1);
    Player::wannaPlayAgain = true;
    auto p2 = std::make_unique<PlayerProxy>(std::move(p1));
    informWinner(*p2);
    Player::wannaPlayAgain = false;
    informWinner(*p2);
    Player::wannaPlayAgain = true;
    PlayerProxy::connected = false;
    informWinner(*p2);
    Player::wannaPlayAgain = false;
    informWinner(*p2);
    Player::wannaPlayAgain = true;

}

void decoratorExample()
{
    Paragraph p("A party? For me? Thanks!");
    std::cout << BoldParagraph(p).getHTML() << std::endl;
    std::cout << ItalicParagraph(BoldParagraph(p)).getHTML() << std::endl;
}

void observerExample()
{
    ObservableSubject subject;

    ConcreteObserver1 observer1;
    subject.addObserver(&observer1);

    subject.modifyData();

    std::cout << std::endl;

    ConcreteObserver2 observer2;
    subject.addObserver(&observer2);

    subject.modifyData();
}

int main()
{
    // singletonExample();
    // factoryExample();
    // proxyExample();
    // decoratorExample();
    observerExample();
    return 0;
}