thread_local unsigned long externed_hoge = 0;
static thread_local unsigned long static_hoge = 0;

void general_dynamic_access() {
  externed_hoge = 0xaaaaaaaaaaaaaaaa;
}

void local_dynamic_access() {
  static_hoge = 0xbbbbbbbbbbbbbbbb;
}

