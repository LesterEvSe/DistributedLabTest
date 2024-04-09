#include <iostream>
#include <bitset>
#include "test.hpp"

// Using test from https://raw.githubusercontent.com/microsoft/rego-cpp/main/tests/bigint.yaml
std::string Test::detail::check(BigInt num1, BigInt num2, BigInt actual, char op, int test) {
    BigInt res;
    switch (op)
    {
        case '+': res = num1 + num2; break;
        case '-': res = num1 - num2; break;
        case '*': res = num1 * num2; break;
        case '/': res = num1 / num2; break;
        case '%': res = num1 % num2; break;
        case '^': res = num1.pow(num2); break;
    }


    std::cout << "Test" << test << "\n";
    std::cout << std::string(num1) << ' ' << op << ' ' << std::string(num2) <<
        " = " << std::string(res) << "\n";
    return (res == actual ? "true" : "false") + std::string("\n\n");
}

void Test::detail::add() {
    std::cout << "Add tests\n";
    BigInt num1, num2;

    num1 = BigInt(-2);
    num2 = BigInt(-15);
    std::cout << check(num1, num2, BigInt(-17), '+', 1);

    num1 = BigInt(-3796);
    num2 = BigInt(4047);
    std::cout << check(num1, num2, BigInt(251), '+', 2);

    num1 = BigInt(-253534);
    num2 = BigInt(-214311);
    std::cout << check(num1, num2, BigInt(-467845), '+', 3);

    num1 = BigInt("187224985");
    num2 = BigInt("235111630");
    std::cout << check(num1, num2, BigInt("422336615"), '+', 4);

    num1 = BigInt();
    num2 = BigInt(12124);
    std::cout << check(num1, num2, num2, '+', 5);

    num1 = BigInt("6466055601279126416241593829827225642974873054416615134420424370024610277048");
    num2 = BigInt("812377893613439962506223192889271172721150454313527119829598533028254192660");
    std::cout << check(num1, num2, BigInt("7278433494892566378747817022716496815696023508730142254250022903052864469708"), '+', 6);

    std::cout << std::endl;
}

void Test::detail::subtract() {
    std::cout << "Subtract tests\n";
    BigInt num1, num2;

    num1 = BigInt(-1);
    num2 = BigInt(11);
    std::cout << check(num1, num2, BigInt(-12), '-', 1);

    num1 = BigInt(2527);
    num2 = BigInt(-1226);
    std::cout << check(num1, num2, BigInt(3753), '-', 2);

    num1 = BigInt(-316587);
    num2 = BigInt(-767603);
    std::cout << check(num1, num2, BigInt(451016), '-', 3);

    num1 = BigInt("-5912796750055159349348285095168029999547805837934919256759875720338049163859");
    num2 = BigInt("2100436268304949465469152169050553499388589256398614019764087298232731952205");
    std::cout << check(num1, num2, BigInt("-8013233018360108814817437264218583498936395094333533276523963018570781116064"), '-', 4);

    num1 = BigInt("8796");
    num2 = BigInt("23");
    std::cout << check(num1, num2, BigInt("8773"), '-', 5);

    std::cout << std::endl;
}

void Test::detail::multiply() {
    std::cout << "Multiply Tests\n";
    BigInt num1, num2;

    num1 = BigInt(3942);
    num2 = BigInt(7390);
    std::cout << check(num1, num2, BigInt("29131380"), '*', 1);

    num1 = BigInt(2);
    num2 = BigInt(6);
    std::cout << check(num1, num2, BigInt(12), '*', 2);

    num1 = BigInt(-3125);
    num2 = BigInt(3702);
    std::cout <<  check(num1, num2, BigInt("-11568750"), '*', 3);

    num1 = BigInt("140316724549002105");
    num2 = BigInt("573252767549507142");
    std::cout << check(num1, num2, BigInt("80436950681197326061797920670533910"), '*', 4);

    num1 = BigInt("-5786314899744711870314487313338784069375375316866554430539107712879654609997");
    num2 = BigInt("-3029613346087335900692057905494693632329204701910191321772183583923555603055");
    BigInt res("17530296844930584098686471133123526535894636896209113668872569260041333924699635889877017262804525726346271216292420744804783913117122283226890166740835");
    std::cout << check(num1, num2, res, '*', 5);

    num1 = BigInt("20000");
    num2 = BigInt("45000");
    std::cout << check(num1, num2, BigInt("900000000"), '*', 6);

    num1 = BigInt();
    num2 = BigInt("8872569260041333924699635889877017262804525726346271216292420744804783913117122283226");
    std::cout << check(num1, num2, BigInt("0"), '*', 7);

    std::cout << std::endl;
}

void Test::detail::division() {
    std::cout << "Division Tests\n";
    BigInt num1, num2;

    num1 = BigInt(12);
    num2 = BigInt(1);
    std::cout << check(num1, num2, BigInt(12), '/', 1);

    num1 = BigInt(-524);
    num2 = BigInt(-56);
    std::cout << check(num1, num2, BigInt(9), '/', 2);

    num1 = BigInt(978567);
    num2 = BigInt(-734);
    std::cout << check(num1, num2, BigInt(-1333), '/', 3);

    num1 = BigInt("1725644784760724795304475");
    num2 = BigInt("2767901553815");
    std::cout << check(num1, num2, BigInt("623448757555"), '/', 4);

    num1 = BigInt("235328967186965560636092487672274298032698178001584420387677709515603751810");
    num2 = BigInt("61042697860145807716747171190736990291");
    std::cout << check(num1, num2, BigInt("3855153448920703543655522463019737887"), '/', 5);

    num1 = BigInt("1234125123");
    num2 = BigInt("2366515463");
    std::cout << check(num1, num2, BigInt(0), '/', 6);

    std::cout << std::endl;
}
void Test::detail::division_with_remainder() {
    std::cout << "Division with remainder tests\n";
    BigInt num1, num2;

    num1 = BigInt(23512);
    num2 = BigInt(321662);
    std::cout << check(num1, num2, num1, '%', 1);

    num1 = BigInt(424268);
    num2 = BigInt(-358);
    std::cout << check(num1, num2, BigInt(38), '%', 2);

    num1 = BigInt("-165552611");
    num2 = BigInt("-15653");
    std::cout << check(num1, num2, BigInt(-6483), '%', 3);

    num1 = BigInt("-1030904679897134708160285970453473199806033360699641489201333428182197161893");
    num2 = BigInt("45845269018283096547057010054707163542");
    std::cout << check(num1, num2, BigInt("-41806999527922083709215100619759029989"), '%', 4);

    std::cout << std::endl;
}

