import sys
import os
import subprocess

def run(test_command):
     result = subprocess.run(test_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
     if "FAILED" in result.stdout or "FAILED" in result.stderr: 
         return 0
     else:
         return 1

res = 0
test_command=['python', 'distributed/test_c10d_ops_xccl.py']
res += run(test_command)
test_command=['python', 'distributed/test_c10d_xccl.py']
res += run(test_command)

exit_code = os.WEXITSTATUS(res)
sys.exit(exit_code)

