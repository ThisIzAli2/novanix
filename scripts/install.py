import os
import sys
import subprocess


def main():
    subprocess.run(["cd",".."],check=True)
    subprocess.run(["cd","libcx"],check=True)
    subprocess.run(["make", "clean"], check=False)

    subprocess.run(["make", "install"], check=True)


if __name__ == "__main__":
    main()