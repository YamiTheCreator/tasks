#include <gtest/gtest.h>
#include <sstream>
#include "../classBasics/Car.h"
#include "../classBasics/CarController.h"

class CarTest : public ::testing::Test {
protected:
    Car car;
};

class CarControllerTest : public ::testing::Test {
protected:
    std::stringstream input;
    std::stringstream output;
    CarController controller{input, output};
    
    void SetUp() override {
        output.str("");
        input.str("");
    }
};

// Engine tests
TEST_F(CarTest, InitialStateEngineOff) {
    EXPECT_FALSE(car.IsTurnedOn());
    EXPECT_EQ(car.GetGear(), Gear::NeutralGear);
    EXPECT_EQ(car.GetSpeed(), 0);
    EXPECT_EQ(car.GetDirection(), Direction::standing);
}

TEST_F(CarTest, TurnOnEngine) {
    car.TurnOnEngine();
    EXPECT_TRUE(car.IsTurnedOn());
    EXPECT_EQ(car.GetGear(), Gear::NeutralGear);
    EXPECT_EQ(car.GetSpeed(), 0);
}

TEST_F(CarTest, TurnOnEngineWhenAlreadyOn) {
    car.TurnOnEngine();
    EXPECT_THROW(car.TurnOnEngine(), std::runtime_error);
}

TEST_F(CarTest, TurnOffEngine) {
    car.TurnOnEngine();
    car.TurnOffEngine();
    EXPECT_FALSE(car.IsTurnedOn());
}

TEST_F(CarTest, TurnOffEngineWhenMoving) {
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(10);
    EXPECT_THROW(car.TurnOffEngine(), std::runtime_error);
}

TEST_F(CarTest, TurnOffEngineWhenNotInNeutral) {
    car.TurnOnEngine();
    car.SetGear(1);
    EXPECT_THROW(car.TurnOffEngine(), std::runtime_error);
}

// Gear tests
TEST_F(CarTest, SetGearWhenEngineOff) {
    EXPECT_THROW(car.SetGear(1), std::runtime_error);
}

TEST_F(CarTest, SetNeutralGearWhenEngineOff) {
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_EQ(car.GetGear(), Gear::NeutralGear);
}

TEST_F(CarTest, SetInvalidGear) {
    car.TurnOnEngine();
    EXPECT_THROW(car.SetGear(-2), std::runtime_error);
    EXPECT_THROW(car.SetGear(6), std::runtime_error);
}

TEST_F(CarTest, SetReverseGearWhenMovingForward) {
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(10);
    EXPECT_THROW(car.SetGear(-1), std::runtime_error);
}

TEST_F(CarTest, SetForwardGearWhenMovingBackward) {
    car.TurnOnEngine();
    car.SetGear(-1);
    car.SetSpeed(10);
    EXPECT_THROW(car.SetGear(1), std::runtime_error);
}

TEST_F(CarTest, SetGearWithInappropriateSpeed) {
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    EXPECT_THROW(car.SetGear(3), std::runtime_error); // Third gear requires min speed 30
}

// Speed tests
TEST_F(CarTest, SetSpeedWhenEngineOff) {
    EXPECT_THROW(car.SetSpeed(10), std::runtime_error);
}

TEST_F(CarTest, SetNegativeSpeed) {
    car.TurnOnEngine();
    EXPECT_THROW(car.SetSpeed(-10), std::runtime_error);
}

TEST_F(CarTest, SetSpeedOutOfGearRange) {
    car.TurnOnEngine();
    car.SetGear(1);
    EXPECT_THROW(car.SetSpeed(31), std::runtime_error); // First gear max is 30
}

TEST_F(CarTest, AccelerateInNeutral) {
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(0);
    EXPECT_THROW(car.SetSpeed(30), std::runtime_error);
}

TEST_F(CarTest, DecelerateInNeutral) {
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(20);
    car.SetGear(0);
    EXPECT_NO_THROW(car.SetSpeed(10));
    EXPECT_EQ(car.GetSpeed(), 10);
}

// Direction tests
TEST_F(CarTest, DirectionForward) {
    car.TurnOnEngine();
    car.SetGear(1);
    car.SetSpeed(10);
    EXPECT_EQ(car.GetDirection(), Direction::forward);
}

TEST_F(CarTest, DirectionBackward) {
    car.TurnOnEngine();
    car.SetGear(-1);
    car.SetSpeed(10);
    EXPECT_EQ(car.GetDirection(), Direction::backward);
}

