"""
Author : Ali Mirmohammad

This file is a part of Novanix project
"""

import os

def contains(path):
    try:
        with open(path, 'r',encoding='utf-8',errors='ignore') as f:
            for line in f:
                if line.strip().startswith("#define"):
                    return True
                else:
                    return False
    except Exception as exc:
        print(exc)

def main():
    # Step 1: Change to parent directory
    os.chdir("..")
    os.chdir("..")
    print("Changed directory to:", os.getcwd())

    # Step 2: Walk through all files
    for root, dirs, files in os.walk("."):
        for file in files:
            if file.endswith((".h", ".hpp", ".c", ".cpp")):
                full_path = os.path.join(root, file)
                if contains(full_path):
                    print(f"#define found in: {full_path}")


if __name__ == "__main__":
    main()