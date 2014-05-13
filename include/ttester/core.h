#pragma once

#define stringify(_s) #_s
#define expect_true(_x) { if ((_x) == false) throw tsuite_exception(strobj() << "expect_true(" << stringify(_x) << ") on " << __FILE__ << ":" << __LINE__); }