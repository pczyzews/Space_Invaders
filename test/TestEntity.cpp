#include <boost/test/unit_test.hpp>

#include "Entity.h"

BOOST_AUTO_TEST_SUITE(TestEntity)

class TestEntity : public Entity {
public:
        TestEntity(float sizeX, float sizeY, float positionX, float positionY)
            : Entity(sizeX, sizeY, positionX, positionY) {}

        std::shared_ptr<Projectile> shoot() override { return nullptr; }
};


BOOST_AUTO_TEST_CASE(ConstructorTest)
{
        TestEntity entity(50.0f, 100.0f, 10.0f, 20.0f);
        BOOST_CHECK_EQUAL(entity.getSizeX(), 50.0f);
        BOOST_CHECK_EQUAL(entity.getSizeY(), 100.0f);
        BOOST_CHECK_EQUAL(entity.getPositionX(), 10.0f);
        BOOST_CHECK_EQUAL(entity.getPositionY(), 20.0f);
}

BOOST_AUTO_TEST_CASE(PositionUpdateTest)
{
        TestEntity entity(50.0f, 100.0f, 10.0f, 20.0f);
        entity.updatePosition(5.0f, -10.0f);
        BOOST_CHECK_EQUAL(entity.getPositionX(), 15.0f);
        BOOST_CHECK_EQUAL(entity.getPositionY(), 10.0f);
}

BOOST_AUTO_TEST_CASE(PositionPointerTest)
{
        TestEntity entity(50.0f, 100.0f, 10.0f, 20.0f);
        auto posXPtr = entity.getPositionXPtr();
        auto posYPtr = entity.getPositionYPtr();

        BOOST_CHECK_EQUAL(*posXPtr, 10.0f);
        BOOST_CHECK_EQUAL(*posYPtr, 20.0f);
}

BOOST_AUTO_TEST_CASE(RectangleShapeTest)
{
        TestEntity entity(50.0f, 100.0f, 10.0f, 20.0f);
        sf::RectangleShape& rect = entity.getRect();
        BOOST_CHECK_EQUAL(rect.getSize().x, 50.0f);
        BOOST_CHECK_EQUAL(rect.getSize().y, 100.0f);
        BOOST_CHECK_EQUAL(rect.getPosition().x, 10.0f);
        BOOST_CHECK_EQUAL(rect.getPosition().y, 20.0f);
}

BOOST_AUTO_TEST_SUITE_END()