TEST_F(CarTest, DirectionStanding) {
    car.TurnOnEngine();
    EXPECT_EQ(car.GetDirection(), Direction::standing);
    
    car.SetGear(1);
    car.SetSpeed(10);
    car.SetSpeed(0);
    EXPECT_EQ(car.GetDirection(), Direction::standing);
}

// Gear range tests
TEST_F(CarTest, GearRanges) {
    car.TurnOnEngine();
    
    // Reverse gear (0-20)
    car.SetGear(-1);
    EXPECT_NO_THROW(car.SetSpeed(0));
    EXPECT_NO_THROW(car.SetSpeed(20));
    EXPECT_THROW(car.SetSpeed(21), std::runtime_error);
    
    // Back to neutral and stop
    car.SetGear(0);
    car.SetSpeed(0);
    
    // First gear (0-30)
    car.SetGear(1);
    EXPECT_NO_THROW(car.SetSpeed(0));
    EXPECT_NO_THROW(car.SetSpeed(30));
    EXPECT_THROW(car.SetSpeed(31), std::runtime_error);
    
    // Second gear (20-50)
    car.SetSpeed(20);
    EXPECT_NO_THROW(car.SetGear(2));
    EXPECT_NO_THROW(car.SetSpeed(50));
    EXPECT_THROW(car.SetSpeed(51), std::runtime_error);
    EXPECT_THROW(car.SetSpeed(19), std::runtime_error);
    
    // Third gear (30-60)
    car.SetSpeed(30);
    EXPECT_NO_THROW(car.SetGear(3));
    EXPECT_NO_THROW(car.SetSpeed(60));
    EXPECT_THROW(car.SetSpeed(61), std::runtime_error);
    EXPECT_THROW(car.SetSpeed(29), std::runtime_error);
    
    // Fourth gear (40-90)
    car.SetSpeed(40);
    EXPECT_NO_THROW(car.SetGear(4));
    EXPECT_NO_THROW(car.SetSpeed(90));
    EXPECT_THROW(car.SetSpeed(91), std::runtime_error);
    EXPECT_THROW(car.SetSpeed(39), std::runtime_error);
    
    // Fifth gear (50-150)
    car.SetSpeed(50);
    EXPECT_NO_THROW(car.SetGear(5));
    EXPECT_NO_THROW(car.SetSpeed(150));
    EXPECT_THROW(car.SetSpeed(151), std::runtime_error);
    EXPECT_THROW(car.SetSpeed(49), std::runtime_error);
}

// Complex scenarios
TEST_F(CarTest, CompleteScenario) {
    // Start the car
    EXPECT_NO_THROW(car.TurnOnEngine());
    
    // Move forward
    EXPECT_NO_THROW(car.SetGear(1));
    EXPECT_NO_THROW(car.SetSpeed(20));
    EXPECT_EQ(car.GetDirection(), Direction::forward);
    
    // Shift to second gear
    EXPECT_NO_THROW(car.SetGear(2));
    EXPECT_NO_THROW(car.SetSpeed(40));
    
    // Slow down and shift back to first
    EXPECT_NO_THROW(car.SetSpeed(20));
    EXPECT_NO_THROW(car.SetGear(1));
    
    // Stop
    EXPECT_NO_THROW(car.SetSpeed(0));
    
    // Shift to reverse
    EXPECT_NO_THROW(car.SetGear(-1));
    EXPECT_NO_THROW(car.SetSpeed(10));
    EXPECT_EQ(car.GetDirection(), Direction::backward);
    
    // Stop again
    EXPECT_NO_THROW(car.SetSpeed(0));
    
    // Shift to neutral and turn off
    EXPECT_NO_THROW(car.SetGear(0));
    EXPECT_NO_THROW(car.TurnOffEngine());
}

TEST_F(CarControllerTest, InfoCommand) {
    controller.HandleInput("Info");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Engine: off") != std::string::npos);
    EXPECT_TRUE(result.find("Direction: standing still") != std::string::npos);
    EXPECT_TRUE(result.find("Speed: 0") != std::string::npos);
    EXPECT_TRUE(result.find("Gear: 0") != std::string::npos);
}

TEST_F(CarControllerTest, EngineOnCommand) {
    controller.HandleInput("EngineOn");
    output.str("");
    controller.HandleInput("Info");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Engine: on") != std::string::npos);
}

TEST_F(CarControllerTest, EngineOffCommand) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("EngineOff");
    output.str("");
    controller.HandleInput("Info");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Engine: off") != std::string::npos);
}

TEST_F(CarControllerTest, SetGearCommand) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear 1");
    output.str("");
    controller.HandleInput("Info");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Gear: 1") != std::string::npos);
}

