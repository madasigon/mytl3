from autotest import Codeforces, run_test
import instance.config as config
import instance.secret as secret


cf = Codeforces(*secret.credentials)

print(run_test(cf, config.LIBRARY_PATH, config.SRC_PATH, config.DST_PATH))