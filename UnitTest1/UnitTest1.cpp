#include "pch.h"
#include "CppUnitTest.h"
#include "../man/tapeInterface.cpp"

#define fileName "hello.txt"
#define testText "123456789"
#define testTextSize 7

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static void fileGeneration(void) {
	std::ofstream _file(fileName, std::ios_base::out | std::ios_base::trunc);
	char a[] = testText;
	_file.write(a, sizeof(int8_t) * 50);
	_file.close();
}


namespace YadroTask
{
	TEST_CLASS(TapeTest)
	{
	public:

		TEST_METHOD(Test_TapeIfNotExist)
		{
			fileGeneration();
			char a[] = testText;

			remove(fileName);
			Tape mytape(testTextSize, fileName);
		}

		TEST_METHOD(Test_ReadTape_correctRead)
		{
			fileGeneration();
			char a[] = testText;

			Tape mytape(testTextSize, fileName);
			int8_t result = mytape.read();
			Assert::AreEqual((int8_t)a[0], result);
		}

		TEST_METHOD(Test_WriteTape_correctWrite)
		{
			fileGeneration();

			Tape mytape(testTextSize, fileName);
			mytape.write('a');
			int8_t result = mytape.read();
			Assert::AreEqual((int8_t)'a', result);
		}

		TEST_METHOD(Test_ShiftAndRead_curPos2)
		{
			fileGeneration();
			char a[] = testText;

			Tape mytape(testTextSize, fileName);
			std::streampos pos = mytape.shiftCur(2);
			Assert::AreEqual((int)pos, 2);

			int8_t result2 = mytape.read();
			Assert::AreEqual((int8_t)a[2], result2);
		}

		TEST_METHOD(Test_ShiftAndRead_curPosMunus1)
		{
			fileGeneration();
			char a[] = testText;

			Tape mytape(testTextSize, fileName);
			std::streampos pos = mytape.shiftCur(-1);
			Assert::AreEqual(0, (int)pos);

			int8_t result2 = mytape.read();
			Assert::AreEqual((int8_t)a[0], result2);
		}

		TEST_METHOD(Test_ShiftTape_counterMoveLeft)
		{
			fileGeneration();

			//Мне стыдно за такое оформление тестов
			Tape mytape(testTextSize, fileName);
			mytape.shiftCur(-1);
			Assert::AreEqual(0, (int)mytape.getShiftCounter());
			mytape.shiftCur(2);
			Assert::AreEqual(2, (int)mytape.getShiftCounter());
			mytape.shiftCur(-1);
			Assert::AreEqual(3, (int)mytape.getShiftCounter());
			mytape.shiftCur(-3);
			Assert::AreEqual(4, (int)mytape.getShiftCounter());
		}

		TEST_METHOD(Test_ShiftTape_counterMoveRight)
		{
			fileGeneration();

			Tape mytape(testTextSize, fileName);
			mytape.shiftCur(testTextSize - 5);
			Assert::AreEqual(testTextSize - 5, (int)mytape.getShiftCounter());
			mytape.shiftCur(5);
			Assert::AreEqual(testTextSize, (int)mytape.getShiftCounter());
			mytape.shiftCur(5);
			Assert::AreEqual(testTextSize, (int)mytape.getShiftCounter());
		}

		TEST_METHOD(Test_ReadTape_counter)
		{
			fileGeneration();
			char a[] = testText;

			Tape mytape(testTextSize, fileName);
			mytape.read();
			uint32_t res = mytape.getReadCounter();
			Assert::AreEqual(1, (int)res);
			mytape.read();
			mytape.read();
			res = mytape.getReadCounter();
			Assert::AreEqual(3, (int)res);
		}

		TEST_METHOD(Test_WriteTape_counterNoDoubleEntry)
		{
			fileGeneration();
			char a[] = testText;

			Tape mytape(testTextSize, fileName);
			mytape.write(0x71);
			uint32_t res = mytape.getWriteCounter();
			Assert::AreEqual(1, (int)res);
			mytape.write(0x71);
			mytape.write(0x81);
			res = mytape.getWriteCounter();
			Assert::AreEqual(3, (int)res);
		}


		TEST_METHOD(Test_WriteTape_counterDoubleEntry)
		{
			/* Отличие от пред идущего только в том что не должна считаться
				попытка записать такое же значение */
			fileGeneration();
			char a[] = testText;

			Tape mytape(testTextSize, fileName);
			mytape.write(0x71);
			uint32_t res = mytape.getWriteCounter();
			Assert::AreEqual(1, (int)res);
			mytape.write(0x71);
			mytape.write(0x81);
			res = mytape.getWriteCounter();
			Assert::AreEqual(2, (int)res);
		}

	};
	TEST_CLASS(SortTest)
	{
	public:
		TEST_METHOD(My_test)
		{

		}
	};
}