TEST_F(CarControllerTest, SetSpeedCommand) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 20");
    output.str("");
    controller.HandleInput("Info");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Speed: 20") != std::string::npos);
    EXPECT_TRUE(result.find("Direction: forward") != std::string::npos);
}

TEST_F(CarControllerTest, InvalidCommand) {
    EXPECT_THROW(controller.HandleInput("InvalidCommand"), std::runtime_error);
}

TEST_F(CarControllerTest, InvalidGearArgument) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear abc");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Invalid command argument") != std::string::npos);
}

TEST_F(CarControllerTest, InvalidSpeedArgument) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed abc");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Invalid command argument") != std::string::npos);
}

TEST_F(CarControllerTest, DirectionOutput) {
    controller.HandleInput("EngineOn");
    
    // Test standing
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Direction: standing still") != std::string::npos);
    
    // Test forward
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 10");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Direction: forward") != std::string::npos);
    
    // Back to neutral and stop
    controller.HandleInput("SetSpeed 0");
    controller.HandleInput("SetGear 0");
    
    // Test backward
    controller.HandleInput("SetGear -1");
    controller.HandleInput("SetSpeed 10");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Direction: backward") != std::string::npos);
}

TEST_F(CarControllerTest, CompleteScenario) {
    // Start the car
    controller.HandleInput("EngineOn");
    
    // Move forward
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 20");
    
    // Check status
    output.str("");
    controller.HandleInput("Info");
    std::string result = output.str();
    EXPECT_TRUE(result.find("Engine: on") != std::string::npos);
    EXPECT_TRUE(result.find("Direction: forward") != std::string::npos);
    EXPECT_TRUE(result.find("Speed: 20") != std::string::npos);
    EXPECT_TRUE(result.find("Gear: 1") != std::string::npos);
    
    // Shift to second gear
    controller.HandleInput("SetGear 2");
    controller.HandleInput("SetSpeed 40");
    
    // Slow down and shift back to first
    controller.HandleInput("SetSpeed 20");
    controller.HandleInput("SetGear 1");
    
    // Stop
    controller.HandleInput("SetSpeed 0");
    
    // Shift to reverse
    controller.HandleInput("SetGear -1");
    controller.HandleInput("SetSpeed 10");
    
    // Check status again
    output.str("");
    controller.HandleInput("Info");
    result = output.str();
    EXPECT_TRUE(result.find("Direction: backward") != std::string::npos);
    EXPECT_TRUE(result.find("Speed: 10") != std::string::npos);
    EXPECT_TRUE(result.find("Gear: -1") != std::string::npos);
    
    // Stop again
    controller.HandleInput("SetSpeed 0");
    
    // Shift to neutral and turn off
    controller.HandleInput("SetGear 0");
    controller.HandleInput("EngineOff");
    
    // Final check
    output.str("");
    controller.HandleInput("Info");
    result = output.str();
    EXPECT_TRUE(result.find("Engine: off") != std::string::npos);
    EXPECT_TRUE(result.find("Direction: standing still") != std::string::npos);
    EXPECT_TRUE(result.find("Speed: 0") != std::string::npos);
    EXPECT_TRUE(result.find("Gear: 0") != std::string::npos);
}

TEST_F(CarControllerTest, ErrorHandling) {
    // Try to set gear when engine is off
    controller.HandleInput("SetGear 1");
    EXPECT_TRUE(output.str().find("Сannot set gear while engine is off") != std::string::npos);
    output.str("");
    
    // Try to set speed when engine is off
    controller.HandleInput("SetSpeed 10");
    EXPECT_TRUE(output.str().find("Cannot set speed while engine is off") != std::string::npos);
    output.str("");
    
    // Turn on engine
    controller.HandleInput("EngineOn");
    output.str("");
    
    // Try to turn on engine again
    controller.HandleInput("EngineOn");
    EXPECT_TRUE(output.str().find("Engine is already turned on") != std::string::npos);
    output.str("");
    
    // Try to set invalid gear
    controller.HandleInput("SetGear 10");
    EXPECT_TRUE(output.str().find("Invalid gear") != std::string::npos);
    output.str("");
    
    // Try to set negative speed
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed -10");
    EXPECT_TRUE(output.str().find("Speed cannot be negative") != std::string::npos);
    output.str("");
    
    // Try to set speed out of gear range
    controller.HandleInput("SetSpeed 40");
    EXPECT_TRUE(output.str().find("Speed is out of gear range") != std::string::npos);
    output.str("");
    
    // Try to turn off engine when not in neutral
    controller.HandleInput("SetSpeed 10");
    controller.HandleInput("EngineOff");
    EXPECT_TRUE(output.str().find("Car must be stopped and in neutral gear") != std::string::npos);
    output.str("");
    
    // Try to set reverse gear while moving
    controller.HandleInput("SetGear -1");
    EXPECT_TRUE(output.str().find("Cannot reverse while moving") != std::string::npos);
    output.str("");
}

