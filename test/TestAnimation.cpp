#include <boost/test/unit_test.hpp>

#include "Animation.h"
#include "Entity.h"

BOOST_AUTO_TEST_SUITE(TestAnimation)
class TestEntity : public Entity {
public:
    TestEntity(float sizeX, float sizeY, float positionX, float positionY)
        : Entity(sizeX, sizeY, positionX, positionY) {}

    std::shared_ptr<Projectile> shoot() override { return nullptr; }
};
BOOST_AUTO_TEST_CASE(AnimationConstructorTest)
{
    sf::Texture texture;
    Animation animation(texture, 64, 64, 10, 0.1f);
    BOOST_CHECK_EQUAL(animation.getEntity(), nullptr);
}

BOOST_AUTO_TEST_CASE(AnimationPlayStopTest)
{
    sf::Texture texture;
    Animation animation(texture, 64, 64, 10, 0.1f);
    animation.play();
    animation.stop();
    BOOST_CHECK_EQUAL(animation.getEntity(), nullptr);
}

BOOST_AUTO_TEST_CASE(AnimationPositionTest)
{
    sf::Texture texture;
    Animation animation(texture, 64, 64, 10, 0.1f);
    animation.setPosition(100.0f, 200.0f);
}

BOOST_AUTO_TEST_CASE(AnimationSetReferenceTest)
{
    sf::Texture texture;
    Animation animation(texture, 64, 64, 10, 0.1f);
    std::shared_ptr<TestEntity> entity = std::make_shared<TestEntity>(50.0f, 100.0f, 10.0f, 20.0f);
    animation.setReference(entity);
    BOOST_CHECK(animation.getEntity() == entity);
}
BOOST_AUTO_TEST_SUITE_END()