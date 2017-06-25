/*
 * @author: MasterJEET
 * @email : masterjeet9@gmail.com
 * @date  : 25th Jun 2017
 *
 * */

#ifndef TESTCOMMON_H
#define TESTCOMMON_H

template <typename T>
::testing::AssertionResult checkPrint(const char* print_expr, const char* T_expr, const std::string print, const T& type){
    std::stringstream ss;
    ss << type;

    if( print.compare(ss.str()) == 0 )
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << "Expected \"" << T_expr << "\" : " << print_expr << "\n"
                                             << "Actual   \"" << T_expr << "\" : \"" << type << "\"";
}

#endif
