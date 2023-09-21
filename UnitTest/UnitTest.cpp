#include "CppUnitTest.h"
#include "FCPosition.h"
#include <Resource.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestCheckCoordinateBoundry)
		{
			FCPosition pos;

			// Test within bounds
			Assert::IsTrue(pos.checkCoordinateBoundry(Coordinate(0, 0)));
			Assert::IsTrue(pos.checkCoordinateBoundry(Coordinate(GRID_SIZE - 1, GRID_SIZE - 1)));

			// Test out of bounds
			Assert::IsFalse(pos.checkCoordinateBoundry(Coordinate(GRID_SIZE, 0)));
			Assert::IsFalse(pos.checkCoordinateBoundry(Coordinate(0, GRID_SIZE)));
		}

      
        TEST_METHOD(TestFaceLeft)
        {
            FCPosition pos(0, 0, ID_FACING_NORTH);
            pos.faceLeft();
            Assert::IsTrue(pos.facing == Coordinate(-1, 0));

            pos.faceLeft();
            Assert::IsTrue(pos.facing == Coordinate(0, -1));

            // ... Continue for other directions
        }

        TEST_METHOD(TestFaceRight)
        {
            FCPosition pos(0, 0, ID_FACING_NORTH);
            pos.faceRight();
            Assert::IsTrue(pos.facing == Coordinate(1, 0));

            pos.faceRight();
            Assert::IsTrue(pos.facing == Coordinate(0, -1));
        }

        TEST_METHOD(TestMove)
        {
            FCPosition pos(0, 0, ID_FACING_EAST);
            Assert::IsTrue(pos.move());
            Assert::IsTrue(pos.coordinate == Coordinate(1, 0));

            pos.faceRight();
            //Move out of boundary
            Assert::IsFalse(pos.move());

            // ... Test for boundary conditions
            pos = FCPosition(GRID_SIZE - 1, GRID_SIZE - 1, ID_FACING_EAST);
            Assert::IsFalse(pos.move());  // Should not be able to move out of bounds
        }


	};
}
