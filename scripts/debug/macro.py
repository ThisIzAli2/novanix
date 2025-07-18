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