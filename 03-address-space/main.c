int data_section = 0x5555;
int bss_section;
const int rodata_section = 0xaaaa;

int main() {
  const char* str = "hello, world!";
  const char array[] = { 'a', 'b', 'c', 'd', 'e' };
  return 0;
}
