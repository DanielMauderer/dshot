//
// Created by Daniel on 30.11.2020.
//

#include "gmock/gmock.h"
#include "../dshot/include/dshot.h"
#include "../dshot/include/dshot_value.h"


using namespace testing;

namespace testCMake::tests
{
    TEST(DShotFlowTest, CompleteFlow) {
        dshot_client client;
        client.initialize(DSHOT1200);
        client.start();
        client.update({0,0,0,0});
        client.update({0,0,0,0});
    }

    TEST(DShotFlowTest, MissingInitialize) {
        dshot_client client;
          
        try {
            client.start();
            FAIL() << "Expected dhsot not triggered";
        }
        catch(const dshot_flow_exception& err) {
            EXPECT_EQ(err.get_message(), std::string("dhsot not initialized"));
        }
        catch(...) {
            FAIL() << "Expected dhsot wrong exception";
        }
    }
    
    TEST(DShotFlowTest, MissingStart) {
        dshot_client client;
        client.initialize(DSHOT1200);

        try {
            client.update({0,0,0,0});
            FAIL() << "Expected dhsot not triggered";
        }
        catch(dshot_flow_exception const & err) {
            EXPECT_EQ(err.get_message(),std::string("dhsot not started"));
        }
        catch(...) {
            FAIL() << "Expected dhsot wrong exception";
        }
    }

    TEST(DShotFlowTest, AlreadyInitialized) {
        dshot_client client;
        client.initialize(DSHOT1200);
        client.start();
        client.update({0,0,0,0});
        try {
            client.initialize(DSHOT1200);
            FAIL() << "Expected dhsot not triggered";
        }
        catch(dshot_flow_exception const & err) {
            EXPECT_EQ(err.get_message(),std::string("dhsot already initialized"));
        }
        catch(...) {
            FAIL() << "Expected dhsot wrong exception";
        }
    }

    TEST(DshotValueTest, NoThrottle) {
        dshot_value t1(0, false); //0000 0110 0000 0110
        EXPECT_EQ(t1.getPackage(), 0b0000011000000110);

        dshot_value t2(0, true); //0000 0111 0000 0111
        EXPECT_EQ(t2.getPackage(), 0b0000011000010111);
    }

    TEST(DshotValueTest, HalfThrottle) {
        dshot_value t1(0.5, false); //1000 0010 1110 0100
        EXPECT_EQ(t1.getPackage(), 0b1000001100001011);

        dshot_value t2(0.5, true); //1000 0010 1111 0101
        EXPECT_EQ(t2.getPackage(), 0b1000001100011010);
    }

    TEST(DshotValueTest, FullThrottle) {
        dshot_value t1(1, false); //1111 1111 1110 1110
        EXPECT_EQ(t1.getPackage(), 0b1111111111101110);

        dshot_value t2(1, true); //1111 1111 1111 1111
        EXPECT_EQ(t2.getPackage(), 0b1111111111111111);
    }

    TEST(DshotValueTest, BitWiseReturn) {
        bool bits[] = {1,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1};
        dshot_value t1(0.5, false); //1000 0010 1110 0100
        for (size_t i = 0; i < 16; i++)
        {
            EXPECT_EQ(t1.nextBit(), bits[i]);
        }
        
        for (size_t i = 0; i < 16; i++)
        {
            EXPECT_EQ(t1.nextBit(), bits[i]);
        }
    }

    TEST(DshotValueTest, BitWiseUpdateReturn) {
        bool bits1[] = {1,0,0,0,0,0,1,1,0,0,0,0,1,0,1,1};
        bool bits2[] = {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0};

        dshot_value t1(0.5, false);
        for (size_t i = 0; i < 16; i++)
        {
            EXPECT_EQ(t1.nextBit(), bits1[i]);
            if (i == 10)
            {
                t1.updateValue(1, false);
            }
            
        }
        
        for (size_t i = 0; i < 16; i++)
        {
            EXPECT_EQ(t1.nextBit(), bits2[i]);
        }
    }
    
    int main(int argc, char **argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}