void Test::detail::binary_conversion() {
    std::cout << "Binary conversion\n";
    BigInt num;

    num = BigInt("140316724549002105");

    std::bitset<64> plus(140316724549002105);
    std::bitset<64> minus(-140316724549002105);

    std::cout << "Test1\n";
    std::cout << "num: " << std::string(num) << "\n";
    std::cout << "BigInt:       " << num.binary() << "\n";
    std::cout << "bitset: " << plus << "\n\n";

    num = BigInt("-140316724549002105");
    std::cout << "Test2\n";

    std::cout << "num: " << std::string(num) << "\n";
    std::cout << "BigInt:       " << num.binary() << "\n";
    std::cout << "bitset: " << minus << "\n\n";

    num = BigInt("10346798971347081602859704534736033360699641489201333421893");
    std::cout << "Test3\n";

    std::cout << "num: " << std::string(num) << "\n";
    std::cout << "BigInt:   " << num.binary() << "\n";
    std::cout << "Web-Site: 01101001011111100110011111001001110010110101001000011001011000110011100001111011000101001001011001001110110001101011101011011110000000111111111001001001010110000100000100110001100100011101000101" << "\n";

    std::cout << "\n\n";
}
void Test::detail::int_conversion() {
    std::cout << "Int conversion\n";

    std::cout << "number: " << (long long)140316724549002105 << std::endl;
    std::cout << "int:         " << (int)140316724549002105 << "\n";
    std::cout << "From BigInt: " << (int)BigInt("140316724549002105") << "\n\n";

    std::cout << "number: " << (long long)-1403167245002105 << std::endl;
    std::cout << "int:         " << (int)-1403167245002105 << "\n";
    std::cout << "From BigInt: " << (int)BigInt("-1403167245002105") << "\n\n";
}
void Test::detail::pow() {
    // using python ** for testing
    std::cout << "Pow Tests\n";
    BigInt num, degree, res;

    num = BigInt(2);
    degree = BigInt(20);
    std::cout << check(num, degree, BigInt(1048576), '^', 1);

    num = BigInt(13);
    degree = BigInt(138);
    res = BigInt("5298862111705984468986826004208960681542272238274522316228155317510506921316368923561909729710342452590041368532447502426123793365390569569956006999824329");
    std::cout << check(num, degree, res, '^', 2);

    num = BigInt(1);
    degree = BigInt("6815422722382745223162281553175105069213163");
    std::cout << check(num, degree, num, '^', 3);

    num = BigInt("88621117059844689868260042");
    degree = BigInt(0);
    std::cout << check(num, degree, BigInt(1), '^', 4);

    num = BigInt("19097297103424525900413685324475024261237933653905695699560");
    degree = BigInt("-892356190972971034245259004136853");
    std::cout << check(num, degree, BigInt(0), '^', 5);

    num = BigInt("227223827452231622815531");
    degree = BigInt("1");
    std::cout << check(num, degree, BigInt("227223827452231622815531"), '^', 6);

    num = BigInt(-131);
    degree = BigInt(34);
    res = BigInt("971010782003735157367948228694272300966014258337791091007277131562493321");
    std::cout << check(num, degree, res, '^', 7);

    num = BigInt(-32);
    degree = BigInt(378);
    res = BigInt("88448771443952937988070644155037561422858825544533428496495779911601139499522777157934184566439227216106791839364897366036734335634912102738537861483096452501590794500366037505070655509492154554330380012187428569493313327601290644792165407831275752714974250153462485472760588879376768193944545983701113594651492775803125944164632554194156221540393238651200515281509096320752698232834711818187909914434986938220058194138506237353577333336102788317629403447047617577968414072793190825064536181674655498943658601158166803883275870027173333526136193657844232347425622196224");
    std::cout << check(num, degree, res, '^', 8);

    // Perfomance tests
    /*
    num = BigInt(235);
    degree = BigInt(523'425);
    */
    // num.pow(degree); // Too long for Karatsuba, but not for FFT!

    std::cout << std::endl;
}


void Test::detail::print(const std::vector<long long> &nums, const std::string &name) {
    std::cout << name;
    for (long long num : nums)
        std::cout << num << ' ';
    std::cout << std::endl;
}

void Test::detail::fft() {
    std::cout << "FFT tests\n";
    std::vector<long long> a = std::vector<long long> {3, 9, 4, 2};
    std::vector<long long> b = std::vector<long long> {7, 3, 9, 0};
    std::vector<long long> c = FFT::multiply(a, b);

    print(a, "pol1: ");
    print(b, "pol2: ");
    print(c, "res:  ");

    std::cout << std::endl;
}


void Test::start() {
    detail::add();
    detail::subtract();
    detail::fft();
    detail::multiply();
    detail::division();
    detail::division_with_remainder();
    detail::binary_conversion();
    detail::int_conversion();
    detail::pow();
}