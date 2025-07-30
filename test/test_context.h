#ifdef UNIT_TEST

namespace ArduinoContextTest
{
    void test_single_instance(void)
    {
        ArduinoFakeContext* context1 = getArduinoFakeContext();
        ArduinoFakeContext* context2 = getArduinoFakeContext();

        TEST_ASSERT_NOT_NULL(context1);
        TEST_ASSERT_NOT_NULL(context2);

        TEST_ASSERT_EQUAL(context1, context2);
    }

    void test_reset(void)
    {
        ArduinoFakeContext* context = getArduinoFakeContext();
        ArduinoFakeInstances* instances = context->Instances;

        // Broke pointers for testing purposes
        context->Instances->Serial = nullptr;
        context->Instances->SPI = nullptr;

        TEST_ASSERT_NULL(context->Instances->Serial);
        TEST_ASSERT_NULL(context->Instances->SPI);

        ArduinoFakeReset();

        // After reset, a new instance of ArduinoFakeInstances should be created
        // and the previous instance should be deleted.
        // The Serial and SPI instances should also be reset to nullptr.
        TEST_ASSERT_NOT_NULL(context->Instances);
        TEST_ASSERT_NOT_NULL(context->Instances->Serial);
        TEST_ASSERT_NOT_NULL(context->Instances->SPI);

        // A simple pointer comparison like TEST_ASSERT_NOT_EQUAL(context->Instances, instances); 
        // is not a reliable way to check if a new instance was created, because 
        // memory allocators can reuse the same address for new objects after deletion. 
        // This means a new instance could be created at the same memory location as the old one, 
        // causing the test to fail even though the instance is actually new. 
        // To properly verify a new instance, you should check object identity or state, not just pointer values.
    }

    void test_function_mock(void)
    {
        Mock<FunctionFake>* m1 = &ArduinoFake(Function);
        Mock<FunctionFake>* m2 = &ArduinoFake(Function);
        Mock<FunctionFake>* m3 = &ArduinoFake();

        TEST_ASSERT_NOT_NULL(m1);
        TEST_ASSERT_NOT_NULL(m2);
        TEST_ASSERT_NOT_NULL(m3);

        TEST_ASSERT_EQUAL(m1, m2);
        TEST_ASSERT_EQUAL(m1, m3);

        FunctionFake* i1 = ArduinoFakeInstance(Function);
        FunctionFake* i2 = ArduinoFakeInstance(Function);

        TEST_ASSERT_NOT_NULL(i1);
        TEST_ASSERT_NOT_NULL(i2);
        TEST_ASSERT_EQUAL(i1, i2);
    }

    void test_print_mock(void)
    {
        Mock<PrintFake>* m1 = &ArduinoFake(Print);
        Mock<PrintFake>* m2 = &ArduinoFake(Print);

        TEST_ASSERT_NOT_NULL(m1);
        TEST_ASSERT_NOT_NULL(m2);
        TEST_ASSERT_EQUAL(m1, m2);

        PrintFake* i1 = ArduinoFakeInstance(Print);
        PrintFake* i2 = ArduinoFakeInstance(Print);

        TEST_ASSERT_NOT_NULL(i1);
        TEST_ASSERT_NOT_NULL(i2);
        TEST_ASSERT_EQUAL(i1, i2);
    }

    void test_stream_mock(void)
    {
        Mock<StreamFake>* m1 = &ArduinoFake(Stream);
        Mock<StreamFake>* m2 = &ArduinoFake(Stream);

        TEST_ASSERT_NOT_NULL(m1);
        TEST_ASSERT_NOT_NULL(m2);
        TEST_ASSERT_EQUAL(m1, m2);

        StreamFake* i1 = ArduinoFakeInstance(Stream);
        StreamFake* i2 = ArduinoFakeInstance(Stream);

        TEST_ASSERT_NOT_NULL(i1);
        TEST_ASSERT_NOT_NULL(i2);
        TEST_ASSERT_EQUAL(i1, i2);
    }

    void test_serial_mock(void)
    {
        Mock<SerialFake>* m1 = &ArduinoFake(Serial);
        Mock<SerialFake>* m2 = &ArduinoFake(Serial);

        TEST_ASSERT_NOT_NULL(m1);
        TEST_ASSERT_NOT_NULL(m2);
        TEST_ASSERT_EQUAL(m1, m2);

        SerialFake* i1 = ArduinoFakeInstance(Serial);
        SerialFake* i2 = ArduinoFakeInstance(Serial);

        TEST_ASSERT_NOT_NULL(i1);
        TEST_ASSERT_NOT_NULL(i2);
        TEST_ASSERT_EQUAL(i1, i2);
    }

    void test_unknown_instance_exception(void)
    {
        fakeit::Mock<Serial_> fake;

        try {
            ArduinoFakeInstance(Print, &fake.get());
        } catch (const std::runtime_error& e) {
            TEST_ASSERT_EQUAL_STRING("Unknown instance", e.what());
        }
    }

    void test_getter_overload_with_proxy(void)
    {
        Serial_* serial = ArduinoFakeMock(Serial);
        PrintFake* fake = ArduinoFakeInstance(Stream, serial);

        TEST_ASSERT_EQUAL(getArduinoFakeContext()->Serial(), fake);
    }

    void test_getter_overload_with_mapping(void)
    {
        Serial_* serial = &::Serial;
        PrintFake* fake = ArduinoFakeInstance(Stream, serial);

        TEST_ASSERT_EQUAL(getArduinoFakeContext()->Serial(), fake);
    }

    void run_tests(void)
    {
        RUN_TEST(ArduinoContextTest::test_single_instance);
        RUN_TEST(ArduinoContextTest::test_reset);
        RUN_TEST(ArduinoContextTest::test_function_mock);
        RUN_TEST(ArduinoContextTest::test_print_mock);
        RUN_TEST(ArduinoContextTest::test_stream_mock);
        RUN_TEST(ArduinoContextTest::test_serial_mock);
        RUN_TEST(ArduinoContextTest::test_getter_overload_with_proxy);
        RUN_TEST(ArduinoContextTest::test_getter_overload_with_mapping);
        RUN_TEST(ArduinoContextTest::test_unknown_instance_exception);
    }
}

#endif
