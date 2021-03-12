#include <stdio.h>

int main(void)
{
	size_t i;
	unsigned int checksum;
	char	pass;
	char password[25];
	unsigned char key_bytes[25] = "\x1e\xcd\x2a\xd5\x34\x87\xfc\x78\x64\x35\x9d\xec\xde\x15\xac\x97\x99\xaf\x96\xda\x79\x26\x4f\x32\xe0";

	unsigned char shellcode[164] =
		"\xb8\x04\x00\x00\x00\xbb\x01\x00\x00\x00\xb9\xa1\x91\x04"
		"\x08\xba\x26\x00\x00\x00\xcd\x80\xb8\x03\x00\x00\x00\x31"
		"\xdb\xb9\x88\x91\x04\x08\xba\x33\x00\x00\x00\xcd\x80\x31"
		"\xc9\xb8\x80\x80\x04\x08\xbb\x23\x81\x04\x08\xe8\x5b\x00"
		"\x00\x00\x89\xca\xb9\x19\x00\x00\x00\xb8\x55\x91\x04\x08"
		"\xbb\x88\x91\x04\x08\xd1\xca\x8a\x44\x08\xff\x8a\x5c\x0b"
		"\xff\x30\xd8\x30\xd0\x75\x1b\x49\x75\xe3\xb8\x04\x00\x00"
		"\x00\xbb\x01\x00\x00\x00\xb9\x24\x91\x04\x08\xba\x26\x00"
		"\x00\x00\xcd\x80\xeb\x16\xb8\x04\x00\x00\x00\xbb\x01\x00"
		"\x00\x00\xb9\x4a\x91\x04\x08\xba\x0b\x00\x00\x00\xcd\x80"
		"\xb8\x01\x00\x00\x00\x31\xdb\xcd\x80\x29\xc3\x31\xc9\x02"
		"\x08\xc1\xc1\x03\x40\x4b\x75\xf7\xc3";

	asm(
		".intel_syntax noprefix;"
		"lea esi, [%1];"
		"mov ebx, 163;"
		"mov ecx, 0;"

	"_loop:"
		"add cl, [esi];"
		"rol ecx, 0x3;"
		"inc esi;"
		"dec ebx;"
		"jnz _Loop;"
		"mov %0, ecx;"

		".att_syntax;"
		:"=r" (checksum)
		:"r" (shellcode)
	);

	printf("Checksum: %x\n\n", checksum);

	for (i = 0; i < 25; i++) {
		checksum = (checksum >> 1) | (checksum << (32 - 1)); // ror by 1
		pass = checksum ^ (key_bytes[24 - i]);
		printf("%p xor %x = %c\n", checksum, key_bytes[24 - i], pass);
		password[24 - i] = pass;
	}
	printf("\n\nSerial: ");
	for (i = 0; i < 25; i++)
		printf("%c", *(password+i));
	return 0;
 }