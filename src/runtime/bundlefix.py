#!/usr/bin/python3

import os
import sys

def main(args: list[str]):
    if len(args) == 0:
        exit(1)

    with open('wow.txt', 'w+') as f:
        f.writelines("FUCK")
    
    print(f"Args: {args}")

if __name__ == "__main__":
    main(sys.argv[1:])
