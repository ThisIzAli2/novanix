import os
import sys

def getdir():
    return os.getcwd()

def main():
    # Go up one directory
    os.chdir("..")
    
    # Now change into libcx
    os.chdir("libcx")

    # Run 'make clean'
    os.system("make clean")

    # Run 'make install'
    os.system("make install")

if __name__ == "__main__":
    main()
