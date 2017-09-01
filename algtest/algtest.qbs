import qbs
CppApplication {
    consoleApplication: true
    files: [
        "01beibao.hh",
        "01beibao_new.hh",
        "1004.hh",
        "1005.hh",
        "1358.hh",
        "1402.hh",
        "1402_c.hh",
        "1402_mix.hh",
        "1402_new.hh",
        "1402_remix.hh",
        "1402_test.hh",
        "1402_w.hh",
        "1711.hh",
        "1711_other.hh",
        "2025.hh",
        "2089.hh",
        "2089_dp.hh",
        "2203.hh",
        "MyTimer_linux.h",
        "MyTimer_win.h",
        "bignum.hh",
        "common.h",
        "dp1.h",
        "dp2.h",
        "heap.hh",
        "imagezip.h",
        "joseph.h",
        "joseph_my.h",
        "kmp.hh",
        "lanqiao10.hh",
        "main.cpp",
        "my01beibao.hh",
        "proptest.hh",
        "stltest.hh",
        "t_1004.hh",
        "t_1022.hh",
        "t_1234.hh",
        "t_1242.hh",
        "t_1242_error.hh",
        "t_1242_error2.hh",
        "vjc_1.hh",
        "vjc_2.hh",
        "vjc_3.hh",
        "vjc_e.hh",
        "vjc_f.hh",
    ]
    cpp.cxxLanguageVersion: "c++11"
    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
