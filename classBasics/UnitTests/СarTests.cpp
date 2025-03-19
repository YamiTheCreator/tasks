#include "../classBasics/Car.h"
#include <gtest/gtest.h>

class CarTest : public ::testing::Test
{
protected:
    Car car;
};

TEST_F(CarTest, InitialState)
{
    EXPECT_FALSE(car.IsTurnedOn());
    EXPECT_EQ("standing still", car.GetDirection());
    EXPECT_EQ(0, car.GetSpeed());
    EXPECT_EQ(0, car.GetGear());
}

TEST_F(CarTest, EngineOnOff)
{
    EXPECT_TRUE(car.TurnOnEngine());
    EXPECT_TRUE(car.IsTurnedOn());
    
    EXPECT_TRUE(car.TurnOffEngine());
    EXPECT_FALSE(car.IsTurnedOn());
    
    car.TurnOnEngine();
    car.SetGear(1);
    EXPECT_FALSE(car.TurnOffEngine());
    
    car.SetGear(0);
    car.SetSpeed(10);
    EXPECT_FALSE(car.TurnOffEngine());
}

TEST_F(CarTest, GearShifting)
{
    car.TurnOnEngine();
    
    EXPECT_TRUE(car.SetGear(1));
    EXPECT_EQ(1, car.GetGear());
    
    EXPECT_TRUE(car.SetSpeed(20));
    EXPECT_EQ(20, car.GetSpeed());
    EXPECT_EQ("forward", car.GetDirection());
    
    EXPECT_TRUE(car.SetGear(2));
    EXPECT_EQ(2, car.GetGear());
    
    EXPECT_TRUE(car.SetSpeed(40));
    EXPECT_EQ(40, car.GetSpeed());
    
    EXPECT_FALSE(car.SetGear(-1));
    
    EXPECT_TRUE(car.SetGear(0));
    EXPECT_EQ(0, car.GetGear());
    
    EXPECT_TRUE(car.SetSpeed(30));
    EXPECT_EQ(30, car.GetSpeed());
    
    EXPECT_FALSE(car.SetSpeed(50));
}

TEST_F(CarTest, ReverseGear)
{
    car.TurnOnEngine();
    
    car.SetGear(1);
    car.SetSpeed(10);
    EXPECT_FALSE(car.SetGear(-1));
    
    car.SetSpeed(0);
    
    EXPECT_TRUE(car.SetGear(0));
    EXPECT_TRUE(car.SetGear(-1));
    EXPECT_EQ(-1, car.GetGear());
    
    EXPECT_TRUE(car.SetSpeed(10));
    EXPECT_EQ(10, car.GetSpeed());
    EXPECT_EQ("backward", car.GetDirection());
    
    EXPECT_FALSE(car.SetGear(1));
    
    car.SetSpeed(0);
    
    EXPECT_TRUE(car.SetGear(0));
    EXPECT_TRUE(car.SetGear(1));
}

TEST_F(CarTest, SpeedLimits)
{
    car.TurnOnEngine();
    
    car.SetGear(1);
    EXPECT_TRUE(car.SetSpeed(30));
    EXPECT_FALSE(car.SetSpeed(31));
    
    car.SetGear(2);
    EXPECT_TRUE(car.SetSpeed(50));
    EXPECT_FALSE(car.SetSpeed(51));
    EXPECT_FALSE(car.SetSpeed(19));
    
    car.SetSpeed(30);
    car.SetGear(3);
    EXPECT_TRUE(car.SetSpeed(60));
    EXPECT_FALSE(car.SetSpeed(61));
    EXPECT_FALSE(car.SetSpeed(29));
}

TEST_F(CarTest, NeutralGearBehavior)
{
    car.TurnOnEngine();
    
    car.SetGear(1);
    car.SetSpeed(20);
    
    EXPECT_TRUE(car.SetGear(0));
    
    EXPECT_TRUE(car.SetSpeed(10));
    EXPECT_EQ(10, car.GetSpeed());
    
    EXPECT_FALSE(car.SetSpeed(15));
    
    EXPECT_TRUE(car.SetSpeed(0));
    EXPECT_EQ(0, car.GetSpeed());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
