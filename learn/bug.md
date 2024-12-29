vscode 输出


解决方法：
https://stackoverflow.com/questions/75921414/java-symbol-lookup-error-snap-core20-current-lib-x86-64-linux-gnu-libpthread

unset GTK_PATH

unset GIO_MODULE_DIR

---
总是报以下错误：
Gtk-Message: Failed to load module “canberra-gtk-module”
解决办法：apt-get install .*canberra.*gtk.*