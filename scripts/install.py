import os
import sys
import subprocess


def main():
    subprocess.run(["make", "clean"], check=False)

    subprocess.run(["make", "install"], check=True)