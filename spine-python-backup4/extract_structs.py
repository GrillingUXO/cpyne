import os
import re

def extract_structs_from_file(filepath):
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    # Match from "typedef struct <name>" to "};"
    struct_pattern = re.compile(
        r'(typedef\s+struct\s+(?:\w+)?\s*\{[^{}]*?(?:\{[^{}]*?\}[^{}]*?)*\}\s*\w*;)',
        re.DOTALL | re.MULTILINE
    )

    matches = struct_pattern.findall(content)
    return matches

def extract_structs_from_directory(directory):
    all_structs = []
    for root, _, files in os.walk(directory):
        for filename in files:
            if filename.endswith('.h'):
                path = os.path.join(root, filename)
                structs = extract_structs_from_file(path)
                if structs:
                    all_structs.append((path, structs))
    return all_structs

def main():
    header_dir = "/Users/michelleyan/Downloads/sp/spine-python/src/spine-c/include/spine"  # Change this to your actual include path
    output_file = "/Users/michelleyan/Downloads/sp/spine-python/extracted_structs.h"

    all_structs = extract_structs_from_directory(header_dir)

    with open(output_file, 'w', encoding='utf-8') as out:
        for path, structs in all_structs:
            out.write(f"// From {path}\n")
            for struct in structs:
                out.write(struct.strip() + '\n\n')

    print(f"Extracted {sum(len(s) for _, s in all_structs)} structs to {output_file}")

if __name__ == "__main__":
    main()
