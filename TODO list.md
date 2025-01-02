Alright, I've got this task to write unit tests for the `Biliardo` class using Doctest. I'm not entirely familiar
with Doctest, but I've used other testing frameworks before, so the concepts should be similar. Let's start by
understanding what Doctest is and how it works.

Doctest is a C++ test framework that allows you to write tests in the form of doc comments. It's pretty
straightforward and integrates well with existing codebases. The idea is to write tests right above the functions
they're testing, which keeps everything organized and easy to maintain.

First things first, I need to include Doctest in my project. Since it's a header-only library, I can just download
the single header file and include it in my test file. I should make sure that the path to the Doctest header is
correctly set in my build system.

Now, looking at the `Biliardo` class, it seems quite comprehensive. There are methods for setting parameters like
`l`, `r1`, `r2`, changing the type of the billiard, and performing simulations. I need to test all these
functionalities to ensure they work as expected.

Let's start by testing the constructor and the type-related functions. The `BiliardoType` enum has three possible
values: `circle`, `ellipse`, and `hyperbola`. The constructor takes this type as an argument, and there's a method
to change the type. I need to make sure that the type is set correctly and that invalid types are handled
properly.

Here's a basic test for the constructor and the `type` method:

```cpp
TEST_CASE("Constructor and type getter") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    REQUIRE(billiard.type() == bt::BiliardoType::circle);

    bt::Biliardo ellipse_billiard(bt::BiliardoType::ellipse);
    REQUIRE(ellipse_billiard.type() == bt::BiliardoType::ellipse);

    bt::Biliardo hyperbola_billiard(bt::BiliardoType::hyperbola);
    REQUIRE(hyperbola_billiard.type() == bt::BiliardoType::hyperbola);
}
```

Next, I need to test the `changeType` method to ensure it correctly changes the type and handles invalid inputs.

```cpp
TEST_CASE("Change type") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    REQUIRE(billiard.changeType(bt::BiliardoType::ellipse));
    REQUIRE(billiard.type() == bt::BiliardoType::ellipse);

    // Trying to set an invalid type
    REQUIRE_FALSE(billiard.changeType(static_cast<bt::BiliardoType>(3)));
    REQUIRE(billiard.type() == bt::BiliardoType::ellipse);
}
```

Now, let's move on to the setter methods: `l`, `r1`, and `r2`. These methods should throw exceptions if negative
or zero values are provided. I need to test both the valid and invalid cases.

```cpp
TEST_CASE("Setter methods with valid inputs") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    billiard.l(5.0);
    billiard.r1(2.0);
    billiard.r2(3.0);

    REQUIRE(billiard.l() == 5.0);
    REQUIRE(billiard.r1() == 2.0);
    REQUIRE(billiard.r2() == 3.0);
}

TEST_CASE("Setter methods with invalid inputs") {
    bt::Biliardo billiard(bt::BiliardoType::circle);

    // Testing l with invalid value
    REQUIRE_THROWS_AS(billiard.l(-1.0), std::invalid_argument);
    REQUIRE_THROWS_AS(billiard.l(0.0), std::invalid_argument);

    // Testing r1 with invalid value
    REQUIRE_THROWS_AS(billiard.r1(-1.0), std::invalid_argument);
    REQUIRE_THROWS_AS(billiard.r1(0.0), std::invalid_argument);

    // Testing r2 with invalid value
    REQUIRE_THROWS_AS(billiard.r2(-1.0), std::invalid_argument);
    REQUIRE_THROWS_AS(billiard.r2(0.0), std::invalid_argument);
}
```

The `modify` method allows changing multiple parameters at once. I need to ensure that it correctly updates all
parameters and handles invalid inputs.

```cpp
TEST_CASE("Modify method with valid inputs") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    bool result = billiard.modify(5.0, 2.0, 3.0);
    REQUIRE(result);
    REQUIRE(billiard.l() == 5.0);
    REQUIRE(billiard.r1() == 2.0);
    REQUIRE(billiard.r2() == 3.0);
}

TEST_CASE("Modify method with invalid inputs") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    bool result = billiard.modify(-1.0, 2.0, 3.0);
    REQUIRE_FALSE(result);
    // Check if parameters remain unchanged
    REQUIRE(billiard.l() != -1.0);
    REQUIRE(billiard.r1() != 2.0);
    REQUIRE(billiard.r2() != 3.0);

    result = billiard.modify(5.0, 0.0, 3.0);
    REQUIRE_FALSE(result);
    REQUIRE(billiard.r1() != 0.0);

    result = billiard.modify(5.0, 2.0, -1.0);
    REQUIRE_FALSE(result);
    REQUIRE(billiard.r2() != -1.0);
}
```

