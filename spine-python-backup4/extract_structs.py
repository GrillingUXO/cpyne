import os
import re

def remove_comments_and_cpp_blocks(content):
    """移除C/C++注释和C++条件编译块"""
    # 移除块注释
    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
    # 移除行注释
    content = re.sub(r'//.*?$', '', content, flags=re.MULTILINE)
    # 移除C++条件编译块
    content = re.sub(r'#ifdef\s+__cplusplus.*?#endif', '', content, flags=re.DOTALL)
    return content

def extract_array_macros(content):
    """提取并转换SP_ARRAY_DECL宏定义的结构体"""
    pattern = re.compile(
        r'SP_ARRAY_DECL\s*\(\s*([\w\s*]+)\s*,\s*(\w+)\s*\)',
        re.DOTALL
    )
    structs = []
    for match in pattern.finditer(content):
        item_type = match.group(1).strip()
        struct_name = match.group(2).strip()
        struct_def = (
            f"typedef struct {struct_name} {{\n"
            f"    int size;\n"
            f"    int capacity;\n"
            f"    {item_type}* items;\n"
            f"}} {struct_name};"
        )
        structs.append(struct_def)
    return structs

def extract_structs_with_state_machine(content):
    """使用状态机提取结构体定义（支持嵌套花括号）"""
    structs = []
    index = 0
    len_content = len(content)
    
    while index < len_content:
        # 查找"typedef struct"起始位置
        start = content.find("typedef struct", index)
        if start == -1:
            break
            
        # 初始化状态机
        stack = 0
        pos = start
        in_struct = False
        current = ""
        
        # 遍历字符直到结构体结束
        while pos < len_content:
            c = content[pos]
            current += c
            
            # 处理花括号嵌套
            if c == '{':
                stack += 1
                in_struct = True
            elif c == '}':
                stack -= 1
                if stack < 0:  # 错误情况
                    stack = 0
                    
            # 检测结构体结束
            if in_struct and stack == 0 and c == ';':
                structs.append(current)
                index = pos + 1
                break
                
            pos += 1
        else:
            index = start + len("typedef struct")
            
    return structs

def extract_structs_from_file(filepath):
    """从单个文件中提取所有结构体定义"""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # 预处理内容
    clean_content = remove_comments_and_cpp_blocks(content)
    
    # 提取标准结构体
    structs = extract_structs_with_state_machine(clean_content)
    
    # 提取宏定义的结构体
    array_structs = extract_array_macros(clean_content)
    
    # 合并结果
    return structs + array_structs

def extract_structs_from_directory(directory):
    """从目录中递归提取所有结构体"""
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
    header_dir = "/Users/michelleyan/Downloads/sp/spine-python/src/spine-c/include/spine"
    output_file = "/Users/michelleyan/Downloads/sp/spine-python/extracted_structs.h"
    
    all_structs = extract_structs_from_directory(header_dir)
    
    with open(output_file, 'w', encoding='utf-8') as out:
        # 添加文件头说明
        out.write("/* 提取的结构体定义 - 包含嵌套结构体和宏生成结构体 */\n\n")
        
        for path, structs in all_structs:
            out.write(f"/* From {path} */\n")
            for struct in structs:
                # 格式化输出
                formatted = struct.strip()
                if not formatted.endswith(';'):
                    formatted += ';'
                out.write(formatted + '\n\n')
    
    total = sum(len(s) for _, s in all_structs)
    print(f"成功提取 {total} 个结构体到 {output_file}")

if __name__ == "__main__":
    main()
