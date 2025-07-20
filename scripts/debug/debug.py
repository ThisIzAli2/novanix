"""
Author : Ali Mirmohammad

This file is a part of Novanix project
"""

import os
import argparse

class Cmd:
    @staticmethod
    def parse():
        parser = argparse.ArgumentParser(description="macro debugger")
        debug = parser.add_argument_group("Debugging")

        debug.add_argument("--macro-have",help="Check which files has macros.",required=False,action="store_true")
        args = parser.parse_args()
        return args


def extract_command():
    args = Cmd.parse()
    macro_have = args.macro_have

    return ( 
        macro_have
    )

def contains_macro(path):
    try:
        with open(path, 'r',encoding='utf-8',errors='ignore') as f:
            for line in f:
                if line.strip().startswith("#define"):
                    yield True
                else:
                    return False
    except Exception as exc:
        print(exc)

def main():
    args = Cmd.parse()
    macro_have = args.macro_have

    
    # Step 1: Change to parent directory
    os.chdir("..")
    os.chdir("..")
    print("Changed directory to:", os.getcwd())

    if macro_have:
    # Step 2: Walk through all files
        for root, dirs, files in os.walk("."):
            for file in files:
                if file.endswith((".h", ".hpp", ".c", ".cpp")):
                    full_path = os.path.join(root, file)
                    if contains_macro(full_path):
                        print(f"#define found in: {full_path}")


if __name__ == "__main__":
    main()