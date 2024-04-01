#include <iostream>
#include "BigInt.hpp"
#include "fft.hpp"

// Using test from https://raw.githubusercontent.com/microsoft/rego-cpp/main/tests/bigint.yaml
std::string check(BigInt actual, BigInt expected) {
    return std::string(actual == expected ? "true" : "false") + "\n";
}

void plus_and_minus_tests() {
    std::cout << "Tests of addition and subtraction\n";
    BigInt num1, num2;

    num1 = BigInt(-2);
    num2 = BigInt(-15);
    std::cout << "Test1: " << check(num1 + num2, BigInt(-17));

    num1 = BigInt(-3796);
    num2 = BigInt(4047);
    std::cout << "Test2: " << check(num1 + num2, BigInt(251));

    num1 = BigInt(-253534);
    num2 = BigInt(-214311);
    std::cout << "Test3: " << check(num1 + num2, BigInt(-467845));

    num1 = BigInt("187224985");
    num2 = BigInt("235111630");
    std::cout << "Test4: " << check(num1 + num2, BigInt("422336615"));

    num1 = BigInt();
    num2 = BigInt(12124);
    std::cout << "Test5: " << check(num1 + num2, num2);

    num1 = BigInt("6466055601279126416241593829827225642974873054416615134420424370024610277048");
    num2 = BigInt("812377893613439962506223192889271172721150454313527119829598533028254192660");
    std::cout << "Test6: " << check(num1 + num2, BigInt("7278433494892566378747817022716496815696023508730142254250022903052864469708"));

    // subtract Test
    num1 = BigInt(-1);
    num2 = BigInt(11);
    std::cout << "Test7: " << check(num1 - num2, BigInt(-12));

    num1 = BigInt(2527);
    num2 = BigInt(-1226);
    std::cout << "Test8: " << check(num1 - num2, BigInt(3753));

    num1 = BigInt(-316587);
    num2 = BigInt(-767603);
    std::cout << "Test9: " << check(num1 - num2, BigInt(451016));

    num1 = BigInt("-5912796750055159349348285095168029999547805837934919256759875720338049163859");
    num2 = BigInt("2100436268304949465469152169050553499388589256398614019764087298232731952205");
    std::cout << "Test10: " << check(num1 - num2, BigInt("-8013233018360108814817437264218583498936395094333533276523963018570781116064"));

    num1 = BigInt("8796");
    num2 = BigInt("23");
    std::cout << "Test11: " << check(num1 - num2, BigInt("8773"));

    std::cout << std::endl;
}

void multiply_tests() {
    BigInt num1, num2;
    num1 = BigInt(3942);
    num2 = BigInt(7390);
    std::cout << "Test1: " << check(num1 * num2, BigInt("29131380"));

    num1 = BigInt(2);
    num2 = BigInt(6);
    std::cout << "Test2: " << check(num1 * num2, BigInt(12));

    num1 = BigInt(-3125);
    num2 = BigInt(3702);
    std::cout << "Test3: " << check(num1 * num2, BigInt("-11568750"));

    num1 = BigInt("140316724549002105");
    num2 = BigInt("573252767549507142");
    std::cout << "Test4: " << check(num1 * num2, BigInt("80436950681197326061797920670533910"));

    num1 = BigInt("-5786314899744711870314487313338784069375375316866554430539107712879654609997");
    num2 = BigInt("-3029613346087335900692057905494693632329204701910191321772183583923555603055");
    BigInt res("17530296844930584098686471133123526535894636896209113668872569260041333924699635889877017262804525726346271216292420744804783913117122283226890166740835");
    std::cout << "Test5: " << check(num1 * num2, res);

    std::cout << std::endl;
}

void division_tests() {
    BigInt num1, num2;
    num1 = BigInt("235328967186965560636092487672274298032698178001584420387677709515603751810");
    num2 = BigInt("61042697860145807716747171190736990291");
    std::cout << "Test5: " << check(num1 / num2, BigInt("3855153448920703543655522463019737887"));

    std::cout << std::endl;
}

void fft_tests() {
    std::vector<int> a = std::vector<int> {3, 9, 4, 2};
    std::vector<int> b = std::vector<int> {7, 3, 9, 0};
    std::vector<int> c = FFT::multiply(a, b);

    for (int num : c)
        std::cout << num << ' ';
}

int main() {
    plus_and_minus_tests();
    multiply_tests();
    division_tests();
    
    return 0;
}