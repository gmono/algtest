import qbs
CppApplication {
    consoleApplication: true
    files: [
        "1402.hh",
        "1402_new.hh",
        "1402_test.hh",
        "MyTimer_linux.h",
        "MyTimer_win.h",
        "bignum.hh",
        "common.h",
        "dp1.h",
        "dp2.h",
        "heap.hh",
        "imagezip.h",
        "lanqiao10.hh",
        "main.cpp",
        "t_1004.hh",
        "t_1022.hh",
        "t_1234.hh",
        "t_1242.hh",
        "t_1242_error.hh",
        "t_1242_error2.hh",
    ]
    cpp.cxxLanguageVersion: "c++11"
    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
