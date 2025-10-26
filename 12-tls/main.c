static thread_local unsigned long static_main = 0;
extern thread_local unsigned long externed_hoge;

void initial_executable_access() {
  externed_hoge = 0xffffffffffffffff;
}

void local_executable_access() {
  static_main = 0xdeadbeefdeadbeef;
}

int main() {
  return 0;
}