TEST_F(CarControllerTest, NeutralGearBehavior) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 20");
    controller.HandleInput("SetGear 0");
    
    // Try to accelerate in neutral
    controller.HandleInput("SetSpeed 30");
    EXPECT_TRUE(output.str().find("Cannot accelerate on neutral") != std::string::npos);
    output.str("");
    
    // Can decelerate in neutral
    controller.HandleInput("SetSpeed 10");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Speed: 10") != std::string::npos);
}

TEST_F(CarControllerTest, GearTransitions) {
    controller.HandleInput("EngineOn");
    
    // First gear
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 30");
    
    // Direct transition to third gear (should work at speed 30)
    controller.HandleInput("SetGear 3");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Gear: 3") != std::string::npos);
    
    // Try to go to fifth gear (should fail - speed too low)
    controller.HandleInput("SetGear 5");
    EXPECT_TRUE(output.str().find("Unsuitable current speed") != std::string::npos);
    output.str("");
    
    // Accelerate and try again
    controller.HandleInput("SetSpeed 50");
    controller.HandleInput("SetGear 5");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Gear: 5") != std::string::npos);
    
    // Try to go back to first gear (should fail - speed too high)
    controller.HandleInput("SetGear 1");
    EXPECT_TRUE(output.str().find("Unsuitable current speed") != std::string::npos);
}

TEST_F(CarControllerTest, ReverseToForwardTransition) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear -1");
    controller.HandleInput("SetSpeed 10");
    
    // Try to go directly to first gear while moving backward
    controller.HandleInput("SetGear 1");
    EXPECT_TRUE(output.str().find("Unsuitable current speed") != std::string::npos);
    output.str("");
    
    // Stop first
    controller.HandleInput("SetSpeed 0");
    
    // Now can switch to first
    controller.HandleInput("SetGear 1");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Gear: 1") != std::string::npos);
}

TEST_F(CarControllerTest, ForwardToReverseTransition) {
    controller.HandleInput("EngineOn");
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 10");
    
    // Try to go directly to reverse gear while moving forward
    controller.HandleInput("SetGear -1");
    EXPECT_TRUE(output.str().find("Cannot reverse while moving") != std::string::npos);
    output.str("");
    
    // Stop first
    controller.HandleInput("SetSpeed 0");
    
    // Now can switch to reverse
    controller.HandleInput("SetGear -1");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Gear: -1") != std::string::npos);
}

TEST_F(CarControllerTest, SpeedAbsoluteValue) {
    controller.HandleInput("EngineOn");
    
    // Forward
    controller.HandleInput("SetGear 1");
    controller.HandleInput("SetSpeed 20");
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Speed: 20") != std::string::npos);
    
    // Stop and reverse
    controller.HandleInput("SetSpeed 0");
    controller.HandleInput("SetGear -1");
    controller.HandleInput("SetSpeed 15");
    
    // Speed should be reported as positive value
    output.str("");
    controller.HandleInput("Info");
    EXPECT_TRUE(output.str().find("Speed: 15") != std::string::npos);
    EXPECT_TRUE(output.str().find("Direction: backward") != std::string::npos);
}

TEST_F(CarControllerTest, MissingArguments) {
    controller.HandleInput("EngineOn");
    
    // Missing gear value
    controller.HandleInput("SetGear");
    EXPECT_TRUE(output.str().find("Invalid command argument") != std::string::npos);
    output.str("");
    
    // Missing speed value
    controller.HandleInput("SetSpeed");
    EXPECT_TRUE(output.str().find("Invalid command argument") != std::string::npos);
}

TEST_F(CarControllerTest, ExtraArguments) {
    controller.HandleInput("EngineOn extra arguments");
    output.str("");
    controller.HandleInput("Info");
    // Should ignore extra arguments and execute command
    EXPECT_TRUE(output.str().find("Engine: on") != std::string::npos);
    
    controller.HandleInput("SetGear 1 extra arguments");
    output.str("");
    controller.HandleInput("Info");
    // Should ignore extra arguments and execute command
    EXPECT_TRUE(output.str().find("Gear: 1") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