Now, for the simulation methods like `simulate` and `calculateTrajectory`, I need to verify that they perform the
expected calculations based on the billiard type and parameters. This might involve some mathematical assertions,
so I have to make sure I understand the expected behavior for each billiard type.

For example, for a circular billiard, the trajectory should be straightforward, while for elliptical and
hyperbolic billiards, the trajectories would be more complex. I need to set up test cases with known inputs and
expected outputs.

```cpp
TEST_CASE("Simulate method for circle billiard") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    billiard.r1(2.0); // Assuming r1 is the radius for circle

    std::vector<Point> trajectory = billiard.simulate(start_point, direction);
    // Add assertions to check the trajectory points
}

TEST_CASE("Simulate method for ellipse billiard") {
    bt::Biliardo billiard(bt::BiliardoType::ellipse);
    billiard.l(5.0);
    billiard.r1(2.0);
    billiard.r2(3.0);

    std::vector<Point> trajectory = billiard.simulate(start_point, direction);
    // Add assertions to check the trajectory points
}

TEST_CASE("Simulate method for hyperbola billiard") {
    bt::Biliardo billiard(bt::BiliardoType::hyperbola);
    billiard.l(5.0);
    billiard.r1(2.0);
    billiard.r2(3.0);

    std::vector<Point> trajectory = billiard.simulate(start_point, direction);
    // Add assertions to check the trajectory points
}
```

I need to define the `Point` struct or whatever structure is used to represent points in the code. Assuming it's a
simple struct with x and y coordinates, I can proceed accordingly.

Additionally, there are methods like `reflect` and `intersect` that are crucial for calculating the trajectory. I
should write tests for these helper methods to ensure they work correctly.

```cpp
TEST_CASE("Reflect method") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    Vector incident_vector(1, 0);
    Vector normal_vector(0, 1);
    Vector reflected = billiard.reflect(incident_vector, normal_vector);
    // Expected reflection for incident (1,0) and normal (0,1) should be (-1,0)
    REQUIRE(reflected.x == Approx(-1));
    REQUIRE(reflected.y == Approx(0));
}

TEST_CASE("Intersect method for circle") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    billiard.r1(2.0);
    Line line(start_point, direction);
    std::vector<Point> intersections = billiard.intersect(line);
    // Add assertions to check the intersection points
}
```

I need to make sure that the `intersect` method correctly finds the points where the line intersects with the
billiard boundary, depending on the type.

Furthermore, the `calculateTrajectory` method likely uses these helper methods to compute the full trajectory of a
particle bouncing inside the billiard. I need to test this method with various starting points and directions to
ensure it behaves as expected.

```cpp
TEST_CASE("Calculate trajectory for circle billiard") {
    bt::Biliardo billiard(bt::BiliardoType::circle);
    billiard.r1(2.0);
    Point start(1, 0);
    Vector direction(0, 1);
    std::vector<Point> trajectory = billiard.calculateTrajectory(start, direction, max_reflections);
    // Add assertions to check the trajectory points
}

TEST_CASE("Calculate trajectory for ellipse billiard") {
    bt::Biliardo billiard(bt::BiliardoType::ellipse);
    billiard.l(5.0);
    billiard.r1(2.0);
    billiard.r2(3.0);
    Point start(1, 1);
    Vector direction(1, 1);
    std::vector<Point> trajectory = billiard.calculateTrajectory(start, direction, max_reflections);
    // Add assertions to check the trajectory points
}

TEST_CASE("Calculate trajectory for hyperbola billiard") {
    bt::Biliardo billiard(bt::BiliardoType::hyperbola);
    billiard.l(5.0);
    billiard.r1(2.0);
    billiard.r2(3.0);
    Point start(1, 1);
    Vector direction(1, -1);
    std::vector<Point> trajectory = billiard.calculateTrajectory(start, direction, max_reflections);
    // Add assertions to check the trajectory points
}
```

Lastly, I should consider edge cases, such as starting points on the boundary, directions parallel to the
boundary, or cases where the particle does not intersect the boundary after reflection.

By covering these scenarios with appropriate test cases, I can ensure that the `Billiard` class functions
correctly for different types of billiards and various initial conditions.
<!--stackedit_data:
eyJoaXN0b3J5IjpbMjExNjg5MDYyMywtMTg4NTk4NzIyLC02ND
M2MjA0MDYsLTIxMDExNzM5MDAsOTIyMjAzMzU1LC01Nzc5NjQy
MywxMDE1NjYzMTQ5LDE3MTIzNjIyNywtMTY0MDkzMTExNl19
-->