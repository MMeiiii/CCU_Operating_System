#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main (){

	char str[1];
	long len = 1;     // 因為是64位元，所以宣告long
	long ret;         // 因為是64位元，所以宣告long
	
  //sys_read
	__asm__ volatile(
		"mov $0, %%rax\n"   // sys_read是第0號服務，所以把0存到rax暫存器
		"mov $0, %%rdi\n"   // fd(file descriptor檔案描述器) stdin(0), stdout(1), stderr(2) --> 因為是讀入所以是0
		"mov %1, %%rsi\n"   // buffer
		"mov %2, %%rdx\n"   // buffer size
		"syscall\n"
		"mov %%rax, %0"     //system call 回傳值放rax
		: "=m"(ret)
		: "g"(str), "g"(len)
		:"rax", "rbx", "rcx", "rdx");
	
  // sys_write
	__asm__ volatile(
		"mov $1, %%rax\n"
		"mov $2, %%rdi\n"
		"mov %1, %%rsi\n"
		"mov %2, %%rdx\n"
		"syscall\n"
		"mov %%rax, %0"
		: "=m"(ret)
		: "g"(str), "g"(len)
		:"rax", "rbx", "rcx", "rdx");
	
	printf("\n讀入的字元為\"%s\" \n", str);
}
