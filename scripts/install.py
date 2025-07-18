import os
import sys
import subprocess


def getdir():
    retVal = os.getcwd()
    return retVal

def main():
    dr = getdir()
    print(dr)
    os.chdir("..")
    subprocess.run(["cd","libcx"],check=True)
    subprocess.run(["make", "clean"], check=False)

    os.system("make install")
    # subprocess.run(["make", "install"], capture_output=True,text=True)


if __name__ == "__main__":
    main()